#include "UWAnalysis/RecoTools/plugins/PATTauMatchSelector.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "UWAnalysis/RecoTools/plugins/DiCandidateSorterByZMass.h"

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
typedef DiCandidateSorterByZMass<PATEleEleEleSCQuad> PATEleEleEleSCQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleSCEleEleQuad> PATEleSCEleEleQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATMuMuEleSCQuad> PATMuMuEleSCQuadSorterByZMass;
typedef DiCandidateSorterByZMass<PATEleSCMuMuQuad> PATEleSCMuMuQuadSorterByZMass;


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
DEFINE_FWK_MODULE(PATEleEleEleSCQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleSCEleEleQuadSorterByZMass);
DEFINE_FWK_MODULE(PATMuMuEleSCQuadSorterByZMass);
DEFINE_FWK_MODULE(PATEleSCMuMuQuadSorterByZMass);
