#ifndef TauAnalysis_SmearedParticleProducer
#define TauAnalysis_SmearedParticleProducer
/* Smeared Particle Producer 
Module that changes the energy scale PT, ETA 
for a general PAT Particle 
Author : Michail Bachtis 
University of Wisconsin
*/
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Utilities/interface/Exception.h"
#include "UWAnalysis/RecoTools/interface/SmearedParticleMaker.h"

template <typename T,typename G>
class SmearedParticleProducer : public edm::EDProducer {
   public:
  explicit SmearedParticleProducer(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src"))  
    {
      smearingModule = new SmearedParticleMaker<T,G>(iConfig);
      produces<std::vector<T> >();

    }
  ~SmearedParticleProducer() 
    {

    }
    
   protected:
    
     virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup) {
       using namespace edm;
       
       std::auto_ptr<std::vector<T> > out(new std::vector<T> );
       Handle<std::vector<T> > srcH;
       
       if(iEvent.getByLabel(src_,srcH)) 
	 for(unsigned int i=0;i<srcH->size();++i) {
	   T object = srcH->at(i);
	   smearingModule->smear(object);
	   out->push_back(object);
	 }
       iEvent.put(out);
     } 


      edm::InputTag src_;           //input Collection
      SmearedParticleMaker<T,G> *smearingModule;
};


#endif
