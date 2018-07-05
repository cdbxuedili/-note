#!/bin/bash 

num=1
sum=0

while [ $num -le 100 ]
do
	sum=`expr $sum + $num`
	num=`expr $num + 1`
#	((sum += num))
#	((num ++))
done 
echo $sum
