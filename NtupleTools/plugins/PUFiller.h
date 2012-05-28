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
	  value = new float[6];
	  t->Branch((tag_+"BXminus").c_str(),&value[0],(tag_+"BXminus/F").c_str());
	  t->Branch((tag_+"Truth").c_str(),&value[1],(tag_+"Truth/F").c_str());
	  t->Branch((tag_+"BX0").c_str(),&value[2],(tag_+"BX0/F").c_str());
	  t->Branch((tag_+"BXplus").c_str(),&value[4],(tag_+"BXplus/F").c_str());
	}


  ~PUFiller()
    { 

    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<PileupSummaryInfo> > PupInfo;

    if(iEvent.getByLabel(src_, PupInfo)) {
      for(std::vector<PileupSummaryInfo>::const_iterator i = PupInfo->begin();
	  i!=PupInfo->end();++i) {
	int BX = i->getBunchCrossing();
	if(BX==-1) {
	  value[0] =  i->getPU_NumInteractions(); 
	}
	if(BX==0) {
	  value[2] =  i->getPU_NumInteractions(); 
	  value[1] =i->getTrueNumInteractions(); 
	}
	if(BX==1) {
	  value[4] =  i->getPU_NumInteractions(); 
	}
      }
    }
    else
      {
	printf("PU Info not found\n");
      }



  }
  

 protected:
  edm::InputTag src_;
  std::string tag_;
  float* value;

};






