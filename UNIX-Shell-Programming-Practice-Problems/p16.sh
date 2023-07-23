#!/bin/bash
arr[farm]=0
for i in `seq 5` ; do
	arr[farm]+=1
done


for key in "${!arr[@]}" ; do
	echo "$key -> ${arr[$key]}" ;
done 
