#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void merge(int*, int, int, int);
void merge_sort(int*, int, int);
void swap_items(int*, int*);
void bubble_sort(int*, int);
void selection_sort(int*, int);
int search_element_in_array(int*, int, int);
void show_array(int*, int);
void quick_sort(int*, int, int);
#define TRUE 1
#define FALSE 0

#define MAX_HEAP 1
#define MIN_HEAP 0

typedef struct heap {
    int count; //number of elements present in heap.
    int heap_type; // 0: min heap, 1: max heap
    int size;
    int *array;
} Heap;

void heap_sort(int*, int);
Heap* create_heap(int*, int, int);
void heapify(Heap*, int, int);
void delete_item_from_heap (Heap*, int, int);



