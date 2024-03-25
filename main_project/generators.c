#include "main.h"

double random_ratio(){
	return (double)rand() / (double)RAND_MAX ;
}

int generate_0_or_1(double probability){
	double random_value = random_ratio();
	if(random_value < probability){
		return 1;
	}
	return 0;
}

baskets * generate_baskets_randomly(int nb_baskets,int nb_items,double probability){
	if(probability < 0 || probability > 1){
		return NULL;
	}
	baskets * bs = init_baskets();
	int** matrix = (int**)malloc(nb_baskets * sizeof(int*));
	for(int i = 0 ; i < nb_baskets ; i++){
		matrix[i] = (int *)malloc(nb_items * sizeof(int));
	}
	for(int i = 0 ; i < nb_baskets ; i++){
		for(int j = 0 ; j < nb_items ; j++){
			matrix[i][j] = generate_0_or_1(probability);
		}
	}
	bs->basket = matrix;
	bs->count = nb_baskets;
	return bs;
}

void generate_csv(int nb_basket, int nb_items, double probability){
	FILE *file = fopen("DataRand.csv", "w");
	if (file == NULL) {
		fprintf(stderr, "Error opening file.\n");
		return;
	}
   
	fprintf(file, "transaction ID,items"); 
	for (int i = 1; i <= nb_basket; i++) {
		for (int j = 1; j <= nb_items; j++) {
			if (generate_0_or_1(probability) == 1) {
				fprintf(file, "\n");
				fprintf(file, "%d,", i);
				fprintf(file, "%d", j);
			}
		}
	}

	fclose(file);
}

// void