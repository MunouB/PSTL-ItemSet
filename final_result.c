#include "final_result.h"

item_set* init_item_set(){
	item_set * new_item_set = (item_set*)malloc(sizeof(item_set));
	if(new_item_set != NULL){
		new_item_set -> k = 0;
		new_item_set -> count = 0;
		new_item_set -> items = NULL;
	}
	return new_item_set;
}

// baskets * init_baskets(){
// 	baskets * new_baskets = malloc(sizeof(baskets));
// 	new_baskets -> size = 0;
// 	return new_baskets;
// }

hash_node * init_node(){
	hash_node * new_node = (hash_node*)malloc(sizeof(hash_node));
	if(new_node != NULL){
		new_node -> item_set = init_item_set();
		new_node -> next = NULL;
	}
}

hash_table* init_hash_table(){
	hash_table* table = (hash_table*)malloc(sizeof(hash_table));
	if(table != NULL){
		table->pointers = (hash_node**)malloc(sizeof(hash_node*) * TABLE_SIZE);
		if(table->pointers != NULL){
			for (int i = 0; i < TABLE_SIZE; i++) {
				table->pointers[i] = NULL;
			}
		}
		else{
			free(table);
			return NULL;
		}
	}
	return table;
}

unsigned int hash_item_set(item_set * item_set){
	unsigned int hash = 0;
	for(int i = 0 ; i < item_set->k ; i++){
		hash = hash + item_set->items[i];
	}
	return hash % TABLE_SIZE;
}

unsigned int hash_item_id(int id){
	return id % TABLE_SIZE;
}

bool item_in_item_set(int item_id,item_set* item_set){
	for(int i = 0 ; i < item_set->k ; i++){
		if(item_set->items[i] == item_id){
			return true;
		}
	}
	return false;
}

bool item_in_integer_table(int id,int* table,int size){
	for(int i = 0 ; i < size ; i++){
		if(table[i] == id){
			return true;
		}
	}
	return false;
}

bool two_item_sets_are_similar(item_set * s1,item_set * s2){
	if(s1->k != s2->k) return false;
	for (int i = 0 ; i < s1->k ; i++){
		if(!item_in_item_set(s1->items[i],s2)) return false;
	}
	return true;
}

bool item_set_in_hash_table(item_set * item_set, hash_table * table){
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

bool item_in_hash_table(int item_id,hash_table * table){
	unsigned int index = hash_item_id(item_id);
	hash_node * current = table->pointers[index];
	item_set * item_set = init_item_set();
	add_item_to_item_set(item_id,item_set);
	return item_set_in_hash_table(item_set,table);
}

void display_itemset(item_set * s){
	printf("{");
	for(int i = 0 ; i < s->k ; i++){
		if(i == s-> k - 1){
			printf(" %d }\n",s->items[i]);
		}
		else{
			printf(" %d , ",s->items[i]);
		}
	}
}

void display_hash_table(hash_table *table){
    for (int i = 0; i < TABLE_SIZE; i++) {
        printf("Bucket %d: ", i);
        hash_node *current = table->pointers[i];
        if (current == NULL) {
            printf("empty\n");
        }
        while (current != NULL) {
            display_itemset(current->item_set);
            current = current->next;
        }
    }
}


void add_item_to_item_set(int item_id,item_set * item_set){
	if(!(item_in_item_set(item_id,item_set))){
		item_set-> items = realloc(item_set-> items , sizeof(int) * (item_set->k + 1));
		item_set->items[item_set->k] = item_id;
		item_set->k += 1;
	}
}

void add_item_set_to_hash_table(item_set * item_set, hash_table * table){
	if(item_set == NULL || table == NULL){
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

void add_item_to_hash_table(int item_id,hash_table * table){
	if(!item_in_hash_table(item_id,table)){
		unsigned int index = hash_item_id(item_id);
		hash_node * new_node = init_node();
		if(new_node == NULL){
			return;
		}
		add_item_to_item_set(item_id,new_node->item_set);
		if(table->pointers[index] == NULL){
			table -> pointers[index] = new_node;
		}
		else{
			new_node->next = table->pointers[index];
			table->pointers[index] = new_node;
		}
	}
}

int * add_id_to_integer_table(int id,int * table, int* size){
	if(!(item_in_integer_table(id,table,*size))){
		table = realloc(table,sizeof(int) * (*size + 1));
		if(table != NULL) {
			table[*size] = id;
			(*size)++;
		}
	}
	return table;
}

int * get_items_from_file(char * f,int id_column){
	int * table = NULL;
	int size = 0;
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
				table = add_id_to_integer_table(item_id, table, &size);
			}
			token = strtok(NULL,seperator);
		}
	}
	return table;
}

hash_table * construct_l1(char* f, int support,int id_column){
	int * table = get_items_from_file(f,id_column);
	hash_table * t = init_hash_table();
	FILE * file = fopen(f, "r");
	if(file == NULL){
		perror("Error");
		// return EXIT_FAILURE;
	}
	char line[50];
	const char * seperator = ",";
	// Ignore the first line
	fgets(line, sizeof(line), file);
	int i = 0;
	int count = 0;
	while(table[i] != '\0'){
		count = 0;
		while(fgets(line, sizeof(line),file)){
			char * token = strtok(line, seperator);
			for(int i = 0 ; i < id_column ; i++){
				if(i == id_column - 1){
					int item_id = atoi(token);
					if(table[i] == item_id){
						count++;
						if(count >= support){
							add_item_to_hash_table(item_id,t);
						}
					}
				}
				token = strtok(NULL,seperator);
			}
			if(count >= support){
				break;
			}
		}
		i++;
	}
	return t;
}

// hash_table * apriori_algorithme(char * f){

// }

int main(int argc, char const *argv[])
{
	hash_table * t = construct_l1("ratings.csv",1,2);
	display_hash_table(t);
	// int * t = get_items_from_file("try.csv",2);
	// int i = 0;
	// while(t[i] != '\0'){
	// 	printf("%d\n",t[i]);
	// 	i++;
	// }
	return 0;
}