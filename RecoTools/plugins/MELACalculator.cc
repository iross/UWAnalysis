#include "UWAnalysis/RecoTools/plugins/MELACalculator.h"

#include "DataFormats/Candidate/interface/Candidate.h" 

typedef MELACalculator<PATMuPair, PATDiTauPair> PATMuMuTauTauMELACalculator;
typedef MELACalculator<PATMuPair, PATMuTauPair> PATMuMuMuTauMELACalculator;
typedef MELACalculator<PATMuPair, PATElecTauPair> PATMuMuEleTauMELACalculator;
typedef MELACalculator<PATMuPair, PATElecMuPair> PATMuMuEleMuMELACalculator;
typedef MELACalculator<PATMuPair, PATElecPair> PATMuMuEleEleMELACalculator;
typedef MELACalculator<PATMuPair, PATMuPair> PATMuMuMuMuMELACalculator;
typedef MELACalculator<PATElecPair, PATElecTauPair> PATEleEleEleTauMELACalculator;
typedef MELACalculator<PATElecPair, PATDiTauPair> PATEleEleTauTauMELACalculator;
typedef MELACalculator<PATElecPair, PATElecPair> PATEleEleEleEleMELACalculator;
typedef MELACalculator<PATElecPair, PATMuTauPair> PATEleEleMuTauMELACalculator;
typedef MELACalculator<PATElecPair, PATElecMuPair> PATEleEleEleMuMELACalculator;
typedef MELACalculator<PATElecPair, PATMuPair> PATEleEleMuMuMELACalculator;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PATMuMuMuTauMELACalculator);
DEFINE_FWK_MODULE(PATMuMuTauTauMELACalculator);
DEFINE_FWK_MODULE(PATMuMuEleTauMELACalculator);
DEFINE_FWK_MODULE(PATMuMuEleMuMELACalculator);
DEFINE_FWK_MODULE(PATMuMuEleEleMELACalculator);
DEFINE_FWK_MODULE(PATMuMuMuMuMELACalculator);
DEFINE_FWK_MODULE(PATEleEleEleTauMELACalculator);
DEFINE_FWK_MODULE(PATEleEleTauTauMELACalculator);
DEFINE_FWK_MODULE(PATEleEleEleEleMELACalculator);
DEFINE_FWK_MODULE(PATEleEleMuTauMELACalculator);
DEFINE_FWK_MODULE(PATEleEleEleMuMELACalculator);
DEFINE_FWK_MODULE(PATEleEleMuMuMELACalculator);
