#include "main.h"

int * get_items_from_file(char * f,int id_column,int* size){ //correct
	int * table = NULL;
	FILE * file = fopen(f, "r");
	if(file == NULL){
		perror("Error");
		// return EXIT_FAILURE;
	}
	char line[50];
	const char * seperator = ",";
	// Ignore the first line
	fgets(line, sizeof(line), file);
	while(fgets(line, sizeof(line),file)){
		char * token = strtok(line, seperator);
		for(int i = 0 ; i < id_column ; i++){
			if(i == id_column - 1){
				int item_id = atoi(token);
				table = add_id_to_integer_table(item_id, table, size);
			}
			token = strtok(NULL,seperator);
		}
	}
	fclose(file);
	return table;
}



int * get_items_from_hash_table(hash_table * table, int* size){ //correct
	int * t = NULL;
	for(int j = 0 ; j < TABLE_SIZE ; j++){
		hash_node * current = table->pointers[j];
		while(current != NULL){
			for(int i = 0 ; i < current->item_set->k ; i++){
				t = add_id_to_integer_table(current->item_set->items[i],t,size);
			}
			current = current->next;
		}
	}
	return t;
}

item_set * get_sub_item_set_without_element(item_set * set, int element){
	item_set * sub_set = init_item_set();
	for(int i = 0 ; i < set->k ; i++){
		if(set->items[i] != element){
			add_item_to_item_set(set->items[i],sub_set);
		}
	}
	return sub_set;
}

item_set * cpy_item_set(item_set * set){
	item_set * res = init_item_set();
	for(int i = 0 ; i < set->k ; i++){
		add_item_to_item_set(set->items[i],res);
	}
	return res;
}