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
nvdimm=48
k=10
file_name=2k_500k.txt

#printf("%d,%d,%d,%d,%d,%lf,%lf\n", m, n, nvdimm_array_length, dram_threads, nvdimm_threads, dram_average, nvdimm_average );
echo m:$m,n:$n,nvdimm_size:$nvdimm
#echo m,n,nvdimm_array_length,dram_threads,nvdimm_threads,dram_average,nvdimm_average
echo m,n,nvdimm_array_length,dram_threads,nvdimm_threads,dram_average,dram_min,dram_max,nvdimm_average,nvdimm_min,nvdimm_max,total_average,total_min,total_max > temp_0-16.txt
echo start > $file_name
echo 1
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 48 15 1 $k >> $file_name
echo 2
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 95 14 2 $k >> $file_name
echo 3
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 146 13 3 $k >> $file_name
echo 4
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 195 12 4 $k >> $file_name
echo 5
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 246 11 5 $k >> $file_name
echo 6
numactl --physcpubind=0-15 ./LargeArrayTest.out $m $n 296 10 6 $k >> $file_name

#numactl --physcpubind=0-2 ./LargeArrayTest.out 200 200 50 2 1 2
#numactl --physcpubind=0-15 ./LargeArrayTest.out 4000 500000  10 6 $k

#m=1000
#n=100000
#nvdimm=100
#k=10
