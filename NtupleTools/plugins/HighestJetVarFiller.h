// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include "DataFormats/PatCandidates/interface/Jet.h"

#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"

//
// class decleration
//
template<typename T>
class HighestJetVarFiller : public NtupleFillerBase {
 public:
    HighestJetVarFiller(){
    }


    HighestJetVarFiller(const edm::ParameterSet& iConfig, TTree* t):
      NtupleFillerBase(iConfig,t),
      src_(iConfig.getParameter<edm::InputTag>("src")),
      var_(iConfig.getParameter<std::string>("method")),
      tag_(iConfig.getParameter<std::string>("tag")),
      leadingOnly_(iConfig.getUntrackedParameter<bool>("leadingOnly",true))
	{
	  value = new std::vector<double>();
	  singleValue=0.;
	  function = new StringObjectFunction<pat::Jet>(var_);
	  if(!leadingOnly_)
	    vbranch = t->Branch(tag_.c_str(),"std::vector<double>",&value);
	  else
	    vbranch = t->Branch(tag_.c_str(),&singleValue,(tag_+"/F").c_str());

	}


  ~HighestJetVarFiller()
    { 
      if(function!=0) delete function;
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
	    for(unsigned int i=0;i<handle->at(0).jets().size();++i)
	      if((*function)(*(handle->at(0).jets().at(i)))>singleValue)
		singleValue = (*function)(*(handle->at(0).jets().at(i)));
	}
      else {
	  if(handle->size()>0)
	    for(unsigned int j=0;j<handle->size();++j) {
	      singleValue=-1.;
	      for(unsigned int i=0;i<handle->at(j).jets().size();++i)
		if((*function)(*(handle->at(j).jets().at(i)))>singleValue)
		  singleValue = (*function)(*(handle->at(j).jets().at(i)));
	      value->push_back(singleValue);
	    }    
      }


    }
    else
      {
	printf("Obj not found \n");
      }
    //    vbranch->Fill();
  }
  

 protected:
  edm::InputTag src_;
  std::string var_;
  std::string tag_;
  bool leadingOnly_;
  std::vector<double>* value;
  float singleValue;
  StringObjectFunction<pat::Jet>*function;
  TBranch *vbranch;

};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef HighestJetVarFiller<PATMuTauPair> PATMuTauPairHighestJetVarFiller;
typedef HighestJetVarFiller<PATMuTauPair> PATMuJetPairHighestJetVarFiller;





