This folder contain the test where datageneration are done by one group of threads and the transfer to nvm and analyze of the data are done by another group of threads.

The performance_test_part1.sh tests all the different combinations of threads X amount of times and output the data to a file.
The performance_test_part2.sh takes the data from the first script and calculate the average of all the tests and output this to another file that can be pasted into excel.

The performance_test_spread_part1.sh are not yet complete.
