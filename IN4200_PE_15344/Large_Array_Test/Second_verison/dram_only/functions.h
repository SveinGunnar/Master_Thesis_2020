#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <omp.h>
#include <libpmemobj.h>

double * dram_calculation(int,int,int,int);
double mysecond();
