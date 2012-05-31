// system include files
#include <memory>

// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>

#include "DataFormats/PatCandidates/interface/Tau.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//

class TauCountFiller : public NtupleFillerBase {
 public:
    TauCountFiller(){
    }


    TauCountFiller(const edm::ParameterSet& iConfig, TTree* t):
      src_(iConfig.getParameter<edm::InputTag>("src")),
      tag_(iConfig.getParameter<std::string>("tag")),
      var_(iConfig.getParameter<std::string>("method"))
	{
	  value = 0;
	  t->Branch(tag_.c_str(),&value,(tag_+"/I").c_str());
	  function = new StringCutObjectSelector<pat::Tau>(var_,true);
	}


  ~TauCountFiller()
    { 
      if(function!=0) delete function;
    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<edm::View<pat::Tau> > handle;
    value=0;
    if(iEvent.getByLabel(src_,handle)) {
	  //loop over handle, sum those passing the requirements
		for (unsigned int i = 0; i < handle->size(); i++) {
			if ((*function)(handle->at(i))) value++; 
		}
    }
  }
  

 protected:
  edm::InputTag src_;
  std::string tag_;
  std::string var_;
  int value;
  StringCutObjectSelector<pat::Tau>*function;

};






