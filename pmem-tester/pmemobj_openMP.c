#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#ifndef _WIN32
#include <unistd.h>
#endif
#include <stdint.h>
#include <string.h>
#include <libpmemobj.h>
#include <omp.h>
#include <limits.h>
#include <float.h>
#include <sys/time.h>


//void transfer(float *a, float *b, int n);
double mysecond();
double mysecond2();

//TESTING
#define TOID_ARRAY(x) TOID(x)
#define COUNT_OF(x) (sizeof(x) / sizeof(x[0]))
#define MAX_BUFFLEN 30
#define MAX_TYPE_NUM 8

POBJ_LAYOUT_BEGIN(array);
POBJ_LAYOUT_TOID(array, double);
POBJ_LAYOUT_END(array);

/* size of the pmemobj pool -- 1 GB */
#define POOL_SIZE ((size_t)(1UL << 33))

/* name of our layout in the pool */
#define LAYOUT_NAME "my_layout"

#define BILLION 1E9
//#define ARRAY_SIZE (1073741824)// 1GB * a_number
//                   100000000
#define ARRAY_LENGTH 100000000
//#define ARRAY_LENGTH 1000
# define MIN(x,y) ((x)<(y)?(x):(y))
# define MAX(x,y) ((x)>(y)?(x):(y))

int main(int argc, char *argv[])
{
	//printf("%lu\n", sizeof(double));
        //const char path[] = "/mnt/pmem0/sveingf/pmem_objects";
	const char path[] = "/mnt/pmem0-xfs/pool.obj";
        PMEMobjpool *pop;
        /* create the pmemobj pool or open it if it already exists */
        //pop = pmemobj_create(path, LAYOUT_NAME, POOL_SIZE, 0666);
	//pop = pmemobj_create(path, LAYOUT_NAME, xxx, 0666);
	//pop = pmemobj_create(path, LAYOUT_NAME, 10737418240, 0666);

        if (pop == NULL)
            pop = pmemobj_open(path, LAYOUT_NAME);

        if (pop == NULL) {
                perror(path);
                exit(1);
        }

        /* ... */
	//Her er testkoden
	int number_of_tests = 50;
	int valid_tests = 10;
	int nthreads;
	double scalar = 3.0;
	double bytes = 2 * sizeof(double) * ARRAY_LENGTH;	
	double** test_time;
	int x=0;
	//double aTest = mysecond();
	#pragma omp parallel
	{
		int thread_id = omp_get_thread_num();
		int i,j;
		double *drm_read_array;
		double *drm_write_array;
		TOID(double) nvm_read_array;
                TOID(double) nvm_write_array;
		srand((unsigned int)time(NULL));
		
		#pragma omp master
		{
			nthreads = omp_get_num_threads();
			test_time = (double**)malloc(nthreads*sizeof(double*));
			for(i=0;i<nthreads;i++){
                		test_time[i] = (double*)malloc(number_of_tests*sizeof(double));
        		}
        		for(i=0;i<nthreads;i++)
                		for(j=0;j<number_of_tests;j++)
                        		test_time[i][j]=0;
		}
		
		#pragma omp barrier
		printf("%d\n", thread_id);
		if(thread_id%2 == 0){
			drm_read_array = (double*)malloc(ARRAY_LENGTH*sizeof(double));
        		drm_write_array = (double*)malloc(ARRAY_LENGTH*sizeof(double));
			#pragma omp critical
			{
				for(i=0;i<ARRAY_LENGTH;i++)
					drm_read_array[i] = ((double)rand()/(double)(RAND_MAX));
                       		printf("thread_id: %d, %f\n", thread_id, drm_read_array[11235]);
			}
		}
		else if(thread_id%2 == 1){
        		POBJ_ALLOC(pop, &nvm_read_array, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
        		POBJ_ALLOC(pop, &nvm_write_array, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
			#pragma omp critical
			{
				for(i=0;i<ARRAY_LENGTH;i++)
					D_RW(nvm_read_array)[i] = ((double)rand()/(double)(RAND_MAX));
                        	printf("thread_id: %d, %f\n", thread_id, D_RO(nvm_read_array)[11235]);
			}
		}
		
		#pragma omp barrier
		if(thread_id%2 == 0){
			//From DRAM to DRAM:
			for(i=0;i<number_of_tests;i++){
				//Time start
				test_time[thread_id][i] = mysecond();

				for(j=0;j<ARRAY_LENGTH;j++)
					drm_write_array[j] = drm_read_array[j];

				//Time stop.
				test_time[thread_id][i] = mysecond() - test_time[thread_id][i];
			}
		}
		else if(thread_id%2 == 1){
			//From NVM to NVM:
			for(i=0;i<number_of_tests;i++){
				//Time start
				test_time[thread_id][i] = mysecond();
				
				for(j=0;j<ARRAY_LENGTH;j++)
					D_RW(nvm_write_array)[j] = D_RO(nvm_read_array)[j];

				//Time stop.
				test_time[thread_id][i] = mysecond() - test_time[thread_id][i];
			}
		}
		else
			printf("FEIL\n");
		
		/**/
		if(thread_id%2 == 0){
			free(drm_read_array);
        		free(drm_write_array);
		}
		else if(thread_id%2 == 1){
        		POBJ_FREE(&nvm_read_array);
        		POBJ_FREE(&nvm_write_array);
		}
		/**/
		#pragma omp barrier
	}
	printf("END of parallel\n\n");
	int i,j;

	//Average
	// i%2 == 0 -> DRAM
	// i%2 == 1 -> NVM
	double *average = (double*)malloc(nthreads*sizeof(double));
        for(i=0;i<nthreads;i++)
                average[i] = 0;
	
	for(i=0;i<nthreads;i++){
		for(j=2;j<valid_tests+2;j++){
			average[i] += test_time[i][j];
		}
		average[i] = average[i]/valid_tests;
	}
	
	int fastest_dram = 0;
	int fastest_nvm = 1;
	for(i=2;i<nthreads;i++){
		if( i%2 == 0 )
			if( average[i] < average[fastest_dram] )
				fastest_dram = i;
		else if( i%2 == 1 )
			if( average[i] < average[fastest_nvm] )
                        	fastest_nvm = i;
        }
	
        printf("From DRAM to DRAM\n");
        printf("Time: %lf\n", average[fastest_dram]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/average[fastest_dram]);
        printf("From NVM to NVM\n");
        printf("Time: %lf\n", average[fastest_nvm]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/average[fastest_nvm]);
	
//	printf("fastest_dram: %d, fastest_nvm: %d\n", fastest_dram, fastest_nvm);
//	for(i=1;i<valid_tests;i++){
//		printf("Interval %d: DRAM: %f, NVM: %f\n", i, average[i], average[i]);
//	}

	printf("Full printout\n");
        for(i=0;i<nthreads;i++){
                printf("%d:\t", i);
                for(j=1;j<valid_tests;j++)
                        printf("%0.2f, ", 1.0E-06 * bytes/test_time[i][j]);
                printf("\n");
        }

        printf("Ended successfully\n");
	pmemobj_close(pop);
	return 0;
}

double mysecond(){
	struct timeval tp;
	struct timezone tzp;
	int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

double mysecond2(){
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}


