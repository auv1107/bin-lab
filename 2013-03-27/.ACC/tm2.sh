#/bin/bash

cat tmp| wc -c
file tmp

while read content
do
	echo $content >> temp.c
done

gcc -o temp temp.c && ./temp
