#!/bin/bash

n=$1
dir=$2
if [[ ! -d $dir ]] ; then
	echo "$dir is not valid directory"
	exit 1
fi

#oldfiles=`find $dir -type f | tr " " "\n"`
`find $dir -type f > /tmp/oldfiles`
sleep $n
while true ; do
	#newfiles=`find $dir -type f`
	`find $dir -type f > /tmp/newfiles`
	#if [[ $oldfiles == $newfiles ]] ; then 
	if [[ `cat /tmp/oldfiles` == `cat /tmp/newfiles` ]] ; then
		echo "nothing changes"
	else
		for change in `diff <(sort /tmp/oldfiles) <(sort /tmp/newfiles)` ; do
			if [[ `echo $change | grep -E "^>.*"` ]] ; then
				change=`echo $change | tr -d ">"`
				echo "$change removed"
			elif [[ `echo $change | grep -E "^<.*"` ]] ; then
				change=`echo $change | tr -d "<"`
				echo "$change created"
			fi
		done
	fi

	cat /tmp/oldfiles > /tmp/newfiles	
	sleep $n
done
