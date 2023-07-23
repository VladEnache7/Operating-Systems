#!/bin/bash

read -p "Provide an directory: " dir

# validation
while [ $# -ne 1 ] | [ ! -d $dir ]; do # if the argument is empty, zero
        read -p "!!Provide one existent directory!!: " dir
done


for file in `find $dir -type f`; do
	basename $file

done | sort --unique

