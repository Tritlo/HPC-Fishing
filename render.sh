#!/bin/bash
filename="out"
if [ ! -z $2 ]
	then filename=$2
	fi

ticks=$(head -n 1 $filename | awk '{print $1}')
for i in $(seq 0 $ticks);
do
    STR="^$i	"
    grep $STR $filename |  ./render.py $1
done
