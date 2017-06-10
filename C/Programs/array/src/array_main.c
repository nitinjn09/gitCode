#include <stdio.h>
#include <stdlib.h>
#include "array.h"

int main () 
{
    int arr[] = {54, 29, 21, 400, -37, 100, 20, 6, 70};
       // int arr[] = {1, 1, 1, 1, 1, 5, 1, 1, 1, 1, 1};
       // int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int size = sizeof(arr)/sizeof(arr[0]);
    int choice;

    while(1) {
        printf("Enter your choice:\n 1. SHOW ARRAY\n 2. SEARCH ELEMENT IN ARRAY\n 3. SELECTION SORT\n"
                " 4. BUBBLE SORT\n 5. MERGE SORT\n 6. QUICK SORT\n 7. HEAP SORT\n 0. EXIT\n");
        scanf("%d", &choice);
        switch (choice) {
            case 1: 
                show_array(arr, size);
                break;
            case 2: 
                search_element_in_array(arr, size, 5);
                break;
            case 3: 
                selection_sort(arr, size);
                printf("After selection sort\n");
                show_array(arr, size);
                break;
            case 4:
                bubble_sort(arr, size);
                printf("After bubble sort\n");
                show_array(arr, size);
                break;
            case 5:
                merge_sort(arr, 0, size-1);
                printf("After merge sort\n");
                show_array(arr, size);
                break;
            case 6:
                quick_sort(arr, 0, size-1);
                printf("After quick sort\n");
                show_array(arr, size);
                break;
            case 7:
                heap_sort(arr, size);
                printf("After heap sort\n");
                show_array(arr, size);
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice. Enter again\n");
                break;
        }
    }
}
