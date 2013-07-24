#ifndef TRUTHFILLER_H_
#define TRUTHFILLER_H_

// system include files
#include <memory>
#include <vector>
#include <algorithm>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include <TTree.h>
#include <TLorentzVector.h>

#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/LorentzVector.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"
#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "SimGeneral/HepPDTRecord/interface/ParticleDataTable.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"

#include <math.h>
#include "Math/GenVector/VectorUtil.h"

#include "UWAnalysis/NtupleTools/plugins/GenLevelFiller.h"
#include "DataFormats/Candidate/interface/Candidate.h"
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
            zmatched[i]=false;

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
        }

        t->Branch("hPt",&hPt,"hPt/F");
        t->Branch("hMass",&hMass,"hMass/F");
        t->Branch("hEta",&hEta,"hEta/F");
        t->Branch("hPhi",&hPhi,"hPhi/F");

        t->Branch("gMass",&zzMass,"gMass/F");
        t->Branch("gPt",&zzPt,"gPt/F");
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
                zp4[i].SetPtEtaPhiM(100,0,0,100);
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
            std::vector<std::vector<reco::GenParticle>::const_iterator> leptons;
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
                    zp4[zn].SetPtEtaPhiM(candIt->pt(), candIt->eta(), candIt->phi(), candIt->mass());
                    if( zn<4) zn++;
                } else if ((abs(candIt->pdgId())==11 || abs(candIt->pdgId())==13 || abs(candIt->pdgId())==15 ) && candIt->status()==3){
                    //					std::cout << "lepton coming from: " << candIt->mother(0)->pdgId() << std::endl;
                    lPt[ln]=candIt->pt();
                    lEta[ln]=candIt->eta();
                    lPhi[ln]=candIt->phi();
                    lPdgId[ln]=candIt->pdgId();
                    lp4[ln]=candIt->p4();
                    leptons.push_back(candIt);
                    if (ln<9) ln++;
                }
            }
            edm::Handle<std::vector<T> > handle;
            if (zn == 0) {
                //no Zs found, build from leptons, choose 'best' mass from OSSF pairs
                // leptons must be sorted before they can be permuted
                std::sort(leptons.begin(),leptons.end(),compareLeptons);

                double min = 91.2;
                TLorentzVector L1, L2, L3, L4, Z1, Z2;
                int id1, id2, id3, id4;
                do
                {
                    // ensure opposite-charge-same-flavor pairs
                    // permute through different combinations of the leptons to build Z candidates
                    if ( leptons.at(0)->pdgId() == -leptons.at(1)->pdgId() && leptons.at(2)->pdgId() == -leptons.at(3)->pdgId() ) {
                        // build lepton 4-vectors from lepton candidates
                        TLorentzVector l1, l2, l3, l4, z1, z2;
                        l1.SetPtEtaPhiM(leptons.at(0)->pt(),leptons.at(0)->eta(),leptons.at(0)->phi(),leptons.at(0)->mass());
                        l2.SetPtEtaPhiM(leptons.at(1)->pt(),leptons.at(1)->eta(),leptons.at(1)->phi(),leptons.at(1)->mass());
                        l3.SetPtEtaPhiM(leptons.at(2)->pt(),leptons.at(2)->eta(),leptons.at(2)->phi(),leptons.at(2)->mass());
                        l4.SetPtEtaPhiM(leptons.at(3)->pt(),leptons.at(3)->eta(),leptons.at(3)->phi(),leptons.at(3)->mass());

                        z1 = l1 + l2; // create Z 4-vectors from leptons
                        z2 = l3 + l4;

                        // set Z1 to be closest to nominal Z mass
                        if ( fabs(z1.M()-91.2) < min )
                        {
                            min = fabs(z1.M()-91.2);
                            Z1 = z1;
                            Z2 = z2;
                            L1 = l1;
                            L2 = l2;
                            L3 = l3;
                            L4 = l4;
                            id1 = leptons.at(0)->pdgId();
                            id2 = leptons.at(1)->pdgId();
                            id3 = leptons.at(2)->pdgId();
                            id4 = leptons.at(3)->pdgId();
                        }
                    }


                } while ( next_permutation(leptons.begin(), leptons.end(), compareLeptons) );
                zp4[0].SetPtEtaPhiM(Z1.Pt(), Z1.Eta(), Z1.Phi(), Z1.M());
                zPt[0]    = Z1.Pt();
                zEta[0]   = Z1.Eta();
                zPhi[0]   = Z1.Phi();
                zMass[0]  = Z1.M();
                zp4[1].SetPtEtaPhiM(Z2.Pt(), Z2.Eta(), Z2.Phi(), Z2.M());
                zPt[1]    = Z2.Pt();
                zEta[1]   = Z2.Eta();
                zPhi[1]   = Z2.Phi();
                zMass[1]  = Z2.M();
            }

            if(iEvent.getByLabel(src_,handle)) {
                //look at everything and try to match...
                float tempzdR0=0.5;
                float tempzdR1=0.5;
                float tempdR0=0.5;
                float tempdR1=0.5;
                float tempdR2=0.5;
                float tempdR3=0.5;
                zmatched[0]=false; zmatched[1]=false;
                for (unsigned int j = 0; j < handle->size(); ++j) { //check if ANY of the candidates match leptons+Zs
                    for (int i=0; i<5; ++i){
                        if (reco::deltaR(handle->at(j).leg1()->leg1()->p4(),lp4[i])<tempdR0){
                            tempdR0=reco::deltaR(handle->at(j).leg1()->leg1()->p4(),lp4[i]);
                            lInd[0]=i;
                            if (handle->at(j).leg1()->leg1()->pdgId()==lPdgId[i]){
                                matched[0]=true;
                            }
                        }
                    }
                    for (int i=0; i<5; ++i){
                        if (reco::deltaR(handle->at(j).leg1()->leg2()->p4(),lp4[i])<tempdR1){
                            tempdR1=reco::deltaR(handle->at(j).leg1()->leg2()->p4(),lp4[i]);
                            lInd[1]=i;
                            if (handle->at(j).leg1()->leg2()->pdgId()==lPdgId[i]){
                                matched[1]=true;
                            }
                        }
                    }
                    for (int i=0; i<5; ++i){
                        if (reco::deltaR(handle->at(j).leg2()->leg1()->p4(),lp4[i])<tempdR2){
                            tempdR2=reco::deltaR(handle->at(j).leg2()->leg1()->p4(),lp4[i]);
                            lInd[2]=i;
                            if (handle->at(j).leg2()->leg1()->pdgId()==lPdgId[i]){
                                matched[2]=true;
                            }
                        }
                    }
                    for (int i=0; i<5; ++i){
                        if (reco::deltaR(handle->at(j).leg2()->leg2()->p4(),lp4[i])<tempdR3){
                            tempdR3=reco::deltaR(handle->at(j).leg2()->leg2()->p4(),lp4[i]);
                            lInd[3]=i;
                            if ( handle->at(j).leg2()->leg2()->pdgId()==lPdgId[i]){
                                matched[3]=true;
                            }
                        }
                    }
                    for (int i=0; i<5; ++i){
                        if (ROOT::Math::VectorUtil::DeltaR(handle->at(j).leg1()->p4(),zp4[i])<tempzdR0 && zMass[i]>0){
                            tempzdR0=ROOT::Math::VectorUtil::DeltaR(handle->at(j).leg1()->p4(),zp4[i]);
                            zInd[0]=i;	zmatched[0]=true;
                        }
                    }
                    for (int i=0; i<5; ++i){
                        if (ROOT::Math::VectorUtil::DeltaR(handle->at(j).leg2()->p4(),zp4[i])<tempzdR1 && zMass[i]>0 && i != zInd[0]){
                            tempzdR1=ROOT::Math::VectorUtil::DeltaR(handle->at(j).leg2()->p4(),zp4[i]);
                            zInd[1]=i;	zmatched[1]=true;
                        }
                    }
                }

                z1l1Pt=lPt[lInd[0]]; z1l1Eta=lEta[lInd[0]]; z1l1Phi=lPhi[lInd[0]]; z1l1PdgId=lPdgId[lInd[0]];
                z1l2Pt=lPt[lInd[1]]; z1l2Eta=lEta[lInd[1]]; z1l2Phi=lPhi[lInd[1]]; z1l2PdgId=lPdgId[lInd[1]];
                z2l1Pt=lPt[lInd[2]]; z2l1Eta=lEta[lInd[2]]; z2l1Phi=lPhi[lInd[2]]; z2l1PdgId=lPdgId[lInd[2]];
                z2l2Pt=lPt[lInd[3]]; z2l2Eta=lEta[lInd[3]]; z2l2Phi=lPhi[lInd[3]]; z2l2PdgId=lPdgId[lInd[3]];
                mz1Pt=zPt[zInd[0]]; mz1Eta=zEta[zInd[0]]; mz1Phi=zPhi[zInd[0]]; mz1Mass=zMass[zInd[0]];
                mz2Pt=zPt[zInd[1]]; mz2Eta=zEta[zInd[1]]; mz2Phi=zPhi[zInd[1]]; mz2Mass=zMass[zInd[1]];
                zzMass=(zp4[0]+zp4[1]).M();
                if ((zp4[0]+zp4[1]).Pt()>0.1)  zzEta = (zp4[0]+zp4[1]).Eta();
                else zzEta=-137;
                zzPhi=(zp4[0]+zp4[1]).Phi();
                zzPt=(zp4[0]+zp4[1]).Pt();
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
        reco::Candidate::LorentzVector lp4[10];
        TLorentzVector zp4[5];
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
typedef TruthFiller<PATEleSCMuMuQuad> PATEleSCMuMuTruthFiller;
//typedef TruthFiller<PATEleEleMuNuQuad> PATEleEleMuNuTruthFiller;
//typedef TruthFiller<PATEleEleEleNuQuad> PATEleEleEleNuTruthFiller;
//typedef TruthFiller<PATMuMuMuNuQuad> PATMuMuMuNuTruthFiller;
//typedef TruthFiller<PATMuMuEleNuQuad> PATMuMuEleNuTruthFiller;

#endif
