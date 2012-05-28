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

   
   parser.parseArguments (argc, argv);

   std::vector<std::string> files   = parser.stringVector("inputFiles");
   double lumi = parser.doubleValue("lumi");
   
   float errors[500][10];
   vector<string> labels;
   float err;

   for(size_t n=0;n<files.size();++n){
   
   		//get the number of and name filters
   		TFile f(files[n].c_str());

 	   	TTree *t = (TTree*)f.Get(parser.stringValue("tree").c_str());   
    	TH1F* results = (TH1F*)f.Get("summary/results");
  		float weight;
   		t->SetBranchAddress("__WEIGHT__",&weight);
   		t->GetEntry(0);

   			for(int i=0;i<=results->GetNbinsX();++i) {
   				if(n==0){labels.push_back(results->GetXaxis()->GetBinLabel(i));}

				errors[i][n] = weight*lumi*pow(results->GetBinContent(i),0.5);
				
   			}

   		f.Close();
  	
   }

   
   for(size_t i=1; i<labels.size();++i){
   		err = 0;
   		for(size_t n=0; n<files.size(); ++n){
   		 	err += pow(errors[i][n],2);
   		}
   		err = pow(err,0.5);
   		printf("%s %f \n",labels[i].c_str(),err);
   }

  
}
