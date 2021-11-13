#!/bin/bash
socket1=0
socket2=16
num_threads=1
file1="temp.txt"
file2="NVM_sum_test_16_111121.txt"
CPUs=""
#program="Stream_.out"
program="Stream_sum_pmemobj.out"
cores=0

if [ -f $file1 ]; then
   rm $file1
fi

if [ -f $file2 ]; then
   rm $file2
fi

#touch $file1

echo NVM sum test cpu 16-32 > $file2

for (( n=16; n<32; n++ ))
do
	echo $(($n+1-16))
	echo $(($n+1-16)) >> $file1
	numactl --physcpubind=16-$n ./$program | grep -E 'Copy:|Scale:|Add:|Triad:|Average:' | awk '{print $2}' >> $file1
done

#for (( n=17; n<33; n++ ))
#do
#	export OMP_NUM_THREADS=$n
#	echo $n
#	echo $n >> $file1
#	numactl --physcpubind=0-15 ./$program | grep -E 'Copy:|Scale:|Add:|Triad:|Average:' | awk '{print $2}' >> $file1
#done

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

#./Stream_c_s.out
#export OMP_NUM_THREADS=1
#export OMP_PLACES='{0}'

