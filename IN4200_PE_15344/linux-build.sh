#!/bin/bash

export OMP_NESTED=TRUE

file3="DRAM_only/neighbours_8_16M.txt"
file_output="simulation_result.txt"
#output_file="Result/result_n5000_16threads_16M_n_130521.txt"

#printf("%d,%d,%d,%f,%f,%f,%f,%f,%f,%f\n", iter_threads+transfer_threads, iter_threads, transfer_threads, iteration_time, iteration_idle_time, transfer_time, transfer_idle_time, DRAM_to_NVM_time, Analyse_time, test_time);
echo Total threads,DataGen Threads,Analyze threads,DataGen time,DataGen idle time,Transfer time,Transfer idle time,DRAM-NVM time,Analyze time,TestTime

#numactl --physcpubind=0-15 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 2 14 16

echo > $file_output
echo 1
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 15 1 16 >> $file_output
echo 2
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 14 2 16 >> $file_output
echo 3
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 13 3 16 >> $file_output
echo 4
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 12 4 16 >> $file_output
echo 5
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 11 5 16 >> $file_output
echo 6
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 10 6 16 >> $file_output
echo 7
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 9 7 16 >> $file_output
echo 8
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 8 8 16 >> $file_output
echo 9
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 7 9 16 >> $file_output
echo 10
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 6 10 16 >> $file_output
echo 11
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 5 11 16 >> $file_output
echo 12
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 4 12 16 >> $file_output
echo 13
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 3 13 16 >> $file_output
echo 14
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 2 14 16 >> $file_output
echo 15
numactl --physcpubind=16-31 --membind=1 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 1 15 16 >> $file_output

#PageRank_iterations
#perf probe --exec=Page_rank.out --funcs --no-demangle --filter='*'
#perf probe --exec=Page_rank.out --add='PageRank_iterations'
#perf stat -e cpu-clock,faults ./Page_rank.out
