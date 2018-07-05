read var1
read var2 

#符号的左右必须有空格
ret=`expr $var1 \* $var2`
echo $ret
