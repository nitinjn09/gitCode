#include <stdio.h>

typedef struct node {
    int size;
    struct node *head[10];
} Node;

int *m;
char *n;
int main ()
{
    int *p;
    char *q;
    void *v;
    Node temp;
    printf("sizeof Node : %lu\n",sizeof(temp));
    printf("sizeof node *head : %lu\n",sizeof(Node*));
    printf("sizeof int : %lu\n",sizeof(int));
    printf("sizeof global int* : %lu\n",sizeof(m));
    printf("sizeof global char* : %lu\n",sizeof(n));
    printf("sizeof local int* : %lu\n",sizeof(p));
    printf("sizeof local int* : %lu\n",sizeof(q));
    printf("sizeof local void* : %lu\n",sizeof(v));
    return 0;
}
