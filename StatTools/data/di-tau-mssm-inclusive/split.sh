#!/bin/sh
#merge the files
#takes as input the channel  i.e MuTau


for higgsMass in 90 100 120 130 140 160 180 200 250 300 350 400 450 500 
do
cp  models/common.hlf tmp;
cat models/mutau.hlf >>tmp;
cat models/etau.hlf >>tmp;
cat models/emu.hlf >>tmp;
cat models/combined.hlf >>tmp;




#set Higgs mass
sed -i "s/GGH120/GGH$higgsMass/g"  tmp;
sed -i "s/BBH120/BBH$higgsMass/g"  tmp;

#add the common theory parameters (we dont want a mass replace for those 
#thats why we do it like this
cp models/theory.hlf tt_$1_MSSM_mA$higgsMass.hlf;
cat tmp >>tt_$1_MSSM_mA$higgsMass.hlf;
rm tmp;

#remove include lines
sed -i '/^\#/d' tt_$1_MSSM_mA$higgsMass.hlf;


#change files
sed -i "s#import(#import($PWD/#g"  tt_$1_MSSM_mA$higgsMass.hlf;


#setup default model
sed -i "s/model_$1_MSSM_s/model_s/g"  tt_$1_MSSM_mA$higgsMass.hlf;
sed -i "s/model_$1_MSSM_b/model_b/g"  tt_$1_MSSM_mA$higgsMass.hlf;
sed -i "s/model_$1_MSSM_nuisances/nuisances/g"  tt_$1_MSSM_mA$higgsMass.hlf;
sed -i "s/model_$1_MSSM_observables/observables/g"  tt_$1_MSSM_mA$higgsMass.hlf;
sed -i "s/model_$1_MSSM_POI/POI/g"  tt_$1_MSSM_mA$higgsMass.hlf;
sed -i "s/model_$1_MSSM_nuisancePdf/nuisancePdf/g"  tt_$1_MSSM_mA$higgsMass.hlf;
done



for higgsMass in 100 105 110 115 120 130
do
cp  models/common.hlf tmp;
cat models/mutau.hlf >>tmp;
cat models/etau.hlf >>tmp;
cat models/emu.hlf >>tmp;
cat models/combined.hlf >>tmp;




#set Higgs mass
sed -i "s/SM120/SM$higgsMass/g"  tmp;


#add the common theory parameters (we dont want a mass replace for those 
#thats why we do it like this
cp models/theory.hlf tt_$1_SM_mA$higgsMass.hlf;
cat tmp >>tt_$1_SM_mA$higgsMass.hlf;
rm tmp;

#remove include lines
sed -i '/^\#/d' tt_$1_SM_mA$higgsMass.hlf;


#change files
sed -i "s#import(#import($PWD/#g"  tt_$1_SM_mA$higgsMass.hlf;


#setup default model
sed -i "s/model_$1_SM_s/model_s/g"  tt_$1_SM_mA$higgsMass.hlf;
sed -i "s/model_$1_SM_b/model_b/g"  tt_$1_SM_mA$higgsMass.hlf;
sed -i "s/model_$1_SM_nuisances/nuisances/g"  tt_$1_SM_mA$higgsMass.hlf;
sed -i "s/model_$1_SM_observables/observables/g"  tt_$1_SM_mA$higgsMass.hlf;
sed -i "s/model_$1_SM_POI/POI/g"  tt_$1_SM_mA$higgsMass.hlf;
sed -i "s/model_$1_SM_nuisancePdf/nuisancePdf/g"  tt_$1_SM_mA$higgsMass.hlf;
done









