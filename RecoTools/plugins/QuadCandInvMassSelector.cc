#include "UWAnalysis/RecoTools/plugins/QuadCandInvMassSelector.h"

#include "DataFormats/Candidate/interface/Candidate.h" 

typedef QuadCandInvMassSelector<PATMuPair, PATDiTauPair> PATMuMuTauTauQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATMuPair, PATMuTauPair> PATMuMuMuTauQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATMuPair, PATElecTauPair> PATMuMuEleTauQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATMuPair, PATElecMuPair> PATMuMuEleMuQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATMuPair, PATElecPair> PATMuMuEleEleQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATMuPair, PATMuPair> PATMuMuMuMuQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATElecPair, PATElecTauPair> PATEleEleEleTauQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATElecPair, PATDiTauPair> PATEleEleTauTauQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATElecPair, PATElecPair> PATEleEleEleEleQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATElecPair, PATMuTauPair> PATEleEleMuTauQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATElecPair, PATElecMuPair> PATEleEleEleMuQuadInvMassSelector;
typedef QuadCandInvMassSelector<PATElecPair, PATMuPair> PATEleEleMuMuQuadInvMassSelector;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PATMuMuMuTauQuadInvMassSelector);
DEFINE_FWK_MODULE(PATMuMuTauTauQuadInvMassSelector);
DEFINE_FWK_MODULE(PATMuMuEleTauQuadInvMassSelector);
DEFINE_FWK_MODULE(PATMuMuEleMuQuadInvMassSelector);
DEFINE_FWK_MODULE(PATMuMuEleEleQuadInvMassSelector);
DEFINE_FWK_MODULE(PATMuMuMuMuQuadInvMassSelector);
DEFINE_FWK_MODULE(PATEleEleEleTauQuadInvMassSelector);
DEFINE_FWK_MODULE(PATEleEleTauTauQuadInvMassSelector);
DEFINE_FWK_MODULE(PATEleEleEleEleQuadInvMassSelector);
DEFINE_FWK_MODULE(PATEleEleMuTauQuadInvMassSelector);
DEFINE_FWK_MODULE(PATEleEleEleMuQuadInvMassSelector);
DEFINE_FWK_MODULE(PATEleEleMuMuQuadInvMassSelector);
