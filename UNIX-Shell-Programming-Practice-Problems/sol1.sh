#!/bin/bash

read -p "Provide a directory: " dir

if [[ ! -d $dir ]] ; then
	echo "$dir is not a valid directory"
	exit 1
fi


for file in $@ ; do
	if [[ -f $dir/$file ]] ; then
		digits=`cat $dir/$file | tail -10 | grep -E "[0-9]+" | fold -1 | wc -l`
		echo "$file:$digits"
	else
		echo "$file:does not exits"	
	fi
done

