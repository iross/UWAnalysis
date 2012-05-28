#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooArgSet.h"



int main (int argc, char* argv[]) 
{
  using namespace RooFit;


   optutl::CommandLineParser parser ("Combines datasets to create a new simultaneous one");
   parser.addOption("categoryVariable",optutl::CommandLineParser::kString,"CategoryVar","channel");
   parser.addOption("categories",optutl::CommandLineParser::kStringVector,"Categories");
   parser.addOption("inputNames",optutl::CommandLineParser::kStringVector,"Input names");
   parser.addOption("name",optutl::CommandLineParser::kString,"Data set name");


   //Input Files-------------------

   //Data

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   //Define the workspace
   TFile *fout = TFile::Open(parser.stringValue("outputFile").c_str() ,"UPDATE");

   //Define the workspace
   RooWorkspace *w = (RooWorkspace*)fout->Get("w");
   w->factory("mass[0.,1000.]");

   std::vector<std::string> inputNames = parser.stringVector("inputNames");
   std::string output = parser.stringValue("outputFile");
   std::string name = parser.stringValue("name");
   std::string catVar = parser.stringValue("categoryVariable");
   std::vector<std::string> categories = parser.stringVector("categories");


   //first create the category string
   TString catStr = TString::Format("%s[",catVar.c_str());
   for(unsigned int i=0;i<categories.size();++i)
     if(i<categories.size()-1)
       catStr+=TString::Format("%s=%d,",categories[i].c_str(),i);
     else
       catStr+=TString::Format("%s=%d]",categories[i].c_str(),i);

   w->factory(catStr.Data());


   std::map<string,RooDataSet*> importMap;

   RooArgSet variables;

   for(unsigned int i=0;i<inputNames.size();++i) {
     if(i==0) {
       w->defineSet("dataVars",*w->set("dataVars"));
     }
     RooDataSet * data =(RooDataSet*) w->data(inputNames.at(i).c_str());
     printf("Importing %d entries\n",data->numEntries()); 
     importMap[categories[i]] = data;
   }

   RooDataSet *newdata=new RooDataSet(name.c_str(),name.c_str(),*w->set("dataVars"),Index(*w->cat(catVar.c_str())),Import(importMap));
   w->import(*newdata);

   fout->cd(); 
   w->Write("w",TObject::kOverwrite);
   fout->Close();
  

   

}

