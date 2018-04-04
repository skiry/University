#!/bin/sh

set -x
set -e

if [ $# -eq 1 ]; then
	find $1 -type f -name '*.mp3' | while read f
	do
		md5sum $f
	done | sort | awk '{ if (index($1, a) && length($1) == length(a))
       		printf $2 " is duplicate\n"; a = $1;}' # | xargs rm -v
fi
