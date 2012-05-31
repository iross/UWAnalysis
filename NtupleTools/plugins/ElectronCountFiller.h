// system include files
#include <memory>

// user include files
#include "DataFormats/Candidate/interface/Candidate.h"
#include <TTree.h>
#include "DataFormats/PatCandidates/interface/Electron.h"
#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "CommonTools/UtilAlgos/interface/StringCutObjectSelector.h"
//
// class decleration
//

class ElectronCountFiller : public NtupleFillerBase {
 public:
    ElectronCountFiller(){
    }


    ElectronCountFiller(const edm::ParameterSet& iConfig, TTree* t):
      src_(iConfig.getParameter<edm::InputTag>("src")),
      tag_(iConfig.getParameter<std::string>("tag")),
      var_(iConfig.getParameter<std::string>("method"))

	{
	  value = 0;
	  t->Branch(tag_.c_str(),&value,(tag_+"/I").c_str());
	  function = new StringCutObjectSelector<pat::Electron>(var_,true);
	}


  ~ElectronCountFiller()
    { 
      if(function!=0) delete function;
    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<edm::View<pat::Electron> > handle;
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
  StringCutObjectSelector<pat::Electron>*function;

};






