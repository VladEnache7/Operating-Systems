#!/bin/bash

read -p "Enter a character: " char

case $char in
	a | A) echo "Yeeey, $char is a vowel";;
    e | E) echo "Yeeey, $char is a vowel";;
    i | I) echo "Yeeey, $char is a vowel";;
    o | O) echo "Yeeey, $char is a vowel";;
    u | U) echo "Yeeey, $char is a vowel";;
	*) echo "Noo, $char is not a vowel";;
esac
