#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 

#include "RooRealVar.h"
#include "RooVoigtian.h"
#include "RooPolynomial.h"
#include "RooKeysPdf.h"
#include "RooNDKeysPdf.h"
#include "RooChebychev.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGlobalFunc.h" 
#include "RooChi2Var.h"
#include "RooRealVar.h"
#include "RooLandau.h"
#include "RooGaussian.h"
#include "RooNumConvPdf.h"
#include "RooMinuit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TH1.h"
#include "TF1.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"


void createWorspace(RooWorkspace *w,const std::string& signalFile,const std::string& treeDir, const std::string& prefix, int constrainBackground,const std::string& cut);




int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);

   optutl::CommandLineParser parser ("Applies a cut and saves a variable");

   //Input Files-------------------

   //Data
   parser.addOption("inputFile",optutl::CommandLineParser::kString,"Input File","DATA.root");
   parser.addOption("inputTree",optutl::CommandLineParser::kString,"Input Tree");
   parser.addOption("cut",optutl::CommandLineParser::kString,"Tree selection","");
   parser.addOption("weight",optutl::CommandLineParser::kString,"weight","");
   parser.addOption("normName",optutl::CommandLineParser::kString,"Name of Normalization variable");

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   TFile *fout = TFile::Open(parser.stringValue("outputFile").c_str() ,"UPDATE");

   //Define the workspace
   RooWorkspace *w = (RooWorkspace*)fout->Get("w");

   std::string inputFile = parser.stringValue("inputFile");
   std::string inputTree = parser.stringValue("inputTree");
   std::string normName  = parser.stringValue("normName");
   std::string cut = parser.stringValue("cut");
   std::string weight = parser.stringValue("weight"); 

   

   if(weight.size()!=0)
     if(w->var(weight.c_str())==0)
       w->factory(TString::Format("%s[0,10000]",weight.c_str()));




   
   TFile *f = new TFile(inputFile.c_str());

   TTree *t = (TTree*)f->Get(inputTree.c_str());
   TFile *ftmp = new TFile("tmp.root","RECREATE");
   ftmp->cd();
   TTree *treePass = t->CopyTree(cut.c_str());
   printf("Saving normalization\n");
   TH1F *test = new TH1F("test","test",2,0,2);
   treePass->Draw("1>>test",weight.c_str());

   printf("Normalization calculated as %f\n",test->Integral());
   w->factory(TString::Format("%s[%f]",normName.c_str(),test->Integral()));
   w->var(normName.c_str())->setConstant(kTRUE);

   delete test;
   delete treePass;

   fout->cd();
   w->Write("w",TObject::kOverwrite);
   f->Close();
   fout->Close();




}

