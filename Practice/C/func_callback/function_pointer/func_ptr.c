#include <stdio.h>

int test_func (int a, int b)
{
    printf("Value of a and b are : %d, %d \n",a,b);
    return a+b;
}

int main ()
{
    int (*fp)(int, int) = &test_func;
    
    int (*fp1)(int, int); 
    fp1 = test_func;
    
    (*fp)(10,20);
    fp1(15,25);
    return 0;
}
