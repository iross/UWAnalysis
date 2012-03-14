#!/bin/bash

if [ "$1" = "" ]; then
   echo 'Usage : bash submitBatch.sh observed/expected model toys toys__per_job addopts'
fi

export ADDOPT=$5;
export WORKINGDIR=$PWD

if [ "$1" = "observed" ]; then

    N=$3/$4;

    for ((i=1; i<=$N ; i++ ))
      do
      farmoutAnalysisJobs   --input-dir=$PWD  --match-input-files=$2'_mA*.txt' --fwklite  --output-dir=. limits_$2-obs$i $CMSSW_BASE $PWD/condor/runObserved.sh
      done
fi

if [ "$1" = "expected" ]; then

    #find number of jobs = toys / toys per job
    N=$3/$4;

    for ((i=1; i<=$N ; i++ ))
      do
      export TOYMC=$4;
      farmoutAnalysisJobs   --input-dir=$PWD  --match-input-files=$2'_mA*.txt' --quick-test --fwklite --output-dir=. limits_$2-exp$i $CMSSW_BASE $PWD/condor/runExpected.sh 
      done

fi






