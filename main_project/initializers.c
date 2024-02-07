#include "main.h"

item_set* init_item_set(){ //correct
	item_set * new_item_set = (item_set*)malloc(sizeof(item_set));
	if(new_item_set != NULL){
		new_item_set -> k = 0;
		new_item_set -> count = 0;
		new_item_set -> items = NULL;
	}
	return new_item_set;
}

hash_node * init_node(){
	hash_node * new_node = (hash_node*)malloc(sizeof(hash_node));
	if(new_node != NULL){
		new_node -> item_set = init_item_set();
		new_node -> index = -1; //TO CHECK
		new_node -> next = NULL;
	}
	return new_node;
}

hash_table* init_hash_table(){ //correct
	hash_table* table = (hash_table*)malloc(sizeof(hash_table));
	if(table != NULL){
		table->pointers = (hash_node**)malloc(sizeof(hash_node*) * TABLE_SIZE);
		if(table->pointers != NULL){
			for (int i = 0; i < TABLE_SIZE; i++) {
				table->pointers[i] = NULL;
			}
		}
		else{
			free(table);
			return NULL;
		}
	}
	return table;
}