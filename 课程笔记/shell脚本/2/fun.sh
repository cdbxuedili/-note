#!/bin/bash 

function fun1()
{
	ls -l
}

#fun1
value=`fun1`
echo "$value"

fun2()
{
	i=10
	i=`expr $i + 2`

	return $i
}

#fun2

#value=`fun2`
#echo $value

fun2 
value=$?
echo $value
