#!/bin/bash

if [[ `echo "1000M" | tr -d "M"` < 1024 ]] ; then
	echo "yes" 
else
	echo "no"
fi
