#!/bin/bash

LOGDIR=/home/scott/bin/lab/log
CDID=
#TIT2=
#TPE1=
FORMAT=cdv
ID=1
DESTDIR=${1:-"."}
FILES=

readtag()
{
	mid3v2 $1 |sed -n '/TIT2\|TPE1/p' >_1.sh
	CDID=$( echo $1 |awk -F/ '{print $(NF-1)}')
}

makesh()
{
	cat >>_1.sh <<EOF
CDID=$CDID
LOGDIR=$LOGDIR
FORMAT=$FORMAT 
ID=$ID

if [ ! -e \$LOGDIR ]
then 
	mkdir -pv \$LOGDIR
fi
echo $CDID,$ID,\$TIT2,\$TPE1 >>${LOGDIR}/${CDID}.${FORMAT}
EOF
}

execsh()
{
	bash _1.sh
}

findmp3()
{
	FILES=$(find $DESTDIR -name *.mp3)
	if [ ${#FILES} -eq 0 ]
	then 
		echo No mp3 found
		exit 1
	fi
}

main()
{
	findmp3

	for file in $FILES
	do
		readtag $file
		makesh
		execsh
		: $((ID++))
	done
}

main
rm -rf _1.sh
