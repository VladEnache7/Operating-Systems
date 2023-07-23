#!/bin/bash

read -p "Provide a directory: " dir

for file in `find $dir`; do
	echo $file
	if [ -L $file ] && [ -e $file ]; then
		echo "$file is symbolic link to a file that no longer exits"
	fi
done

