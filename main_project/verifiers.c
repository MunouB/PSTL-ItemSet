#include "main.h"

bool item_in_item_set(int item_id,item_set* item_set){ //correct
	for(int i = 0 ; i < item_set->k ; i++){
		if(item_set->items[i] == item_id){
			return true;
		}
	}
	return false;
}

bool item_in_integer_table(int id,int* table,int size){ //correct
	for(int i = 0 ; i < size ; i++){
		if(table[i] == id){
			return true;
		}
	}
	return false;
}

bool two_item_sets_are_similar(item_set * s1,item_set * s2){ //correct
	if(s1->k != s2->k) return false;
	for (int i = 0 ; i < s1->k ; i++){
		if(!item_in_item_set(s1->items[i],s2)) return false;
	}
	return true;
}

bool item_set_in_hash_table(item_set * item_set, hash_table * table){ //correct
	unsigned int index = hash_item_set(item_set);
	hash_node * current = table->pointers[index];
	while(current != NULL){
		if(two_item_sets_are_similar(item_set,current->item_set)){
			return true;
		}
		current = current->next;
	}
	return false;
}

bool item_in_hash_table(int item_id,hash_table * table){ //correct
	item_set * item_set = init_item_set();
	add_item_to_item_set(item_id,item_set);
	return item_set_in_hash_table(item_set,table);
}

bool all_sub_item_sets_in_hash_table(item_set* set,hash_table* table){
	for(int i = 0 ; i < set->k ; i++){
		item_set * sub_set = get_sub_item_set_without_element(set,set->items[i]);
		if(!(item_set_in_hash_table(sub_set,table))){
			return false;
		}
		free(sub_set);
	}
	return true;
}