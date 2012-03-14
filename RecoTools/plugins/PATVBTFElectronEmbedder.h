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
// $Id: PATVBTFElectronEmbedder.h,v 1.1 2011/01/23 22:00:02 bachtis Exp $
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



class PATVBTFElectronEmbedder : public edm::EDProducer {
	public:



		explicit PATVBTFElectronEmbedder(const edm::ParameterSet& iConfig):
			src_(iConfig.getParameter<edm::InputTag>("src")),
			sigmaEtaEta_(iConfig.getParameter<std::vector<double> >("sigmaEtaEta")),
			deltaEta_(iConfig.getParameter<std::vector<double> >("deltaEta")),
			deltaPhi_(iConfig.getParameter<std::vector<double> >("deltaPhi")),
			hoE_(iConfig.getParameter<std::vector<double> >("hoE")),
			id_(iConfig.getParameter<std::string>("id"))
	{
		produces<pat::ElectronCollection>();
	}

		~PATVBTFElectronEmbedder() {}
	private:



		virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			using namespace edm;
			using namespace reco;
			std::auto_ptr<pat::ElectronCollection > out(new pat::ElectronCollection);

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
			Handle<pat::ElectronCollection > cands;
			if(iEvent.getByLabel(src_,cands)) 
				for(unsigned int  i=0;i!=cands->size();++i){
				
					if(cands->at(i).isEB()||cands->at(i).isEE()) {
						pat::Electron electron = cands->at(i);
						//if ((electron.electronID("cicTight")==1||electron.electronID("cicTight")==3||electron.electronID("cicTight")==5||electron.electronID("cicTight")==7||electron.electronID("cicTight")==9||electron.electronID("cicTight")==11||electron.electronID("cicTight")==13||electron.electronID("cicTight")==15)&&electron.userFloat("SIP3D")<100&&electron.pt()>20&&electron.eta()<2.5&&electron.gsfTrack()->trackerExpectedHitsInner().numberOfLostHits()<2) std::cout<< iEvent.id().event() << "\t" << electron.pt() << "\t" << electron.eta() << "\tCiCTight: " << electron.electronID("cicTight") << "\t" << electron.userFloat("SIP3D") << std::endl; 
						//std::cout << electron.electronID("cicTight") << std::endl;
						//std::cout << electron.pt() << std::endl;
//					std::cout << "pt:" << electron.pt() << std::endl;
//					std::cout << "ecal:" << electron.ecalIso() << " " << electron.ecalIso()/electron.pt() << std::endl;
//					std::cout << "ecal2: " << electron.dr03EcalRecHitSumEt()/electron.pt() << std::endl;
//					std::cout << "userIsos:" << electron.userIso(0) << " " <<  electron.userIso(1) << " " << electron.userIso(2) << " " << electron.userIso(3) << std::endl;
//					std::cout << "hcal:" << electron.hcalIso() << " " << electron.hcalIso()/electron.pt() << std::endl;
//					std::cout << "tracker:" << electron.trackIso() << " " << electron.trackIso()/electron.pt()  << std::endl;
						eletrack = electron.gsfTrack();
						tempsip3D=-137;
						eletranstrack = trackBuilder->build(eletrack);
						z1l1IPpair = IPTools::absoluteImpactParameter3D(eletranstrack, primVertex);
						if (z1l1IPpair.first) tempsip3D  = z1l1IPpair.second.significance();	

						bool passID=false;
						unsigned int type=0;
						if(electron.isEE()) type=1;

						if(fabs(electron.sigmaIetaIeta())<sigmaEtaEta_[type]) 
							if(fabs(electron.deltaEtaSuperClusterTrackAtVtx())<deltaEta_[type]) 
								if(fabs(electron.deltaPhiSuperClusterTrackAtVtx())<deltaPhi_[type]) 
									if(fabs(electron.hcalOverEcal())<hoE_[type]) 
										passID=true;



						if(passID)
							electron.addUserFloat(id_,1.0);
						else
							electron.addUserFloat(id_,0.0);
						electron.addUserFloat("SIP3D",tempsip3D);
						out->push_back(electron);

					}
				}

			iEvent.put(out);

		} 

		// ----------member data ---------------------------
		edm::InputTag src_;
		std::vector<double>  sigmaEtaEta_;
		std::vector<double>  deltaEta_;
		std::vector<double>  deltaPhi_;
		std::vector<double>  hoE_;
		std::string id_;
};

