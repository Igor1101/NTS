#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
/* Log */
#include <syslog.h>
/*prog*/
#include "NTS.h"
void arg_recognize(char* argv_1)
{
    if(argv_1==NULL)
    {
        return;/* Just start daemon */
    }
    else if(strcmp(argv_1,"--help")==0)
	{
        printf("\n\
\n\t\tNetwork Traffic Service\
\n\tRUN THIS AS ROOT!!!\
\nUsage: NTS [option]\
\n\t--console : run console also\
\n\t--consoleonly : run console, don`t run service\
\n\t--debug : switch service to debug mode\
\n\t--help : print help and exit\
\n\t if  no option specified, run service\
\n\t only 1st argument matters, other ignored\
\n\t Attention: every error, \
\n\teven not fatal ( for ex. caused by wrong paramameters given in cli ) \
\n\twill eventually stop daemon running, \
\n\tsuch method prevents segmentation faults or system damage\
\nA daemon which sniffs packets, \
\nsaves ip addresses and number of incoming packets from each ip to \
\n/var/log/NTS.log\
\nin format %%x:%%llx:%%s (or hex int converted ip address, \
\nlong long int (64bit) amount of packets, string iface).\
\n");
        NTS_exit(0);
    }
    else if(strcmp(argv_1,"--console")==0)
    {
        console_is_running=true;
        return;
    }
    else if(strcmp(argv_1,"--debug")==0)
    {
        printf("Will open debug promt under %s \n", PRG_STDOUT);
        console_is_running=true;
        return;
    }
    else
    {
        perror("Unknown option specified");
        NTS_exit(-1);
    }
}
void init_nts(char* argv_1)
{
    arg_recognize(argv_1);
    pid_t NTS_pid;
    /* set communication */
    pipe(NTS_pipe);
    switch(NTS_pid=fork())
    {
        case -1: {
                     perror("ERROR Cannot run child process(NTS)\n");
                     NTS_exit(-1);
                 }
        case 0: break;/*we are in child!*/
        default: /* run cli */
                if(console_is_running==true)
                {
                    NTS_cli(NTS_pid);
                }
                _exit(0); /* we are in parent! */
    }
    if(setsid() == -1)
    {
        fprintf(stderr, "ERROR this can`t be leader");
        NTS_exit(-1);
    }
    umask(0);
    /* reopen standard streams
     * or close them, if useless*/
    close(STDIN_FILENO); 
    if(argv_1 == NULL || strcmp(argv_1, "--debug")!=0)
    {
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        stdout = fopen("/dev/null", "w+");
	    stderr = fopen("/dev/null", "w+");
    }
    stdin = fopen("/dev/null", "r");
    chdir("/");
}
