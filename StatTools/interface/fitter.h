#include <TList.h>
#include <TString.h>

#include <RooAbsData.h>
#include <Math/MinimizerOptions.h>
#include <RooAbsReal.h>
#include <RooAbsPdf.h>
#include <RooAddPdf.h>
#include <RooArgSet.h>
#include <RooCurve.h>
#include <RooDataHist.h>
#include <RooDataSet.h>
#include <RooExtendPdf.h>
#include <RooFitResult.h>
#include <RooHist.h>
#include <RooHistPdf.h>
#include <RooMinuit.h>
#include <RooPlot.h>
#include <RooProdPdf.h>
#include <RooRealVar.h>
#include <RooSimultaneous.h>
#include <RooWorkspace.h>
#include <RooStats/RooStatsUtils.h>



class fitter {
 public:
  fitter() {}
  ~fitter() {}
  fitter(RooWorkspace *w,std::string channel,std::string model):
    w_(w),
    model_(model)
    {
      if(channel!="")
	modelPdf_ = w->pdf(("model_"+channel+"_"+model).c_str());
      else
	modelPdf_ = w->pdf(("model_"+model).c_str());

      if(model!="s" && model!="b") {
	nuisances_ = w->set(("model_"+channel+"_"+model+"_nuisances").c_str());
	nuisancePdf_ = w->pdf(("model_"+channel+"_"+model+"_nuisancePdf").c_str());
      }
      else
	{
	  if(channel!="") {
	    nuisances_ = w->set(("model_"+channel+"_nuisances").c_str());
	    nuisancePdf_ = w->pdf(("model_"+channel+"_nuisancePdf").c_str());
	  }
	  else
	    {
	      nuisances_ = w->set("nuisances");
	      nuisancePdf_ = w->pdf("nuisancePdf");

	    }
	}


    //get the constraints
    const RooArgSet* constraints = w->set(("model_"+channel+"_"+model+"_constraints").c_str());
    freezeSet(constraints);
    
    //error control
    if (modelPdf_ == 0) {
      std::cerr << "ERROR: missing pdf " << "model_"+channel+"_"+model << std::endl;
    }
    if (nuisances_ == 0) {
        std::cerr << "ERROR: missing nuisance set " <<"model_"+channel+"_"+model+"_nuisances-using none"<< std::endl;
    }

  }

  void fit(RooAbsData* data)
  {
    using namespace RooFit;

    std::cout << "Will fit using minimizer " << ROOT::Math::MinimizerOptions::DefaultMinimizerType() << ", algo " << ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo() << std::endl;
    const RooCmdArg & myMinimizer = Minimizer(ROOT::Math::MinimizerOptions::DefaultMinimizerType().c_str(), ROOT::Math::MinimizerOptions::DefaultMinimizerAlgo().c_str());
    
    //perform the fit
    RooFitResult *result =0;
    
    if(nuisances_!=0)
      result = modelPdf_->fitTo(*data, Save(1), Minos(true), Constrain(*nuisances_), myMinimizer,SumW2Error(kFALSE));
    else
      result = modelPdf_->fitTo(*data, Save(1), Minos(true),myMinimizer,SumW2Error(kFALSE));

    result->floatParsFinal().Print("V");

    delete result;
  }



  void saveSnapshot(const char* name) {
    w_->saveSnapshot(name,w_->allVars());
  }

  void createOutput(const char* name) {
    w_->SetName("w");
    w_->writeToFile(name);

  }

  void freezeSet(const RooArgSet* set) {
    //set the constraints to constants
    if (set != 0) {
      TIterator *iter = set->createIterator();
      for (RooAbsArg *a = 0; (a = (RooAbsArg *)iter->Next()) != 0; ) {
            if (a->InheritsFrom("RooRealVar")) ((RooRealVar &)*a).setConstant(true);
      }
      delete iter; 
    }
  }

  void releaseSet(const RooArgSet* set) {
    //set the constraints to constants
    if (set != 0) {
      TIterator *iter = set->createIterator();
      for (RooAbsArg *a = 0; (a = (RooAbsArg *)iter->Next()) != 0; ) {
            if (a->InheritsFrom("RooRealVar")) ((RooRealVar &)*a).setConstant(false);
      }
      delete iter; 
    }
  }







 private:
  RooWorkspace *w_;
  std::string model_;
  const RooArgSet *nuisances_;
  RooAbsPdf *modelPdf_;
  RooAbsPdf *nuisancePdf_;
 
};
