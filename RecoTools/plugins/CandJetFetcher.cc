#include "UWAnalysis/RecoTools/plugins/CandJetFetcher.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef CandJetFetcher<PATMuonNuPair> MuonNuPairJetFetcher;
typedef CandJetFetcher<PATMuTauPair> MuonTauPairJetFetcher;
typedef CandJetFetcher<PATMuPair> MuonPairJetFetcher;


DEFINE_FWK_MODULE(MuonPairJetFetcher);
DEFINE_FWK_MODULE(MuonNuPairJetFetcher);
DEFINE_FWK_MODULE(MuonTauPairJetFetcher);

