#!/bin/bash

first=0

cat test.txt | while read -r word ; do
	if (( first != 0 )) ; then
		printf ","		
	fi
	printf $word
	printf "@scs.ubbcluj.ro"
	first=1
done

