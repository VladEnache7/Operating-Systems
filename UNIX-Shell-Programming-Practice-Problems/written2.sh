#!/bin/bash

dir=""

while [ -z $dir ] || [ ! -d $dir ] ; do
	read -p "Provide an directory: " dir
done

sum=0
count=0

for subDir in `find $dir -type d` ; do
	txts=0
	for file in `find $subDir -name "*.txt"` ; do
		txts=`expr $txts + 1`
	done

	if [ $txts -ne 0 ] ; then
		sum=`expr $sum + $txts`
		count=`expr $count + 1`
	fi	
done

echo "Count: " $count
echo "Sum: " $sum
echo "Average: " `echo "$sum $count" | awk 'END {print $1/$2}'`
