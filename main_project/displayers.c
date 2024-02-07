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

void display_hash_table(hash_table *table){ //correct
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