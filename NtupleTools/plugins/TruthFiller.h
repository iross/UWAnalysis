// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include <TTree.h>

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h" 
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//
// class decleration
//
template<typename T>
class TruthFiller : public NtupleFillerBase {
	public:
		TruthFiller(){
		}


		TruthFiller(const edm::ParameterSet& iConfig, TTree* t):
			NtupleFillerBase(iConfig,t),
			src_(iConfig.getParameter<edm::InputTag>("src")),
			gensrc_(iConfig.getParameter<edm::InputTag>("gensrc")),
			var_(iConfig.getParameter<std::string>("method")),
			tag_(iConfig.getParameter<std::string>("tag")),
			leadingOnly_(iConfig.getUntrackedParameter<bool>("leadingOnly",true))
	{
		hPt = 0;
		hMass = 0;
		hEta = 0;
		hPhi = 0;
		for (int i = 0; i < 5; i++) {
			zPt[i]=0;
			zMass[i]=0;
			zEta[i]=0;
			zPhi[i]=0;

			lPt[i]=0;
			lPdgId[i]=0;
			lEta[i]=0;
			lPhi[i]=0;
			lPt[9-i]=0;
			lPdgId[9-i]=0;
			lEta[9-i]=0;
			lPhi[9-i]=0;
			lInd[i]=9;
//			lp4[i]=(0,0,0,0);
//			lp4[9-i]=(0,0,0,0);
		}

		t->Branch("hPt",&hPt,"hPt/F");
		t->Branch("hMass",&hMass,"hMass/F");
		t->Branch("hEta",&hEta,"hEta/F");
		t->Branch("hPhi",&hPhi,"hPhi/F");

		t->Branch("gz1Pt",&zPt[0],"gz1Pt/F");
		t->Branch("gz1Mass",&zMass[0],"gz1Mass/F");
		t->Branch("gz1Eta",&zEta[0],"gz1Eta/F");
		t->Branch("gz1Phi",&zPhi[0],"gz1Phi/F");
		t->Branch("gz2Pt",&zPt[1],"gz2Pt/F");
		t->Branch("gz2Mass",&zMass[1],"gz2Mass/F");
		t->Branch("gz2Eta",&zEta[1],"gz2Eta/F");
		t->Branch("gz2Phi",&zPhi[1],"gz2Phi/F");

		t->Branch("gl1Pt",&lPt[0],"gl1Pt/F");
		t->Branch("gl1Eta",&lEta[0],"gl1Eta/F");
		t->Branch("gl1Phi",&lPhi[0],"gl1Phi/F");
		t->Branch("gl1PdgId",&lPdgId[0],"gl1PdgId/F");
		t->Branch("gl2Pt",&lPt[1],"gl2Pt/F");
		t->Branch("gl2Eta",&lEta[1],"gl2Eta/F");
		t->Branch("gl2Phi",&lPhi[1],"gl2Phi/F");
		t->Branch("gl2PdgId",&lPdgId[1],"gl2PdgId/I");
		t->Branch("gl3Pt",&lPt[2],"gl3Pt/F");
		t->Branch("gl3Eta",&lEta[2],"gl3Eta/F");
		t->Branch("gl3Phi",&lPhi[2],"gl3Phi/F");
		t->Branch("gl3PdgId",&lPdgId[2],"gl3PdgId/I");
		t->Branch("gl4Pt",&lPt[3],"gl4Pt/F");
		t->Branch("gl4Eta",&lEta[3],"gl4Eta/F");
		t->Branch("gl4Phi",&lPhi[3],"gl4Phi/F");
		t->Branch("gl4PdgId",&lPdgId[3],"gl4PdgId/I");

		//		t->Branch("gz1l1Pt",&lPt[lInd[0]],"gz1l1Pt/F");
		//		t->Branch("gz1l1Eta",&lEta[lInd[0]],"gz1l1Eta/F");
		//		t->Branch("gz1l1Phi",&lPhi[lInd[0]],"gz1l1Phi/F");
		//		t->Branch("gz1l1PdgId",&lPdgId[lInd[0]],"gz1l1PdgId/F");
		//		t->Branch("gz1l2Pt",&lPt[lInd[1]],"gz1l2Pt/F");
		//		t->Branch("gz1l2Eta",&lEta[lInd[1]],"gz1l2Eta/F");
		//		t->Branch("gz1l2Phi",&lPhi[lInd[1]],"gz1l2Phi/F");
		//		t->Branch("gz1l2PdgId",&lPdgId[lInd[1]],"gz1l2PdgId/I");
		//		t->Branch("gz1l3Pt",&lPt[lInd[2]],"gz1l3Pt/F");
		//		t->Branch("gz1l3Eta",&lEta[lInd[2]],"gz1l3Eta/F");
		//		t->Branch("gz1l3Phi",&lPhi[lInd[2]],"gz1l3Phi/F");
		//		t->Branch("gz1l3PdgId",&lPdgId[lInd[2]],"gz1l3PdgId/I");
		//		t->Branch("gz1l4Pt",&lPt[lInd[3]],"gz1l4Pt/F");
		//		t->Branch("gz1l4Eta",&lEta[lInd[3]],"gz1l4Eta/F");
		//		t->Branch("gz1l4Phi",&lPhi[lInd[3]],"gz1l4Phi/F");
		//		t->Branch("gz1l4PdgId",&lPdgId[lInd[3]],"gz1l4PdgId/I");

		value = new std::vector<double>();
		singleValue=0.;
		function = new StringObjectFunction<T>(var_);
		if(!leadingOnly_)
			vbranch = t->Branch(tag_.c_str(),"std::vector<double>",&value);
		else
			vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());
	}


		~TruthFiller()
		{ 
			if(function!=0) delete function;
		}


		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{

			for (int i = 0; i < 5; i++) {
				zPt[i]=0;
				zMass[i]=0;
				zEta[i]=0;
				zPhi[i]=0;

				lPt[i]=0;
				lPdgId[i]=0;
				lEta[i]=0;
				lPhi[i]=0;
				lPt[9-i]=0;
				lPdgId[9-i]=0;
				lEta[9-i]=0;
				lPhi[9-i]=0;
				lInd[i]=9;
				//lp4[9-i]=(0,0,0,0);
			}
			singleValue=-1;
			// get gen particle candidates 
			edm::Handle<reco::GenParticleCollection> genCandidates;
			iEvent.getByLabel(gensrc_, genCandidates);
			int zn=0;
			int ln=0;
			for ( reco::GenParticleCollection::const_iterator candIt=genCandidates->begin(); candIt!=genCandidates->end(); ++candIt ) {
				// higgs pt
				if ( candIt->pdgId()==25 ){
					//					std::cout << "Found Higgs with mass= " << candIt->mass() << " and PT= " << candIt->pt() << " and status " << candIt->status() << std::endl;	    
					hPt=candIt->pt(); hMass=candIt->mass(); hEta=candIt->eta(); hPhi=candIt->phi();
				} else if (candIt->pdgId()==23 && (candIt->status()==3||candIt->status()==2) ){
					//					std::cout << "Z with mass: " << candIt->mass() << std::endl;
					zPt[zn]=candIt->pt();
					zMass[zn]=candIt->mass();
					zEta[zn]=candIt->eta();
					zPhi[zn]=candIt->phi();
					if( zn<4) zn++;
				} else if ((abs(candIt->pdgId())==11 || abs(candIt->pdgId())==13 || abs(candIt->pdgId())==15 ) && candIt->status()==1){
					//					std::cout << "lepton coming from: " << candIt->mother(0)->pdgId() << std::endl;
					lPt[ln]=candIt->pt();
					lEta[ln]=candIt->eta();
					lPhi[ln]=candIt->phi();
					lPdgId[ln]=candIt->pdgId();
					lp4[ln]=candIt->p4();
					if (ln<9) ln++;
				}
			} 
			std::cout << "finished loop over genParticles" << std::endl;

			if(value->size()>0)
				value->clear();

			edm::Handle<std::vector<T> > handle;
			std::cout << "Getting by handle" << std::endl;
			if(iEvent.getByLabel(src_,handle)) {
				//look at everything and try to match...
				//match z1l1
				float tempdR0=0.5;
				float tempdR1=0.5;
				float tempdR2=0.5;
				float tempdR3=0.5;
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg1()->leg1()->p4(),lp4[i])<tempdR0){
						tempdR0=reco::deltaR(handle->at(0).leg1()->leg1()->p4(),lp4[i]);
						lInd[0]=i; matched[0]=true;	
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg1()->leg2()->p4(),lp4[i])<tempdR1){
						tempdR1=reco::deltaR(handle->at(0).leg1()->leg2()->p4(),lp4[i]);
						lInd[1]=i; matched[1]=true;	
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg2()->leg1()->p4(),lp4[i])<tempdR2){
						tempdR2=reco::deltaR(handle->at(0).leg2()->leg1()->p4(),lp4[i]);
						lInd[2]=i; matched[2]=true;
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg2()->leg2()->p4(),lp4[i])<tempdR3){
						tempdR3=reco::deltaR(handle->at(0).leg2()->leg2()->p4(),lp4[i]);
						lInd[3]=i;	matched[3]=true;
					}
				}
				//				std::cout << "best indices:" << lInd[0] << "(" <<  tempdR0 << ")" <<std::endl;
				//				std::cout << "best indices:" << lInd[1] << "(" <<  tempdR1 << ")" <<std::endl;
				//				std::cout << "best indices:" << lInd[2] << "(" <<  tempdR2 << ")" <<std::endl;
				//				std::cout << "best indices:" << lInd[3] << "(" <<  tempdR3 << ")" <<std::endl;
			} else {
				printf("Obj not found \n");
			}
			std::cout << "finished..." << std::endl;
		}


	protected:
		edm::InputTag src_;
		edm::InputTag gensrc_;
		std::string var_;
		std::string tag_;
		bool leadingOnly_;
		std::vector<double>* value;
		float singleValue;

		StringObjectFunction<T>*function;
		TBranch *vbranch;
		float hPt, hMass, hEta, hPhi;
		float zPt[5], zMass[5], zEta[5], zPhi[5];
		float lPt[10], lEta[10], lPhi[10];
		int lPdgId[10];
		int lInd[4]; float dR[4]; bool matched[4];
		reco::Candidate::LorentzVector lp4[10];
};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
#include "DataFormats/METReco/interface/PFMET.h"
#include "DataFormats/METReco/interface/GenMET.h"
//typedef TruthFiller<PATMuTauPair> PATMuTauPairFiller;
//typedef TruthFiller<PATDiTauPair> PATDiTauPairFiller;
//typedef TruthFiller<PATElecTauPair> PATEleTauPairFiller;
//typedef TruthFiller<PATElecMuPair> PATEleMuPairFiller;
//typedef TruthFiller<PATElecPair> PATElePairFiller;
//typedef TruthFiller<PATMuonNuPair> PATMuonNuPairFiller;
//typedef TruthFiller<PATCandNuPair> PATCandNuPairFiller;
//typedef TruthFiller<PATMuTrackPair> PATMuTrackPairFiller;
//typedef TruthFiller<PATEleTrackPair> PATEleTrackPairFiller;
//typedef TruthFiller<PATMuPair> PATMuPairFiller;
//typedef TruthFiller<pat::Muon> PATMuonFiller;
//typedef TruthFiller<reco::MET> PATMETFiller;
//typedef TruthFiller<reco::PFMET> PATPFMETFiller;
//typedef TruthFiller<reco::GenMET> PATGenMETFiller;
typedef TruthFiller<PATMuMuMuTauQuad> PATMuMuMuTauTruthFiller;
typedef TruthFiller<PATMuMuTauTauQuad> PATMuMuTauTauTruthFiller;
typedef TruthFiller<PATMuMuEleTauQuad> PATMuMuEleTauTruthFiller;
typedef TruthFiller<PATMuMuEleMuQuad> PATMuMuEleMuTruthFiller;
typedef TruthFiller<PATMuMuEleEleQuad> PATMuMuEleEleTruthFiller;
typedef TruthFiller<PATMuMuMuMuQuad> PATMuMuMuMuTruthFiller;
typedef TruthFiller<PATEleEleTauTauQuad> PATEleEleTauTauTruthFiller;
typedef TruthFiller<PATEleEleEleTauQuad> PATEleEleEleTauTruthFiller;
typedef TruthFiller<PATEleEleMuTauQuad> PATEleEleMuTauTruthFiller;
typedef TruthFiller<PATEleEleEleMuQuad> PATEleEleEleMuTruthFiller;
typedef TruthFiller<PATEleEleEleEleQuad> PATEleEleEleEleTruthFiller;
typedef TruthFiller<PATEleEleMuMuQuad> PATEleEleMuMuTruthFiller;
//typedef TruthFiller<PATEleEleMuNuQuad> PATEleEleMuNuTruthFiller;
//typedef TruthFiller<PATEleEleEleNuQuad> PATEleEleEleNuTruthFiller;
//typedef TruthFiller<PATMuMuMuNuQuad> PATMuMuMuNuTruthFiller;
//typedef TruthFiller<PATMuMuEleNuQuad> PATMuMuEleNuTruthFiller;

