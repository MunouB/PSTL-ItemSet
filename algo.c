#include "algo.h"

item_set* init_set(){
	item_set * new_item_set = malloc(sizeof(item_set));
	new_item_set -> k = 0;
	new_item_set -> items = malloc(sizeof(item));
	return new_item_set;
}

basket* init_basket(){
	basket * new_basket = malloc(sizeof(basket));
	new_basket -> basket_id = 0;
	new_basket -> size = 0;
	new_basket -> items = malloc(sizeof(item));
	return new_basket;
}

baskets * init_baskets(){
	baskets * new_baskets = malloc(sizeof(baskets));
	new_baskets -> size = 0;
	return new_baskets;
}

bool in_set(item item,item_set * s){
	for(int i = 0 ; i < s->k ; i++){
		if(s->items[i].item_id == item.item_id){
			return true;
		}
	}
	return false;
}

bool in_basket(item item,basket * b){
	for(int i = 0 ; i < b->size ; i++){
		if(b->items[i].item_id == item.item_id){
			return true;
		}
	}
	return false;
}

void add_itemset(item item, item_set * s){
	if(!(in_set(item,s))){
		s-> items = realloc(s-> items , sizeof(item) * (s->k + 1));
		s->items[s->k] = item;
		s->k += 1;
	}
}

void add_basket(item item,basket *b){
	if(!(in_basket(item,b))){
		b-> items = realloc(b-> items , sizeof(item) * (b->size + 1));
		b-> items[b->size] = item;
		b->size +=1;
	}
}

void add_baskets(basket * b,baskets *bs){
	bs-> bsk_list = realloc(bs-> bsk_list , sizeof(basket) * (bs->size + 1));
	bs-> bsk_list[bs->size] = * b;
	bs->size +=1;
}

baskets * add_baskets2(char * f){
	baskets *bs = init_baskets();
	FILE * file = fopen(f, "r");
	if(file == NULL){
		perror("Error");
		// return EXIT_FAILURE;
	}
	char line[50];
	const char * seperator = ",";
	fgets(line, sizeof(line), file);
    int a = -1;
    basket * b = init_basket();
	while(fgets(line,sizeof(line),file)){
		char * token = strtok(line, seperator);
		int basket_number = atoi(token);
		if(basket_number != a){
			
			if(b -> size != 0){
				add_baskets(b,bs);
				bs -> size += 1;
			}
			basket * b = init_basket();
		}
		for(int i = 0 ; i < 2 ; i++){
			if(i==0){
				int a = atoi(token);
			}
			if(i == 1){
				int item_id = atoi(token);
				item it;
				it.item_id = item_id;
				add_basket(it,b);
			}
			token = strtok(NULL,seperator);
		}
	}
	fclose(file);
	return bs;
}


void display_basket(basket * b){
	printf("{");
	for(int i = 0 ; i < b->size ; i++){
		if(i == b-> size-1){
			printf(" %d }\n",b->items[i].item_id);
		}
		else{
			printf(" %d ,",b->items[i].item_id);
		}
	}
}

void display_itemset(item_set * s){
	printf("{");
	for(int i = 0 ; i < s->k ; i++){
		if(i == s-> k-1){
			printf(" %d }\n",s->items[i].item_id);
		}
		else{
			printf(" %d ,",s->items[i].item_id);
		}
	}
}

int main(int argc, char const *argv[]) {
	baskets * x = add_baskets2("ratings.csv");
	if(x == NULL){
		return EXIT_FAILURE;
	}

	for(int i = 0 ; i < x-> size ; i++){
		basket curr = x -> bsk_list[i];
		printf("Basket ID : %d ***** Size = %d\n",curr.basket_id,curr.size);
		// display_basket(curr);
	}

	/*basket * b = init_basket();
	int x = add_basket();*/

	return 0;
}