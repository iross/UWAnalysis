#include "UWAnalysis/RecoTools/interface/CompositePtrCandidateTMEtProducer.h"

#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

typedef CompositePtrCandidateTMEtProducer<pat::Muon> PATMuonNuPairProducer;
typedef CompositePtrCandidateTMEtProducer<reco::Candidate> PATCandNuPairProducer;
#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PATMuonNuPairProducer);
DEFINE_FWK_MODULE(PATCandNuPairProducer);
