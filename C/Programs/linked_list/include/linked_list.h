#include <stdio.h>
#include <stdlib.h>

typedef struct node {
        int data;
            struct node *next;
} Node;

typedef struct dnode {
        int data;
            struct dnode *next;
                struct dnode *prev;
} dNode;

void create_list(Node**, int*, int);
void create_dlist(dNode**, int*, int);
void insert_item_in_list_at_last_pos(Node**, int);
void delete_item_from_list(Node**);
void show_list(Node**);
void show_dlist(dNode**);
void swap_nodes(Node**, int, int);
void swap_nodes_without_data_swap(Node**, int, int);
void reverse_list(Node**);
int list_size(Node**);
int detect_loop_in_list(Node**);
Node* merge_two_sorted_list(Node **, Node **);
Node* list_intersection_1 (Node*, Node*);
Node* list_intersection (Node**, Node**);
