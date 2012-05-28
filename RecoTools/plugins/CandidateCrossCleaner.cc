#include "UWAnalysis/RecoTools/plugins/CandidateCrossCleaner.h"
#include "FWCore/Framework/interface/MakerMacros.h"

typedef CandidateCrossCleaner<reco::RecoChargedCandidate,PATMuPair> TrackCrossCleanerFromDiMuon;
typedef CandidateCrossCleaner<pat::Tau,DiCandidatePair> TauCleanerFromDiMuon;

