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
   parser.addOption("tree",optutl::CommandLineParser::kString,"tree","muTauEventTree/eventTree");

   int NFiles = 5;
   parser.parseArguments (argc, argv);

   std::vector<std::string> files   = parser.stringVector("inputFiles");
   double lumi = parser.doubleValue("lumi");
   
   int numbers[500][5];
   int errors[500][5];
   vector<string> labels;
   
   for(int n=0;n<=NFiles-1;++n){
   
   		//get the number of and name filters
   		TFile f(files[n].c_str());

 	   	TTree *t = (TTree*)f.Get(parser.stringValue("tree").c_str());   
    	TH1F* results = (TH1F*)f.Get("summary/results");
  		
   		if(n==0){   		
   			for(int i=0;i<=results->GetNbinsX();++i) {		

				labels.push_back(results->GetXaxis()->GetBinLabel(i));
				numbers[i][n] = results->GetBinContent(i);
				errors[i][n] = pow(results->GetBinContent(i),0.5);
   			}
   		}
   		if(n>0){
   			for(int i=0;i<=results->GetNbinsX();++i) {
   			
  				float weight;
   				t->SetBranchAddress("__WEIGHT__",&weight);
   				t->GetEntry(0);
				numbers[i][n] = weight*lumi*results->GetBinContent(i);
				errors[i][n] = weight*lumi*pow(results->GetBinContent(i),0.5);
				
   			}
   		}
   		f.Close();
  	
   }
   printf("\\begin{table}[htbp] \n");
   printf("\\centering \n");
   printf("\\begin{tabular}{|c|c|c|c|c|c|} \n");
   printf("\\hline \n");
   printf("\\multicolumn{5}{|c|}{$\\mu+\\tau$}  \\\\ \n");
   printf("\\hline \n");
   printf(" & Data & Z $\\rightarrow \\tau\\tau$ & W+Jets & QCD & $t\\bar{t}$/EWK \\\\ \n");
   printf("\\hline \n");
   printf("\\hline \n");
   for(size_t i=1; i<labels.size();++i){
   		printf("%s ",labels[i].c_str());
   		for(int n=0; n<=NFiles-1; ++n){
   		 	printf("& %i $\\pm$ %i ", numbers[i][n], errors[i][n]);
   		}
   		printf("\\\\ \n");
   }
   printf("HLT & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # & # $\\pm$ # \\\\ \n");
   printf("\\hline \n");
   printf("\\end{tabular} \n");
   printf("\\caption{Cut Flow , $\\mu+ \\tau$ channel.}  \n");
   printf("\\label{table:mutauevents} \n");
   printf("\\end{table} \n");
  
}
