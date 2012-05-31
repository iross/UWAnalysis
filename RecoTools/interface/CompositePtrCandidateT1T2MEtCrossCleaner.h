#ifndef UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtCrossCleaner_h
#define UWAnalysis_RecoTools_CompositePtrCandidateT1T2MEtCrossCleaner_h



#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "UWAnalysis/RecoTools/interface/FetchCollection.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"

#include "UWAnalysis/RecoTools/interface/CompositePtrCandidateT1T2MEtAlgorithm.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <string>

template<typename T1, typename T2>
class CompositePtrCandidateT1T2MEtCrossCleaner : public edm::EDProducer 
{
  typedef edm::Ptr<T1> T1Ptr;
  typedef edm::Ptr<T2> T2Ptr;

  typedef std::vector<CompositePtrCandidateT1T2MEt<T1,T2> > CompositePtrCandidateCollection;
  
 public:

  explicit CompositePtrCandidateT1T2MEtCrossCleaner(const edm::ParameterSet& cfg)
  {

    src_ = cfg.getParameter<edm::InputTag>("src");
    dR_ = cfg.getParameter<double>("dR");
    
    produces<CompositePtrCandidateCollection>("");
  }

  ~CompositePtrCandidateT1T2MEtCrossCleaner() {}

  void produce(edm::Event& evt, const edm::EventSetup& es)
  {

    typedef edm::View<CompositePtrCandidateT1T2MEt<T1,T2> > TView;
    edm::Handle<TView> collection;
    pf::fetchCollection(collection, src_, evt);
  
    std::auto_ptr<CompositePtrCandidateCollection> compositePtrCandidateCollection(new CompositePtrCandidateCollection());

    //Cross clean by C++ pointer 
    //Also by Delta R if the user wants 

    for(unsigned int i=0;i<collection->size();++i) {
      CompositePtrCandidateT1T2MEt<T1,T2> cand = collection->at(i);
//      if(cand.leg1()->leg1().id()!=cand.leg2()->leg1().id())
	if(deltaR(*cand.leg1()->leg1(),*cand.leg2()->leg1())>dR_)
//	  if(cand.leg1()->leg1().id()!=cand.leg2()->leg2().id())
	    if(deltaR(*cand.leg1()->leg1(),*cand.leg2()->leg2())>dR_)
//	      if(cand.leg1()->leg2().id()!=cand.leg2()->leg1().id())
		if(deltaR(*cand.leg1()->leg2(),*cand.leg2()->leg1())>dR_)
//		  if(cand.leg1()->leg2().id()!=cand.leg2()->leg2().id())
		    if(deltaR(*cand.leg1()->leg2(),*cand.leg2()->leg2())>dR_)
		      compositePtrCandidateCollection->push_back(cand);

      }



    evt.put(compositePtrCandidateCollection);
  }

 private:

  edm::InputTag src_;
  double dR_;

};

#endif

