#!/bin/bash



cat $INPUT |
(
while read FILENAME
do

#create random number
NUMBER=1

while [ $NUMBER -lt 15000 ] 
do
NUMBER=$RANDOM
done 
echo $NUMBER


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

$CMSSW_BASE/bin/$SCRAM_ARCH/combine -d $FILENAME  -s  $NUMBER -m $MASS -t $TOYMC  $ADDOPT
mv  higgsCombineTest.ProfileLikelihood.mH$MASS.$NUMBER.root $OUTPUT

done
)




