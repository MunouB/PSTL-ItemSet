#include "main.h"

void free_hash_table(hash_table * table){
	for(int i = 0 ; i < TABLE_SIZE ; i++){
		hash_node * current = table->pointers[i];
		while(current != NULL){
			hash_node * tmp = current;
			current = current -> next;
			free(tmp->item_set->items);
			free(tmp->item_set);
			free(tmp);
		}
	}
	free(table->pointers);
	free(table);
}