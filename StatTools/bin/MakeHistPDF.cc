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
   parser.addOption("variableNewName",optutl::CommandLineParser::kString,"Variable from the tree","");
   parser.addOption("pdfNames",optutl::CommandLineParser::kStringVector,"PDF Names");
   parser.addOption("min",optutl::CommandLineParser::kDouble,"Min",0.);
   parser.addOption("max",optutl::CommandLineParser::kDouble,"Max",600.);
   parser.addOption("cut",optutl::CommandLineParser::kString,"Tree preselection","");
   parser.addOption("bins",optutl::CommandLineParser::kInteger,"bins",60);
   parser.addOption("weight",optutl::CommandLineParser::kString,"weight","");
   parser.addOption("binning",optutl::CommandLineParser::kDoubleVector,"binning");

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   TFile *fout = TFile::Open(parser.stringValue("outputFile").c_str() ,"UPDATE");

   //Define the workspace
   RooWorkspace *w = (RooWorkspace*)fout->Get("w");

   std::string inputFile = parser.stringValue("inputFile");
   std::vector<std::string> inputTrees = parser.stringVector("inputTrees");
   std::vector<std::string> pdfNames = parser.stringVector("pdfNames");
   std::string var = parser.stringValue("variable");
   std::string varNewname = parser.stringValue("variableNewName");
   if(varNewname=="") varNewname=var;
   std::string cut = parser.stringValue("cut");
   double min = parser.doubleValue("min");
   double max = parser.doubleValue("max");
   std::string weight = parser.stringValue("weight"); 
   int bins = parser.integerValue("bins");
   std::vector<double> binning = parser.doubleVector("binning");

   
   w->factory(TString::Format("%s[%f,%f]",var.c_str(),min,max));
   w->var(var.c_str())->setBins(bins);
   w->var(var.c_str())->setMin(min);
   w->var(var.c_str())->setMax(max);

   if(weight.size()!=0)
     if(w->var(weight.c_str())==0)
       w->factory(TString::Format("%s[0,10000]",weight.c_str()));

   if(binning.size()!=0) {
     RooBinning rooBinning(bins,&binning[0]);
     w->var(var.c_str())->setBinning(rooBinning);
   }

   RooPlot * frame = w->var(var.c_str())->frame() ;


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

     //convert to histogram
     RooDataHist *tempDS = new RooDataHist("tempDS","tempDS",RooArgList(*w->var(var.c_str())),h);
     RooHistPdf pdf(pdfNames[i].c_str(),pdfNames[i].c_str(), *w->var(var.c_str()),  *tempDS);
     printf("Importing\n");
     w->import(pdf,RenameVariable(var.c_str(),varNewname.c_str()));

     pdf.plotOn(frame);
     
     delete tempDS;
     delete h;
     ftmp->Close();

   }

   frame->Draw();
   gPad->SaveAs(("plots/"+pdfNames[0]+".png").c_str());
   delete frame;

   //Write it in root
   fout->cd(); 
   w->Write("w",TObject::kOverwrite);
   
   f->Close();
   fout->Close();
}

