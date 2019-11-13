#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdint.h>
#include <string.h>
#include <sys/time.h>
#include <limits.h>
#include <float.h>
#include <libpmemobj.h>



int main(){
	//long long int safd = 34;

	clock_gettime(CLOCK_REALTIME, &start);

    	// chew up some CPU time
    	int i,j; for (i=0,j=0; i<100000000; i++) { j+=i*i; }

    	clock_gettime(CLOCK_REALTIME, &finish);

    	long seconds = finish.tv_sec - start.tv_sec;
    	long ns = finish.tv_nsec - start.tv_nsec;

    	if (start.tv_nsec > finish.tv_nsec) { // clock underflow
		--seconds;
		ns += 1000000000;
    	}
    	printf("seconds without ns: %ld\n", seconds);
    	printf("nanoseconds: %ld\n", ns);
    	printf("total seconds: %e\n", (double)seconds + (double)ns/(double)1000000000);
}
