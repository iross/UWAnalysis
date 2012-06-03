#include "UWAnalysis/RecoTools/plugins/PATRhoOverloader.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef PATRhoOverloader<pat::Muon> MuonRhoOverloader;
typedef PATRhoOverloader<pat::Tau> TauRhoOverloader;
typedef PATRhoOverloader<pat::Electron> ElectronRhoOverloader;

DEFINE_FWK_MODULE(MuonRhoOverloader);
DEFINE_FWK_MODULE(ElectronRhoOverloader);
DEFINE_FWK_MODULE(TauRhoOverloader);

