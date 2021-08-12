#include "functions.h"

//Creates DRAM arrays.
double** create_DRAM_Array( int m, int n ){
	int i,j;
	double **array = (double**)malloc(m*sizeof(double*));
	//#pragma omp parallel for
	for(i=0;i<m;i++){
                array[i] = (double*)malloc(n*sizeof(double));
                for(j=0;j<n;j++){
                        array[i][j] = ((double)rand()/(double)(RAND_MAX));
                }
        }
	return array;
}
//POBJ_ALLOC(pop, &nvm_write_array, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
//

void calculation( int m, int n, int dram_threads, int nvdimm_threads, int nvdimm_array_length, int K_length ){
//	printf("m: %d, n: %d, dram_threads: %d, nvdimm_threads: %d, nvdimm_array_length %d, K_length: %d\n", m,n,dram_threads,nvdimm_threads,nvdimm_array_length,K_length);
	int k=0;
	int num_threads = dram_threads+nvdimm_threads;
	//int dram_max, nvdimm_max;
	int mMinusOne = m-1;
	int nMinusOne = n-1;
	double inverseEigth = 1/8;
	int dram_part = m-nvdimm_array_length;
	double *nvdimm_time = (double*)malloc(K_length*sizeof(double));
	double *individual_time = (double*)malloc((dram_threads+nvdimm_threads)*sizeof(double));
	double *dram_time = (double*)malloc(K_length*sizeof(double));

//	printf("Before Array creation\n");

	//Creating DRAM arrays.
	double **A = create_DRAM_Array(dram_part,n);
	double **B = create_DRAM_Array(dram_part,n);

	#pragma omp parallel num_threads(num_threads) 
	{
		int thread_id = omp_get_thread_num();
		int slice_start, slice_end;
		int i,j;
		double temp;

		//Add values to nvdimm 2d array
		#pragma omp for
		for(i=0;i<nvdimm_array_length;i++){
			for(j=0;j<n;j++){
			//	printf("T: %d, i: %d, j: %d, i*n+j: %d\n", thread_id, i, j, i*n+j);
				D_RW(C)[i*nvdimm_array_length+j] = i+j;
				D_RW(D)[i*nvdimm_array_length+j] = 0;
			}
		}
		//Add values to dram 2d array
		#pragma omp for
                for(i=0;i<m-nvdimm_array_length;i++){
                        for(j=0;j<n;j++){
                        //      printf("T: %d, i: %d, j: %d, i*n+j: %d\n", thread_id, i, j, i*n+j);
				A[i][j] = i+j;
                                B[i][j] = 0;
                        }
                }

		//Creates slices for dram and nvdimm.
		if( thread_id < dram_threads ){
			slice_start = thread_id*(dram_part/dram_threads);
			slice_end = (thread_id+1)*(dram_part/dram_threads);
			if(thread_id==0)
				slice_start++;
		}else{
			slice_start = (thread_id-dram_threads)*(nvdimm_array_length/nvdimm_threads);
			slice_end = (thread_id-dram_threads+1)*(nvdimm_array_length/nvdimm_threads);
			if(thread_id==(dram_threads+nvdimm_threads-1))
				slice_end--;
		}
//		printf("thread id: %d, slice start: %d, slice end: %d\n", thread_id, slice_start, slice_end);
		#pragma omp single
		{
			//printf("Before calculation.\n");
		}
		while(k<K_length){
			#pragma omp barrier
			#pragma omp single
			{
//				printf("k: %d\n", k);
				//k++;
			}
			#pragma omp barrier
			//printf("%d\n", thread_id);
			individual_time[thread_id] = mysecond();
                        for( i=slice_start; i<slice_end; i++){
                        	for( j=1; j<nMinusOne; j++){
                                	temp = A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
                                	A[i][j-1]        +        A[i][j+1]+
                                        A[i+1][j-1] + A[i+1][j] + A[i+1][j+1];
                                        B[i][j] = temp*inverseEigth;
                                }
                        }
			individual_time[thread_id] = mysecond() - individual_time[thread_id];
			#pragma omp barrier
			#pragma omp single
			{
				dram_time[k]=individual_time[0];
				for(i=1;i<dram_threads;i++){
					if(dram_time[k]<individual_time[i])
						dram_time[k]=individual_time[i];
				}
				nvdimm_time[k]=individual_time[dram_threads];
				for(i=dram_threads+1;i<dram_threads+nvdimm_threads;i++){
                                        if(nvdimm_time[k]<individual_time[i])
                                                nvdimm_time[k]=individual_time[i];
                                }
				k++;
			}
			#pragma omp barrier
		}
//		printf("End of thread id: %d\n", thread_id);
	}//End of parallel
	POBJ_FREE(&C);
	POBJ_FREE(&D);
	int i;
	double dram_average=0;
        double nvdimm_average=0;
        for(i=0;i<K_length;i++){
                dram_average += dram_time[i];
                nvdimm_average += nvdimm_time[i];
        }
        dram_average = dram_average/K_length;
        nvdimm_average = nvdimm_average/K_length;
	printf("%d,%d,%d,%d,%d,%lf,%lf\n", m, n, nvdimm_array_length, dram_threads, nvdimm_threads, dram_average, nvdimm_average );
}//End of method
//pmempool create --layout my_layout --size=10G obj pool.obj
double mysecond(){ //fpo 2
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}

//End of file.
