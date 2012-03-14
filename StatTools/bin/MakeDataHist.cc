#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "TH1F.h"
#include "TTree.h"
#include "TStyle.h"
#include "RooWorkspace.h"
#include "RooDataHist.h"
#include "RooRealVar.h"
#include "RooCategory.h"




int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);

   optutl::CommandLineParser parser ("Creates a RooDataSet From a Histogram");

   //Data
   parser.addOption("inputFile",optutl::CommandLineParser::kString,"Input File","DATA.root");
   parser.addOption("inputTree",optutl::CommandLineParser::kString,"Input Tree","muTauEventTree/eventTree");
   parser.addOption("name",optutl::CommandLineParser::kString,"Name of the dataset");
   parser.addOption("variables",optutl::CommandLineParser::kString,"Variable from the tree");
   parser.addOption("variableNewnames",optutl::CommandLineParser::kString,"Variables from the tree");
   parser.addOption("bins",optutl::CommandLineParser::kInteger,"bins",60);
   parser.addOption("min",optutl::CommandLineParser::kDouble,"Minimum vector");
   parser.addOption("max",optutl::CommandLineParser::kDouble,"Maximum Vector");
   parser.addOption("cut",optutl::CommandLineParser::kString,"Tree preselection","");
   parser.addOption("weight",optutl::CommandLineParser::kString,"weight","");
   parser.addOption("binning",optutl::CommandLineParser::kDoubleVector,"binning");


   //Parse Arguments!
   parser.parseArguments (argc, argv);
   TFile *fout = TFile::Open(parser.stringValue("outputFile").c_str() ,"UPDATE");

   //Define the workspace
   RooWorkspace *w = (RooWorkspace*)fout->Get("w");


   std::string inputFile = parser.stringValue("inputFile");
   std::string inputTree = parser.stringValue("inputTree");
   std::string var = parser.stringValue("variables");
   std::string varNewName = parser.stringValue("variableNewNames");
   std::string cut = parser.stringValue("cut");
   double min = parser.doubleValue("min");
   double max = parser.doubleValue("max");
   int bins = parser.integerValue("bins");
   std::vector<double> binning =parser.doubleVector("binning"); 

   //create the variable
   if(w->var(var.c_str())==0)
     w->factory(TString::Format("%s[%f,%f]",var.c_str(),min,max));
   if(w->var(var.c_str())==0)
     w->factory(TString::Format("%s[%f,%f]",varNewName.c_str(),min,max));
   
   //open the file and get the tree
   TFile *f = new TFile(inputFile.c_str());
   TTree *t = (TTree*)f->Get(inputTree.c_str());

   //create a Histogram
   TH1F *h =0;
   if(binning.size()==0)
     h= new TH1F("h","h1k",bins,min,max);
   else
     h = new TH1F("h","h1k",bins,&binning[0]);


   if(parser.stringValue("weight").size()>0)
     t->Draw((var+">>h").c_str(),(parser.stringValue("weight")+"*("+cut+")").c_str());
   else
     t->Draw((var+">>h").c_str(),cut.c_str());

   RooDataHist *data = new RooDataHist(parser.stringValue("name").c_str(),"tempDS",RooArgList(*w->var(var.c_str())),h);


   if(varNewName.size()==0)
     w->import(*data);
   else if(varNewName.size()>0)
     w->import(*data,RenameVariable(var.c_str(),varNewName.c_str()));

    fout->cd(); 
    w->Write("w",TObject::kOverwrite);
    fout->Close();
    f->Close();


   

}

