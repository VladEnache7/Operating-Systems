#!/bin/bash

s=0
for f in $1/*.c; do
	N=`grep "[^ \t]" $f | wc -l`
	s=`expr $s + $N`
done
echo $s
