// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "DataFormats/Candidate/interface/Candidate.h"
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"


#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBaseMultiCand.h"


#include <TTree.h>

template<typename T,typename U>
class EventTreeMaker : public edm::EDAnalyzer {
    public:
        explicit EventTreeMaker(const edm::ParameterSet& iConfig)
        {

            typedef std::vector<edm::ParameterSet> VPSet;

            edm::Service<TFileService> fs;
            t = fs->make<TTree>( "eventTree"  , "");

            t->Branch("EVENT",&EVENT,"EVENT/i");
            t->Branch("RUN",&RUN,"RUN/i");
            t->Branch("LUMI",&LUMI,"LUMI/i");
            coreColl = iConfig.getParameter<std::vector<edm::InputTag> >("coreCollections");
            leadingOnly_ = iConfig.getParameter<bool>("leadingOnly");

            std::vector<std::string> branchNames = iConfig.getParameterNamesForType<edm::ParameterSet>();
            for ( std::vector<std::string>::const_iterator branchName = branchNames.begin();
                    branchName != branchNames.end(); ++branchName ) {
                std::cout << " reading configuration parameters for Branch = " << (*branchName) << std::endl;

                edm::ParameterSet ntupleFillerCfg = iConfig.getParameter<edm::ParameterSet>(*branchName);
                std::string fillerPlugin = ntupleFillerCfg.getParameter<std::string>("pluginType");
                //Need to do this separately for non-templated
                if (fillerPlugin.find("QuadFiller") != std::string::npos || fillerPlugin.find("TriFiller") != std::string::npos || fillerPlugin.find("PairFiller") != std::string::npos) {
                    NtupleFillerBaseMultiCand<T>* filler = U::get()->create(fillerPlugin,ntupleFillerCfg,t);
                    fillers.push_back(filler);
                } else {
                    NtupleFillerBase* filler = NtupleFillerFactory::get()->create(fillerPlugin,ntupleFillerCfg,t);
                    sharedFillers.push_back(filler);
                }
            }

            //if Ian's VPsets exist, add them to the fillers.
            VPSet plugins;
            VPSet zzShared = iConfig.exists("zzShared") ? iConfig.getParameter<VPSet>("zzShared") : VPSet();
            VPSet fsrShared = iConfig.exists("fsrShared") ? iConfig.getParameter<VPSet>("fsrShared") : VPSet();
            VPSet anglesShared = iConfig.exists("anglesShared") ? iConfig.getParameter<VPSet>("anglesShared") : VPSet();
            VPSet metShared = iConfig.exists("metShared") ? iConfig.getParameter<VPSet>("metShared") : VPSet();
            VPSet genShared = iConfig.exists("genShared") ? iConfig.getParameter<VPSet>("genShared") : VPSet();
            VPSet counters = iConfig.exists("counters") ? iConfig.getParameter<VPSet>("counters") : VPSet();
            VPSet z1l1 = iConfig.exists("z1l1") ? iConfig.getParameter<VPSet>("z1l1") : VPSet();
            VPSet z1l2 = iConfig.exists("z1l2") ? iConfig.getParameter<VPSet>("z1l2") : VPSet();
            VPSet z2l1 = iConfig.exists("z2l1") ? iConfig.getParameter<VPSet>("z2l1") : VPSet();
            VPSet z2l2 = iConfig.exists("z2l2") ? iConfig.getParameter<VPSet>("z2l2") : VPSet();

            plugins.insert(plugins.end(),zzShared.begin(),zzShared.end());
            plugins.insert(plugins.end(),fsrShared.begin(),fsrShared.end());
            plugins.insert(plugins.end(),anglesShared.begin(),anglesShared.end());
            plugins.insert(plugins.end(),metShared.begin(),metShared.end());
            plugins.insert(plugins.end(),genShared.begin(),genShared.end());
            plugins.insert(plugins.end(),counters.begin(),counters.end());
            plugins.insert(plugins.end(),z1l1.begin(),z1l1.end());
            plugins.insert(plugins.end(),z1l2.begin(),z1l2.end());
            plugins.insert(plugins.end(),z2l1.begin(),z2l1.end());
            plugins.insert(plugins.end(),z2l2.begin(),z2l2.end());

            for (std::vector<edm::ParameterSet>::const_iterator branch = plugins.begin(); branch != plugins.end(); ++branch){
                std::string fillerPlugin = branch->getParameter<std::string>("pluginType");
                if (fillerPlugin.find("QuadFiller") != std::string::npos || fillerPlugin.find("TriFiller") != std::string::npos || fillerPlugin.find("PairFiller") != std::string::npos) {
                    NtupleFillerBaseMultiCand<T>* filler = U::get()->create(fillerPlugin,*branch,t);
                    fillers.push_back(filler);
                } else {
                    NtupleFillerBase* filler = NtupleFillerFactory::get()->create(fillerPlugin,*branch,t);
                    sharedFillers.push_back(filler);
                }
            }

        }

