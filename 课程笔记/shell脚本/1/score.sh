#!/bin/bash 

read score

#if [ $score -gt 100 ] || [ $score -lt 0 ]
if [ $score -gt 100 -o $score -lt 0 ]
then
	echo "input error"
	exit
fi

if [ $score -ge 80 -a $score -le 100 ]
then 
	echo "A"
else if [ $score -ge 60 -a $score -lt 80 ]
then 
	echo "B"
else 
	echo "C"
fi
fi
