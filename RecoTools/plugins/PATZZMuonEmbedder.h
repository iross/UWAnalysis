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
// $Id: PATZZMuonEmbedder.h,v 1.1 2011/10/08 14:06:14 Joshua Exp $
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


#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration



class PATZZMuonEmbedder : public edm::EDProducer {
   public:

  

  explicit PATZZMuonEmbedder(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    maxChi2_(iConfig.getParameter<double>("maxChi2")),
    minTrackerHits_(iConfig.getParameter<int>("minTrackerHits")),
    minMuonHits_(iConfig.getParameter<int>("minMuonHits")),
    minMatches_(iConfig.getParameter<int>("minMatches"))
  {
    produces<pat::MuonCollection>();
  }
  
  ~PATZZMuonEmbedder() {}
   private:



  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;

    Handle<reco::BeamSpot> beamSpotHandle;
    if (!iEvent.getByLabel(InputTag("offlineBeamSpot"), beamSpotHandle)) {
      LogTrace("") << ">>> No beam spot found !!!";
      return;
    }
    
    std::auto_ptr<pat::MuonCollection > out(new pat::MuonCollection);

    
    Handle<pat::MuonCollection > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){
	pat::Muon muon = cands->at(i);

	bool passID=false;

	if(muon.isGlobalMuon()&&muon.isTrackerMuon()) 
	    if(muon.globalTrack()->normalizedChi2()<maxChi2_)
	      if(muon.innerTrack()->hitPattern().numberOfValidTrackerHits()>=minTrackerHits_)
		    if(muon.numberOfMatches()>=minMatches_)
		    passID=true;

	if(passID)
	  muon.addUserFloat("isZZMuon",1.0);
	else
	  muon.addUserFloat("isZZMuon",0.0);
	out->push_back(muon);

      }
  
    
    iEvent.put(out);

  } 

      // ----------member data ---------------------------
      edm::InputTag src_;
      double maxChi2_;
      int minTrackerHits_;
      int minMuonHits_;
      int minMatches_;
};

