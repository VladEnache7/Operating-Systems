#!/bin/bash

for user in `who | awk {print $1}`; do
	echo $user `ps -u $user | wc -l`
done

