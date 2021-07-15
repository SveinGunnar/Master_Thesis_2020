#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <libpmemobj.h>

omp_lock_t lock_dram, lock_nvdimm;
omp_nest_lock_t nested_lock;

POBJ_LAYOUT_BEGIN(array);
POBJ_LAYOUT_TOID(array, double);
POBJ_LAYOUT_END(array);
#define LAYOUT_NAME "my_layout"

double * dram_calculation(int,int,int,int);
double * nvdimm_calculation(int,int,int,int,int);
void calculation(int,int,int,int,int);
double mysecond();
