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

int * get_items_from_hash_table(hash_table * table, int* size){ //correct
	int * t = NULL;
	for(int j = 0 ; j < TABLE_SIZE ; j++){
		hash_node * current = table->pointers[j];
		while(current != NULL){
			for(int i = 0 ; i < current->item_set->k ; i++){
				t = add_id_to_integer_table(current->item_set->items[i],t,size);
			}
			current = current->next;
		}
	}
	return t;
}

item_set * get_sub_item_set_without_element(item_set * set, int element){
	item_set * sub_set = init_item_set();
	for(int i = 0 ; i < set->k ; i++){
		if(set->items[i] != element){
			add_item_to_item_set(set->items[i],sub_set);
		}
	}
	return sub_set;
}

item_set * cpy_item_set(item_set * set){
	item_set * res = init_item_set();
	for(int i = 0 ; i < set->k ; i++){
		add_item_to_item_set(set->items[i],res);
	}
	return res;
}

double get_execution_time(char *f, int support, int item_id_column, int basket_id_column, int *size) {
	clock_t begin = clock();
	hash_table *t = NULL;

	// Attempt to execute
	if ((t = apriori_algorithm_1(f, support, item_id_column, basket_id_column, size)) == NULL) {
		fprintf(stderr, " Failed to execute apriori\n");
		return -1.0;
	}

	// Measure time spent
	clock_t end = clock();
	double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;

	// Free memory allocated for t
	free_hash_table(t);

	return time_spent;
}

void run_experiment(int varchoice){
	if(varchoice == 1){
		run_experiment_probability();
	}
	else if(varchoice == 2){
		run_experiment_transaction();
	}
	else if(varchoice == 3){
		run_experiment_items();
	}
	else if(varchoice == 4){
		run_experiment_support();
	}
}

void run_experiment_probability(){
	srand(time(NULL));
	// les params fixes
	int nb_basket = 60;
	int nb_items = 100;
	int support = 30;
	int param1 = 1; // colonne id
	int param2 = 2; // colonne items

	FILE *dataFile = fopen("execution_times.dat", "w");
	if (dataFile == NULL) {
		fprintf(stderr, "Error opening file.\n");
		exit(1);
	}

	for (double probability = 0.1; probability <= 0.9; probability += 0.02) {
		double total_exec_time = 0;
		for(int i = 0 ; i < 1 ; i++){
			int items = 0;
			generate_csv(nb_basket, nb_items, probability);
			// Check if CSV file was successfully generated
			if (access("DataRand.csv", F_OK) != -1) {
				// File exists
				total_exec_time += get_execution_time("DataRand.csv", support, param1, param2, &items);
			} else {
				// File doesn't exist
				fprintf(stderr, "failed to generate CSV file.\n");
			}
		}
		double exec_time = total_exec_time / 1.0;
		fprintf(dataFile, "%.2f %f\n", probability, exec_time);
	}
	fclose(dataFile);

	FILE *gnuplotPipe = popen("gnuplot -persist", "w");
	if (gnuplotPipe) {
		fprintf(gnuplotPipe, "Test\n");
		fprintf(gnuplotPipe, "set xlabel 'Probablité'\n");
		fprintf(gnuplotPipe, "set ylabel 'Temps execution (secondes)'\n");
		fprintf(gnuplotPipe, "plot 'execution_times.dat' with linespoints title 'Execution Time'\n");
		fprintf(gnuplotPipe, "pause -1\n");
		fprintf(gnuplotPipe, "exit\n");
		pclose(gnuplotPipe);
	} else {
		fprintf(stderr, "Error executing gnuplot.\n");
		exit(1);
	}
}

void run_experiment_transaction(){
	srand(time(NULL));
	// les params fixes
	double probability = 0.7;
	int nb_items = 100;
	int support = 20;
	int param1 = 1; // colonne id
	int param2 = 2; // colonne items

	FILE *dataFile = fopen("execution_times.dat", "w");
	if (dataFile == NULL) {
		fprintf(stderr, "Error opening file.\n");
		exit(1);
	}

	for (int nb_basket = 30; nb_basket <= 60; nb_basket += 1) {
		double total_exec_time = 0;
		for(int i = 0 ; i < 1 ; i++){
			int items = 0;
			generate_csv(nb_basket, nb_items, probability);
			// Check if CSV file was successfully generated
			if (access("DataRand.csv", F_OK) != -1) {
				// File exists
				total_exec_time += get_execution_time("DataRand.csv", support, param1, param2, &items);
			} else {
				// File doesn't exist
				fprintf(stderr, "failed to generate CSV file.\n");
			}
		}
		double exec_time = total_exec_time / 1.0;
		fprintf(dataFile, "%d %f\n", nb_basket, exec_time);
	}
	fclose(dataFile);

	FILE *gnuplotPipe = popen("gnuplot -persist", "w");
	if (gnuplotPipe) {
		fprintf(gnuplotPipe, "Test\n");
		fprintf(gnuplotPipe, "set xlabel 'Nb de transactions'\n");
		fprintf(gnuplotPipe, "set ylabel 'Temps execution (secondes)'\n");
		fprintf(gnuplotPipe, "plot 'execution_times.dat' with linespoints title 'Execution Time'\n");
		fprintf(gnuplotPipe, "pause -1\n");
		fprintf(gnuplotPipe, "exit\n");
		pclose(gnuplotPipe);
	} else {
		fprintf(stderr, "Error executing gnuplot.\n");
		exit(1);
	}
}

