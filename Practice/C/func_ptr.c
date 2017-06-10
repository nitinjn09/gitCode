#include <stdio.h>

void add(int a, int b)
{

    printf("Sum is %d\n",a+b);
}

void sub(int a, int b) 
{
    printf("sub is %d\n",a-b);
}

int wrap(void fun())
{
    fun(10,20);
    return 0;
}

void multiply(int a, int b)
{
    printf("Mul = %d\n",a*b);
}

int main()
{
    void (*ptr[])(int, int) = {add, sub, multiply};

    int choice;

    printf("Enter 0 for add, 1 for subtraction and 2 for multiplication\n");
    scanf("%d",&choice);

    if (choice > 2) {
        return 0;
    }

    (ptr[choice])(10,20);
    // (ptr[0])(10,20);
    //(ptr[1])(20,10);
    wrap(add);

    return 0;
}
