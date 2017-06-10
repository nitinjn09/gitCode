#include <stdio.h>
#include <stdlib.h>

int main() 
{
    //int arr[5];
    //int *ptr = arr;
    //int *newPtr;


    char *str = (char*) calloc(10, sizeof(char));    
    int *array = (int*) calloc(10,  sizeof(int));
    
    for (int i = 0;i <10; i++) {
        array[i] = i;
        str[i] = i + 65;
    }

    //newPtr = (int*) realloc(ptr, 10); //--->run time  Error

    int *newArray = (int*) realloc(array, 20);
    printf("\n");
    for (int j = 0; j<12; j++) {
        printf("%d %c \n",array[j],str[j]);

    }
    printf("\n");
    return 0;
}
