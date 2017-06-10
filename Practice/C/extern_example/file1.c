#include <stdio.h>

extern int test_count;
extern int test_func();
int main ()
{
    printf("I am in main function\n");
    test_func();
    return 0;
}
