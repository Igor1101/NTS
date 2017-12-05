#include <stdio.h>
#include <stdlib.h>
#include "NTS.h"
void openlogfile(void)
{
    if ((logfile = fopen(LOGFILE, "r+"))== NULL)
    {
        puts("Creating log for a first time");
        logfile = fopen(LOGFILE, "w+");
    }
}
unsigned int scanlogfile(void)
{
    /* return amount of items in logfile */
    unsigned int item=0;
    rewind(logfile);
    while(fscanf(logfile, "%x:%llx",
                &loginfo[item].ipv4,
                &loginfo[item].times) !=EOF)
    {
        if(item >= MAX_AMOUNT_OF_ADDRS)break;
        item++;
    }
    return item;
}
void writelogfile(void)
{
    unsigned int item;
    /* clear file */
    fclose(logfile);
    logfile = fopen(LOGFILE, "w+");
    for(item=0; item<amount_of_logaddr; item++)
    {
        fprintf(logfile, "%x:%llx\n", 
                loginfo[item].ipv4,
                loginfo[item].times);
    }
}
