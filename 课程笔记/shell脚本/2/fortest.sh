#!/bin/bash 

while :
do
	echo -n "请输入一个目录名:"
	read fname    #输入/home/linux/teach

	if [ ! -e $fname ]
	then
		echo "文件不存在,请重新输入"
		continue
	fi

	if [ -d $fname ]
	then  #fname=/home/linux/teach
		list=`ls $fname`   #单词表
		cd $fname #切换路径
		for var in $list
		do
			#echo $var
			#if [ -f $var ]
			#认为是当前路径下的内容,单独写这句话是错误的,避免错误可以提前切换路径
			#if [ -f $fname/$var ]正确的

			if [ -f $var ]
			then
				cp $var ~/file 
			fi 

			if [ -d $var ]
			then 
				cp $var ~/dir -arf
			fi 
		done

	else
		echo "文件不是目录,重新输入"
		continue
	fi
done
