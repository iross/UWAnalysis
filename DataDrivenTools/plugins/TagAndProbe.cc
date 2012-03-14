// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/CompositeCandidate.h"
#include "DataFormats/RecoCandidate/interface/RecoChargedCandidate.h"
#include "DataFormats/Candidate/interface/ShallowCloneCandidate.h"
#include "DataFormats/Candidate/interface/CompositeCandidateFwd.h"

// class decleration
//

class TagAndProbe : public edm::EDProducer {

   public:
     explicit TagAndProbe (const edm::ParameterSet& iConfig):
       src_(iConfig.getParameter<edm::InputTag>("src"))
       {
	 produces<std::vector<reco::RecoChargedCandidate> >();
       }

      ~TagAndProbe ()
	{

	}

   private:
      virtual void beginJob(const edm::EventSetup& es) { }

      virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
	{
	  using namespace reco;
	  //Read the shallow clones of a candidate and save the SECOND Clone
	  std::auto_ptr<std::vector<RecoChargedCandidate> > out(new std::vector<RecoChargedCandidate> );
	  edm::Handle<CompositeCandidateCollection> collH;
	  if(iEvent.getByLabel(src_,collH))
	    {
	      if(collH->size()>0)
	      for(CompositeCandidateCollection::const_iterator i=collH->begin();
		  i!=collH->end();
		  ++i)
		    {
		      const  RecoChargedCandidate* leptonPtr = dynamic_cast<const RecoChargedCandidate*>(i->daughter("probe"));
		      RecoChargedCandidate lepton = *leptonPtr;
		      out->push_back(lepton);
		    }
	    }
	  iEvent.put(out);
	}

      virtual void endJob() { }
      edm::InputTag src_;
};


#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"

DEFINE_FWK_MODULE(TagAndProbe);
