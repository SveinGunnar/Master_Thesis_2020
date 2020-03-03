#!/bin/bash

input="DRAM_only.txt"
output="DRAM_only_average.txt"
t=10

total_time=0
iteration_time=0
analyse_time=0

echo "" > $output
while IFS= read -r line
do
#: <<'END'
	if [ -z $line ]
	then
		temp1=$(echo "scale=6;$total_time / $t" | bc)
                temp2=$(echo "scale=6;$iteration_time / $t" | bc)
                temp3=$(echo "scale=6;$analyse_time / $t" | bc)
                echo $total_thread,$temp1,$temp2,$temp3 >> $output
                echo $total_thread
		
		total_time=0
		iteration_time=0
		analyse_time=0

	else
		total_thread=$(echo $line | cut -d "," -f 1)

		temp=$(echo $line | cut -d "," -f 2)
		total_time=$(echo "${total_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 3)
                iteration_time=$(echo "${iteration_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 4)
                analyse_time=$(echo "${analyse_time} + ${temp}" | bc)
	fi
#END

#echo $line | cut -d "," -f 3

done < "$input"


