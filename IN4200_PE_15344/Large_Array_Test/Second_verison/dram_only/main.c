#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include "functions.h"

#define LAYOUT_NAME "my_layout"
//static PMEMobjpool *pop;

//argv[1] = Length of 2d array.
//argv[2] = Length of 2d array.
//argv[3] = NVDIMM array size.
//argv[4] = Number of DRAM threads.
//argv[5] = Number of NVDIMM threads.
//argv[6] = K_length


int main(int argc, char *argv[]) {
	int i,j,k;
	double *dram_time;
	double *nvdimm_time;
	int m = atof(argv[1]);
	int n = atof(argv[2]);
	int dram_threads = atof(argv[3]);
	int K_length = atof(argv[4]);

//	printf("Main parallel.\n");
//	printf("m: %d\n", m);
//	printf("n: %d\n", n);
//	printf("nvdimm_array_length: %d\n", nvdimm_array_length);
//	printf("m-nvdimm_array_length: %d\n", m-nvdimm_array_length);
//	printf("dram_threads: %d\n", dram_threads);
//	printf("nvdimm_threads: %d\n", nvdimm_threads);
//	printf("K_length: %d\n", K_length);

	dram_time = dram_calculation( m, n, dram_threads, K_length);
	
	double dram_average=0;
	for(i=0;i<K_length;i++){
		dram_average += dram_time[i];
	}
	dram_average = dram_average/K_length;

	printf("%d,%d,%d,%lf\n", m, n, dram_threads, dram_average );

	//printf("End of program\n");
}
