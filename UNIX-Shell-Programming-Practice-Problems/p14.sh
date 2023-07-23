#!/bin/bash

read -p "Enter a number: " n

i=1
sum=0

while [ $sum -le $n ] ; do
	i=`expr $i + 1`
	sum=`expr $sum + $i`
	echo "i = $i"
done
 
echo "sum = $sum"
