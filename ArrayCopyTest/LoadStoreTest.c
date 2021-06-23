#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include <papi.h>

#define event_count (3)

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
	int n = atof(argv[1]);
	int nMinusOne = n-1;
	//Creating the arrays.
	double *A = (double*)malloc(n*sizeof(double));
	double *B = (double*)malloc(n*sizeof(double));
	for(i=0;i<n;i++){
		A[i] = (double) rand();
		B[i] = (double) rand();
	}

	//Counter
	int events[event_count] = {PAPI_L1_TCM, PAPI_L2_DCH, PAPI_L3_DCH}; // L3 Data Cache Read
	int ret;
	long long int values[event_count]; // result
	/* start counters */
//	ret = PAPI_start_counters(events, event_count);
//	CHECK_EQ(ret, PAPI_OK);
//	printf("PAPI_L3_DCR: %lli\n", values[0]);

	double time = mysecond();

	ret = PAPI_start_counters(events, event_count);
	//Copying Data from array A to array B.
	#pragma omp parallel
	{
		#pragma omp single
		{
			num_threads = omp_get_num_threads();
		}
		while( k<1 ){
			#pragma omp barrier
			#pragma omp single
			{
				k++;
			}
			//double temp;
			#pragma omp for
			for( i=1; i<n; i++){
				B[i] = A[i];
			}
		}
	}
	ret = PAPI_read_counters(values, event_count);
	printf("%lli, %lli, %lli.\n", values[0], values[1], values[2]);
	printf("READS: %lli stk.\n", values[0]-(values[1]+values[2]));
//	printf("PAPI_L3_TCM: %lli cache misses.\n", values[0]);
//	printf("PAPI_L3_TCW: %lli total cache writes.\n", values[1]);
	time = mysecond()-time;

	/* read counters */
//	ret = PAPI_read_counters(values, event_count);
//	CHECK_EQ(ret, PAPI_OK);//
//	printf("PAPI_L3_DCR: %lli\n", values[0]);

	printf("%d,%f\n", num_threads, time);

	//Freeing up memory.
	free(A);
	free(B);
	return 0;
}
