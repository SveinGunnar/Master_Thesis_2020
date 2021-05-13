#include <stdio.h>
#include "functions.h"


/*
	argv[1] = filename of the webpage linkage information
	argv[2] = Number of max threads
*/
int main(int argc, char **argv){
	
	read_graph_from_file(argv[1]);
        //printf("Nodes: %d, Edges: %d\n", nodes, edges);

	int i,j;
	double iN = 1.0/nodes;
	int top_n_index;
	x = (double*)malloc(nodes*sizeof(double));
	xk_1 = (double*)malloc(nodes*sizeof(double));

	max_threads = atof(argv[2]);
	PageRank_iterations();
	
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
