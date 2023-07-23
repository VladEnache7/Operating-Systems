#!/bin/bash

echo -n "a = "
read a

read -p "b = " b

sum=`expr $a + $b`

echo "The sum is" $sum
