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
# Add all the SVfit nonsense 
cvs co -r bMinimalSVfit-08-03-11 AnalysisDataFormats/TauAnalysis                  
cvs co -r bMinimalSVfit_2012May13 TauAnalysis/CandidateTools                       

# PAT RECIPE V08-06-58 IAR 27.Sep.2012
addpkg DataFormats/PatCandidates  V06-04-19-05
# patch in 44X electrons so regression BS works
cvs up -r 1.44 DataFormats/PatCandidates/interface/Electron.h
cvs up -r 1.33 DataFormats/PatCandidates/src/Electron.cc
addpkg PhysicsTools/PatAlgos V08-06-58
addpkg PhysicsTools/PatUtils V03-09-18
addpkg CommonTools/ParticleFlow B4_2_X_V00-03-05
addpkg PhysicsTools/SelectorUtils V00-03-24
addpkg PhysicsTools/UtilAlgos V08-02-14 
# Remove this junky MHT package, we don't need it and it causes
# link errors with the MVAMET
rm -f PhysicsTools/PatAlgos/plugins/PATMHTProducer*

#Update to calculate Single Tower H/E in 42X
#https://twiki.cern.ch/twiki/bin/view/CMS/HoverE2012
cvs co -r CMSSW_4_2_8_patch7 RecoEgamma/EgammaElectronAlgos
cvs co -r CMSSW_5_2_2 RecoEgamma/EgammaElectronAlgos/src/ElectronHcalHelper.cc
cvs co -r CMSSW_5_2_2 RecoEgamma/EgammaElectronAlgos/interface/ElectronHcalHelper.h
cvs co -r CMSSW_5_2_2 RecoEgamma/EgammaIsolationAlgos

# For a fix to prevent segfaults on certain MC samples when using
# the GenParticlePrunder
cvs co -r V11-03-16 PhysicsTools/HepMCCandAlgos

# need these to work with the latest pattuples.
cvs co -r V03-03-18 DataFormats/METReco
cvs co -r V05-00-16 DataFormats/JetReco
# apparently this file called some headers that have moved...
cvs up -r 1.1 DataFormats/JetReco/interface/PFClusterJet.h  

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

#Ghost muon cleaning https://www.dropbox.com/s/oddw6hrl67tgnrk/gp-ghost.pptx
cvs co -r U09-00-00-01 DataFormats/MuonReco 
cvs co -r V02-03-00 MuonAnalysis/MuonAssociators/plugins/MuonCleanerBySegments.cc
cvs co -r V02-03-00 MuonAnalysis/MuonAssociators/plugins/BuildFile.xml
cvs co -r V02-03-00 MuonAnalysis/MuonAssociators/BuildFile.xml
cvs co -r V02-03-00 MuonAnalysis/MuonAssociators/python/muonCleanerBySegments_cfi.py
# apply patches
pushd MuonAnalysis/MuonAssociators/plugins/
patch -p1 MuonCleanerBySegments.cc $CMSSW_BASE/src/UWAnalysis/patches/MuonCleanerBySegments_cc.patch
cd ../python/
patch -p1 muonCleanerBySegments_cfi.py $CMSSW_BASE/src/UWAnalysis/patches/muonCleanerBySegments_cfi_py.patch
popd

cd $CMSSW_BASE/src
echo "To compile: scram b -j 4"
