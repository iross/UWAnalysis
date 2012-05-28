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
   
   int numbers[500][10];
   int errors[500][10];
   vector<string> labels;
   std::string dataFile = "DATA.root";
   
   for(size_t n=0;n<files.size();++n){
   
   		//get the number of and name filters
   		TFile f(files[n].c_str());

 	   	TTree *t = (TTree*)f.Get(parser.stringValue("tree").c_str());   
    	TH1F* results = (TH1F*)f.Get("summary/results");
    	
  		
  		
   		if(files[n].c_str()==dataFile){   		
   			for(int i=0;i<=results->GetNbinsX();++i) {		
				if(n==0){labels.push_back(results->GetXaxis()->GetBinLabel(i));}
				numbers[i][n] = results->GetBinContent(i);
				errors[i][n] = pow(results->GetBinContent(i),0.5);
   			}
   		}
   		else{
   			for(int i=0;i<=results->GetNbinsX();++i) {
   			
  				float weight;
   				t->SetBranchAddress("__WEIGHT__",&weight);
   				t->GetEntry(0);
				numbers[i][n] = weight*lumi*results->GetBinContent(i);
				errors[i][n] = weight*lumi*pow(results->GetBinContent(i),0.5);
				if(n==0){labels.push_back(results->GetXaxis()->GetBinLabel(i));}
   			}
   		}
   		f.Close();
  	
   }
   printf("\\begin{table}[htbp] \n");
   printf("\\centering \n");
   printf("\\begin{tabular}{|c||c|c|c|c|c|} \n");
   printf("\\hline \n");
   printf("\\multicolumn{%i}{|c|}{$e+\\tau$}  \\\\ \n",files.size());
   printf("\\hline \n");
   for(size_t m=0; m<files.size(); ++m){
   		printf(" & %s ", files[m].c_str());
   }
   printf(" \\\\ \n");
   printf("\\hline \n");
   printf("\\hline \n");
   for(size_t i=1; i<labels.size();++i){
   		printf("%s ",labels[i].c_str());
   		for(size_t n=0; n<files.size(); ++n){
   		 	printf("& %i $\\pm$ %i ", numbers[i][n], errors[i][n]);
   		}
   		printf("\\\\ \n");
   }
   printf("Di-Electron Veto & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # \\\\ \n");
   printf("HLT & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # \\\\ \n");
   printf("\\hline \n");
   printf("\\end{tabular} \n");
   printf("\\caption{Cut Flow , $e+ \\tau$ channel.}  \n");
   printf("\\label{table:etauevents} \n");
   printf("\\end{table} \n");
  
}
