#!/bin/bash

n=$1
dir=$2
if [[ ! -d $dir ]] ; then
	echo "$dir is not valid directory"
	exit 1
fi

`find $dir -type f > /tmp/oldfiles`

`cat $dir/secret.txt > /tmp/secret`
shasum=`sha1sum $dir/secret.txt | awk '{print $1}'`

while true ; do
	`find $dir -type f > /tmp/newfiles`
	if [[ `cat /tmp/oldfiles` == `cat /tmp/newfiles` ]] ; then
		echo "nothing changes"
	else
		# checking for changes in secret.txt
		if [ ! `find $dir -name "secret.txt"` ] ; then
			`cat /tmp/secret > $dir/secret.txt`
			echo "$dir/secret.txt removed - restoring"
			continue
		elif [[ $shasum != `sha1sum $dir/secret.txt | awk '{print $1}'` ]] ; then
			`cat /tmp/secret > $dir/secret.txt`
			echo "$dir/secret.txt changed - restoring" 
			continue
		fi

		for file1 in `cat /tmp/oldfiles` ; do
			found=0
			for file2 in `cat /tmp/newfiles` ; do
				if [[ $file1 == $file2 ]] ; then
					found=1
				fi
			done
			# if the file was in old files but is not in newfiles => removed
			if [[ $found == 0 ]] ; then
				echo "$file1 removed"
			fi 
		done
		
		for file1 in `cat /tmp/newfiles` ; do
            found=0
            for file2 in `cat /tmp/oldfiles` ; do
                if [[ $file1 == $file2 ]] ; then
                    found=1
                fi
            done
            # if the file was in new files but is not in old files => created      
            if [[ $found == 0 ]] ; then
                echo "$file1 created"
            fi
        done
		
	fi

	cat /tmp/newfiles > /tmp/oldfiles
	sleep $n
done
