#!/bin/bash

S=0

for f in `find $1 -type f -name "*.c"`; do
	N=`grep "[^ \t]" $f | wc -l`
	S=`expr $S + $N`
done

echo $S
