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
   optutl::CommandLineParser parser ("Prints the Event Yield table");
   parser.addOption("lumi",optutl::CommandLineParser::kDouble,"luminosity");
   parser.addOption("eff",optutl::CommandLineParser::kInteger,"doEfficiency",0);

   std::vector<std::string> trees;
   trees.push_back("eleEleEleEleEventTree/eventTree");
   trees.push_back("eleEleMuMuEventTree/eventTree");
   trees.push_back("muMuEleEleEventTree/eventTree");
   trees.push_back("muMuMuMuEventTree/eventTree");
   trees.push_back("muMuTauTauEventTree/eventTree");
   trees.push_back("muMuMuTauEventTree/eventTree");
   trees.push_back("muMuEleTauEventTree/eventTree");
   trees.push_back("muMuEleMuEventTree/eventTree");
   trees.push_back("eleEleTauTauEventTree/eventTree");
   trees.push_back("eleEleMuTauEventTree/eventTree");
   trees.push_back("eleEleEleTauEventTree/eventTree");
   trees.push_back("eleEleEleMuEventTree/eventTree");
   
   std::vector<std::string> labels;
   
   labels.push_back("$eeee$");
   labels.push_back("$ee\\mu\\mu$");
   labels.push_back("$\\mu\\mu ee$");
   labels.push_back("$\\mu\\mu\\mu\\mu$");
   labels.push_back("$\\mu\\mu\\tau\\tau$");
   labels.push_back("$\\mu\\mu\\mu\\tau$");
   labels.push_back("$\\mu\\mu e\\tau$");
   labels.push_back("$\\mu\\mu e\\mu$");
   labels.push_back("$ee\\tau\\tau$");
   labels.push_back("$ee\\mu\\tau$");
   labels.push_back("$eee\\tau$");
   labels.push_back("$eee\\mu$");
   
   std::vector<string> cuts;
   
   cuts.push_back("z2Charge==0&&z1Mass>60&&z1Mass<120&&z2l1CiCTight&9==9&&z2l2CiCTight&9==9&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z2l1MissHits<2&&z2l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20");
   cuts.push_back("z2Charge==0&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1RelPfIsoRho<0.25&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20");
   cuts.push_back("z2Charge==0&&z1Mass>60&&z1Mass<120&&z2l1CiCTight&9==9&&z2l2CiCTight&9==9&&z2l1MissHits<2&&z2l2MissHits<2&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z2Charge==0&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.25&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30&&z2l2Pt>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25&&z2Charge==0");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1MediumIso&&z2l2MediumIso&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2LooseIso&&z2l1RelPfIsoRho<0.2&&z2l2EleVeto&&z2l2MuVetoTight&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20");
   cuts.push_back("z1Mass>60&&z1Mass<120&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25&&z2Charge==0");
  
   parser.parseArguments (argc, argv);

   std::vector<std::string> files   = parser.stringVector("inputFiles");
   double lumi = parser.doubleValue("lumi");
   
   float numbers[50][15];
   float errors[50][15];

   for(size_t n=0;n<files.size();++n){

   		//get the number of and name filters
   		TFile f(files[n].c_str());

		for(size_t l=0; l<trees.size();++l){

 	   	   TTree *t = (TTree*)f.Get(trees[l].c_str());   
	       TH1F *h = new TH1F("h","h",2,0,2);
	       h->Sumw2();
	       t->Draw("1>>h",TString::Format("(%s)*__WEIGHT__*%f",cuts[l].c_str(),lumi));
	       numbers[n][l] = h->GetBinContent(2);
	       errors[n][l] = h->GetBinError(2);
	       delete h;

	    }
	    
   f.Close();

   }



   vector<float> Sig;

   printf("\\begin{table}[htbp] \n");
   printf("\\centering \n");
   printf("\\begin{tabular}{|c||c|c|c|c|c|c|} \n");
   printf("\\hline \n");
   for(size_t m=0; m<files.size(); ++m){
   		printf(" & %s ", files[m].c_str());
   }
   printf(" \\\\ \n");
   printf("\\hline \n");
   printf("\\hline \n");
   for(size_t i=0; i<trees.size();++i){
   		printf("%s ",labels[i].c_str());
   	   	float S = 0;
   		float B = 0;	
   		for(size_t n=0; n<files.size(); ++n){
   		 	printf("& %0.2f $\\pm$ %0.4f ", numbers[n][i], errors[n][i]);
   		 	if(n==0){ S = numbers[n][i]; }
   		 	if(n>1) { B += numbers[n][i]; }
   		}
   		Sig.push_back(S/sqrt(S+B));
   		printf("\\\\ \n");
   }
   printf("\\hline \n");
   printf("\\end{tabular} \n");
   printf("\\caption{Event Yields}  \n");
   printf("\\label{table:eventYields} \n");
   printf("\\end{table} \n");

   printf("\n \n \n");   
   for(size_t l=0; l<Sig.size(); ++l){
   		printf("%s  %f \n", labels[l].c_str(), Sig[l] );
   }
  
}