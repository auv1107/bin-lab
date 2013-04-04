#!/bin/bash

for (( i=0; i<54; i++)) 
do
	x="$x\n$i $RANDOM"
done
#echo -e ${x[*]}
#echo

echo -e ${x[*]} |sed '/^$/d'| sort -nk2 | awk 'BEGIN{x[0]="A";x[1]="B";x[2]="C";x[3]="D"}{printf "%d %c\n",$1/4+1,x[$1%4]}'
