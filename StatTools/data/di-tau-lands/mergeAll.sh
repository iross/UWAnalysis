#!/bin/sh
rm -rf results
mkdir results
cd results
bash ../mergeFiles.sh muTau_X
bash ../mergeFiles.sh eleTau_X
bash ../mergeFiles.sh eleMu_X
bash ../mergeFiles.sh Comb_X

bash ../mergeFiles.sh muTau_BTag
bash ../mergeFiles.sh eleTau_BTag
bash ../mergeFiles.sh eleMu_BTag
bash ../mergeFiles.sh Comb_BTag


bash ../mergeFiles.sh muTau_SM
bash ../mergeFiles.sh eleTau_SM
bash ../mergeFiles.sh eleMu_SM
bash ../mergeFiles.sh Comb_SM




