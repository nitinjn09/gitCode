#include "../include/hash.h"

/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
    int data;
    struct node *next;
} Node;
*/
/*
int hash_func (int item)
{
    return (item % 10);
}

void show_table (Node *hash_table, int size_of_table) 
{
    Node *temp;
    printf("Hash table is::\n\n");
    for (int i = 0; i < size_of_table; i++) {
        printf("%d  ",hash_table[i].data);
        temp = &hash_table[i];
        while (temp->next != NULL) {
            temp = temp->next;
            printf("%d  ",temp->data);
        }
        printf("\n");
    }
}

void insert_item_in_hash_table (Node *hash_table, int item)
{
    int key;
    key = hash_func(item);
    Node *temp = &hash_table[key];
    if (temp->data == 0) {
        temp->data = item;
        temp->next = NULL;
    } else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        Node *new_node = (Node*) malloc (sizeof(Node));
        if (new_node == NULL) {
            printf("Error in malloc");
            return;
        }
        
        new_node->next = NULL;
        new_node->data = item;
        temp->next = new_node;
    }
}
*/

int main ()
{
    int list[28] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,35,45,55};
    Node hash_table[10];
    memset(hash_table, 0, sizeof(hash_table));
    int index;
    for (index = 0; index < 28; index++) {
        insert_item_in_hash_table(hash_table, list[index]);
    } 

    show_table(hash_table, 10);
    return 0;
}
