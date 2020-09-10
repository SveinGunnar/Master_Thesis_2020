#include "Analyse.h"

void analyse(){
	int nodes = 1000000000; // 1 billion
	int i=0;
	double time;
	double average = 0;
	double *array = (double*)malloc(nodes*sizeof(double));
	
	for(i=0;i<nodes;i++){
                array[i] = rand() % 1000000;
                //sumSquare += xk_1[i]*xk_1[i];
        }
	#pragma omp parallel //num_threads(1)
	{
		#pragma omp single
		{
			time = mysecond();
		}
		int j;
		#pragma omp for reduction(+ : average)
		for(j=0;j<nodes;j++){
			average += array[j];
		}
		#pragma omp barrier
		#pragma omp single
                {
			time = mysecond() - time;
                }


	}
	double speed = (8*nodes)/(1000*1000);
	speed = speed/time;
	printf("%f, %f\n", time, speed);	
}

double mysecond(){
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
