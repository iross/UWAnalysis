#!/bin/bash

echo "Checking for CERN CVS kerberos ticket"
HAS_TICKET=`klist 2>&1 | grep CERN.CH`

# Check if we can checkout anonymously
IS_ANON=`echo $CVSROOT | grep pserver`

if [ -z "$HAS_TICKET" ]; then
    if [ -z "$IS_ANON" ] ; then
        echo "ERROR: You need to kinit yourname@CERN.CH to enable CVS checkouts"
        exit 1
    fi
fi

cd $CMSSW_BASE/src
#for new pattuples
cvs co -r V06-05-06-03 DataFormats/PatCandidates 
cvs co -r V08-09-47 PhysicsTools/PatAlgos

# Add all the SVfit nonsense 
cvs co -r bMinimalSVfit-08-03-11 AnalysisDataFormats/TauAnalysis                  
cvs co -r bMinimalSVfit_2012May13 TauAnalysis/CandidateTools                       

#to compile our limit package
cvs co -r V02-01-00 HiggsAnalysis/CombinedLimit

#electron e corrections
cvs co -r ICHEP2012_V03 -d EgammaCalibratedGsfElectrons UserCode/EGamma/EgammaCalibratedGsfElectrons

#get the stuff for recalculating the electron MVAs, if necessary
cvs co -r V00-00-08 -d EGamma/EGammaAnalysisTools UserCode/EGamma/EGammaAnalysisTools
pushd EGamma/EGammaAnalysisTools/data
cat download.url | xargs wget
popd
# Get updated effective areas
cvs up -r 1.3 EGamma/EGammaAnalysisTools/interface/ElectronEffectiveArea.h

# Add muon effective area code
cvs co -r V00-00-10 -d Muon/MuonAnalysisTools UserCode/sixie/Muon/MuonAnalysisTools 
# Remove trainings we don't use
rm Muon/MuonAnalysisTools/data/*xml

# Muon ghost cleaning https://www.dropbox.com/s/oddw6hrl67tgnrk/gp-ghost.pptx
cvs co -r U09-04-03-00-01 DataFormats/MuonReco 
cvs co -r V02-03-00 MuonAnalysis/MuonAssociators

# MELA + MEKD garbage
cvs co -r V02-06-00 HiggsAnalysis/CombinedLimit
cvs co -r V00-03-01 -d Higgs/Higgs_CS_and_Width UserCode/Snowball/Higgs/Higgs_CS_and_Width 
cvs co -r bonato_supermela_20121107 -d HZZ4L_Combination/CombinationPy UserCode/HZZ4L_Combination/CombinationPy
cvs co -r V00-01-26 -d ZZMatrixElement/MELA UserCode/CJLST/ZZMatrixElement/MELA
cvs co -r V00-01-04 -d ZZMatrixElement/MEKD UserCode/UFL/ZZMatrixElement/MEKD
cvs co -r  V00-00-09 -d ZZMatrixElement/MEMCalculators UserCode/HZZ4l_MEM/ZZMatrixElement/MEMCalculators

# grab the latest data JSONs
cd $CMSSW_BASE/src/UWAnalysis/CRAB/LLLL/dataJSONs
sh update.sh

echo Checking out the submodules...
pushd $CMSSW_BASE/src/UWAnalysis
git submodule init
git submodule update
popd

cd $CMSSW_BASE/src/
pushd ZZMatrixElement/MELA/src/
patch -p1 computeAngles.cc $CMSSW_BASE/src/UWAnalysis/patches/computeAngles_cc.patch
popd

echo "To compile: go to CMSSW_BASE/src and scram b -j 4"
