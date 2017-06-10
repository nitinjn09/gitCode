#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main()
{
    printf("%s %s\n",__DATE__, __TIME__);
    sleep(61);
    printf("%s %s\n",__DATE__, __TIME__);
    sleep(2);
    return 0;
}
