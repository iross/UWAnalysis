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
// $Id: PATTauOverloader.h,v 1.2 2011/11/03 18:32:57 bachtis Exp $
//
//
#include "PhysicsTools/JetMCUtils/interface/JetMCTag.h"

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/TauReco/interface/PFTau.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Tau.h"


#include "DataFormats/TrackReco/interface/TrackFwd.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrackFwd.h"
#include "DataFormats/TrackReco/interface/Track.h"
#include "DataFormats/GsfTrackReco/interface/GsfTrack.h"


#include "Math/GenVector/VectorUtil.h"
//
// class decleration
#include <boost/foreach.hpp>
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/angle.h"


class PATTauOverloader : public edm::EDProducer {
   public:
  
  

  explicit PATTauOverloader(const edm::ParameterSet& iConfig):
  src_(iConfig.getParameter<edm::InputTag>("src"))
  {
    produces<pat::TauCollection>();
  }
  
  ~PATTauOverloader() {}
   private:

  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    std::auto_ptr<pat::TauCollection> taus(new pat::TauCollection);
    Handle<pat::TauCollection > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){
	pat::Tau tau = cands->at(i);
	//add track Momentum
	if (tau.leadPFChargedHadrCand().isNonnull()) {
	  if(tau.leadPFChargedHadrCand()->trackRef().isNonnull())
	    tau.addUserFloat("leadingChargedKFP",tau.leadPFChargedHadrCand()->trackRef()->p());
	  else
	    tau.addUserFloat("leadingChargedKFP",-1.);
	  
	  if(tau.leadPFChargedHadrCand()->gsfTrackRef().isNonnull())
	    tau.addUserFloat("leadingChargedGSFP",tau.leadPFChargedHadrCand()->gsfTrackRef()->p());
	  else
	    tau.addUserFloat("leadingChargedGSFP",-1.);
	}

	if (tau.leadPFChargedHadrCand().isNonnull()) {
	  float eta = tau.leadPFChargedHadrCand()->positionAtECALEntrance().eta();

	  bool InCrack =  (eta < 0.018 ||
			       (eta>0.423 && eta<0.461) ||
			       (eta>0.770 && eta<0.806) ||
			       (eta>1.127 && eta<1.163) ||
			       (eta>1.460 && eta<1.558));

	  if(InCrack) {
	    tau.addUserFloat("crackVeto",0.);
	  }
	  else
	    {
	      tau.addUserFloat("crackVeto",1.);
	    }
	}
	else
	  {
	    tau.addUserFloat("crackVeto",0.);
	  }
      

	if(tau.leadPFCand().isNonnull()&&tau.leadPFCand()->trackRef().isNonnull()) {
	  tau.addUserFloat("leadingKFP",tau.leadPFCand()->trackRef()->p());
	}
	else {
	  tau.addUserFloat("leadingKFP",-1.);
	}


	if(tau.leadPFCand().isNonnull()&&tau.leadPFCand()->gsfTrackRef().isNonnull()) {
	  tau.addUserFloat("leadingGSFP",tau.leadPFCand()->gsfTrackRef()->p());
	}
	else {
	  tau.addUserFloat("leadingGSFP",-1.);
	}
	  
	  if(tau.leadPFCand().isNonnull()&&tau.leadPFCand()->charge()!=0) {
	    tau.addUserFloat("leadingMVA",tau.leadPFCand()->mva_e_pi());

	    if(tau.leadPFCand()->gsfTrackRef().isNonnull())
	      tau.addUserFloat("pixelHits",tau.leadPFCand()->gsfTrackRef()->trackerExpectedHitsInner().numberOfHits());
	    else
	      tau.addUserFloat("pixelHits",-1.);

	  }
	  else if(tau.leadPFChargedHadrCand().isNonnull()) {
	    tau.addUserFloat("leadingMVA",tau.leadPFChargedHadrCand()->mva_e_pi());

	    if(tau.leadPFChargedHadrCand()->gsfTrackRef().isNonnull())
	      tau.addUserFloat("pixelHits",tau.leadPFChargedHadrCand()->gsfTrackRef()->trackerExpectedHitsInner().numberOfHits());
	    else
	      tau.addUserFloat("pixelHits",-1.);
	  }
	//add brem strip
	float bremEnergy=0;
	float emEnergy=0;
	float refEta=0.0;
	
	if(tau.leadPFCand().isNonnull()&&tau.leadPFCand()->charge()!=0)
	  refEta=tau.leadPFCand()->eta();
	else if(tau.leadPFChargedHadrCand().isNonnull())
	  refEta=tau.leadPFChargedHadrCand()->eta();
	for(unsigned int Nc = 0 ;Nc < tau.signalPFGammaCands().size();++Nc)
	  {
	    PFCandidateRef cand = tau.signalPFGammaCands().at(Nc);
	    if(fabs(refEta-cand->eta())<0.03)
	      bremEnergy+=cand->energy();
	    emEnergy+=cand->energy();
	  }

	if(emEnergy>0)
	  tau.addUserFloat("bremEnergy",bremEnergy/emEnergy);
	else
	  tau.addUserFloat("bremEnergy",-1.);
	  
	taus->push_back(tau);
      }
     
    iEvent.put(taus);
  } 

      // ----------member data ---------------------------
      edm::InputTag src_;


};

