/* 
 * (c) 2018 Igor Muravyov
 * All rights reserved
 */
/* NETWORK TRAFFIC SERVICE */
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
/* socket headers */
#include <sys/socket.h>
#include <netinet/in.h> /* For SOCK_RAW */
#include <arpa/inet.h> /* for htons */
#include <netpacket/packet.h> /* for protocol defs*/
#include <net/ethernet.h> /* protocols */
#include <netinet/if_ether.h> /* protocols */
#include <netinet/ip.h>
/* ioctl */
#include <sys/ioctl.h>
#include <linux/if.h> /* documented as net/if.h, 
                         but net/if.h does not work */
/* logging info*/
/* ERROR process*/
#include <errno.h>
/*threads */
#include <pthread.h>
/* signals */
#include <signal.h>
/* NTS headers*/
#include "NTS.h"
/* macro and definitions */
#define MAX_INPUT_SIZE 64
#define MAX_OUTPUT_SIZE 128
#define read_cli read(to_NTS_pipe[0], input_buf, sizeof(input_buf))
#define write_cli write(from_NTS_pipe[1], output_buf, sizeof(output_buf))
/*global variables*/
    struct sockaddr_ll  saddr;/* address info */
    struct sockaddr_in*  saddr_conv;/* address info */
    char addr_conv[INET_ADDRSTRLEN];
    unsigned int saddr_size = sizeof (struct sockaddr_ll);
    struct ifreq ifinfo; /* Inteface info */
    struct iphdr*ipinfo = (struct iphdr*)(buffer + sizeof(struct ethhdr));
    pthread_t NTS_recv;/* recvfrom thread */
