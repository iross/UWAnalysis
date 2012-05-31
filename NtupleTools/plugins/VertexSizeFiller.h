
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

class VertexSizeFiller : public NtupleFillerBase {
 public:
    VertexSizeFiller(){
    }


    VertexSizeFiller(const edm::ParameterSet& iConfig, TTree* t):
      src_(iConfig.getParameter<edm::InputTag>("src")),
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  value = 0;
	  t->Branch(tag_.c_str(),&value,(tag_+"/I").c_str());
	}


  ~VertexSizeFiller()
    { 

    }
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<reco::VertexCollection > handle;
    value=0;
    if(iEvent.getByLabel(src_,handle)) {
      value = handle->size();
    }
  }
  

 protected:
  edm::InputTag src_;
  std::string tag_;
  int value;


};






