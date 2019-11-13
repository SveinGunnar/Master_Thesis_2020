
#include <memkind.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <omp.h>
#include <string.h>

double transfer(float *a, float *b, int);
//#include "functions.h"

#define BILLION 1E9
//#define PMEM_MAX_SIZE (8 * 1024 * 1024 * 500)  // 1 Gigabyte
//#define PMEM_MAX_SIZE (1024 * 1024 * 32)
#define PMEM_MAX_SIZE (1073741824*5)// 1GB * a_number
#define ARRAY_SIZE (1073741824)// 1GB * a_number
float global_GB;

static char path[100]="/mnt/pmem1/sveingf/";
//static char path[100]="testing/";


int main(){
	/*
	//100MB in floats
	int ff = 1638400;
	int gb = 16777216;
	int hundre_mb = 8*1024*1024*100;
	int ti_mb = 1024*1024*10;
	int i,j;
	int array_length = ti_mb/64;
	double accum;
	float a = 5.0, b=0;
	struct timespec start, stop;

	struct memkind *pmem_kind = NULL;
	int err = 0;
	*/
	
	int a=5.0, b=0;
	int i,j;
	int GB = 1073741824; // 1GB
	int total_GB = GB*4; // GB*a_number
	int array_length = ARRAY_SIZE/64;
	//float array_length = total_GB/64;
	global_GB = total_GB;

	
	/*
	// Create PMEM partition with specific size
    	err = memkind_create_pmem(path, PMEM_MAX_SIZE, &pmem_kind);
	printf("her: %d\n", err);
	if (err) {
        	//print_err_message(err);
		printf("Error in line 29!\n");
        	return 1;
	}
	*/
	
	float *drm_float_array = (float*)malloc(array_length*sizeof(float));
	float *drm_float_array2 = (float*)malloc(array_length*sizeof(float));
	float *drm_float_array3 = (float*)malloc(array_length*sizeof(float));

	float *nvm_float_array = (float*)memkind_malloc(MEMKIND_DEFAULT, array_length*sizeof(float));
	float *nvm_float_array2 = (float*)memkind_malloc(MEMKIND_DEFAULT, array_length*sizeof(float));
	float *nvm_float_array3 = (float*)memkind_malloc(MEMKIND_DEFAULT, array_length*sizeof(float));
	
	//printf("%d\n", array_length );

	b=55,6548;
	//Adding random numbers to two arrays.
	for(i=0;i<array_length;i++){
		b = (float)rand()/(float)(RAND_MAX/a);
		//b =5.9987;
		drm_float_array[i] = b;
		nvm_float_array[i] = b;
		//printf("%lf\n", nvm_float_array[i] );
	}
	
	#pragma omp parallel num_threads(2)
	{	
		int k;
		double accum;
		struct timespec start, stop;
		char z[50];
		double result;

		int thread_id = omp_get_thread_num();
		if( thread_id == 0){
			//From DRAM to DRAM:
			strcpy(z, "From DRAM to DRAM:\n");
			//z = "From DRAM to DRAM:\n";
			printf("From DRAM to DRAM\n");
			result = transfer(drm_float_array, drm_float_array2, array_length);
		} else {
			//From NVM to NVM:
			strcpy(z, "From NVM to NVM:\n");
			//z = "From NVM to NVM:\n"
			printf("From NVM to NVM\n");
			result = transfer(nvm_float_array, nvm_float_array2, array_length);
		}

		#pragma omp critial
		{
			printf("%s", z);
			printf("Time: %lf\n", result);
        		printf("GB/S: %0.2f\n", (ARRAY_SIZE/result)/(1024*1024*1024));
        		printf("GB/S: %0.2f\n", (global_GB/result)/(1024*1024*1024));
		}

	}
	//printf("%lf\n", nvm_float_array[45]);
	//printf("%lf\n", drm_float_array[463]);
	
	free(drm_float_array);
	free(drm_float_array2);
	free(drm_float_array3);
	memkind_free(MEMKIND_DEFAULT, nvm_float_array);
	memkind_free(MEMKIND_DEFAULT, nvm_float_array2);
	memkind_free(MEMKIND_DEFAULT, nvm_float_array3);
	printf("Ended successfully\n");
	return 0;
	
}


double transfer(float *a, float *b, int n){
	
	int i;
        double accum;
        struct timespec start, stop;

	//Time start
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
	
	return accum;	
        //printf("Time: %lf\n", accum);
	//printf("GB/S: %0.2f\n", (ARRAY_SIZE/accum)/(1024*1024*1024));
	//printf("GB/S: %0.2f\n", (global_GB/accum)/(1024*1024*1024));
	
}
