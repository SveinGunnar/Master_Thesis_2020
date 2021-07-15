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
	int nvdimm_array_length = atof(argv[3]);
	int dram_threads = atof(argv[4]);
	int nvdimm_threads = atof(argv[5]);
	int K_length = atof(argv[6]);

	//Initiate and set locks.
	omp_init_lock(&lock_dram);
	omp_init_lock(&lock_nvdimm);
	omp_set_lock(&lock_dram);
	omp_set_lock(&lock_nvdimm);
	
//	printf("Main parallel.\n");
//	printf("m: %d\n", m);
//	printf("n: %d\n", n);
//	printf("nvdimm_array_length: %d\n", nvdimm_array_length);
//	printf("m-nvdimm_array_length: %d\n", m-nvdimm_array_length);
//	printf("dram_threads: %d\n", dram_threads);
//	printf("nvdimm_threads: %d\n", nvdimm_threads);
//	printf("K_length: %d\n", K_length);

	#pragma omp parallel num_threads(2)
	{
		int thread_id = omp_get_thread_num();
		if( thread_id == 0 ){
			dram_time = dram_calculation( m-nvdimm_array_length, n, dram_threads, K_length);
		}else if( thread_id == 1 ){
			nvdimm_time = nvdimm_calculation( nvdimm_array_length, n, nvdimm_threads, m-nvdimm_array_length, K_length);
		}
	}
	
	//printf("%d,%d,%lf,%lf\n", dram_threads, nvdimm_threads, dram_time[2], nvdimm_time[2] );

	/*
	printf("m: %d, n: %d, threads: %d, K: %d\n", m-nvdimm_array_length, n, dram_threads, K_length);
	printf("DRAM_time:,%lf", dram_time[0]);
	for(i=1; i<K_length; i++){
		printf(",%lf", dram_time[i]);
	}
	printf("\n");
	
	printf("m: %d, n: %d, threads: %d, dram_start: %d, K: %d\n", nvdimm_array_length, n, nvdimm_threads, m-nvdimm_array_length, K_length);
	printf("NVDIMM_time:,%lf", nvdimm_time[0]);
        for(i=1; i<K_length; i++){
                printf(",%lf", nvdimm_time[i]);
        }
        printf("\n");
	*/
	double dram_average=0;
	double nvdimm_average=0;
	for(i=0;i<K_length;i++){
		dram_average += dram_time[i];
		nvdimm_average += nvdimm_time[i];
	}
	dram_average = dram_average/K_length;
	nvdimm_average = nvdimm_average/K_length;

	printf("%d,%d,%d,%d,%d,%lf,%lf\n", m, n, nvdimm_array_length, dram_threads, nvdimm_threads, dram_average, nvdimm_average );

	//printf("End of program\n");
}
