#!/bin/bash

export OMP_NESTED=TRUE
#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

file="testfile.txt"
file2="testfile2.txt"
file3="web-NotreDame.txt"
file4="100nodes_graphs.txt"
#file5="~/Master_Thesis_2020/IN4200_PE_15344/input_list/neighbours_8.txt"
file5="neighbours_8.txt"

output_file="Result/result_n5000_01to16threads_1504_2021.txt"

#d=0.85
d=0.99
# 0.0000001
e=0.0000001
n=10

threads=16

#head -10 $file5

#argv[1] = filename of the webpage linkage information
#argv[2] = Number of max threads

#echo "" > $output
j=1
#truncate -s 0 $output_file
echo Threads, Total time, Iteration time, Calculation time
echo Threads, Total time, Iteration time, Calculation time > $output_file
for (( i=0; i<16; i++ ))
do
	echo $j
	numactl --physcpubind=0-$i ./Page_rank.out $file5 $j >> $output_file
	((j=j+1))
done
