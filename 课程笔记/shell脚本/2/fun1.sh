#!/bin/bash 

function fun()
{
	local value=100
	echo $1
	echo $2
}

fun 3 4

echo $1
echo $2
echo $value
