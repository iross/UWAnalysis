#include "UWAnalysis/PatTools/interface/CompositePtrCandidateT1T2MEtTriCrossCleaner.h"

#include "DataFormats/Candidate/interface/Candidate.h" 

typedef CompositePtrCandidateT1T2MEtTriCrossCleaner<PATMuPair, pat::Muon> PATMuMuMuTriCrossCleaner;
typedef CompositePtrCandidateT1T2MEtTriCrossCleaner<PATMuPair, pat::Electron> PATMuMuEleTriCrossCleaner;
typedef CompositePtrCandidateT1T2MEtTriCrossCleaner<PATElecPair, pat::Muon> PATEleEleMuTriCrossCleaner;
typedef CompositePtrCandidateT1T2MEtTriCrossCleaner<PATElecPair, pat::Electron> PATEleEleEleTriCrossCleaner;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PATMuMuMuTriCrossCleaner);
DEFINE_FWK_MODULE(PATMuMuEleTriCrossCleaner);
DEFINE_FWK_MODULE(PATEleEleMuTriCrossCleaner);
DEFINE_FWK_MODULE(PATEleEleEleTriCrossCleaner);


