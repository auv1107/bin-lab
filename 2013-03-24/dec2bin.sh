#!/bin/bash


transfer()
{
	if [ $1 -eq 0 ]
	then
		return 0
	fi
	transfer $(($1/2))
	echo -n $(($1%2))
}

transfer $1
echo
