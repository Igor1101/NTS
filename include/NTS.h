#ifndef NTS_H
#define NTS_H
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <linux/if_ether.h>
#include <linux/ip.h>
/* Default inteface */
#ifndef DEFAULT_IF
#error "Specify default ethernet interface in your machine in cmake file"
#endif /* DEFAULT_IF */

/*THIS PROGRAM NAME*/
#ifndef PROG_NAME
#define PROG_NAME "NTS"
#endif /* PROG_NAME */
#define LOGFILE "/var/log/NTS.log"
#define PRG_STDOUT/* used only if -debug specified*/\
    "/dev/tty8"
#define MAX_IFACE_LEN 64
#define MAX_AMOUNT_OF_ADDRS/*program doesn`t use
                             memory allocation*/10240
/* 10K addresses, I`m sure, that`s more than enough */

/* Variables */
/* IP info Logfile */
FILE* logfile;
/* info structure*/
struct logaddr
{
    unsigned int ipv4;
    unsigned long long int times;
    char iface[MAX_IFACE_LEN];
};
char iface[MAX_IFACE_LEN];/* current full iface name */
int socketdesc;/*socket*/
/* Declared info array */
struct logaddr loginfo[MAX_AMOUNT_OF_ADDRS];
/* amount of addresses in logaddr*/
unsigned int amount_of_logaddr;
/* used for finding out type of signal\interrupt*/
int signal_def;
/* receive buffer */
unsigned char buffer[(sizeof(struct ethhdr) + sizeof(struct iphdr))];
/* functions */
/* daemon INIT */
void init_nts(char* argv_1);
/* signals process */
void signal_handler(int signal);
/* open or create new logfile for RW */
void openlogfile(void);
/* add address or increase counter  */
void address_add(struct in_addr saddr);
/* set signals*/
void set_signal_handler(void);
/* put info from logfile to loginfo return : amount of addresses*/
unsigned int scanlogfile(void);
/* put info from loginfo to logfile */
void writelogfile(void);
/* used in debug mode; print all address information */
void log_print(void);
#endif /* NTS_H */

