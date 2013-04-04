#!/bin/bash

a=$*
res=0

for ((i=0; i<${#a}; i++)) 
do
	if [ ${a:$i:1} -gt 1 ]
	then
		echo $* is not a valuable binary number
		exit -1
	fi
	res=$((res*2+${a:$i:1}))
done

echo $*'(b)' = $res'(d)'
exit 0
