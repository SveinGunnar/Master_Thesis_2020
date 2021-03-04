#!/bin/bash

export OMP_NESTED=TRUE
#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

file="testfile.txt"
file2="testfile2.txt"
file3="web-NotreDame.txt"
file4="100nodes_graphs.txt"
#file5="~/Master_Thesis_2020/IN4200_PE_15344/input_list/neighbours_8.txt"
file5="neighbours_8.txt"

output_file="Result/result_n5000_01to16threads_0303_2021.txt"

#d=0.85
d=0.99
# 0.0000001
e=0.0000001
n=10

threads=16

#head -10 $file5

#argv[1] = filename of the webpage linkage information
#argv[2] = damping constant d
#argv[3] = convergence threshold value e
#argv[4] = Number of max threads

#echo "" > $output
j=1
#truncate -s 0 $output_file
echo Threads, Total time, Iteration time, Calculation time
echo Threads, Total time, Iteration time, Calculation time > $output_file
for (( i=0; i<16; i++ ))
do
	echo $j
	#for (( j=0; j<100; j++ ))
	#do
	#numactl --physcpubind=0-$i ./Page_rank.out $file3 $d $e $i
	numactl --physcpubind=0-$i ./Page_rank.out $file5 $d $e $j >> $output_file
	((j=j+1))
	#>> $output
	#done
	#echo $i
	#echo "" >> $output
done
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e 16

#./PageRank.exe $file $d $e $n
#./PageRank.exe $file2 $d $e $n
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $n
#./Page_rank.out $file3 $d $e $n $threads $threads
#./PageRank.exe $file4 $d $e $n

#./PageRank.exe 0.85 0.000001 3
