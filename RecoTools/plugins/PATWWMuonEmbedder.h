// -*- C++ -*-
//
// Package:    PATMuonTrackVetoSelector
// Class:      PATMuonTrackVetoSelector
// 
//
// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
// $Id: PATWWMuonEmbedder.h,v 1.4 2011/11/25 14:53:45 bachtis Exp $
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
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration



class PATWWMuonEmbedder : public edm::EDProducer {
   public:

  

  explicit PATWWMuonEmbedder(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    srcVertices_(iConfig.getParameter<edm::InputTag>("srcVertices")),
    maxDxDy_(iConfig.getParameter<double>("maxDxDy")),
    maxChi2_(iConfig.getParameter<double>("maxChi2")),
    minTrackerHits_(iConfig.getParameter<int>("minTrackerHits")),
    minPixelHits_(iConfig.getParameter<int>("minPixelHits")),
    minMuonHits_(iConfig.getParameter<int>("minMuonHits")),
    minMatches_(iConfig.getParameter<int>("minMatches")),
    maxResol_(iConfig.getParameter<double>("maxResol")), 
    dz_(iConfig.getParameter<double>("dz"))

 {
    produces<pat::MuonCollection>();
  }
  
  ~PATWWMuonEmbedder() {}
   private:



  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;


    edm::Handle<reco::VertexCollection> vertexHandle;
    iEvent.getByLabel(srcVertices_, vertexHandle);


    
    std::auto_ptr<pat::MuonCollection > out(new pat::MuonCollection);

    
    Handle<pat::MuonCollection > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i){

	pat::Muon muon = cands->at(i);

	double d0=100.;
	double dz=100.0;
	TrackRef track = muon.innerTrack();



 	if(track.isNonnull())
	  if(vertexHandle->size()>0) {
	      d0 = track->dxy(vertexHandle->at(0).position());
	      dz = track->dz(vertexHandle->at(0).position());
	  }



	//find the number of station bits 
	unsigned int stationMask = (unsigned int)muon.stationMask(reco::Muon::SegmentAndTrackArbitration);
	int segs=0;
	for(unsigned int b=0;b<8;++b) {
	  unsigned int oper =1 << b; 

	  if((stationMask & oper) == oper)
	    segs++;
	}




	bool pass=true;

	if(!(muon.isGlobalMuon()&&muon.isTrackerMuon())) {pass=false;}

// 	if(pass)
// 	  if(!muon::isGoodMuon(muon,muon::GlobalMuonPromptTight)) {pass=false; }


	//	printf("Starting \n Dec=%d\n",pass);
	
	if(pass)
	if(!muon::isGoodMuon(muon,muon::AllArbitrated)) {pass=false;}

	//	printf("Dec=%d\n",pass);

	if(pass)
	  if(fabs(d0)>=maxDxDy_) {pass=false;}

	//	printf("Dec=%d\n",pass);

	if(pass)
	if(muon.globalTrack()->normalizedChi2()>=maxChi2_) {pass=false; }

	//	printf("Dec=%d\n",pass);

	if(pass)
	if(muon.innerTrack()->hitPattern().numberOfValidTrackerHits()<minTrackerHits_) {pass=false;}

	//	printf("Dec=%d\n",pass);

	if(pass)
	if(muon.innerTrack()->hitPattern().numberOfValidPixelHits()<minPixelHits_) {pass=false;}

	//	printf("Dec=%d\n",pass);

	if(pass)
	if(muon.innerTrack()->ptError()/muon.innerTrack()->pt()>=maxResol_) {pass=false; }

	//	printf("Dec=%d\n",pass);

	if(pass)
	if(!(muon.numberOfMatches()>=minMatches_ || segs>=minMatches_)) {pass=false; }

	///	printf("Dec=%d\n",pass);

	if(pass)
	  if( fabs(dz)>=dz_) {pass=false; }

	///	printf("Dec=%d\n",pass);
	
	if(pass)
	  muon.addUserFloat("isWWMuon",1.0);
	else
	  muon.addUserFloat("isWWMuon",0.0);
	out->push_back(muon);

      }
  
    
    iEvent.put(out);

  } 

      // ----------member data ---------------------------
      edm::InputTag src_;
      edm::InputTag srcVertices_;
      double maxDxDy_;
      double maxChi2_;
      int minTrackerHits_;
      int minPixelHits_;
      int minMuonHits_;
      int minMatches_;
      double maxResol_;
      double dz_;
};

