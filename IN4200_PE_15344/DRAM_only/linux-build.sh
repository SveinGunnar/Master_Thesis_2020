#!/bin/bash

export OMP_NESTED=TRUE
#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

file1="neighbours_8.txt"
file2="neighbours_8_16M.txt"

output_file="Result/result_n5000_01to16threads_16M-n_0605_2021.txt"

threads=16

#argv[1] = filename of the webpage linkage information
#argv[2] = Number of max threads

j=1
#truncate -s 0 $output_file
echo Threads, Total time, Iteration time, Calculation time
echo Threads, Total time, Iteration time, Calculation time > $output_file
for (( i=0; i<16; i++ ))
do
	echo $j
	numactl --physcpubind=0-$i ./Page_rank.out $file2 $j >> $output_file
	((j=j+1))
done
#numactl --physcpubind=0-15 ./Page_rank.out neighbours_8.txt 16
