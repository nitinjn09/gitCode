#include "../include/hash.h"

HashTable* create_hash_table (int input_size)
{
    HashTable *hash = (HashTable*) malloc (sizeof(HashTable));
    if(!hash) {
        printf("%s : Malloc error\n",__FUNCTION__);
        return NULL;
    }
    
    hash->count = 0;
    hash->size = input_size/HASH_TABLE_LOAD_FACTOR;
    hash->table = (Node*) malloc (hash->size * sizeof(Node));

    if(!hash->table) {
        printf("%s : Malloc error\n",__FUNCTION__);
        free(hash);
        return NULL;
    }
    for (int i =0; i < hash->size; i++) {
        hash->table[i].data = INVALID;
        hash->table[i].next = NULL;
        hash->table[i].frequency = 0;
    }
    return hash;
}

int hash_func (HashTable *hash, int item)
{
        return (item % hash->size);
}

void show_table (HashTable *hash)
{
    Node *temp;
    printf("Hash table is::\n\n");
    for (int i = 0; i < hash->size; i++) {
        temp = &hash->table[i];
        if(temp->data != INVALID) {
            printf("%d : %d ", i, temp->data);
            while (temp->next != NULL) {
                temp = temp->next;
                printf("%d ",temp->data);
            }
            printf("\n");
        }
    }
}

void insert_item_in_hash_table (HashTable *hash, int item)
{
    int key;
    key = hash_func(hash, item);
    Node *temp = &hash->table[key];
    if (temp->data == INVALID) { // hash table dont have any element at this key.
        temp->data = item;
        temp->frequency++;
        temp->next = NULL;
    } else { //Collision detected
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
    hash->count++;
}

int search_hash_table (HashTable *hash, int item)
{
    int key = hash_func(hash, item);
    if(hash->table[key].data != INVALID) {
        Node *temp = &hash->table[key];
        if (temp->data == item) {
            printf("Element fount at table index/key : %d\n",key);
            return key;
        } else {
            while(temp->next != NULL) {
                temp = temp->next;
                if (temp->data == item) {
                    printf("Element fount at table index/key : %d\n",key);
                    return key;
                }
            }
        }
    }
    printf("Element %d NOT Found\n",item);
    return -1;
}
