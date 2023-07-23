#!/bin/bash

for x in * ; do
   if [ `file $x | grep -ci "ASCII text"` -eq 0 ] ; then continue ; fi
   #Variabila cuv1 retine primul cuvant de pe o linie, delimitator spatiu
  	for cuv1 in `cat $x` ; do
      #verificam daca linia nu e vida, respectiv lungimea primului cuvant
      if [ ! -z $cuv1 ] && [ `expr length $cuv1` -ge 5 ] ; then
         echo "In $x s-a gasit $cuv1 cu lungimea `expr length $cuv1`"
         break  # Se iese din ciclul while
      fi
   done
   break # Se iese din ciclul for
done

