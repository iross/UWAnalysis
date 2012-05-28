#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
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
   parser.addOption("variables",optutl::CommandLineParser::kStringVector,"Variables from the tree");
   parser.addOption("variableNewnames",optutl::CommandLineParser::kStringVector,"Variables from the tree");
   parser.addOption("min",optutl::CommandLineParser::kDoubleVector,"Minimum vector");
   parser.addOption("max",optutl::CommandLineParser::kDoubleVector,"Maximum Vector");
   parser.addOption("cut",optutl::CommandLineParser::kString,"Tree preselection","");
   parser.addOption("weight",optutl::CommandLineParser::kString,"weight","");

   //Parse Arguments!
   parser.parseArguments (argc, argv);
   TFile *fout = TFile::Open(parser.stringValue("outputFile").c_str() ,"UPDATE");

   //Define the workspace
   RooWorkspace *w = (RooWorkspace*)fout->Get("w");


   std::string inputFile = parser.stringValue("inputFile");
   std::string inputTree = parser.stringValue("inputTree");
   std::vector<std::string> vars = parser.stringVector("variables");
   std::vector<std::string> varNewNames = parser.stringVector("variableNewNames");
   std::string cut = parser.stringValue("cut");
   std::vector<double> min = parser.doubleVector("min");
   std::vector<double> max = parser.doubleVector("max");
   RooArgSet variables("oldVars");
   RooArgSet newVariables("dataVars");

   //create the variables
   for(unsigned int i=0;i<vars.size();++i) {
      w->factory(TString::Format("%s[%f,%f]",vars[i].c_str(),min[i],max[i]));
      w->factory(TString::Format("%s[%f,%f]",varNewNames[i].c_str(),min[i],max[i]));
      variables.add(*w->var(vars[i].c_str()));
      newVariables.add(*w->var(varNewNames[i].c_str()));
   }

   w->defineSet("dataVars",newVariables);
   
   //open the file and get the tree
   TFile *f = new TFile(inputFile.c_str());
   TTree *t = (TTree*)f->Get(inputTree.c_str());
   TFile *ftmp = new TFile("tmp.root","RECREATE");
   ftmp->cd();
   //cut on the tree
   TTree *treePass = t->CopyTree(cut.c_str());

   //create a dataset if there is weight do weighted
   RooDataSet * data=0;
   if(parser.stringValue("weight").size()>0)
     data=new RooDataSet(parser.stringValue("name").c_str(),parser.stringValue("name").c_str(), treePass,variables,"",parser.stringValue("weight").c_str());
   else
     data=new RooDataSet(parser.stringValue("name").c_str(),parser.stringValue("name").c_str(), treePass,variables);


   if(varNewNames.size()==0)
     w->import(*data);
   else if(varNewNames.size()==1)
     w->import(*data,RenameVariable(vars[0].c_str(),varNewNames[0].c_str()));
   else if(varNewNames.size()==2)
     w->import(*data,RenameVariable(vars[0].c_str(),varNewNames[0].c_str()),RenameVariable(vars[1].c_str(),varNewNames[1].c_str()));
   else if(varNewNames.size()==3)
     w->import(*data,RenameVariable(vars[0].c_str(),varNewNames[0].c_str()),RenameVariable(vars[1].c_str(),varNewNames[1].c_str()),RenameVariable(vars[2].c_str(),varNewNames[2].c_str()));


    fout->cd(); 
    w->Write("w",TObject::kOverwrite);
    ftmp->Close();
    fout->Close();
    f->Close();


   

}

