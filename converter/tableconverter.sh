#!/bin/bash

input="input.txt"
column=14
row=""

echo "\begin{center}"
echo "\begin{tabular}{ |c|c|c|c|c|c| } "


while IFS=',' read -r -a line
do
	row=""
	for (( n=0; n<6; n++ ))
	do
		row="$row ${line[$n]} &"
#		echo hline
	done
	echo \\hline
	echo "$row \\\\"
done < "$input"
echo \\hline

echo "\end{tabular}"
echo "\end{center}"
