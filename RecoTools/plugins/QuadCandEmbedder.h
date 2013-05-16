/*  ---------------------
File: QuadCandEmbedder
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Embed some information about 4l candidates (angles, KDs, cross-leg inv. mass, etc.)
*/

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

#include "DataFormats/ParticleFlowCandidate/interface/PFCandidate.h"
#include "DataFormats/ParticleFlowCandidate/interface/PFCandidateFwd.h"

#include "Math/GenVector/VectorUtil.h"

#include "DataFormats/Math/interface/deltaR.h"
#include "TLorentzVector.h"

#include "ZZMatrixElement/MELA/interface/Mela.h"
#include "ZZMatrixElement/MELA/interface/PseudoMELA.h"
#include "ZZMatrixElement/MELA/interface/SpinTwoMinimalMELA.h"
#include "ZZMatrixElement/MEMCalculators/interface/MEMCalculators.h"


template <class T>
class QuadCandEmbedder : public edm::EDProducer {
    public:
        explicit QuadCandEmbedder(const edm::ParameterSet& iConfig)
        {
            src_ = iConfig.getParameter<edm::InputTag>("src");
            minMll_ = iConfig.getParameter<double>("minMll");
            produces<std::vector<T> >();
            Mela mela;
            PseudoMELA psMela;
            SpinTwoMinimalMELA spin2MMela;
            combinedMEM = MEMs(8.0);
        }

        ~QuadCandEmbedder() {}


    private:

        bool checkPassing(const edm::Ptr<pat::Electron> ele, double phoIso){
            bool pass = false;
            if (ele->userFloat("mvaNonTrigV0Pass")>0 && ele->gsfTrack()->trackerExpectedHitsInner().numberOfHits()<2 && ele->pt()>7 && fabs(ele->eta())<2.5 && fabs(ele->userFloat("ip3DS"))<4 && fabs(ele->userFloat("ipDXY"))<0.5 && fabs(ele->userFloat("dz"))<1.0 &&(ele->chargedHadronIso()+max(0.0,ele->neutralHadronIso()+phoIso-ele->userFloat("effArea")*ele->userFloat("zzRho2012")))/ele->pt()<0.4) pass=true;
            return pass;
        }

        bool checkPassing(const edm::Ptr<pat::Muon> mu, double phoIso){
            bool pass = false;
            if (mu->pfCandidateRef().isNonnull()&&(mu->isGlobalMuon()||mu->isTrackerMuon()) && fabs(mu->eta())<2.4 && mu->pt()>5 && fabs(mu->userFloat("ip3DS"))<4 && fabs(mu->userFloat("ipDXY"))<0.5 && fabs(mu->userFloat("dz"))<1.0 && (mu->chargedHadronIso()+max(0.0,mu->neutralHadronIso()+phoIso-mu->userFloat("effArea")*mu->userFloat("zzRho2012")))/mu->pt()<0.4) pass=true;
            return pass;
        }

        bool checkPassing(const edm::Ptr<pat::Tau> tau, double phoIso){
            bool pass = false;
            //check tau id here. There's a 99% chance this will never be used...
            return pass;
        }

        virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            using namespace edm;
            using namespace reco;
            std::vector<T> toBeSorted;
            Handle<std::vector<T> > cands;
            if(iEvent.getByLabel(src_,cands))
                toBeSorted =  *cands;

