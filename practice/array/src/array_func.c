#include <stdio.h>
#include <stdlib.h>
#include <math.h>
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
/*
void insertion_sort (int *arr, int size)
{
    int i,j, pos;
    for (i = 0; i < size; i++) {
        for (j = 0; j < size; j++) {
            if (arr[i] > arr[j]) {
                pos  = j;


*/

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

void heapify (Heap *maxheap, int index)
{
    int largest = index;
    int left  = 2*index + 1;
    int right = 2*index + 2;

    if ((left < maxheap->size) && (maxheap->array[left] > maxheap->array[largest])) {
        largest = left;
    }

    if ((right < maxheap->size) && (maxheap->array[right] > maxheap->array[largest])) {
        largest = right;
    }

    if (largest != index) {
        swap_items(&(maxheap->array[largest]), &(maxheap->array[index]));
        heapify(maxheap, largest);
    }
}

Heap* create_maxheap (int *arr, int size)
{
    int i;
    Heap *maxheap = (Heap*) malloc (sizeof(Heap));
    if (maxheap == NULL) {
        printf("Malloc failed\n");
        return NULL;
    }
    maxheap->size = size;
    maxheap->array = arr;

    for (i = (maxheap->size - 2)/2; i >= 0; i--) {
        heapify(maxheap, i);
    }

    return maxheap;
}

void heap_sort (int *arr, int size)
{

    Heap *maxheap = create_maxheap(arr, size);
    if (maxheap == NULL) {
        printf("Error in creating heap\n");
        return;
    }

    /* Sort the array */
    while (maxheap->size > 1) {
        swap_items(&(maxheap->array[0]), &(maxheap->array[maxheap->size -1]));
        maxheap->size--;
        heapify(maxheap, 0);
    }

    /*restore the heap size*/
    maxheap->size = size;

    //delete_item_from_heap(maxheap, 20);
}

void delete_item_from_heap (Heap *maxheap, int item) 
{
     int item_index = search_element_in_array(maxheap->array, maxheap->size, item);
     if (item_index == -1) {
         printf("Item %d not found in heap\n", item);
         return;
     }

     swap_items(&(maxheap->array[item_index]), &(maxheap->array[maxheap->size - 1]));

     heapify(maxheap, item_index);

     printf("Item %d deleted. Heap after delete\n", item);
     show_array(maxheap->array, maxheap->size -1);
}
