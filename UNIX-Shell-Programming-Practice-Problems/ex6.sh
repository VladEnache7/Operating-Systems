#!/bin/bash

for file in `find dir -type f -perm -a=w`; do
	echo `ls $file -l | awk '{print $1}'` $file
	`chmod o-w $file`
	echo `ls $file -l | awk '{print $1}'` $file	
done
