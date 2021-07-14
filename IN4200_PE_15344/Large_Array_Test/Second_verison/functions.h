#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <libpmemobj.h>

//static PMEMobjpool *pop;
//double nvm_values
POBJ_LAYOUT_BEGIN(array);
POBJ_LAYOUT_TOID(array, double);
POBJ_LAYOUT_END(array);
#define LAYOUT_NAME "my_layout"
//TOID(double) C;
//TOID(double) D;

//double** create_DRAM_Array(int,int,int);
//void** create_NVDIMM_Array(int,int);
void calculation(int,int,int,int,int);

