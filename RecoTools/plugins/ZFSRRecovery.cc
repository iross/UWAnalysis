#include "UWAnalysis/RecoTools/plugins/ZFSRRecovery.h"

#include "DataFormats/Candidate/interface/Candidate.h" 

typedef ZFSRRecovery<PATMuPair> MuMuZFSRRecovery;
typedef ZFSRRecovery<PATElecPair> EleEleZFSRRecovery;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(MuMuZFSRRecovery);
DEFINE_FWK_MODULE(EleEleZFSRRecovery);
