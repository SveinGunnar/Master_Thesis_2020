#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <omp.h>
#include "functions.h"

#define LAYOUT_NAME "my_layout"
static PMEMobjpool *pop;

//argv[1] = Length of 2d array.
//argv[2] = Length of 2d array.
//argv[3] = Number of DRAM threads.
//argv[4] = Number of NVDIMM threads.
//argv[5] = NVDIMM array size.



int main(int argc, char *argv[]) {
	int i,j,k;
	int m = atof(argv[1]);
	int n = atof(argv[2]);
	int dram_threads = atof(argv[3]);
	int nvdimm_threads = atof(argv[4]);
	int percents = atof(argv[5]);

	const char path[] = "/mnt/pmem0-xfs/pool.obj";
	//PMEMobjpool *pop;
	pop = pmemobj_open(path, LAYOUT_NAME);
	if (pop == NULL) {
		perror(path);
		return 1;
	}
	POBJ_ALLOC(pop, &C, double, sizeof(double)*percents*n, NULL, NULL);
        POBJ_ALLOC(pop, &D, double, sizeof(double)*percents*n, NULL, NULL);

	calculation(m,n, dram_threads, nvdimm_threads, percents);
	
	POBJ_FREE(&C);
        POBJ_FREE(&D);
	printf("End of program\n");
}
