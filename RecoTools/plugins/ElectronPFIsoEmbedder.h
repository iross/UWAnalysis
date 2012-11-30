/*  ---------------------
File: ElectronPFIsoEmbedder
Author: Ian Ross (iross@cern.ch), University of Wisconsin Madison
Description: Embed a bunch of userData into a PATElectron collection
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

#include "RecoEgamma/EgammaTools/interface/ConversionTools.h"

#include "DataFormats/BeamSpot/interface/BeamSpot.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"

#include "RecoEcal/EgammaCoreTools/interface/EcalClusterLazyTools.h"
#include "Utilities/General/interface/FileInPath.h"

#include "DataFormats/Common/interface/ValueMap.h"
#include "PhysicsTools/PatAlgos/interface/MultiIsolator.h"

#include "Math/GenVector/VectorUtil.h"
//
// class decleration



class ElectronPFIsoEmbedder : public edm::EDProducer {
    typedef std::pair<pat::IsolationKeys,edm::InputTag> IsolationLabel;
    typedef std::vector<IsolationLabel> IsolationLabels;
    typedef std::vector< edm::Handle< edm::ValueMap<double> > > IsolationValueMaps;
    public:

    explicit ElectronPFIsoEmbedder(const edm::ParameterSet& iConfig):
        src_(iConfig.getParameter<edm::InputTag>("src"))
//        isoValueMaps_(iConfig.getParameter<std::vector<edm::InputTag> >("valueMaps"))
    {
        produces<pat::ElectronCollection>();
        readIsolationLabels(iConfig, "isolationValues", isolationValueLabels_);
    }

    ~ElectronPFIsoEmbedder() {}

    private:

    virtual void produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
    {
        using namespace edm;
        using namespace reco;
        std::auto_ptr<pat::ElectronCollection > out(new pat::ElectronCollection);

        IsolationValueMaps isolationValues(isolationValueLabels_.size());
        std::cout << isolationValueLabels_.size() << " labels" << std::endl;
        std::cout << isolationValues.size() << " values" << std::endl;
        for (size_t j = 0; j<isoValueMaps_.size(); ++j) {
            iEvent.getByLabel(isolationValueLabels_[j].second, isolationValues[j]);
        }

        std::cout << "dumping iso values" << std::endl;
        for (unsigned int i = 0; i < isolationValues.size(); ++i) {
            std::cout << isolationValueLabels_.size() << " labels" << std::endl;
            std::cout << isolationValues.size() << " values" << std::endl;
            std::cout << isolationValueLabels_[i].first << std::endl;
            std::cout << isolationValueLabels_[i].second << std::endl;
//            std::cout << *isolationValues[i] << std::endl;
        }

        Handle<pat::ElectronCollection > cands;
        if(iEvent.getByLabel(src_,cands))
            for(unsigned int  i=0;i!=cands->size();++i){
                pat::Electron ele(cands->at(i));
                std::cout << ele << std::endl;
                std::vector<std::string> labels = ele.userFloatNames();
                std::cout << labels.size() << " size before" << std::endl;
                ele.addUserFloat("test",1237.0);
                labels = ele.userFloatNames();
                std::cout << labels.size() << " size after" << std::endl;
                //                    for (unsigned int i = 0; i < labels.size(); ++i) {
                //                        std::cout << labels.at(i) << std::endl;
                //                    }
                for (size_t j = 0; j<isolationValues.size(); ++j) {
//                    reco::CandidatePtr source = ele.pfCandidateRef()->sourceCandidatePtr(0);
//                    reco::GsfElectronRef test = ele.originalObjectRef();
                    edm::Handle<reco::GsfElectronCollection> gsfElectronH;
                    bool test = iEvent.getByLabel("gsfElectrons",gsfElectronH);
                    if (test)
                     for(unsigned iele=0; iele<gsfElectronH->size();++iele) {
                         reco::GsfElectronRef myElectronRef(gsfElectronH,iele);
                         std::cout << "got that ref" << std::endl;
                         std::cout << isolationValueLabels_[j].second << std::endl;
                        double iso = (*isolationValues[j])[myElectronRef];
                        std::cout << iso << std::endl;
                     }
                    else std::cout << "Shiiit. I couldn't get those electrons :(" << std::endl;

//                    std::cout << (*(isolationValues)[j])[test] << std::endl;
                }
                out->push_back(ele);
            }
        iEvent.put(out);

    }
    virtual void readIsolationLabels( const edm::ParameterSet & iConfig,
            const char* psetName,
            IsolationLabels& labels) {

        labels.clear();

        if (iConfig.exists( psetName )) {
            edm::ParameterSet depconf
                = iConfig.getParameter<edm::ParameterSet>(psetName);

            if (depconf.exists("tracker")) labels.push_back(std::make_pair(pat::TrackIso, depconf.getParameter<edm::InputTag>("tracker")));
            if (depconf.exists("ecal"))    labels.push_back(std::make_pair(pat::EcalIso, depconf.getParameter<edm::InputTag>("ecal")));
            if (depconf.exists("hcal"))    labels.push_back(std::make_pair(pat::HcalIso, depconf.getParameter<edm::InputTag>("hcal")));
            if (depconf.exists("pfAllParticles"))  {
                labels.push_back(std::make_pair(pat::PfAllParticleIso, depconf.getParameter<edm::InputTag>("pfAllParticles")));
            }
            if (depconf.exists("pfChargedHadrons"))  {
                labels.push_back(std::make_pair(pat::PfChargedHadronIso, depconf.getParameter<edm::InputTag>("pfChargedHadrons")));
            }
            if (depconf.exists("pfChargedAll"))  {
                labels.push_back(std::make_pair(pat::PfChargedAllIso, depconf.getParameter<edm::InputTag>("pfChargedAll")));
            }
            if (depconf.exists("pfPUChargedHadrons"))  {
                labels.push_back(std::make_pair(pat::PfPUChargedHadronIso, depconf.getParameter<edm::InputTag>("pfPUChargedHadrons")));
            }
            if (depconf.exists("pfNeutralHadrons"))  {
                labels.push_back(std::make_pair(pat::PfNeutralHadronIso, depconf.getParameter<edm::InputTag>("pfNeutralHadrons")));
            }
            if (depconf.exists("pfPhotons")) {
                labels.push_back(std::make_pair(pat::PfGammaIso, depconf.getParameter<edm::InputTag>("pfPhotons")));
            }
            if (depconf.exists("user")) {
                std::vector<edm::InputTag> userdeps = depconf.getParameter<std::vector<edm::InputTag> >("user");
                std::vector<edm::InputTag>::const_iterator it = userdeps.begin(), ed = userdeps.end();
                int key = pat::UserBaseIso;
                for ( ; it != ed; ++it, ++key) {
                    labels.push_back(std::make_pair(pat::IsolationKeys(key), *it));
                }
            }
        }
        std::cout << labels.size() << " labels read"  << std::endl;


    }


    // ----------member data ---------------------------
    edm::InputTag src_;
    std::vector<edm::InputTag> isoValueMaps_;
    IsolationLabels isolationValueLabels_;
};

