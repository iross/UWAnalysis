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

		zzMass=0;
		zzEta=0;
		zzPhi=0;
		zzPt=0;

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
			zInd[i]=1;
			//			lp4[i]=(0,0,0,0);
			//			lp4[9-i]=(0,0,0,0);
		}

		t->Branch("hPt",&hPt,"hPt/F");
		t->Branch("hMass",&hMass,"hMass/F");
		t->Branch("hEta",&hEta,"hEta/F");
		t->Branch("hPhi",&hPhi,"hPhi/F");

		t->Branch("gMass",&zzMass,"gMass/F");
		t->Branch("gEta",&zzEta,"gEta/F");
		t->Branch("gPhi",&zzPhi,"gPhi/F");

		t->Branch("gz1Pt",&zPt[0],"gz1Pt/F");
		t->Branch("gz1Mass",&zMass[0],"gz1Mass/F");
		t->Branch("gz1Eta",&zEta[0],"gz1Eta/F");
		t->Branch("gz1Phi",&zPhi[0],"gz1Phi/F");
		t->Branch("gz2Pt",&zPt[1],"gz2Pt/F");
		t->Branch("gz2Mass",&zMass[1],"gz2Mass/F");
		t->Branch("gz2Eta",&zEta[1],"gz2Eta/F");
		t->Branch("gz2Phi",&zPhi[1],"gz2Phi/F");

		t->Branch("mz1Pt",&mz1Pt,"mz1Pt/F");
		t->Branch("mz1Mass",&mz1Mass,"mz1Mass/F");
		t->Branch("mz1Eta",&mz1Eta,"mz1Eta/F");
		t->Branch("mz1Phi",&mz1Phi,"mz1Phi/F");
		t->Branch("mz1Matched",&zmatched[0],"mz1Matched/B");
		t->Branch("mz2Pt",&mz2Pt,"mz2Pt/F");
		t->Branch("mz2Mass",&mz2Mass,"mz2Mass/F");
		t->Branch("mz2Eta",&mz2Eta,"mz2Eta/F");
		t->Branch("mz2Phi",&mz2Phi,"mz2Phi/F");
		t->Branch("mz2Matched",&zmatched[1],"mz2Matched/B");

		t->Branch("gl1Pt",&lPt[0],"gl1Pt/F");
		t->Branch("gl1Eta",&lEta[0],"gl1Eta/F");
		t->Branch("gl1Phi",&lPhi[0],"gl1Phi/F");
		t->Branch("gl1PdgId",&lPdgId[0],"gl1PdgId/I");
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

		t->Branch("gz1l1Pt",&z1l1Pt,"gz1l1Pt/F");
		t->Branch("gz1l1Eta",&z1l1Eta,"gz1l1Eta/F");
		t->Branch("gz1l1Phi",&z1l1Phi,"gz1l1Phi/F");
		t->Branch("gz1l1PdgId",&z1l1PdgId,"gz1l1PdgId/I");
		t->Branch("gz1l2Pt",&z1l2Pt,"gz1l2Pt/F");
		t->Branch("gz1l2Eta",&z1l2Eta,"gz1l2Eta/F");
		t->Branch("gz1l2Phi",&z1l2Phi,"gz1l2Phi/F");
		t->Branch("gz1l2PdgId",&z1l2PdgId,"gz1l2PdgId/I");
		t->Branch("gz2l1Pt",&z2l1Pt,"gz2l1Pt/F");
		t->Branch("gz2l1Eta",&z2l1Eta,"gz2l1Eta/F");
		t->Branch("gz2l1Phi",&z2l1Phi,"gz2l1Phi/F");
		t->Branch("gz2l1PdgId",&z2l1PdgId,"gz2l1PdgId/I");
		t->Branch("gz2l2Pt",&z2l2Pt,"gz2l2Pt/F");
		t->Branch("gz2l2Eta",&z2l2Eta,"gz2l2Eta/F");
		t->Branch("gz2l2Phi",&z2l2Phi,"gz2l2Phi/F");
		t->Branch("gz2l2PdgId",&z2l2PdgId,"gz2l2PdgId/I");
		t->Branch("z1l1Matched",&matched[0],"z1l1Matched/B");
		t->Branch("z1l2Matched",&matched[1],"z1l2Matched/B");
		t->Branch("z2l1Matched",&matched[2],"z2l1Matched/B");
		t->Branch("z2l2Matched",&matched[3],"z2l2Matched/B");

	}


		~TruthFiller()
		{ 
//			if(function!=0) delete function;
		}


		void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
		{

			hMass=0;
			hEta=0;
			hPhi=0;
			zzMass=0;
			zzEta=0;
			zzPhi=0;
			zzPt=0;
			for (int i = 0; i < 5; i++) {
				zPt[i]=0;
				zMass[i]=0;
				zEta[i]=0;
				zPhi[i]=0;

				lPt[i]=0;
				lPdgId[i]=137;
				lEta[i]=0;
				lPhi[i]=0;
				lPt[9-i]=0;
				lPdgId[9-i]=137;
				lEta[9-i]=0;
				lPhi[9-i]=0;
				lInd[i]=9;
				matched[i]=false;
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
				} else if (candIt->pdgId()==23 ){
					//					std::cout << "Z with mass: " << candIt->mass() << std::endl;
					zPt[zn]=candIt->pt();
					zMass[zn]=candIt->mass();
					zEta[zn]=candIt->eta();
					zPhi[zn]=candIt->phi();
					zp4[zn]=candIt->p4();
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
			edm::Handle<std::vector<T> > handle;
			if(iEvent.getByLabel(src_,handle)) {
				//look at everything and try to match...
				//match z1l1
				float tempzdR0=0.5;
				float tempzdR1=0.5;
				float tempdR0=0.5;
				float tempdR1=0.5;
				float tempdR2=0.5;
				float tempdR3=0.5;
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg1()->leg1()->p4(),lp4[i])<tempdR0){
						tempdR0=reco::deltaR(handle->at(0).leg1()->leg1()->p4(),lp4[i]);
						lInd[0]=i; 
						if (handle->at(0).leg1()->leg1()->pdgId()==lPdgId[i]){ 
							matched[0]=true;
						}
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg1()->leg2()->p4(),lp4[i])<tempdR1){
						tempdR1=reco::deltaR(handle->at(0).leg1()->leg2()->p4(),lp4[i]);
						lInd[1]=i;
						if (handle->at(0).leg1()->leg2()->pdgId()==lPdgId[i]){
							matched[1]=true;	
						}
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg2()->leg1()->p4(),lp4[i])<tempdR2){
						tempdR2=reco::deltaR(handle->at(0).leg2()->leg1()->p4(),lp4[i]);
						lInd[2]=i;
						if (handle->at(0).leg2()->leg1()->pdgId()==lPdgId[i]){
							matched[2]=true;
						}
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg2()->leg2()->p4(),lp4[i])<tempdR3){
						tempdR3=reco::deltaR(handle->at(0).leg2()->leg2()->p4(),lp4[i]);
						lInd[3]=i;
						if ( handle->at(0).leg2()->leg2()->pdgId()==lPdgId[i]){
							matched[3]=true;
						}
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg1()->p4(),zp4[i])<tempzdR0){
						tempzdR0=reco::deltaR(handle->at(0).leg1()->p4(),zp4[i]);
						zInd[0]=i;	zmatched[0]=true;
					}
				}
				for (int i=0; i<5; ++i){
					if (reco::deltaR(handle->at(0).leg2()->p4(),zp4[i])<tempzdR1){
						tempzdR1=reco::deltaR(handle->at(0).leg2()->p4(),zp4[i]);
						zInd[1]=i;	zmatched[1]=true;
					}
				}
