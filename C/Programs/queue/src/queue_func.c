#include "queue.h"

Queue* createQueue() {
    Queue *q = (Queue*) malloc(sizeof(Queue));
    if(!q) {
        printf("Error is creating queue. Exiting..\n");
        exit(EXIT_FAILURE);
    }
    q->array = (int*) malloc(QUEUE_SIZE * sizeof(int));
    if(!q->array) {
        printf("Error in creating queue array. Exiting..\n");
        exit(EXIT_FAILURE);
    }
    q->capacity = QUEUE_SIZE;
    q->front = q->rear = -1;
    return q;
}

void Enqueue(Queue *q, int data) {
    if(isFull(q)) {
        printf("Queue is full\n");
    } else {
        q->rear = (q->rear + 1) % q->capacity;
        q->array[q->rear] = data;
        if(q->front == -1) {
            q->front = q->rear;
        }
    }
}

int Dequeue(Queue *q) {
    int data;
    if(isEmpty(q)) {
        printf("queue is empty\n");
        return -1;
    } else {
        data = q->array[q->front];
        if(q->front == q->rear) {
            q->front = q->rear = -1;
        } else {
            q->front = (q->front + 1) % q->capacity;
        }
    }
    return data;
}

void ShowQueue(Queue *q) {
    int index = q->front;
    printf("Queue: ");
    while(!isEmpty(q) && (index != q->rear+1)) {
        printf("%d ",q->array[index]);
        index = (index+1)%q->capacity;
    }
    printf("\n");
    return;
}

int isEmpty(Queue *q) {
    return (q->front == -1);
}

int isFull(Queue *q) {
    return (((q->rear + 1) % q->capacity) == q->front);
}

int getQueueSize(Queue *q) {
    return (q->capacity + q->rear - q->front +1)%q->capacity;
}
