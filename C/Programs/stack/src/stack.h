#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 2

typedef struct stack {
    int top;
    unsigned int capacity;
    int *arr;
} Stack;

void push(Stack*, int);
void pop(Stack*);
void show_stack(Stack*);
int isStackFull(Stack*);
int isStackEmpty(Stack*);
void doubleStackCapacity(Stack*);

