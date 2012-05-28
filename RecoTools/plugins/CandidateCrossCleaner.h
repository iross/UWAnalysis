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
template <typename T,typename G> 
class CandidateCrossCleaner : public edm::EDProducer {

   public:
     explicit CandidateCrossCleaner (const edm::ParameterSet& iConfig):
       src_(iConfig.getParameter<edm::InputTag>("src")),
       ref_(iConfig.getParameter<edm::InputTag>("ref")),
       matchDR_(iConfig.getParameter<double>("matchDeltaR"))
       {
	 produces<std::vector<T> >();
       }

      ~CandidateCrossCleaner ()
	{

	}

   private:
      virtual void beginJob(const edm::EventSetup& es) { }

      virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
	{
	  using namespace reco;
	  //Read the shallow clones of a candidate and save the SECOND Clone
	  std::auto_ptr<std::vector<T> > out(new std::vector<T> );
	  edm::Handle<std::vector<G> > ref;
	  edm::Handle<std::vector<T> > src;

	  if(iEvent.getByLabel(src_,src))
	    if(iEvent.getByLabel(ref_,ref))
	    {

	      for(unsigned int j=0;j<src->size();++j) {
		bool keep=true;

		for( unsigned int i=0;i<ref->size();++i)
		  for(unsigned int k=0;k<ref->at(i).numberOfSourceCandidatePtrs();++k)
		    {
		      edm::Ptr<reco::Candidate> muPtr = ref->at(i).sourceCandidatePtr(k); 
		      if(ROOT::Math::VectorUtil::DeltaR(src->at(j).p4(),muPtr->p4())<matchDR_)
			keep=false;
		    }

		if(keep)
		  out->push_back(src->at(j));
	      }
	    
	      iEvent.put(out);
	    }
	}
      virtual void endJob() { }
      edm::InputTag src_;
      edm::InputTag ref_;
      double matchDR_;

};
