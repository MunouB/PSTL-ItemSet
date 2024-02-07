#include "main.h"

int main(int argc, char const *argv[]){
	hash_table * table = construct_l1("ratings.csv",100,2);
	display_hash_table(table);
	free_hash_table(table);
	// int *t = NULL;
	// int size = 0;
	// srand(time(NULL));
	// for(int j = 0 ; j < 10 ; j++){
	// 	int random = rand() % 1000;
	// 	printf("%d\n\n\n",random);
	// 	t = add_id_to_integer_table(random,t,&size);
	// 	if(j==9){
	// 		hash_table * table = construct_c1(t,size);
	// 		display_hash_table(table);
	// 	}
	// }
	// for(int i = 0 ; i < size +2 ; i++){
	// 	printf("%d\n",t[i]);
	// }
	// int freq[10] = {0,0,0,0,0,0,0,0,0,0};
	// table = construct_c1(t);
	// display_hash_table(table);
	
	// Algorithm to increase the frequencies table values of a single item
	// int initial_index = -1;
	// int basket[6] = {12,515,608,643,904,2904};
	// for(int i = 0 ; i < 6 ; i++){
	// 	int index = hash_item_id(basket[i]);
	// 	item_set * item_set = init_item_set();
	// 	add_item_to_item_set(basket[i],item_set);
	// 	display_itemset(item_set);
	// 	hash_node * current = table->pointers[index];
	// 	while(current != NULL){
	// 		printf("Je suis là et ton variable de bool : %d\n",two_item_sets_are_similar(item_set,current->item_set));
	// 		if(two_item_sets_are_similar(item_set,current->item_set)){
	// 			initial_index = current -> index;
	// 			printf("%d\n\n",initial_index);
	// 			freq[initial_index] += 1;
	// 			break;
	// 		}
	// 		current = current -> next;
	// 	}
	// 	free(item_set);
	// }

	// for (int i = 0; i < 10; i++){
	// 	printf("%d\n",freq[i]);
	// }

	// hash_table * table = construct_l1("ratings.csv",100,2);
	// display_hash_table(table);
	// int * t = get_items_from_file("try.csv",2);
	// item_set * item_set = init_item_set();
	// display_itemset(item_set);
	// hash_table * table = init_hash_table();
	// add_item_set_to_hash_table(item_set,table);
	// display_hash_table(table);
	// int * t = get_items_from_file("try.csv",2);
	// int i = 0;
	// while(t[i] != '\0'){
	// 	add_item_to_item_set(t[i],item_set);
	// 	i++;
	// }
	// printf("\n");

	// display_itemset(item_set);
	// display_hash_table(table);
	// add_item_set_to_hash_table(item_set,table);
	// display_hash_table(table);
	// display_itemset(item_set);
	// hash_table * table = init_hash_table();
	// display_hash_table(table);
	// int * t = get_items_from_file("try.csv",2);
	// int i = 0;
	// while(t[i] != '\0'){
	// 	add_item_to_hash_table(t[i],table);
	// 	i++;
	// }
	// printf("\n");
	// display_hash_table(table);
	// display_hash_table(table);
	return 0;
}
