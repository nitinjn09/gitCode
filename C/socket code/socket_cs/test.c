#include<stdio.h>

struct test
{
int a;
struct test *next;
};

struct test t1;

int main()
{
printf("a = %d",t1.a);
if(t1.next == NULL) {
printf("\nNitin\n");
}
return 1;
}
