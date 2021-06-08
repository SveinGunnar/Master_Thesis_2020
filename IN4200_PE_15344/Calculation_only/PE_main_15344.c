#include <stdio.h>
#include <libpmemobj.h>
#include "PE_functions_15344.h"

//#define TOID_ARRAY(x) TOID(x)
//#define COUNT_OF(x) (sizeof(x) / sizeof(x[0]))
//#define MAX_BUFFLEN 30
//#define MAX_TYPE_NUM 8

//POBJ_LAYOUT_BEGIN(array);
//POBJ_LAYOUT_TOID(array, double);
//POBJ_LAYOUT_END(array);
#define LAYOUT_NAME "my_layout"

static PMEMobjpool *pop;

/*
	argv[1] = filename of the webpage linkage information
	argv[2] = Number of iteration threads
	argv[3] = Number of transfer threads
	argv[4] = Number of max threads
*/
int main(int argc, char **argv){
	//printf("seg fault test");
	read_graph_from_file(argv[1]);
        printf("test\n");
	//printf("Nodes: %d, Edges: %d\n", nodes, edges);
	//printf("seg fault test");
	int i,j;
	double iN = 1.0/nodes;
	iteration_time=0.0, transfer_time=0.0;
	int top_n_index;
	x = (double*)malloc(nodes*sizeof(double));
	xk_1 = (double*)malloc(nodes*sizeof(double));

	//omp_set_lock(&top_n_lock);
	omp_init_lock(&lock_a);
	omp_init_lock(&lock_b);
	omp_init_lock(&lock_c);
	omp_set_lock(&lock_b);
	omp_set_lock(&lock_c);
	iteration_ongoing = 1;
	transfer_ongoing = 1;

	iter_threads = atof(argv[2]);
	transfer_threads = atof(argv[3]);
	//max_threads = atof(argv[4]);
	//printf("test 1\n");
	
	double test_time = mysecond();
	//printf("test\n");
	PageRank_iterations();
	test_time = mysecond() - test_time;
	
	//printf("Iteration_threads transfer_threads max_threads time\n");
	
	printf("%d,%d,%d,%f,%f,%f\n", iter_threads+transfer_threads, iter_threads, transfer_threads, iteration_time, iteration_idle_time, test_time);
	//printf("%d, %d, %lf\n", iter_threads, transfer_threads, test_time);

	//printf("Top n is: %d and has value %lf\n", top_n_index, D_RO(nvm_values)[top_n_index]);

	//top_n_webpages( atof(argv[4]) );
	
	//Prints "return 0" when program ends without crashing
	//printf("\nreturn 0 det er slutt!\n");
	POBJ_FREE(&nvm_values);
	pmemobj_close(pop);
	return 0;
}

//double** test_time;
//test_time = mysecond();
//test_time = mysecond() - test_time;
//
