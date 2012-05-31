// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//
template<typename T>
class PATIsolationFiller : public NtupleFillerBase {
 public:
    PATIsolationFiller(){
    }


    PATIsolationFiller(const edm::ParameterSet& iConfig, TTree* t):
      NtupleFillerBase(iConfig,t),
      src_(iConfig.getParameter<edm::InputTag>("src")),
      cone_(iConfig.getParameter<double>("cone")),
      type_(iConfig.getParameter<std::string>("type")),
      leg_(iConfig.getParameter<int>("leg")),
      veto_(iConfig.getParameter<double>("innerVeto")),
      multiplicity_(iConfig.getParameter<bool>("multiplicity")),
      tag_(iConfig.getParameter<std::string>("tag")),
      leadingOnly_(iConfig.getUntrackedParameter<bool>("leadingOnly",true))
	{
	  singleValue=0.;

	  value = new std::vector<double>();

	  if(!leadingOnly_)
	    vbranch = t->Branch(tag_.c_str(),"std::vector<double>",&value);
	  else
	    vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());
	}


  ~PATIsolationFiller()
    { 
    }


  
       

  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;
    singleValue=-1;
    if(value->size()>0)
            value->clear();
    
    if(iEvent.getByLabel(src_,handle)) {

      if(leadingOnly_)
	{
	  if(handle->size()>0)
	    singleValue = (*function)(handle->at(0));
	}
      else
	for(unsigned int i=0;i<handle->size();++i) {
	  value->push_back((*function)(handle->at(i)));
	}    


    }
    else
      {
	printf("Obj not found \n");
      }
    //    vbranch->Fill();
  }
  

 protected:

  std::pair<double,int> getIsoDeposit(const T& obj,int leg,std::string type) {
    edm::Ptr<T> ptr = 
  }






  edm::InputTag src_;
  std::string var_;
  std::string tag_;
  bool multiplicity_;
  bool leadingOnly_;
  double cone_;
  std::string type_;
  double veto_;
  int leg_;

  float singlevalue;
  TBranch *vbranch;

  std::vector<double>* value;

};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef PATIsolationFiller<PATMuPair> PATMuPairIsolationFiller;
typedef PATIsolationFiller<pat::Muon> PATMuonFiller;




