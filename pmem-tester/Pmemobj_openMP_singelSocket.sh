#!/bin/bash
#Pmemobj_openMP_singelSocket.sh
#file1="Result/Raws/NVM-NVM_16t_5000i_v3.txt"
file1="Result/Raws/Test_001/NVM-NVM_16t_400i_16GB.txt"
#file2="Result/Raws/Test_001/DRAM-NVM_16t_300i_16GB.txt"
#file3="Result/Raws/Test_001/NVM-DRAM_16t_300i_16GB.txt"

#file1_average="Result/NVM-NVM_16t_average"
#file2_average="Result/DRAM-NVM_16t_average"
#file3_average="Result/NVM-DRAM_16t_average"

iterations=400
total_threads=16
#socket1=0
#socket2=16
#CPUs={0},{1},{2},{3},{4},{5},{6},{7},{8},{9},{10},{11},{12},{13},{14},{15}

#export OMP_PLACES=cores
#export OMP_PROC_BIND=close
#export OMP_NUM_THREADS=$total_threads
#export OMP_PLACES="'"$CPUs"'"
#pmempool create --layout my_layout --size=50G obj pool.obj

#NVM-NVM
echo NVM-NVM
#truncate -s 0 $file1
echo "" > $file1
echo "" >> $file1
for (( n=1; n<16; n++ ))
do
	echo $n
	numactl --physcpubind=0-15 --membind=0 ./Pmemobj_openMP_NVM-NVM.out $n $total_threads $iterations >> $file1
	echo "" >> $file1
	echo "" >> $file1
done

#DRAM-NVM
#echo DRAM-NVM
#truncate -s 0 $file2
#echo "" > $file2
#echo "" >> $file2
#for (( n=1; n<16; n++ ))
#do
#	echo $n
#	numactl --physcpubind=0-15 --membind=0 ./Pmemobj_openMP_DRAM-NVM.out $n $total_threads $iterations >> $file2
#	echo "" >> $file2
#	echo "" >> $file2
#done

#NVM-DRAM
#echo NVM-DRAM
#truncate -s 0 $file3
#echo "" > $file3
#echo "" >> $file3
#for (( n=1; n<16; n++ ))
#do
#	echo $n
#	numactl --physcpubind=0-15 --membind=0 ./Pmemobj_openMP_NVM-DRAM.out $n $total_threads $iterations >> $file3
#	echo "" >> $file3
#	echo "" >> $file3
#done

#END
