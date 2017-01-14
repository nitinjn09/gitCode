#include "tree.h"

void create_queue (Queue *q)
{
    q->size = QUEUE_SIZE;
    q->front = q->rear = -1;
    q->queue = (Node**) malloc (q->size * sizeof(Node*));
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

void enqueue (Queue *q, Node *root)
{
    if (is_queue_full(q)) {
        printf("Queue found full. Enqueue failed\n");
        return;
    }
    q->rear = (q->rear + 1) % q->size;
    q->queue[q->rear] = root;
    if (q->front == -1) {
        q->front = q->rear;
    }
}

Node* dequeue (Queue *q)
{
    if (is_queue_empty(q)) {
        printf("Queue found empty. Dequeue failed\n");
        return NULL;
    }
    Node *temp = q->queue[q->front];
    if (q->front == q->rear) {
        q->front = q->rear = -1;
    } else {
    q->front = (q->front + 1) % q->size;
    }

    return temp;
}

void delete_queue (Queue *q)
{
    free(q->queue);
}

void show_queue (Queue *q)
{
    int f = q->front, r = q->rear;
    printf("Queue is : ");
    while ((f%q->size) <= (r%q->size)) {
        printf("%d, ",(q->queue[f])->key);
        f = (f+1) % q->size;
        if ((f%q->size) == (r%q->size)) {
            break;
        }
    }
}



























