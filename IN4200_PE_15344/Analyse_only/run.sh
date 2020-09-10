#!/bin/bash

for (( i=0; i<16; i++ ))
do
	numactl --physcpubind=0-$i ./Analyse.out
done
