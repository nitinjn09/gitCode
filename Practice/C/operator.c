#include<stdio.h>

int main ()
{
    int mast = 10;
    int val = 5;
    int enable = 1;
    int x;

    if (enable && ! (val&mast)) {
    printf(" Hi \n");
    }
    return 0;
}
