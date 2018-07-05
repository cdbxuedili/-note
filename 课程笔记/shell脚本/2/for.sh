#!/bin/bash 

string="a   b    c     d      e"

count=0
for var in $string
do
	count=`expr $count + 1`
	echo "$var"
done 
echo $count
