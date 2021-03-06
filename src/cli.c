#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include "NTS.h"
#define MAX_CMD_SIZE 0x10
#define MAX_ARG_SIZE 0x50
#define MAX_NTS 128
/* start cli session
 ***********************
 *       NTS  CLI      *
 ***********************
 CMD    ARGS    SIGNALS TO NTS          FROM NTS
 start              s\0                success/fault
 stop               p\0                success/fault
 show   [ip]      w xx.xx.xx.xx\n     unsigned decimal
 select [iface]   l iface\n             success/fault
 stat   [iface]   a iface\n             long string; 

 quit          -|
 exit           |==> CMD internal commands
 [CMD]  --help -|
 */
void print_stat(char * arg)
{
    logfile=fopen(LOGFILE, "r");
    if(arg!=NULL && strcmp(arg, "less") == 0)
    {
        strcpy(iface, DEFAULT_IF);
        scanlogfile();
        all_log_print("less");
    }
    else if(arg!=NULL && strlen(arg)!=0)
    {
        strcpy(iface, arg);
        scanlogfile();
        log_print();
    }
    else
    {
        strcpy(iface, DEFAULT_IF);
        scanlogfile();
        all_log_print(NULL);
    }

}

void NTS_cli(pid_t NTS_pid)
{
    puts("Starting CLI");
    char cmd[MAX_CMD_SIZE];
    char arg[MAX_ARG_SIZE];
    char input[MAX_ARG_SIZE+MAX_CMD_SIZE];
    char from_NTS[MAX_NTS];
    while(1)
    {
        memset(input, 0, sizeof input);
        memset(cmd, 0, sizeof cmd);
        memset(arg, 0, sizeof arg);
        memset(from_NTS, 0, sizeof from_NTS);
        usleep(9999);/* BSD\SYSTEM V function
                      * useful, when running from scripts 
                      * */
        printf("-> ");
        fgets(input, MAX_CMD_SIZE+MAX_ARG_SIZE, stdin);
        sscanf(input,"%s%s", cmd, arg);
        if( cmd != NULL && strcmp(cmd, "start")==0)
        {
            if(arg != NULL && strcmp(arg, "--help")==0)
            {
                printf("usage: start ; no args, \
 starting service with DEFAULT_IF");
            }
            else
            {
                puts("starting...");
                write(to_NTS_pipe[1], START, sizeof START);
            }
        }
        else if( cmd != NULL && strcmp(cmd, "stop")==0)
        {
            if(arg != NULL && strcmp(arg, "--help")==0)
            {
                printf("usage: stop ; no args, \
 pausing service, receiving info");
            }
            else
            {
                puts("pause...");
                write(to_NTS_pipe[1], STOP, sizeof STOP);
            }
        }
        else if( cmd != NULL && strcmp(cmd, "show") == 0)
        {
            if(arg != NULL && strcmp(arg, "--help") == 0)
            {
                printf("usage: show x.x.x.x ;  \
 show packet count, example: \n show 127.0.0.1");
            }
            else if(arg!=NULL && strlen(arg)!=0)
            {
                unsigned int converted_addr;
                char hex_addr[MAX_CMD_SIZE+MAX_ARG_SIZE];
                if(inet_pton(AF_INET, arg, &converted_addr)!=1)
                {
                    perror("wrong ip!");
                }
                else
                {
                    sprintf(hex_addr, "%s %x\n", SHOW, converted_addr);
                    write(to_NTS_pipe[1], hex_addr, strlen(hex_addr)+1);
                    read(from_NTS_pipe[0], from_NTS, sizeof from_NTS);
                    puts(from_NTS);
                }
            }

        }
        else if( cmd != NULL && strcmp(cmd, "select")==0)
        {
            if(arg != NULL && strcmp(arg, "--help")==0)
            {
                printf("usage: select [iface] ;  \
 \nAttention, if wrong iface selected (unavailable or uninitialized),\
 daemon will finish it`s work\n\
 if you want to see daemon error, run it in debug mode\n\
 example: \n select eth2");
            }
            else if(arg!=NULL && strlen(arg)!=0)
            {
                char str[MAX_CMD_SIZE+MAX_ARG_SIZE];
                sprintf(str, "%s %s\n", SELECT, arg);
                write(to_NTS_pipe[1], str, strlen(str)+1);
            }
        } 
        else if( cmd != NULL && strcmp(cmd, "stat")==0)
        {
            if(arg != NULL && strcmp(arg, "--help")==0)
            {
                printf("usage: stat [iface] ;  \
 iface is optional, write status info in format xx.xx.xx.xx:[times]\\n\n\
 example: \n stat");
            }
            else 
            {
                char str[MAX_CMD_SIZE+MAX_ARG_SIZE];
                sprintf(str, "%s %s\n", STAT, arg);
                write(to_NTS_pipe[1], str, strlen(str)+1);
                read(from_NTS_pipe[0], from_NTS, sizeof from_NTS);
                if(strcmp("s", from_NTS))/* 's' means success*/
                {
                    print_stat(arg);
                }
            }
        } 
        else if( cmd != NULL && strcmp(cmd, "less")==0)
        {
            if(arg != NULL && strcmp(arg, "--help")==0)
            {
                printf("usage: less ;  \
 same as stat [no args], but put all output into less \
 exit after less exited\
 example: \n stat");
            }
            else 
            {
                char str[MAX_CMD_SIZE+MAX_ARG_SIZE];
                sprintf(str, "%s %s\n", STAT, arg);
                write(to_NTS_pipe[1], str, strlen(str)+1);
                read(from_NTS_pipe[0], from_NTS, sizeof from_NTS);
                if(strcmp("s", from_NTS))/* 's' means success*/
                {
                    print_stat("less");
                }
            }
        } 
        else if( cmd != NULL && (strcmp(cmd, "exit")==0||strcmp(cmd, "quit")==0))
        {
            NTS_exit(0);
        }
        else if( cmd != NULL && (strcmp(cmd, "killNTS")==0))
	{
            if(arg != NULL && strcmp(arg, "--help")==0)
            {
                printf("usage: killNTS ;  \
\n\rsend SIGTERM to daemon, exit after\
 example: \n killNTS");
	    }
	    else
	    {
		if(kill(NTS_pid, SIGTERM)==-1)
		{
		    fprintf(stderr, strerror(errno));
		    exit(-1);
		}
		exit(0);
	    }
	}
    }
}

