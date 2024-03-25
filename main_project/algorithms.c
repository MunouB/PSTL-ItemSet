#include "main.h"

void runner(){
	int size = 0;
	char filename[50];
	printf("Enter the file's name : ");
	scanf("%49s",filename);
	int support;
	printf("\nEnter your support : ");
	scanf("%d",&support);
	int item_id_column;
	printf("\nEnter the number of the column that contains the ids of the items : ");
	scanf("%d",&item_id_column);
	int basket_id_column;
	printf("\nEnter the number of the column that contains the ids of the baskets : ");
	scanf("%d",&basket_id_column);
	int choice;
	do{
		printf("\nChoose one of the following methods : \n");
		printf("1 - Read the file every time a new Lk is constructed.\n");
		printf("2 - Store the data of the baskets then read the stored data.\n");
		printf("Your choice : ");
		scanf("%d",&choice);
		printf("\n");
	}while(choice != 1 && choice != 2);
	hash_table * t = apriori(filename,support,item_id_column,basket_id_column,&size,choice);
}

hash_table * apriori(char * f,int support,int item_id_column,int basket_id_column,int *size,int choice){
	if(choice == 1){
		return apriori_algorithm_1(f,support,item_id_column,basket_id_column,size);
	}
	else if(choice == 2){
		return apriori_algorithm_2(f,support,item_id_column,basket_id_column,size);
	}
	return NULL;
}

hash_table * apriori_algorithm_1(char * f,int support,int item_id_column,int basket_id_column,int *size){
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

hash_table * apriori_algorithm_2(char * f,int support,int item_id_column,int basket_id_column,int *size){
	int * t = get_items_from_file(f,item_id_column,size);
	hash_table * indexes = construct_c1(t,*size);
	hash_table * ck = construct_c1(t,*size);
	hash_table * lk = init_hash_table();
	hash_table * res = init_hash_table();
	*size = 0;
	baskets * bs = construct_baskets(f,item_id_column,basket_id_column,size);
	bool end = true;
	while(end){
		end = false;
		for(int i = 0 ; i < TABLE_SIZE ; i++){
			hash_node * current = ck->pointers[i];
			while(current != NULL){
				for(int j = 0 ; j < bs->count ; j++){
					if(all_items_of_set_in_bitmap(current->item_set,bs->basket[j],indexes)){
						current->item_set->count++;
						if(current->item_set->count >= support){
							item_set * lk_item_set = cpy_item_set(current->item_set);
							item_set * res_item_set = cpy_item_set(current->item_set);
							add_item_set_to_hash_table(lk_item_set,lk);
							add_item_set_to_hash_table(res_item_set,res);
							end = true;
							break;
						}
					}
				}
				current = current->next;
			}
		}
		ck = construct_ck(lk);
		free_hash_table(lk);
		lk = init_hash_table();
	}
	return res;
}
