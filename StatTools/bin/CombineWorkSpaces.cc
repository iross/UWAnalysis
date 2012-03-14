#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "RooWorkspace.h"



int main (int argc, char* argv[]) 
{
  using namespace RooFit;


   optutl::CommandLineParser parser ("Combines workspaces from multiple files");

   //Input Files-------------------

   //Data

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   //Define the workspace
   RooWorkspace *w = new RooWorkspace("w","workspace");
   std::vector<std::string> inputs = parser.stringVector("inputFiles");
   std::string output = parser.stringValue("outputFile");

   for(unsigned int i=0;i<inputs.size();++i) {
     TFile *f = TFile::Open(inputs[i].c_str());
     RooWorkspace *wF = (RooWorkspace*)f->Get("w");
     w->merge(*wF);
   }

   w->writeToFile(output.c_str());
   

}

