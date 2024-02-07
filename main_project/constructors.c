#include "main.h"

hash_table * construct_c1(int * t, int size){
	if(t != NULL){
		hash_table * table = init_hash_table();
		for (int i = 0 ; i < size ; i++){
			add_item_to_hash_table(t[i],table,i);
		}
		return table;
	}
	return NULL;
}

hash_table * construct_l1(char * f,int support,int id_column){
	int size = 0;
	int * t = get_items_from_file(f,id_column,&size);
	hash_table * table = construct_c1(t,size);
	int * items_frequencies = (int*)calloc(size,sizeof(int));
	if(items_frequencies == NULL){
		perror("Error");
		return NULL;
	}
	FILE * file = fopen(f, "r");
	if(file == NULL){
		perror("Error");
		// return EXIT_FAILURE;
	}
	char line[50];
	const char * seperator = ",";
	// Ignore the first line
	fgets(line, sizeof(line), file);
	// int a = -1;
	// int max = (item_id_column > basket_id_column) ? item_id_column : basket_id_column;
	while(fgets(line,sizeof(line),file)){
		char * token = strtok(line,seperator);
		// int basket_number = atoi(token);
		for(int i = 0 ; i < id_column ; i++){
			if(i == id_column - 1){
				int item_id = atoi(token);
				int index = hash_item_id(item_id);
				item_set * item_set = init_item_set();
				add_item_to_item_set(item_id,item_set);
				hash_node * current = table->pointers[index];
				while(current != NULL){
					if(two_item_sets_are_similar(item_set,current->item_set)){
						int initial_index = current -> index;
						items_frequencies[initial_index] += 1;
						break;
					}
					current = current -> next;
				}
				free(item_set);
			}
			token = strtok(NULL,seperator);
			// if(i == basket_id_column - 1){
			// 	a = atoi(token);
			// }
		}
		// if(basket_number != a && *size != 0){
		// 	for (int j = 0 ; j < *size ; ++j){
		// 		/* code */
		// 	}
		// }
	}
	fclose(file);
	hash_table * l1 = init_hash_table();
	for(int i = 0 ; i < size ; i++){
		if(items_frequencies[i]>=support){
			item_set * item_set = init_item_set();
			add_item_to_item_set(t[i],item_set);
			add_item_set_to_hash_table(item_set,l1);
		}
	}
	return l1;
}