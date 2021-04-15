#!/bin/bash
socket1=0
socket2=16
num_threads=1
file1="temp.txt"
file2="DRAM_average_dualSocket_test_32.txt"
CPUs=""
#program="Stream_.out"
program="Stream_average.out"
cores=0

if [ -f $file1 ]; then
   rm $file1
fi

if [ -f $file2 ]; then
   rm $file2
fi

echo DRAM average dual sockets test cpu 0-32 > $file2

a=0
b=16

for (( n=0; n<32; n++ ))
do
	echo $(($n+1))
	echo $(($n+1)) >> $file1
	if (( $n == 0 )) ; then
		numactl --physcpubind=0-$a ./$program | grep -E 'Copy:|Scale:|Add:|Triad:|Average:' | awk '{print $2}' >> $file1
	elif (( $n == 1 )) ; then
		numactl --physcpubind=0-$a,16-$b ./$program | grep -E 'Copy:|Scale:|Add:|Triad:|Average:' | awk '{print $2}' >> $file1
	else
		if ((n % 2)); then
                	((b+=1))
        	else
                	((a+=1))
        	fi

		numactl --physcpubind=0-$a,16-$b ./$program | grep -E 'Copy:|Scale:|Add:|Triad:|Average:' | awk '{print $2}' >> $file1
	fi
done

m=0
templine=""

while IFS= read -r line
do
	if (( $m == 0 )) ; then
		templine=$line 
		m=$(($m+1))
	elif (( $m == 5 )) ; then
		templine=$templine","$line
		echo $templine >> $file2
		templine=""
		m=0
	else
		templine=$templine","$line
		m=$(($m+1))
	fi
done < "$file1"
