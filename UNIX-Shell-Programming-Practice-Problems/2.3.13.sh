#!/bin/bash

awk <$1 '{for (i=1; i<=NF; i++)\
if ($i !~ /^[a-z]+$/) $i="";\
linie = ""; for (i=1; i<=NF; i++) if($i != "") linie = linie $i " ";\
if (linie != "") print substr(linie,1,length(linie)-1);}' |\
sort -u >$2 

