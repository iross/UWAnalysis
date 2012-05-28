#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include <iostream>
#include <sstream>
#include <math.h>
using namespace std;

int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Prints the Event Selection table");
   parser.addOption("lumi",optutl::CommandLineParser::kDouble,"luminosity");
   parser.addOption("eff",optutl::CommandLineParser::kInteger,"doEfficiency",0);
   parser.addOption("tree",optutl::CommandLineParser::kString,"tree","eleTauEventTree/eventTree");
   parser.addOption("cuts",optutl::CommandLineParser::kStringVector,"cuts");
   parser.addOption("labels",optutl::CommandLineParser::kStringVector,"labels");

   parser.parseArguments (argc, argv);

   std::vector<std::string> files   = parser.stringVector("inputFiles");
   double lumi = parser.doubleValue("lumi");
   
   //get the number of and name filters
   TFile f(files[0].c_str());

   TTree *t = (TTree*)f.Get(parser.stringValue("tree").c_str());

   //get the cuts from the input
   std::vector<std::string> cuts = parser.stringVector("cuts");
   std::vector<std::string> labels = parser.stringVector("labels");
   std::string cutString="";
   //loop on the cuts and fill the string to have all previous + the current cut
   for(unsigned int i=0;i<cuts.size();++i) {
     if(i==0)
       cutString = cuts[i];
     else
       cutString+="&&"+cuts[i];



     float entries = (float)t->GetEntries(cutString.c_str());
     
     //if lumi==0 it is DATA so just get the entries
     if(lumi==0.0)
       printf("%s : %f +- %f \n",labels[i].c_str(),entries,sqrt(entries));
     else {//MC
       //draw a histogram using a var that is common to all ntuples
       //like PVs>-1 is always true .Weigh the histogram
       TH1F *h = new TH1F("h","h",2,0,2);
       h->Sumw2();
       t->Draw("(PVs>-1)>>h",TString::Format("(%s)*__WEIGHT__*%f",cutString.c_str(),lumi));
       printf("%s : %f +- %f \n",labels[i].c_str(),h->GetBinContent(2),h->GetBinError(2));
       delete h;
     }


   }
     



   f.Close();
   
}
