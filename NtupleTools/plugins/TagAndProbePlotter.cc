#include "UWAnalysis/NtupleTools/plugins/TagAndProbePlotter.h"
#include "Math/GenVector/VectorUtil.h"
#include <string>
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"


typedef TagAndProbePlotter<PATMuTrackPair,pat::Muon> MuonTagAndProbePlotter;
typedef TagAndProbePlotter<PATMuTrackPair,pat::Tau> MuonMisIDTagAndProbePlotter;

typedef TagAndProbePlotter<PATEleTrackPair,pat::Electron> ElectronTrackTagAndProbePlotter;
typedef TagAndProbePlotter<PATElecSCPair,pat::Electron> ElectronSCTagAndProbePlotter;
typedef TagAndProbePlotter<PATElecPair,pat::Electron> ElectronTagAndProbePlotter;
typedef TagAndProbePlotter<PATEleTrackPair,pat::Tau> ElectronMisIDTagAndProbePlotter;


DEFINE_FWK_MODULE(MuonTagAndProbePlotter);
DEFINE_FWK_MODULE(MuonMisIDTagAndProbePlotter);

DEFINE_FWK_MODULE(ElectronTrackTagAndProbePlotter);
DEFINE_FWK_MODULE(ElectronSCTagAndProbePlotter);
DEFINE_FWK_MODULE(ElectronTagAndProbePlotter);
DEFINE_FWK_MODULE(ElectronMisIDTagAndProbePlotter);
