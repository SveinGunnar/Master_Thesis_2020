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
#include <omp.h>

//#include <stdio.h>

//void transfer(float *a, float *b, int n);
double mysecond();
void tid();
//long mysecond();

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
//                   100000000
//#define ARRAY_LENGTH 100000000
#define ARRAY_LENGTH 1
# define MIN(x,y) ((x)<(y)?(x):(y))
# define MAX(x,y) ((x)>(y)?(x):(y))
double a[1000000],b[1000000];
int array_length[9] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000};

int main(int argc, char *argv[])
{	
        const char path[] = "/mnt/pmem0/sveingf/pmem_objects";
	//const char path[] = "/mnt/pmem1/sveingf/pmem_objects";
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

        int i,j,k;
	double bytes = 2 * sizeof(double) * ARRAY_LENGTH;

	double *drm_read_array1 = (double*)malloc(ARRAY_LENGTH*sizeof(double));
        double *drm_read_array2 = (double*)malloc(ARRAY_LENGTH*sizeof(double));
        double *drm_write_array1 = (double*)malloc(ARRAY_LENGTH*sizeof(double));
	double *drm_write_array2 = (double*)malloc(ARRAY_LENGTH*sizeof(double));

	TOID(double) nvm_read_array1;
	TOID(double) nvm_read_array2;
	TOID(double) nvm_write_array1;
	TOID(double) nvm_write_array2;
	POBJ_ALLOC(pop, &nvm_read_array1, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	POBJ_ALLOC(pop, &nvm_read_array2, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	POBJ_ALLOC(pop, &nvm_write_array1, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	POBJ_ALLOC(pop, &nvm_write_array2, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	
        //Adding random numbers to two arrays.
	double a=5.40, b=9.79, c=3.23, d=5.599;
        srand((unsigned int)time(NULL));
        for(i=0;i<ARRAY_LENGTH;i++){
                //b = ((float)rand()/(float)(RAND_MAX)) * a;
                drm_read_array1[i] = ((double)rand()/(double)(RAND_MAX)) * a;
                drm_read_array2[i] = ((double)rand()/(double)(RAND_MAX)) * b;
                D_RW(nvm_read_array1)[i] = ((double)rand()/(double)(RAND_MAX)) * c;
		D_RW(nvm_read_array2)[i] = ((double)rand()/(double)(RAND_MAX)) * d;
                //printf("%lf\n", nvm_float_array[i] );
        }

	double** test_time = (double**)malloc(4*sizeof(double*));
	for(i=0;i<4;i++){
		test_time[i] = (double*)malloc(10*sizeof(double));
	}
	
	#pragma omp parallel num_threads(1)
        {
		double temp;
		struct timespec start, end;
		long second, ns;
		for(i=0;i<10;i++){
			//From DRAM to DRAM:
			//Time start
			timespec_get(&start, TIME_UTC);
			//clock_gettime(CLOCK_REALTIME, &start);
			//test_time[0][i] = mysecond();
			for(j=0;j<ARRAY_LENGTH;j++){
				drm_write_array1[j] = drm_read_array1[j];
			}
			//Time stop.
			timespec_get(&end, TIME_UTC);
			//clock_gettime(CLOCK_REALTIME, &end);
			//temp = mysecond();
			second = end.tv_sec - start.tv_sec; 
			ns = end.tv_nsec - start.tv_nsec; 

			if (start.tv_nsec > end.tv_nsec) { // clock underflow 
				--second; 
				ns += 1000000000; 
			}
			//tid(&start);
			//printf(" ");
			//tid(&end);
			//printf("\n");
			//test_time[0][i] = temp - test_time[0][i];
			test_time[0][i] = (double)second + (double)ns/(double)1000000000;
			///////////////////////////////////////////////////////////////////////////////////


			//From DRAM to NVM:
			//Time start
			timespec_get(&start, TIME_UTC);
			for(j=0;j<ARRAY_LENGTH;j++){
				D_RW(nvm_write_array1)[j] = drm_read_array2[j];
			}
			//Time stop.
			timespec_get(&end, TIME_UTC);
			second = end.tv_sec - start.tv_sec;
			ns = end.tv_nsec - start.tv_nsec;
			if (start.tv_nsec > end.tv_nsec) { // clock underflow
				--second;
				ns += 1000000000;
			}
			test_time[1][i] = (double)second + (double)ns/(double)1000000000;

			///////////////////////////////////////////////////////////////////////////////////

			//From NVM to DRAM:
			//Time start
			timespec_get(&start, TIME_UTC);
			for(j=0;j<ARRAY_LENGTH;j++){
				drm_write_array2[j] = D_RO(nvm_read_array1)[j];
			}
			//Time stop.
			timespec_get(&end, TIME_UTC);
			second = end.tv_sec - start.tv_sec;
			ns = end.tv_nsec - start.tv_nsec;
			if (start.tv_nsec > end.tv_nsec) { // clock underflow
				--second;
				ns += 1000000000;
			}
			test_time[2][i] = (double)second + (double)ns/(double)1000000000;

			///////////////////////////////////////////////////////////////////////////////////


			//From NVM to NVM:
			//Time start
			timespec_get(&start, TIME_UTC);
			for(j=0;j<ARRAY_LENGTH;j++){
				D_RW(nvm_write_array2)[j] = D_RO(nvm_read_array2)[j];
			}
			//Time stop.
			timespec_get(&end, TIME_UTC);
			second = end.tv_sec - start.tv_sec;
			ns = end.tv_nsec - start.tv_nsec;
			if (start.tv_nsec > end.tv_nsec) { // clock underflow
				--second;
				ns += 1000000000;
			}
			test_time[3][i] = (double)second + (double)ns/(double)1000000000;

			////////////////////////////////////////////////////////////////////////////////////
		}
	}
	
	//Finds the fastest time.
	double min_test_time[4] = {FLT_MAX,FLT_MAX,FLT_MAX,FLT_MAX};
	for(i=0;i<4;i++){
		for(j=0;j<10;j++){
			min_test_time[i] = MIN(min_test_time[i], test_time[i][j]);
		}
	}
	
	//Print out
	for(i=0;i<4;i++){
		if(i==0) printf("From DRAM to DRAM\n");
		else if(i==1) printf("From DRAM to NVM\n");
		else if(i==2) printf("From NVM to DRAM\n");
		else if(i==3) printf("From NVM to NVM\n");
		printf("Time: %e\n", min_test_time[i]);
                printf("MB/S: %0.2f\n", 1.0E-06 * bytes/min_test_time[i]);
		//printf("MB/S: %f\n", bytes/min_test_time[i]);
	}

        free(drm_read_array1);
        free(drm_read_array2);
        free(drm_write_array1);
	free(drm_write_array2);
	free(test_time);

	POBJ_FREE(&nvm_read_array1);
        POBJ_FREE(&nvm_read_array2);
	POBJ_FREE(&nvm_write_array1);
	POBJ_FREE(&nvm_write_array2);
	
        printf("Ended successfully\n");
	pmemobj_close(pop);
	return 0;
}

/*
double mysecond(){
	struct timeval tp;
	struct timezone tzp;
	int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
*/

double mysecond(){
        int i;
	struct timespec ts;

	clock_gettime(CLOCK_REALTIME, &ts);
	
        return ( (double) ts.tv_sec + (double) ts.tv_nsec * 1.e-9 );
}


void tid(struct timespec ts){
	//struct timespec ts;
    	//timespec_get(&ts, TIME_UTC);
    	char buff[100];
    	strftime(buff, sizeof buff, "%D %T", gmtime(&ts.tv_sec));
    	printf("Current time: %s.%09ld UTC\n", buff, ts.tv_nsec);
}

void random_dram(double* ptr, int size){
	int i;
	srand((unsigned int)time(NULL));
	for(i=0;i<size;i++){
		ptr[i]=((double)rand()/(double)(RAND_MAX));
	}
}

void random_nvm(void* ptr, int size){
	int i;
	srand((unsigned int)time(NULL));
	for(i=0;i<size;i++){
		//D_RW(ptr)[i] = ((double)rand()/(double)(RAND_MAX));
	}
}

void cache_clearing(){
	int i;
	srand((unsigned int)time(NULL));
	for(i=0;i<1000000;i++)
		b[i]=((double)rand()/(double)(RAND_MAX));
	for(i=0;i<1000000;i++)
		a[i]=b[i];
}

/*
void transfer(float *a, float *b, int n){
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
        printf("Time: %lf\n", accum);
        printf("GB/S: %0.2f\n", (ARRAY_SIZE/accum)/(1024*1024*1024));
        //printf("GB/S: %0.2f\n", (global_GB/accum)/(1024*1024*1024));
}
*/
