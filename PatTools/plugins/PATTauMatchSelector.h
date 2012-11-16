// -*- C++ -*-
//
// Package:    PATMuonTrackVetoSelector
// Class:      PATMuonTrackVetoSelector
// 
/**\class PATMuonTrackVetoSelector PATMuonTrackVetoSelector.cc UWAnalysis/PATMuonTrackVetoSelector/src/PATMuonTrackVetoSelector.cc

 Description: <one line class summary>

 Implementation:
     <Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
// $Id: PATTauMatchSelector.h,v 1.1.1.1 2010/04/16 10:07:30 bachtis Exp $
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration


template <class T>
class PATTauMatchSelector : public edm::EDProducer {
   public:

  

  explicit PATTauMatchSelector(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    ref_(iConfig.getParameter<edm::InputTag>("ref")),
    matchDR_(iConfig.getParameter<double>("matchDeltaR"))
     {
       produces<std::vector<T> >();
     }

  ~PATTauMatchSelector() {}
   private:



  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    
    Handle<edm::View<reco::Candidate> > ref;
    bool particlesExist = iEvent.getByLabel(ref_,ref);
    std::auto_ptr<std::vector<T> > out(new std::vector<T>);

    Handle<std::vector<T> > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){
	if(particlesExist)
	  for(edm::View<reco::Candidate>::const_iterator j=ref->begin();j!=ref->end();++j)
	    if(ROOT::Math::VectorUtil::DeltaR(j->p4(),cands->at(i).p4())<matchDR_)
	      out->push_back(cands->at(i));
      }
  
    
    iEvent.put(out);

  } 

      // ----------member data ---------------------------
      edm::InputTag src_;
      edm::InputTag ref_;
     double matchDR_;
};

