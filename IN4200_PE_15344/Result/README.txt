Explanation for both performance_result_100_chunksize1000.pdf and Performance_result_14-2_chunksize1000.pdf

Explanation of columns from left to right
The first column show the total number of cores used in the test. The second column show how many cores are used to generate data and the third column show how many cores are used to analyze the data. 

The fourth and fifth column show how much time the data generating cores used to generate the data and how much of that time they were idle waiting for for the analyze part to complete.

Sixth and seventh column show how much time the cores used for analyzing spent on analyzing the data and how much of that time they were idle waiting for the data generation cores to finish their tasks.

Column six that show how much time spent on data generation are divided into two task in column eight and nine. Column eight show how much of the time was spent on transfering the data from DRAM to NVDIMM. Column nine show much time are spent on analyzing the data.

The tenth column show the time spent from the program enters and exit the parallel region in the main method.

performance_result_100_chunksize1000.pdf
This is the test result of all the different possibilities to distribute the cores between data-generation and  data-analyzing. Each combination have been test 100 times and then an average have been taken of the result. 

Performance_result_14-2_chunksize1000.pdf
This result focus only on the fastest core combination in performance_result_100_chunksize1000.pdf.
It lists all the 100 test result and place them in a histogram where one can see the spread of the result. 71 of the tests have a total time of either 0.32 second or 0.33 second. The rest of the result are spread from 0.25 second to 0.4 second.
