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

// class decleration
//
template <typename T> 
class CandDaughterFetcher : public edm::EDProducer {

   public:
     explicit CandDaughterFetcher (const edm::ParameterSet& iConfig):
       src_(iConfig.getParameter<edm::InputTag>("src")),
       daughterToFetch_(iConfig.getUntrackedParameter<int>("daughter",2))
       {
	 produces<std::vector<T> >();
       }

      ~CandDaughterFetcher ()
	{

	}

   private:


      virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
	{
	  using namespace reco;
	  //Read the shallow clones of a candidate and save the SECOND Clone
	  std::auto_ptr<std::vector<T> > out(new std::vector<T> );
	  edm::Handle<std::vector<CompositePtrCandidateT1T2MEt<T,T> > > src;

	  if(iEvent.getByLabel(src_,src))
	    {

	      for(unsigned int j=0;j<src->size();++j) {
		if(daughterToFetch_==1) {
		  edm::Ptr<reco::Candidate> muPtr = src->at(j).leg1();
		  const T * muon  =  dynamic_cast<const T*>(muPtr.get());
		  out->push_back(*muon);
		}
		if(daughterToFetch_==2) {
		  edm::Ptr<reco::Candidate> muPtr = src->at(j).leg2();
		  const T * muon  =  dynamic_cast<const T*>(muPtr.get());
		  out->push_back(*muon);
		}

		if(daughterToFetch_==0) 
		  for(unsigned int k=0;k<src->at(j).numberOfSourceCandidatePtrs();++k)
		    {
			edm::Ptr<reco::Candidate> muPtr = src->at(j).sourceCandidatePtr(k); 
			const T * muon  =  dynamic_cast<const T*>(muPtr.get());
			out->push_back(*muon);
		    }
	      }
	    }
	    
	  iEvent.put(out);
	}

      virtual void endJob() { }
      edm::InputTag src_;
      int daughterToFetch_;
};
