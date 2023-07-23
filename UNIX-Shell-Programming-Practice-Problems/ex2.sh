#!/bin/bash

found=0 # variable that would help us

for file in `find dir -name "*.c"`; do # going through all the file ending in .c in the directory
	# stopping condition
	if [ $found -ge 2 ]; then
		break
	fi
	# tacking into consideration only the files having more than 500 lines
	if [ `cat $file | wc -l` -gt 500 ]; then
		found=`expr $found + 1`
		echo $file
	fi
done
