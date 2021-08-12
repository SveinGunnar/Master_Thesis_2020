#!/bin/bash

export OMP_NESTED=TRUE

m=1000
n=1000000
k=10

echo m:$m,n:$n,k:$k
echo m,n,dram_threads,dram_time
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 1 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 2 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 3 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 4 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 5 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 6 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 7 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 8 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 9 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 10 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 11 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 12 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 13 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 14 $k
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 15 $k

#numactl --physcpubind=0-8 ./LargeArrayTest.out 10000 10000 5000 2 2 10
