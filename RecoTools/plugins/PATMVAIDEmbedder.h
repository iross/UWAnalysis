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
// $Id: PATMVAIDEmbedder.h,v 1.1 2011/01/23 22:00:02 bachtis Exp $
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

#include "Math/GenVector/VectorUtil.h"
//
// class decleration



class PATMVAIDEmbedder : public edm::EDProducer {
	public:



		explicit PATMVAIDEmbedder(const edm::ParameterSet& iConfig):
			src_(iConfig.getParameter<edm::InputTag>("src")),
			id_(iConfig.getParameter<std::string>("id"))
	{
		produces<pat::ElectronCollection>();
	}

		~PATMVAIDEmbedder() {}
	private:



		virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
		{
			using namespace edm;
			using namespace reco;
			std::auto_ptr<pat::ElectronCollection > out(new pat::ElectronCollection);

			Handle<pat::ElectronCollection > cands;
			if(iEvent.getByLabel(src_,cands)) 
				for(unsigned int  i=0;i!=cands->size();++i){
					bool passID=false;
					//loop over electrons, embed MVA values
					pat::Electron electron = cands->at(i);
					//BDT eID ("non-triggered"), BDT>XX (fixed for practical reasons, comparisons ongoing, could still evolve)
					//5 < Pt < 10 GeV
					//|eta| < 0.8: BDT > 0.47
					//0.8< |eta| < 1.479: BDT > 0.004
					//|eta| > 1.479: BDT > 0.295
					//Pt > 10 GeV
					//|eta| < 0.8: BDT > 0.5
					//0.8 < |eta| < 1.479: BDT > 0.12
					//|eta| > 1.479: BDT > 0.6
					if (electron.pt()>5 && electron.pt()<10){
						if (fabs(electron.eta())<0.8) {
							if (electron.electronID(id_)>0.47) passID=true;
						} 
						else if (fabs(electron.eta())<1.479) {
							if (electron.electronID(id_)>0.004) passID=true;
						}
						else {
							if (electron.electronID(id_)>0.295) passID=true;
						}
					} else {
						if (fabs(electron.eta())<0.8 ) {
							if (electron.electronID(id_)>0.5) passID=true;
						} else if (fabs(electron.eta())<1.479) {
							if (electron.electronID(id_)>0.12) passID=true;
						} else {
							if (electron.electronID(id_)>0.6) passID=true;
						}
					}
					if(passID)
						electron.addUserFloat(id_+"Pass",1.0);
					else
						electron.addUserFloat(id_+"Pass",0.0);
					out->push_back(electron);
				}

			iEvent.put(out);
		}


		// ----------member data ---------------------------
		edm::InputTag src_;
		std::string id_;
};

