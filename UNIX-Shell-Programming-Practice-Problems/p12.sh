#!/bin/bash

read -p "Enter a number: " x

if [ $x -gt 10 ] & [ $x -lt 20 ]; then
	echo "$x is between 10 and 20"
else
	echo "is not"
fi

