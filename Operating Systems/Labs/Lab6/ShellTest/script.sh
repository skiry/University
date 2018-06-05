#!/bin/sh

file='nume.txt'
file2='nume2.txt'

cp "$file" "$file2"

while :; do
	x=`diff $file $file2`
	if echo $x | grep -q '.\+'
	then
		cat "$file"
		cp $file $file2
	fi

	sleep 1
done
