#include "NTS.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
void all_log_print(char * arg)
{/* print all info(used in debug mode) 
    for all ifaces*/
    pid_t less_pid=1;
    int fd[2];
    if(arg != NULL)
    {
        pipe(fd);
        fflush(stdout);
        less_pid = fork();
    }
    if( less_pid > 0 )
    {
        if(arg != NULL)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);/* duplicate output */
            close(fd[1]);
        }
        unsigned int item;
        printf("%s%u\n", "\n\n\n\nLOG INFO\nAMOUNT OF ADDRESSES: ", 
                amount_of_logaddr);
        for(item=0; item<amount_of_logaddr; item++)
        {
            printf("%s %u.%u.%u.%u %s %llu %s %s\n", 
                    "IP:",
                    loginfo[item].ipv4&0xFF,/* XX:00:00:00 */
                    (loginfo[item].ipv4>>8)&0xFF,/* 00:XX:00:00 */
                    (loginfo[item].ipv4>>16)&0xFF,/* 00:00:XX:00 */
                    loginfo[item].ipv4>>24,/* 00:00:00:XX */
                    "TIMES:",
                    loginfo[item].times,
                    "IFACE:",
                    loginfo[item].iface
                    );
        }
        for(item=0; item<amount_of_notcurrent; item++)
        {
            printf("%s %u.%u.%u.%u %s %llu %s %s\n", 
                    "IP:",
                    lognotcurrent[item].ipv4&0xFF,/* XX:00:00:00 */
                    (lognotcurrent[item].ipv4>>8)&0xFF,/* 00:XX:00:00 */
                    (lognotcurrent[item].ipv4>>16)&0xFF,/* 00:00:XX:00 */
                    lognotcurrent[item].ipv4>>24,/* 00:00:00:XX */
                    "TIMES:",
                    lognotcurrent[item].times,
                    "IFACE:",
                    lognotcurrent[item].iface
                    );
        }
        if(arg != NULL)
        {
            close(STDIN_FILENO); 
            close(STDOUT_FILENO);
            waitpid(less_pid, NULL, 0);
            exit(0);
        }
    }
    else if(less_pid == 0)
    {
        close(fd[1]);
        dup2(fd[0], STDIN_FILENO);/* duplicate input */
        close(fd[0]);
        usleep(9999);
        execlp("less","less", NULL);
    }
    else
    {
        perror("cannot create child");
    }
}

void log_print(void)
{/* print all info(used in debug mode) */
    unsigned int item;
    printf("%s%u\n", "\n\n\n\nLOG INFO\nAMOUNT OF ADDRESSES: ", amount_of_logaddr);
    for(item=0; item<amount_of_logaddr; item++)
    {
        printf("%s %u.%u.%u.%u %s %llu %s %s\n", 
                "IP:",
                loginfo[item].ipv4&0xFF,/* XX:00:00:00 */
                (loginfo[item].ipv4>>8)&0xFF,/* 00:XX:00:00 */
                (loginfo[item].ipv4>>16)&0xFF,/* 00:00:XX:00 */
                loginfo[item].ipv4>>24,/* 00:00:00:XX */
                "TIMES:",
                loginfo[item].times,
                "IFACE:",
                loginfo[item].iface
                );
    }
}

