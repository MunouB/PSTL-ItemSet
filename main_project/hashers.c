#include "main.h"

unsigned int hash_item_set(item_set * item_set){ //correct
	unsigned int hash = 0;
	for(int i = 0 ; i < item_set->k ; i++){
		hash = hash + item_set->items[i];
	}
	return hash % TABLE_SIZE;
}

unsigned int hash_item_id(int id){ //correct
	return id % TABLE_SIZE;
}