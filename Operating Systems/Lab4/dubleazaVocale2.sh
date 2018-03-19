#!/bin/sh 
 
awk -F: '{ if( index($1,"r") == 1) print $1 }' /etc/passwd |  while read u 
do 
#echo $u 
p=`ps U $u | wc -l` 
if test $p -gt 1; then 
echo $u | sed "s/\([aeiou]\)/\1\1/gi"  
fi 
done

