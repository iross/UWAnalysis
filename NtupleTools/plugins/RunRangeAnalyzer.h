

// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/LuminosityBlock.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "DataFormats/PatCandidates/interface/TriggerPath.h"
#include <TH1F.h>

#include "DataFormats/Luminosity/interface/LumiDetails.h"
#include "DataFormats/Luminosity/interface/LumiSummary.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"


//
// class decleration
//


class RunRangeAnalyzer : public edm::EDAnalyzer {
   public:
  explicit RunRangeAnalyzer(const edm::ParameterSet& iConfig):
    patTrigger_(iConfig.getParameter<edm::InputTag>("patTrigger")),
    triggerRanges_(iConfig.getParameter<std::vector<std::string> >("triggerRanges"))
      {
	edm::Service<TFileService> fs;
	histogram = fs->make<TH1F>("runRangeSummary","Run Range Lumi",triggerRanges_.size(),0,triggerRanges_.size());
	range=-1;
      }

    ~RunRangeAnalyzer() {}


   private:

    virtual void analyze(const edm::Event& iEvent, const edm::EventSetup&) {
      range=-1;
      edm::Handle<pat::TriggerPathCollection> paths;
      if(iEvent.getByLabel(patTrigger_, paths))
	for(unsigned int i=0;i<triggerRanges_.size();++i) 
	  for(unsigned int j=0;j<paths->size();++j) 
	    if(paths->at(j).name()==triggerRanges_.at(i)) {
	      if(paths->at(j).wasRun()&&paths->at(j).prescale()==1) {
		  range=i;
		  break;
	      }
	      break;
	    }
    }

    virtual void endLuminosityBlock(edm::LuminosityBlock const& lumiBlock, edm::EventSetup const& c) {
      edm::Handle<LumiSummary> lumiSummary;
      lumiBlock.getByLabel("lumiProducer", lumiSummary);
      histogram->Fill(range,lumiSummary->avgInsRecLumi());
    }


    virtual void endJob() {


    }

    edm::InputTag patTrigger_;
    std::vector<std::string> triggerRanges_;
    TH1F *histogram;
    int range;
};
      
