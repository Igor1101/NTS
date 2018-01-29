#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "NTS.h"
#define MAX_CMD_SIZE 0x10
#define MAX_ARG_SIZE 0x50
#define START   "s\0"
#define STOP   "p\0"
#define SHOW   "show\0"
#define SELECT   "select\0"
#define STAT   "stat\0"
/* start cli session
 ***********************
 *       NTS  CLI      *
 ***********************
 CMD    ARGS    SIGNALS TO NTS
 start              's'
 stop               'p'
 show   [hex_ip]  show\nxx:xx:xx:xx\n
 select [iface]   select\niface\n
 stat   [iface]   stat\niface\n
 [CMD]  --help
 quit
 */
void NTS_cli(pid_t NTS_pid)
{
    puts("Starting CLI");
    char cmd[MAX_CMD_SIZE];
    char arg[MAX_ARG_SIZE];
    char input[MAX_ARG_SIZE+MAX_CMD_SIZE];
    while(1)
    {
        memset(input, 0, sizeof input);
        printf("\n-> ");
        fgets(input, MAX_CMD_SIZE+MAX_ARG_SIZE, stdin);
        sscanf(input,"%s%s", cmd, arg);
        if( cmd!=NULL && strcmp(cmd, "start")==0)
        {
            puts("starting...");
            write(NTS_pipe[1], START, sizeof START);
        }
        else if( cmd!=NULL && strcmp(cmd, "stop")==0)
        {
            puts("pause...");
            write(NTS_pipe[1], STOP, sizeof STOP);
        }
    }
}

