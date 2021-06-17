#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
omp_lock_t lock_a, lock_b;
int* A;
int* B;
int* temp;
int A_ongoing;

void processA(){
	int n=0;
	int a=0;

	while( n<2 ){
		printf("%d\n",n);
		n++;
		
		A[0]++;
		omp_set_lock(&lock_a);
		//swap pointers here
		temp=A;
		A=B;
		B=temp;
		omp_unset_lock(&lock_b);
	}
	printf("A done.\n");
}
void processB(){
	int n=0;
	int a=0;
	int b=0;
	while(n<2){
		printf("%d\n",n);
		n++;
		omp_set_lock(&lock_b);
		//transfer from DRAM-NVDIMM
		omp_unset_lock(&lock_a);
		//Analyze
		b += 1;
	}
	printf("B done.\n");
}

int main(int argc, char **argv){
	A=(int*)malloc(1*sizeof(int));
	A[0]=0;
	B=(int*)malloc(1*sizeof(int));
	B[0]=0;
	A_ongoing=1;
	omp_set_lock(&lock_b);
	#pragma omp parallel num_threads(2)
	{
		int thread_id = omp_get_thread_num();
		if( thread_id == 0 ){
			processA();
		}else if( thread_id == 1 ){
			processB();
		}
	}
	free(A);
	free(B);
	return 0;
}
