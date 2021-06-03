#include "function.h"

//TOID(double) *nvm_values;
void transfer_DRAM_to_NVM(){
        int i;
	int n=0;
	//int size;
	//int maximum_index=0, minimum_index=0;
	double iN = 1.0/nodes;
	double average=0.0;
	//antiOpt=0;

	#pragma omp parallel num_threads(transfer_threads)
        {
		//printf("test\n");
		#pragma omp for
                for( i=0; i<nodes; i++){
			D_RW(nvm_values)[i]=((double)rand()/(double)(RAND_MAX));
                }
		//double temp_value=0.0;
		#pragma omp single
		{
			transfer_time = mysecond();
		}

                while(n<5000){
			#pragma omp barrier
			#pragma omp single 
			{
				average=0.0;
				n++;
			}
			
			//first time
			#pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){ // 1
                                average += D_RO(nvm_values)[i]; // 1
                        }
			//Second time.
			#pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){ // 1
                                average += D_RO(nvm_values)[i]; // 1
                        }
			//Third time.
                        #pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){ // 1
                                average += D_RO(nvm_values)[i]; // 1
                        }
			//fourth time.
                        #pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){ // 1
                                average += D_RO(nvm_values)[i]; // 1
                        }
			//fifth time.
                        #pragma omp for reduction(+ : average)
                        for(i=0;i<nodes;i++){ // 1
                                average += D_RO(nvm_values)[i]; // 1
                        }
                        #pragma omp single
                        {
				average *= iN;
                        }
                }
        }//end of parallel

	transfer_time = mysecond() - transfer_time;
} 

double mysecond(){ //fpo 2
        struct timeval tp;
        struct timezone tzp;
        int i;

        i = gettimeofday(&tp,&tzp);
        return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
}
