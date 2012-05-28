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
// $Id: PATMuonIpProducer.h,v 1.2 2011/05/26 09:04:35 bachtis Exp $
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

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration



class PATMuonIpProducer : public edm::EDProducer {
   public:

  

  explicit PATMuonIpProducer(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    vertex_(iConfig.getParameter<edm::InputTag>("vertices"))
     {
       produces<std::vector<pat::Muon> >();
     }

  ~PATMuonIpProducer() {}
   private:



  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    
    Handle<reco::VertexCollection> vertices;
    bool verticesExist = iEvent.getByLabel(vertex_,vertices);

    if(verticesExist)
      verticesExist*=(vertices->size()>0)&&(vertices->at(0).isValid());

    std::auto_ptr<std::vector<pat::Muon> > out(new std::vector<pat::Muon>);
    Handle<std::vector<pat::Muon> > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){
	pat::Muon mu = cands->at(i);

	if(verticesExist) {
	  if(mu.innerTrack().isNonnull()) {
	    mu.addUserFloat("dxy",mu.innerTrack()->dxy(vertices->at(0).position()));
	    mu.addUserFloat("dz",mu.innerTrack()->dz(vertices->at(0).position()));

	  }
	  else {
	    mu.addUserFloat("dxy",-500.);
	    mu.addUserFloat("dz",-500.);
	  }
	}
	else
	  {
	    mu.addUserFloat("dxy",-500.);
	    mu.addUserFloat("dz",-500.);

	  }
	out->push_back(mu);
      }
      
    iEvent.put(out);

  } 

      // ----------member data ---------------------------
      edm::InputTag src_;
      edm::InputTag vertex_;

};

