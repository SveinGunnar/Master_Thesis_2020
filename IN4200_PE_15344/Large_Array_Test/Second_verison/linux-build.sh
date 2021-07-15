#!/bin/bash

export OMP_NESTED=TRUE
file3="DRAM_only/neighbours_8_16M.t100"

numactl --physcpubind=0-8 ./LargeArrayTest.out 100000 50000 15000 1 1 5
#numactl --physcpubind=0-8 ./LargeArrayTest.out 10000 10000 5000 2 2 10
