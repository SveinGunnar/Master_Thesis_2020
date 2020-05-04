Explanation of the code

The program are divided into two parts. The data generating part and the analyzing part. How many cores each part gets are determined by the user by input parameters when the program start. The program uses a nested parallel region where the main method asks for two threads that divides the program by calling their own part of the program.

Each of those methods will then creates their own parallel regions and ask for the amount of threads specified by the user when he started the program. The two part of the program must communicate with each other in order to synchronize their work. The communication are done by using omp_set_lock and  omp_unset_lock. 

The data generating part of the program have two sets of array it stores its data on, but only uses one for each iteration and it will change the arrays by swapping pointers. The other array is used by the analyze part of the program to transfer the data over to NVDIMM where it will be analyzed by the program. 

While the analyzing part are transferring the data over to NVDIMM it will prevent the other part from swapping pointers by using the omp_set_lock before transferring the data and then use the omp_unset_lock when its done. The data generating part will also use the same method to prevent the analyzing part from starting the transfer when it is in the process of swapping pointers.

Below are an example of how the code can be structured.
The main method uses omp_set_lock before the parallel region so analyze method must wait until the data generating method have done the first iteration.

int main(int argc, char **argv){
	omp_init_lock(&lock_a);
	omp_init_lock(&lock_b);
	omp_set_lock(&lock_b);
	#pragma omp parallel num_threads(2)
	{
		if( thread_id == 0)
			data_generating();
		else if( thread_id == 1){
			analyze();
	}
}

data_generating(){
	#pragma omp parallel num_threads(threads)
 	{
		// Data generation
		omp_set_lock(&lock_a);
		// array swapping
		omp_unset_lock(&lock_b);
	}
}

analyze(){
	#pragma omp parallel num_threads(threads)
 	{
		omp_set_lock(&lock_b);
		// transferring data from DRAM to NVDIMM
		omp_unset_lock(&lock_a);
		// analyze data
	}
}
