#include "algo.h"

item_set* init_set(){
	item_set * new_item_set = malloc(sizeof(item_set));
	new_item_set -> k = 0;
	new_item_set -> items = malloc(sizeof(item));
	return new_item_set;
}

basket* init_basket(int id){
	basket * new_basket = malloc(sizeof(basket));
	new_basket -> basket_id = id;
	new_basket -> size = 0;
	new_basket -> items = malloc(sizeof(item));
	return new_basket;
}

baskets * init_baskets(){
	baskets * new_baskets = malloc(sizeof(baskets));
	new_baskets -> size = 0;
	return new_baskets;
}

large_item_set * init_large_item_set(int support){
	large_item_set * new_large_item_set = (large_item_set*)malloc(sizeof(large_item_set));
	new_large_item_set -> support = support;
	new_large_item_set -> items = *init_set();
	new_large_item_set -> next = NULL;
	return new_large_item_set;
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

bool two_item_sets_are_similar(item_set * s1,item_set * s2){
	if(s1->k != s2->k) return false;
	for (int i = 0 ; i < s1->k ; i++){
		if(!in_set(s1->items[i],s2)) return false;
	}
	return true;
}

bool in_large_item_set(item_set *it,large_item_set * l){
	while(l != NULL){
		if(two_item_sets_are_similar(it,&(l->items))){
			return true;
		}
		 l = l -> next;
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

baskets * generate_baskets(char * f){
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
    basket * b = init_basket(0);
	while(fgets(line,sizeof(line),file)){
		char * token = strtok(line, seperator);
		int basket_number = atoi(token);
		if(basket_number != a){
			if(b -> size != 0){
				add_baskets(b,bs);
			}
			b = init_basket(basket_number);
		}
		for(int i = 0 ; i < 2 ; i++){
			if(i==0){
				a = atoi(token);
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
	add_baskets(b,bs);
	// display_baskets(bs);
	fclose(file);
	return bs;
}

large_item_set* add_large_item_set(item_set is,large_item_set * l){
	large_item_set * new_large_item_set = init_large_item_set(l->support);
	new_large_item_set ->items = is;
	if(l==NULL){
		return new_large_item_set;
	}
	else{
		if(!in_large_item_set(&(is),l)){
			large_item_set *curr = l;
			while(curr-> next != NULL){
				curr = curr -> next;
			}
			curr -> next = new_large_item_set;
		}
	}
	return l;
}

void display_itemset(item_set * s){
	printf("{");
	for(int i = 0 ; i < s->k ; i++){
		if(i == s-> k-1){
			printf(" %d }\n",s->items[i].item_id);
		}
		else{
			printf(" %d , ",s->items[i].item_id);
		}
	}
}

void display_basket(basket b){
	printf("Basket ID : %d\n",b.basket_id);
	printf("Basket Size : %d\n",b.size);
	printf("{");
	for(int i = 0 ; i < b.size ; i++){
		if(i == b.size-1){
			printf(" %d }\n\n\n",b.items[i].item_id);
		}
		else{
			printf(" %d ,",b.items[i].item_id);
		}
	}
}

void display_baskets(baskets * bs){
	for(int i = 0 ; i < bs->size ; i++){
		display_basket(bs->bsk_list[i]);
	}
}

void display_large_item_set(large_item_set * l){
	while(l->next != NULL){
		l=l->next;
		display_itemset(&(l->items));
	}
}

item_set * cpy_item_set(item_set * s){
	item_set * copy = init_set();
	for(int i = 0 ; i < s -> k ; i++){
		int id = s->items[i].item_id;
		item t;
		t.item_id = id;
		add_itemset(t,copy);
	}
	return copy;
}

large_item_set * construct_l1(char * f,int support){
	baskets * bs = generate_baskets(f);
	item_set * is = init_set();
	for(int i = 0 ; i < bs -> size ; i++){
		basket b = bs->bsk_list[i];
		for(int j = 0 ; j < b.size ; j++){
			add_itemset(b.items[j],is);
		}
	}

	large_item_set * c1 = init_large_item_set(support);
	item_set * is_1 = init_set();
	for(int i = 0 ; i<is-> k ; i++){
		is_1 = init_set();
		add_itemset(is -> items[i],is_1);
		add_large_item_set(*is_1,c1);
	}
	
	large_item_set * l1 = init_large_item_set(support);
	while(c1->next != NULL){
		c1 = c1->next;
		int count = 0;
		for(int j = 0 ; j < bs->size ; j++){
			if(in_basket(*(c1->items.items),&(bs->bsk_list[j]))){
				count++;
				if(count>=support){
					l1 = add_large_item_set(c1->items,l1);
					break;
				}
			}
		}
	}
	return l1;
}

item_set* get_items_from_large_item_set(large_item_set* l){
	item_set * s = init_set();
	while(l != NULL){
		for(int i = 0 ; i < l->items.k ; i++){
			add_itemset(l->items.items[i],s);
		}
		l = l->next;
	}
	return s;
}

// large_item_set* construct_ck(item_set * s,large_item_set* lk_1){
// 	large_item_set* l = lk_1;
// 	memcpy(l,lk_1,sizeof(large_item_set));
// 	int k = l->items.k;
// 	if(s == NULL){
// 		return NULL;
// 	}
// 	// display_large_item_set(l);
// 	item_set * new = init_set();
// 	large_item_set * ck = init_large_item_set(l->support);
// 	l=l->next;
// 	while(l != NULL){
// 		// display_itemset(new);
// 		new = cpy_item_set(&(l->items));
// 		// display_itemset(new);
// 		// new = &(l->items);
// 		// printf("%d\n",new->k);
// 		// display_itemset(new);

// 		for (int i = 0 ; i < s->k ; i++){
// 			// printf("iteration %d\n",i);
// 			printf("Your boolean variable is: %d\n",new->k != l->items.k + 1);
// 			// printf("%d\n",l->items.k+1);
// 			if(new->k != l->items.k + 1){
// 				// printf("%d != %d\n",new->k,l->items.k+1);
// 				add_itemset(s->items[i],new);
// 				display_itemset(new);
// 				// display_itemset(new);
// 				// printf("%d\n",new->k);
// 			}
// 			else{
// 				// printf("Je suis là\n");
// 				printf("Here is the new new after something : ");
// 				display_itemset(new);
// 				ck = add_large_item_set(*new,ck);
// 				printf("Here is ck after the last element was added : ");
// 				display_large_item_set(ck);
// 				item_set * new = init_set();
// 				new = cpy_item_set(&(l->items));
// 				printf("Here is new after it was reinitialized : ");
// 				display_itemset(new);
// 				add_itemset(s->items[i],new);
// 				printf("Here is new after the current element was added : ");
// 				display_itemset(new);
// 				if(i == s->k - 1 && l-> next != NULL){	
// 					ck = add_large_item_set(*new,ck);
// 				}
// 			}
// 		}
// 		l = l->next;
// 	}
// 	return ck;
// }

large_item_set * construct_ck(large_item_set * lk_1){
	item_set* s = get_items_from_large_item_set(lk_1);
	item_set * new = init_set();
	large_item_set * ck = init_large_item_set(lk_1->support);
	lk_1=lk_1->next;
	while(lk_1 != NULL){
		new = cpy_item_set(&(lk_1->items));
		for(int i = 0 ; i < s->k ; i++){
			new = cpy_item_set(&(lk_1->items));
			add_itemset(s->items[i],new);
			if(new->k == lk_1->items.k+1){
				ck = add_large_item_set(*new,ck);
			}
		}
		lk_1=lk_1->next;
	}

}

large_item_set* apriori_generator(large_item_set * lk_1){
	item_set* s = get_items_from_large_item_set(lk_1);
	large_item_set * ck = construct_ck(lk_1);
}

large_item_set* apriori_algorithme(char * f,int support){
	large_item_set * l1 = construct_l1(f,support);
	return l1;
}


int main(int argc, char const *argv[]) {
	large_item_set* l = apriori_algorithme("ratings.csv",250);
	// display_large_item_set(l);
	// item_set* s = get_items_from_large_item_set(l);
	// item_set* copy = cpy_item_set(s);
	// display_itemset(copy);
	// item il;
	// il.item_id = 260;
	// add_itemset(il,copy);
	// display_itemset(s);
	// display_itemset(copy);
	printf("\n\n\n");
	// display_itemset(s);
	large_item_set *ck = construct_ck(l);
	printf("\n\n\n");
	display_large_item_set(ck);



	// baskets * x = generate_baskets("ratings.csv");
	// if(x == NULL){
	// 	return EXIT_FAILURE;
	// }
	// display_baskets(x);




	// for(int i = 0 ; i < x-> size ; i++){
	// 	basket curr = x -> bsk_list[i];
	// 	printf("Basket ID : %d ***** Size = %d ***** order : %d\n",curr.basket_id,curr.size,i+1);
	// 	for(int j = 0 ; j < curr.size ; j++){
	// 		printf("Item ID , %d\n",curr.items[j].item_id);
	// 	}
	// }

	/*basket * b = init_basket();
	int x = add_basket();*/

	// item_set * is = init_set();
	// for(int i = 1 ; i < 20 ; i+=2){
	// 	item it;
	// 	it.item_id = i;
	// 	add_itemset(it,is);
	// }
	// item il;
	// il.item_id = 260;
	// add_itemset(il,is);
	// display_itemset(is);
	// large_item_set * l = init_large_item_set(10);
	// item_set * is_1 = init_set();
	// for(int i = 0 ; i<is-> k ; i++){
	// 	is_1 = init_set();
	// 	add_itemset(is -> items[i],is_1);
	// 	add_large_item_set(*is_1,l);
	// }
	// add_large_item_set(*is,l);

	printf("\n");
	// display_large_item_set(l);
	// while(l -> next != NULL){
	// 	l = l -> next;
	// 	printf("%d\n",l->items.k);
	// }

	return 0;
}