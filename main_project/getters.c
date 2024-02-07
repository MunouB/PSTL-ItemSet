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