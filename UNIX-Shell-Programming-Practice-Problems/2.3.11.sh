#!/bin/bash

read -p "Provide one existent directory:" dir

while [ $# -ne 1 ] | [ ! -d $dir ]; do # if the argument is empty, zero
	read -p "!!Provide one existent directory!!:" dir
done

totalLines=0
totalFiles=0

for file in `find $dir -name "*.c"` ; do
	fileLines=`wc -l $file | awk '{print $1}'`
	totalLines=`expr $totalLines + $fileLines`
	totalFiles=`expr $totalFiles + 1`
	#echo $file
	basename $file
done

echo "Total lines: $totalLines"

echo "Nr of files: $totalFiles"

result=`expr $totalLines / $totalFiles`

echo "Medium nr of lines $result"
