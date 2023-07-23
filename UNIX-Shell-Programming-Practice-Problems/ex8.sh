#!/bin/bash

first=0

cat df.fake | tr -d "\r" | while read line ; do
	# not taking in consideration the first line
	if [ $first -eq 0 ] ; then
		first=1
		continue
	fi
	
	#echo "--> $line"
	
	if (( `echo $line | awk '{print $5}' | tr -d "%"` > 80 )) || (( `echo $line | awk '{print $3}' | tr -d "M"` < 1024 )) ; then
			awk '{print $6}'
	fi

done
