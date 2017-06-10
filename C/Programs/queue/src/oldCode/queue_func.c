#include "queue.h"

void create_queue (Queue *q)
{
    q->size = QUEUE_SIZE;
    q->front = q->rear = -1;
    q->queue = (int*) malloc (q->size * sizeof(int));
    if(!q->queue) {
        printf("\nMalloc failed in create_queue");
    }
}

int is_queue_empty (Queue *q)
{
    return(q->front == -1);
}

int is_queue_full (Queue *q)
{
    return ((q->rear + 1) % q->size == q->front);
}

void enqueue (Queue *q, int item)
{
    if (is_queue_full(q)) {
        printf("Queue found full. Enqueue failed\n");
        return;
    }
    q->rear = (q->rear + 1) % q->size;
    q->queue[q->rear] = item;
    if (q->front == -1) {
        q->front = q->rear;
    }
}

int dequeue (Queue *q)
{
    if (is_queue_empty(q)) {
        printf("Queue found empty. Dequeue failed\n");
        return 1;
    }
    int item = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
    q->front = (q->front + 1) % q->size;
    }

    return item;
}

void show_queue (Queue *q)
{
    int f = q->front, r = q->rear;
    printf("Queue is : ");
    while ((f%q->size) <= (r%q->size)) {
        printf("%d, ",q->queue[f]);
        f = (f+1) % q->size;
        if ((f%q->size) == (r%q->size)) {
            break;
        }
    }
}



























