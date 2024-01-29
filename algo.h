#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>


struct item{
	int item_id;
};
typedef struct item item;

struct item_set {
	int k;
	item * items;
};
typedef struct item_set item_set;

struct basket { 
    int basket_id;
    int size;
    item * items;
};
typedef struct basket basket;


typedef struct baskets {
	basket * bsk_list;
	int size;
}baskets;

typedef struct large_item_set{
	int support;
	item_set items;
	struct large_item_set * next;
}large_item_set;


/*struct Candidate {
	int support;
	item_set items;
	Candidate * next;
}*/


item_set* init_set();
basket* init_basket(int);	
baskets* init_baskets();
large_item_set * init_large_item_set(int);

bool in_set(item,item_set*);
bool in_basket(item,basket*);

void add_itemset(item,item_set*);
void add_basket(item,basket*);
void add_baskets(basket *,baskets *);
baskets * generate_baskets(char *);
large_item_set* add_large_item_set(item_set,large_item_set *);

void display_itemset(item_set*);
void display_basket(basket);
void display_baskets(baskets*);
void display_large_item_set(large_item_set*);

item_set* get_items_from_large_item_set(large_item_set*);
large_item_set* construct_l1(char*,int);
large_item_set* apriori_generator(large_item_set *);
large_item_set* apriori_algorithm(char*,int);
