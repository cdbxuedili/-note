#!/bin/bash 

string=`ifconfig | head -2 | tail -1`
#echo "$string"

ip=${string%Bcast*}
#echo "$ip"

info=${string#"$ip"}
#echo "$info"

Bcast=${info%Mask*}
#echo "$Bcast"

Mask=${info#"$Bcast"}
#echo "$Mask"

ip=`echo $ip | cut -d ':' -f 2`
Bcast=`echo $Bcast | cut -d ':' -f 2`
Mask=`echo $Mask | cut -d ':' -f 2`

#echo $ip > note
#echo $Bcast >> note
#echo $Mask >> note

cat << EOF > note
$ip
$Bcast
$Mask
EOF
