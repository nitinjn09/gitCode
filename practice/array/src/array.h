

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

typedef struct heap {
    int size;
    int *array;
} Heap;

void heap_sort(int*, int);
Heap* create_maxheap(int*, int);
void heapify(Heap*, int);

void delete_item_from_heap (Heap*, int);



