#!/bin/bash

cat df.fake | tail -n+2 | while read line ; do
	size=`echo $line | awk '{print $3}' | tr -d "M"`
	use=`echo $line | awk '{print $5}' | tr -d "%"`
	name=`echo $line | awk '{print $6}'`
	
	if [ $size -lt 1024 ] || [ $use -gt 80 ] ; then
		echo $name
	fi

done
