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
	return 0;
}

//double** test_time;
//test_time = mysecond();
//test_time = mysecond() - test_time;
//
