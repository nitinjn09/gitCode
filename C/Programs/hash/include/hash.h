#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* load_factor = (number of element in hash table)/(size of hash table) */
#define HASH_TABLE_LOAD_FACTOR 3
#define INVALID -1

typedef struct node {
        int data;
        int frequency; // how many times the same element is requested to insert in table.
        struct node *next;
} Node;

typedef struct hashTable {
    int size;
    int count;
    Node *table;
} HashTable;

void show_table (HashTable*);
void insert_item_in_hash_table (HashTable*, int);
HashTable* create_hash_table(int);
int hash_func (HashTable*, int);
int search_hash_table(HashTable* ,int);
