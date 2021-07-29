#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <libpmemobj.h>

POBJ_LAYOUT_BEGIN(array);
POBJ_LAYOUT_TOID(array, double);
POBJ_LAYOUT_END(array);
#define LAYOUT_NAME "my_layout"

double * nvdimm_calculation(int,int,int,int);
double mysecond();
