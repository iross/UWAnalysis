#!/bin/bash


#create random number
NUMBER=0
echo 'Random Number = '$NUMBER

cat $INPUT |
(
while read FILENAME
do
#trim and get the filename
FILE=${FILENAME##*/} 
echo 'Input = '$FILE

#get the mass
MASSANDEXT=${FILE##*_mA}
echo 'Mass and extention = '$MASSANDEXT

MASS=${MASSANDEXT%*.hlf}
echo 'Mass  = '$MASS


CHANNEL=${DA%%_*}
echo 'Channel  = '$CHANNEL

$CMSSW_BASE/bin/$SCRAM_ARCH/combine -d $FILENAME   -m $MASS -M ProfileLikelihood --maxTries 50 --tries 5 $ADDOPT
mv  higgsCombineTest.ProfileLikelihood.mH$MASS.root $OUTPUT


done
)




