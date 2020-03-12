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

spread1=0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15
spread2=16,24,20,28,18,26,22,30,17,25,21,29,19,27,23,31
spread3=('0' '16' '8' '24' '4' '20' '12' '28' '2' '18' '10' '26' '6' '22' '14' '30' '1' '17' '9' '25' '5' '21' '13' '29' '3' '19' '11' '27' '7' '23' '15' '31')

current_spread=""

#echo Iteration_threads transfer_threads max_threads time > $result
#echo total_threads iteration_threads transfer_threads iteration_time iteration_idle_time transfer_time transfer_idle_time DRAM_to_NVM_time Analyse_time Total time > $result

#Total threads
for (( i=2; i<=16; i++ ))
do
	current_spread="${spread3[0]}"
	for (( m=1; m<i; m++ ))
	do
		current_spread+=",${spread3[$m]}"
	done
	echo $current_spread

	#Iteration threads
	for (( j=1; j<i; j++ ))
	do
		#transfer threads
		for (( k=1; k<=i-j; k++))
		do
			if [ $(($j+$k)) == $i ]
			then
				for (( l=0; l<1; l++))
				do
					numactl --physcpubind=$current_spread ./Page_rank.out $file $d $e $p $j $k $i #>> $result
					#echo
					#echo $i, $j, $k
				done
				#echo "" #>> $result

			fi
		done
	done	
done

