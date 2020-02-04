#include <stdio.h>
#include <time.h>
#include "functions.h"
/*
	argv[1] = filename of the webpage linkage information
	argv[2] = damping constant d
	argv[3] = convergence threshold value e
	argv[4] = n value for showing the top n webpages
*/
int main(int argc, char **argv){
	int i,j;
	clock_t start = clock();
	read_graph_from_file(argv[1]);
	PageRank_iterations( atof(argv[2]), atof(argv[3]) );
	top_n_webpages( atof(argv[4]) );

	//Prints "return 0" when program ends without crashing
	printf("\nreturn 0\n");
	return 0;
}
