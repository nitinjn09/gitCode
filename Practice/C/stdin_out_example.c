#include <stdio.h>

int main (int argc, char *argv[]) 
{
    char buff[50];
    printf("Program name is : %s\n",argv[0]);
    fgets(buff, sizeof(buff), stdin);
    fprintf(stdout, "input taken from stdin : %s", buff);
    fputs(buff, stdout);
    fprintf(stdout, "This is test output to console via stdout\n");
    return 0;
}
