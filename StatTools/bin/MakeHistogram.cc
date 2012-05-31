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
#include "RooBinning.h"
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

   optutl::CommandLineParser parser ("Creates a PDF from a tree using Kernel Density Estimators");

   //Input Files-------------------

   //Data
   parser.addOption("inputFile",optutl::CommandLineParser::kString,"Input File","DATA.root");
   parser.addOption("inputTrees",optutl::CommandLineParser::kStringVector,"Input Trees");
   parser.addOption("variable",optutl::CommandLineParser::kString,"Variable from the tree","muTauMass");
   parser.addOption("histoNames",optutl::CommandLineParser::kStringVector,"PDF Names");
   parser.addOption("folderName",optutl::CommandLineParser::kString,"folderName");
   parser.addOption("min",optutl::CommandLineParser::kDouble,"Min",0.);
   parser.addOption("max",optutl::CommandLineParser::kDouble,"Max",600.);
   parser.addOption("cut",optutl::CommandLineParser::kString,"Tree preselection","");
   parser.addOption("bins",optutl::CommandLineParser::kInteger,"bins",60);
   parser.addOption("weight",optutl::CommandLineParser::kString,"weight","");
   parser.addOption("binning",optutl::CommandLineParser::kDoubleVector,"binning");

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   TFile *fout = TFile::Open(parser.stringValue("outputFile").c_str() ,"UPDATE");

   std::string inputFile = parser.stringValue("inputFile");
   std::vector<std::string> inputTrees = parser.stringVector("inputTrees");
   std::vector<std::string> pdfNames = parser.stringVector("histoNames");
   std::string var = parser.stringValue("variable");
   std::string cut = parser.stringValue("cut");
   double min = parser.doubleValue("min");
   double max = parser.doubleValue("max");
   std::string weight = parser.stringValue("weight"); 
   int bins = parser.integerValue("bins");
   std::vector<double> binning = parser.doubleVector("binning");
   std::string foldername = parser.stringValue("folderName");

   //create folder 
   if(fout->Get(foldername.c_str())==0)
     fout->mkdir(foldername.c_str());

   TFile *f = new TFile(inputFile.c_str());
   for(unsigned int i=0;i<inputTrees.size();++i) {
     printf("Reading tree %s\n",inputTrees[i].c_str());
     TTree *t = (TTree*)f->Get(inputTrees[i].c_str());
     TFile *ftmp = new TFile("tmp.root","RECREATE");
     ftmp->cd();
     TH1F *h=0;

     if(binning.size()==0)
       h= new TH1F("h","h1k",bins,min,max);
     else
       h = new TH1F("h","h1k",bins,&binning[0]);

     h->Sumw2();
     
     if(weight.size()==0) 
       t->Draw((var+">>h").c_str(),cut.c_str());
     else
       t->Draw((var+">>h").c_str(),(weight+"*("+cut+")").c_str());
     
     h->SetName(pdfNames[i].c_str());
     fout->cd(foldername.c_str());
     h->Write();
   }

   
   f->Close();
   fout->Close();
}

