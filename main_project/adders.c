#include "main.h"

void add_item_to_item_set(int item_id,item_set * item_set){ //correct
	if(!(item_in_item_set(item_id,item_set))){
		item_set-> items = realloc(item_set-> items , sizeof(int) * (item_set->k + 1));
		item_set->items[item_set->k] = item_id;
		item_set->k += 1;
	}
}

void add_item_set_to_hash_table(item_set * item_set, hash_table * table){
	if(item_set == NULL || table == NULL || item_set->k == 0){
		return;
	}
	if(!item_set_in_hash_table(item_set,table)){
		unsigned int index = hash_item_set(item_set);
		hash_node * new_node = init_node();
		if(new_node == NULL){
			return;
		}
		new_node->item_set = item_set;
		if(table->pointers[index] == NULL){
			table -> pointers[index] = new_node;
		}
		else{
			new_node->next = table->pointers[index];
			table->pointers[index] = new_node;
		}
	}
}

void add_item_to_hash_table(int item_id,hash_table * table,int initial_index){ //correct
	if(!item_in_hash_table(item_id,table)){
		unsigned int index = hash_item_id(item_id);
		hash_node * new_node = init_node();
		if(new_node == NULL){
			return;
		}
		add_item_to_item_set(item_id,new_node->item_set);
		new_node->index = initial_index;
		if(table->pointers[index] == NULL){
			table -> pointers[index] = new_node;
		}
		else{
			new_node->next = table->pointers[index];
			table->pointers[index] = new_node;
		}
	}
}

int * add_id_to_integer_table(int id,int * table, int* size){ //correct
	if(!(item_in_integer_table(id,table,*size))){
		table = realloc(table,sizeof(int) * (*size + 1));
		if(table != NULL) {
			table[*size] = id;
			(*size)++;
		}
	}
	return table;
}

void add_bit_map_to_baskets(int * bitmap, baskets * bs, int size){
	bs->basket = realloc(bs->basket,sizeof(int*) * (bs->count + 1));
	if(bs->basket == NULL){
		perror("Error");
		exit(EXIT_FAILURE);
	}
	bs->basket[bs->count] = malloc(size * sizeof(int));
	if (bs->basket[bs->count] == NULL) {
		perror("Error");
		exit(EXIT_FAILURE);
	}
	for (int i = 0; i < size; i++) {
		bs->basket[bs->count][i] = bitmap[i];
	}
	bs->count++;
}
