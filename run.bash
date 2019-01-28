#!/bin/bash
  
i=0

while [ $i -lt 15 ]
do
  ./speedtest
  let "i++"
done

