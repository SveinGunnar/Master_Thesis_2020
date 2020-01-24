#ifndef PE_FUNCTIONS_15344_H
#define PE_FUNCTIONS_15344_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>
#include <sys/time.h>
#include <libpmemobj.h>

#define iter_threads 10
#define transfer_thread 11

int nodes, edges;
int *dwp; //dangling webpages
int dwp_size; //size of the dwp array.
int *CRS_row_ptr, *CRS_col_idx;
double *CRS_values;
double *x;
double *xk_1;

//double nvm_values
POBJ_LAYOUT_BEGIN(array);
POBJ_LAYOUT_TOID(array, double);
POBJ_LAYOUT_END(array);
#define LAYOUT_NAME "my_layout"
TOID(double) nvm_values;

void read_graph_from_file(char[]);
void PageRank_iterations(double, double);
void top_n_webpages(int);
void transfer_DRAM_to_NVM();
int top_n();
double mysecond();

#endif
