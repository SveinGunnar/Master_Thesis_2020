#!/bin/bash
#Pmemobj_openMP_singelSocket.sh
file1="Result/Raws/NVM-NVM_12nvmt_12dramt_5000i.txt"
file2="Result/Raws/DRAM-NVM_12nvmt_12dramt_5000i.txt"
file3="Result/Raws/NVM-DRAM_12nvmt_12dramt_5000i.txt"

iterations=5000
total_threads=16
n=16

echo NVM-NVM
echo $n
numactl --physcpubind=0-15 ./Pmemobj_openMP_NVM-NVM.out $n $total_threads $iterations >> $file1
echo "" >> $file1

#DRAM-NVM
echo DRAM-NVM
echo $n
numactl --physcpubind=0-15 ./Pmemobj_openMP_DRAM-NVM.out $n $total_threads $iterations >> $file2
echo "" >> $file2

#NVM-DRAM
echo NVM-DRAM
echo $n
numactl --physcpubind=0-15 ./Pmemobj_openMP_NVM-DRAM.out $n $total_threads $iterations >> $file3
echo "" >> $file3
