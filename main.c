/* NETWORK TRAFFIC SERVICE */
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
#include <linux/if_ether.h> /* protocols */
/* ioctl */
#include <sys/ioctl.h>
#include <linux/if.h> /* documented as net/if.h */
/* logging info*/
#include <syslog.h>
/* ERROR process*/
#include <errno.h>
/* NTS headers*/
#include "NTS.h"
/* macro and definitions */
#define GREEN_FOREGROUND "\033[32m"
#define DEFAULT_FOREGROUND "\033[0m"
/*global variables*/
    struct sockaddr  saddr;/* address info */
    struct sockaddr_in* saddr_conv;/* address info */
    char addr_conv[32];
    unsigned int saddr_size = sizeof (struct sockaddr_ll);
    struct ifreq ifinfo; /* Inteface info */
/* functions */
void print_received_ip(void)
{
    printf( "%s%s", 
            "\nIP: ",
            inet_ntop(AF_INET6, &saddr_conv->sin_addr, (char*)&addr_conv, sizeof(addr_conv))
            );
}
int init_socket( char* device)
{/* return: socket fd*/
#define EXIT close(socketf);\
              exit(-1);
    static struct ifreq ifinfo;
    static struct sockaddr_ll addr;
    int socketf;
    memset(&ifinfo, 0, sizeof (ifinfo));
    memset(&addr, 0, sizeof (addr));
    /* Try initialize  socket */
    if((socketf = socket(AF_PACKET, SOCK_RAW, htons(ETH_P_ALL))) == -1)
    {
        fprintf(stderr, "socket create ERROR: %s\n", strerror(errno));
        EXIT
    }
    /* set device name */
    strcpy(ifinfo.ifr_name, device);
    /* get existing flags */
    if(ioctl(socketf, SIOCGIFFLAGS, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl get ERROR: %s\n", strerror(errno));
        EXIT
    }
    ifinfo.ifr_flags |= IFF_PROMISC;
    /* enter promiscuous mode */
    if(ioctl(socketf, SIOCSIFFLAGS, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl set ERROR: %s\n", strerror(errno));
        EXIT
    }
    if(ioctl(socketf, SIOCGIFADDR, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl get addr: %s\n", strerror(errno));
        EXIT
    }
    if(ioctl(socketf, SIOCGIFINDEX, &ifinfo) == -1)
    {
        fprintf(stderr, "ioctl configuring ERROR: %s\n", strerror(errno));
        EXIT
    }
    addr.sll_family = AF_PACKET/*AF_PACKET*/;
    addr.sll_ifindex = ifinfo.ifr_ifindex;
    addr.sll_protocol = htons(ETH_P_ALL);
    if(bind(socketf, (struct sockaddr*)&addr, sizeof(struct sockaddr_ll)) == -1)
    {
        fprintf(stderr, "bind error :%s\n", strerror(errno));
    }
#undef EXIT
    return socketf;
}
/* main */
int main(int argc, char** argv)
{   
    socketdesc = init_socket(DEFAULT_IF);
    /* clear info buffer */
    memset(loginfo, 0, sizeof(loginfo));
    /* Init daemon */
    if(argc>1)
    {
        init_nts(argv[1]);
    }
    else init_nts(NULL);
    /* start daemon session 
     ***********************
     *         NTS         *
     ***********************
     */
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
                    NULL, /* received data */
                    0, /* size of received data */
                    0/*MSG_WAITALL*//* just wait for IP info */,
                    &saddr,\
                    &saddr_size\
                    )
          )
        {
            printf("receive ERROR: %s\n", strerror(errno));
        }
        else if(signal_def==0)
        {
            saddr_conv = (struct sockaddr_in*)&saddr;
            address_add(saddr);
            print_received_ip();
            writelogfile();
        }
    }
    return 0;
}
