#include "functions.h"

double * dram_calculation( int m, int n, int threads, int K ){
	double inverseEigth = 1/8;
	int k=0;
	int k_length = K;
	//double time;
	double *time = (double*)malloc(k_length*sizeof(double));

	//Creating 2d DRAM arrays.
        double **A = (double**)malloc( (m+1)*sizeof(double*));
        double **B = (double**)malloc( (m+1)*sizeof(double*));

	#pragma omp parallel num_threads(threads)
        {
		int i,j;
		double temp;
		int thread_id = omp_get_thread_num();
		//Add values to 2d array elements.
		#pragma omp for
		for(i=0;i<m;i++){
			A[i] = (double*)malloc(n*sizeof(double));
			B[i] = (double*)malloc(n*sizeof(double));
			for(j=0;j<n;j++){
				A[i][j] = i+j;
				B[i][j] = 0;
			}
		}
		#pragma omp single
		{
			A[m] = (double*)malloc(n*sizeof(double));
			B[m] = (double*)malloc(n*sizeof(double));
		}
		//Makes ghost array.
		#pragma omp for
		for(i=0;i<n;i++){
			A[m][i] = i;
		}
		while(k<k_length){
			#pragma omp barrier
			#pragma omp single
			{	
				time[k] = mysecond();
			}
			#pragma omp for
			for( i=1; i<m; i++){
				for( j=1; j<n-1; j++){
					temp =  A[i-1][j-1] + A[i-1][j] + A[i-1][j+1]+
						A[i][j-1]        +        A[i][j+1]+
						A[i+1][j-1] + A[i+1][j] + A[i+1][j+1];
					B[i][j] = temp*inverseEigth;
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
