#include "UWAnalysis/RecoTools/plugins/PATTauMatchSelector.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "UWAnalysis/RecoTools/plugins/DiCandidateSorterByZMass.h"

//typedef DiCandidateSorterByZMass<PATMuTauPair> PATMuTauPairSorterByZMass;
//typedef DiCandidateSorterByZMass<PATMuPair> PATMuPairSorterByZMass;
//typedef DiCandidateSorterByZMass<PATElecPair> PATElePairSorterByZMass;
//typedef DiCandidateSorterByZMass<PATMuTrackPair> PATMuTrackPairSorterByZMass;
//typedef DiCandidateSorterByZMass<PATEleTrackPair> PATEleTrackPairSorterByZMass;
//typedef DiCandidateSorterByZMass<PATElecMuPair> PATEleMuPairSorterByZMass;
//typedef DiCandidateSorterByZMass<PATElecTauPair> PATEleTauPairSorterByZMass;
typedef DiCandidateSorterByZMass<PATMuMuMuTauQuad> PATMuMuMuTauQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATMuMuTauTauQuad> PATMuMuTauTauQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATMuMuEleTauQuad> PATMuMuEleTauQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATMuMuEleMuQuad> PATMuMuEleMuQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATMuMuMuMuQuad> PATMuMuMuMuQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATMuMuEleEleQuad> PATMuMuEleEleQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleEleEleTauQuad> PATEleEleEleTauQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleEleTauTauQuad> PATEleEleTauTauQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleEleEleEleQuad> PATEleEleEleEleQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleEleMuTauQuad> PATEleEleMuTauQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleEleEleMuQuad> PATEleEleEleMuQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleEleMuMuQuad> PATEleEleMuMuQuadSorterByZMass;


//DEFINE_FWK_MODULE(PATMuTauPairSorterByZMass);
//DEFINE_FWK_MODULE(PATMuPairSorterByZMass);
//DEFINE_FWK_MODULE(PATElePairSorterByZMass);
//DEFINE_FWK_MODULE(PATMuTrackPairSorterByZMass);
//DEFINE_FWK_MODULE(PATEleTrackPairSorterByZMass);
//DEFINE_FWK_MODULE(PATEleTauPairSorterByZMass);
//DEFINE_FWK_MODULE(PATEleMuPairSorterByZMass);
DEFINE_FWK_MODULE(PATMuMuMuTauQuadSorterByZMass);
DEFINE_FWK_MODULE(PATMuMuTauTauQuadSorterByZMass);
DEFINE_FWK_MODULE(PATMuMuEleTauQuadSorterByZMass);
DEFINE_FWK_MODULE(PATMuMuEleMuQuadSorterByZMass);
DEFINE_FWK_MODULE(PATMuMuMuMuQuadSorterByZMass);
DEFINE_FWK_MODULE(PATMuMuEleEleQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleEleEleTauQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleEleTauTauQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleEleEleEleQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleEleMuTauQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleEleEleMuQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleEleMuMuQuadSorterByZMass);
