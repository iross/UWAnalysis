#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "RooWorkspace.h"



int main (int argc, char* argv[]) 
{
  using namespace RooFit;


   optutl::CommandLineParser parser ("Creates empty workspace");

   //Input Files-------------------

   //Data
   //Parse Arguments!
   parser.parseArguments (argc, argv);

   //Define the workspace
   RooWorkspace *w = new RooWorkspace("w","workspace");
   std::string output = parser.stringValue("outputFile");
   w->writeToFile(output.c_str());
   

}

