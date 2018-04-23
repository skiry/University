#!/bin/sh

q=''
touch out.txt

cat 'f.txt' | while read x
do
	y=`finger $x`
	if echo $y | grep -q '^Login'
	then
		printf ", $x@scs.ubbcluj.ro" >> out.txt
	fi
done > /dev/null 2>&1

sed -i 's/,//' out.txt
