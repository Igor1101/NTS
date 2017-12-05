/* NETWORK TRAFFIC SERVICE */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* socket headers */
#include <sys/socket.h>
#include <netinet/in.h> /* For SOCK_RAW */
/* logging info*/
#include <syslog.h>
/* NTS headers*/
#include "NTS.h"
/* macro and definitions */
#define FAMILY AF_INET
#define GREEN_FOREGROUND "\033[32m"
#define DEFAULT_FOREGROUND "\033[0m"
/*global variables*/
    char* message_buffer = "NOMEMORY";/*
                                         WE DONT NEED/
                                        WANT TO RECEIVE THIS DATA
                                       Just point to somewhere
                                       */
    int socketdesc;/*socket*/
    struct sockaddr  saddr;/* address info */
    unsigned int saddr_size = sizeof saddr;
/* functions */
void print_received_ip(void)
{
    printf( "%s%u:%u:%u:%u", 
            "\nIP: ",
            (unsigned char)saddr.sa_data[2],
            (unsigned char)saddr.sa_data[3],
            (unsigned char)saddr.sa_data[4],
            (unsigned char)saddr.sa_data[5]
            );
}
/* main */
int main(int argc, char** argv)
{   
    /* Try initialize IPv4 socket */
    socketdesc = socket(FAMILY, SOCK_RAW, IPPROTO_TCP);
    if(socketdesc == -1)
    {
        printf("Socket create error\nRUN with sudo, right?");
        exit(-1);
    }
    memset(loginfo, 0, sizeof(loginfo));
    /* Init daemon */
    if(argc>1)
    {
        init_nts(argv[1]);
    }
    else init_nts(NULL);
    /* start daemon session */
    openlogfile();
    /* for interrupts */
    set_signal_handler();
    /* read from file info, write to loginfo */
    amount_of_logaddr = scanlogfile();
    printf(GREEN_FOREGROUND);/*since this 
                               line every print to stdout (defined in NTS.h) 
                               works only if "-debug" arg added
                              */
    while(1)
    {
        /* clear signal info */
        signal_def = 0;
        if(recvfrom(socketdesc,
                    message_buffer, /* received data */
                    0, /* size of received data */
                    MSG_WAITALL/* just wait for IP info */,
                    &saddr,\
                    &saddr_size\
                    )
          )
        {
            puts("receive data error");
        }
        if(signal_def==0)
        {
            address_add(saddr);
            print_received_ip();
            writelogfile();
        }
    }
    return 0;
}
