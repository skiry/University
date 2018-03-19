#!/bin/bash

for f in `find /home/skiry/Desktop`; do
  if [ ! -f $f ]; then
    continue 
  fi
  u=`ls -l $f | cut -d' ' -f3`;
  s=`ls -l $f | cut -d' ' -f5`;
  if [ $s -gt 1000 ]; then
    echo $u
  fi
done|uniq
