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
// $Id: PATTauOverloader.h,v 1.1 2011/03/03 15:24:08 bachtis Exp $
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
#include "DataFormats/MuonReco/interface/MuonSelectors.h"
#include "DataFormats/PatCandidates/interface/Tau.h"

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
    dmMap["electron"] = 11;
    dmMap["muon"] = 13;
    dmMap["oneProng0Pi0"] = 1;
    dmMap["oneProng1Pi0"] = 2;
    dmMap["oneProng2Pi0"] = 3;
    dmMap["oneProngOther"] = 4;
    dmMap["threeProng0Pi0"] = 5;
    dmMap["threeProng1Pi0"] = 6;
    dmMap["threeProngOther"] = 7;
    dmMap["rare"] = 8;

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
	
	int mcDecayMode=0;
	float genJetPt=0.0;
	float genJetEta=0.0;

	if(tau.genJet()!=0) {
	  //save MC decay mode
	  std::string dm = JetMCTagUtils::genTauDecayMode(*tau.genJet());
	  mcDecayMode = dmMap[dm];
	  genJetPt = tau.genJet()->pt();
	  genJetEta = tau.genJet()->eta();
	}

	tau.addUserInt("mcDecayMode",mcDecayMode);
	tau.addUserFloat("genJetPt",genJetPt);
	tau.addUserFloat("genJetEta",genJetEta);
	taus->push_back(tau);

      }  
    
    iEvent.put(taus);

  } 

      // ----------member data ---------------------------
      edm::InputTag src_;
      std::map<std::string,int> dmMap;

};

