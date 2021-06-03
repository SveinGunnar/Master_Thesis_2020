#!/bin/bash

export OMP_NESTED=TRUE

file3="DRAM_only/neighbours_8_16M.txt"
#output_file="Result/result_n5000_16threads_16M_n_130521.txt"

#printf("%d,%d,%d,%f,%f,%f,%f,%f,%f,%f\n", iter_threads+transfer_threads, iter_threads, transfer_threads, iteration_time, iteration_idle_time, transfer_time, transfer_idle_time, DRAM_to_NVM_time, Analyse_time, test_time);
#echo Total threads,DataGen Threads,Analyze threads,DataGen time,DataGen idle time,Transfer time,Transfer idle time,DRAM-NVM time,Analyze time,TestTime

#numactl --physcpubind=0-15 ./Page_rank.out DRAM_only/neighbours_8_16M.txt 2 14 16

numactl --physcpubind=0-0 ./Page_rank.out 1 16000000
numactl --physcpubind=0-1 ./Page_rank.out 2 16000000
numactl --physcpubind=0-2 ./Page_rank.out 3 16000000
numactl --physcpubind=0-3 ./Page_rank.out 4 16000000
numactl --physcpubind=0-4 ./Page_rank.out 5 16000000

numactl --physcpubind=0-5 ./Page_rank.out 6 16000000
numactl --physcpubind=0-6 ./Page_rank.out 7 16000000
numactl --physcpubind=0-7 ./Page_rank.out 8 16000000
numactl --physcpubind=0-8 ./Page_rank.out 9 16000000
numactl --physcpubind=0-9 ./Page_rank.out 10 16000000

numactl --physcpubind=0-10 ./Page_rank.out 11 16000000
numactl --physcpubind=0-11 ./Page_rank.out 12 16000000
numactl --physcpubind=0-12 ./Page_rank.out 13 16000000
numactl --physcpubind=0-13 ./Page_rank.out 14 16000000
numactl --physcpubind=0-14 ./Page_rank.out 15 16000000

numactl --physcpubind=0-15 ./Page_rank.out 16 16000000