//				std::cout << "best indices:" << lInd[0] << "(" <<  tempdR0 << ")" << lPt[lInd[0]]<<std::endl;
//				std::cout << "best indices:" << lInd[1] << "(" <<  tempdR1 << ")" <<  lPt[lInd[1]] << std::endl;
//				std::cout << "best indices:" << lInd[2] << "(" <<  tempdR2 << ")" << lPt[lInd[2]]<< std::endl;
//				std::cout << "best indices:" << lInd[3] << "(" <<  tempdR3 << ")" << lPt[lInd[3]]<< std::endl;
//				std::cout << "best indices (z):" << zInd[0]  << " matched: " << zmatched[0]<< std::endl;
//				std::cout << "best indices (z):" << zInd[1] << " matched: " << zmatched[1] << std::endl;
				z1l1Pt=lPt[lInd[0]]; z1l1Eta=lEta[lInd[0]]; z1l1Phi=lPhi[lInd[0]]; z1l1PdgId=lPdgId[lInd[0]];
				z1l2Pt=lPt[lInd[1]]; z1l2Eta=lEta[lInd[1]]; z1l2Phi=lPhi[lInd[1]]; z1l2PdgId=lPdgId[lInd[1]];
				z2l1Pt=lPt[lInd[2]]; z2l1Eta=lEta[lInd[2]]; z2l1Phi=lPhi[lInd[2]]; z2l1PdgId=lPdgId[lInd[2]];
				z2l2Pt=lPt[lInd[3]]; z2l2Eta=lEta[lInd[3]]; z2l2Phi=lPhi[lInd[3]]; z2l2PdgId=lPdgId[lInd[3]];
				mz1Pt=zPt[zInd[0]]; mz1Eta=zEta[zInd[0]]; mz1Phi=zPhi[zInd[0]]; mz1Mass=zMass[zInd[0]];
				mz2Pt=zPt[zInd[1]]; mz2Eta=zEta[zInd[1]]; mz2Phi=zPhi[zInd[1]]; mz2Mass=zMass[zInd[1]];
				zzMass=(zp4[0]+zp4[1]).M();
				zzEta=(zp4[0]+zp4[1]).eta();
				zzPhi=(zp4[0]+zp4[1]).phi();
				zzPt=(zp4[0]+zp4[1]).pt();
			} else {
				printf("Obj not found \n");
			}
		}


	protected:
		edm::InputTag src_;
		edm::InputTag gensrc_;
		std::string var_;
		std::string tag_;
		bool leadingOnly_;
		float singleValue;

