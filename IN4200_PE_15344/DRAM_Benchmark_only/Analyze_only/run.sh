#!/bin/bash

export OMP_NESTED=TRUE
#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

#output_file="Result/result_n5000_01to16threads_0303_2021.txt"

#threads=16

nodes=4000000

#echo "" > $output
j=1
#truncate -s 0 $output_file
echo Threads, Total time
#echo Threads, Total time, Iteration time, Calculation time > $output_file
for (( i=0; i<16; i++ ))
do
	numactl --physcpubind=0-$i ./Analyze_only.out $nodes $j
	((j=j+1))
done
