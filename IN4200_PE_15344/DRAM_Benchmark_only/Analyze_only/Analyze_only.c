#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
//#include "functions.h"


double mysecond(){
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

void PageRank_iterations(int node_size, int max_threads){
	int num_threads;

	double *temp_x; //Will be using this when swapping x and x^k-1
	int nodes = node_size;
	//inverse N
	double iN = 1.0/nodes;

	//This variable will be compared against the convergence threshold value
	//double diff=0.0;
	double average=0.0;
	int size;

	//Counts the number of iterations.
	int n=0;
	//int i;
	int iteration_size=1;
        double analyze_time;
	double calculation=0.0, temp_calc;
	//double filler=0;

	double *x = (double*)malloc(node_size*sizeof(double));
	double *xk_1 = (double*)malloc(node_size*sizeof(double));

	#pragma omp parallel num_threads(max_threads)
	{
		int i,j;

		//Adds values to x^0.
		#pragma omp for
		for( i=0; i<nodes; i++){
			xk_1[i] = ((double)rand()/(double)(RAND_MAX));;
			x[i] = ((double)rand()/(double)(RAND_MAX));;
		}

		#pragma omp single
                {
			analyze_time = mysecond();
		}
		
		while( n<5000 ){
			#pragma omp barrier
			#pragma omp single
			{
				n++;
				average = 0;
			}

			//calculation
			#pragma omp barrier
			#pragma omp single
			{
				temp_x = xk_1;
                                xk_1 = x;
                                x = temp_x;

				//starting time measurement of calculation.
				//temp_calc=mysecond();
			}

			//Analyse part
			#pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){
                        	average += xk_1[i];
                        }

			#pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){
                        	average += xk_1[i];
                     	}

			#pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){
                        	average += xk_1[i];
                   	}

			#pragma omp for reduction(+ : average)
			for(i=0;i<nodes;i++){
          			average += xk_1[i];
                     	}

			#pragma omp for reduction(+ : average)
                       	for(i=0;i<nodes;i++){
                		average += xk_1[i];
                   	}

			#pragma omp barrier
			#pragma omp single
			{
				average *= iN;
				//filler += average;
				//calculation+=mysecond()-temp_calc;
			}
		}//end of while-loop
	}//End parallel
	analyze_time = mysecond() - analyze_time;
	//printf("Threads, Total time, Iteration time, Calculation time\n");
	//printf("%f\n", filler);
        printf("%d,%f\n", max_threads, analyze_time);
	//For testing:
	//printf("iterations: %d\n", n);
	//printf("%f, %f, %f %f\n", average, sumSquare, test1, test2);
	//printf("temp_counter_double: %f\n", temp_counter_double);
	//printf("temp_counter_int: %f\n", temp_counter_ana);
}

/*
	argv[1] = Number of nodes
	argv[2] = Number of threads
*/
int main(int argc, char **argv){
	
	//read_graph_from_file(argv[1]);
        //printf("Nodes: %d, Edges: %d\n", nodes, edges);

	PageRank_iterations( atof(argv[1]), atof(argv[2]) );
	
	//Prints "return 0" when program ends without crashing
	//printf("\nreturn 0 det er slutt!\n");
	return 0;
}
