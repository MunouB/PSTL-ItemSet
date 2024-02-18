#include "main.h"

hash_table * add_hash_table_to_hash_table(hash_table * h1, hash_table * h2){
	if(h1 == NULL || h2 == NULL){
		return NULL;
	}
	for(int i = 0 ; i < TABLE_SIZE ; i++){
		hash_node * current = h2->pointers[i];
		while(current != NULL){
			if(!item_set_in_hash_table(current->item_set,h1)){
				item_set * copy = cpy_item_set(current->item_set);
				add_item_set_to_hash_table(copy,h1);
			}
			current = current->next;
		}
	}
	return h1;
}

// hash_table * construct_l1(char* f, int support,int id_column){
// 	int * table = get_items_from_file(f,id_column);
// 	hash_table * t = init_hash_table();
// 	// FILE * file = fopen(f, "r");
// 	// if(file == NULL){
// 	// 	perror("Error");
// 	// 	// return EXIT_FAILURE;
// 	// }
// 	char line[50];
// 	const char * seperator = ",";
// 	// Ignore the first line
// 	// fgets(line, sizeof(line), file);
// 	int i = 0;
// 	int count = 0;
// 	// while(table[i] != '\0'){
// 	// 	printf("%d , %d\n",i,table[i]);
// 	// 	i++;
// 	// }
// 	// i = 0;
// 	while(table[i] != '\0'){
// 		count = 0;
// 		FILE * files = fopen(f, "r");
// 		if(files == NULL){
// 			perror("Error");
// 		}
// 		// Ignore the first line
// 		fgets(line, sizeof(line), files);
// 		while(fgets(line, sizeof(line),files)){
// 			char * token = strtok(line, seperator);
// 			for(int j = 0 ; j < id_column ; j++){
// 				if(j == id_column - 1){
// 					int item_id = atoi(token);
// 					if(table[i] == item_id){
// 						count++;
// 						if(count >= support){
// 							add_item_to_hash_table(item_id,t);
// 						}
// 					}
// 				}
// 				token = strtok(NULL,seperator);
// 			}
// 			if(count >= support /*&& fgets(line,sizeof(line), file) != NULL*/){
// 				// fseek(file,0,SEEK_SET);
// 				// fgets(line, sizeof(line), file);
// 				// printf("First line: %s and i = %d\n", line,i);
// 				break;
// 			}
// 		}
// 		i++;
// 		fclose(files);
// 	}
// 	// fclose(file);
// 	return t;
// }
