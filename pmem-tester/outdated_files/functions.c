#include "functions.h"

#define BILLION 1E9

void transfer(float *a, float *b, int n){
	int i;
	double accum;
	struct timespec start, stop;

	//Time start.
        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
                perror( "clock gettime" );
                exit( EXIT_FAILURE );
        }

	for(i=0;i<n;i++){
		b[i] = a[i];
	}

	//Time stop.
        if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
                perror( "clock gettime" );
                exit( EXIT_FAILURE );
        }
	accum = ( stop.tv_sec - start.tv_sec )
              + ( stop.tv_nsec - start.tv_nsec ) / BILLION;
	printf("Time: %lf\n", accum);
}	
