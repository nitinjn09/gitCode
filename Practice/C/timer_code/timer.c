#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>

void test_func();
void timer_handler (int signum)
{
    static int count = 0;
    time_t t;
    time(&t);
    printf ("count %d time : %s",++count, ctime(&t));
    test_func();
}

void test_func() {
    printf("%s %s I am in test function\n",__DATE__, __TIME__);
}

int main ()
{
    struct sigaction sa;
    struct itimerval timer;

    /* Install timer_handler as the signal handler for SIGVTALRM. */
    memset (&sa, 0, sizeof (sa));

    sa.sa_handler = &timer_handler;

    sigaction (SIGVTALRM, &sa, NULL);
    /* Configure the timer to expire after 1 sec... */
    timer.it_value.tv_sec = 5;
    timer.it_value.tv_usec = 0;
    /* ... and every 1000 msec after that. */
    timer.it_interval.tv_sec = 2;
    timer.it_interval.tv_usec = 0;
    /* Start a virtual timer. It counts down whenever this process is
     *    executing. */
    setitimer (ITIMER_VIRTUAL, &timer, NULL);
    /* Do busy work. */
    while(1);
      //sleep(3); 
}
