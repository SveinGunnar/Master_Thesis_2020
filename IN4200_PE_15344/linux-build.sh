#!/bin/bash

#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

file="testfile.txt"
file2="testfile2.txt"
file3="web-NotreDame.txt"
file4="100nodes_graphs.txt"
#d=0.85
d=0.99
# 0.0000001
e=0.00000001
n=10

#./PageRank.exe $file $d $e $n
#./PageRank.exe $file2 $d $e $n
./Page_rank.out $file3 $d $e $n
#./PageRank.exe $file4 $d $e $n

#./PageRank.exe 0.85 0.000001 3
