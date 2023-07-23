#!/bin/bash

for file in `find dir -name "*.log"`; do # search for all the files that ends with .log
	`sort $file > $file.saved` # sort them
done
