#include "UWAnalysis/RecoTools/plugins/MyTriggerMatcher.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef MyTriggerMatcher<pat::Muon> MuonTriggerMatcher;
typedef MyTriggerMatcher<pat::Tau> TauTriggerMatcher;
typedef MyTriggerMatcher<pat::Electron> ElectronTriggerMatcher;

DEFINE_FWK_MODULE(MuonTriggerMatcher);
DEFINE_FWK_MODULE(ElectronTriggerMatcher);
DEFINE_FWK_MODULE(TauTriggerMatcher);

