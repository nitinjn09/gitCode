#include "array.h"

void merge (int *arr, int left, int mid, int right) 
{
    int i, j, k = left;
    int nl = mid - left +1, nr = right - mid;
    int L[nl], R[nr];

    for (i = 0; i < nl; i++) {
        L[i] = arr[left + i];
    }
    for (j = 0; j < nr; j++) {
        R[j] = arr[mid + j + 1];
    }

    for (i = 0, j = 0; (i < nl) && (j < nr); k++) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
    }

    while (i < nl) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < nr) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void merge_sort ( int *arr, int left, int right) 
{
    if (left < right) {
        int mid;
        mid = ceil((left + right) / 2);
        merge_sort(arr, left, mid);
        merge_sort(arr, mid+1, right);
        merge(arr, left, mid, right);
    }
}


