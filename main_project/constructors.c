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

candidates *construct_c1_tid(char *f, int item_id_column, int basket_id_column, int *size) {
    int *t = get_items_from_file(f, item_id_column, size);
    candidates *database = (candidates*)malloc((*size) * sizeof(candidates));
    
    FILE *file = fopen(f, "r");
    if (file == NULL) {
        perror("Error");
        return NULL;
    }

    char line[50];
    const char *seperator = ",";
    
    fgets(line, sizeof(line), file);

    int currentIndex = 0;

    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, seperator);
        int basket_number = -1;

        while (token != NULL) {
            if (basket_id_column > 0) {
                if (basket_id_column == 1) {
                    basket_number = atoi(token);
                } 
            }

            if (item_id_column > 0) {
                if (item_id_column == 1) {
                    int item_id = atoi(token);
                    database[currentIndex].t_id = basket_number;
                    database[currentIndex].itemsets = (item_set*)malloc(sizeof(item_set));
                    initialize_item_set(database[currentIndex].itemsets);
                    add_item_to_item_set(item_id, database[currentIndex].itemsets);
                    currentIndex++;
                }
            }

            token = strtok(NULL, seperator);
        }
    }

    fclose(file);
    return database;
}

hash_table * construct_l1(char * f,int support,int id_column,int * size){
	int * t = get_items_from_file(f,id_column,size);
	hash_table * table = construct_c1(t,*size);
	int * items_frequencies = (int*)calloc(*size,sizeof(int));
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
	for(int i = 0 ; i < *size ; i++){
		if(items_frequencies[i]>=support){
			item_set * item_set = init_item_set();
			add_item_to_item_set(t[i],item_set);
			add_item_set_to_hash_table(item_set,l1);
		}
	}
	return l1;
}

hash_table * construct_ck(hash_table * lk_1){
	int possible_item_size = 0;
	int * possible_items = get_items_from_hash_table(lk_1,&possible_item_size);
	hash_table * ck = init_hash_table();
	for(int i = 0 ; i < TABLE_SIZE ; i++){
		hash_node * current = lk_1->pointers[i];
		while(current != NULL){
			for(int j = 0 ; j < possible_item_size ; j++){
				item_set * possible_candidate = cpy_item_set(current->item_set);
				add_item_to_item_set(possible_items[j],possible_candidate);
				if(possible_candidate->k != current->item_set->k){
					if(all_sub_item_sets_in_hash_table(possible_candidate,lk_1)){
						add_item_set_to_hash_table(possible_candidate,ck);
					}
				}
			}
			current = current->next;
		}
	}
	return ck;
}



