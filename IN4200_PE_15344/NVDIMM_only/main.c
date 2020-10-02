#include <stdio.h>
#include <libpmemobj.h>
#include "functions.h"

//static PMEMobjpool *pop;

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
	const char path[] = "/mnt/pmem0-xfs/pool.obj";
	pop = pmemobj_open(path, LAYOUT_NAME);

        if (pop == NULL) {
                perror(path);
                return 1;
        }

	nodes = 1000001;
	edges = 16000000;

	//read_graph_from_file(argv[1]);
        //printf("Nodes: %d, Edges: %d\n", nodes, edges);

	int i,j;
	double iN = 1.0/nodes;
	int top_n_index;
	//x = (double*)malloc(nodes*sizeof(double));
	//xk_1 = (double*)malloc(nodes*sizeof(double));
	POBJ_ALLOC(pop, &x, double, sizeof(double) * nodes, NULL, NULL);
	POBJ_ALLOC(pop, &xk_1, double, sizeof(double) * nodes, NULL, NULL);
	
	POBJ_ALLOC(pop, &CRS_row_ptr, int, sizeof(int) * edges, NULL, NULL);
        POBJ_ALLOC(pop, &CRS_col_idx, int, sizeof(int) * edges, NULL, NULL);
        POBJ_ALLOC(pop, &CRS_values, double, sizeof(double) * edges, NULL, NULL);

	read_graph_from_file(argv[1]);

	iter_threads = atof(argv[5]);
	transfer_threads = atof(argv[6]);
	//max_threads = atof(argv[7]);|

	//double test_time = mysecond();

	//printf("test\n");
	PageRank_iterations( atof(argv[2]), atof(argv[3]) );
	//transfer_DRAM_to_NVM();
	
	//test_time = mysecond() - test_time;
	
	//printf("Iteration_threads transfer_threads max_threads time\n");
	//printf("%d, %d, %lf\n", iter_threads, transfer_threads, test_time);

	//printf("Top n is: %d and has value %lf\n", top_n_index, D_RO(nvm_values)[top_n_index]);

	//top_n_webpages( atof(argv[4]) );
	
	//Prints "return 0" when program ends without crashing
	//printf("\nreturn 0 det er slutt!\n");
	POBJ_FREE(&x);
	POBJ_FREE(&xk_1);
	POBJ_FREE(&CRS_values);
	POBJ_FREE(&CRS_row_ptr);
	POBJ_FREE(&CRS_col_idx);
	//POBJ_FREE(&temp_x);
	return 0;
}

//double** test_time;
//test_time = mysecond();
//test_time = mysecond() - test_time;
//
