#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main()
{
    time_t t;
    time(&t);
    printf("Today's date and time : %s",ctime(&t));
    sleep(5);
    time(&t);
    printf("Today's date and time : %s",ctime(&t));
}
