#!/bin/bash

export OMP_NESTED=TRUE

output_file="Test_results.txt"


#echo 4000*4000 > $output_file
#echo Threads,Time >> $output_file

#for (( i=0; i<16; i++ ))
#do
	#echo $i
	#numactl --physcpubind=0-$i ./2D_arrayTest.out 10000 10000 >> $output_file
#done

numactl --physcpubind=0-15 ./LoadStoreTest.out 100000000
