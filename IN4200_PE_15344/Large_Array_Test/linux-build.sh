#!/bin/bash

export OMP_NESTED=TRUE
file3="DRAM_only/neighbours_8_16M.txt"

numactl --physcpubind=0-2 ./LargeArrayTest.out 200 200 2 1 50
