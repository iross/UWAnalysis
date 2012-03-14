// system include files
#include <memory>

// user include files

#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "SimDataFormats/PileupSummaryInfo/interface/PileupSummaryInfo.h" 

//
// class decleration
//

class PUFiller : public NtupleFillerBase {
 public:
    PUFiller(){
    }


    PUFiller(const edm::ParameterSet& iConfig, TTree* t):
      src_(iConfig.getParameter<edm::InputTag>("src")),
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  value = 0;
	  t->Branch(tag_.c_str(),&value,(tag_+"/F").c_str());
	}


  ~PUFiller()
    { 

    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;
    value=0;
    int crossings=0;

    if(iEvent.getByLabel(src_, PupInfo)) {
      for(std::vector<PileupSummaryInfo>::const_iterator i = PupInfo->begin();
	  i!=PupInfo->end();++i) {
	value +=  i->getPU_NumInteractions(); 
	crossings++;
      }
    }
    else
      {
	printf("PU Info not found\n");
      }

    value=value/crossings;

  }
  

 protected:
  edm::InputTag src_;
  std::string tag_;
  float value;


};






