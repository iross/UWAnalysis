// system include files
#include <memory>

// user include files
#include "CommonTools/Utils/interface/StringObjectFunction.h"
#include "DataFormats/PatCandidates/interface/LookupTableRecord.h"
#include <TTree.h>

#include "UWAnalysis/NtupleTools/interface/NtupleFillerBase.h"
#include "AnalysisDataFormats/TauAnalysis/interface/NSVfitResonanceHypothesisSummary.h"

//
// class decleration
//
template<typename T>
class SVFitFiller : public NtupleFillerBase {
 public:
    SVFitFiller(){
    }


    SVFitFiller(const edm::ParameterSet& iConfig, TTree* t):
      NtupleFillerBase(iConfig,t),
      src_(iConfig.getParameter<edm::InputTag>("src")),
      solution_(iConfig.getUntrackedParameter<std::string>("solution","PsMETLogM_fit")),
      tag_(iConfig.getParameter<std::string>("tag"))
	{


          // NSVfit plots
          nsvPsMETLogM_fit = -1;
          nsvPsMETLogM_fit_valid = -1;
          nsvPsMETLogM_fit_errUp = -1;
          nsvPsMETLogM_fit_errDown = -1;
	  t->Branch((tag_+"Mass").c_str(),&nsvPsMETLogM_fit,(tag_+"Mass").c_str());
	  t->Branch((tag_+"Valid").c_str(),&nsvPsMETLogM_fit_valid,(tag_+"Valid").c_str());
	  t->Branch((tag_+"ErrUp").c_str(),&nsvPsMETLogM_fit_errUp,(tag_+"ErrUp").c_str());
	  t->Branch((tag_+"ErrDown").c_str(),&nsvPsMETLogM_fit_errDown,(tag_+"ErrDown").c_str());
	}


  ~SVFitFiller()
    {
    }


  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;



    if(iEvent.getByLabel(src_,handle)) {


          if (handle->size()>0 &&handle->at(0).hasNSVFitSolutions()) {
            const NSVfitResonanceHypothesisSummary* fitSoln = handle->at(0).nSVfitSolution(solution_);
            if (fitSoln) {
              nsvPsMETLogM_fit = fitSoln->mass();
              nsvPsMETLogM_fit_valid = fitSoln->isValidSolution();
              nsvPsMETLogM_fit_errUp = fitSoln->massErrUp();
              nsvPsMETLogM_fit_errDown = fitSoln->massErrDown();
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
  std::string tag_;
  std::string solution_;

  float nsvPsMETLogM_fit;
  float nsvPsMETLogM_fit_valid;
  float nsvPsMETLogM_fit_errUp;
  float nsvPsMETLogM_fit_errDown;


};


#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateT1T2MEt.h"
#include "UWAnalysis/DataFormats/interface/CompositePtrCandidateTMEt.h"
typedef SVFitFiller<PATMuTauPair> PATMuTauSVFitFiller;
typedef SVFitFiller<PATElecTauPair> PATEleTauSVFitFiller;
typedef SVFitFiller<PATElecMuPair> PATEleMuSVFitFiller;
typedef SVFitFiller<PATElecPair> PATEleSVFitFiller;
typedef SVFitFiller<PATMuTrackPair> PATMuTrackSVFitFiller;
typedef SVFitFiller<PATEleTrackPair> PATEleTrackSVFitFiller;
typedef SVFitFiller<PATMuPair> PATMuSVFitFiller;





