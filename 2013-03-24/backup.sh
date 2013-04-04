#!/bin/bash

if [ ! -e _backup ]
then
	mkdir _backup
fi

tar czvf _backup/$(date +_bak_%Y%m%d_%H%M%S) $*
