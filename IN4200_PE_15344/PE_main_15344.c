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
	argv[2] = damping constant d
	argv[3] = convergence threshold value e
	argv[4] = n value for showing the top n webpages
*/
int main(int argc, char **argv){
        const char path[] = "/mnt/pmem0-xfs/pool.obj";
        //PMEMobjpool *pop;
	pop = pmemobj_open(path, LAYOUT_NAME);

        if (pop == NULL) {
                perror(path);
                return 1;
        }
	
	read_graph_from_file(argv[1]);
        printf("Nodes: %d, Edges: %d\n", nodes, edges);

	int i,j;
	double iN = 1.0/nodes;
	int top_n_index;
	x = (double*)malloc(nodes*sizeof(double));
	xk_1 = (double*)malloc(nodes*sizeof(double));

        POBJ_ALLOC(pop, &nvm_values, double, sizeof(double) * nodes, NULL, NULL);

	double test_time = mysecond();

	//omp_set_lock(&top_n_lock);
	omp_init_lock(&lock_a);
	omp_init_lock(&lock_b);
	omp_set_lock(&lock_b);
	iteration_ongoing = 1;

	#pragma omp parallel num_threads(2)
	{
		int thread_id = omp_get_thread_num();
		if( thread_id == 0){
			PageRank_iterations( atof(argv[2]), atof(argv[3]) );
		}
		else if( thread_id == 1){
			top_n_index = top_n();
		}
		printf("I'm number %d\n", thread_id);
	}
	test_time = mysecond() - test_time;
	printf("Time: %lf\n\n", test_time);

	printf("Top n is: %d and has value %lf\n", top_webpage, D_RO(nvm_values)[top_webpage]);

	top_n_webpages( atof(argv[4]) );
	
	//Prints "return 0" when program ends without crashing
	printf("\nreturn 0 det er slutt!\n");
	POBJ_FREE(&nvm_values);
	pmemobj_close(pop);
	return 0;
}

//double** test_time;
//test_time = mysecond();
//test_time = mysecond() - test_time;
//
