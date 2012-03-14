#include "FWCore/Framework/interface/MakerMacros.h"
#include "UWAnalysis/NtupleTools/plugins/VertexFillerDicand.h"

DEFINE_EDM_PLUGIN(NtupleFillerFactory, MuMuVertexFiller, "MuMuVertexFiller");
DEFINE_EDM_PLUGIN(NtupleFillerFactory, EleEleVertexFiller, "EleEleVertexFiller");
