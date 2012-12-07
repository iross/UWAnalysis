/*  ---------------------
File: PATCalibrationChooser
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Switch lepton to the specified calibration+regression (or Rochestor corr) combination
Calibration types: SmearedRegression, RegressionOnly, SmearedNoRegression

Available calibration targets:
 2012 Data : 2012Jul13ReReco, Summer12_DR53X_HCP2012,
             Prompt, ReReco, ICHEP2012
 2012 MC   : Summer12, Summer12_DR53X_HCP2012
 2011 Data : Jan16ReReco
 2011 MC   : Summer11, Fall11

Rochester Correction types: RochCor2011A, RochCor2011B, RochCor2012

*/
// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDProducer.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Framework/interface/Event.h"

#include "DataFormats/PatCandidates/interface/Electron.h"
#include "DataFormats/PatCandidates/interface/Muon.h"

template <typename T>
class PATCalibrationChooser : public edm::EDProducer {
    public:
        explicit PATCalibrationChooser(const edm::ParameterSet& iConfig):
            src_(iConfig.getParameter<edm::InputTag>("src")),
            correctionType_(iConfig.existsAs<std::string>("corrType") ? iConfig.getParameter<std::string>("corrType") : "dummy"),
            calibrationTarget_(iConfig.existsAs<std::string>("calTarget") ? iConfig.getParameter<std::string>("calTarget") : "dummy"),
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
                    const math::XYZTLorentzVector* temp = getUserLorentzVector(lepton);
                    if (temp==NULL) {
                        lepton.setP4(cands->at(i).p4());
                    } else {
                        lepton.setP4(*temp);
                    }
                    out->push_back(lepton);
                }
            iEvent.put(out);
        }

        const math::XYZTLorentzVector* getUserLorentzVector(pat::Muon cand)
        {
            const math::XYZTLorentzVector* p4 = cand.userData<math::XYZTLorentzVector>("p4_"+rochcorType_);
            if (p4 == NULL) {
                edm::LogWarning("CalibrationChooser") << "Could not find corrected p4 with label p4_" << rochcorType_ << "!" << std::endl;
            }
            return p4;
        }

        const math::XYZTLorentzVector* getUserLorentzVector(pat::Electron cand)
        {
            const math::XYZTLorentzVector* p4 = cand.userData<math::XYZTLorentzVector>("EGCorr_"+calibrationTarget_+correctionType_);
            if (p4 == NULL) {
                edm::LogWarning("CalibrationChooser") << "Could not find corrected p4 with label p4_" << calibrationTarget_ << correctionType_ << "!" << std::endl;
            }
            return p4;

        }

        // ----------member data ---------------------------
        edm::InputTag src_;
        std::string correctionType_;
        std::string calibrationTarget_;
        std::string rochcorType_;
};

#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/PluginManager/interface/ModuleDef.h"

typedef PATCalibrationChooser<pat::Electron> PATElectronCalibrationChooser;
DEFINE_FWK_MODULE(PATElectronCalibrationChooser);
typedef PATCalibrationChooser<pat::Muon> PATMuonCalibrationChooser;
DEFINE_FWK_MODULE(PATMuonCalibrationChooser);
