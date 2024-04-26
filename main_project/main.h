#ifndef FINAL_RESULT_H_INCLUDED
#define FINAL_RESULT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

// To store the baskets instead of reading the file multiple times, we need a 2D integer array structure
typedef struct {
	int **basket;
	int count; //Number of baskets
}baskets;

//
typedef struct {
    int tid;
    item_set *itemset;
} tid_entry;

typedef struct {
    tid_entry *entries;
    int count;
    int capacity;
} tid_map;
//

item_set* init_item_set();
hash_node * init_node();
hash_table* init_hash_table();
baskets * init_baskets();



//
tid_map *init_tid_map(int initial_capacity);
void add_to_tid_map(tid_map *map, int tid, item_set *set);
void free_tid_map(tid_map *map);
bool all_items_of_tid_in_itemset(tid_map *map, int tid, item_set *set);
void update_tid_sets(tid_map *map, hash_table *lk, baskets *bs);
hash_table *generate_lk_from_tid_map(tid_map *map, int support);
hash_table *apriori_tid_algorithm(char *f, int support, int item_id_column, int basket_id_column, int *size);
//

unsigned int hash_item_set(item_set*);
unsigned int hash_item_id(int);

bool item_in_item_set(int,item_set*);
bool item_in_integer_table(int,int*,int);
bool two_item_sets_are_similar(item_set*,item_set*);
bool item_set_in_hash_table(item_set*, hash_table*);
bool item_in_hash_table(int,hash_table*);
bool all_sub_item_sets_in_hash_table(item_set*,hash_table*);
bool all_items_of_set_in_bitmap(item_set*,int*,hash_table*);

void display_itemset(item_set*);
void display_hash_table(hash_table*);
void display_baskets(baskets*,int);

void add_item_to_item_set(int,item_set*);
void add_item_set_to_hash_table(item_set*, hash_table*);
void add_item_to_hash_table(int,hash_table*,int);
int * add_id_to_integer_table(int,int*,int*);
hash_table * add_hash_table_to_hash_table(hash_table*, hash_table*);
void add_bit_map_to_baskets(int*, baskets*, int);

void free_hash_table(hash_table*);

int * get_items_from_file(char* f,int,int*);
int * get_items_from_hash_table(hash_table*, int*);
item_set * get_sub_item_set_without_element(item_set*, int);
item_set * cpy_item_set(item_set*);
double get_execution_time(char*,int,int,int,int*);

hash_table * construct_c1(int*, int);
hash_table * construct_l1(char*,int,int,int*);
hash_table * construct_ck(hash_table*);
baskets * construct_baskets(char*,int,int, int*);

hash_table * apriori(char*,int,int,int,int*,int);
hash_table * apriori_algorithm_1(char*,int,int,int,int*);
hash_table * apriori_algorithm_2(char*,int,int,int,int*);
void runner();

double random_ratio();
int generate_0_or_1(double);
baskets * generate_baskets_randomly(int,int,double);
void generate_csv(int,int,double);


void run_experiment(int);
void run_experiment_probability();
void run_experiment_transaction();
void run_experiment_items();
void run_experiment_support();


#endif
