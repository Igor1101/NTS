#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
/* Log */
#include <syslog.h>
/*prog*/
#include "NTS.h"
void init_nts(char* argv_1)
{
    switch(fork())
    {
        case -1: {
                     perror("ERROR Cannot run child process(NTS)\n");
                     exit(-1);
                 }
        case 0: break;/*we are in child!*/
        default: _exit(0); /* we are in parent! */
    }
    /* setting syslog connection*/
    /*openlog(PROG_NAME, LOG_CONS, LOG_DAEMON);*/
    if(setsid() == -1)
    {
        syslog(LOG_ERR, "%s", "ERROR this cant be leader");
        exit(-1);
    }
    umask(0);
    /* reopen standard streams*/
    close(STDIN_FILENO); 
    if((argv_1!=NULL)&&!(strcmp(argv_1,"-debug")))
    {
	    stdout = fopen(PRG_STDOUT, "w+");
    }
    else
    {
        close(STDOUT_FILENO);
        stdout = fopen("/dev/null", "w+");
    }
    close(STDERR_FILENO);
    stdin = fopen("/dev/null", "r");
	stderr = fopen("/dev/null", "w+");
    chdir("/");
}
