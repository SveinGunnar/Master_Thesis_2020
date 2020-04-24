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

numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 14 2 16

#./Page_rank.out $file3 $d $e $n 3 8

#./PageRank.exe $file4 $d $e $n
#./PageRank.exe 0.85 0.000001 3

#testing=$(./Page_rank.out $file3 $d $e $n 4 10)
#echo $testing
