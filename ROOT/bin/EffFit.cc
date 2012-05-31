#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/LikelihoodIntervalPlot.h"


int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------

   //Data

   parser.addOption("all",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.03);
   parser.addOption("allErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.01);
   parser.addOption("pass",optutl::CommandLineParser::kDouble,"WMN factor",0.287);
   parser.addOption("passErr",optutl::CommandLineParser::kDouble,"WMN factor",0.010);

   parser.parseArguments (argc, argv);

   float all = parser.doubleValue("all");
   float allErr = parser.doubleValue("allErr");
   float pass = parser.doubleValue("pass");
   float passErr = parser.doubleValue("passErr");

   RooWorkspace *w = new RooWorkspace("w","ww");
//    w->factory(TString::Format("N0[%f,50,300]",all));
//    w->factory(TString::Format("P0[%f,50,300]",pass));

    w->factory(TString::Format("N0[%f]",all));
    w->factory(TString::Format("P0[%f]",pass));


   w->factory(TString::Format("N[%f,%f,%f]",all,all-3*allErr,all+3*allErr));
   w->factory("e[0.3,0.8]");

   w->factory("expr::P('e*N',e,N)");

   w->factory(TString::Format("Gaussian::p1(N0,N,%f)",allErr));
   w->factory(TString::Format("Gaussian::p2(P0,P,%f)",passErr));

   w->factory("PROD::model(p1,p2)");

    RooArgSet observables;
    observables.add(*w->var("N0"));
    observables.add(*w->var("P0"));


    RooDataSet dataset("dataset","dataset",observables);
    dataset.add(observables);

   RooAbsPdf* pdf = w->pdf("model");

   pdf->fitTo(dataset,SumW2Error(kTRUE));

   



}


