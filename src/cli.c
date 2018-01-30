#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <errno.h>
#include "NTS.h"
#define MAX_CMD_SIZE 0x10
#define MAX_ARG_SIZE 0x50
#define MAX_NTS 256
#define START   "s\0"
#define STOP   "p\0"
#define SHOW   "w"
#define SELECT   "l"
#define STAT   "a"
/* start cli session
 ***********************
 *       NTS  CLI      *
 ***********************
 CMD    ARGS    SIGNALS TO NTS          FROM NTS
 start              s\n                success/fault
 stop               p\n                success/fault
 show   [ip]      w xx.xx.xx.xx\n     unsigned decimal
 select [iface]   l:iface\n      success/fault
 stat   [iface]   a:iface\n        long string; just output
 quit          -|
 exit           |==> CMD internal commands
 [CMD]  --help -|
 */
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
        printf("-> ");
        fgets(input, MAX_CMD_SIZE+MAX_ARG_SIZE, stdin);
        sscanf(input,"%s%s", cmd, arg);
        if( cmd!=NULL && strcmp(cmd, "start")==0)
        {
            if(arg!=NULL && strcmp(arg, "--help")==0)
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
        else if( cmd!=NULL && strcmp(cmd, "stop")==0)
        {
            if(arg!=NULL && strcmp(arg, "--help")==0)
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
        else if( cmd!=NULL && strcmp(cmd, "show")==0)
        {
            if(arg!=NULL && strcmp(arg, "--help")==0)
            {
                printf("usage: show x.x.x.x ;  \
 show packet count, ex: \n show 127.0.0.1");
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
                    if(write(to_NTS_pipe[1], hex_addr, strlen(hex_addr)+1)==-1)
                    {
                        perror("cannot write to pipe");
                    }
                    read(from_NTS_pipe[0], from_NTS, sizeof from_NTS);
                    puts(from_NTS);
                }
            }

        }
    }
}

