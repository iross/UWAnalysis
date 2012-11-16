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
// $Id: PATPFMuonEmbedder.h,v 1.1 2010/09/24 16:57:19 bachtis Exp $
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



class PATPFMuonEmbedder : public edm::EDProducer {
   public:

  

  explicit PATPFMuonEmbedder(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    ref_(iConfig.getParameter<edm::InputTag>("ref"))
     {
       produces<pat::MuonCollection>();
     }

  ~PATPFMuonEmbedder() {}
   private:



  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    
    Handle<reco::PFCandidateCollection> ref;
    bool particlesExist = iEvent.getByLabel(ref_,ref);
    std::auto_ptr<pat::MuonCollection > out(new pat::MuonCollection);

    Handle<pat::MuonCollection > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){
	pat::Muon muon = cands->at(i);
	bool matched=false;
	if(muon.track().isNonnull())
	  for(reco::PFCandidateCollection::const_iterator j=ref->begin();j!=ref->end();++j)
	    //	  if(ROOT::Math::VectorUtil::DeltaR(j->p4(),muon.p4())<0.1)
	    if(muon.track()==j->muonRef()->track())
	    {
	      matched=true;
	      edm::Ref<reco::PFCandidateCollection> refCand(ref,j-ref->begin());
	      muon.setPFCandidateRef(refCand);
	      muon.addUserFloat("isPFMuon",1.0);
	      break;
	    }
	
	if(!matched)
	      muon.addUserFloat("isPFMuon",0.0);
	  
	out->push_back(muon);

      }
  
    
    iEvent.put(out);

  } 

      // ----------member data ---------------------------
      edm::InputTag src_;
      edm::InputTag ref_;

};

