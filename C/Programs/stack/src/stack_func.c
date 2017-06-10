#include "stack.h"

void push (Stack *s, int element)
{
    if (isStackFull(s)) {
        doubleStackCapacity(s);
        printf("Stack full. Doubling capacity to %d\n",s->capacity);
    }

    s->arr[++(s->top)] = element;
}

void pop (Stack *s)
{
    if(isStackEmpty(s)) {
        printf("Stack empty\n");
        return;
    }

    (s->top)--;
}

int isStackFull(Stack *s) 
{
    return (s->top == (s->capacity -1));
}

int isStackEmpty(Stack *s)
{
    return (s->top == -1);
}

void doubleStackCapacity(Stack *s)
{
    s->capacity = 2 * s->capacity;
}

void show_stack (Stack *s)
{
    if (s->top == -1) {
        printf("stack empty\n");
        return;
    }

    for (int index = 0; index <= s->top; index++) {
        printf("%d,  ",s->arr[index]);
    }
}


