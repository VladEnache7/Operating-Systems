#!/bin/bash

read -p "Computer Science is a great subject: " asw

case $asw in
	"True" | "true" | "TRUE") echo "Yes, you are right" ;;

	"False" | "false" | "FALSE") echo "NOO, you are wrong" ;;
esac
