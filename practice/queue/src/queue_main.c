#include "queue.h"

int main ()
{
    int list[] = {10, 5, 14, 4, 3, 7, 6, 9, 11, 12, 16, 15, 17};
    int choice, data, index, size;
    size = sizeof(list)/sizeof(int);
    Queue q;

    while (TRUE) {
        printf("\n\nEnter your choice:\n 1. Create queue\n 2. Enqueue\n 3. Dequeue\n 4. Show queue\n 0. EXIT\n");
        scanf("%d",&choice);

        switch (choice) {
            case 1: 
                create_queue(&q);
                break;
            case 2:
                for (index = 0; index < size; index++) {
                    enqueue(&q, list[index]);
                }
                break;
            case 3:
                data = dequeue(&q);
                if (data != -1) {
                    printf("item %d deleted\n", data);
                }
                break;
            case 4:
                show_queue(&q);
                break;
            case 0:
                return 0;
            default:
                printf("Invalid choice. Enter again\n");
        }
    }

    return 0;
}
