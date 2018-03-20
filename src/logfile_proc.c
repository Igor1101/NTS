#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NTS.h"
void openlogfile(void)
{
    if ((logfile = fopen(LOGFILE, "r+"))== NULL)
    {
        puts("Creating log for a first time");
        logfile = fopen(LOGFILE, "w+");
    }
}
void scanlogfile(void)
{
    /* return amount of items in logfile */
    unsigned int item=0;
    unsigned int itemnotcur=0;
    rewind(logfile);
    while(fscanf(logfile, "%x:%llx:%lx:%s\n",
                &loginfo[item].ipv4,
                &loginfo[item].times,
                &loginfo[item].timeSinceEpoch,
                loginfo[item].iface
                ) != EOF/* Size of iface is not 
                                              verified in file!!!*/
            )
    {
        if(item >= MAX_AMOUNT_OF_ADDRS)break;/*buffer overflow, 
                                               read what we can read */
        if(strcmp(iface, loginfo[item].iface)!=0)
        {
            lognotcurrent[itemnotcur].ipv4 = loginfo[item].ipv4;
            lognotcurrent[itemnotcur].times = loginfo[item].times;
            strcpy(lognotcurrent[itemnotcur].iface, loginfo[item].iface);
            itemnotcur++;
        }
        else
        { 
            item++;
        }
    }
    amount_of_notcurrent=itemnotcur;
    amount_of_logaddr=item;
}
void writelogfile(void)
{
    unsigned int item;
    /* clear file */
    fclose(logfile);
    logfile = fopen(LOGFILE, "w+");
    for(item=0; item<amount_of_logaddr; item++)
    {
        fprintf(logfile, "%x:%llx:%lx:%s\n", 
                loginfo[item].ipv4,
                loginfo[item].times,
                loginfo[item].timeSinceEpoch,
                loginfo[item].iface);
    }
    for(item=0; item<amount_of_notcurrent; item++)
    {
        fprintf(logfile, "%x:%llx:%lx:%s\n", 
                lognotcurrent[item].ipv4,
                lognotcurrent[item].times,
                loginfo[item].timeSinceEpoch,
                lognotcurrent[item].iface);
    }
}
