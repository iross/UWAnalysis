// system include files
#include <memory>
#include "UWAnalysis/RecoTools/interface/SmearedParticleMaker.h"

class SmearedTauProducer : public edm::EDProducer  {
 public:
  explicit SmearedTauProducer(const edm::ParameterSet& iConfig);
  ~SmearedTauProducer();
    
 private:
  void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);

  
  // ----------member data ---------------------------
  edm::InputTag src_;           //input Collection
  bool smearConstituents_;
  double hadronEnergyScale_;
  double gammaEnergyScale_;
  
  SmearedParticleMaker<pat::Tau,GenJetRetriever<pat::Tau> > *smearingModule;
  
};



 

