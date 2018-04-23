#!/bin/sh

for fisier in $@
do
	x=`find $fisier`
	if echo $x | grep -q '^find:'; then
		echo good
	else
	 	y=`ls -la $fisier`
		if echo $y | grep "^.r" -q; then
			touch ${fisier}.info
		    echo $y | awk '{ print "Size:"; print $5; print "Data:"; print $6; print $7; print "Type:";}' > ${fisier}.info	
		    file $fisier >> ${fisier}.info	
		fi			
	fi


done > /dev/null 2>&1

