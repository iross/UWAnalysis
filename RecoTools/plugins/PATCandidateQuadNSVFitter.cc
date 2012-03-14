#include "UWAnalysis/RecoTools/plugins/PATCandidateQuadNSVFitter.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"


typedef PATCandidateQuadNSVFitter<PATMuPair, PATMuTauPair> PATMuMuMuTauNSVFitter;
DEFINE_FWK_MODULE(PATMuMuMuTauNSVFitter);
