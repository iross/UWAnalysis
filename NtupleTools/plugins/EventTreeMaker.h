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


#include <TTree.h>

//
// class decleration
//
class EventTreeMaker : public edm::EDAnalyzer {
	public:
		explicit EventTreeMaker(const edm::ParameterSet& iConfig)
		{

			typedef std::vector<edm::ParameterSet> VPSet;

			edm::Service<TFileService> fs;
			t = fs->make<TTree>( "eventTree"  , "");

			//Add event and RUN BRANCHING	 
			t->Branch("EVENT",&EVENT,"EVENT/i");
			t->Branch("RUN",&RUN,"RUN/i");
			t->Branch("LUMI",&LUMI,"LUMI/i");
			coreColl = iConfig.getParameter<std::vector<edm::InputTag> >("coreCollections");

			std::vector<std::string> branchNames = iConfig.getParameterNamesForType<edm::ParameterSet>();
			for ( std::vector<std::string>::const_iterator branchName = branchNames.begin(); 
					branchName != branchNames.end(); ++branchName ) {
				std::cout << " reading configuration parameters for Branch = " << (*branchName) << std::endl;

				edm::ParameterSet ntupleFillerCfg = iConfig.getParameter<edm::ParameterSet>(*branchName);
				std::string fillerPlugin = ntupleFillerCfg.getParameter<std::string>("pluginType");
				NtupleFillerBase* filler = NtupleFillerFactory::get()->create(fillerPlugin,ntupleFillerCfg,t);
				fillers.push_back(filler);

			}

			//if Ian's VPsets exist, add them to the fillers. 
			VPSet plugins;
			VPSet zzShared = iConfig.exists("zzShared") ? iConfig.getParameter<VPSet>("zzShared") : VPSet();
			VPSet genShared = iConfig.exists("genShared") ? iConfig.getParameter<VPSet>("genShared") : VPSet();
			VPSet counters = iConfig.exists("counters") ? iConfig.getParameter<VPSet>("counters") : VPSet();
			VPSet z1l1 = iConfig.exists("z1l1") ? iConfig.getParameter<VPSet>("z1l1") : VPSet();
			VPSet z1l2 = iConfig.exists("z1l2") ? iConfig.getParameter<VPSet>("z1l2") : VPSet();
			VPSet z2l1 = iConfig.exists("z2l1") ? iConfig.getParameter<VPSet>("z2l1") : VPSet();
			VPSet z2l2 = iConfig.exists("z2l2") ? iConfig.getParameter<VPSet>("z2l2") : VPSet();
			
			plugins.insert(plugins.end(),zzShared.begin(),zzShared.end());
			plugins.insert(plugins.end(),genShared.begin(),genShared.end());
			plugins.insert(plugins.end(),counters.begin(),counters.end());
			plugins.insert(plugins.end(),z1l1.begin(),z1l1.end());
			plugins.insert(plugins.end(),z1l2.begin(),z1l2.end());
			plugins.insert(plugins.end(),z2l1.begin(),z2l1.end());
			plugins.insert(plugins.end(),z2l2.begin(),z2l2.end());
			for (std::vector<edm::ParameterSet>::const_iterator branch = plugins.begin(); branch != plugins.end(); ++branch){
				std::string fillerPlugin = branch->getParameter<std::string>("pluginType");
				NtupleFillerBase* filler = NtupleFillerFactory::get()->create(fillerPlugin,*branch,t);
				fillers.push_back(filler);
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


			bool doFill=false;
			for(unsigned int i=0;i<coreColl.size();++i) {
				edm::Handle<edm::View<reco::Candidate> > handle;
				if(iEvent.getByLabel(coreColl.at(i),handle))
					if(handle->size()>0)
						doFill=true;
			}

			if(doFill) {
				for(unsigned int i=0;i<fillers.size();++i)
					fillers.at(i)->fill(iEvent, iSetup);

				t->Fill();
			}
		}

		// ----------member data ---------------------------

		TTree *t;

		//add run event data
		unsigned int EVENT;
		unsigned int RUN;
		unsigned int LUMI;

		std::vector<edm::InputTag> coreColl;
		std::vector<NtupleFillerBase*> fillers;

};	 



