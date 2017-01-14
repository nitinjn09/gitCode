#include "../include/hash.h"

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

