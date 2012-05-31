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


struct BkgOutput {
  float W;
  float WErr;

  float TOP;
  float TOPErr;

  float QCD;
  float QCDErr;

  float ZMFT;
  float ZMFTErr;

  float ZJFT;
  float ZJFTErr;
  
  float VV;
  float VVErr;


};

BkgOutput extractSignal(float osHigh,float osLow,float sHigh,float ssLow,float zmft,float zjft,float ttbarHigh,float ttbarLow,float vvHigh,float vvLow,optutl::CommandLineParser parser);

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
   parser.addOption("ssHighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("ssLowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.06);
   parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.02);
   parser.addOption("wFactor",optutl::CommandLineParser::kDouble,"W factor",0.31);
   parser.addOption("wFactorErr",optutl::CommandLineParser::kDouble,"W factor error ",0.00);
   parser.addOption("ttbarLow",optutl::CommandLineParser::kDouble,"TTBar From MC Low",6.);
   parser.addOption("ttbarHigh",optutl::CommandLineParser::kDouble,"TTBar From MC High",15.);
   parser.addOption("ttbarErr",optutl::CommandLineParser::kDouble,"TTBar Relative Error",0.5);
   parser.addOption("vvLow",optutl::CommandLineParser::kDouble,"DiBoson From MC Low",1.6);
   parser.addOption("vvHigh",optutl::CommandLineParser::kDouble,"DiBoson From MC High",3.0);
   parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson RelativeError",0.5);   
   parser.addOption("zMFT",optutl::CommandLineParser::kDouble,"Z Muon fakes tau",0.5);
   parser.addOption("zMFTErr",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",0.5);
   parser.addOption("zJFT",optutl::CommandLineParser::kDouble,"Z Jet Fakes tau",0.5);
   parser.addOption("zJFTErr",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.5);
   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","muTauEventTree/eventTree");
   parser.parseArguments (argc, argv);


   //translate the parser selections 
   std::string preselection    = parser.stringValue("preselection");
   std::string oshighSelection = preselection+"&&"+parser.stringValue("osHighSelection");
   std::string oslowSelection  = preselection+"&&"+parser.stringValue("osLowSelection");
   std::string sshighSelection = preselection+"&&"+parser.stringValue("ssHighSelection");
   std::string sslowSelection  = preselection+"&&"+parser.stringValue("ssLowSelection");

   //Get file and tree
   TFile *f = new TFile(parser.stringValue("dataFile").c_str());
   TTree *t =(TTree*) f->Get(parser.stringValue("treeName").c_str());
   
   //calculate events in the regions

   float osHigh = t->GetEntries( oshighSelection.c_str());
   float osLow = t->GetEntries( oslowSelection.c_str());
   float ssHigh = t->GetEntries( sshighSelection.c_str());
   float ssLow = t->GetEntries( sslowSelection.c_str());
   float zmft = parser.doubleValue("zMFT");
   float zjft = parser.doubleValue("zJFT");
   float ttbarHigh = parser.doubleValue("ttbarHigh");
   float ttbarLow = parser.doubleValue("ttbarLow");
   float vvHigh = parser.doubleValue("vvHigh");
   float vvLow = parser.doubleValue("vvLow");
   
   BkgOutput out = extractSignal(osHigh,osLow,ssHigh, ssLow, zmft,zjft, ttbarHigh,ttbarLow, vvHigh, vvLow,parser);

}


