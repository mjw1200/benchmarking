#!/bin/bash
  
i=0

while [ $i -lt 50 ]
do
  ./speedtest
  let "i++"
done

