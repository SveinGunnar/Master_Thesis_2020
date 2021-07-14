#!/bin/bash

export OMP_NESTED=TRUE
file3="DRAM_only/neighbours_8_16M.txt"

numactl --physcpubind=0-2 ./LargeArrayTest.out 20 10 2 1 10
