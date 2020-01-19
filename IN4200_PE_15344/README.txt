The program can be compiled and run by using the build.bat on winsdows
or linux-build.sh on linux.

The commands I used to compile the program was:
Windows
gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.exe

Linux
gcc -fopenmp PE_main_15344.c PE_functions_15344.c -o PageRank.out

The inputs variables are in following order:
textfile damping epsilon top-N

The commandlines I used to start the program was
Windows
PageRank.exe web-NotreDame.txt 0.99 0.0000001 10

Linux
./PageRank.out web-NotreDame.txt 0.99 0.0000001 10