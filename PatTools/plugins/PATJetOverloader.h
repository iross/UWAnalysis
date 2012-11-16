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
// $Id: PATJetOverloader.h,v 1.1 2011/06/18 00:41:29 bachtis Exp $
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
#include "DataFormats/PatCandidates/interface/Jet.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration
#include <boost/foreach.hpp>
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/angle.h"


class PATJetOverloader : public edm::EDProducer {
   public:
  
  

  explicit PATJetOverloader(const edm::ParameterSet& iConfig):
  src_(iConfig.getParameter<edm::InputTag>("src"))
  {
    produces<pat::JetCollection>();
  }
  
  ~PATJetOverloader() {}
   private:

  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    std::auto_ptr<pat::JetCollection> jets(new pat::JetCollection);
    Handle<pat::JetCollection > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){
	pat::Jet jet = cands->at(i);
	float pt=0.0;
	float sumPt=0.0;
	float sumPt2=0.0;
	for(unsigned int j=0;j<jet.getPFConstituents().size();++j) {
	  pt = jet.getPFConstituents().at(j)->pt();
	  sumPt+=pt;
	  sumPt2+=pt*pt;
	}

	jet.addUserFloat("ptRMS",sqrt(sumPt2/(sumPt*sumPt)));
	jets->push_back(jet);

      }  
    
    iEvent.put(jets);

  } 

      // ----------member data ---------------------------
      edm::InputTag src_;


};