//		StringObjectFunction<T>*function;
//		TBranch *vbranch;
		float hPt, hMass, hEta, hPhi;
		float zPt[5], zMass[5], zEta[5], zPhi[5];
		float lPt[10], lEta[10], lPhi[10];
		int lPdgId[10];
		int lInd[5]; bool matched[5];
		int zInd[2]; bool zmatched[5];
		float zzMass, zzEta, zzPhi, zzPt;
		float z1l1Pt, z1l1Eta, z1l1Phi; 
		float z1l2Pt, z1l2Eta, z1l2Phi; 
		float z2l1Pt, z2l1Eta, z2l1Phi; 
		float z2l2Pt, z2l2Eta, z2l2Phi; 
		int z1l1PdgId, z1l2PdgId, z2l1PdgId, z2l2PdgId;
		float mz1Mass, mz1Pt, mz1Eta, mz1Phi;
		float mz2Mass, mz2Pt, mz2Eta, mz2Phi;
		reco::Candidate::LorentzVector lp4[10], zp4[5];
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
typedef TruthFiller<PATEleSCEleEleQuad> PATEleSCEleEleTruthFiller;
typedef TruthFiller<PATEleEleEleSCQuad> PATEleEleEleSCTruthFiller;
typedef TruthFiller<PATMuMuEleSCQuad> PATMuMuEleSCTruthFiller;
//typedef TruthFiller<PATEleEleMuNuQuad> PATEleEleMuNuTruthFiller;
//typedef TruthFiller<PATEleEleEleNuQuad> PATEleEleEleNuTruthFiller;
//typedef TruthFiller<PATMuMuMuNuQuad> PATMuMuMuNuTruthFiller;
//typedef TruthFiller<PATMuMuEleNuQuad> PATMuMuEleNuTruthFiller;

