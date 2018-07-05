#!/bin/bash 

read score 

if [ $score -lt 0 ] || [ $score -gt 100 ]
then
	echo "error"
	exit
fi

num=`expr $score / 10`
#((num = score / 10))

case $num in 
	10 | 9 | 8)
		echo "A"
		;;
	6 | 7)
		echo "B"
		;;
	*)
		echo "C"
		;;
esac

