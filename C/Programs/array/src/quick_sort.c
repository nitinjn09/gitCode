#include "array.h"


int partition (int *arr, int left, int right, int pivot)
{
    while (TRUE) {
        while (arr[++left] < arr[pivot]);
        while ((right > 0) && (arr[--right] > arr[pivot]));
        if (left >= right) {
            break;
        } else {
            swap_items(&arr[left], &arr[right]);
        }
    }
    swap_items(&arr[left], &arr[pivot]);
    return left;
}

void quick_sort (int *arr, int left, int right)
{
    if (right - left <= 0) {
        return;
    }

    int pivot = right;
    int pptr = partition(arr, left, right, pivot);
    quick_sort(arr, left, pptr-1);
    quick_sort(arr, pptr+1, right);
}
