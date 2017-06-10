#include <stdio.h>
#include "bits.h"


int main ()
{
    int choice, size, num;
    int arr[9] = {1, 2, 3, 5, 6, 7, 8, 9, 10};
    size = sizeof(arr)/sizeof(int);

    while (1) {
        printf("Enter your choice\n "
               "1. Find missing number in array\n "
               "0. Exit\n");
        scanf("%d",&choice);

        switch (choice) {
            case 1:
                num = get_missing_number(arr, size);
                if (num != 0) {
                    printf("Missing number is : %d\n", num);
                } else {
                    printf("Element not found\n");
                }
                break;

            case 0: return 0;
            
            default:
                printf("Invalid choice. Enter again\n");
                break;
        }
    }

    /*
       int a = 10; //  1010 
        int b = 20; // 10100 
        int c = XOR(a,b); // c = 11110 = 30
        printf("XOR of %d and %d is %d\n",a, b, c);
        c = a^b;
        printf("a^b = %d\n",c);
    */


    return 0;
}

