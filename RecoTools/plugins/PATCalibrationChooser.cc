/*  ---------------------
File: PATCalibrationChooser
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Switch lepton to the specified calibration+regression (or Rochestor corr) combination
Regression types: NoTrackVars, WithTrackVars, NoRegression
Calibration types: SmearedRegression, RegressionOnly, SmearedNoRegression
Rochester Correction types: RochCor2011A, RochCor2011B, RochCor2012
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

#include "Math/GenVector/VectorUtil.h"

//template<class T>
//reco::TransientTrack getTrack(const T& cand, const TransientTrackBuilder& builder);
//template<>
//reco::TransientTrack getTrack<pat::Muon>(const pat::Muon& muon, const TransientTrackBuilder& builder) { return builder.build(muon.innerTrack()); }
//template<>
//reco::TransientTrack getTrack<pat::Electron>(const pat::Electron& electron, const TransientTrackBuilder& builder) { return builder.build(electron.gsfTrack()); }
//template<>
//reco::TransientTrack getTrack<pat::Tau>(const pat::Tau& tau, const TransientTrackBuilder& builder) {
//    if (tau.signalPFChargedHadrCands()[0]->trackRef().isNonnull()) return (builder.build(tau.signalPFChargedHadrCands()[0]->trackRef()));
//    else return (builder.build(tau.signalPFChargedHadrCands()[0]->gsfTrackRef()));
//}

template <typename T>
class PATCalibrationChooser : public edm::EDProducer {
    public:
        explicit PATCalibrationChooser(const edm::ParameterSet& iConfig):
            src_(iConfig.getParameter<edm::InputTag>("src")),
            regressionType_(iConfig.existsAs<std::string>("regType") ? iConfig.getParameter<std::string>("regType") : "dummy"),
            calibrationType_(iConfig.existsAs<std::string>("calType") ? iConfig.getParameter<std::string>("calType") : "dummy"),
            rochcorType_(iConfig.existsAs<std::string>("rochcorType") ? iConfig.getParameter<std::string>("rochcorType") : "dummy")
            {
                produces<std::vector<T> >();
            }

        ~PATCalibrationChooser() {}
    private:
        virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            using namespace edm;
            using namespace reco;
            std::auto_ptr<std::vector<T> > out(new std::vector<T>);
            Handle<std::vector<T> > cands;

            if(iEvent.getByLabel(src_,cands))
                for(unsigned int  i=0;i!=cands->size();++i){
                    T lepton = cands->at(i);
                    std::cout << "Before:" << cands->at(i).pt() << std::endl;
                    const math::XYZTLorentzVector* temp = getUserLorentzVector(lepton);
                    if (temp==NULL) {
                        printf("Could not find corrected P4 with label EGCorr_%s%s\n",calibrationType_.c_str(),regressionType_.c_str());
                        lepton.setP4(cands->at(i).p4());
                    } else {
                        lepton.setP4(*temp);
                    }

                    std::cout << lepton.pt() << std::endl;
                    out->push_back(lepton);
                }
            iEvent.put(out);
        }

//        const math::XYZTLorentzVector* getUserLorentzVector(pat::Muon cand)
//        {
//            const math::XYZTLorentzVector* p4 = cand.userData<math::XYZTLorentzVector>("p4_"+rochcorType__);
//            return p4;
//        }

        const math::XYZTLorentzVector* getUserLorentzVector(pat::Electron cand)
        {
            const math::XYZTLorentzVector* p4 = cand.userData<math::XYZTLorentzVector>("EGCorr_"+calibrationType_+regressionType_);
            return p4;

        }

        // ----------member data ---------------------------
        edm::InputTag src_;
        std::string regressionType_;
        std::string calibrationType_;
        std::string rochcorType_;
};

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"

typedef PATCalibrationChooser<pat::Electron> PATElectronCalibrationChooser;
DEFINE_FWK_MODULE(PATElectronCalibrationChooser);
