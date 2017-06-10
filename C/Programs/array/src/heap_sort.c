#include "array.h"

void heapify (Heap *maxheap, int heap_type, int index)
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
        heapify(maxheap, heap_type, largest);
    }
}

Heap* create_heap (int *arr, int size, int heap_type)
{
    int i;
    Heap *heap = (Heap*) malloc (sizeof(Heap));
    if (heap == NULL) {
        printf("Malloc failed\n");
        return NULL;
    }
    heap->size = size;
    heap->array = arr;

    for (i = (heap->size - 2)/2; i >= 0; i--) {
        heapify(heap, heap_type, i);
    }

    return heap;
}

void heap_sort (int *arr, int size)
{

    Heap *maxheap = create_heap(arr, size, MAX_HEAP);
    if (maxheap == NULL) {
        printf("Error in creating heap\n");
        return;
    }

    /* Sort the array */
    while (maxheap->size > 1) {
        swap_items(&(maxheap->array[0]), &(maxheap->array[maxheap->size -1]));
        maxheap->size--;
        heapify(maxheap, MAX_HEAP, 0);
    }

    /*restore the heap size*/
    maxheap->size = size;

    //delete_item_from_heap(maxheap, 20);
}

void delete_item_from_heap (Heap *maxheap, int heap_type, int item) 
{
    int item_index = search_element_in_array(maxheap->array, maxheap->size, item);
    if (item_index == -1) {
        printf("Item %d not found in heap\n", item);
        return;
    }

    swap_items(&(maxheap->array[item_index]), &(maxheap->array[maxheap->size - 1]));

    heapify(maxheap, heap_type, item_index);

    printf("Item %d deleted. Heap after delete\n", item);
    show_array(maxheap->array, maxheap->size -1);
}

