#include <stdio.h>
#include <stdlib.h>
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
        loginfo[amount_of_logaddr].ipv4 = ip;
        loginfo[amount_of_logaddr].times = 1;
        amount_of_logaddr++;
        if(amount_of_logaddr >= MAX_AMOUNT_OF_ADDRS)
        {
            exit(-1);/* static memory overflow */
        }
        qsort((void*)&loginfo, 
                amount_of_logaddr, 
                sizeof(struct logaddr), 
                compare_addresses);
    }
    else
    {/* increase amount of times */
        ((struct logaddr*)found) -> times++;
    }
}
void log_print(void)
{/* print all info(used in debug mode) */
    unsigned int item;
    printf("%s%u", "\n\n\n\nLOG INFO\nAMOUNT OF ADDRESS: ", amount_of_logaddr);
    for(item=0; item<amount_of_logaddr; item++)
    {
        printf("%s %u:%u:%u:%u %s %llu\n", 
                "IP:",
                loginfo[item].ipv4&0xFF,/* XX:00:00:00 */
                (loginfo[item].ipv4>>8)&0xFF,/* 00:XX:00:00 */
                (loginfo[item].ipv4>>16)&0xFF,/* 00:00:XX:00 */
                loginfo[item].ipv4>>24,/* 00:00:00:XX */
                "TIMES:",
                loginfo[item].times
                );
    }
}
