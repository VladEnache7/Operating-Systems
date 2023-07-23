#!/bin/bash


f=""

while [ -z "$f" ] || ! [ -f "$f" ] || ! [ -r "$f" ]; do
	read -p "Provide an existing and readable file path:" f
done

