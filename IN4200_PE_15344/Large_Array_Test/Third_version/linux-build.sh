#!/bin/bash

export OMP_NESTED=TRUE
file3="DRAM_only/neighbours_8_16M.txt"

#argv[1] = Length of 2d array.
#argv[2] = Length of 2d array.
#argv[3] = NVDIMM array size.
#argv[4] = Number of DRAM threads.
#argv[5] = Number of NVDIMM threads.
#argv[6] = K_length

m=89450
n=89450
nvdimm=48
k=10
file_name=Single_results.txt

#printf("%d,%d,%d,%d,%d,%lf,%lf\n", m, n, nvdimm_array_length, dram_threads, nvdimm_threads, dram_average, nvdimm_average );
echo m:$m,n:$n,nvdimm_size:$nvdimm
#echo m,n,nvdimm_array_length,dram_threads,nvdimm_threads,dram_average,nvdimm_average
#echo m,n,nvdimm_array_length,dram_threads,nvdimm_threads,dram_average,dram_min,dram_max,nvdimm_average,nvdimm_min,nvdimm_max,total_average,total_min,total_max > temp_0-16.txt

m=31620
n=31620

#echo start > $file_name
#echo 1
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 727 15 1 $k >> $file_name
#echo 2
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 1438 14 2 $k >> $file_name
#echo 3
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 1972 13 3 $k >> $file_name
#echo 4
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 2560 12 4 $k >> $file_name
#echo 5
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 3060 11 5 $k >> $file_name
#echo 6
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 4086 10 6 $k >> $file_name

m=44720
n=44720
#echo "" >> $file_name

#echo 1
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 1080 15 1 $k >> $file_name
#echo 2
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 2033 14 2 $k >> $file_name
#echo 3
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 2789 13 3 $k >> $file_name
#echo 4
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 3620 12 4 $k >> $file_name
#echo 5
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 4328 11 5 $k >> $file_name
#echo 6
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 5779 10 6 $k >> $file_name

m=63250
n=63250
#echo "" >> $file_name

#echo 1
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 1454 15 1 $k >> $file_name
#echo 2
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 2876 14 2 $k >> $file_name
#echo 3
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 3945 13 3 $k >> $file_name
#echo 4
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 5121 12 4 $k >> $file_name
#echo 5
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 6121 11 5 $k >> $file_name
#echo 6
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 8174 10 6 $k >> $file_name

m=89450
n=89450
echo "" >> $file_name

echo 1
numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 2056 15 1 $k >> $file_name
echo 2
numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 4067 14 2 $k >> $file_name
echo 3
numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 5579 13 3 $k >> $file_name
echo 4
numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 7242 12 4 $k >> $file_name
echo 5
numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 8656 11 5 $k >> $file_name
echo 6
numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 11560 10 6 $k >> $file_name

m=100000
n=100000
#echo "" >> $file_name

#echo 1
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 2299 15 1 $k >> $file_name
#echo 2
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 4547 14 2 $k >> $file_name
#echo 3
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 6237 13 3 $k >> $file_name
#echo 4
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 8096 12 4 $k >> $file_name
#echo 5
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 9677 11 5 $k >> $file_name
#echo 6
#numactl --physcpubind=0-15 --membind=0 ./LargeArrayTest.out $m $n 12923 10 6 $k >> $file_name

