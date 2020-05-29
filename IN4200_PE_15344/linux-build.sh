#!/bin/bash

export OMP_NESTED=TRUE
#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

file="testfile.txt"
file2="testfile2.txt"
file3="web-NotreDame.txt"
file4="100nodes_graphs.txt"
#d=0.85
d=0.99
# 0.0000001
e=0.0000001
n=10

p=10

#./PageRank.exe $file $d $e $n
#./PageRank.exe $file2 $d $e $n
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $n

#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 15 1 16
numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 14 2 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 13 3 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 12 4 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 11 5 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 10 6 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 9 7 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 8 8 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 7 9 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 6 10 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 5 11 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 4 12 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 3 13 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 2 14 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 1 15 16

#for (( i=1; i<=10; i++ ))
#do
	#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 14 2 16
	#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 1 1 2
#done

#./Page_rank.out $file3 $d $e $n 3 8

#./PageRank.exe $file4 $d $e $n
#./PageRank.exe 0.85 0.000001 3

#testing=$(./Page_rank.out $file3 $d $e $n 4 10)
#echo $testing
