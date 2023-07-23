#!/bin/bash

declare -i totalLines

nrOfFiles=0
#
#
#
#for file in `find . -name "*.sh"` ; do
for file in written4.sh ; do
	totalLines=0
	cat $file | while read -r line ; do
		#echo $line
		# empty lines
		if [ -z "$line" ] ; then 
			echo "empty line" 
			continue
		fi
		# comments lines
		if [ ` echo "$line" | grep -E "^[ \t]*#.*$" ` ] ; then
			echo "Comment :" $line
			continue
		fi
		# lines with only spaces or tabs
		if [ ` echo "$line" | grep -E "^[ \t]*$" ` ] ; then
			echo "Free line "	
			continue
		fi
		
		#totalLines=`expr $totalLines + 1`
		totalLines=$((totalLines+1))
		echo "while loop: " $totalLines
	done
	echo "for loop: " $totalLines

	nrOfFiles=`expr $nrOfFiles + 1`
done

echo "Nr of Files .sh : " $nrOfFiles
echo "Nr of ok lines : " $totalLines
