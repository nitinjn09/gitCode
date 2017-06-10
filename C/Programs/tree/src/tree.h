#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0
#define QUEUE_SIZE 50
#define STACK_MAX_SIZE 50

typedef struct node {
    int key;
    struct node *left;
    struct node *right;
} Node ;

typedef struct queue {
        int size;
        int front;
        int rear;
        Node **queue;
} Queue;

typedef struct stack {
        int top;
        unsigned int capacity;
        Node **arr;
} Stack;

void create_tree (Node**, int*, int);
void show_tree_inorder(Node**);
void show_tree_preorder(Node**);
void show_tree_postorder(Node**);
void level_order_traversal(Node**);
void level_order_traversal_reverse(Node **);
Node* find_min(Node **);
Node* find_max(Node **);
Node* search_node(Node**, int);
Node* delete_node(Node*, int);
void tree_mirror_image(Node**);
Node* build_tree(int*, int*, int, int);
int find_item_index(int*, int, int, int);


void create_queue (Queue *);
void enqueue (Queue *, Node*);
Node* dequeue (Queue *);
int is_queue_empty (Queue *);
int is_queue_full (Queue *);
void show_queue (Queue *);
void delete_queue(Queue*);

void push(Stack*, Node*);
Node* pop(Stack*);
void show_stack(Stack*);
int is_stack_empty(Stack*);
int is_stack_full(Stack*);
void delete_stack(Stack*);
void create_stack(Stack*);







