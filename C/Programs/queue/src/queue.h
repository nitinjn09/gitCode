#include <stdio.h>
#include <stdlib.h>

#define QUEUE_SIZE 5
#define TRUE 1
#define FALSE 0

typedef struct queue {
    int front, rear, capacity;
    int *array;
}Queue;

Queue* createQueue();
void Enqueue(Queue*,int);
int Dequeue(Queue*);
int isFull(Queue*);
int isEmpty(Queue*);
int getQueueSize(Queue*);
void ShowQueue(Queue*);
