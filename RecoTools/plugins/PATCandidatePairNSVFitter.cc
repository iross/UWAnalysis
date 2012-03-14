#include "UWAnalysis/RecoTools/plugins/PATCandidatePairNSVFitter.h"

#include "FWCore/Framework/interface/MakerMacros.h"

#include "DataFormats/Candidate/interface/Candidate.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"


typedef PATCandidatePairNSVFitter<pat::Muon, pat::Tau> PATMuTauNSVFitter;
typedef PATCandidatePairNSVFitter<pat::Electron, pat::Tau> PATElecTauNSVFitter;
typedef PATCandidatePairNSVFitter<pat::Electron, pat::Muon> PATElecMuNSVFitter;
typedef PATCandidatePairNSVFitter<pat::Muon, pat::Muon> PATMuMuNSVFitter;



DEFINE_FWK_MODULE(PATMuTauNSVFitter);
DEFINE_FWK_MODULE(PATElecTauNSVFitter);
DEFINE_FWK_MODULE(PATElecMuNSVFitter);
DEFINE_FWK_MODULE(PATMuMuNSVFitter);
