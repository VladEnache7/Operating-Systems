#!/bin/bash

read -p "Provide a file: " file

while [ -z $file ] || [ ! -f $file ] ; do
	read -p "Provide a valid file!:" file
done

count=1
res=""
for word in `cat $file | tr -d "\n\r"`; do
	
	res+="$word"
	res+="@scs.ubbcluj.ro"
	if [ $count -lt `wc -l <$file` ]; then
		res+=", "
	fi
	count=`expr $count + 1`
done

echo "$res"
