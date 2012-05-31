/*  ---------------------
File: PATElectronMVAIsoEmbedder.h
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Embeds MVA isolation results, takes the relevant tag as input and adds tagPass as a userFloat
*/
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

class PATElectronMVAIsoEmbedder : public edm::EDProducer {
	public:



		explicit PATElectronMVAIsoEmbedder(const edm::ParameterSet& iConfig):
			src_(iConfig.getParameter<edm::InputTag>("src")),
			id_(iConfig.getParameter<std::string>("id"))
	{
		produces<pat::ElectronCollection>();
	}

		~PATElectronMVAIsoEmbedder() {}
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
					//pT < 10 && abs(eta) < 0.8 0.369 0.385
					//pT < 10 && 0.8 <= abs(eta) < 1.479 (Barrel) -0.025 -0.083
					//pT < 10 && abs(eta) > 1.479 ( Endcap ) 0.531 -0.573
					//pT >= 10 && abs(eta) < 0.8 0.735 0.413
					//pT >= 10 &&735 0.8 <= abs(eta) < 1.479 (Barrel) 0.467 0.271
					//pT >= 10 && abs(eta) > 1.479 ( Endcap ) 0.795 0.135
//					std::cout << "MVA iso " << id_ << "val: " << electron.userFloat(id_) << std::endl;
					if (electron.pt()>5 && electron.pt()<10){
						if (fabs(electron.eta())<0.8) {
							if (electron.userFloat(id_)>0.385) passID=true;
						} 
						else if (fabs(electron.eta())<1.479) {
							if (electron.userFloat(id_)>-0.083) passID=true;
						}
						else {
							if (electron.userFloat(id_)>-0.573) passID=true;
						}
					} else {
						if (fabs(electron.eta())<0.8 ) {
							if (electron.userFloat(id_)>0.413) passID=true;
						} else if (fabs(electron.eta())<1.479) {
							if (electron.userFloat(id_)>0.271) passID=true;
						} else {
							if (electron.userFloat(id_)>0.135) passID=true;
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