hash_table * apriori_algorithm(char * f,int support,int item_id_column,int basket_id_column,int *size){
	hash_table * res = construct_l1(f,support,item_id_column,size);
	*size = 0;
	hash_table * lk_1 = construct_l1(f,support,item_id_column,size);
	bool end = true;
	while(end){
		end = false;
		hash_table * ck = construct_ck(lk_1);
		free_hash_table(lk_1);
		lk_1 = init_hash_table();
		*size = 0;
		int * t = get_items_from_file(f,item_id_column,size);
		hash_table * indexes = construct_c1(t,*size);
		FILE * file = fopen(f, "r");
		if(file == NULL){
			perror("Error");
			// return EXIT_FAILURE;
		}
		char line[50];
		const char * seperator = ",";
		// Ignore the first line
		fgets(line, sizeof(line), file);
		int a = -1;
		int max = (item_id_column > basket_id_column) ? item_id_column : basket_id_column;
		int * bitmap = (int*)calloc(*size,sizeof(int));
		while(fgets(line, sizeof(line), file)){
			// int len = strlen(line);
			// if (len > 0 && line[len - 1] == '\n') {
			// 	line[len - 1] = '\0';
			// }
			char * token = strtok(line,seperator);
			for(int i = 0 ; i < max ; i++){
				if(i == item_id_column - 1){
					int item_id = atoi(token);
					unsigned int index = hash_item_id(item_id);
					item_set * item_set = init_item_set();
					add_item_to_item_set(item_id,item_set);
					hash_node * curr = indexes->pointers[index];
					while(curr != NULL){
						if(two_item_sets_are_similar(item_set,curr->item_set)){
							int initial_index = curr -> index;
							bitmap[initial_index] = 1;
							break;
						}
						curr = curr -> next;
					}
				}
				if(i == basket_id_column - 1){
					int basket_number = atoi(token);
					if(basket_number != a){
						if(a == -1){
							a = atoi(token);
						}
						else{
							for(int j = 0 ; j < TABLE_SIZE ; j++){
								hash_node * current = ck->pointers[j];
								while(current != NULL){
									if(all_items_of_set_in_bitmap(current->item_set,bitmap,indexes)){
										current->item_set->count++;
									}
									current = current->next;
								}
							}
							memset(bitmap,0,(*size)*sizeof(bitmap[0]));
							a = atoi(token);
						}
					}
				}
				token = strtok(NULL,seperator);
			}
		}
		for(int j = 0 ; j < TABLE_SIZE ; j++){
			hash_node * current = ck->pointers[j];
			while(current != NULL){
				if(all_items_of_set_in_bitmap(current->item_set,bitmap,indexes)){
					current->item_set->count++;
				}
				current = current->next;
			}
		}
		memset(bitmap,0,(*size)*sizeof(bitmap[0]));
		fclose(file);
		for(int j = 0 ; j < TABLE_SIZE ; j++){
			hash_node * current = ck->pointers[j];
			while(current != NULL){
				if(current->item_set->count >= support){
					item_set * lk_item_set = cpy_item_set(current->item_set);
					item_set * res_item_set = cpy_item_set(current->item_set);
					add_item_set_to_hash_table(lk_item_set,lk_1);
					add_item_set_to_hash_table(res_item_set,res);
					end = true;
				}
				current = current->next;
			}
		}
	}
	return res;
}

hash_table *initialize_Ek() {
    return init_hash_table();
}

// ----------------- AprioriTid algorithm
hash_table *apriori_tid_algorithm(char *f, int support, int item_id_column, int basket_id_column, int *size) {
    hash_table *res = construct_l1(f, support, item_id_column, size);
    *size = 0;
    hash_table *lk_1 = construct_l1(f, support, item_id_column, size);
    bool end = true;

	while (end) {
    end = false;

    // Construct candidates for the next level (ck)
    hash_table *ck = construct_ck_tid(lk_1, f, item_id_column, basket_id_column, size); // didnt define construct_ck_tid  yet

    
    free_hash_table(lk_1);
    lk_1 = init_hash_table();
    *size = 0;

    

    for (int j = 0; j < TABLE_SIZE; j++) {
        hash_node *current = ck->pointers[j];
        while (current != NULL) {
            if (current->item_set->count >= support) {
                item_set *lk_item_set = cpy_item_set(current->item_set);
                item_set *res_item_set = cpy_item_set(current->item_set);
                add_item_set_to_hash_table(lk_item_set, lk_1);
                add_item_set_to_hash_table(res_item_set, res);
                
                end = true;
            }
            current = current->next;
        }
    }

    
    free_hash_table(ck);
}	

    return res;
}


