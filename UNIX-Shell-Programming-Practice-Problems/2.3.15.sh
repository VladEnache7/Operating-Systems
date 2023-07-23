#!/bin/bash

if [ ! $# -eq 2 ] ; then
	echo "You have not provided exactly 2 arguments"
	exit 1
fi

if [ ! -d $1 ] ; then
	echo "$1 is not a valid directory"
	exit 1
fi

D=$1	# the directory
N=$2 	# the maximum nr of lines to be printed

for file in `find $D -perm -u=rx -type f ` ; do
	echo 
	echo "---$file---"
	head -$N $file
done


