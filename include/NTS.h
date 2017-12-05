#ifndef NTS_H
#define NTS_H
#include <stdio.h>
#include <sys/socket.h>

/*THIS PROGRAM NAME*/
#ifndef PROG_NAME
#define PROG_NAME "NTS"
#endif /* PROG_NAME */
#define LOGFILE "/var/log/NTS.log"
#define PRG_STDOUT/* used only if -debug specified*/\
    "/dev/tty8"
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
};
/* Declared info array */
struct logaddr loginfo[MAX_AMOUNT_OF_ADDRS];
/* amount of addresses in logaddr*/
unsigned int amount_of_logaddr;
/* used for finding out type of signal\interrupt*/
int signal_def;
/* functions */
/* daemon INIT */
void init_nts(char* argv_1);
/* signals process */
void signal_handler(int signal);
/* open or create new logfile for RW */
void openlogfile(void);
/* add address or increase counter  */
void address_add(struct sockaddr saddr);
/* set signals*/
void set_signal_handler(void);
/* put info from logfile to loginfo return : amount of addresses*/
unsigned int scanlogfile(void);
/* put info from loginfo to logfile */
void writelogfile(void);
/* used in debug mode; print all address information */
void log_print(void);
#endif /* NTS_H */

