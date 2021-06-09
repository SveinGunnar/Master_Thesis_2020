#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>

#include "/usr/include/papi.h"

#define event_count (1)

double mysecond(){ //fpo 2
	struct timeval tp;
	struct timezone tzp;
	int i;
	i = gettimeofday(&tp,&tzp);
	return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}


int main(int argc, char *argv[]) {
	int num_threads;
	int i,j,k;
	double inverseEigth = 1/8;
	int m = atof(argv[1]);
	int mMinusOne = m-1;
	int n = atof(argv[2]);
	int nMinusOne = n-1;
	//Creating the arrays.
	double **A = (double**)malloc(m*sizeof(double*));
	double **B = (double**)malloc(m*sizeof(double*));
	for(i=0;i<m;i++){
		A[i] = (double*)malloc(n*sizeof(double));
		B[i] = (double*)malloc(n*sizeof(double));
		for(j=0;j<n;j++){
			A[i][j] = (double) rand();
		}
	}

	//Counter
	int events[event_count] = {PAPI_L3_DCR}; // L3 Data Cache Read
	int ret;
	long long int values[event_count]; // result
	/* start counters */
	ret = PAPI_start_counters(events, event_count);
	CHECK_EQ(ret, PAPI_OK);
	
	double time = mysecond();
	//Copying Data from array A to array B.
	#pragma omp parallel
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();
		}
		while( k<5000 ){
			#pragma omp barrier
			#pragma omp single
			{
				k++;
			}
			double temp;
			#pragma omp for
			for( i=1; i<mMinusOne; i++){
				for( j=1; j<nMinusOne; j++){
					temp = A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
						   A[i][j-1]        +        A[i][j+1]+
						  A[i+1][j-1] + A[i+1][j] + A[i+1][j+1];
					B[i][j] = temp*inverseEigth;
				}
			}
		}
	}
	time = mysecond()-time;

	/* read counters */
	ret = PAPI_read_counters(values, event_count);
	CHECK_EQ(ret, PAPI_OK);


	printf("%d,%f\n", num_threads, time);

	//Freeing up memory.
	for(i=0;i<m;i++){
		free(A[i]);
		free(B[i]);
	}
	free(A);
	free(B);
	return 0;
}
