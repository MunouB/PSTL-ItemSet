#include "main.h"

void display_itemset(item_set * s){ //correct
	printf("{");
	for(int i = 0 ; i < s->k ; i++){
		printf(" %d",s->items[i]);
		if(i < s-> k - 1){
			printf(" ,");
		}
	}
	printf(" }\n");
}

void display_hash_table(hash_table *table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_node *current = table->pointers[i];
        while (current != NULL) {
            printf(" %d-k Itemset : ", current->item_set->k);
            display_itemset(current->item_set);
            current = current->next;
        }
    }
}



void display_baskets(baskets * bs,int size){
	if(bs == NULL || bs->basket == NULL || bs->count == 0){
		printf("No baskets found\n");
		return;
	}
	for (int i = 0; i < bs->count; i++) {
		printf("Basket %d : ", i + 1);
		for (int j = 0; j < size; j++) {
			printf("%d ", bs->basket[i][j]);
		}
		printf("\n");
	}
}

void display_baskets2(baskets * bs,int size){
	if(bs == NULL || bs->basket == NULL || bs->count == 0){
		printf("No baskets found\n");
		return;
	}
	for (int i = 0; i < bs->count; i++) {
		printf("Basket %d : ", i + 1);
		for (int j = 0; j < size; j++) {
			printf("%d ", bs->basket[i][j]);
		}
		printf("\n");
	}
}
