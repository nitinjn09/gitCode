#include <stdio.h>

void test_func (int a) {
    printf("Value of a is %d\n",a);
}

int main (void)
{
void (*fun_ptr)(int) = &test_func;

/*
 * Above code is equivalent to:
 * void (*fun_ptr)(int);
 * fun_ptr = &test_func;
 */

(*fun_ptr)(10);
//We can also use  fun_ptr(10)
fun_ptr(20);
return 0;
}
