#!/bin/bash

while read content
do
	echo $content >>temp.c
done
cat tmp|wc -c
file tmp

gcc -o temp temp.c && ./temp