/* functions */
void respond_NTS(void);
void print_received_ip(void)
{
    printf( "%s%s IFACE: %s", 
            "\nIP: ",
            inet_ntop(AF_INET, /* AF_PACKET 
                                *  is not suppoted
                                *  by inet_ntop */
                &saddr_conv->sin_addr, 
                (char*)&addr_conv, 
                sizeof(addr_conv)),
                iface
            );
}
int init_socket( char* device)
{/* return: socket fd*/
    static struct ifreq ifinfo;
    static struct sockaddr_ll addr;
    int socketf;
    memset(&ifinfo, 0, sizeof (ifinfo));
    memset(&addr, 0, sizeof (addr));
    /* Try initialize  socket */
    if((socketf = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_IP))) == -1)
    {
        fprintf(stderr, "socket create ERROR: %s\n", strerror(errno));
        NTS_exit(-1);
    }
    /* set device name */
    strcpy(ifinfo.ifr_name, device);
    /* get existing flags */
    if(ioctl(socketf, SIOCGIFFLAGS, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl get ERROR: %s\n", strerror(errno));
        NTS_exit(-1);
    }
    ifinfo.ifr_flags |= IFF_PROMISC;
    /* enter promiscuous mode */
    if(ioctl(socketf, SIOCSIFFLAGS, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl set ERROR: %s\n", strerror(errno));
        NTS_exit(-1);
    }
    if(ioctl(socketf, SIOCGIFADDR, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl get addr: %s\n", strerror(errno));
        NTS_exit(-1);
    }
    if(ioctl(socketf, SIOCGIFINDEX, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl configuring ERROR: %s\n", strerror(errno));
        NTS_exit(-1);
    }
    addr.sll_family = AF_PACKET/*AF_PACKET*/;
    addr.sll_ifindex = ifinfo.ifr_ifindex;
    addr.sll_protocol = htons(ETH_P_ALL);
    if(bind(socketf, (struct sockaddr*)&addr, sizeof(struct sockaddr_ll)) == -1)
    {
        fprintf(stderr, "bind error :%s\n", strerror(errno));
        NTS_exit(-1);
    }
    return socketf;
}
void recv_thread(void)
{
    /* Ignore all not
     * important signals
     * */
    sigset_t signals;
    sigfillset(&signals);/*fill signals*/
    sigdelset(&signals, SIGKILL);
    if(pthread_sigmask(SIG_BLOCK, &signals, NULL)!=0)
    {
        printf("sigmask: %s, something strange is going on\n", strerror(errno));
        NTS_exit(-1);
    }
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    while(1)
    {
        if(recvfrom(socketdesc,
                    buffer /* received data */,
                    sizeof (buffer) /* size of received data */,
                    0/* MSG_WAITALL *//* just wait for IP info
                                       with MSG_WAIT it doesn`t work...
                                       */,
                    (struct sockaddr*)&saddr,\
                    &saddr_size\
                    ) == -1
         )
        {
            printf("receive ERROR: %s, error ignored\n", strerror(errno));
        }
        else 
        {
            if(/*(saddr.sll_pkttype == PACKET_HOST)||*//*
                                                        * local address 
                                                        * */
                /*(saddr.sll_pkttype == PACKET_BROADCAST)||*/
                (saddr.sll_pkttype == PACKET_MULTICAST)||
                (saddr.sll_pkttype == PACKET_OTHERHOST)||
                (saddr.sll_pkttype == PACKET_OUTGOING)
                    )
            {
                pthread_mutex_lock(&logaccess);
                address_add(saddr_conv->sin_addr);
                pthread_mutex_unlock(&logaccess);
                print_received_ip();
            }
        }
    }
    /* this thread NEVER die itself */
}


void respond_NTS(void)
{
    char input_buf[MAX_INPUT_SIZE];
    char output_buf[MAX_OUTPUT_SIZE];
    bool recv_from_ON=false;
    pthread_mutex_init(&logaccess, NULL);
    pthread_mutex_init(&logfileaccess, NULL);
    puts("respond NTS running");
    while(1)
    {
        memset(input_buf, 0, sizeof input_buf);
        read_cli;
        if(strlen(input_buf) !=0 ) 
        {
            puts("CLI COMMAND:");
            puts(input_buf);
        }
        if(strcmp(input_buf, "p")/* stop */== 0 
                && recv_from_ON == true)
        {
            puts("closing recvfrom");
            /* wait untill loginfo accessible 
             * and destroy recvfrom thread*/
            pthread_mutex_lock(&logaccess);
            pthread_cancel(NTS_recv);
            pthread_mutex_unlock(&logaccess);
            recv_from_ON = false;
        }
        else if(strcmp(input_buf, "s")/* start */== 0 
                && recv_from_ON == false)
        {
            puts("opening recvfrom");
            pthread_create(&NTS_recv, NULL, (void*) &recv_thread, NULL);
            recv_from_ON = true;
        }
        else if(strncmp(input_buf, "w", 1) == 0)
        {/* show */
            unsigned int addr;
            sscanf(input_buf, "%c %x", input_buf, &addr);
            pthread_mutex_lock(&logaccess);/* wait, untill 
                                            * array`ll be sorted */
            /* search in current iface */
            void*found = bsearch((void*)&addr, 
                        (void*)&loginfo, 
                        amount_of_logaddr, 
                        sizeof(struct logaddr),
                        compare_addresses);
            if(found != NULL)
            {
                printf("RESULT: %llx", ((struct logaddr*)found) -> times
                /* only for current iface */);
                sprintf(output_buf, "%llu", ((struct logaddr*)found) -> times);
            }
            else
            {
                strcpy(output_buf, "0\n");
            }
            pthread_mutex_unlock(&logaccess);
            write(from_NTS_pipe[1], output_buf, strlen(output_buf));
        }
        else if(strncmp(input_buf, "l", 1) == 0)/* select iface*/
        { /*stop recv*/
            if(recv_from_ON == true)
            {
                pthread_mutex_lock(&logaccess);
                pthread_cancel(NTS_recv);
                pthread_mutex_unlock(&logaccess);
            }
            sscanf(input_buf, "%c %s", input_buf, iface);
            pthread_mutex_lock(&logfileaccess);
            writelogfile();
            pthread_mutex_unlock(&logfileaccess);
            scanlogfile();
            socketdesc = init_socket(iface);
            if(recv_from_ON == true)
            {
                pthread_create(&NTS_recv, NULL, (void*) &recv_thread, NULL);
            }
        }
        else if(strncmp(input_buf, "a", 1) == 0)/* stat iface*/
        { /* update log file and write answer*/
            pthread_mutex_lock(&logaccess);
            pthread_mutex_lock(&logfileaccess);
            writelogfile();
            fflush(logfile);
            pthread_mutex_unlock(&logfileaccess);
            pthread_mutex_unlock(&logaccess);
            write(from_NTS_pipe[1], "s\n", 2 );
            puts("successfully updated");
        }

    }
}
/* main */
int main(int argc, char** argv)
{   
    if(geteuid()!=0)
    {
        setfor;
        puts("run this as root or errors can occur");
    }
    /* Init daemon */
    if(argc>1)
    {
        setfor;
        init_nts(argv[1]);
         /* set interface */
        strcpy(iface, DEFAULT_IF);
        socketdesc = init_socket(DEFAULT_IF);
        /* clear info buffer */
        memset(loginfo, 0, sizeof(loginfo));
    }
    else
    { 
        init_nts(NULL);
        /* set interface */
        strcpy(iface, DEFAULT_IF);
        socketdesc = init_socket(DEFAULT_IF);
        /* clear info buffer */
        memset(loginfo, 0, sizeof(loginfo));
    }
    /* start daemon session 
     ***********************
     *         NTS         *
     ***********************
     */
    openlogfile();
    /* for interrupts */
    set_signal_handler();
    /* read from file info, write to loginfo */
    scanlogfile();
    saddr_conv = (struct sockaddr_in*)&ipinfo->saddr;
    respond_NTS();
    while(1);
}