BkgOutput extractSignal(float osHigh,float osLow,float ssHigh,float ssLow,float zmft,float zjft,float ttbarHigh,float ttbarLow,float vvHigh,float vvLow,optutl::CommandLineParser parser)
{

  BkgOutput output;


  printf("total os high events = %f\n",osHigh);
  printf("total ss high events = %f\n",ssHigh);

  printf("total os low events = %f\n",osLow);
  printf("total ss low events = %f\n",ssLow);


   printf("Diboson from MC\n");
   printf("---------------\n");
   double VVLow = vvLow;
   double VVLowErr = vvLow*parser.doubleValue("vvErr");
   printf("Di Boson in low MT = %f +- %f \n",VVLow, VVLowErr);
   output.VV = VVLow;
   output.VVErr = VVLowErr;
   double VVHigh = vvHigh;
   double VVHighErr = vvHigh*parser.doubleValue("vvErr");
   printf("Di Boson in high MT = %f +- %f \n",VVHigh, VVHighErr);

   printf("TTbar from MC\n");
   printf("-------------\n");
   double topLow = ttbarLow;
   double topLowErr = ttbarLow*parser.doubleValue("ttbarErr");
   printf("Top in low MT = %f +- %f \n",topLow, topLowErr);
   output.TOP = topLow;
   output.TOPErr = topLowErr;
   double topHigh = ttbarHigh;
   double topHighErr = ttbarHigh*parser.doubleValue("ttbarErr");
   printf("Top in High MT = %f +- %f \n",topHigh, topHighErr);

   printf("Z l fakes tau  from MC\n");
   printf("----------------------\n");
   double zmftErr = zmft*parser.doubleValue("zMFTErr");
   printf("Z lepton fakes tau = %f +- %f \n",zmft, zmftErr);
   output.ZMFT = zmft;
   output.ZMFTErr = zmftErr;

   printf("Z jet fakes tau  from MC\n");
   printf("----------------------\n");
   double zjftErr = zjft*parser.doubleValue("zJFTErr");
   printf("Z jet fakes tau = %f +- %f \n",zjft, zjftErr);
   output.ZJFT = zjft;
   output.ZJFTErr = zjftErr;
  

   printf("1. Subtract TTbar and VV from sideband");

   float osWHigh = osHigh-topHigh-VVHigh;
   float osWHighErr = sqrt(osWHigh+topHighErr*topHighErr+VVHighErr*VVHighErr);
   
   printf("OS W in sideband  =%f -%f  = %f +- %f \n",osHigh,topHigh,osWHigh,osWHighErr);

   printf("2. Extrapolate W in the low MT region\n");
   float osWLow = osWHigh*parser.doubleValue("wFactor");
   float osWLowErr = sqrt(osWHigh*osWHigh*parser.doubleValue("wFactorErr")*parser.doubleValue("wFactorErr")+osWHighErr*osWHighErr*parser.doubleValue("wFactor")*parser.doubleValue("wFactor"));
   output.W = osWLow;
   output.WErr = osWLowErr;

   printf("OS W  in core  =%f *%f  = %f +- %f \n",osWHigh,parser.doubleValue("wFactor"),osWLow,osWLowErr);
      
   printf("3. Repeat for SS : first extrapolate W\n");
   float ssWLow = ssHigh*parser.doubleValue("wFactor");
   float ssWLowErr = sqrt(ssHigh*ssHigh*parser.doubleValue("wFactorErr")*parser.doubleValue("wFactorErr")+ssHigh*parser.doubleValue("wFactor")*parser.doubleValue("wFactor"));
   printf("SS W  in core  =%f *%f  = %f +- %f \n",ssHigh,parser.doubleValue("wFactor"),ssWLow,ssWLowErr);


   
   printf("4. From all SS events subtract W and Z jet fakes tau to get QCD ");
   float ssQCDLow = ssLow-ssWLow-zjft;
   float ssQCDLowErr = sqrt(ssLow+ssWLowErr*ssWLowErr+zjftErr*zjftErr);
   printf("SS QCD in  core  =%f -%f -%f  = %f +- %f \n",ssLow,ssWLow,zjft,ssQCDLow,ssQCDLowErr);


   printf("7. Extrapolate OS QCD ");
   float osQCDLow = ssQCDLow*parser.doubleValue("qcdFactor");
   float osQCDLowErr = sqrt(ssQCDLowErr*ssQCDLowErr*parser.doubleValue("qcdFactor")*parser.doubleValue("qcdFactor")+parser.doubleValue("qcdFactorErr")*parser.doubleValue("qcdFactorErr")*ssQCDLow*ssQCDLow);
   output.QCD = osQCDLow;
   output.QCDErr = osQCDLowErr;

   printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCDLow,parser.doubleValue("qcdFactor"),osQCDLow,osQCDLowErr);


   float background = osQCDLow+osWLow+ttbarLow+VVLow+zmft+zjft;
   float backgroundErr= sqrt(osQCDLowErr*osQCDLowErr+
			      osWLowErr*osWLowErr+
			      topLowErr*topLowErr+
			      VVLowErr*VVLowErr+
			      zmftErr*zmftErr+
			      zjftErr*zjftErr);



   printf("BACKGROUND=%f +-%f \n",background,backgroundErr);

   printf("Di-TAU SIGNAL=%f +-%f \n",osLow-background,sqrt(osLow+backgroundErr*backgroundErr));

										     
   printf(" \n \n ");									     				     
   printf("Total & %.2f & %.2f & %.2f & %.2f \\\\ \n", osLow, osHigh, ssLow, ssHigh);
   printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", VVLow, VVLowErr, VVHigh, VVHighErr);
   printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", topLow, topLowErr, topHigh, topHighErr);
   printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zjft, zjftErr, zjft, zjftErr);
   printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zmft, zmftErr);
   printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow, osWLowErr, osWHigh, osWHighErr, ssWLow, ssWLowErr, ssHigh, sqrt(ssHigh));
   printf("QCD & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osQCDLow, osQCDLowErr, ssQCDLow, ssQCDLowErr);
   printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,backgroundErr);

   return output;
}

