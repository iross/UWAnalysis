// system include files
#include <memory>

// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/PatCandidates/interface/TriggerPath.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"

//
// class decleration
//

class TriggerFiller : public NtupleFillerBase {
 public:

    TriggerFiller(){
    }

    TriggerFiller(const edm::ParameterSet& iConfig, TTree* t):
      src_(iConfig.getParameter<edm::InputTag>("src")),
      paths_(iConfig.getParameter<std::vector<std::string> >("paths"))
	{
	  fired    = std::vector<int>(paths_.size());
	  wasRun   = std::vector<int>(paths_.size());
	  prescale = std::vector<int>(paths_.size());
	  error    = std::vector<int>(paths_.size());

	  any=0;

	  for(unsigned int i=0;i<paths_.size();++i) {
	    fired[i]=0;
	    wasRun[i]=0;
	    prescale[i]=0;
	    error[i]=0;

	    t->Branch((paths_[i]+"_wasRun").c_str(),&wasRun[i],(paths_[i]+"_wasRun/I").c_str());
	    t->Branch((paths_[i]+"_fired").c_str(),&fired[i],(paths_[i]+"_fired/I").c_str());
	    t->Branch((paths_[i]+"_prescale").c_str(),&prescale[i],(paths_[i]+"_prescale/I").c_str());
	    t->Branch((paths_[i]+"_error").c_str(),&error[i],(paths_[i]+"_error/I").c_str());

	  }
      t->Branch("HLT_Any",&any,"HLT_Any/I");

	}

      
      
      ~TriggerFiller()
	{ 
	  
	}
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {

    using namespace std; 
    any=0;

    edm::Handle<pat::TriggerPathCollection> paths;
    if(iEvent.getByLabel(src_, paths)) {

    

      //get the names of the triggers
      for(unsigned int i=0;i<paths_.size();++i) {
	bool found=false;
		bool fired_t=false;
	for(unsigned int j=0;j<paths->size() && fired_t==false;++j) {
          size_t trigPath = paths->at(j).name().find(paths_.at(i));
          if ( trigPath == 0) {
	    found=true;
	    fired[i]=paths->at(j).wasAccept(); 
	    wasRun[i]=paths->at(j).wasRun();
	    prescale[i]=paths->at(j).prescale();
	    error[i]=paths->at(j).wasError();
	    if(paths->at(j).wasRun()&&paths->at(j).wasAccept()&&paths->at(j).prescale()==1){
	      any=1; fired_t=true;
		}
	    break;
	  }
	}
	if(!found) {
	  fired[i]=0;
	  wasRun[i]=0;
	  prescale[i]=0;
	  error[i]=0;

	}
      }

    }
  }
  

 protected:
  edm::InputTag src_;
  std::vector<std::string> paths_;

  std::vector<int> fired;
  std::vector<int> wasRun;
  std::vector<int> prescale;
  std::vector<int> error;
  int any;

};






