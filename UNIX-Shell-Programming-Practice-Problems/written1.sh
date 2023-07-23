#!/bin/bash

for user in vlad ; do
	N=`ps -u $user | wc -l`
	N=`expr $N - 1` # excluding the header line
	echo $user " - " $N
done
