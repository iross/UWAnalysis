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


#include "TrackingTools/TransientTrack/interface/TransientTrackBuilder.h"
#include "TrackingTools/Records/interface/TransientTrackRecord.h"
#include "TrackingTools/IPTools/interface/IPTools.h"

#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/BeamSpot/interface/BeamSpot.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration
//stuff for MVA recalculation

#include "EGamma/EGammaAnalysisTools/interface/EGammaMvaEleEstimator.h"


class PATMVAIDEmbedder : public edm::EDProducer {
    public:

        explicit PATMVAIDEmbedder(const edm::ParameterSet& iConfig):
            src_(iConfig.getParameter<edm::InputTag>("src")),
            id_(iConfig.getParameter<std::string>("id")),
            recalMVA_(iConfig.getParameter<bool>("recalculateMVA"))
    {
        produces<pat::ElectronCollection>();

        std::vector<std::string> myManualCatWeights;
        Bool_t manualCat = true;
        if (recalMVA_) {
            myManualCatWeights.push_back(edm::FileInPath("EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat1.weights.xml").fullPath());
            myManualCatWeights.push_back(edm::FileInPath("EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat2.weights.xml").fullPath());
            myManualCatWeights.push_back(edm::FileInPath("EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat3.weights.xml").fullPath());
            myManualCatWeights.push_back(edm::FileInPath("EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat4.weights.xml").fullPath());
            myManualCatWeights.push_back(edm::FileInPath("EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat5.weights.xml").fullPath());
            myManualCatWeights.push_back(edm::FileInPath("EGamma/EGammaAnalysisTools/data/Electrons_BDTG_NonTrigV0_Cat6.weights.xml").fullPath());
            myMVANonTrig.initialize("BDT",EGammaMvaEleEstimator::kNonTrig,manualCat,myManualCatWeights);
        }

    }

        ~PATMVAIDEmbedder() {}
    private:



        virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            using namespace edm;
            using namespace reco;
            std::auto_ptr<pat::ElectronCollection > out(new pat::ElectronCollection);

            Handle<pat::ElectronCollection > cands;

            InputTag  vertexLabel(string("offlinePrimaryVertices"));
            Handle<reco::VertexCollection> thePrimaryVertexColl;
            iEvent.getByLabel(vertexLabel,thePrimaryVertexColl);

            edm::ESHandle<TransientTrackBuilder> builder;
            iSetup.get<TransientTrackRecord>().get("TransientTrackBuilder", builder);
            TransientTrackBuilder thebuilder = *(builder.product());

            Vertex dummy;
            const Vertex *pv = &dummy;
            if (thePrimaryVertexColl->size() != 0) {
                pv = &*thePrimaryVertexColl->begin();
            } else { // create a dummy PV
                Vertex::Error e;
                e(0, 0) = 0.0015 * 0.0015;
                e(1, 1) = 0.0015 * 0.0015;
                e(2, 2) = 15. * 15.;
                Vertex::Point p(0, 0, 0);
                dummy = Vertex(p, e, 0, 0, 0);
            }

