//#include <memkind.h>
#include <libvmmalloc.h>
#include <stdio.h>
#include <time.h>

#include "functions.h"

#define BILLION 1E9

export VMMALLOC_POOL_SIZE=$((16*1024*1024))
export VMMALLOC_POOL_DIR="/pmem-fs"

int main(){
        //100MB in floats
        int ff = 1638400;
        int i,j;
        int array_length = ff*100;
        double accum;
        float a = 5.0, b=0;
        struct timespec start, stop;

        float *drm_float_array = (float*)malloc(array_length*sizeof(float));
        float *drm_float_array2 = (float*)malloc(array_length*sizeof(float));
        float *drm_float_array3 = (float*)malloc(array_length*sizeof(float));

        float *nvm_float_array = (float*)malloc(array_length*sizeof(float));
        float *nvm_float_array2 = (float*)malloc(array_length*sizeof(float));
        float *nvm_float_array3 = (float*)malloc(array_length*sizeof(float));

        //Adding random numbers to two arrays.
        for(i=0;i<array_length;i++){
                b = (float)rand()/(float)(RAND_MAX/a);
                drm_float_array[i] = b;
                nvm_float_array[i] = b;
	}

        //From DRAM to DRAM:
        printf("From DRAM to DRAM\n");
        transfer(drm_float_array, drm_float_array2, array_length);

        //From DRAM to NVM:
        printf("From DRAM to NVM\n");
        transfer(drm_float_array, nvm_float_array3, array_length);

        //From NVM to DRAM:
        printf("From NVM to DRAM\n");
        transfer(nvm_float_array, drm_float_array3, array_length);

        //From NVM to NVM:
        printf("From NVM to NVM\n");
	transfer(nvm_float_array, nvm_float_array2, array_length);

        free(drm_float_array);
        free(drm_float_array2);
        free(drm_float_array3);

        free(nvm_float_array);
        free(nvm_float_array2);
        free(nvm_float_array3);
        
	printf("Ended successfully\n");
        return 0;
}

