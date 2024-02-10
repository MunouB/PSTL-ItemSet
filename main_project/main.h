#ifndef FINAL_RESULT_H_INCLUDED
#define FINAL_RESULT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define TABLE_SIZE 100
#define MAX_ITEMS 10000

typedef struct item_set {
    int k;
    int *items;
    int count;
}item_set;

typedef struct hash_node{
    item_set* item_set;
    int index;
    struct hash_node * next;
}hash_node;

typedef struct hash_table{
    hash_node** pointers;
}hash_table;

item_set* init_item_set();
hash_node * init_node();
hash_table* init_hash_table();

unsigned int hash_item_set(item_set*);
unsigned int hash_item_id(int);

bool item_in_item_set(int,item_set*);
bool item_in_integer_table(int,int*,int);
bool two_item_sets_are_similar(item_set*,item_set*);
bool item_set_in_hash_table(item_set*, hash_table*);
bool item_in_hash_table(int,hash_table*);
bool all_sub_item_sets_in_hash_table(item_set*,hash_table*);

void display_itemset(item_set*);
void display_hash_table(hash_table*);

void add_item_to_item_set(int,item_set*);
void add_item_set_to_hash_table(item_set*, hash_table*);
void add_item_to_hash_table(int,hash_table*,int);
int * add_id_to_integer_table(int,int*,int*);

void free_hash_table(hash_table*);

int * get_items_from_file(char* f,int,int*);
int * get_items_from_hash_table(hash_table*, int*);
item_set * get_sub_item_set_without_element(item_set*, int);

hash_table * construct_c1(int*, int);
hash_table * construct_l1(char*,int,int);
// hash_table * apriori_algorithm(char*,int,int);

#endif