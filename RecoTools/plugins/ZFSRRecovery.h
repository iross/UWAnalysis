#ifndef UWAnalysis_RecoTools_ZFSRRecovery_h
#define UWAnalysis_RecoTools_ZFSRRecovery_h

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"

#include "DataFormats/Common/interface/View.h"
#include "DataFormats/PatCandidates/interface/PFParticle.h"

#include "DataFormats/Math/interface/deltaR.h"

#include "UWAnalysis/RecoTools/interface/FetchCollection.h"

#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEtFwd.h"

#include "UWAnalysis/RecoTools/interface/CompositePtrCandidateT1T2MEtAlgorithm.h"

#include "DataFormats/HepMCCandidate/interface/GenParticleFwd.h"
#include "DataFormats/HepMCCandidate/interface/GenParticle.h"

#include <string>

template<typename T1>
class ZFSRRecovery : public edm::EDProducer 
{
    typedef edm::Ptr<T1> T1Ptr;

    typedef std::vector<T1> CompositePtrCandidateCollection;
    public:

    explicit ZFSRRecovery(const edm::ParameterSet& cfg)
    {

        src_ = cfg.getParameter<edm::InputTag>("src");
        eSrc_ = cfg.getParameter<edm::InputTag>("eSrc");
        mSrc_ = cfg.getParameter<edm::InputTag>("mSrc");
        gSrc_ = cfg.getParameter<edm::InputTag>("gSrc");

        produces<CompositePtrCandidateCollection>("");
    }

    ~ZFSRRecovery() {}

