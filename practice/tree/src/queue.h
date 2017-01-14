#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "tree.h"

#define TRUE 1
#define FALSE 0
#define QUEUE_SIZE 50

typedef struct queue {
    int size;
    int front;
    int rear;
    Node **queue;
} Queue;

void create_queue (Queue *);
void enqueue (Queue *, Node**);
Node* dequeue (Queue *);
int is_queue_empty (Queue *);
int is_queue_full (Queue *);
void show_queue (Queue *);
































