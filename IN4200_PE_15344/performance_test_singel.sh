#!/bin/bash

export OMP_NESTED=TRUE

file="web-NotreDame.txt"
file2="100nodes_graphs.txt"
result="Result/rawdata_singel_100.txt"
#d=0.85
d=0.99
# 0.0000001
e=0.0000001
p=10
#temp=0
t=10
tt=0.1
tests=100

echo Iteration_threads transfer_threads max_threads time > $result
echo total_threads iteration_threads transfer_threads iteration_time iteration_idle_time transfer_time transfer_idle_time DRAM_to_NVM_time Analyse_time Total time > $result

i=16
j=14
k=2


for (( l=0; l<100; l++))
do
	numactl --physcpubind=0-15 ./Page_rank.out $file $d $e $p $j $k $i >> $result
	#echo $i, $j, $k
done
echo "" >> $result
