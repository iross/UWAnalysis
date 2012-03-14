//Ovserloads the lepton with the rho factor


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "Math/GenVector/VectorUtil.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEtFwd.h"

// class decleration
//
template <typename T> 
class PATZZStdIsoOverloader : public edm::EDProducer {

   public:
     explicit PATZZStdIsoOverloader (const edm::ParameterSet& iConfig):
       src_(iConfig.getParameter<edm::InputTag>("src")),
       srcZZStdIso_(iConfig.getParameter<edm::InputTag>("srcZZStdIso"))
       {
	 produces<std::vector<T> >();
       }

      ~PATZZStdIsoOverloader ()
	{

	}

   private:


      virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
	{
	  using namespace reco;
	  //Read the shallow clones of a candidate and save the SECOND Clone
	  std::auto_ptr<std::vector<T> > out(new std::vector<T> );
	  edm::Handle<std::vector<T> > src;
	  
	  float rho = 0.0;

	  edm::Handle<double> srcZZStdIso;
	  if(iEvent.getByLabel(srcZZStdIso_,srcZZStdIso))
	    rho = *srcZZStdIso;


	  if(iEvent.getByLabel(src_,src))
	    for(unsigned int i=0;i<src->size();++i) {
	      T obj = src->at(i);
	      obj.addUserFloat( "rho", rho );
	      out->push_back(obj);
	    }
	    
	  iEvent.put(out);
	}

      virtual void endJob() { }

      edm::InputTag src_;
      edm::InputTag srcZZStdIso_;

};
