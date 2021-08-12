#!/bin/bash

export OMP_NESTED=TRUE

m=1000
n=1000000
nvdimm=200
k=10

echo m:$m,n:$n,nvdimm_size:$nvdimm
echo m,n,nvdimm_array_length,dram_threads,nvdimm_threads,dram_average,dram_min,dram_max,nvdimm_average,nvdimm_min,nvdimm_max
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 1 15 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 2 14 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 3 13 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 4 12 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 5 11 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 6 10 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 7 9 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 8 8 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 9 7 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 10 6 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 11 5 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 12 4 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 13 3 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 14 2 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n $nvdimm 15 1 $k

#numactl --physcpubind=0-8 ./LargeArrayTest.out 10000 10000 5000 2 2 10
