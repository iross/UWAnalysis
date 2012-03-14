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
   parser.addOption("weight",optutl::CommandLineParser::kString,"weight","");
   parser.addOption("rho",optutl::CommandLineParser::kDouble,"rho",2.0);
   parser.addOption("maxEntries",optutl::CommandLineParser::kInteger,"maxEntries",5000);

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

   
   w->factory(TString::Format("%s[%f,%f]",var.c_str(),min,max));
   if(weight.size()!=0)
     if(w->var(weight.c_str())==0)
       w->factory(TString::Format("%s[0,10000]",weight.c_str()));


   RooRealVar * mass = w->var(var.c_str());

   
   TFile *f = new TFile(inputFile.c_str());
   for(unsigned int i=0;i<inputTrees.size();++i) {
     printf("Reading tree %s\n",inputTrees[i].c_str());
     TTree *t = (TTree*)f->Get(inputTrees[i].c_str());
     TFile *ftmp = new TFile("tmp.root","RECREATE");
     ftmp->cd();

     printf("Applying Cut %s on %d entries\n",cut.c_str(),(int)t->GetEntries());
     //     TTree *treePass = t->CopyTree(cut.c_str(),"",parser.integerValue("maxEntries"));
     TTree *treePassCut = t->CopyTree(cut.c_str(),"");
     TTree *treePass = t->CopyTree("","",10000);

     printf("%d entries in tree after cuts\n",(int)treePass->GetEntries()); 
   
     RooDataSet *data;
     if(weight.size()==0) 
       data = new RooDataSet("dataset", "dss", treePass, RooArgSet(*mass));
     else
       data = new RooDataSet("dataset", "dss", treePass, RooArgSet(*mass,w->var(weight.c_str())),weight.c_str());

     RooKeysPdf pdf(pdfNames[i].c_str(),pdfNames[i].c_str(), *mass,  *data,RooKeysPdf::NoMirror,parser.doubleValue("rho"));
     //      RooNDKeysPdf *pdf = new RooNDKeysPdf(pdfName.c_str(),"PDF", RooArgList(*mass), *data,"a",1.0,3,kTRUE);
     printf("Importing\n");
      w->import(pdf,RenameVariable(var.c_str(),varNewname.c_str()));
  
      //    //Draw It
      RooPlot * Frame2 = mass->frame() ;
      pdf.plotOn(Frame2);
      Frame2->Draw();
      gPad->SaveAs(("plots/"+pdfNames[i]+".png").c_str());
      delete Frame2;
      delete data;
      delete treePass;
      delete treePassCut;
      ftmp->Close();
   }

   //Write it in root
    fout->cd(); 
    w->Write("w",TObject::kOverwrite);
   

    f->Close();
    fout->Close();




}

