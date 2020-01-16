#!/bin/bash
#Pmemobj_openMP_dualSocket.sh

file1="Result/Raws/NVM-NVM.txt"
file2="Result/Raws/DRAM-NVM.txt"
file3="Result/Raws/NVM-DRAM.txt"

total_threads=32
s1=0
s2=16


#NVM-NVM
truncate -s 0 $file1
for (( n=1; n<32; n++ ))
do
	#echo $n
	#echo $n NVM thread >> $file1

	if [ $n == 1 ]
	then
		numactl --physcpubind=0-$s1,16-$s2 ./Pmemobj_openMP_NVM-NVM.out $n $total_threads >> $file1
	elif [ $(($n % 2)) == 1 ]
	then
		numactl --physcpubind=0-$s1,16-$s2 ./Pmemobj_openMP_NVM-NVM.out $n $total_threads >> $file1
	elif [ $(($n % 2)) == 0 ]
	then
		numactl --physcpubind=0-$s1,16-$s2 ./Pmemobj_openMP_NVM-NVM.out $n $total_threads >> $file1
	else
		echo feil
	fi
done

#NVM-DRAM
#truncate -s 0 $file2
#for (( n=1; n<16; n++ ))
#do
#        echo $n >> $file2
#	numactl --physcpubind=0-15 ./Pmemobj_openMP_DRAM-NVM.out $n $total_threads >> $file2
#done

#DRAM-NVM
#truncate -s 0 $file3
#for (( n=1; n<16; n++ ))
#do
#	echo $n >> $file3
#	numactl --physcpubind=0-15 ./Pmemobj_openMP_NVM-DRAM.out $n $total_threads >> $file3
#done


#END
