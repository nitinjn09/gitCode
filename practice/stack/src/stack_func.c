#include "stack.h"

void push (Stack *s, int element)
{
    if (s->top == s->capacity) {
        printf("stack full\n");
        return;
    }

    s->arr[++(s->top)] = element;
}

void pop (Stack *s)
{
    if(s->top == -1) {
        printf("stack empty\n");
        return;
    }

    (s->top)--;
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

