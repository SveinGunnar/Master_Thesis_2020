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

        //if (pop == NULL)
        pop = pmemobj_open(path, LAYOUT_NAME);

        if (pop == NULL) {
                perror(path);
                exit(1);
        }

        /* ... */
	//Her er testkoden
	int nvmThreads = atoi(argv[1]);
	int totalThreads = atoi(argv[2]);
	int nthreads;
	int total_tests = atoi(argv[3]);
	//int valid_tests = 10;
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
                //TOID(double) nvm_write_array;
		srand((unsigned int)time(NULL));
		
		#pragma omp master
		{
			//Creates array where the testresult will be added.
			nthreads = omp_get_num_threads();
			test_time = (double**)malloc(nthreads*sizeof(double*));
			for(i=0;i<nthreads;i++){
                		test_time[i] = (double*)malloc(total_tests*sizeof(double));
        		}
        		for(i=0;i<nthreads;i++)
                		for(j=0;j<total_tests;j++)
                        		test_time[i][j]=0;
		}
		
		//Creates all the arrays needed for the test.
		#pragma omp barrier
		if(thread_id < totalThreads-nvmThreads){
			drm_read_array = (double*)malloc(ARRAY_LENGTH*sizeof(double));
        		drm_write_array = (double*)malloc(ARRAY_LENGTH*sizeof(double));
			#pragma omp critical
			{
				for(i=0;i<ARRAY_LENGTH;i++)
					drm_read_array[i] = ((double)rand()/(double)(RAND_MAX));
					drm_write_array[i] = ((double)rand()/(double)(RAND_MAX));
			}
		}
		else if(thread_id >= totalThreads-nvmThreads){
			drm_write_array = (double*)malloc(ARRAY_LENGTH*sizeof(double));
        		POBJ_ALLOC(pop, &nvm_read_array, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
			#pragma omp critical
			{
				for(i=0;i<ARRAY_LENGTH;i++)
					D_RW(nvm_read_array)[i] = ((double)rand()/(double)(RAND_MAX));
					drm_write_array[i] = ((double)rand()/(double)(RAND_MAX));
			}
		}
		
		//Doing the test.
		#pragma omp barrier
		if(thread_id < totalThreads-nvmThreads){
			//From DRAM to DRAM:
			for(i=0;i<total_tests;i++){
				//Time start
				test_time[thread_id][i] = mysecond();
			
				for(j=0;j<ARRAY_LENGTH;j++){
					drm_write_array[j] = drm_read_array[j];
				}
			
				//Time stop.
				test_time[thread_id][i] = mysecond() - test_time[thread_id][i];
			}
		}
		else if(thread_id >= totalThreads-nvmThreads){
			//From NVM to DRAM:
			for(i=0;i<total_tests;i++){
				//Time start
				test_time[thread_id][i] = mysecond();
				
				for(j=0;j<ARRAY_LENGTH;j++)
					drm_write_array[j] = D_RO(nvm_read_array)[j];		

				//Time stop.
				test_time[thread_id][i] = mysecond() - test_time[thread_id][i];
			}
		}
		else
			printf("FEIL\n");


		/**/
		if(thread_id < totalThreads-nvmThreads){
			free(drm_read_array);
        		free(drm_write_array);
		}
		else if(thread_id >= totalThreads-nvmThreads){
        		POBJ_FREE(&nvm_read_array);
        		//POBJ_FREE(&nvm_write_array);
			free(drm_write_array);
		}

		/**/
		#pragma omp barrier
	}
	int i,j;

	//Average
	// i%2 == 0 -> DRAM
	// i%2 == 1 -> NVM

	for(i=0;i<nthreads;i++){
		if(i < totalThreads-nvmThreads)
			printf("DRAM,");
		else if(i >= totalThreads-nvmThreads)
			printf("NVMe,");
		for(j=0;j<total_tests;j++){
			printf("%0.2f", 1.0E-06 * bytes/test_time[i][j]);
			if( j != total_tests-1 )
				printf(",");
		}
		printf("\n");
	}

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


