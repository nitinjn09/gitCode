#include "array.h"

void selection_sort (int *arr, int size)
{
    int i, j, min_index, temp;
    for (i = 0; i < size; i++) {
        min_index = i;
        for (j = i; j < size; j++) {
            if (arr[min_index] > arr[j]) {
                min_index = j;
            }
        }
        swap_items(&arr[i], &arr[min_index]);
    }
}
