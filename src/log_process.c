#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NTS.h"

int compare_addresses(const void*a, const void*b)
{/* used by qsort, binary search 
  we use unsigned values, convert result to sign
  */
        if(((const struct logaddr*)a) -> ipv4 >
                ((const struct logaddr*)b) -> ipv4)
        {
            return 1;
        }
        else if(((const struct logaddr*)a) -> ipv4 <
                ((const struct logaddr*)b) -> ipv4)
        {
            return -1;/* a - b */
        }
        else
        {
            return 0;/* a==b*/
        }
}


void address_add(struct in_addr saddr)
{
    time_t timeSinceEpoch=time(NULL);
    unsigned int ip = saddr.s_addr;
    struct logaddr address;
    address.ipv4 = ip;
    /* if saddr in loginfo: */
    void*found = bsearch((void*)&address, 
            (void*)&loginfo, 
            amount_of_logaddr, 
            sizeof(struct logaddr),
            compare_addresses);
    if(found == NULL)
    {/* write address to array and sort array */
        loginfo[amount_of_logaddr].timeSinceEpoch = timeSinceEpoch;
        loginfo[amount_of_logaddr].ipv4 = ip;
        loginfo[amount_of_logaddr].times = 1;
        strcpy(loginfo[amount_of_logaddr].iface, iface);
        amount_of_logaddr++;
        if(amount_of_logaddr >= MAX_AMOUNT_OF_ADDRS)
        {
            perror("STATIC MEMORY OVERFLOW... exiting");
            pthread_mutex_lock(&logfileaccess);
            writelogfile();
            pthread_mutex_unlock(&logfileaccess);
            NTS_exit(-1);/* static memory overflow */
        }
        qsort((void*)&loginfo, 
                amount_of_logaddr, 
                sizeof(struct logaddr), 
                compare_addresses);
    }
    else
    {/* increase amount of times */
        ((struct logaddr*)found) -> times++;
     /* write last packet sniffed time */
        ((struct logaddr*)found) -> timeSinceEpoch = 
            timeSinceEpoch;
    }
}

