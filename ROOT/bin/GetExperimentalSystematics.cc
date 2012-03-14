#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TMath.h"
#include <iostream>
#include <sstream>

using namespace std;

int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Prints the Event Selection table");
   parser.addOption("folders",optutl::CommandLineParser::kStringVector,"folders");
   parser.addOption("cut",optutl::CommandLineParser::kString,"cut");
   parser.addOption("file",optutl::CommandLineParser::kString,"file");

   parser.parseArguments (argc, argv);

   TFile *f = new TFile(parser.stringValue("file").c_str());
   std::vector<std::string> folders = parser.stringVector("folders");
   std::vector<float> yields;
   for(unsigned int i=0;i<folders.size();++i) {
     TTree *h = (TTree*)f->Get((folders[i]+"/eventTree").c_str());
     yields.push_back(h->GetEntries(parser.stringValue("cut").c_str()));
     
   }

   printf("Systematics for %s\n",parser.stringValue("file").c_str());

   float total=0.0;
   for(unsigned int i=1;i<yields.size();++i) {
     printf("     %s : %f percent\n",folders[i].c_str(),(yields[i]-yields[0])*100/yields[0]);
     total+=((yields[i]-yields[0])/yields[0])*((yields[i]-yields[0])/yields[0]);
       }
   printf("total = %f \n",TMath::Sqrt(total)*100.);
   f->Close();

}
