#!/bin/bash
#Pmemobj_openMP_singelSocket.sh
#file1="Result/Raws/NVM-NVM_16t.txt"
#file2="Result/Raws/DRAM-NVM_16t.txt"
file3="Result/Raws/NVM-DRAM_16t.txt"

#file1_average="Result/NVM-NVM_16t_average"
#file2_average="Result/DRAM-NVM_16t_average"
file3_average="Result/NVM-DRAM_16t_average"

iterations=1000
total_threads=16
#socket1=0
#socket2=16
#CPUs={0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15}

#export OMP_PLACES=cores
#export OMP_PROC_BIND=close
#export OMP_NUM_THREADS=$total_threads
#export OMP_PLACES="'"$CPUs"'"

#NVM-NVM
echo NVM-NVM
#truncate -s 0 $file1
for (( n=1; n<16; n++ ))
do
	echo $n
	#echo $n NVM thread >> $file1
	#numactl --physcpubind=0-15 ./Pmemobj_openMP_NVM-NVM.out $n $total_threads $iterations >> $file1
done



#DRAM-NVM
echo DRAM-NVM
#truncate -s 0 $file2
for (( n=1; n<16; n++ ))
do
	echo $n
        #echo $n >> $file2
	#numactl --physcpubind=0-15 ./Pmemobj_openMP_DRAM-NVM.out $n $total_threads $iterations >> $file2
done

#NVM-DRAM
echo NVM-DRAM
truncate -s 0 $file3
for (( n=1; n<16; n++ ))
do
	echo $n
	echo $n >> $file3
	numactl --physcpubind=0-15 ./Pmemobj_openMP_NVM-DRAM.out $n $total_threads $iterations >> $file3
done



#END