// hash_table * apriori_algorithm(char * f,int support,int item_id_column,int basket_id_column,int *size){
// 	int n = 4;
// 	while(n > 0){
// 		int possible_items_size = 0;
// 		hash_table * l1 = construct_l1(f,support,item_id_column,size);
// 		*size = 0;
// 		hash_table * lk = construct_l1(f,support,item_id_column,size);
// 		int * possible_items = get_items_from_hash_table(l1,&possible_items_size);
// 		hash_table * ck = init_hash_table();		
// 		for(int i = 0 ; i < TABLE_SIZE ; i++){
// 			hash_node * current = l1->pointers[i];
// 			while(current != NULL){
// 				for(int j = 0 ; j < possible_items_size ; j++){
// 					item_set * possible_candidate = cpy_item_set(current->item_set);
// 					add_item_to_item_set(possible_items[j],possible_candidate);
// 					if(possible_candidate -> k != current->item_set->k){
// 						if(all_sub_item_sets_in_hash_table(possible_candidate,l1)){
// 							add_item_set_to_hash_table(possible_candidate,ck);
// 						}
// 					}
// 				}
// 				current = current->next;
// 			}
// 		}
// 		*size = 0;
// 		int * t = get_items_from_file(f,item_id_column,size);
// 		hash_table * indexes = construct_c1(t,*size);
// 		FILE * file = fopen(f, "r");
// 		if(file == NULL){
// 			perror("Error");
// 			// return EXIT_FAILURE;
// 		}
// 		char line[50];
// 		const char * seperator = ",";
// 		// Ignore the first line
// 		fgets(line, sizeof(line), file);
// 		int a = -1;
// 		int max = (item_id_column > basket_id_column) ? item_id_column : basket_id_column;
// 		int * bitmap = (int*)calloc(*size,sizeof(int));
// 		display_hash_table(ck);
// 		while(fgets(line,sizeof(line),file)){
// 			char * token = strtok(line,seperator);
// 			for(int i = 0 ; i < max ; i++){
// 				if(i == item_id_column - 1){
// 					int item_id = atoi(token);
// 					unsigned int index = hash_item_id(item_id);
// 					item_set * item_set = init_item_set();
// 					add_item_to_item_set(item_id,item_set);
// 					hash_node * curr = indexes->pointers[index];
// 					while(curr != NULL){
// 						if(two_item_sets_are_similar(item_set,curr->item_set)){
// 							int initial_index = curr -> index;
// 							bitmap[initial_index] = 1;
							
// 							printf("\n\n");
// 							break;
// 						}
// 						curr = curr -> next;
// 					}
// 					for (int k = 0; k < *size; ++k)
// 							{
// 								printf("i = %d and %d\n",k,bitmap[k]);
// 							}
// 					free(item_set);
// 				}
// 				if(i == basket_id_column - 1){
// 					int basket_number = atoi(token);
// 					if(basket_number != a && a == -1){
// 						a = atoi(token);
// 					}
// 					else if(basket_number != a){
// 						if(item_id_column <= basket_id_column){

// 						}
// 						else{
// 							for(int j = 0 ; j < TABLE_SIZE ; j++){
// 								hash_node * temp = ck->pointers[j];
// 								while(temp != NULL){
// 									if(all_items_of_set_in_bitmap(temp->item_set,bitmap)){
// 										temp->item_set->count++;
// 									}
// 									temp = temp->next;
// 								}
// 							}
// 						}
// 						free_hash_table(l1);
// 						for(int j = 0 ; j < TABLE_SIZE ; j++){
// 							hash_node * temp = ck->pointers[j];
// 							while(temp != NULL){
// 								if(temp->item_set->count >= support){
// 									add_item_set_to_hash_table(temp->item_set,l1);
// 								}
// 								temp = temp->next;
// 							}
// 						}
// 						lk = add_hash_table_to_hash_table(lk, l1);
// 						//DEBUG
// 						free(bitmap);
// 						free_hash_table(ck);

// 					}
// 				}
// 				token = strtok(NULL,seperator);
// 			}
// 			// if(basket_number != a && *size != 0){
// 			// 	for (int j = 0 ; j < *size ; ++j){
// 			// 		/* code */
// 			// 	}
// 			// }
// 		}
// 		fclose(file);
// 		if(n == 1){
// 			return lk;
// 		}
// 		n--;
// 	}
// }