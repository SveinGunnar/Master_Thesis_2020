#!/bin/bash
socket1=0
socket2=16
num_threads=1
file="test1.txt"
CPUs=""
program="Stream_pmemobj_m.out"
#program="Stream_c_m.out"

echo DRAM test > $file

for (( n=0; n<16; n++ ))
do
	CPUs+="{$((socket1 + n))}"
	export OMP_NUM_THREADS=$num_threads
	echo OMP_NUM_THREADS=$num_threads >> $file
	export export OMP_PLACES=$CPUs
	echo export OMP_PLACES="'"$CPUs"'" >> $file
	./$program | grep -E 'Copy:|Scale:|Add:|Triad:' | awk '{print $2}' >> $file
	num_threads=$((num_threads+1))

	CPUs+=",{$((socket2 + n))}"
	export OMP_NUM_THREADS=$num_threads
	echo OMP_NUM_THREADS=$num_threads >> $file
	export export OMP_PLACES=$CPUs
	echo export OMP_PLACES="'"$CPUs"'" >> $file
	./$program | grep -E 'Copy:|Scale:|Add:|Triad:' | awk '{print $2}' >> $file
	num_threads=$((num_threads+1))
	CPUs+=","
done

#./Stream_c_s.out
#export OMP_NUM_THREADS=1
#export OMP_PLACES='{0}'

