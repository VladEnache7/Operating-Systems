#!/bin/bash

max=10
i=5
while (( i <= $max ))
do
    echo "$i"
	i=`expr $i + 1`
	if (( i > 4 )) ; then
		echo "Greater than 4"
	fi
done
