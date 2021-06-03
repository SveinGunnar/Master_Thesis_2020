#include <stdio.h>
#include <libpmemobj.h>
#include "function.h"

//#define TOID_ARRAY(x) TOID(x)
//#define COUNT_OF(x) (sizeof(x) / sizeof(x[0]))
//#define MAX_BUFFLEN 30
//#define MAX_TYPE_NUM 8

//POBJ_LAYOUT_BEGIN(array);
//POBJ_LAYOUT_TOID(array, double);
//POBJ_LAYOUT_END(array);
#define LAYOUT_NAME "my_layout"

static PMEMobjpool *pop;

/*
	argv[1] = Number of max threads
	argv[2] = n
*/
int main(int argc, char **argv){
        const char path[] = "/mnt/pmem0-xfs/pool.obj";
        //PMEMobjpool *pop;
	pop = pmemobj_open(path, LAYOUT_NAME);

        if (pop == NULL) {
                perror(path);
                return 1;
        }
	
	int i,j;
	double iN = 1.0/nodes;
	transfer_threads = atof(argv[1]);
        nodes = atof(argv[2]);
	//iteration_time=0.0, transfer_time=0.0;
	//int top_n_index;
	//x = (double*)malloc(nodes*sizeof(double));
	//xk_1 = (double*)malloc(nodes*sizeof(double));

        POBJ_ALLOC(pop, &nvm_values, double, sizeof(double) * nodes, NULL, NULL);

	transfer_DRAM_to_NVM();
	//printf("Iteration_threads transfer_threads max_threads time\n");
	
	printf("%d,%f\n", transfer_threads, transfer_time);
	
	//Prints "return 0" when program ends without crashing
	//printf("\nreturn 0 det er slutt!\n");
	POBJ_FREE(&nvm_values);
	pmemobj_close(pop);
	return 0;
}

//double** test_time;
//test_time = mysecond();
//test_time = mysecond() - test_time;
//
