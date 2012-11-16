#include "UWAnalysis/PatTools/plugins/BestSelector.h"

#include "DataFormats/Candidate/interface/Candidate.h" 

typedef BestSelector<PATMuPair, PATElecPair> PATMuMuEleEleBestSelector;
typedef BestSelector<PATMuPair, PATElecPair> PATMuMuMuMuBestSelector;
typedef BestSelector<PATElecPair,PATMuPair> PATEleEleEleEleBestSelector;

typedef BestSelector<PATMuPair, PATDiTauPair> PATMuMuTauTauBestSelector;
typedef BestSelector<PATMuPair, PATMuTauPair> PATMuMuMuTauBestSelector;
typedef BestSelector<PATMuPair, PATElecTauPair> PATMuMuEleTauBestSelector;
typedef BestSelector<PATMuPair, PATElecMuPair> PATMuMuEleMuBestSelector;
typedef BestSelector<PATMuPair, PATElecPair> PATMuMuEleEleBestSelector;
//typedef BestSelector<PATMuPair, PATMuPair> PATMuMuMuMuBestSelector;
typedef BestSelector<PATElecPair, PATElecTauPair> PATEleEleEleTauBestSelector;
typedef BestSelector<PATElecPair, PATDiTauPair> PATEleEleTauTauBestSelector;
//typedef BestSelector<PATElecPair, PATElecPair> PATEleEleEleEleBestSelector;
typedef BestSelector<PATElecPair, PATMuTauPair> PATEleEleMuTauBestSelector;
typedef BestSelector<PATElecPair, PATElecMuPair> PATEleEleEleMuBestSelector;
typedef BestSelector<PATElecPair, PATMuPair> PATEleEleMuMuBestSelector;

#include "FWCore/Framework/interface/MakerMacros.h"

DEFINE_FWK_MODULE(PATMuMuMuTauBestSelector);
DEFINE_FWK_MODULE(PATMuMuTauTauBestSelector);
DEFINE_FWK_MODULE(PATMuMuEleTauBestSelector);
DEFINE_FWK_MODULE(PATMuMuEleMuBestSelector);
DEFINE_FWK_MODULE(PATMuMuEleEleBestSelector);
DEFINE_FWK_MODULE(PATMuMuMuMuBestSelector);
DEFINE_FWK_MODULE(PATEleEleEleTauBestSelector);
DEFINE_FWK_MODULE(PATEleEleTauTauBestSelector);
DEFINE_FWK_MODULE(PATEleEleEleEleBestSelector);
DEFINE_FWK_MODULE(PATEleEleMuTauBestSelector);
DEFINE_FWK_MODULE(PATEleEleEleMuBestSelector);
DEFINE_FWK_MODULE(PATEleEleMuMuBestSelector);
