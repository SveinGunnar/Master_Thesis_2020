#include "functions.h"

double * nvdimm_calculation( int m, int n, int threads, int K ){
	double inverseEigth = 1/8;
	int nMinusOne=n-1;
	int mMinusOne=m-1;
	double temp;
	int k=0;
	int k_length = K;
        double *time = (double*)malloc(k_length*sizeof(double));

	//Creating memory pool on NVDIMM.
        static PMEMobjpool *pop;
        const char path[] = "/mnt/pmem0-xfs/pool.obj";
        pop = pmemobj_open(path, LAYOUT_NAME);
        if (pop == NULL) {
                perror(path);
        }

	//Creating NVDIMM arrays.
        TOID(double) C;
        TOID(double) D;
        POBJ_ALLOC(pop, &C, double, sizeof(double)*(m+1)*n, NULL, NULL);
        POBJ_ALLOC(pop, &D, double, sizeof(double)*(m+1)*n, NULL, NULL);

	#pragma omp parallel num_threads(threads)
        {
		int i,j;
		int thread_id = omp_get_thread_num();
		#pragma omp for
		for(i=0;i<m;i++){
			for(j=0;j<n;j++){
				D_RW(C)[i*n+j] = i+j;
				D_RW(D)[i*n+j] = 0;
			}
		}
		
		while(k<k_length){
                        #pragma omp barrier
                        #pragma omp single
                        {
				time[k] = mysecond();
                        }
			#pragma omp for
			for( i=1; i<mMinusOne; i++){
				for( j=1; j<nMinusOne; j++){
					temp = D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j]+
						D_RO(C)[(i+1)*n+j]            +            D_RO(C)[(i+1)*n+j]+
						D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j];
					D_RW(D)[i*n+j] = temp*inverseEigth;
				}
			}
			#pragma omp barrier
                        #pragma omp single
                        {
                                time[k] = mysecond() - time[k];
                                k++;
                        }
		}
	}
	//printf("Nvdimm time: %lf\n", time[k_length/2]);
	POBJ_FREE(&C);
	POBJ_FREE(&D);
	return time;
}

//pmempool create --layout my_layout --size=10G obj pool.obj
double mysecond(){ //fpo 2
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
//End of file.
