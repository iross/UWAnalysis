#include "FWCore/Framework/interface/MakerMacros.h"
#include "UWAnalysis/NtupleTools/plugins/EventTreeMaker.h"

//4l
DEFINE_FWK_MODULE(MMMMEventTree);
DEFINE_FWK_MODULE(EEEEEventTree);
DEFINE_FWK_MODULE(MMEEEventTree);
DEFINE_FWK_MODULE(EEMMEventTree);

//2l2t
DEFINE_FWK_MODULE(MMMTEventTree);
DEFINE_FWK_MODULE(MMTTEventTree);
DEFINE_FWK_MODULE(MMETEventTree);
DEFINE_FWK_MODULE(MMEMEventTree);
DEFINE_FWK_MODULE(EEMTEventTree);
DEFINE_FWK_MODULE(EETTEventTree);
DEFINE_FWK_MODULE(EEETEventTree);
DEFINE_FWK_MODULE(EEEMEventTree);

//Z+l
DEFINE_FWK_MODULE(EEEEventTree);
DEFINE_FWK_MODULE(EEMEventTree);
DEFINE_FWK_MODULE(MMEEventTree);
DEFINE_FWK_MODULE(MMMEventTree);

//Z
DEFINE_FWK_MODULE(EEEventTree);
DEFINE_FWK_MODULE(MMEventTree);
