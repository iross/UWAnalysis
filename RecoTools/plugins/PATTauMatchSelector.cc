#include "UWAnalysis/RecoTools/plugins/PATTauMatchSelector.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Tau.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"

typedef PATTauMatchSelector<pat::Muon> PATMuonTauMatchSelector;
typedef PATTauMatchSelector<pat::Tau> PATTauTauMatchSelector;
typedef PATTauMatchSelector<reco::RecoChargedCandidate> PATTrackTauMatchSelector;

DEFINE_FWK_MODULE(PATMuonTauMatchSelector);
DEFINE_FWK_MODULE(PATTrackTauMatchSelector);
DEFINE_FWK_MODULE(PATTauTauMatchSelector);
