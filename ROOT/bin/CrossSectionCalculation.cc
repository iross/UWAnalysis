#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TH1.h"
#include <math.h>
int main (int argc, char* argv[]) 
{

  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Calculates Cross section");


   //Background Template Invariant mass
   parser.addOption("N",optutl::CommandLineParser::kDouble,"Number of Events",0.0);
   parser.addOption("dN",optutl::CommandLineParser::kDouble,"Number of Events Error",0.0);

   parser.addOption("L",optutl::CommandLineParser::kDouble,"Lumi",0.0);
   parser.addOption("dL",optutl::CommandLineParser::kDouble,"Lumi Error",0.0);

   parser.addOption("T",optutl::CommandLineParser::kDouble,"TauID",0.0);
   parser.addOption("dT",optutl::CommandLineParser::kDouble,"Tau ID Error",0.0);


   parser.addOption("E",optutl::CommandLineParser::kDoubleVector,"Efficiency");
   parser.addOption("dE",optutl::CommandLineParser::kDoubleVector,"EfficiencyError");




   parser.parseArguments (argc, argv);


   double denominator=1.0;
   double corr=1.;
   for(unsigned int i=0;i<parser.doubleVector("E").size();++i) {
     denominator*=parser.doubleVector("E").at(i);
     if(i>0)
       corr*=parser.doubleVector("E").at(i);
   }

   
   denominator*=parser.doubleValue("L");
   double sigma = parser.doubleValue("N")/denominator;
   double statErr = parser.doubleValue("dN")/denominator;


   double lumiErr = sigma*parser.doubleValue("dL")/parser.doubleValue("L");
   
   double systematic = 0.0;
   double systematicCorr = 0.0;
   for(unsigned int i=0;i<parser.doubleVector("dE").size();++i) {
     systematic+=sigma*sigma*parser.doubleVector("dE").at(i)*parser.doubleVector("dE").at(i);
     if(i>0)
       systematicCorr+=parser.doubleVector("dE").at(i)*parser.doubleVector("dE").at(i);
       
   }
   systematic = sqrt(systematic);
   systematicCorr = sqrt(systematicCorr)/corr;

   
   double tauidErr = sigma*parser.doubleValue("dT")/parser.doubleValue("T");
   
   printf("Correction factor = %f +- %f\n",corr,systematicCorr); 
   
   printf("Cross section result :: sigma = %f  pm %f (stat) pm %f (syst) pm %f (lumi) pm %f (tauID) \n",sigma,statErr,systematic,lumiErr,tauidErr);
   
}

