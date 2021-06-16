#include <stdio.h>
#include <omp.h>
omp_lock_t lock_a, lock_b;

void processA(){
	int n=0;
	int a=0;

	while( n<5000 ){
		n++;

		omp_set_lock(&lock_a);
		//swap pointers here
		
		omp_unset_lock(&lock_b);
	}
}
void processB(){
	while(1==1){
		omp_set_lock(&lock_b);
		//transfer from DRAM-NVDIMM
		omp_unset_lock(&lock_a);
		//Analyze
	}
}

int main(int argc, char **argv){
	//
	return 0;
}
