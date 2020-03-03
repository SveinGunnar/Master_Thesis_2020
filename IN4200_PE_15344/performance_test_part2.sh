#!/bin/bash

input="Result/rawdata2.txt"
output="Result/performance_result.txt"
t=10

total_thread=0
iteration_thread=0
transfer_thread=0

iteration_time=0
iteration_idle_time=0
transfer_time=0
transfer_idle_time=0
DRAM_to_NVM_time=0
Analyse_time=0
total_time=0

temp=""

while IFS= read -r line
do
#: <<'END'
	if [ -z $line ]
	then
		temp1=$(echo "scale=6;$iteration_time / $t" | bc)
                temp2=$(echo "scale=6;$iteration_idle_time / $t" | bc)
                temp3=$(echo "scale=6;$transfer_time / $t" | bc)
                temp4=$(echo "scale=6;$transfer_idle_time / $t" | bc)
                temp5=$(echo "scale=6;$DRAM_to_NVM_time / $t" | bc)
                temp6=$(echo "scale=6;$Analyse_time / $t" | bc)
                temp7=$(echo "scale=6;$total_time / $t" | bc)
                echo $total_thread,$iteration_thread,$transfer_thread,$temp1,$temp2,$temp3,$temp4,$temp5,$temp6,$temp7 >> $output
                echo $total_thread,$iteration_thread,$transfer_thread
		
		iteration_time=0
		iteration_idle_time=0
		transfer_time=0
		transfer_idle_time=0
		DRAM_to_NVM_time=0
		Analyse_time=0
		total_time=0

	else
		total_thread=$(echo $line | cut -d "," -f 1)
		iteration_thread=$(echo $line | cut -d "," -f 2)
		transfer_thread=$(echo $line | cut -d "," -f 3)

		temp=$(echo $line | cut -d "," -f 4)
		iteration_time=$(echo "${iteration_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 5)
                iteration_idle_time=$(echo "${iteration_idle_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 6)
                transfer_time=$(echo "${transfer_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 7)
                transfer_idle_time=$(echo "${transfer_idle_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 8)
                DRAM_to_NVM_time=$(echo "${DRAM_to_NVM_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 9)
                Analyse_time=$(echo "${Analyse_time} + ${temp}" | bc)
		temp=$(echo $line | cut -d "," -f 10)
                total_time=$(echo "${total_time} + ${temp}" | bc)
	fi
#END

#echo $line | cut -d "," -f 3

done < "$input"

#echo $iteration_time



: <<'END'
echo $STRING | cut -d " " -f $N

#Total threads
for (( i=16; i<=16; i++ ))
do
	#Iteration threads
	for (( j=15; j<i; j++ ))
	do
		#transfer threads
		for (( k=1; k<=i-j; k++))
		do
			if [ $(($j+$k)) == $i ]
			then
				iteration_time=0
                		iteration_idle_time=0
                		transfer_time=0
                		transfer_idle_time=0
                		DRAM_to_NVM_time=0
                		Analyse_time=0
				total_time=0
			
				for (( l=0; l<t; l++ ))
				do
					temp1=$(echo $temp | awk '{print $1}')
					temp2=$(echo $temp | awk '{print $2}')
					temp3=$(echo $temp | awk '{print $3}')
					temp4=$(echo $temp | awk '{print $4}')
					temp5=$(echo $temp | awk '{print $5}')
					temp6=$(echo $temp | awk '{print $6}')
					temp7=$(echo $temp | awk '{print $7}')
					iteration_time=$(echo "${iteration_time} + ${temp1}" | bc)
					iteration_idle_time=$(echo "${iteration_idle_time} + ${temp2}" | bc)
					transfer_time=$(echo "${transfer_time} + ${temp3}" | bc)
					transfer_idle_time=$(echo "${transfer_idle_time} + ${temp4}" | bc)
					DRAM_to_NVM_time=$(echo "${DRAM_to_NVM_time} + ${temp5}" | bc)
					Analyse_time=$(echo "${Analyse_time} + ${temp6}" | bc)
					total_time=$(echo "${total_time} + ${temp7}" | bc)
				done
				temp1=$(echo "scale=6;$iteration_time / $t" | bc)
				temp2=$(echo "scale=6;$iteration_idle_time / $t" | bc)
				temp3=$(echo "scale=6;$transfer_time / $t" | bc)
				temp4=$(echo "scale=6;$transfer_idle_time / $t" | bc)
				temp5=$(echo "scale=6;$DRAM_to_NVM_time / $t" | bc)
				temp6=$(echo "scale=6;$Analyse_time / $t" | bc)
				temp7=$(echo "scale=6;$total_time / $t" | bc)
				echo $i,$j,$k,$temp7,$temp1,$temp2,$temp3,$temp4,$temp5,$temp6 >> $result
				echo $i,$j,$k
			fi
		done
	done
done
END
