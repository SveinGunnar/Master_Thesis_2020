#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include "functions.h"

#define LAYOUT_NAME "my_layout"

//argv[1] = Length of 2d array.
//argv[2] = Length of 2d array.
//argv[3] = NVDIMM array size.
//argv[4] = Number of DRAM threads.
//argv[5] = Number of NVDIMM threads.
//argv[6] = K_length



int main(int argc, char *argv[]) {
	int i,j,k;
	int m = atof(argv[1]);
	int n = atof(argv[2]);
	int dram_threads = atof(argv[3]);
	int K_length = atof(argv[4]);

	calculation(m,n, dram_threads, K_length);
	
//	printf("End of program\n");
}
