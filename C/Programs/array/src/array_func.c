
#include "array.h"

void show_array (int *arr, int size)
{
    int i;
    printf("Array is:  ");
    for (i = 0; i < size; i++) {
        printf("%d",arr[i]);
        if (i != (size - 1)) {
            printf(",  ");
        }
    }
    printf("\n\n");

}

int search_element_in_array (int *arr, int size, int item) 
{
    int i;
    for (i = 0; i < size; i++) {
        if (item == arr[i]) {
            printf("item %d found at index %d\n", item, i);
            return i;
        }
    }
    printf("item %d not found\n", item);
    return -1;
}

void swap_items (int *a, int *b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}
