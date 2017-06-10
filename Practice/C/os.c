#include <stdio.h>
#include  <sys/types.h>
#include <stdlib.h>
#include <unistd.h> 

int main()
{
    int i = 7;
    int *p = &i;
    if (fork()) { //Parent process 
        *p = *p + 10; printf("parent %d\n", i); 
    } else { // child process
        wait(0); 
        printf("child %d\n" , i); 
    }
    return 0;
}
