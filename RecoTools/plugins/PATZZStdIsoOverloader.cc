#include "UWAnalysis/RecoTools/plugins/PATZZStdIsoOverloader.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef PATZZStdIsoOverloader<pat::Muon> MuonZZStdIsoOverloader;
typedef PATZZStdIsoOverloader<pat::Tau> TauZZStdIsoOverloader;
typedef PATZZStdIsoOverloader<pat::Electron> ElectronZZStdIsoOverloader;

DEFINE_FWK_MODULE(MuonZZStdIsoOverloader);
DEFINE_FWK_MODULE(ElectronZZStdIsoOverloader);
DEFINE_FWK_MODULE(TauZZStdIsoOverloader);

