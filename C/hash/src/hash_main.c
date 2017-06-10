#include "../include/hash.h"


int main ()
{
    int list[28] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,35,45,55};
    int input_size = sizeof(list)/sizeof(int);
    printf("Input size : %d\n",input_size);
    HashTable *hash = create_hash_table(input_size);
    if(!hash) {
        printf("%s : Hash table creation failed..Exiting!\n",__FUNCTION__);
        exit(EXIT_FAILURE);
    }
    Node hash_table[10];
    memset(hash_table, 0, sizeof(hash_table));
    int index;
    for (index = 0; index < 28; index++) {
        //insert_item_in_hash_table(hash, hash_table, list[index]);
        insert_item_in_hash_table(hash, list[index]);
    } 

    show_table(hash);
    search_hash_table(hash, 18);
    search_hash_table(hash, 35);
    search_hash_table(hash, 50);
    return 0;
}
