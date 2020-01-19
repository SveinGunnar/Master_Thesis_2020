@echo off


gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.exe

PageRank.exe web-NotreDame.txt 0.99 0.0000001 10
