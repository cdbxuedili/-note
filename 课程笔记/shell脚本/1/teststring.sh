#!/bin/bash 

string="he2llo"

#比较时＝和!=两边必须有空格
#test "$string"="hello" 这个是错误的
#test "$string" = "hello" 
#test语句和[]是一样的
#注意:[的右边和]的左边必须至少有一个空格
[ "$string" = "hello" ]
echo $?

test "$string" != "hello"
echo $?

test -z "$string"
echo $?

test -n "$string"
echo $?

# -eq -ne -le -lt -ge -gt 
#  =  !=  <=  <   >=  >

#[80,100)
value=70
#test $value -ge 80 -a $value -lt 100
#[ $value -ge 80 -a $value -lt 100 ]

#test $value -ge 80 && test $value -lt 100 #这种情况不能使用-a
[ $value -ge 80 ] && [ $value -lt 100 ]
echo $?

echo "请输入一个文件名，包含路径:"
read fname

#test -f $fname
test -d $fname
echo $?
