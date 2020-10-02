#!/bin/bash

export OMP_NESTED=TRUE
#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

file="testfile.txt"
file2="testfile2.txt"
file3="web-NotreDame.txt"
file4="100nodes_graphs.txt"

output=DRAM_only_100_chunksize1000.txt

#d=0.85
d=0.99
# 0.0000001
e=0.0000001
n=10

threads=16

#echo "" > $output
j=8
#echo Threads, Total time, Iteration time, Calculation time
for (( i=7; i<9; i++ ))
do
	#for (( j=0; j<100; j++ ))
	#do
	numactl --physcpubind=0-$i ./Page_rank.out $file3 $d $e $n $j $j 
	((j=j+1))
	#>> $output
	#done
	#echo $i
	#echo "" >> $output
done


#./PageRank.exe $file $d $e $n
#./PageRank.exe $file2 $d $e $n
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $n
#./Page_rank.out $file3 $d $e $n $threads $threads
#./PageRank.exe $file4 $d $e $n

#./PageRank.exe 0.85 0.000001 3
