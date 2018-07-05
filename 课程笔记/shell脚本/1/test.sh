#!/bin/bash
#cat passwd | head -`cat passwd | cut -d ':' -f 1 | grep "^linux$" -n | cut -d ':' -f 1` | tail -1

#num=`cat passwd | cut -d ':' -f 1 | grep "^linux$" -n | cut -d ':' -f 1`
#echo $num

#string=`cat passwd | head -$num | tail -1`
#echo $string


string=`cat passwd | head -\`cat passwd | cut -d ':' -f 1 | grep "^$1$" -n | cut -d ':' -f 1\` | tail -1`
echo $string


