#include <signal.h>
#include <stdlib.h>
#include "NTS.h"
/* process sys signals */
void signal_handler(int signal)
{
    signal_def = signal;
    switch(signal)
    {
        case SIGHUP:
            {
                fflush(logfile);
                puts("NTS: SIGHUP");
                fflush(stdout);
                return;
            }
        case SIGINT:
            {
                puts("NTS: CTRL-C");
                log_print();/* Year, print log info*/
                fflush(stdout);
                return;
            }
        case SIGTERM:
            {
                fclose(logfile);
                puts("NTS: SIGTERM");
                fflush(stdout);
                exit(0);
            }
        default:
            {
                signal_def = -1;
                /* Unknown signal*/
                return;
            }
    }
}

void set_signal_handler(void)
{
    struct sigaction act;
    sigemptyset(&act.sa_mask);
    act.sa_handler = signal_handler;
    act.sa_flags = SA_RESTART;/* needed by recvmsg*/
    /*Signals*/
    sigaction(SIGHUP, &act, NULL);
    sigaction(SIGINT, &act, NULL);
    sigaction(SIGTERM, &act, NULL);
}
