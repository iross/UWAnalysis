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
      tag_(iConfig.getParameter<std::string>("tag"))
	{
	  psMass=0;
	  psMETMass=0;
	  psMETPtMass=0;
	  x1=0.0;
	  x2=0.0;
	  t->Branch((tag_+"KineMass").c_str(),&psMass,(tag_+"KineMass/F").c_str());
	  t->Branch((tag_+"KineMETMass").c_str(),&psMETMass,(tag_+"KineMETMass/F").c_str());
	  t->Branch((tag_+"KineMETPtMass").c_str(),&psMETPtMass,(tag_+"KineMETPtMass/F").c_str());
	  t->Branch((tag_+"x1").c_str(),&x1,(tag_+"x1/F").c_str());
	  t->Branch((tag_+"x2").c_str(),&x2,(tag_+"x2/F").c_str());

          // NSVfit plots
          nsvPsMETLogM_fit = -1;
          nsvPsMETLogM_fit_valid = -1;
          nsvPsMETLogM_fit_errUp = -1;
          nsvPsMETLogM_fit_errDown = -1;
	  t->Branch((tag_+"NSVPsMEtLogM_fit").c_str(),&nsvPsMETLogM_fit,(tag_+"NSVPsMEtLogM_fit").c_str());
	  t->Branch((tag_+"NSVPsMEtLogM_fit_valid").c_str(),&nsvPsMETLogM_fit_valid,(tag_+"NSVPsMEtLogM_fit_valid").c_str());
	  t->Branch((tag_+"NSVPsMEtLogM_fit_errUp").c_str(),&nsvPsMETLogM_fit_errUp,(tag_+"NSVPsMEtLogM_fit_errUp").c_str());
	  t->Branch((tag_+"NSVPsMEtLogM_fit_errDown").c_str(),&nsvPsMETLogM_fit_errDown,(tag_+"NSVPsMEtLogM_fit_errDown").c_str());

          nsvPsMETLogM_int = -1;
          nsvPsMETLogM_int_valid = -1;
          nsvPsMETLogM_int_errUp = -1;
          nsvPsMETLogM_int_errDown = -1;
	  t->Branch((tag_+"NSVPsMEtLogM_int").c_str(),&nsvPsMETLogM_int,(tag_+"NSVPsMEtLogM_int").c_str());
	  t->Branch((tag_+"NSVPsMEtLogM_int_valid").c_str(),&nsvPsMETLogM_int_valid,(tag_+"NSVPsMEtLogM_int_valid").c_str());
	  t->Branch((tag_+"NSVPsMEtLogM_int_errUp").c_str(),&nsvPsMETLogM_int_errUp,(tag_+"NSVPsMEtLogM_int_errUp").c_str());
	  t->Branch((tag_+"NSVPsMEtLogM_int_errDown").c_str(),&nsvPsMETLogM_int_errDown,(tag_+"NSVPsMEtLogM_int_errDown").c_str());
	}


  ~SVFitFiller()
    {
    }


  void fill(const edm::Event& iEvent, const edm::EventSetup& iSetup)
  {
    edm::Handle<std::vector<T> > handle;



    if(iEvent.getByLabel(src_,handle)) {
	  psMass=0;
	  psMETMass=0;
	  psMETPtMass=0;

	  if(handle->size()>0 &&handle->at(0).hasSVFitSolutions()) {
	    psMass = handle->at(0).svFitSolution("psKine")->mass();
	    psMETMass = handle->at(0).svFitSolution("psKine_MEt")->mass();
	    psMETPtMass = handle->at(0).svFitSolution("psKine_MEt_ptBalance")->mass();
	    x1 = handle->at(0).svFitSolution("psKine_MEt_ptBalance")->leg1().x();
	    x2 = handle->at(0).svFitSolution("psKine_MEt_ptBalance")->leg2().x();
          }
          if (handle->size()>0 &&handle->at(0).hasNSVFitSolutions()) {
            const NSVfitResonanceHypothesisSummary* fitSoln = handle->at(0).nSVfitSolution("PsMETLogM_fit");
            if (fitSoln) {
              nsvPsMETLogM_fit = fitSoln->mass();
              nsvPsMETLogM_fit_valid = fitSoln->isValidSolution();
              nsvPsMETLogM_fit_errUp = fitSoln->massErrUp();
              nsvPsMETLogM_fit_errDown = fitSoln->massErrDown();
            }
            const NSVfitResonanceHypothesisSummary* intSoln = handle->at(0).nSVfitSolution("PsMETLogM_int");
            if (intSoln) {
              nsvPsMETLogM_int = intSoln->mass();
              nsvPsMETLogM_int_valid = intSoln->isValidSolution();
              nsvPsMETLogM_int_errUp = intSoln->massErrUp();
              nsvPsMETLogM_int_errDown = intSoln->massErrDown();
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
  float psMass;

  float psMETMass;


  float psMETPtMass;
  float x1,x2;

  float nsvPsMETLogM_fit;
  float nsvPsMETLogM_fit_valid;
  float nsvPsMETLogM_fit_errUp;
  float nsvPsMETLogM_fit_errDown;

  float nsvPsMETLogM_int;
  float nsvPsMETLogM_int_valid;
  float nsvPsMETLogM_int_errUp;
  float nsvPsMETLogM_int_errDown;

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
typedef SVFitFiller<PATEleEleEleTauQuad> PATEEETSVFitFiller;
typedef SVFitFiller<PATEleEleMuTauQuad> PATEEMTSVFitFiller;
typedef SVFitFiller<PATEleEleTauTauQuad> PATEETTSVFitFiller;
typedef SVFitFiller<PATEleEleEleMuQuad> PATEEEMSVFitFiller;
typedef SVFitFiller<PATMuMuEleTauQuad> PATMMETSVFitFiller;
typedef SVFitFiller<PATMuMuMuTauQuad> PATMMMTSVFitFiller;
typedef SVFitFiller<PATMuMuTauTauQuad> PATMMTTSVFitFiller;
typedef SVFitFiller<PATMuMuEleMuQuad> PATMMEMSVFitFiller;