    void produce(edm::Event& evt, const edm::EventSetup& es)
    {
        std::auto_ptr<CompositePtrCandidateCollection> newColl(new CompositePtrCandidateCollection());
        //get Z candidates
        typedef edm::View<T1> T1View;
        edm::Handle<T1View> collection;
        pf::fetchCollection(collection, src_, evt);

        //get photon collection
        edm::Handle<pat::PFParticleCollection> photons;
        edm::Handle<pat::MuonCollection> muons;
        edm::Handle<pat::ElectronCollection> electrons;
        pf::fetchCollection(photons, gSrc_, evt);

        pat::PFParticleCollection goodPhotons;
        std::vector<double> lepPts;
        std::vector<double> dRs;

        double z0=91.1876;
        evt.getByLabel(gSrc_,photons);
        if(evt.getByLabel(gSrc_,photons) && evt.getByLabel(eSrc_,electrons) && evt.getByLabel(mSrc_,muons) ){
            for (unsigned int j = 0; j < photons->size(); j++) {
                //first remove photons that overlap with SCs of IDed electrons
//                std::cout << photons->at(j).pt() << " (eta, phi): " << photons->at(j).eta() << " " << photons->at(j).phi() << std::endl;
                bool scOL=false;
                bool muMatch=false;
                bool eleMatch=false;
                bool closeMatch=false;
                double lepPt=0.0;
                double mindR=0.5;
                for (unsigned int i = 0; i < electrons->size(); ++i) {
                    if (electrons->at(i).userFloat("mvaNonTrigV0Pass")>0 && electrons->at(i).pt()>7 && fabs(electrons->at(i).eta())<2.5 && abs(electrons->at(i).userFloat("ip3DS"))<4){
//                        if ((abs(electrons->at(i).superCluster()->phi()-photons->at(j).phi()) < 2 && abs(electrons->at(i).superCluster()->eta()-photons->at(j).eta())<0.05) || deltaR(electrons->at(i).superCluster()->eta(),electrons->at(i).superCluster()->phi(),photons->at(j).eta(),photons->at(j).phi())<0.15){
                        //apparently this veto is for electrons, NOT electron SC.
                        if ((abs(electrons->at(i).phi()-photons->at(j).phi()) < 2 && abs(electrons->at(i).eta()-photons->at(j).eta())<0.05) || deltaR(electrons->at(i).eta(),electrons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi())<0.15){
//                            std::cout << "eSC:" << " (eta, phi): " << electrons->at(i).superCluster()->eta() << " " << electrons->at(i).superCluster()->phi() << std::endl;
//                            std::cout << "e:" << electrons->at(i).pt() << " (eta, phi): " << electrons->at(i).eta() << " " << electrons->at(i).phi() << std::endl;
//                            std::cout << "photon: " << photons->at(j).pt() << " (eta, phi): " << photons->at(j).eta() << " " << photons->at(j).phi() << std::endl;
                            scOL=true;
                        } 
                    } else continue;
                }
                if (!scOL) { 
                    //then find closest lepton and apply req. on photon which depends on dR to the closest lepton
                    for (unsigned int i = 0; i < electrons->size(); ++i) {
                        if (electrons->at(i).userFloat("mvaNonTrigV0Pass")>0 && electrons->at(i).pt()>7 && fabs(electrons->at(i).eta())<2.5 && abs(electrons->at(i).userFloat("ip3DS"))<4){
                            if (deltaR(electrons->at(i).eta(),electrons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi()) < mindR){
                                mindR=deltaR(electrons->at(i).eta(),electrons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi());   
                                lepPt=electrons->at(i).pt();
                                eleMatch=true;
                            }
                        }
                    }                                                           
                    for (unsigned int i = 0; i < muons->size(); ++i) {
                        if ((muons->at(i).isTrackerMuon() || muons->at(i).isGlobalMuon()) && muons->at(i).pfCandidateRef().isNonnull()){
                            if (deltaR(muons->at(i).eta(),muons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi()) < mindR){
                                mindR=deltaR(muons->at(i).eta(),muons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi());   
                                lepPt=muons->at(i).pt();
                                muMatch=true;
                            }
                        }

                    }
                    if (mindR<0.07) closeMatch=true;
                    //now check iso based on closest match
//                    if dR(gamma,l) < 0.07, accept the photon if it has pT > 2 GeV
//                    otherwise, if dR(gamma,l) < 0.5, accept the photon if it has pT > 4 GeV and a PF relative isolation less than 1.0. 
                    if (closeMatch){
                        if (photons->at(j).pt()>2) {
                            goodPhotons.push_back( photons->at(j) );
                            lepPts.push_back( lepPt );
                            dRs.push_back( mindR );
                        }
                    } else if ((eleMatch||muMatch) && mindR<0.5) {
                        float relIso=(photons->at(j).userFloat("fsrPhotonPFIsoChHad03pt02")+photons->at(j).userFloat("fsrPhotonPFIsoNHad03")+photons->at(j).userFloat("fsrPhotonPFIsoPhoton03"))/photons->at(j).pt();
                        if (relIso < 1.0 && photons->at(j).pt()>4){
                            goodPhotons.push_back( photons->at(j) );
                            lepPts.push_back( lepPt );
                            dRs.push_back( mindR );
                        }
                    } else {
//                        float relIso=(photons->at(j).userFloat("fsrPhotonPFIsoChHad03pt02")+photons->at(j).userFloat("fsrPhotonPFIsoNHad03")+photons->at(j).userFloat("fsrPhotonPFIsoPhoton03"))/photons->at(j).pt();
//                        std::cout << "minDR: " << mindR << std::endl;
//                        std::cout << photons->at(j).pt() << "(eta, phi): " << photons->at(j).eta() << " " << photons->at(j).phi() << std::endl;
//                        std::cout << "Photon reliso: " << relIso << std::endl;
//                        std::cout << photons->at(j).userFloat("fsrPhotonPFIsoChHad03pt02") << "+" << photons->at(j).userFloat("fsrPhotonPFIsoNHad03")<<"+"<<photons->at(j).userFloat("fsrPhotonPFIsoPhoton03") << std::endl;
                    }
                }
            }
        }
        for (unsigned int i = 0; i < collection->size(); ++i) {
            newColl->push_back(collection->at(i));
            double leg1iso=newColl->at(i).leg1()->photonIso();
            double leg2iso=newColl->at(i).leg2()->photonIso();
            newColl->at(i).setFSRVariables(-999.0, -999.0, -999.0, -999.0, -999.0, newColl->at(i).p4(), leg1iso, leg2iso);
            for (unsigned int j = 0; j < goodPhotons.size(); ++j) {
                double newM = (newColl->at(i).p4() + goodPhotons.at(j).p4()).M();
                if ( (abs(newM-z0) < abs(newColl->at(i).mass()-z0)) && newM>4 && newM<100 && (newColl->at(i).leg1()->pt()==lepPts.at(j)|| newColl->at(i).leg2()->pt()==lepPts.at(j))){
//                    std::cout << "Pt matched: " << lepPts.at(j) << "is " << newColl->at(i).leg1()->pt() << " or " << newColl->at(i).leg2()->pt() << std::endl;
//                    std::cout << "Z candidate improved! Old mass: " << newColl->at(i).mass() << ", new mass: " << newM << std::endl;
                    //remove photon from lepton isolations
//                    if (dRs.at(j) < 0.4 && dRs.at(j) > 0.005){
                    if (deltaR(newColl->at(i).leg1()->eta(),newColl->at(i).leg1()->phi(),goodPhotons.at(j).eta(),goodPhotons.at(j).phi()) < 0.4){
                        leg1iso=leg1iso-goodPhotons.at(j).pt();
                    }
                    if (deltaR(newColl->at(i).leg2()->eta(),newColl->at(i).leg2()->phi(),goodPhotons.at(j).eta(),goodPhotons.at(j).phi()) < 0.4){
                        leg2iso=leg2iso-goodPhotons.at(j).pt();
                    }
                    //set the new p4, save the old one
                    newColl->at(i).setP4(newColl->at(i).p4()+goodPhotons.at(j).p4());
                    newColl->at(i).setFSRVariables(goodPhotons.at(j).pt(), goodPhotons.at(j).eta(), goodPhotons.at(j).phi(), dRs.at(j), lepPts.at(j), collection->at(i).p4(), leg1iso, leg2iso);
                }
            }
        }
        for (unsigned int i = 0; i < newColl->size(); ++i) {
            std::cout << newColl->at(i).mass() << ", " << newColl->at(i).noPhoP4().M() << std::endl;
//            std::cout << newColl->at(i).phoEta() << std::endl;
//            std::cout << newColl->at(i).phoPhi() << std::endl;
//            std::cout << newColl->at(i).phoPt() << std::endl;
            std::cout << newColl->at(i).leg1()->photonIso() << ", " << newColl->at(i).leg1PhotonIso() << std::endl;
            std::cout << newColl->at(i).leg2()->photonIso() << ", " << newColl->at(i).leg2PhotonIso() << std::endl;
        }
        evt.put(newColl);
    }

    private:

    edm::InputTag src_;
    edm::InputTag eSrc_;
    edm::InputTag mSrc_;
    edm::InputTag gSrc_;

};

#endif

