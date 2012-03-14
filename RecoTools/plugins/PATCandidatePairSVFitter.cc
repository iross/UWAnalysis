#include "UWAnalysis/RecoTools/plugins/PATCandidatePairSVFitter.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Candidate/interface/Candidate.h" 
#include "DataFormats/PatCandidates/interface/Muon.h" 
#include "DataFormats/PatCandidates/interface/Electron.h" 
#include "DataFormats/PatCandidates/interface/Tau.h" 


typedef PATCandidatePairSVFitter<pat::Muon, pat::Tau> PATMuTauSVFitter;
typedef PATCandidatePairSVFitter<pat::Electron, pat::Tau> PATEleTauSVFitter;
typedef PATCandidatePairSVFitter<pat::Electron, pat::Muon> PATEleMuSVFitter;
typedef PATCandidatePairSVFitter<pat::Muon, pat::Muon> PATMuMuSVFitter;



DEFINE_FWK_MODULE(PATMuTauSVFitter);
DEFINE_FWK_MODULE(PATEleTauSVFitter);
DEFINE_FWK_MODULE(PATEleMuSVFitter);
DEFINE_FWK_MODULE(PATMuMuSVFitter);
