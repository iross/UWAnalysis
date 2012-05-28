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
class CandJetFetcher : public edm::EDProducer {

   public:
     explicit CandJetFetcher (const edm::ParameterSet& iConfig):
       src_(iConfig.getParameter<edm::InputTag>("src"))
       {
	 produces<std::vector<pat::Jet> >();
       }

      ~CandJetFetcher ()
	{

	}

   private:


      virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
	{
	  using namespace reco;
	  //Read the shallow clones of a candidate and save the SECOND Clone
	  std::auto_ptr<std::vector<pat::Jet> > out(new std::vector<pat::Jet> );
	  edm::Handle<std::vector<T> > src;

	  if(iEvent.getByLabel(src_,src))
	    {

	      for(unsigned int j=0;j<src->size();++j) {
		for(unsigned int k=0;k<src->at(j).jets().size();++k)
		    {
		      edm::Ptr<pat::Jet> jetPtr = src->at(j).jets().at(k); 
		      const pat::Jet * jet  =  dynamic_cast<const pat::Jet*>(jetPtr.get());
		      out->push_back(*jet);
		    }
	      }
	    }
	    
	  iEvent.put(out);
	}

      virtual void endJob() { }
      edm::InputTag src_;

};
