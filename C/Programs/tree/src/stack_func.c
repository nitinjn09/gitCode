#include "tree.h"

void create_stack (Stack *s)
{
    s->capacity = STACK_MAX_SIZE;
    s->top = -1;
    s->arr = (Node**) malloc (s->capacity * sizeof(Node*));
}

int is_stack_empty (Stack *s)
{
    return (s->top == -1);
}

int is_stack_full (Stack *s)
{
    return (s->top == s->capacity);
}

void push (Stack *s, Node *root)
{
    if (is_stack_full(s)) {
        printf("stack full\n");
        return;
    }

    s->arr[++(s->top)] = root;
}

Node* pop (Stack *s)
{
    if(is_stack_empty(s)) {
        printf("stack empty\n");
        return NULL;
    }

    return (s->arr[(s->top)--]);
}

void show_stack (Stack *s)
{
    if (s->top == -1) {
        printf("stack empty\n");
        return;
    }

    for (int index = 0; index <= s->top; index++) {
        printf("%d,  ",(s->arr[index])->key);
    }
}

void delete_stack(Stack *s)
{
    free(s->arr);
}
