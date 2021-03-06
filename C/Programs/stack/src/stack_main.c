#include "stack.h"


int main ()
{
    int list[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    Stack s;
    int choice, element;
    
    s.capacity = STACK_MAX_SIZE;
    s.top = -1;
    s.arr = (int*) malloc (s.capacity * sizeof(int));

    while (1) {
        printf("\n\nEnter your choice: 1. push 2. pop 3. Show stack 0. EXIT! Your chaoice? : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter element: ");
                scanf("%d",&element);
                push(&s, element);
                show_stack(&s);
                break;
            case 2:
                pop(&s);
                show_stack(&s);
                break;
            case 3:
                show_stack(&s);
                break;
            case 0: return 0;
            default :
                printf("Invalid choice. enter again\n");
                break;
        }
    }
    return 0;
}
