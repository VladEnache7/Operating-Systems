#!/bin/bash

# validating the files
allRight=1
for file in $@ ; do
	if [ ! -f $file ] ; then
		echo "$file is not a valid file"
		allRight=0
	fi
done

# if there was something wrong with the files exit
if (( allRight == 0 )) ; then
	exit 1
fi

content=`cat $@ | sort`

duplicated=1
while (( duplicated == 1 )) ; do
	duplicated=0	# first assuming that ther is no duplicates
	apps=() # appointments
	freq=() # how many times they appear
	n=0		# nr of different appointments

	for line in `echo $content` ; do
		# seeing if the appointment does not already exits
		dupl=0
		for i in `seq $n` ; do
			if [[ ${apps[$i]} = $line ]] ; then
				((freq[i]++))
				dupl=1
				duplicated=1
				break
			fi
		done
		# if the line that we read is a duplicate we do not add it to
		# the appointments list
		if (( dupl == 1 )) ; then
			continue
		fi
		
		(( n++ )) # increasing the index
		apps[$n]=$line
		freq[$n]=1
	done

	content=""
	# going throw the appointments	
	for i in `seq $n` ; do
		firstname=`echo ${apps[$i]} | awk -F";" '{print $1}'`
		secondname=`echo ${apps[$i]} | awk -F";" '{print $2}'`
		day=`echo ${apps[$i]} | awk -F";" '{print $3}'`
		hour=`echo ${apps[$i]} | awk -F";" '{print $4}'`
		content+=`echo "$firstname;$secondname;$day;$hour\n"`
		if (( freq[$i] != 1 )) ; then
			if (( hour == 23 )) ; then
				((day++))
				hour=0
			else
				((hour++))
			fi
			content+=`echo "$firstname;$secondname;$day;$hour\n"`
		fi
	done
	content=`echo -e $content`
done #done of the while

# printing the result
echo -e "\n$content\n"
