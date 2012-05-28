#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TEfficiency.h"
#include "TMath.h"
#include <iostream>
#include <sstream>

using namespace std;

int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Prints the Event Selection table");
   parser.addOption("folder",optutl::CommandLineParser::kString,"folder");
   parser.addOption("cut",optutl::CommandLineParser::kString,"cut");
   parser.addOption("preCut",optutl::CommandLineParser::kString,"preCcut");
   parser.addOption("file",optutl::CommandLineParser::kString,"file");
   parser.addOption("fileMC",optutl::CommandLineParser::kString,"file");

   parser.parseArguments (argc, argv);

   TFile *f   = new TFile(parser.stringValue("file").c_str());
   TFile *fMC = new TFile(parser.stringValue("fileMC").c_str());

  std::string folder = parser.stringValue("folder");
  TH1F *h = new TH1F("h","h",2,0,2);
  TTree *t = (TTree*)f->Get((folder+"/eventTree").c_str());

  t->Draw("1>>h",(parser.stringValue("preCut").c_str()));
  float data_denom = h->Integral();

  t->Draw("1>>h",(parser.stringValue("preCut")+"&&"+parser.stringValue("cut")).c_str());
  float data_num = h->Integral();

  TTree *tMC = (TTree*)fMC->Get((folder+"/eventTree").c_str());

  tMC->Draw("1>>h",("("+parser.stringValue("preCut")+")*4000*__WEIGHT__").c_str());
  double mc_denomErr = 0.0;
    float mc_denom = h->IntegralAndError(1,2,mc_denomErr);

  tMC->Draw("1>>h",("("+parser.stringValue("preCut")+"&&"+parser.stringValue("cut")+")*4000*__WEIGHT__").c_str());
  double mc_numErr = 0.0;
  float mc_num = h->IntegralAndError(1,2,mc_numErr);

  float correction = data_num*mc_denom/(mc_num*data_denom);
  float correctionErr =correction*sqrt(pow(mc_numErr/mc_num,2)+
				       pow(mc_denomErr/mc_denom,2)+
				       pow(1./sqrt(data_num),2)+
				       pow(1./sqrt(data_denom),2));

  printf("Eff Data      = %f +-%f \n",data_num/data_denom,
	 max(TEfficiency::ClopperPearson(data_denom,data_num,0.68,true)-data_num/data_denom,data_num/data_denom-TEfficiency::ClopperPearson(data_denom,data_num,0.68,false)));

  printf("Correction factor      = %f +-%f \n",correction,correctionErr);

   f->Close();
   fMC->Close();

}
