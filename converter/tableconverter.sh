#!/bin/bash

input="nvm_table.txt"
column=14
row=""

echo "\begin{table}[!hbtp]"
echo "\begin{tabular}{ |c|c|c|c|c|c| } "


while IFS=',' read -r -a line
do
	row=""
	for (( n=0; n<8; n++ ))
	do
		row="$row ${line[$n]} &"
#		echo hline
	done
	echo \\hline
	echo "$row \\\\"
done < "$input"
echo \\hline

echo "\end{tabular}"
echo "\end{table}"
