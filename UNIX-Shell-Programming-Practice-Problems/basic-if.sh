#!/bin/bash

for e in $@; do
	if [ -f $e ]; then
		echo $e is a file
	elif [ -d $e ]; then
		echo $e is a directory
	elif echo $e | grep -E -q "^[1-9]+$"; then
		echo $e is a number
	else
		echo $e is something else
	fi
done

echo ------------
