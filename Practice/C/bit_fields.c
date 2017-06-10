#include <stdio.h>


int main(int argc, char *argv[]) 
{
    typedef struct test {
        int age  : 5;
        char year : 5;
    } Age;
    Age a;
    printf("size of struct Age : %ld\n",sizeof(Age));
    a.age = 10;
    printf("Age.age = %d\n", a.age);
    return 0;
}
