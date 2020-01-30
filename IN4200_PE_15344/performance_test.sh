#!/bin/bash

export OMP_NESTED=TRUE

file="web-NotreDame.txt"
file2="100nodes_graphs.txt"
result="Result/performance_result.txt"
#d=0.85
d=0.99
# 0.0000001
e=0.0000001
m=10
temp=0

echo Iteration_threads transfer_threads max_threads time > $result

for (( a=0; a<10; a++ ))
do
	for (( n=1; n<15; n++ ))
	do
		temp=$(((16-$n)/2))
		if [ $(($n % 2)) == 0 ]
		then
			numactl --physcpubind=0-15 ./Page_rank.out $file $d $e $m $n $temp $temp >> $result
		else
			numactl --physcpubind=0-15 ./Page_rank.out $file $d $e $m $n $(($temp+1)) $temp >> $result
			numactl --physcpubind=0-15 ./Page_rank.out $file $d $e $m $n $temp $(($temp+1)) >> $result
		fi
	done
done