void run_experiment_items(){
	srand(time(NULL));
	// les params fixes
	double probability = 0.5;
	int nb_basket = 60;
	int support = 20;
	int param1 = 1; // colonne id
	int param2 = 2; // colonne items

	FILE *dataFile = fopen("execution_times.dat", "w");
	if (dataFile == NULL) {
		fprintf(stderr, "Error opening file.\n");
		exit(1);
	}

	for (int nb_items = 50; nb_items <= 100; nb_items += 1) {
		double total_exec_time = 0;
		for(int i = 0 ; i < 1 ; i++){
			int items = 0;
			generate_csv(nb_basket, nb_items, probability);
			// Check if CSV file was successfully generated
			if (access("DataRand.csv", F_OK) != -1) {
				// File exists
				total_exec_time += get_execution_time("DataRand.csv", support, param1, param2, &items);
			} else {
				// File doesn't exist
				fprintf(stderr, "failed to generate CSV file.\n");
			}
		}
		double exec_time = total_exec_time / 1.0;
		fprintf(dataFile, "%d %f\n", nb_items, exec_time);
	}
	fclose(dataFile);

	FILE *gnuplotPipe = popen("gnuplot -persist", "w");
	if (gnuplotPipe) {
		fprintf(gnuplotPipe, "Test\n");
		fprintf(gnuplotPipe, "set xlabel 'Nb de items'\n");
		fprintf(gnuplotPipe, "set ylabel 'Temps execution (secondes)'\n");
		fprintf(gnuplotPipe, "plot 'execution_times.dat' with linespoints title 'Execution Time'\n");
		fprintf(gnuplotPipe, "pause -1\n");
		fprintf(gnuplotPipe, "exit\n");
		pclose(gnuplotPipe);
	} else {
		fprintf(stderr, "Error executing gnuplot.\n");
		exit(1);
	}
}

void run_experiment_support(){
	srand(time(NULL));
	// les params fixes
	double probability = 0.15;
	int nb_basket = 60;
	int nb_items = 60;
	int param1 = 1; // colonne id
	int param2 = 2; // colonne items

	FILE *dataFile = fopen("execution_times.dat", "w");
	if (dataFile == NULL) {
		fprintf(stderr, "Error opening file.\n");
		exit(1);
	}

	for (int support = 1; support <= 40; support += 1) {
		double total_exec_time = 0;
		for(int i = 0 ; i < 1 ; i++){
			int items = 0;
			generate_csv(nb_basket, nb_items, probability);
			// Check if CSV file was successfully generated
			if (access("DataRand.csv", F_OK) != -1) {
				// File exists
				total_exec_time += get_execution_time("DataRand.csv", support, param1, param2, &items);
			} else {
				// File doesn't exist
				fprintf(stderr, "failed to generate CSV file.\n");
			}
		}
		double exec_time = total_exec_time / 1.0;
		fprintf(dataFile, "%d %f\n", support, exec_time);
	}
	fclose(dataFile);

	FILE *gnuplotPipe = popen("gnuplot -persist", "w");
	if (gnuplotPipe) {
		fprintf(gnuplotPipe, "Test\n");
		fprintf(gnuplotPipe, "set xlabel 'Support'\n");
		fprintf(gnuplotPipe, "set ylabel 'Temps execution (secondes)'\n");
		fprintf(gnuplotPipe, "plot 'execution_times.dat' with linespoints title 'Execution Time'\n");
		fprintf(gnuplotPipe, "pause -1\n");
		fprintf(gnuplotPipe, "exit\n");
		pclose(gnuplotPipe);
	} else {
		fprintf(stderr, "Error executing gnuplot.\n");
		exit(1);
	}
}
