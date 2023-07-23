#!/bin/bash

read -p "Enter string 1: " str1

read -p "Enter string 2: " str2

if [ $str1 = $str2 ]; then
	echo "The strings are equal"
else
	echo "Thay are different"
fi
