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
        std::auto_ptr<CompositePtrCandidateCollection> compositePtrCandidateCollection(new CompositePtrCandidateCollection());
        //get Z candidates
        typedef edm::View<T1> T1View;
        edm::Handle<T1View> collection;
        //        pf::fetchCollection(collection, src_, evt);
        std::vector<T1> temp;

        //get photon collection
        edm::Handle<pat::PFParticleCollection> photons;
        edm::Handle<pat::MuonCollection> muons;
        edm::Handle<pat::ElectronCollection> electrons;
        pf::fetchCollection(photons, gSrc_, evt);

        pat::PFParticleCollection goodPhotons;

        double z0=91.1876;
        evt.getByLabel(gSrc_,photons);
        if(evt.getByLabel(gSrc_,photons) && evt.getByLabel(eSrc_,electrons) && evt.getByLabel(mSrc_,muons) ){
            for (unsigned int j = 0; j < photons->size(); j++) {
                //first remove photons that overlap with SCs of IDed electrons
                bool scOL=false;
                bool muMatch=false;
                bool eleMatch=false;
                bool closeMatch=false;
                double mindR=999.;
                for (unsigned int i = 0; i < electrons->size(); ++i) {
                    if (electrons->at(i).userFloat("mvaNonTrigV0Pass")>0 && electrons->at(i).pt()>7 && fabs(electrons->at(i).eta())<2.5 && abs(electrons->at(i).userFloat("ip3DS"))<4){
                        if (abs(electrons->at(i).superCluster()->phi()-photons->at(j).phi()) < 2 || abs(electrons->at(i).superCluster()->eta()-photons->at(j).eta())<0.05 || deltaR(electrons->at(i).superCluster()->eta(),electrons->at(i).superCluster()->phi(),photons->at(j).eta(),photons->at(j).phi())<0.15){
                            //                            std::cout << "Overlaps with a pretty good electron!" << std::endl;
                            scOL=true;
                        } 
                    } else continue;
                }
                if (!scOL) { 
                    //then find closest lepton and apply req. on photon which depends on dR to the closest lepton
                    for (unsigned int i = 0; i < electrons->size(); ++i) {
                        if (electrons->at(i).userFloat("mvaNonTrigV0Pass")>0 && electrons->at(i).pt()>7 && fabs(electrons->at(i).eta())<2.5 && abs(electrons->at(i).userFloat("ip3DS"))<4){
                            if (deltaR(electrons->at(i).eta(),electrons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi()) < 0.5){
                                mindR=deltaR(electrons->at(i).eta(),electrons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi());   
                                eleMatch=true;
                            }
                        }
                    }                                                           
                    for (unsigned int i = 0; i < muons->size(); ++i) {
                        if ((muons->at(i).isTrackerMuon() || muons->at(i).isGlobalMuon()) && muons->at(i).pfCandidateRef().isNonnull()){
                            if (deltaR(muons->at(i).eta(),muons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi()) < 0.5){
                                mindR=deltaR(muons->at(i).eta(),muons->at(i).phi(),photons->at(j).eta(),photons->at(j).phi());   
                                muMatch=true;
                            }
                        }

                    }
                    if (mindR<0.07) closeMatch=true;
                    //now check iso based on closest match
//                    if dR(gamma,l) < 0.07, accept the photon if it has pT > 2 GeV
//                    otherwise, if dR(gamma,l) < 0.5, accept the photon if it has pT > 4 GeV and a PF relative isolation less than 1.0. 
                    if (closeMatch){
                        if (photons->at(j).pt()>2) goodPhotons.push_back( photons->at(j) );
                    } else if ((eleMatch||muMatch) && mindR<0.5) {
                        float relIso=(photons->at(j).userFloat("fsrPhotonPFIsoChHad03pt02")+photons->at(j).userFloat("fsrPhotonPFIsoNHad03")+photons->at(j).userFloat("fsrPhotonPFIsoPhoton03"))/photons->at(j).pt();
                        if (relIso < 1.0 && photons->at(j).pt()>4) goodPhotons.push_back( photons->at(j) );
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
        std::cout << goodPhotons.size() << " GOOD PHOTONS FOUND!" << std::endl;
        //loop over Z candidates, add in photons, etc.
        //if we're keeping it, we need to remove the photon from the leptons' isolation cones.
        evt.put(compositePtrCandidateCollection);
    }

    private:

    edm::InputTag src_;
    edm::InputTag eSrc_;
    edm::InputTag mSrc_;
    edm::InputTag gSrc_;

};

#endif

