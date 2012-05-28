// system include files
#include <memory>
#include "UWAnalysis/RecoTools/interface/SmearedParticleMaker.h"

#include "CondFormats/JetMETObjects/interface/JetCorrectionUncertainty.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "JetMETCorrections/Objects/interface/JetCorrectionsRecord.h"

class SmearedJetProducer : public edm::EDProducer  {
 public:
  explicit SmearedJetProducer(const edm::ParameterSet& iConfig);
  ~SmearedJetProducer();
    
 private:
  void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);

  
  // ----------member data ---------------------------
  edm::InputTag src_;           //input Collection
  int energyScaleDB_;
  
  SmearedParticleMaker<pat::Jet,GenJetRetriever<pat::Jet> > *smearingModule;
  
};



 

