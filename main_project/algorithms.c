#include "main.h"

// void runner(){
// 	int choice;
// 	do{
// 		printf("\nChoose one of the following methods : \n");
// 		printf("1 - Execute an algorithm and view results of some existing file.\n");
// 		printf("2 - Execute some tests on the execution time of the program.\n");
// 		printf("Your choice : ");
// 		scanf("%d",&choice);
// 		printf("\n");
// 	}while(choice != 1 && choice != 2);
	
// 	if(choice == 1){
// 		int size = 0;
// 		char filename[50];
// 		printf("Enter the file's name : ");
// 		scanf("%49s",filename);
// 		int support;
// 		printf("\nEnter your support : ");
// 		scanf("%d",&support);
// 		int item_id_column;
// 		printf("\nIn your file, which column do the items' ids exist in ? ");
// 		scanf("%d",&item_id_column);
// 		int basket_id_column;
// 		printf("\nIn your file, which column do the transactions' ids exist in ? ");
// 		scanf("%d",&basket_id_column);
// 		int algochoice;
// 		do{
// 			printf("\nChoose one of the following methods : \n");
// 			printf("1 - Read the file every time a new Lk is constructed.\n");
// 			printf("2 - Store the data of the baskets then read the stored data.\n");
// 			printf("Your choice : ");
// 			scanf("%d",&algochoice);
// 			printf("\n");
// 		}while(algochoice != 1 && algochoice != 2);
// 		hash_table * t = apriori(filename,support,item_id_column,basket_id_column,&size,algochoice);
// 		display_hash_table(t);
// 		free_hash_table(t);
// 	}
// 	else if(choice == 2){
// 		int testchoice;
// 		do{
// 			printf("\nChoose one of the following tests : \n");
// 			printf("1 - Test the execution time.\n");
// 			printf("Your choice : ");
// 			scanf("%d",&testchoice);
// 			printf("\n");
// 		}
// 		while(testchoice != 1);

// 		if(testchoice == 1){
// 			int varchoice;
// 			do{
// 				printf("\nChoose one of the following variations : \n");
// 				printf("\nTest the execution time depending on the variation of : \n");
// 				printf("1 - The probability of the existance of an element in a transaction.\n");
// 				printf("2 - The total number of transactions.\n");
// 				printf("3 - The total number of items.\n");
// 				printf("4 - The support.\n");
// 				printf("Your choice : ");
// 				scanf("%d",&varchoice);
// 				printf("\n");
// 			}while(varchoice != 1 && varchoice != 2 && varchoice != 3 && varchoice != 4);
// 			run_experiment(varchoice);
// 		}
// 	}
// }

void run_algorithm(char *filename, int support, int algochoice) {
	    printf("Running algorithm with on file: %s, with support of : %d ...\n",
           filename, support);
    int size = 0;
     hash_table * t = apriori(filename, support, 2, 1, &size, algochoice);
     display_hash_table(t);
     free_hash_table(t);

}

void run_algorithm_tid(char *filename, int support) {
	printf("Running algorithm with on file: %s, with support of : %d ...\n",
		   filename, support);
	int size = 0;
	hash_table *t = apriori_tid_algorithm(filename, support, 2, 1, &size);
	display_hash_table(t);
	free_hash_table(t);
}

void run_tests(int varchoice) {
   	 printf("Running tests... \n");
     run_experiment(varchoice);
    
}

void runner(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s choice [args...]\n", argv[0]);
        printf("  choice: 1 - Execute an algorithm\n");
        printf("          2 - Execute tests on execution time\n");
        return;
    }

    int choice = atoi(argv[1]);

    if (choice != 1 && choice != 2 && choice != 3) {
        printf("Invalid choice.\n");
        return;
    }

    if (choice == 1) {
        // if (argc != 7) {
        //     printf("choice: %s 1 filename support algochoice\n", argv[0]);
        //     return;
        // }
        char *filename = argv[2];
        int support = atoi(argv[3]);
        int algochoice = atoi(argv[4]);
        run_algorithm(filename, support, algochoice);
    } 

	if (choice == 2) {
	
		char *filename = argv[2];
		int support = atoi(argv[3]);
		run_algorithm_tid(filename, support);
	}
	
	else if (choice == 3) {
        if (argc != 3) {
            printf("choice: %s 2 varchoice\n", argv[0]);
            return;
        }
        int varchoice = atoi(argv[2]);
        run_tests(varchoice);
    }
}

hash_table * apriori(char * f,int support,int item_id_column,int basket_id_column,int *size,int algochoice){
	if(algochoice == 1){
		return apriori_algorithm_1(f,support,item_id_column,basket_id_column,size);
	}
	else if(algochoice == 2){
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

// Function prototype, declare this in main.h as well
hash_table *apriori_tid_algorithm(char *f, int support, int item_id_column, int basket_id_column, int *size);

// The Apriori TID algorithm
hash_table *apriori_tid_algorithm(char *f, int support, int item_id_column, int basket_id_column, int *size) {
    // Initialize data structures 
    tid_map *map = init_tid_map(10); // Start with an arbitrary initial capacity
    hash_table *res = construct_l1(f, support, item_id_column, size);
	printf("270\n");
	*size = 0;
    hash_table *lk = construct_l1(f, support, item_id_column, size);
	printf("272\n");
	
    
    bool end = true;
    while(end) {
		*size = 0;
        end = false;
        hash_table *ck = construct_ck(lk);
        
        // Update TID sets for the current ck
		baskets *bs = construct_baskets(f, item_id_column, basket_id_column, size);  
		printf("281\n");
        update_tid_sets(map, ck, bs);
        
        // Generate lk from tidsets
        hash_table *new_lk = generate_lk_from_tid_map(map, support);
        printf("289\n");
		
        // here we should have a new lk ready for the next iterationnn
        // if new_lk is empty, end the loop  otherwise update lk and continue
        if (new_lk->pointers != NULL) {
    bool foundLargeItemset = false;
    for (int i = 0; i < TABLE_SIZE; i++) {
        for (hash_node *current = new_lk->pointers[i]; current != NULL; current = current->next) {
            if (current->item_set->count >= support) {
                foundLargeItemset = true;
                break;
            }
        }
        if (foundLargeItemset) break;
    }
    
    if (!foundLargeItemset) {
        free_hash_table(new_lk);
        break;
    } else {
        free_hash_table(lk);
        lk = new_lk;
        // Keep end as true to continue the loop
    }
} else {
    free_hash_table(new_lk);
    break; // exit loop
}
    }
    
    
    free_tid_map(map);
    return res;
}
