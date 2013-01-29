#include "FWCore/Framework/interface/MakerMacros.h"
#include "UWAnalysis/NtupleTools/plugins/StringBasedNtupleFiller.h"

//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTauPairFiller, "PATMuTauPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATGenParticleFiller, "PATGenParticleFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuJetPairFiller, "PATMuJetPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTauPairFiller, "PATEleTauPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATDiTauPairFiller, "PATDiTauPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleMuPairFiller, "PATEleMuPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATCandNuPairFiller, "PATCandNuPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuonNuPairFiller, "PATMuonNuPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuTrackPairFiller, "PATMuTrackPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleTrackPairFiller, "PATEleTrackPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuPairFiller, "PATMuPairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATElePairFiller, "PATElePairFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuonFiller, "PATMuonFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATPFMETFiller, "PATPFMETFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMETFiller, "PATMETFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATGenMETFiller, "PATGenMETFiller");

DEFINE_EDM_PLUGIN(MMMTFillerFactory, PATMuMuMuTauQuadFiller, "PATMuMuMuTauQuadFiller");
DEFINE_EDM_PLUGIN(MMTTFillerFactory, PATMuMuTauTauQuadFiller, "PATMuMuTauTauQuadFiller");
DEFINE_EDM_PLUGIN(MMETFillerFactory, PATMuMuEleTauQuadFiller, "PATMuMuEleTauQuadFiller");
DEFINE_EDM_PLUGIN(MMEMFillerFactory, PATMuMuEleMuQuadFiller, "PATMuMuEleMuQuadFiller");
DEFINE_EDM_PLUGIN(MMEEFillerFactory, PATMuMuEleEleQuadFiller, "PATMuMuEleEleQuadFiller");

DEFINE_EDM_PLUGIN(MMMMFillerFactory, PATMuMuMuMuQuadFiller, "PATMuMuMuMuQuadFiller");

DEFINE_EDM_PLUGIN(EEMTFillerFactory, PATEleEleMuTauQuadFiller, "PATEleEleMuTauQuadFiller");
DEFINE_EDM_PLUGIN(EETTFillerFactory, PATEleEleTauTauQuadFiller, "PATEleEleTauTauQuadFiller");
DEFINE_EDM_PLUGIN(EEETFillerFactory, PATEleEleEleTauQuadFiller, "PATEleEleEleTauQuadFiller");
DEFINE_EDM_PLUGIN(EEEMFillerFactory, PATEleEleEleMuQuadFiller, "PATEleEleEleMuQuadFiller");
DEFINE_EDM_PLUGIN(EEEEFillerFactory, PATEleEleEleEleQuadFiller, "PATEleEleEleEleQuadFiller");
DEFINE_EDM_PLUGIN(EEMMFillerFactory, PATEleEleMuMuQuadFiller, "PATEleEleMuMuQuadFiller");

//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleEleEleSCQuadFiller, "PATEleEleEleSCQuadFiller");

DEFINE_EDM_PLUGIN(EEEFillerFactory, PATEleEleEleTriFiller, "PATEleEleEleTriFiller");
DEFINE_EDM_PLUGIN(EEMFillerFactory, PATEleEleMuTriFiller, "PATEleEleMuTriFiller");
DEFINE_EDM_PLUGIN(MMEFillerFactory, PATMuMuEleTriFiller, "PATMuMuEleTriFiller");
DEFINE_EDM_PLUGIN(MMMFillerFactory, PATMuMuMuTriFiller, "PATMuMuMuTriFiller");

DEFINE_EDM_PLUGIN(EEFillerFactory, PATElePairFiller, "PATElePairFiller");
DEFINE_EDM_PLUGIN(MMFillerFactory, PATMuPairFiller, "PATMuPairFiller");

DEFINE_EDM_PLUGIN(EFillerFactory, PATEleFiller, "PATEleFiller");
DEFINE_EDM_PLUGIN(MFillerFactory, PATMuFiller, "PATMuFiller");
DEFINE_EDM_PLUGIN(TFillerFactory, PATTauFiller, "PATTauFiller");

//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATEleEleMuTriFiller, "PATEleEleMuTriFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuMuEleTriFiller, "PATMuMuEleTriFiller");
//DEFINE_EDM_PLUGIN(NtupleFillerFactory, PATMuMuMuTriFiller, "PATMuMuMuTriFiller");

