#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooBifurGauss.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGlobalFunc.h" 
#include "RooChi2Var.h"
#include "RooRealVar.h"
#include "RooLandau.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooNumConvPdf.h"
#include "RooMinuit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 



void extractSignal(float osHigh,float osLow,float vvHigh,float vvLow,float other,optutl::CommandLineParser parser);

//float getFluctuatedEvents(TTree*,std:string selection);

int main (int argc, char* argv[]) 
{
  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------

   //Data
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   parser.addOption("preselection",optutl::CommandLineParser::kString,"preselection","HLT_Any&&lPfRelIso<0.1&&vertices>0&&diLeptons==0&&tauMuonVeto&&tauElectronVeto");
   parser.addOption("osHighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("osLowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("topFactor",optutl::CommandLineParser::kDouble,"W factor",0.31);
   parser.addOption("topFactorErr",optutl::CommandLineParser::kDouble,"W factor error ",0.00);
   parser.addOption("vvLow",optutl::CommandLineParser::kDouble,"DiBoson From MC Low",1.6);
   parser.addOption("vvHigh",optutl::CommandLineParser::kDouble,"DiBoson From MC High",3.0);
   parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson RelativeError",0.5);   
   parser.addOption("others",optutl::CommandLineParser::kDouble,"others",3.0);
   parser.addOption("othersErr",optutl::CommandLineParser::kDouble,"others RelativeError",0.5);   
   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","muTauEventTree/eventTree");
   parser.parseArguments (argc, argv);


   //translate the parser selections 
   std::string preselection    = parser.stringValue("preselection");
   std::string oshighSelection = preselection+"&&"+parser.stringValue("osHighSelection");
   std::string oslowSelection  = preselection+"&&"+parser.stringValue("osLowSelection");

   //Get file and tree
   TFile *f = new TFile(parser.stringValue("dataFile").c_str());
   TTree *t =(TTree*) f->Get(parser.stringValue("treeName").c_str());
   
   //calculate events in the regions

   float osHigh = t->GetEntries( oshighSelection.c_str());
   float osLow = t->GetEntries( oslowSelection.c_str());
   float vvHigh = parser.doubleValue("vvHigh");
   float vvLow = parser.doubleValue("vvLow");
   float other = parser.doubleValue("others");


   extractSignal(osHigh,osLow,vvHigh, vvLow,other,parser);

}


void extractSignal(float osHigh,float osLow,float vvHigh,float vvLow,float other,optutl::CommandLineParser parser)
{



  printf("total os high events = %f\n",osHigh);
  printf("total os low events = %f\n",osLow);



   printf("Diboson from MC\n");
   printf("---------------\n");
   double VVLow = vvLow;
   double VVLowErr = vvLow*parser.doubleValue("vvErr");
   printf("Di Boson in low MT = %f +- %f \n",VVLow, VVLowErr);
   double VVHigh = vvHigh;
   double VVHighErr = vvHigh*parser.doubleValue("vvErr");
   printf("Di Boson in high MT = %f +- %f \n",VVHigh, VVHighErr);

   printf("Other from MC\n");
   printf("---------------\n");

   double otherErr = vvLow*parser.doubleValue("othersErr");
   printf("Other fakes = %f +- %f \n",other, otherErr);

  

   printf("1.  W/TT from sideband");

   float osTopHigh = osHigh-VVHigh;
   float osTopHighErr = sqrt(osTopHigh+VVHighErr*VVHighErr);
   
   printf("OS W/TT in sideband  =%f -%f  = %f +- %f \n",osHigh,vvHigh,osTopHigh,osTopHighErr);


   printf("2. Extrapolate W in the low MT region\n");
   float osTopLow = osTopHigh*parser.doubleValue("topFactor");
   float osTopLowErr = sqrt(osTopHigh*osTopHigh*parser.doubleValue("topFactorErr")*parser.doubleValue("topFactorErr")+osTopHighErr*osTopHighErr*parser.doubleValue("topFactor")*parser.doubleValue("topFactor"));

   printf("OS TOP  in core  =%f *%f  = %f +- %f \n",osTopHigh,parser.doubleValue("topFactor"),osTopLow,osTopLowErr);


   float background = VVLow+other+osTopLow;
   float backgroundErr =sqrt( VVLowErr*VVLowErr+otherErr*otherErr+osTopLowErr*osTopLowErr);

   float diTau = osLow-background;
   float diTauErr = sqrt(osLow+backgroundErr*backgroundErr);
										     
   printf(" \n \n ");									     				     
   printf("Total & %.2f & %.2f & - & - \\\\ \n", osLow, osHigh);
   printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", VVLow, VVLowErr, VVHigh, VVHighErr);
   printf("QCD,Z+jets & %.2f $\\pm$ %.2f &  -  & - & - \\\\ \n", other, otherErr);
   printf("$t\\bar{t},W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", osTopLow, osTopLowErr, osTopHigh, osTopHighErr);
   printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,backgroundErr);
   printf("Total DiTau & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",diTau,diTauErr);

}

