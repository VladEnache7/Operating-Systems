#!/bin/bash

users=() 	# the users
freq=()		# the frequency of the users
nrUsers=1	# how many users are in who.fake

for userWho in `cat who.fake | awk '{print $1}'`; do
	users[$nrUsers]=$userWho
	freq[$nrUsers]=0
	nrUsers=`expr $nrUsers + 1`
done

# building the frequency vector
for userPs in `cat ps.fake | awk '{print $1}'`; do
	for i in `seq $nrUsers` ; do
		if [ "$userPs" = "${users[$i]}" ] ; then
			freq[$i]=`expr ${freq[$i]} + 1`
		fi
	done
done

# printing the users and the number of processes

for i in `seq $nrUsers` ; do
	echo ${users[$i]} ${freq[$i]}
done