            std::auto_ptr<std::vector<T> > out(new std::vector<T>);
            for(unsigned int i = 0; i < toBeSorted.size(); ++i)
            {
                out->push_back(toBeSorted.at(i));
            }
            for (unsigned int i = 0; i < out->size(); ++i)
            {
                float costheta1=-137.0; float costheta2=-137.0; float phi=-137.0; float costhetastar=-137.0; float phistar1=-137.0; float phistar2=-137.0; float phistar12=-137.0; float phi1=-137.0; float phi2=-137.0;
                float kd=-137.0; float psig=-137.0; float pbkg=-137.0;
                float kdPS=-137.0; float psigPS=-137.0; float psigAltPS=-137.0;
                float kdS2M=-137.0; float psigS2M=-137.0; float psigAltS2M=-137.0;

                double hcp_kd         = -137.0;
                double hcp_ME_SMHiggs = -137.0;
                double hcp_ME_ggZZ    = -137.0;

                double moriond_kd         = -137.0;
                double moriond_ME_SMHiggs = -137.0;
                double moriond_ME_ggZZ    = -137.0;

                int nPass = 0;
                bool l1Pass = false; bool l2Pass = false; bool l3Pass = false; bool l4Pass = false;

                if (checkPassing(out->at(i).leg1()->leg1(),out->at(i).leg1()->leg1PhotonIso())) {nPass++; l1Pass=true; }
                if (checkPassing(out->at(i).leg1()->leg2(),out->at(i).leg1()->leg2PhotonIso())) {nPass++; l2Pass=true; }
                if (checkPassing(out->at(i).leg2()->leg1(),out->at(i).leg2()->leg1PhotonIso())) {nPass++; l3Pass=true; }
                if (checkPassing(out->at(i).leg2()->leg2(),out->at(i).leg2()->leg2PhotonIso())) {nPass++; l4Pass=true; }

                out->at(i).setPassingLeps(nPass,l1Pass,l2Pass,l3Pass,l4Pass);

                TLorentzVector HP4 = convertToTLorentz(out->at(i).p4());
                TLorentzVector z1P4 = convertToTLorentz(out->at(i).leg1()->p4());
                TLorentzVector z1l1P4 = convertToTLorentz(out->at(i).leg1()->leg1()->p4());
                TLorentzVector z1l2P4 = convertToTLorentz(out->at(i).leg1()->leg2()->p4());
                TLorentzVector pho1P4 = z1P4 - z1l1P4 - z1l2P4;

                TLorentzVector z2P4 = convertToTLorentz(out->at(i).leg2()->p4());
                TLorentzVector z2l1P4 = convertToTLorentz(out->at(i).leg2()->leg1()->p4());
                TLorentzVector z2l2P4 = convertToTLorentz(out->at(i).leg2()->leg2()->p4());
                TLorentzVector pho2P4 = z2P4 - z2l1P4 - z2l2P4;

                // vector of lepton 4-vectors
                std::vector<TLorentzVector> partP;
                partP.push_back( z1l1P4 );
                partP.push_back( z1l2P4 );
                partP.push_back( z2l1P4 );
                partP.push_back( z2l2P4 );

                // vector of lepton pdgIDs
                std::vector<int> partId;
                partId.push_back( out->at(i).leg1()->leg1()->pdgId() );
                partId.push_back( out->at(i).leg1()->leg2()->pdgId() );
                partId.push_back( out->at(i).leg2()->leg1()->pdgId() );
                partId.push_back( out->at(i).leg2()->leg2()->pdgId() );

                TLorentzVector temp;
                if (out->at(i).leg1()->leg1()->charge() >0 ){ //make sure angles are calculated wrt negative lepton
                    temp=z1l1P4;
                    z1l1P4=z1l2P4;
                    z1l2P4=temp;
                }
                if (out->at(i).leg2()->leg1()->charge() >0 ){
                    temp=z2l1P4;
                    z2l1P4=z2l2P4;
                    z2l2P4=temp;
                }

                bool fourFour = false;
                bool sixSix = false;

                int charge11 = out->at(i).leg1()->leg1()->charge();
                int charge12 = out->at(i).leg1()->leg2()->charge();
                int charge21 = out->at(i).leg2()->leg1()->charge();
                int charge22 = out->at(i).leg2()->leg2()->charge();

                if (charge11+charge12==0 && charge21+charge22==0) {
                    // compute the HCP and Moriond KDs
                    try{
                        combinedMEM.computeMEs( partP, partId ); //this breaks (in mela, apparently) for poor candidates
                        combinedMEM.computeKD(MEMNames::kSMHiggs, MEMNames::kJHUGen, MEMNames::kqqZZ, MEMNames::kMCFM, &MEMs::probRatio, moriond_kd, moriond_ME_SMHiggs, moriond_ME_ggZZ);
                        combinedMEM.computeKD(MEMNames::kSMHiggs, MEMNames::kMELA_HCP, MEMNames::kqqZZ, MEMNames::kMELA_HCP, &MEMs::probRatio, hcp_kd, hcp_ME_SMHiggs, hcp_ME_ggZZ);
                    }
                    catch(...){
                        edm::LogWarning("QuadCandEmbedder") << "WARNING: Something went wrong in the computeMEs function." <<
                            "Probably some MELA angles were calculated to nan.\n" <<
                            "I don't want to crash everything, so I'm just going to keep cruisin'. You've been warned." << std::endl;
                        moriond_ME_ggZZ = -137.0; //I'll set these guys back to -137, since I don't really know what happens to their values if the computeMEs fails
                        hcp_ME_ggZZ = -137.0;
                    }
                }

                bool check11=false;
                bool check12=false;

                if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg1()->leg2()->p4())).M() > minMll_){
                    if (((out->at(i).leg2()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_){

                        //check OS combinations between legs
                        if (charge11!=charge21){
                            if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_) check11=true;
                        } else if (charge11!=charge22){
                            if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_) check11=true;
                        }

                        if (charge12!=charge21){
                            if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_) check12=true;
                        } else if (charge12!=charge22){
                            if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_) check12=true;
                        }
                        if (check11 && check12) {
                            fourFour=true;
                        }
                    }
                }

                if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg1()->leg2()->p4())).M() > minMll_)
                    if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_)
                        if (((out->at(i).leg1()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_)
                            if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg1()->p4())).M() > minMll_)
                                if (((out->at(i).leg1()->leg2()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_)
                                    if (((out->at(i).leg2()->leg1()->p4())+(out->at(i).leg2()->leg2()->p4())).M() > minMll_)
                                        sixSix=true;

                mela.computeKD(z1l1P4, out->at(i).leg1()->leg1()->pdgId(), z1l2P4, out->at(i).leg1()->leg2()->pdgId(), z2l1P4, out->at(i).leg2()->leg1()->pdgId(), z2l2P4, out->at(i).leg2()->leg2()->pdgId(),
                        costhetastar, costheta1, costheta2, phi, phistar1, kd, psig, pbkg);
                psMela.computeKD(z1l1P4, out->at(i).leg1()->leg1()->pdgId(), z1l2P4, out->at(i).leg1()->leg2()->pdgId(), z2l1P4, out->at(i).leg2()->leg1()->pdgId(), z2l2P4, out->at(i).leg2()->leg2()->pdgId(),
                        kdPS, psigPS, psigAltPS);
                spin2MMela.computeKD(z1l1P4, out->at(i).leg1()->leg1()->pdgId(), z1l2P4, out->at(i).leg1()->leg2()->pdgId(), z2l1P4, out->at(i).leg2()->leg1()->pdgId(), z2l2P4, out->at(i).leg2()->leg2()->pdgId(),
                        kdS2M, psigS2M, psigAltS2M);

                out->at(i).setAngles(costheta1, costheta2, phi, costhetastar, phistar1, phistar2, phistar12, phi1, phi2, kd, psig, pbkg, kdPS, psigPS, psigAltPS, kdS2M, psigS2M, psigAltS2M);

                // add the HCP and Moriond KDs to the candidate
                out->at(i).setKDs( hcp_kd, moriond_kd );

                out->at(i).setNoFSRMass((out->at(i).leg1()->noPhoP4()+out->at(i).leg2()->noPhoP4()).M());
                out->at(i).setInvMasses(out->at(i).leg1()->leg1()->p4(),out->at(i).leg1()->leg2()->p4(),out->at(i).leg2()->leg1()->p4(),out->at(i).leg2()->leg2()->p4(),fourFour,sixSix);

                double bestZmass;
                double subBestZmass;
                double z1mass = z1P4.M();
                double z2mass = z2P4.M();
                if ( fabs(z1mass - 91.2) < fabs(z2mass - 91.2) )
                {
                    bestZmass    = z1mass;
                    subBestZmass = z2mass;
                }
                else
                {
                    bestZmass    = z2mass;
                    subBestZmass = z1mass;
                }
                out->at(i).setBestZmasses(bestZmass, subBestZmass);
            }
            iEvent.put(out);

        }

        TLorentzVector convertToTLorentz(const reco::Candidate::LorentzVector& lorV){
            TLorentzVector out;
            out.SetPxPyPzE( lorV.px(), lorV.py(), lorV.pz(), lorV.energy() );
            return out;
        }

        // ----------member data ---------------------------
        edm::InputTag src_;
        double minMll_;
        Mela mela;
        PseudoMELA psMela;
        SpinTwoMinimalMELA spin2MMela;
        MEMs combinedMEM;

};
