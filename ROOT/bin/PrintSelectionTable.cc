#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include <iostream>
#include <sstream>

using namespace std;

int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Prints the Event Selection table");
   parser.addOption("lumi",optutl::CommandLineParser::kDouble,"luminosity");
   parser.addOption("eff",optutl::CommandLineParser::kInteger,"doEfficiency",0);
   parser.addOption("tree",optutl::CommandLineParser::kString,"tree","eleTauEventTree/eventTree");

   parser.parseArguments (argc, argv);

   std::vector<std::string> files   = parser.stringVector("inputFiles");
   double lumi = parser.doubleValue("lumi");
   
   //get the number of and name filters
   TFile f(files[0].c_str());

   TTree *t = (TTree*)f.Get(parser.stringValue("tree").c_str());

   float weight;
   t->SetBranchAddress("__WEIGHT__",&weight);
   t->GetEntry(0);

   TH1F* results = (TH1F*)f.Get("summary/results");
   for(int i=1;i<=results->GetNbinsX();++i) {

     if(parser.integerValue("eff")==0) {
       if(lumi!=0)
	 printf("%s : %f += %f \n",results->GetXaxis()->GetBinLabel(i),weight*lumi*results->GetBinContent(i),weight*lumi*results->GetBinError(i));
       else
	 printf("%s : %f += %f \n",results->GetXaxis()->GetBinLabel(i),results->GetBinContent(i),results->GetBinError(i));

     }
     else if(parser.integerValue("eff")==1)
       {
	 if(i>1)
	   printf("%s : %f  \n",results->GetXaxis()->GetBinLabel(i),results->GetBinContent(i)/results->GetBinContent(i-1));
       }
     else if(parser.integerValue("eff")==2)
	 if(i>1)
	   printf("%s : %f  \n",results->GetXaxis()->GetBinLabel(i),results->GetBinContent(i)/results->GetBinContent(1));


   }
   f.Close();
   
}


void printFile(std::string file , optutl::CommandLineParser parser) {


}
