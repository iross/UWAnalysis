#!/bin/sh
for i in 1 2 3 4 5 6 7 8 9 
do
find /scratch/bachtis/limits_$1-exp$i*/*/*.root|xargs hadd LIMITS$i.root
done 

find /scratch/bachtis/limits_$1-obs*/*/*.root|xargs hadd LIMITS-OBS.root

find ./LIMITS*.root |xargs hadd $1.root 
rm LIMITS*.root

