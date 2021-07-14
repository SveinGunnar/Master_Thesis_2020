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
//Creates NVDIMM arrays.
void** create_NVDIMM_Array( int m, int n ){
/*	int i,j;
        //double **array = (double**)malloc(m*sizeof(double*));
	//void *array;// = malloc(sizeof(void *)*m);
	TOID(double) array;
	POBJ_ALLOC(pop, &array, double, sizeof(double)*m*n, NULL, NULL);
//	printf("NVDIMM\n");
	//#pragma omp parallel for
        for(i=0;i<m;i++){
		//TOID(double) array[i];
		//POBJ_ALLOC(pop, array[i], double, sizeof(double)*n, NULL, NULL);
		//printf("NVDIMM for\n");
                for(j=0;j<n;j++){
			D_RW(array)[i*m+n] = ((double)rand()/(double)(RAND_MAX));
                }
        }
	return array;
*/
}
//POBJ_ALLOC(pop, &nvm_write_array, double, sizeof(double) * ARRAY_LENGTH, NULL, NULL);
//
void calculation( int m, int n, int dram_threads, int nvdimm_threads, int NVDIMM_size ){
//	int k=0;
	int num_threads;
	//int dram_max, nvdimm_max;
	int mMinusOne = m-1;
	int nMinusOne = n-1;
	double inverseEigth = 1/8;

	int nvdimm_part = NVDIMM_size;
	int dram_part = m-nvdimm_part;

	printf("Before Array creation\n");

	//Creating DRAM arrays.
	double **A = create_DRAM_Array(dram_part,n);
	printf("Before Array creation\n");
	double **B = create_DRAM_Array(dram_part,n);
	//Creating NVDIMM arrays.
//	void **C = create_NVDIMM_Array(nvdimm_part,n);
//	void **D = create_NVDIMM_Array(nvdimm_part,n);
//	TOID(double) C;
//	TOID(double) D;
	printf("Before Array creation3\n");
//	POBJ_ALLOC(pop, &C, double, sizeof(double)*nvdimm_part*n, NULL, NULL);
//	POBJ_ALLOC(pop, &D, double, sizeof(double)*nvdimm_part*n, NULL, NULL);
	printf("After Array creation\n");
	int a,b;
	for(a=0;a<nvdimm_part;a++){
                for(b=0;b<n;b++){
                        //D_RW(C)[nvdimm_part*a+b] = ((double)rand()/(double)(RAND_MAX));
			//D_RW(D)[nvdimm_part*a+b] = ((double)rand()/(double)(RAND_MAX));
                }
        }
	
	printf("Before parallel region\n");

	#pragma omp parallel
	{
		int k;
		int thread_id = omp_get_thread_num();
		int slice_start, slice_end;
		int i,j;
		double temp;
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
		#pragma omp single
		{
			printf("Before calculation.\n");
		}
		
		if( thread_id < dram_threads ){
			//for the thread bordering on nvdimm thread.
			if( thread_id==(dram_threads-1) ){
				while(k<10){
					k++;
					for( i=slice_start; i<slice_end-1; i++){
						for( j=1; j<nMinusOne; j++){
							temp = A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
								 A[i][j-1]        +        A[i][j+1]+
							       A[i+1][j-1] + A[i+1][j] + A[i+1][j+1];
							B[i][j] = temp*inverseEigth;
						}
					}
					
					i = slice_end-1;
					for( j=1; j<nMinusOne; j++){
                                        	temp = A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
                                	                 A[i][j-1]        +        A[i][j+1]+
						      D_RO(C)[i*n+j] + D_RO(C)[i*n+j] + D_RO(C)[i*n+j];
                                             	B[i][j] = temp*inverseEigth;
              				}
				}
			}else{
				while(k<10){
					k++;
                                        for( i=slice_start; i<slice_end; i++){
                                                for( j=1; j<nMinusOne; j++){
                                                        temp = A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
                                                                 A[i][j-1]        +        A[i][j+1]+
                                                               A[i+1][j-1] + A[i+1][j] + A[i+1][j+1];
                                                        B[i][j] = temp*inverseEigth;
                                                }
                                        }
                                }
			}
		}else{
			if( thread_id==dram_threads ){
				while(k<10){
					k++;
					i=0;
                                        for( j=1; j<nMinusOne; j++){
                                                temp = A[0][j-1]         +    A[0][j]      +         A[0][j+1]+
                                                       D_RO(C)[i*n+j]            +            D_RO(C)[i*n+j]+
                                                       D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j];
                                                D_RW(D)[i*n+j] = temp*inverseEigth;
                                        }
					for( i=slice_start+1; i<slice_end-1; i++){
                                                for( j=1; j<nMinusOne; j++){
                                                        temp = D_RO(C)[(i-1)*n+j] + D_RO(C)[(i-1)*n+j] + D_RO(C)[(i-1)*n+j]+
                                                               D_RO(C)[i*n+j]            +            D_RO(C)[i*n+j]+
                                                               D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j];
                                                        D_RW(D)[i*n+j] = temp*inverseEigth;
                                                }
                                        }
				}
			}else{
				while(k<10){
					k++;
                                        for( i=slice_start; i<slice_end; i++){
                                                for( j=1; j<nMinusOne; j++){
                                               		temp = D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j]+
                                                               D_RO(C)[(i+1)*n+j]            +            D_RO(C)[(i+1)*n+j]+
                                                               D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j] + D_RO(C)[(i+1)*n+j];
                                                        D_RW(D)[i*n+j] = temp*inverseEigth;
                                                }
                                        }
				}
			}
		}
		printf("%d\n", thread_id);
	}//End of parallel
	//POBJ_FREE(&C);
	//POBJ_FREE(&D);
}//End of method
//pmempool create --layout my_layout --size=10G obj pool.obj
//End of file.
