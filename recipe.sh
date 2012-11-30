#!/bin/bash

: ${CMSSW_BASE:?"CMSSW_BASE is not set!  Run cmsenv before recipe.sh"}

#echo "Setting up CVS... input username:"
#read cvsuser
#export CVSROOT=:ext:$cvsuser@cmscvs.cern.ch:/cvs_server/repositories/CMSSW
#export CVS_RSH=ssh

#echo "Checking for CERN CVS kerberos ticket"
#HAS_TICKET=`klist 2>&1 | grep CERN.CH`

#if [ -z "$HAS_TICKET" ]; then
#  echo "ERROR: You need to kinit yourname@CERN.CH to enable CVS checkouts"
#  exit 1
#fi

cd $CMSSW_BASE/src
# Add all the SVfit nonsense 
cvs co -r bMinimalSVfit-08-03-11 AnalysisDataFormats/TauAnalysis                  
cvs co -r bMinimalSVfit_2012May13 TauAnalysis/CandidateTools                       

cvs co -r V08-03-15 PhysicsTools/Utilities

# PAT RECIPE V08-06-58 IAR 27.Sep.2012
addpkg DataFormats/PatCandidates  V06-04-19-05
addpkg PhysicsTools/PatAlgos V08-06-58
addpkg PhysicsTools/PatUtils V03-09-18
addpkg CommonTools/ParticleFlow B4_2_X_V00-03-05
addpkg PhysicsTools/SelectorUtils V00-03-24
addpkg PhysicsTools/UtilAlgos V08-02-14 

#to compile our limit package
cvs co  -r Michalis_THKeys_111103 HiggsAnalysis/CombinedLimit

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

# MELA
cvs co -r V00-01-05 -d ZZMatrixElement/MELA UserCode/CJLST/ZZMatrixElement/MELA

#todo: ghost muon cleaning recipe, ???

cd $CMSSW_BASE/src
echo "To compile: scram b -j 4"
