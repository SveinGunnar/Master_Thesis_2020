#!/bin/bash

export OMP_NESTED=TRUE

file="web-NotreDame.txt"
file2="100nodes_graphs.txt"
result="Result/rawdata2.txt"
#d=0.85
d=0.99
# 0.0000001
e=0.0000001
p=10
#temp=0
t=10
tt=0.1

#echo Iteration_threads transfer_threads max_threads time > $result
echo total_threads iteration_threads transfer_threads iteration_time iteration_idle_time transfer_time transfer_idle_time DRAM_to_NVM_time Analyse_time Total time > $result

#Total threads
for (( i=2; i<=16; i++ ))
do
	#Iteration threads
	for (( j=1; j<i; j++ ))
	do
		#transfer threads
		for (( k=1; k<=i-j; k++))
		do
			if [ $(($j+$k)) == $i ]
			then
				for (( l=0; l<10; l++))
				do
					numactl --physcpubind=0-15 ./Page_rank.out $file $d $e $p $j $k $i >> $result
					echo $i, $j, $k
				done
				echo "" >> $result
			fi
		done
	done
done
