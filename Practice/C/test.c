#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int check_palindrom_num(int);
int check_palindrome_str(char[]);
int main ()
{
/*
    int *p = malloc(sizeof(int));
    if (p == NULL) {
        printf("Error in malloc\n");
        return 0;
    }
    int x = 10;
    p = &x;
    free(p);
    printf("char is %d\n",*p);
    
    
  */  
    
    /*   for (int a=0; a<10; a++) {
        static int flag = 1;
        if(flag) {
            flag = 0;
            printf("Nitin\n");
        }
    }
   */
/*
    int num;
    printf("Enter the number to check if taht is palindrom: ");
    scanf("%d",&num);
    check_palindrom_num(num); */
/*
    char str[50];
    printf("Enter string to check if that is Palindrome\n");
    scanf("%s",str);
    check_palindrome_str(str) ? printf("String %s is palindrom\n",str) : printf("String %s is not palindrom\n", str);
  */
    int n = printf("Heloo world");
    printf("\nn = %d\n",n);
    while(!printf("Hi nitin\n")) {}
    return 0;
}


int check_palindrome_str(char *str) {
    int len = strlen(str);
    int tlen = len-1, i = 0;
    while (i < tlen) {
        if (str[i] == str[tlen]) {
            i++, tlen--;
        } else {
            return 0;
        }
    }
    return 1;
}

int check_palindrom_num (int num) {
    int sum = 0, r = 0, n = num;

    while(n>0) {
        r = n%10;
        sum = sum*10 + r;
        n = n/10;
    }
    (sum == num) ? printf("Number %d is palindrom\n",num) : printf("Number %d is not palindrom\n", num);
    return (sum == num);
}
