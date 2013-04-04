#!/bin/bash

if [ $# -eq 0 ]
then
	exit 0
fi

for i in ${*}
do
	exp=$exp+$i
done

echo '('${exp:1}')'/$# 
