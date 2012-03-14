#!/bin/sh
for i in 1 2 3 4 5 6 7 8 9 
do
find /scratch/bachtis/limits_$1-exp$i*/*/run*.root|xargs hadd LIMITS$i.root

find /scratch/bachtis/limits_$1-obs$i*/*/run*.root|xargs hadd LIMITS-OBS$i.root
done 

find ./LIMITS*.root |xargs hadd $1.root 
rm LIMITS*.root

