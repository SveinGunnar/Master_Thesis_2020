#!/bin/bash
socket1=0
socket2=16
num_threads=1
file="temp.txt"
CPUs=""
#program="Stream_.out"
program="Stream_c_m.out"

echo DRAM test > $file

for (( n=0; n<16; n++ ))
do
	echo $n
	echo $n >> $file
	numactl --physcpubind=0-$n ./$program | grep -E 'Copy:|Scale:|Add:|Triad:' | awk '{print $2}' >> $file

done

#./Stream_c_s.out
#export OMP_NUM_THREADS=1
#export OMP_PLACES='{0}'

