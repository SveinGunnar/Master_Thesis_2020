#include <stdio.h>
#include "functions.h"


/*
	argv[1] = filename of the webpage linkage information
	argv[2] = damping constant d
	argv[3] = convergence threshold value e
	argv[4] = n value for showing the top n webpages
	argv[5] = Number of iteration threads
	argv[6] = Number of transfer threads
	argv[7] = Number of max threads
*/
int main(int argc, char **argv){
	
	read_graph_from_file(argv[1]);
        //printf("Nodes: %d, Edges: %d\n", nodes, edges);

	int i,j;
	double iN = 1.0/nodes;
	int top_n_index;
	x = (double*)malloc(nodes*sizeof(double));
	xk_1 = (double*)malloc(nodes*sizeof(double));


	double test_time = mysecond();

	//omp_set_lock(&top_n_lock);
	omp_init_lock(&lock_a);
	omp_init_lock(&lock_b);
	omp_init_lock(&lock_c);
	omp_set_lock(&lock_b);
	omp_set_lock(&lock_c);
	iteration_ongoing = 1;
	transfer_ongoing = 1;

	iter_threads = atof(argv[5]);
	transfer_threads = atof(argv[6]);
	//max_threads = atof(argv[7]);

	#pragma omp parallel num_threads(2)
	{
		int thread_id = omp_get_thread_num();
		if( thread_id == 0){
			PageRank_iterations( atof(argv[2]), atof(argv[3]) );
		}
		else if( thread_id == 1){
			transfer_DRAM_to_NVM();
		}
		//else if( thread_id == 1){
                //      top_n_index = top_n();
                //}
		//printf("Number %d is done.\n", thread_id);
	}
	test_time = mysecond() - test_time;
	//printf("Iteration_threads transfer_threads max_threads time\n");
	printf("%d, %d, %lf\n", iter_threads, transfer_threads, test_time);

	//printf("Top n is: %d and has value %lf\n", top_n_index, D_RO(nvm_values)[top_n_index]);

	//top_n_webpages( atof(argv[4]) );
	
	//Prints "return 0" when program ends without crashing
	//printf("\nreturn 0 det er slutt!\n");
	return 0;
}

//double** test_time;
//test_time = mysecond();
//test_time = mysecond() - test_time;
//
