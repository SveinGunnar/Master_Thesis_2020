#!/bin/bash

export OMP_NESTED=TRUE
file3="DRAM_only/neighbours_8_16M.t100"

numactl --physcpubind=0-8 ./LargeArrayTest.out 100000 100000 30000 6 3
