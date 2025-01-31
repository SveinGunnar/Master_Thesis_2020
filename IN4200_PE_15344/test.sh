#!/bin/bash

export OMP_NESTED=TRUE
#gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

file="testfile.txt"
file2="testfile2.txt"
#file3="web-NotreDame.txt"
file3="input_list/neighbours_8.txt"
#file3="input_list/forTesting.txt"
file4="100nodes_graphs.txt"
altfile="web-Stanford.txt"
#output_file="Result/result_n5000_16threads_040321.txt"

#d=0.85
d=0.99
# 0.0000001
e=0.0000001
n=10

p=10

#./PageRank.exe $file $d $e $n
#./PageRank.exe $file2 $d $e $n
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $n
#

#printf("%d,%d,%d,%f,%f,%f,%f,%f,%f,%f\n", iter_threads+transfer_threads, iter_threads, transfer_threads, iteration_time, iteration_idle_time, transfer_time, transfer_idle_time, DRAM_to_NVM_time, Analyse_time, test_time);
#echo Total threads,DataGen Threads,Analyze threads,DataGen time,DataGen idle time,Transfer time,Transfer idle time,DRAM-NVM time,Analyze time,TestTime > $output_file

#echo 1
numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 15 1 16 
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 14 2 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 13 3 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 12 4 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 11 5 16
#echo 6
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 10 6 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 9 7 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 8 8 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 7 9 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 6 10 16
#echo 11
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 5 11 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 4 12 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 3 13 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 2 14 16
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 1 15 16

#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 15 2 17
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 16 2 18
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 17 2 19
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 18 2 20

#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 19 2 21
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 20 2 22
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 21 2 23
#numactl --physcpubind=0-15 ./Page_rank.out $file3 $d $e $p 22 2 24

#numactl --physcpubind=0-15 ./Page_rank.out $altfile $d $e $p 14 2 16

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

#numactl --physcpubind=0-15 ./Page_rank.out web-NotreDame.txt $d $e $p 2 14 16
#numactl --physcpubind=0-15 ./Page_rank.out input_list/forTesting.txt $d $e $p 2 14 16
#numactl --physcpubind=0-15 ./Page_rank.out input_list/neighbours_8.txt $d $e $p 2 14 16
#numactl --physcpubind=0-15 ./Page_rank.out input_list/neighbours_24.txt $d $e $p 2 14 16
