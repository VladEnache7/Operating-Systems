#!/bin/bash

dir=""

while [ -z $dir ] || [ ! -d $dir ] ; do
        read -p "Provide an directory: " dir
done

for file in $(find $dir -name "*.txt"); do
	filePath=$(echo $file | sed 's/[a-zA-z0-9]*\.txt//gi')
	echo $filePath
done | sort | uniq -c | awk '{print $1}' | awk 'BEGIN {sum=0} {sum=sum+$1} END {print sum/NR}'
