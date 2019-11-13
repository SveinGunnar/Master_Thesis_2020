#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <libpmemobj.h>
#include <sys/time.h>
#include <float.h>

POBJ_LAYOUT_BEGIN(array);
POBJ_LAYOUT_TOID(array, double);
POBJ_LAYOUT_END(array);

double mysecond();
#define POOL_SIZE ((size_t)(1 << 30)*10)
#define LAYOUT_NAME "example_layout"
#define ARRAY_LENGTH 100000000

int main(int argc, char *argv[])
{
	const char path[] = "/mnt/pmem1/sveingf/pmem_objects";
	//const char path[] = "myobjpool.set";
        PMEMobjpool *pop;
	 /* create the pmemobj pool or open it if it already exists */
	pop = pmemobj_create(path, LAYOUT_NAME, POOL_SIZE, 0666);
        //pop = pmemobj_create(path, LAYOUT_NAME, 0, 0666);
	if (pop == NULL)
            pop = pmemobj_open(path, LAYOUT_NAME);
        if (pop == NULL) {
                perror(path);
                exit(1);
        }

	int i,j,k;

	double bytes = 2 * sizeof(double) * ARRAY_LENGTH;

	double *drm_read_array1 = (double*)malloc(ARRAY_LENGTH*sizeof(double));
	double *drm_write_array1 = (double*)malloc(ARRAY_LENGTH*sizeof(double));
	TOID(double) nvm_read_array1;
	POBJ_ALLOC(pop, &nvm_read_array1, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
	TOID(double) nvm_write_array1;
	POBJ_ALLOC(pop, &nvm_write_array1, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);

	double a=5.40, b=9.79, c=3.23, d=5.599;
        srand((unsigned int)time(NULL));
        for(i=0;i<ARRAY_LENGTH;i++){
                //b = ((float)rand()/(float)(RAND_MAX)) * a;
                drm_read_array1[i] = ((double)rand()/(double)(RAND_MAX)) * a;
                //drm_write_array1[i] = ((double)rand()/(double)(RAND_MAX)) * b;
                D_RW(nvm_read_array1)[i] = ((double)rand()/(double)(RAND_MAX)) * c;
                //D_RW(nvm_write_array1)[i] = ((double)rand()/(double)(RAND_MAX)) * d;
                //printf("%lf\n", nvm_float_array[i] );
        }
	
	double** test_time = (double**)malloc(2*sizeof(double*));
        for(i=0;i<2;i++){
                test_time[i] = (double*)malloc(10*sizeof(double));
        }
	i=0;
	#pragma omp parallel num_threads(2)
        {
		int thread_id = omp_get_thread_num();
		int m;

		while(i<10){
			#pragma omp barrier
			if(thread_id == 0){
				//Time start
				test_time[0][i] = mysecond();
				
				for(m=0;m<ARRAY_LENGTH;m++)
					drm_write_array1[m] = D_RO(nvm_read_array1)[m]; 

				//Time stop.
				test_time[0][i] = mysecond() - test_time[0][i];
			}
			else if(thread_id == 1){
				//Time start
                                test_time[1][i] = mysecond();

				for(m=0;m<ARRAY_LENGTH;m++)
                                        D_RW(nvm_write_array1)[m] = drm_read_array1[m];

                                //Time stop.
                                test_time[1][i] = mysecond() - test_time[1][i];
			}else
				printf("FEIL\n");

			#pragma omp barrier
                	if(thread_id==0)
                        	i++;
                	#pragma omp barrier

		}
	}
	double min_read_time[2] = {FLT_MAX,FLT_MAX};
	double min_write_time[2] = {FLT_MAX,FLT_MAX};
	
        for(j=0;j<10;j++){
		if(test_time[0][j] < min_read_time[0]){
			min_read_time[0] = test_time[0][j];
			min_read_time[1] = test_time[1][j];
		}
		if(test_time[1][j] < min_write_time[1]){
			min_write_time[0] = test_time[0][j];
			min_write_time[1] = test_time[1][j];
		}
        }

	printf("Best read time\n");
        printf("From NVM to DRAM\n");
        printf("Time: %lf\n", min_read_time[0]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_read_time[0]);
        printf("From NVM to DRAM\n");
        printf("Time: %lf\n", min_read_time[1]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_read_time[1]);

        printf("Best write time\n");
        printf("From NVM to DRAM\n");
        printf("Time: %lf\n", min_write_time[0]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_write_time[0]);
        printf("From NVM to DRAM\n");
        printf("Time: %lf\n", min_write_time[1]);
        printf("MB/S: %0.2f\n\n", 1.0E-06 * bytes/min_write_time[1]);

	POBJ_FREE(&nvm_read_array1);
	POBJ_FREE(&nvm_write_array1);	
	
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

