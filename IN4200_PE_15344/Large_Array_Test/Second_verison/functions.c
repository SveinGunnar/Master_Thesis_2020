#include "functions.h"

void calculation( int m, int n, int dram_threads, int nvdimm_threads, int nvdimm_array_length ){
	int k=0;
	int num_threads;
	//int dram_max, nvdimm_max;
	int mMinusOne = m-1;
	int nMinusOne = n-1;
	double inverseEigth = 1/8;

	int nvdimm_part = nvdimm_array_length+1;
	int dram_part = m-nvdimm_array_length+1;
	printf("%d\n", dram_part);

	//Creating 2d DRAM arrays.
	double **A = (double**)malloc(dram_part*sizeof(double*));
	double **B = (double**)malloc(dram_part*sizeof(double*));
	
	//Creating memory pool on NVDIMM.
	static PMEMobjpool *pop;
	const char path[] = "/mnt/pmem0-xfs/pool.obj";
        //PMEMobjpool *pop;
	pop = pmemobj_open(path, LAYOUT_NAME);
        if (pop == NULL) {
                perror(path);
                //return 1;
	}
	//Creating NVDIMM arrays.
	TOID(double) C;
	TOID(double) D;
	POBJ_ALLOC(pop, &C, double, sizeof(double)*nvdimm_part*n, NULL, NULL);
	POBJ_ALLOC(pop, &D, double, sizeof(double)*nvdimm_part*n, NULL, NULL);

	printf("Before parallel region\n");
	
	#pragma omp parallel
	{
		int thread_id = omp_get_thread_num();
		int slice_start, slice_end;
		int i,j;
		double temp;
		
		//Add values to 2d array elements.
		#pragma omp for
		for(i=0;i<dram_part-1;i++){
			A[i] = (double*)malloc(n*sizeof(double));
			B[i] = (double*)malloc(n*sizeof(double));
			for(j=0;j<n;j++){
				A[i][j] = i+j;
				B[i][j] = 0;
			}
		}
		//Add values to nvdimm array.
		#pragma omp for
		for(i=1;i<nvdimm_part;i++){
			for(j=0;j<n;j++){
				D_RW(C)[i*n+j] = i+j;
				D_RW(D)[i*n+j] = 0;
			}
		}
		//Makes ghost array.
		#pragma omp for
		for(i=0;i<n;i++){
			A[dram_part-1][i] = D_RO(C)[n+i];
			D_RW(C)[i] = A[m-2][i];
		}

		//Creates slices for dram and nvdimm.
		if( thread_id < dram_threads ){
			slice_start = thread_id*(dram_part/dram_threads);
			slice_end = (thread_id+1)*(dram_part/dram_threads);
			if(thread_id==0)
				slice_start++;
		}else{
			slice_start = (thread_id-dram_threads)*(nvdimm_part/nvdimm_threads);
			slice_end = (thread_id-dram_threads+1)*(nvdimm_part/nvdimm_threads);
			if(thread_id==(dram_threads+nvdimm_threads-1))
				slice_end--;
		}
		printf("Thread id: %d, slice start: %d, slice end: %d\n", thread_id, slice_start, slice_end);
		#pragma omp barrier
		#pragma omp single
		{
			printf("Before calculation.\n");
		}
		
		while(k<10){
			#pragma omp barrier
			#pragma omp singel
			{
				k++;
			}
			if( thread_id < dram_threads ){
				for( i=slice_start; i<slice_end; i++){
					for( j=1; j<nMinusOne; j++){
						temp =  A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
							A[i][j-1]        +        A[i][j+1]+
							A[i+1][j-1] + A[i+1][j] + A[i+1][j+1];
						B[i][j] = temp*inverseEigth;
					}
				}
			}else{	
				/*
				for( i=slice_start; i<slice_end; i++){
					for( j=1; j<nMinusOne; j++){
						temp = D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j]+
							D_RO(C)[(i+1)*n+j]            +            D_RO(C)[(i+1)*n+j]+
							D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j];
						D_RW(D)[i*n+j] = temp*inverseEigth;
					}
				}
				*/
			}
		}
//		printf("%d\n", thread_id);
	}//End of parallel
//	printf("After parallel\n");
	POBJ_FREE(&C);
	POBJ_FREE(&D);
}//End of method
//pmempool create --layout my_layout --size=10G obj pool.obj
//End of file.