            if(iEvent.getByLabel(src_,cands))
                for(unsigned int  i=0;i!=cands->size();++i){
                    bool passID=false;
                    //loop over electrons, embed MVA values
                    pat::Electron electron = cands->at(i);

                    double mvaVal = electron.electronID(id_);

                    if (recalMVA_){
                        getValues(electron, *pv, thebuilder, false);
                        mvaVal = myMVANonTrig.mvaValue( myMVAVar_fbrem,
                                myMVAVar_kfchi2,
                                myMVAVar_kfhits,
                                myMVAVar_gsfchi2,
                                myMVAVar_deta,
                                myMVAVar_dphi,
                                myMVAVar_detacalo,
                                // myMVAVar_dphicalo,
                                myMVAVar_see,
                                myMVAVar_spp,
                                myMVAVar_etawidth,
                                myMVAVar_phiwidth,
                                myMVAVar_e1x5e5x5,
                                myMVAVar_R9,
                                //myMVAVar_nbrems,
                                myMVAVar_HoE,
                                myMVAVar_EoP,
                                myMVAVar_IoEmIoP,
                                myMVAVar_eleEoPout,
                                myMVAVar_PreShowerOverRaw,
                                // myMVAVar_EoPout,
                                myMVAVar_eta,
                                myMVAVar_pt,
                                false);
                    }

                    if (electron.pt()>5 && electron.pt()<10){
                        if (fabs(electron.superCluster()->eta())<0.8) {
                            if (mvaVal>0.47) passID=true;
                        }
                        else if (fabs(electron.superCluster()->eta())<1.479) {
                            if (mvaVal>0.004) passID=true;
                        }
                        else {
                            if (mvaVal>0.295) passID=true;
                        }
                    } else {
                        if (fabs(electron.superCluster()->eta())<0.8 ) {
                            if (mvaVal>0.5) passID=true;
                        } else if (fabs(electron.superCluster()->eta())<1.479) {
                            if (mvaVal>0.12) passID=true;
                        } else {
                            if (mvaVal>0.6) passID=true;
                        }
                    }
                    if(passID)
                        electron.addUserFloat(id_+"Pass",1.0);
                    else
                        electron.addUserFloat(id_+"Pass",0.0);
                    if(recalMVA_)
                        electron.addUserFloat(id_+"Corrected",mvaVal);
//                    std::cout << "Electron: " << electron.pt() << "\t" << electron.eta() << "\t" << electron.phi() << std::endl;
//                    std::cout << "\tID\t" << electron.userFloat("mvaNonTrigV0Pass") << "\t" << electron.userFloat("ip3DS") << "\t" << electron.userFloat("ipDXY") << "\t" << electron.userFloat("dz") << std::endl;
//                    std::cout << "\tID 2\t" << electron.gsfTrack()->trackerExpectedHitsInner().numberOfHits() << electron.charge() << std::endl;
//                    std::cout << "\tISO\t" << (electron.chargedHadronIso()+electron.neutralHadronIso()+electron.photonIso()-electron.userFloat("zzRho2012")*electron.userFloat("effArea"))/electron.pt() << std::endl;
//                    std::cout << "\tDEFAULT ISO\t" << electron.chargedHadronIso() << "\t" << electron.neutralHadronIso() << "\t" << electron.photonIso() << std::endl;
//                    std::cout << "\tUSER ISO\t" << electron.userIso(0) << "\t" << electron.userIso(1) << "\t" << electron.userIso(2) << "\t" << electron.userIso(3) << "\t" << electron.userIso(4) << std::endl;
//                    std::cout << "\tUSER ISO\t" << electron.userIso(5) << "\t" << electron.userIso(6) << "\t" << electron.userIso(7) << "\t" << electron.userIso(8) << "\t" << electron.userIso(9) << std::endl;
//                    std::cout << "\tUSER ISO\t" << electron.userIso(10) << "\t" << electron.userIso(11) << "\t" << electron.userIso(12) << "\t" << electron.userIso(13) << "\t" << electron.userIso(14) << std::endl;
                    out->push_back(electron);
                }

