#include "array.h"

void bubble_sort (int *arr, int size)
{
    int i, j;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[j] > arr[j+1]) {
                swap_items(&arr[j], &arr[j+1]);
            }
        }
    }
}
