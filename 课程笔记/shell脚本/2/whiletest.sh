#!/bin/bash 

cat ip.txt | while read ip 
do
	a=`echo $ip | cut -d '.' -f 1`
	b=`echo $ip | cut -d '.' -f 2`
	c=`echo $ip | cut -d '.' -f 3`
	d=`echo $ip | cut -d '.' -f 4`
	
	sum=`expr $a \* 256 \* 256 \* 256 \
		+ $b \* 256 \* 256 \
		+ $c \* 256 \
		+ $d`
	echo $sum >> ip
done 
