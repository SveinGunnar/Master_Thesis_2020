#!/bin/bash

export OMP_NESTED=TRUE
file3="DRAM_only/neighbours_8_16M.txt"

#argv[1] = Length of 2d array.
#argv[2] = Length of 2d array.
#argv[3] = NVDIMM array size.
#argv[4] = Number of DRAM threads.
#argv[5] = Number of NVDIMM threads.
#argv[6] = K_length

m=2000
n=500000
nvdimm=200
k=10

#printf("%d,%d,%d,%d,%d,%lf,%lf\n", m, n, nvdimm_array_length, dram_threads, nvdimm_threads, dram_average, nvdimm_average );
echo m:$m,n:$n,nvdimm_size:$nvdimm
echo m,n,nvdimm_array_length,dram_threads,nvdimm_threads,dram_average,nvdimm_average
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 1 15 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 2 14 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 3 13 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 4 12 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 5 11 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 6 10 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 7 9 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 8 8 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 9 7 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 10 6 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 11 5 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 12 4 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 13 3 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 14 2 $k
#numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 15 1 $k

numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 10 $k >> temp.txt
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 11 $k >> temp.txt
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 12 $k >> temp.txt
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 13 $k >> temp.txt
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 14 $k >> temp.txt
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 15 $k >> temp.txt

#numactl --physcpubind=0-2 ./LargeArrayTest.out 200 200 50 2 1 2

#m=1000
#n=100000
#nvdimm=100
#k=10
