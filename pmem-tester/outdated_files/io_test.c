#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BILLION 1E9
#define ARRAY_SIZE (1073741824)// 1GB * a_number

int main() {
	int array_length = ARRAY_SIZE/64;
	float *drm_float_array = (float*)malloc(array_length*sizeof(float));
	int b, i;
	int a = 5;
        srand((unsigned int)time(NULL));
        for(i=0;i<array_length;i++){
                b = ((float)rand()/(float)(RAND_MAX)) * a;
                //b =5.9987;
                drm_float_array[i] = ((float)rand()/(float)(RAND_MAX)) * a;
                //D_RW(nvm_float_array)[i] = ((float)rand()/(float)(RAND_MAX)) * a;
                //printf("%lf\n", nvm_float_array[i] );
        }


        double accum;
        struct timespec start, stop;

        //Time start
        if( clock_gettime( CLOCK_REALTIME, &start) == -1 ) {
                perror( "clock gettime" );
                exit( EXIT_FAILURE );
        }

	FILE *fp;
	fp = fopen("/mnt/pmem1/sveingf/testing.txt", "w+");

	fread(drm_float_array, sizeof(float), array_length, fp);

        //fwrite(drm_float_array, sizeof(float), array_length, fp);

        fclose(fp);

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

	for(i=0;i<array_length;i++){
                b = ((float)rand()/(float)(RAND_MAX)) * a;
                //b =5.9987;
                drm_float_array[i] = ((float)rand()/(float)(RAND_MAX));
                //D_RW(nvm_float_array)[i] = ((float)rand()/(float)(RAND_MAX)) * a;
                //printf("%lf\n", nvm_float_array[i] );
        }


	return 0;


}