        ~EventTreeMaker()
        {
            for(unsigned int i=0;i<fillers.size();++i)
            {
                if(fillers[i]!=0)
                    delete fillers[i];
            }
            fillers.clear();
        }

    private:

        virtual void analyze( const edm::Event& iEvent, const edm::EventSetup& iSetup)
        {
            EVENT  = iEvent.id().event();
            RUN    = iEvent.id().run();
            LUMI   = iEvent.luminosityBlock();

            for(unsigned int i=0;i<coreColl.size();++i) {
                edm::Handle<edm::View<T> > handle;

                if(iEvent.getByLabel(coreColl.at(i),handle))
                    if(handle->size()>0){
                        if (leadingOnly_) {
                            for(unsigned int j=0;j<fillers.size();++j)
                                fillers.at(j)->fill(handle->at(0),iEvent, iSetup);
                            for(unsigned int j=0;j<sharedFillers.size();++j) //loop over non-templated stuff
                                sharedFillers.at(j)->fill(iEvent, iSetup);
                            t->Fill();
                        } else {
                            for (unsigned int j = 0; j < handle->size(); ++j) {
                                for (unsigned int k = 0; k < fillers.size(); ++k) {
                                    fillers.at(k)->fill(handle->at(j),iEvent,iSetup);
                                }
                                for (unsigned int k = 0; k < sharedFillers.size(); ++k) {
                                    sharedFillers.at(k)->fill(iEvent,iSetup);
                                }
                                t->Fill();
                            }
                        }
                    }
            }
        }
        //
        // ----------member data ---------------------------
        TTree *t;

        //add run event data
        unsigned int EVENT;
        unsigned int RUN;
        unsigned int LUMI;

        bool leadingOnly_;
        std::vector<edm::InputTag> coreColl;
        std::vector<NtupleFillerBaseMultiCand<T>*> fillers;
        std::vector<NtupleFillerBase*> sharedFillers;

};

//4l
typedef EventTreeMaker<PATMuMuMuMuQuad,MMMMFillerFactory> MMMMEventTree;
typedef EventTreeMaker<PATEleEleEleEleQuad,EEEEFillerFactory> EEEEEventTree;
typedef EventTreeMaker<PATMuMuEleEleQuad,MMEEFillerFactory> MMEEEventTree;
typedef EventTreeMaker<PATEleEleMuMuQuad,EEMMFillerFactory> EEMMEventTree;

//2l2t
typedef EventTreeMaker<PATMuMuMuTauQuad,MMMTFillerFactory> MMMTEventTree;
typedef EventTreeMaker<PATMuMuTauTauQuad,MMTTFillerFactory> MMTTEventTree;
typedef EventTreeMaker<PATMuMuEleTauQuad,MMETFillerFactory> MMETEventTree;
typedef EventTreeMaker<PATMuMuEleMuQuad,MMEMFillerFactory> MMEMEventTree;
typedef EventTreeMaker<PATEleEleMuTauQuad,EEMTFillerFactory> EEMTEventTree;
typedef EventTreeMaker<PATEleEleTauTauQuad,EETTFillerFactory> EETTEventTree;
typedef EventTreeMaker<PATEleEleEleTauQuad,EEETFillerFactory> EEETEventTree;
typedef EventTreeMaker<PATEleEleEleMuQuad,EEEMFillerFactory> EEEMEventTree;

//Z+l
typedef EventTreeMaker<PATEleEleEleTri,EEEFillerFactory> EEEEventTree;
typedef EventTreeMaker<PATEleEleMuTri,EEMFillerFactory> EEMEventTree;
typedef EventTreeMaker<PATMuMuEleTri,MMEFillerFactory> MMEEventTree;
typedef EventTreeMaker<PATMuMuMuTri,MMMFillerFactory> MMMEventTree;

//Z
typedef EventTreeMaker<PATElecPair,EEFillerFactory> EEEventTree;
typedef EventTreeMaker<PATMuPair,MMFillerFactory> MMEventTree;
