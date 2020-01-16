#!/bin/bash
#Pmemobj_openMP_singelSocket.sh
file1="Result/Raws/NVM-NVM_8t.txt"
file2="Result/Raws/DRAM-NVM_8t.txt"
file3="Result/Raws/NVM-DRAM_8t.txt"

iterations=1000
total_threads=8
socket1=0
socket2=16
CPUs={0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15}

#export OMP_PLACES=cores
#export OMP_PROC_BIND=close
#export OMP_NUM_THREADS=$total_threads
#export OMP_PLACES="'"$CPUs"'"

#NVM-NVM
echo NVM-NVM
truncate -s 0 $file1
for (( n=1; n<8; n++ ))
do
	echo $n
	echo $n NVM thread >> $file1
	numactl --physcpubind=0,2,4,6,8,10,12,14 ./Pmemobj_openMP_NVM-NVM.out $n $total_threads $iterations >> $file1
done

#DRAM-NVM
echo DRAM-NVM
truncate -s 0 $file2
for (( n=1; n<8; n++ ))
do
	echo $n
        echo $n >> $file2
	numactl --physcpubind=0,2,4,6,8,10,12,14 ./Pmemobj_openMP_DRAM-NVM.out $n $total_threads $iterations >> $file2
done

#NVM-DRAM
echo NVM-DRAM
truncate -s 0 $file3
for (( n=1; n<8; n++ ))
do
	echo $n
	echo $n >> $file3
	numactl --physcpubind=0,2,4,6,8,10,12,14 ./Pmemobj_openMP_NVM-DRAM.out $n $total_threads $iterations >> $file3
done


#END
