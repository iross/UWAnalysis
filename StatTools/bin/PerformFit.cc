#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include <RooStats/ProfileLikelihoodCalculator.h>
#include <RooStats/LikelihoodInterval.h>
#include <RooStats/LikelihoodIntervalPlot.h>
#include <RooStats/HLFactory.h>
#include <RooStats/HypoTestResult.h>
#include <Math/MinimizerOptions.h>

#include "UWAnalysis/StatTools/interface/fitter.h"

#include "HiggsAnalysis/CombinedLimit/interface/VerticalInterpPdf.h"


int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);

   optutl::CommandLineParser parser ("Performs Fit ");

   //Data
   parser.addOption("modelFile",optutl::CommandLineParser::kString,"Model File","models/mutau.hlf");
   parser.addOption("model",optutl::CommandLineParser::kString,"Model","Yield");
   parser.addOption("channel",optutl::CommandLineParser::kString,"Channel","MuTau");
   parser.addOption("snapShot",optutl::CommandLineParser::kString,"SnapShot","");
   parser.addOption("verbose",optutl::CommandLineParser::kInteger,"verbose",0);
   parser.addOption("data",optutl::CommandLineParser::kString,"data","");
   //Parse Arguments!
   parser.parseArguments (argc, argv);

   std::string modelFile = parser.stringValue("modelFile");
   std::string model     = parser.stringValue("model");
   std::string channel   = parser.stringValue("channel");
   std::string output    = parser.stringValue("outputFile");
   std::string snapShot  = parser.stringValue("snapShot");
   std::string dataset      = parser.stringValue("data");

   
   //Load the factory
   std::auto_ptr<RooStats::HLFactory> hlf(0);
    try {
      hlf.reset(new RooStats::HLFactory("factory", modelFile.c_str()));
    } catch(...) {
        std::cerr << "Exception when readin the HLF " << modelFile << std::endl;
        return 3;
    }
    RooWorkspace *w = hlf->GetWs();
    printf("Read HLF file\n");

    //get the data 
    RooAbsData * data=0;
    if(dataset.size()==0)
      data  = w->data(("DATA_"+channel).c_str());
    else
      data  = w->data(dataset.c_str());
    
    //initialize the fitter
    fitter * myFitter = new fitter(w,channel,model);

    //perform a fit
    myFitter->fit(data);


    //save a snapshot of the fit results
    //and a global outputFile
    if(snapShot.size()>0) {
      myFitter->saveSnapshot(snapShot.c_str());
      myFitter->createOutput(output.c_str());
    }

    if(parser.integerValue("verbose")==1)
      w->allVars().Print("V");


    //delete fitter
    delete myFitter;
      

}

