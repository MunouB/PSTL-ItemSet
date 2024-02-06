#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TABLE_SIZE 100
#define MAX_ITEMS 10000

typedef struct item_set {
    int k;
    int *items;
    int count;
}item_set;

// typedef struct baskets {
//     struct hash_table * bsk_list;
//     int size;
// }baskets;

typedef struct hash_node{
    item_set* item_set;
    struct hash_node * next;
}hash_node;

typedef struct hash_table{
    hash_node** pointers;
}hash_table;item_set* init_item_set();

item_set* init_item_set();
// baskets * init_baskets();
hash_node * init_node();
hash_table* init_hash_table();

unsigned int hash_item_set(item_set*);
unsigned int hash_item_id(int);

bool item_in_item_set(int,item_set*);
bool item_in_integer_table(int,int*,int);
bool two_item_sets_are_similar(item_set*,item_set*);
bool item_set_in_hash_table(item_set*, hash_table*);
bool item_in_hash_table(int,hash_table*);

void display_itemset(item_set*);
void display_hash_table(hash_table*);

void add_item_to_item_set(int,item_set*);
void add_item_set_to_hash_table(item_set*, hash_table*);
void add_item_to_hash_table(int,hash_table*);

int * add_id_to_integer_table(int,int*,int*);
int * get_items_from_file(char* f,int);
hash_table * construct_l1(char*,int,int);
hash_table * apriori_algorithm(char*);