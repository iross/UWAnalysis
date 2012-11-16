#include "UWAnalysis/PatTools/plugins/CandDaughterFetcher.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef CandDaughterFetcher<pat::Muon> MuonPairDaughterFetcher;

DEFINE_FWK_MODULE(MuonPairDaughterFetcher);

