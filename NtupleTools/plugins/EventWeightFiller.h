// system include files
#include <memory>

// user include files
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//

class EventWeightFiller : public NtupleFillerBase {
 public:
    EventWeightFiller(){
    }


    EventWeightFiller(const edm::ParameterSet& iConfig, TTree* t):
      src_(iConfig.getParameter<edm::InputTag>("src")),
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  value = 0;
	  t->Branch(tag_.c_str(),&value,(tag_+"/F").c_str());
	}


  ~EventWeightFiller()
    { 

    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<double> handle;
    value=0;
    if(iEvent.getByLabel(src_,handle)) {
      value = *handle;
    }
  }
  

 protected:
  edm::InputTag src_;
  std::string tag_;
  float value;


};






