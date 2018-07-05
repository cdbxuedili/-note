#!/bin/bash 

echo "请输入一个文件名:"

read fname 

if [ -e $fname ]
then
	echo "输入yes删除，输入no保留"
	read choose

	if [ $choose = "yes" ]
	then
		rm -rf $fname
	else if [ $choose = "no" ]
	then 
		echo "这个文件被保留"
	else 
		echo "输入的不是yes也不是no"
	fi 
	fi

else
	mkdir $fname
fi