            iEvent.put(out);
        }

        void getValues(const pat::Electron& ele, const reco::Vertex& vertex, const TransientTrackBuilder& transientTrackBuilder, bool printDebug=false){
            bool validKF= false;
            reco::TrackRef myTrackRef = ele.closestCtfTrackRef();
            validKF = (myTrackRef.isAvailable());
            validKF = (myTrackRef.isNonnull());

            myMVAVar_fbrem           =  ele.fbrem();
            myMVAVar_kfchi2          =  (validKF) ? myTrackRef->normalizedChi2() : 0 ;
            myMVAVar_kfhits          =  (validKF) ? myTrackRef->hitPattern().trackerLayersWithMeasurement() : -1. ;
            myMVAVar_gsfchi2         =  ele.gsfTrack()->normalizedChi2();  // to be checked


            myMVAVar_deta            =  ele.deltaEtaSuperClusterTrackAtVtx();
            myMVAVar_dphi            =  ele.deltaPhiSuperClusterTrackAtVtx();
            myMVAVar_detacalo        =  ele.deltaEtaSeedClusterTrackAtCalo();
            myMVAVar_dphicalo        =  ele.deltaPhiSeedClusterTrackAtCalo();

            myMVAVar_see             =  ele.sigmaIetaIeta();    //EleSigmaIEtaIEta
            //            std::vector<float> vCov = myEcalCluster.localCovariances(*(ele.superCluster()->seed())) ;
            //            if (!isnan(vCov[2])) myMVAVar_spp = sqrt (vCov[2]);   //EleSigmaIPhiIPhi
            //            else myMVAVar_spp = 0.;

            myMVAVar_spp             = ele.sigmaIphiIphi();
            myMVAVar_etawidth        =  ele.superCluster()->etaWidth();
            myMVAVar_phiwidth        =  ele.superCluster()->phiWidth();
            myMVAVar_e1x5e5x5        =  (ele.e5x5()) !=0. ? 1.-(ele.e1x5()/ele.e5x5()) : -1. ;
            //            myMVAVar_R9              =  myEcalCluster.e3x3(*(ele.superCluster()->seed())) / ele.superCluster()->rawEnergy();
            myMVAVar_R9              =  ele.r9();
            myMVAVar_nbrems          =  fabs(ele.numberOfBrems());

            myMVAVar_HoE             =  ele.hadronicOverEm();
            myMVAVar_EoP             =  ele.eSuperClusterOverP();
            myMVAVar_IoEmIoP         =  (1.0/ele.ecalEnergy()) - (1.0 / ele.p());  // in the future to be changed with ele.gsfTrack()->p()
            myMVAVar_eleEoPout       =  ele.eEleClusterOverPout();
            myMVAVar_EoPout          =  ele.eSeedClusterOverPout();
            myMVAVar_PreShowerOverRaw=  ele.superCluster()->preshowerEnergy() / ele.superCluster()->rawEnergy();


            myMVAVar_eta             =  ele.superCluster()->eta();
            myMVAVar_pt              =  ele.pt();
            //d0
            if (ele.gsfTrack().isNonnull()) {
                myMVAVar_d0 = (-1.0)*ele.gsfTrack()->dxy(vertex.position());
            } else if (ele.closestCtfTrackRef().isNonnull()) {
                myMVAVar_d0 = (-1.0)*ele.closestCtfTrackRef()->dxy(vertex.position());
            } else {
                myMVAVar_d0 = -9999.0;
            }

            //default values for IP3D
            myMVAVar_ip3d = -999.0;
            // myMVAVar_ip3dSig = 0.0;
            if (ele.gsfTrack().isNonnull()) {
                const double gsfsign   = ( (-ele.gsfTrack()->dxy(vertex.position()))   >=0 ) ? 1. : -1.;

                const reco::TransientTrack &tt = transientTrackBuilder.build(ele.gsfTrack());
                const std::pair<bool,Measurement1D> &ip3dpv =  IPTools::absoluteImpactParameter3D(tt,vertex);
                if (ip3dpv.first) {
                    double ip3d = gsfsign*ip3dpv.second.value();
                    //double ip3derr = ip3dpv.second.error();
                    myMVAVar_ip3d = ip3d;
                    // myMVAVar_ip3dSig = ip3d/ip3derr;
                }
            }
            if(printDebug) {
                cout << " My Local Variables " << endl;
                cout << " fbrem " <<  myMVAVar_fbrem
                    << " kfchi2 " << myMVAVar_kfchi2
                    << " mykfhits " << myMVAVar_kfhits
                    << " gsfchi2 " << myMVAVar_gsfchi2
                    << " deta " <<  myMVAVar_deta
                    << " dphi " << myMVAVar_dphi
                    << " detacalo " << myMVAVar_detacalo
                    << " dphicalo " << myMVAVar_dphicalo
                    << " see " << myMVAVar_see
                    << " spp " << myMVAVar_spp
                    << " etawidth " << myMVAVar_etawidth
                    << " phiwidth " << myMVAVar_phiwidth
                    << " e1x5e5x5 " << myMVAVar_e1x5e5x5
                    << " R9 " << myMVAVar_R9
                    << " mynbrems " << myMVAVar_nbrems
                    << " HoE " << myMVAVar_HoE
                    << " EoP " << myMVAVar_EoP
                    << " IoEmIoP " << myMVAVar_IoEmIoP
                    << " eleEoPout " << myMVAVar_eleEoPout
                    << " EoPout " << myMVAVar_EoPout
                    << " PreShowerOverRaw " << myMVAVar_PreShowerOverRaw
                    << " d0 " << myMVAVar_d0
                    << " ip3d " << myMVAVar_ip3d
                    << " eta " << myMVAVar_eta
                    << " pt " << myMVAVar_pt << endl;
            }
        }

        // ----------member data ---------------------------
        edm::InputTag src_;
        std::string id_;
        EGammaMvaEleEstimator myMVANonTrig;
        bool recalMVA_;
        Float_t                   myMVAVar_fbrem;
        Float_t                   myMVAVar_kfchi2;
        Float_t                   myMVAVar_kfhits;
        Float_t                   myMVAVar_gsfchi2;

        Float_t                   myMVAVar_deta;
        Float_t                   myMVAVar_dphi;
        Float_t                   myMVAVar_detacalo;
        Float_t                   myMVAVar_dphicalo;

        Float_t                   myMVAVar_see;
        Float_t                   myMVAVar_spp;
        Float_t                   myMVAVar_etawidth;
        Float_t                   myMVAVar_phiwidth;
        Float_t                   myMVAVar_e1x5e5x5;
        Float_t                   myMVAVar_R9;
        Float_t                   myMVAVar_nbrems;

        Float_t                   myMVAVar_HoE;
        Float_t                   myMVAVar_EoP;
        Float_t                   myMVAVar_IoEmIoP;
        Float_t                   myMVAVar_eleEoPout;
        Float_t                   myMVAVar_PreShowerOverRaw;
        Float_t                   myMVAVar_EoPout;

        Float_t                   myMVAVar_d0;
        Float_t                   myMVAVar_ip3d;

        Float_t                   myMVAVar_eta;
        Float_t                   myMVAVar_pt;
};

