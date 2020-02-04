#ifndef PE_FUNCTIONS_15344_H
#define PE_FUNCTIONS_15344_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <omp.h>
#include <time.h>

int nodes, edges;
int *dwp; //dangling webpages
int dwp_size; //size of the dwp array.
int *CRS_row_ptr, *CRS_col_idx;
double *CRS_values;
double *x;

void read_graph_from_file(char[]);
void PageRank_iterations(double, double);
void top_n_webpages(int);

#endif
