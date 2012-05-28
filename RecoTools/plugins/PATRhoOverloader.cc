#include "UWAnalysis/RecoTools/plugins/PATRhoOverloader.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef PATRhoOverloader<pat::Muon> PATMuonRhoOverloader;
typedef PATRhoOverloader<pat::Tau> PATTauRhoOverloader;
typedef PATRhoOverloader<pat::Electron> PATElectronRhoOverloader;

DEFINE_FWK_MODULE(PATMuonRhoOverloader);
DEFINE_FWK_MODULE(PATElectronRhoOverloader);
DEFINE_FWK_MODULE(PATTauRhoOverloader);

