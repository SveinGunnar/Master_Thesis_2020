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

void calculation( int m, int n, int dram_threads, int K_length ){
//	printf("m: %d, n: %d, dram_threads: %d, nvdimm_threads: %d, nvdimm_array_length %d, K_length: %d\n", m,n,dram_threads,nvdimm_threads,nvdimm_array_length,K_length);
	int k=0;
	int a,b;
	int num_threads = dram_threads;
	//int dram_max, nvdimm_max;
	int mMinusOne = m-1;
	int nMinusOne = n-1;
	double inverseEigth = 1/8;
	double *nvdimm_time = (double*)malloc(K_length*sizeof(double));
	double **individual_time = (double**)malloc((K_length)*sizeof(double*));
	for(a=0;a<K_length;a++){
		individual_time[a] = (double*)malloc((dram_threads)*sizeof(double));
		for(b=0;b<dram_threads;b++)
			individual_time[a][b] = 0.0;
	}
	/*
	double **total_time = (double**)malloc((K_length)*sizeof(double*));
	for(a=0;a<K_length;a++){
                total_time[a] = (double*)malloc((dram_threads)*sizeof(double));
		for(b=0;b<dram_threads;b++)
                        total_time[a][b] = 0.0;
        }
	*/
//	double *individual_time = (double*)malloc((dram_threads+nvdimm_threads)*sizeof(double));
	double *dram_time = (double*)malloc(K_length*sizeof(double));
	double *total_time = (double*)malloc(K_length*sizeof(double));
//	double *total_time;

//	printf("Before Array creation\n");

	//Creating DRAM arrays.
	double **A = create_DRAM_Array(m,n);
	double **B = create_DRAM_Array(m,n);
	double **tempArray;
	
//	printf("Before parallel region\n");

	#pragma omp parallel num_threads(num_threads) 
	{
//		double *individual_total_time = (double*)malloc(K_length*sizeof(double));
		int thread_id = omp_get_thread_num();
		int slice_start, slice_end;
		int i,j;
		double temp;

		
		//Add values to dram 2d array
		#pragma omp for
                for(i=0;i<m;i++){
                        for(j=0;j<n;j++){
                        //      printf("T: %d, i: %d, j: %d, i*n+j: %d\n", thread_id, i, j, i*n+j);
				A[i][j] = i+j;
                                B[i][j] = 0;
                        }
                }

		//Creates slices for dram and nvdimm.
		if( thread_id < dram_threads ){
			slice_start = thread_id*(m/dram_threads);
			slice_end = (thread_id+1)*(m/dram_threads);
			if(thread_id==0)
				slice_start++;
			if(thread_id==(dram_threads-1))
                                slice_end--;
		}else{
		}
//		printf("thread id: %d, slice start: %d, slice end: %d\n", thread_id, slice_start, slice_end);
		while(k<K_length){
			#pragma omp barrier
			#pragma omp single
			{
				total_time[k] = mysecond();
			}
			//#pragma omp barrier
			//for the thread bordering on nvdimm thread.
			individual_time[k][thread_id] = mysecond();
                        for( i=slice_start; i<slice_end; i++){
                                for( j=1; j<nMinusOne; j++){
                                        temp = A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
                                               A[i][j-1]        +        A[i][j+1]+
                                               A[i+1][j-1] + A[i+1][j] + A[i+1][j+1];
                                        B[i][j] = temp*inverseEigth;
                        	}
                        }
			individual_time[k][thread_id] = mysecond() - individual_time[k][thread_id];

			//individual_total_time[k] = mysecond() - individual_total_time[k];
			#pragma omp barrier
			#pragma omp single
			{
				tempArray = B;
				B=A;
				A=tempArray;
				total_time[k] = mysecond() - total_time[k];
				k++;
			}
			#pragma omp barrier
		}//End of while
//		if(thread_id==0)
//			total_time = individual_total_time;
//		printf("End of thread id: %d\n", thread_id);
	}//End of parallel
	int i,j;
	double dram_average=0;
	double total_average=0;
        for(i=1;i<K_length;i++){
		for(j=0;j<dram_threads;j++){
                	dram_average += individual_time[i][j];
		}
		total_average += total_time[i];
        }
	//printf("%d\n", K_length);
        dram_average = dram_average/(dram_threads*(K_length-1));
	total_average = total_average/(K_length-1);
	printf("K_length: %d\n", K_length-1);

	int start = 1;
	double dram_min = individual_time[start][0], dram_max = individual_time[start][0];
	double total_min = total_time[start], total_max = total_time[start];

	for(i=1;i<K_length;i++){
                for(j=0;j<dram_threads;j++){
			if( individual_time[i][j] < dram_min )
				dram_min = individual_time[i][j];
			if( individual_time[i][j] > dram_max )
                                dram_max = individual_time[i][j];
		}
		if( total_time[i] < total_min )
   			total_min = total_time[i];
  		if( total_time[i] > total_max )
      			total_max = total_time[i];
	}
	
	printf("%d,%d,%d,%lf,%lf,%lf,%lf,%lf,%lf\n",m,n,dram_threads, dram_average,dram_min,dram_max, total_average,total_min,total_max );
	//printf("%d, %d\n", K_length, dram_threads);
	for(i=0;i<K_length;i++){
		printf("%lf", individual_time[i][0]);
                for(j=1;j<dram_threads;j++){
			printf(",%lf", individual_time[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	for(i=0;i<K_length;i++){
                printf("%lf\n", total_time[i]);
        }
	printf("\n");
	
//	printf("Iteration,Dram_time,Nvdimm_time\n");
//	for(i=0;i<K_length;i++){
//		printf("%d,%lf,%lf\n", i, dram_time[i], nvdimm_time[i]);
//	}
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
