#include <stdio.h>
#include <stdlib.h>

#define STACK_MAX_SIZE 50

typedef struct stack {
    int top;
    unsigned int capacity;
    int *arr;
} Stack;

void push(Stack*, int);
void pop(Stack*);
void show_stack(Stack*);


