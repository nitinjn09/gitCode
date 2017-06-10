#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

void binary_str(int); //Generate all strings of n bits. Assuming A[0,....,n-1] is an array of size n.
char A[4];
void k_string(int, int); // Generate all string of length n drwan from 0....k-1.
void convert_digit_to_char(int);
void convert_char_to_digit(char);

int main ()
{
    /*
    uint8_t num8 = 255;
    printf("num8  = %d\n",num8);

    unsigned long long int n;
    
    printf("\n uint8_t  size = %lu\n",sizeof(uint8_t));
    printf("\n uint16_t size = %lu\n",sizeof(uint16_t));
    printf("\n uintt_32 size = %lu\n",sizeof(uint32_t));
    printf("\n uint64_t size = %lu\n",sizeof(uint64_t));
    */
    //printf("Array A is %s: \n",A);
//    binary_str(3);
//    k_string(4, 3);
    
   convert_digit_to_char(9);
   convert_char_to_digit('9');
    
    
    return 0;
}

void convert_digit_to_char(int a) {
    char ch;
    ch = a + '0';
    printf("Int: %d, char %c\n", a, ch);
}

void convert_char_to_digit(char ch) {
    int a;
    a = ch - '0';
    printf("char: %c, Int: %d\n", ch, a);
}

void binary_str(int n) {
    if (n < 1) {
        printf("%s\n",A);
        //printf("HI");
    } else {
        A[n-1] = '0';
        binary_str(n-1);
        A[n-1]  ='1';
        binary_str(n-1);
    }
}

void k_string(int n, int k) {
    if(n < 1) {
        printf("%s\n",A);
    } else {
        for (int j = 0; j < k; j++) {
         //   char jj = j;
            A[n-1] = j + '0';
            k_string(n-1, k);
        }
    }
}


