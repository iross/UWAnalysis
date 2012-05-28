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
// $Id: PATWWMVAElectronEmbedder.h,v 1.2 2011/11/05 15:52:39 bachtis Exp $
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
#include "DataFormats/PatCandidates/interface/Electron.h"

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "UWAnalysis/RecoTools/interface/ElectronIDMVA.h"


#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "Utilities/General/interface/FileInPath.h"


#include "Math/GenVector/VectorUtil.h"
//
// class decleration



class PATWWMVAElectronEmbedder : public edm::EDProducer {
   public:

  

  explicit PATWWMVAElectronEmbedder(const edm::ParameterSet& iConfig):
    src_(iConfig.getParameter<edm::InputTag>("src")),
    srcVertices_(iConfig.getParameter<edm::InputTag>("srcVertices")),
    ebHits_(iConfig.getParameter<edm::InputTag>("ebHits")),
    eeHits_(iConfig.getParameter<edm::InputTag>("eeHits")),
    id_(iConfig.getParameter<std::string>("id")),
    DB_(iConfig.getParameter<double>("d0")),
    DZ_(iConfig.getParameter<double>("dz"))
  {
    produces<pat::ElectronCollection>();
    mva = new ElectronIDMVA();


    edm::FileInPath file1("UWAnalysis/Configuration/data/Subdet0LowPt_NoIPInfo_BDTG.weights.xml");
    edm::FileInPath file2("UWAnalysis/Configuration/data/Subdet1LowPt_NoIPInfo_BDTG.weights.xml");
    edm::FileInPath file3("UWAnalysis/Configuration/data/Subdet2LowPt_NoIPInfo_BDTG.weights.xml");
    edm::FileInPath file4("UWAnalysis/Configuration/data/Subdet0HighPt_NoIPInfo_BDTG.weights.xml");
    edm::FileInPath file5("UWAnalysis/Configuration/data/Subdet1HighPt_NoIPInfo_BDTG.weights.xml");
    edm::FileInPath file6("UWAnalysis/Configuration/data/Subdet2HighPt_NoIPInfo_BDTG.weights.xml");


    mva->Initialize("BDTG Method",
		    file1.fullPath(),
		    file2.fullPath(),
		    file3.fullPath(),
		    file4.fullPath(),
		    file5.fullPath(),
		    file6.fullPath(),
		    ElectronIDMVA::kNoIPInfo);
  }
  
  ~PATWWMVAElectronEmbedder() {}
   private:

  virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    using namespace edm;
    using namespace reco;
    std::auto_ptr<pat::ElectronCollection > out(new pat::ElectronCollection);

    edm::Handle<reco::BeamSpot> bsHandle;
    iEvent.getByLabel("offlineBeamSpot", bsHandle);
    const reco::BeamSpot &thebs = *bsHandle.product();

    edm::Handle<reco::VertexCollection> vtxHandle;
    iEvent.getByLabel(srcVertices_, vtxHandle);

    edm::Handle<reco::ConversionCollection> hConversions;
    iEvent.getByLabel("allConversions", hConversions);
    
    Handle<pat::ElectronCollection > cands;
    if(iEvent.getByLabel(src_,cands)) 
      for(unsigned int  i=0;i!=cands->size();++i)
	if(cands->at(i).isEB()||cands->at(i).isEE()) {
	  pat::Electron electron = cands->at(i);

	  bool passID =  !ConversionTools::hasMatchedConversion(electron,hConversions,thebs.position());

	  
	  if(electron.gsfTrack().isNonnull()) {
	    const reco::HitPattern& p_inner = electron.gsfTrack()->trackerExpectedHitsInner();
	    if(p_inner.numberOfHits()>0)
	      passID=false;

	    if(vtxHandle->size()>0) {
	      if(fabs(electron.dB())>DB_||electron.gsfTrack()->dz(vtxHandle->at(0).position())>DZ_)
		passID=false;
	    }
	    else
	      {
		passID=false;
	      }

	  }
	  else
	    {
	      passID=false;
	    }


	  EcalClusterLazyTools  lazyTools(iEvent,iSetup,ebHits_,eeHits_);


	  //get the MVA 
	  float mvaV = mva->MVAValue(&electron,lazyTools);

	  float pt = electron.pt();


	  if(electron.superCluster().isNonnull()) {
	    float eta = fabs(electron.superCluster()->eta());
	    
	    
	    if(pt<20 && eta<1 &&mvaV<0.133) passID=false;
	    if(pt<20 && eta>1.0 && eta<1.5 &&mvaV<0.465) passID=false;
	    if(pt<20 && eta>1.5 && eta<2.5 &&mvaV<0.518) passID=false;
	    
	    if(pt>20 && eta<1 &&mvaV<0.942) passID=false;
	    if(pt>20 && eta>1.0 && eta<1.5 &&mvaV<0.947) passID=false;
	    if(pt>20 && eta>1.5 && eta<2.5 &&mvaV<0.878) passID=false;
	  }
	  else
	    {
	      passID=false;
	    }
	  
	if(passID)
	  electron.addUserFloat(id_,1.0);
	else
	  electron.addUserFloat(id_,0.0);

	out->push_back(electron);

      }
  
    
    iEvent.put(out);

  } 

      // ----------member data ---------------------------
  edm::InputTag src_;
  edm::InputTag srcVertices_;
  edm::InputTag ebHits_;
  edm::InputTag eeHits_;
  ElectronIDMVA *mva;
  std::string id_;
  double DB_;
  double DZ_;


};

