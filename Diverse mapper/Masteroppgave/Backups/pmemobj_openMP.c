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
#define POOL_SIZE ((size_t)(1 << 30))

/* name of our layout in the pool */
#define LAYOUT_NAME "example_layout"

#define BILLION 1E9
//#define ARRAY_SIZE (1073741824)// 1GB * a_number
#define ARRAY_LENGTH 100000000
#define THREADS 4
//#define ARRAY_LENGTH 1000
# define MIN(x,y) ((x)<(y)?(x):(y))
# define MAX(x,y) ((x)>(y)?(x):(y))
double a[1000000],b[1000000];
int array_length[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

int main(int argc, char *argv[])
{
        const char path[] = "/mnt/pmem0/sveingf/pmem_objects";
        PMEMobjpool *pop;

        /* create the pmemobj pool or open it if it already exists */
        //pop = pmemobj_create(path, LAYOUT_NAME, POOL_SIZE, 0666);
	pop = pmemobj_create(path, LAYOUT_NAME, 10737418240, 0666);

        if (pop == NULL)
            pop = pmemobj_open(path, LAYOUT_NAME);

        if (pop == NULL) {
                perror(path);
                exit(1);
        }

        /* ... */
	//Her er testkoden
	double a=5.034, b=4.667;
        int i,j;
	double bytes = 2 * sizeof(double) * ARRAY_LENGTH;
	
	double **drm_read_array = (double**)malloc(*sizeof(double));
	double **drm_write_array = (double**)malloc(ARRAY_LENGTH*sizeof(double));

	
	TOID(double) nvm_read_array;
	TOID(double) nvm_write_array;
	POBJ_ALLOC(pop, &nvm_read_array, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	POBJ_ALLOC(pop, &nvm_write_array, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);	
	
        //Adding random numbers to two arrays.
        srand((unsigned int)time(NULL));
        for(i=0;i<ARRAY_LENGTH;i++){
		drm_read_array[i] = ((double)rand()/(double)(RAND_MAX)) * a;
		D_RW(nvm_read_array)[i] = ((double)rand()/(double)(RAND_MAX)) * b;
        }

	double** test_time = (double**)malloc(2*sizeof(double*));
        for(i=0;i<2;i++){
                test_time[i] = (double*)malloc(10*sizeof(double));
        }
	i=0;
	#pragma omp parallel num_threads(2)
	{
		int k;
                //char z0[50] = "From DRAM to DRAM:";
		//char z1[50] = "From NVM to NVM:";
		//double result;
		int thread_id = omp_get_thread_num();

		while(i<10){
			#pragma omp barrier
			if(thread_id == 0){
				//From DRAM to DRAM:
				//Time start
				test_time[0][i] = mysecond();

				for(k=0;k<ARRAY_LENGTH;k++){
					drm_write_array[k] = drm_read_array[k];
				}

				//Time stop.
				test_time[0][i] = mysecond() - test_time[0][i];
				//printf("Time: %lf\n", test_time[0][i]);
				//////////////////////////////////////////////////

			}
			else if(thread_id == 1){
				//From NVM to NVM:
				//Time start
				test_time[1][i] = mysecond2();

				for(k=0;k<ARRAY_LENGTH;k++){
					D_RW(nvm_write_array)[k] = D_RO(nvm_read_array)[k];
				}

				//Time stop.
				test_time[1][i] = mysecond2() - test_time[1][i];
				//printf("Time: %lf\n", test_time[1][i]);
				//////////////////////////////////////////////////
			}
			else
				printf("FEIL\n");
			#pragma omp barrier
                	if(thread_id==0)
				i++;
			#pragma omp barrier
		}

	}

	double min_nvm_time[2] = {FLT_MAX,FLT_MAX};
	double min_drm_time[2] = {FLT_MAX,FLT_MAX};
	
        for(j=0;j<10;j++){
		if(test_time[0][j] < min_drm_time[0]){
			min_drm_time[0] = test_time[0][j];
			min_drm_time[1] = test_time[1][j];
		}
		if(test_time[1][j] < min_nvm_time[1]){
			min_nvm_time[0] = test_time[0][j];
			min_nvm_time[1] = test_time[1][j];
		}
        }

	printf("Best DRAM\n");
	printf("From DRAM to DRAM\n");
	printf("Time: %lf\n", min_drm_time[0]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_drm_time[0]);
	printf("From NVM to NVM\n");
	printf("Time: %lf\n", min_drm_time[1]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_drm_time[1]);

	printf("Best NVM\n");
	printf("From DRAM to DRAM\n");
	printf("Time: %lf\n", min_nvm_time[0]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_nvm_time[0]);
	printf("From NVM to NVM\n");
	printf("Time: %lf\n", min_nvm_time[1]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_nvm_time[1]);




        free(drm_read_array);
        free(drm_write_array);
	POBJ_FREE(&nvm_read_array);
        POBJ_FREE(&nvm_write_array);

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

