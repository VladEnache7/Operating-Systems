#!/bin/bash

dir=""

while [ -z $dir ] || [ ! -d $dir ] ; do
	read -p "Provide an directory: " dir
done


for file in `find $dir -name "*.txt"` ; do
	if [ `cat $file | grep -E "cat"` ] ; then
		echo "Cat container: " $file
	fi
done
