#!/bin/sh
#merge the files
#takes as input the channel model i.e MuTau_Morph


for higgsMass in 90 100 120 130 140 160 180 200 250 300 350 400 450 500 
do
cp  models/common.hlf tmp;
cat models/mutau.hlf >>tmp;


#set Higgs mass
sed -i "s/GGH120/GGH$higgsMass/g"  tmp;
sed -i "s/BBH120/BBH$higgsMass/g"  tmp;

#add the common theory parameters (we dont want a mass replace for those 
#thats why we do it like this
cp models/theory.hlf tt_$1_mA$higgsMass.hlf;
cat tmp >>tt_$1_mA$higgsMass.hlf;
rm tmp;

#remove include lines
sed -i '/^\#,/d' tt_$1_mA$higgsMass.hlf;

#change files
sed -i "s#import(#import($PWD/#g"  tt_$1_mA$higgsMass.hlf;


#setup default model
sed -i "s/model_$1_s/model_s/g"  tt_$1_mA$higgsMass.hlf;
sed -i "s/model_$1_b/model_b/g"  tt_$1_mA$higgsMass.hlf;
sed -i "s/model_$1_nuisances/nuisances/g"  tt_$1_mA$higgsMass.hlf;
sed -i "s/model_$1_observables/observables/g"  tt_$1_mA$higgsMass.hlf;
sed -i "s/model_$1_POI/POI/g"  tt_$1_mA$higgsMass.hlf;
sed -i "s/model_$1_nuisancePdf/nuisancePdf/g"  tt_$1_mA$higgsMass.hlf;
done








