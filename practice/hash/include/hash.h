#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node {
        int data;
            struct node *next;
} Node;

void show_table (Node*, int);
void insert_item_in_hash_table (Node*, int);
int hash_func (int);
