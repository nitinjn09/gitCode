#include <stdio.h>

/************************/
void fun1(int a) { 
    printf("I am in fun1, value of a : %d\n", a);
}

void fun2(int b) {
    printf("I am in fun2, Value of b is : %d\n",b);
}

void wrapper(int a, void (*fun)()) {
    
    fun(a);
}

/*************************/

float Plus (float a, float b) { return a+b; }
float Minus (float a, float b) { return a-b; }
float Multiply(float a, float b) { return a*b; }
float Divide (float a, float b) { return a/b; } // b!=0 is assumed 

float 
operation_wrapper (float a, float b, float (*operation)(float,float)) {

    float result = operation(a,b);
    return result;
}

int main () 
{
    /************/
    wrapper(10, fun1);
    wrapper(20, fun2);
    /************/
    
   float result = operation_wrapper(10, 20, Plus);
   printf("Result of Plus = %f\n",result);

    return 0;
}
