#!/bin/sh

#Inclusive 
bash submitBatch.sh observed muTau_X  1 1
bash submitBatch.sh observed eleTau_X 1 1
bash submitBatch.sh observed eleMu_X  1 1
bash submitBatch.sh observed Comb_X   1 1

bash submitBatch.sh expected muTau_X 2000 100 
bash submitBatch.sh expected eleMu_X 2000 100 
bash submitBatch.sh expected eleTau_X 2000 100 
bash submitBatch.sh expected Comb_X 2000 50 

#BTagging
bash submitBatch.sh observed muTau_BTag  1 1
bash submitBatch.sh observed eleTau_BTag 1 1
bash submitBatch.sh observed eleMu_BTag  1 1
bash submitBatch.sh observed Comb_BTag   1 1

bash submitBatch.sh expected muTau_BTag 2000 50 
bash submitBatch.sh expected eleMu_BTag 2000 50 
bash submitBatch.sh expected eleTau_BTag 2000 50 
bash submitBatch.sh expected Comb_BTag 2000 25 

#Standard Model
bash submitBatch.sh observed muTau_SM  1 1
bash submitBatch.sh observed eleTau_SM 1 1
bash submitBatch.sh observed eleMu_SM  1 1
bash submitBatch.sh observed Comb_SM   1 1

bash submitBatch.sh expected muTau_SM 2000 50 
bash submitBatch.sh expected eleMu_SM 2000 50 
bash submitBatch.sh expected eleTau_SM 2000 50 
bash submitBatch.sh expected Comb_SM 2000 20 





