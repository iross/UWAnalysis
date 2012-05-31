#!/bin/sh

FLIST=`ls|awk '{ if($1!="DATA.root") print $1}'`

for file in $FLIST
do
EventWeightsForEfficiencyFast  outputfile=$file  branch='__CORR__' finalState=$1
done
