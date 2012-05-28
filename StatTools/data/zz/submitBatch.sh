#!/bin/bash

if [ "$1" = "" ]; then
   echo 'Usage : bash submitBatch.sh observed/expected model toys toys__per_job addopts'
fi

export ADDOPT=$5;

if [ "$1" = "observed" ]; then
    farmoutAnalysisJobs  --express-queue --input-dir=$PWD  --match-input-files='*'$2'_mA*.hlf' --fwklite  --output-dir=. limits_$2-obs $CMSSW_BASE $PWD/condor/runObserved.sh
fi

if [ "$1" = "expected" ]; then

    #find number of jobs = toys / toys per job
    N=$3/$4;

    for ((i=1; i<=$N ; i++ ))
      do
      export TOYMC=$4;
      farmoutAnalysisJobs  --express-queue --input-dir=$PWD  --match-input-files='*'$2'_mA*.hlf' --quick-test --fwklite --output-dir=. limits_$2-exp$i $CMSSW_BASE $PWD/condor/runExpected.sh 
      done

fi






