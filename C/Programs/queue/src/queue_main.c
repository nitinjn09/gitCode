#include "queue.h"

int main() 
{
    int ch, data ;
    Queue *q = createQueue();

    while(TRUE) {
        printf("\nEnter your choice: 1. Enqueue 2. Dequeue 3. ShowQueue 4. GetSize 0. Exit. your choice? : ");
        scanf("%d",&ch);
        switch(ch) {
            case 1:
                printf("\nEnter element : ");
                scanf("%d",&data);
                Enqueue(q, data);
                ShowQueue(q);
                break;

            case 2: 
                data = Dequeue(q);
                printf("Data dequeued is: %d\n",data);
                ShowQueue(q);
                break;

            case 3: ShowQueue(q);
                    break;

            case 4: printf("Size of queue is : %d\n",getQueueSize(q));
                    break;

            case 0: 
                    return 0;
            default:
                    printf("You have entered invalid choice\n");
                    break;
        }
    }
    return 0;
}
