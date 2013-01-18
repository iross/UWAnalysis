#include "UWAnalysis/NtupleTools/interface/NtupleFillerBaseMultiCand.h"

#include "FWCore/Framework/interface/MakerMacros.h"

//EDM_REGISTER_PLUGINFACTORY(NtupleFillerFactory, "NtupleFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MMMMFillerFactory, "MMMMFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EEEEFillerFactory, "EEEEFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MMEEFillerFactory, "MMEEFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EEMMFillerFactory, "EEMMFillerFactory");

EDM_REGISTER_PLUGINFACTORY(MMMTFillerFactory, "MMMTFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MMTTFillerFactory, "MMTTFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MMETFillerFactory, "MMETFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MMEMFillerFactory, "MMEMFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EEMTFillerFactory, "EEMTFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EETTFillerFactory, "EETTFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EEETFillerFactory, "EEETFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EEEMFillerFactory, "EEEMFillerFactory");

EDM_REGISTER_PLUGINFACTORY(EEEFillerFactory, "EEEFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EEMFillerFactory, "EEMFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MMEFillerFactory, "MMEFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MMMFillerFactory, "MMMFillerFactory");

EDM_REGISTER_PLUGINFACTORY(MMFillerFactory, "MMFillerFactory");
EDM_REGISTER_PLUGINFACTORY(EEFillerFactory, "EEFillerFactory");

EDM_REGISTER_PLUGINFACTORY(EFillerFactory, "EFillerFactory");
EDM_REGISTER_PLUGINFACTORY(MFillerFactory, "MFillerFactory");
EDM_REGISTER_PLUGINFACTORY(TFillerFactory, "TFillerFactory");
