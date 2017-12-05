#include <stdio.h>
#include <stdlib.h>
#include "NTS.h"

int compare_addresses(const void*a, const void*b)
{/* used by qsort, binary search */
    return(signed int)
        (((const struct logaddr*)a) -> ipv4 - ((const struct logaddr*)b) -> ipv4);
}


void address_add(struct sockaddr saddr)
{
    /*convert ipv4 XX:XX:XX:XX into 0xXXXXXXXX */
    unsigned int ip = (((unsigned char)saddr.sa_data[2])<<24) + 
        (((unsigned char)saddr.sa_data[3])<<16) +
        (((unsigned char)saddr.sa_data[4])<<8) +
        (unsigned char)saddr.sa_data[5];
    struct logaddr address;
    address.ipv4 = ip;
    /* if saddr in loginfo: */
    void*found = bsearch((void*)&address, 
            (void*)&loginfo, 
            amount_of_logaddr+1, 
            sizeof(address),
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
                sizeof(address), 
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
                loginfo[item].ipv4>>24,/* FF:00:00:00 */
                (loginfo[item].ipv4>>16)&0xFF,/* 00:FF:00:00 */
                (loginfo[item].ipv4>>8)&0xFF,/* 00:00:FF:00 */
                loginfo[item].ipv4&0xFF,
                "TIMES:",
                loginfo[item].times
                );
    }
}
