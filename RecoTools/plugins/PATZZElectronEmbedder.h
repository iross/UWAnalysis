// -*- C++ -*-
//
// Package:    PATElectronTrackVetoSelector
// Class:      PATElectronTrackVetoSelector
// 
/**\class PATElectronTrackVetoSelector PATMuonTrackVetoSelector.cc UWAnalysis/PATMuonTrackVetoSelector/src/PATMuonTrackVetoSelector.cc

Description: <one line class summary>

Implementation:
<Notes on implementation>
*/
//
// Original Author:  Michail Bachtis
//         Created:  Sun Jan 31 15:04:57 CST 2010
// $Id: PATZZElectronEmbedder.h,v 1.1 2011/10/08 14:06:14 Joshua Exp $
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


#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "TrackingTools/TransientTrack/interface/TransientTrack.h"
#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/IPTools/interface/IPTools.h"
#include "RecoVertex/PrimaryVertexProducer/interface/PrimaryVertexSorter.h"
#include "DataFormats/GeometryCommonDetAlgo/interface/Measurement1D.h"
#include "DataFormats/Common/interface/RefToBase.h"



#include "Math/GenVector/VectorUtil.h"
//
// class decleration



class PATZZElectronEmbedder : public edm::EDProducer {
	public:

		explicit PATZZElectronEmbedder(const edm::ParameterSet& iConfig):
			src_(iConfig.getParameter<edm::InputTag>("src"))
	{
		produces<pat::ElectronCollection>();
	}

		~PATZZElectronEmbedder() {}
	private:



		virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			using namespace edm;
			using namespace reco;
			GsfTrackRef eletrack;
			double tempsip3D;
			Handle<reco::BeamSpot> beamSpotHandle;
			if (!iEvent.getByLabel(InputTag("offlineBeamSpot"), beamSpotHandle)) {
				LogTrace("") << ">>> No beam spot found !!!";
				return;
			}
			edm::ESHandle<TransientTrackBuilder> trackBuilder;
			iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder",trackBuilder);

			std::vector<reco::TransientTrack> transientTracks;

			reco::Vertex primVertex;
			edm::Handle<reco::VertexCollection> recoPVCollection;
			iEvent.getByLabel(InputTag("offlinePrimaryVertices"), recoPVCollection);
			PrimaryVertexSorter pvs;
			bool pvfound = (recoPVCollection->size() != 0);
			if (pvfound){
				std::vector<reco::Vertex> sortedList = pvs.sortedList( *recoPVCollection.product() );
				primVertex = (sortedList.front());
			} else {
				//make dummy PV
				reco::Vertex::Point p(0,0,0);
				reco::Vertex::Error e;
				e(0,0) = 0.0015*0.0015;
				e(1,1) = 0.0015*0.0015;
				e(2,2) = 15.*15.;
				primVertex = reco::Vertex(p,e,1,1,1);
			}
			std::pair<bool,Measurement1D> z1l1IPpair;
			reco::TransientTrack eletranstrack;

			std::auto_ptr<pat::ElectronCollection > out(new pat::ElectronCollection);
			Handle<pat::ElectronCollection > cands;

			if(iEvent.getByLabel(src_,cands)) 
				for(unsigned int  i=0;i!=cands->size();++i){
					pat::Electron electron = cands->at(i);
					eletrack = electron.gsfTrack();
					bool passID=false;
					tempsip3D=-137;
					eletranstrack = trackBuilder->build(eletrack);
					z1l1IPpair = IPTools::absoluteImpactParameter3D(eletranstrack, primVertex);
					if (z1l1IPpair.first) tempsip3D  = z1l1IPpair.second.significance();

					if(passID)
						electron.addUserFloat("isZZElectron",1.0);
					else
						electron.addUserFloat("isZZElectron",0.0);
					std::cout << "Electron sip: " << tempsip3D << std::endl;
					electron.addUserFloat("SIP3D",tempsip3D);
					out->push_back(electron);
					std::cout << "pt:" << electron.pt() << std::endl;
					std::cout << "ecal:" << electron.ecalIso() << std::endl;
					std::cout << "hcal:" << electron.hcalIso() << std::endl;
					std::cout << "tracker:" << electron.trackIso() << std::endl;
				}


			iEvent.put(out);

		} 

		// ----------member data ---------------------------
		edm::InputTag src_;
};

