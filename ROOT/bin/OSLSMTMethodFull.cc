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
  float dW;

  float WSS;
  float dWSS;

  float QCD;
  float dQCD;

  float ZLFT;
  float dZLFT;

  float ZJFT;
  float dZJFT;

  float TOP;
  float dTOP;

  float VV;
  float dVV;

  float ZTT;
  float dZTT;


};

BkgOutput extractSignal(optutl::CommandLineParser parser,std::string preselection);
BkgOutput extractBSignal(optutl::CommandLineParser parser,BkgOutput inclusive,std::string preselection);
std::pair<float,float> getYield(TTree * tree,std::string cut,std::string weight = "1",float additionalError =0.);
std::pair<float,float> scale(float n,float err, float factor,float factorErr);

int main (int argc, char* argv[]) 
{
  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------

   //Data
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   parser.addOption("preselection",optutl::CommandLineParser::kString,"preselection","");
   parser.addOption("osHighSelection",optutl::CommandLineParser::kString,"OS HIGH","muTauCharge==0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("osLowSelection",optutl::CommandLineParser::kString,"OS LOW ","muTauCharge==0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("ssHighSelection",optutl::CommandLineParser::kString,"SS HIGH ","muTauCharge!=0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("ssLowSelection",optutl::CommandLineParser::kString,"SS LOW ","muTauCharge!=0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0))");
   parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.06);
   parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.02);
   parser.addOption("wFactor",optutl::CommandLineParser::kDouble,"W factor",0.31);
   parser.addOption("wFactorErr",optutl::CommandLineParser::kDouble,"W factor error ",0.00);
   parser.addOption("topFile",optutl::CommandLineParser::kString,"File with the TTbar","TOP.root");
   parser.addOption("topErr",optutl::CommandLineParser::kDouble,"TTBar Relative Error",0.5);
   parser.addOption("vvFile",optutl::CommandLineParser::kString,"File with the Dibosons","VV.root");
   parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson RelativeError",0.5);   
   parser.addOption("zFile",optutl::CommandLineParser::kString,"File with the ZJETS","ZJETS.root");
   parser.addOption("zLFTSelection",optutl::CommandLineParser::kString,"ZLFT Selection","genTaus==0&&genPt2>0");
   parser.addOption("zJFTSelection",optutl::CommandLineParser::kString,"ZJFT Selection","genTaus==0&&genPt2==0.0");
   parser.addOption("zttFile",optutl::CommandLineParser::kString,"ZTTFile","ZTT.root");
   parser.addOption("zttErr",optutl::CommandLineParser::kDouble,"ZTTErr",0.12);
   parser.addOption("zLFTErr",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",0.5);
   parser.addOption("zJFTErr",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.5);
   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","muTauEventTree/eventTree");
   parser.addOption("weight",optutl::CommandLineParser::kString,"weight","223*__WEIGHT__");
   parser.addOption("bSelection",optutl::CommandLineParser::kString,"bSelection","(nJetsBTag3Pt20>0&&nJetsPt30<2)");
   parser.addOption("antibSelection",optutl::CommandLineParser::kString,"antibSelection","(nJetsBTag3Pt20==0)");
   parser.addOption("bFactor1",optutl::CommandLineParser::kDouble,"B factor 1 jet",0.00801);
   parser.addOption("bFactor2",optutl::CommandLineParser::kDouble,"B Factor 2jets",0.00801);
   parser.addOption("bFactorErr1",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.00035);
   parser.addOption("bFactorErr2",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.00035);

   parser.parseArguments (argc, argv);

   printf("################################################################################################\n");
   printf("################################     INCLUSIVE    ##############################################\n");
   printf("################################################################################################\n");
   printf("################################################################################################\n");

   BkgOutput outInclusive = extractSignal(parser,parser.stringValue("preselection"));

   printf("################################################################################################\n");
   printf("################################     EXCLUSIVE B   ##############################################\n");
   printf("################################################################################################\n");
   printf("################################################################################################\n");
   printf("Applying cut=%s \n",(parser.stringValue("preselection")+"&&("+parser.stringValue("antibSelection")+")").c_str());
   BkgOutput outExclusive = extractSignal(parser,parser.stringValue("preselection")+"&&("+parser.stringValue("antibSelection")+")");


   printf("################################################################################################\n");
   printf("################################      B TAGGED   ##############################################\n");
   printf("################################################################################################\n");
   printf("################################################################################################\n");
   printf("Applying cut=%s \n",(parser.stringValue("preselection")+"&&("+parser.stringValue("bSelection")+")").c_str());
   

   BkgOutput outB = extractBSignal(parser,outInclusive,parser.stringValue("preselection")+"&&"+parser.stringValue("bSelection"));


}


BkgOutput extractSignal(optutl::CommandLineParser parser,std::string preselection)
{

  printf("-------------CALCULATION------------\n");

  //get the DATA
   TFile *f = new TFile(parser.stringValue("dataFile").c_str());
   TTree *t =(TTree*) f->Get(parser.stringValue("treeName").c_str());
   //find the numbers you need from the data
   std::pair<float,float> osHigh = getYield(t,preselection+"&&"+parser.stringValue("osHighSelection"));
   std::pair<float,float> ssHigh = getYield(t,preselection+"&&"+parser.stringValue("ssHighSelection"));
   std::pair<float,float> osLow = getYield(t,preselection+"&&"+parser.stringValue("osLowSelection"));
   std::pair<float,float> ssLow = getYield(t,preselection+"&&"+parser.stringValue("ssLowSelection"));

   printf("total os high events = %f +- %f \n",osHigh.first,osHigh.second);
   printf("total ss high events = %f +- %f \n",ssHigh.first,ssHigh.second);
   printf("total os low events = %f +- %f \n",osLow.first,osLow.second);
   printf("total ss low events = %f +- %f \n",ssLow.first,ssLow.second);

   f->Close();

   //get the MC numbers for diboson
   TFile *fVV = new TFile(parser.stringValue("vvFile").c_str());
   TTree *tVV =(TTree*) fVV->Get(parser.stringValue("treeName").c_str());
   std::pair<float,float> vvHigh = getYield(tVV,preselection+"&&"+parser.stringValue("osHighSelection"),parser.stringValue("weight"),parser.doubleValue("vvErr"));
   std::pair<float,float> vvLow = getYield(tVV,preselection+"&&"+parser.stringValue("osLowSelection"),parser.stringValue("weight"),parser.doubleValue("vvErr"));
   printf("total diboson events in signal region = %f +- %f \n",vvLow.first,vvLow.second);
   printf("total diboson events in sideband region = %f +- %f \n",vvHigh.first,vvHigh.second);
   fVV->Close();

   //get the MC numbers for ttbar
   TFile *fTT = new TFile(parser.stringValue("topFile").c_str());
   TTree *tTT =(TTree*) fTT->Get(parser.stringValue("treeName").c_str());
   std::pair<float,float> topHigh = getYield(tTT,preselection+"&&"+parser.stringValue("osHighSelection"),parser.stringValue("weight"),parser.doubleValue("topErr"));
   std::pair<float,float> topLow = getYield(tTT,preselection+"&&"+parser.stringValue("osLowSelection"),parser.stringValue("weight"),parser.doubleValue("topErr"));
   printf("total ttbar events in signal region = %f +- %f \n",topLow.first,topLow.second);
   printf("total ttbar events in sideband region = %f +- %f \n",topHigh.first,topHigh.second);
   fTT->Close();


   //get the MC numbers for ZTT
   TFile *fZTT = new TFile(parser.stringValue("zttFile").c_str());
   TTree *tZTT =(TTree*) fZTT->Get(parser.stringValue("treeName").c_str());
   std::pair<float,float> zttLow = getYield(tZTT,preselection+"&&"+parser.stringValue("osLowSelection"),parser.stringValue("weight"),parser.doubleValue("zttErr"));
   printf("total ZTT events in signal region = %f +- %f \n",zttLow.first,zttLow.second);
   fZTT->Close();


   //get the MC numbers for z Jet fakes tau  
   TFile *fZ = new TFile(parser.stringValue("zFile").c_str());
   TTree *tZ =(TTree*) fZ->Get(parser.stringValue("treeName").c_str());
   std::pair<float,float> zLFT = getYield(tZ,preselection+"&&"+parser.stringValue("osLowSelection")+"&&"+parser.stringValue("zLFTSelection"),parser.stringValue("weight"),parser.doubleValue("zLFTErr"));
   std::pair<float,float> zLFTSS = getYield(tZ,preselection+"&&"+parser.stringValue("ssLowSelection")+"&&"+parser.stringValue("zLFTSelection"),parser.stringValue("weight"),parser.doubleValue("zLFTErr"));
   std::pair<float,float> zJFT = getYield(tZ,preselection+"&&"+parser.stringValue("osLowSelection")+"&&"+parser.stringValue("zJFTSelection"),parser.stringValue("weight"),parser.doubleValue("zJFTErr"));
   std::pair<float,float> zJFTSS = getYield(tZ,preselection+"&&"+parser.stringValue("ssLowSelection")+"&&"+parser.stringValue("zJFTSelection"),parser.stringValue("weight"),parser.doubleValue("zJFTErr"));
   printf("total Z (l->tau) events in signal region = %f +- %f \n",zLFT.first,zLFT.second);
   printf("total Z (j -> tau) events in signal region = %f +- %f \n",zJFT.first,zJFT.second);
   printf("total Z (l->tau) events in SS region = %f +- %f \n",zLFTSS.first,zLFTSS.second);
   printf("total Z (j -> tau) events in SS region = %f +- %f \n",zJFTSS.first,zJFTSS.second);

   fZ->Close();

  

   printf("1. Subtract TTbar and diboson from sideband");

   std::pair<float,float> osWHigh = std::make_pair(osHigh.first-topHigh.first-vvHigh.first,
						   sqrt(osHigh.second*osHigh.second+topHigh.second*topHigh.second+vvHigh.second*vvHigh.second));
   printf("OS W in sideband  =%f -%f -%f  = %f +- %f \n",osHigh.first,topHigh.first,vvHigh.first,osWHigh.first,osWHigh.second);

   printf("2. Extrapolate W in the low MT region\n");
   std::pair<float,float> osWLow = std::make_pair(osWHigh.first*parser.doubleValue("wFactor"),
						  sqrt(osWHigh.first*osWHigh.first*parser.doubleValue("wFactorErr")*parser.doubleValue("wFactorErr")+osWHigh.second*osWHigh.second*parser.doubleValue("wFactor")*parser.doubleValue("wFactor")));


   printf("OS W  in core  =%f *%f  = %f +- %f \n",osWHigh.first,parser.doubleValue("wFactor"),osWLow.first,osWLow.second);
      
   printf("3. Repeat for SS : first extrapolate W\n");
   std::pair<float,float> ssWLow = std::make_pair(ssHigh.first*parser.doubleValue("wFactor"),
						  sqrt(ssHigh.first*ssHigh.first*parser.doubleValue("wFactorErr")*parser.doubleValue("wFactorErr")+ssHigh.second*ssHigh.second*parser.doubleValue("wFactor")*parser.doubleValue("wFactor")));


   
   printf("4. From all SS events subtract W and Z jet fakes tau to get QCD ");
   std::pair<float,float> ssQCD = std::make_pair(ssLow.first-ssWLow.first-zJFTSS.first-zLFTSS.first,sqrt(ssLow.second*ssLow.second+ssWLow.second*ssWLow.second+zJFTSS.second*zJFTSS.second+zLFTSS.second*zLFTSS.second));
   printf("SS QCD in  core  =%f -%f -%f -%f = %f +- %f \n",ssLow.first,ssWLow.first,zJFTSS.first,zLFTSS.first,ssQCD.first,ssQCD.second);

   printf("5. Extrapolate SS QCD -> OS QCD ");
   std::pair<float,float> osQCD = std::make_pair(ssQCD.first*parser.doubleValue("qcdFactor"),sqrt(ssQCD.second*ssQCD.second*parser.doubleValue("qcdFactor")*parser.doubleValue("qcdFactor")+parser.doubleValue("qcdFactorErr")*parser.doubleValue("qcdFactorErr")*ssQCD.first*ssQCD.first));
   
   printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,parser.doubleValue("qcdFactor"),osQCD.first,osQCD.second);
   
   
   float background = osQCD.first+osWLow.first+topLow.first+vvLow.first+zLFT.first+zJFT.first+zttLow.first;
   float backgroundErr =sqrt( osQCD.second*osQCD.second+osWLow.second*osWLow.second+topLow.second*topLow.second+vvLow.second*vvLow.second+zLFT.second*zLFT.second+zJFT.second*zJFT.second+zttLow.second*zttLow.second);

   printf("BACKGROUND=%f +-%f \n",background,backgroundErr);
   printf("Di-TAU SIGNAL=%f +-%f \n",osLow.first-background,sqrt(osLow.second*osLow.second+backgroundErr*backgroundErr));


										     
   printf(" \n \n ");									     				     

  printf("-------------LATEX------------\n");


   printf("Total & %.2f & %.2f & %.2f & %.2f \\\\ \n", osLow.first, osHigh.first, ssLow.first, ssHigh.first);
   printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", vvLow.first, vvLow.second, vvHigh.first, vvHigh.second);
   printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", topLow.first, topLow.second, topHigh.first, topHigh.second);
   printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zJFT.first, zJFT.second, zJFTSS.first, zJFTSS.second);
   printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zLFT.first, zLFT.second,zLFTSS.first, zLFTSS.second);
   printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow.first, osWLow.second, osWHigh.first, osWHigh.second, ssWLow.first, ssWLow.second, ssHigh.first, ssHigh.second);
   printf("QCD & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
   printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zttLow.first, zttLow.second);
   printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,backgroundErr);

   //Save to output
   BkgOutput output;
   output.W = osWLow.first;
   output.dW = osWLow.second;
   output.WSS = ssWLow.first;
   output.dWSS = ssWLow.second;

   output.QCD = osQCD.first;
   output.dQCD = osQCD.second;
   output.ZLFT = zLFT.first;
   output.dZLFT = zLFT.second;
   output.ZJFT = zJFT.first;
   output.dZJFT = zJFT.second;
   output.TOP = topLow.first;
   output.dTOP = topLow.second;
   output.VV = vvLow.first;
   output.dVV = vvLow.second;
   output.ZTT = zttLow.first;
   output.dZTT = zttLow.second;



  printf("-------------ROOSTATS------------\n");
  float gQCD = osQCD.first*osQCD.first/(osQCD.second*osQCD.second);
  printf("QCD (Gamma function) = %f , %f \n",gQCD,osQCD.first/gQCD);

  float gW = osWLow.first*osWLow.first/(osWLow.second*osWLow.second);
  printf("W (Gamma function) = %f , %f \n",gW,osWLow.first/gW);

  printf("-------------L&S------------\n");
  printf("ZTT = %f +- %f percent\n",output.ZTT,output.dZTT/output.ZTT); 
  printf("QCD = %f +- %f percent\n",output.QCD,output.dQCD/output.QCD); 
  printf("W = %f +- %f percent\n",output.W,output.dW/output.W); 
  printf("ZLFT = %f +- %f percent\n",output.ZLFT,output.dZLFT/output.ZLFT); 
  printf("ZJFT = %f +- %f percent\n",output.ZJFT,output.dZJFT/output.ZJFT); 
  printf("TOP = %f +- %f percent\n",output.TOP,output.dTOP/output.TOP); 
  printf("VV = %f +- %f percent\n",output.VV,output.dVV/output.VV); 



   return output;
}

BkgOutput extractBSignal(optutl::CommandLineParser parser,BkgOutput inclusive,std::string preselection)
{

  printf("-------------CALCULATION------------\n");

  //get the DATA
   TFile *f = new TFile(parser.stringValue("dataFile").c_str());
   TTree *t =(TTree*) f->Get(parser.stringValue("treeName").c_str());
   //find the numbers you need from the data
   std::pair<float,float> osLow = getYield(t,preselection+"&&"+parser.stringValue("osLowSelection"));
   std::pair<float,float> ssLow = getYield(t,preselection+"&&"+parser.stringValue("ssLowSelection"));

   printf("total os low events = %f +- %f \n",osLow.first,osLow.second);
   printf("total ss low events = %f +- %f \n",ssLow.first,ssLow.second);

   f->Close();

   //get the MC numbers for diboson
   TFile *fVV = new TFile(parser.stringValue("vvFile").c_str());
   TTree *tVV =(TTree*) fVV->Get(parser.stringValue("treeName").c_str());
   std::pair<float,float> vvLow = getYield(tVV,preselection+"&&"+parser.stringValue("osLowSelection"),parser.stringValue("weight"),parser.doubleValue("vvErr"));
   printf("total diboson events in signal region = %f +- %f \n",vvLow.first,vvLow.second);
   fVV->Close();

   //get the MC numbers for ttbar
   TFile *fTT = new TFile(parser.stringValue("topFile").c_str());
   TTree *tTT =(TTree*) fTT->Get(parser.stringValue("treeName").c_str());
   std::pair<float,float> topLow = getYield(tTT,preselection+"&&"+parser.stringValue("osLowSelection"),parser.stringValue("weight"),parser.doubleValue("topErr"));
   std::pair<float,float> topSSLow = getYield(tTT,preselection+"&&"+parser.stringValue("ssLowSelection"),parser.stringValue("weight"),parser.doubleValue("topErr"));
   printf("total ttbar events in signal OSregion = %f +- %f \n",topLow.first,topLow.second);
   printf("total ttbar events in signal SS region = %f +- %f \n",topSSLow.first,topSSLow.second);
   fTT->Close();

   //get the scaled numbers for W and Z+jets
   std::pair<float,float> osWLow = scale(inclusive.W,inclusive.dW,parser.doubleValue("bFactor2"),parser.doubleValue("bFactorErr2"));
   printf("total W events in OS region = %f +- %f \n",osWLow.first,osWLow.second);

   std::pair<float,float> ssWLow = scale(inclusive.WSS,inclusive.dWSS,parser.doubleValue("bFactor2"),parser.doubleValue("bFactorErr2"));
   printf("total W events in SS region = %f +- %f \n",ssWLow.first,ssWLow.second);


   std::pair<float,float> zLFT = scale(inclusive.ZLFT,inclusive.dZLFT,parser.doubleValue("bFactor1"),parser.doubleValue("bFactorErr1"));
   printf("total Z(l->tau) events in OS region = %f +- %f \n",zLFT.first,zLFT.second);

   std::pair<float,float> zJFT = scale(inclusive.ZJFT,inclusive.dZJFT,parser.doubleValue("bFactor2"),parser.doubleValue("bFactorErr1"));
   printf("total Z(jet->tau) events in OS region = %f +- %f \n",zJFT.first,zJFT.second);


   std::pair<float,float> zTT = scale(inclusive.ZTT,inclusive.dZTT,parser.doubleValue("bFactor1"),parser.doubleValue("bFactorErr1"));
   printf("total Z->tau tau events in OS region = %f +- %f \n",zTT.first,zTT.second);

   
   printf("1. From all SS events subtract W and Z jet fakesand TTBat  to get QCD ");
   std::pair<float,float> ssQCD = std::make_pair(ssLow.first-ssWLow.first-zJFT.first-topSSLow.first,sqrt(ssLow.second*ssLow.second+ssWLow.second*ssWLow.second+zJFT.second*zJFT.second+topSSLow.second*topSSLow.second));
   printf("SS QCD in  core  =%f -%f -%f -%f = %f +- %f \n",ssLow.first,ssWLow.first,zJFT.first,topSSLow.first,ssQCD.first,ssQCD.second);

   printf("2. Extrapolate SS QCD -> OS QCD ");
   std::pair<float,float> osQCD = std::make_pair(ssQCD.first*parser.doubleValue("qcdFactor"),sqrt(ssQCD.second*ssQCD.second*parser.doubleValue("qcdFactor")*parser.doubleValue("qcdFactor")+parser.doubleValue("qcdFactorErr")*parser.doubleValue("qcdFactorErr")*ssQCD.first*ssQCD.first));
   
   printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,parser.doubleValue("qcdFactor"),osQCD.first,osQCD.second);
   
   
   float background = osQCD.first+osWLow.first+topLow.first+vvLow.first+zLFT.first+zJFT.first+zTT.first;
   float backgroundErr =sqrt( osQCD.second*osQCD.second+osWLow.second*osWLow.second+topLow.second*topLow.second+vvLow.second*vvLow.second+zLFT.second*zLFT.second+zJFT.second*zJFT.second+zTT.second*zTT.second);

   printf("BACKGROUND=%f +-%f \n",background,backgroundErr);
   printf("Di-TAU SIGNAL=%f +-%f \n",osLow.first-background,sqrt(osLow.second*osLow.second+backgroundErr*backgroundErr));


										     
   printf(" \n \n ");									     				     

  printf("-------------LATEX------------\n");


  printf("Total & %.2f & %.2f \\\\ \n", osLow.first,ssLow.first);
   printf("Di-Boson & %.2f $\\pm$ %.2f &  \\\\ \n", vvLow.first, vvLow.second);
   printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", topLow.first, topLow.second, topSSLow.first, topSSLow.second);
   printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f  \\\\ \n", zJFT.first, zJFT.second, zJFT.first, zJFT.second);
   printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & -  \\\\ \n", zLFT.first, zLFT.second);
   printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow.first, osWLow.second,  ssWLow.first, ssWLow.second);
   printf("QCD & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
   printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & -  \\\\ \n", zTT.first, zTT.second);
   printf("Total Background & %.2f $\\pm$ %.2f & - \\\\ \n",background,backgroundErr);

   //Save to output
   BkgOutput output;
   output.W = osWLow.first;
   output.dW = osWLow.second;
   output.WSS = osWLow.first;
   output.dWSS = osWLow.second;
   output.QCD = osQCD.first;
   output.dQCD = osQCD.second;
   output.ZLFT = zLFT.first;
   output.dZLFT = zLFT.second;
   output.ZJFT = zJFT.first;
   output.dZJFT = zJFT.second;
   output.TOP = topLow.first;
   output.dTOP = topLow.second;
   output.VV = vvLow.first;
   output.dVV = vvLow.second;
   output.ZTT = zTT.first;
   output.dZTT = zTT.second;



  printf("-------------ROOSTATS------------\n");
  float gQCD = osQCD.first*osQCD.first/(osQCD.second*osQCD.second);
  printf("QCD (Gamma function) = %f , %f \n",gQCD,osQCD.first/gQCD);

  float gW = osWLow.first*osWLow.first/(osWLow.second*osWLow.second);
  printf("W (Gamma function) = %f , %f \n",gW,osWLow.first/gW);

  float gZLFT = zLFT.first*zLFT.first/(zLFT.second*zLFT.second);
  printf("ZLFT (Gamma function) = %f , %f \n",gZLFT,zLFT.first/gZLFT);

  float gZJFT = zJFT.first*zJFT.first/(zJFT.second*zJFT.second);
  printf("ZJFT (Gamma function) = %f , %f \n",gZJFT,zJFT.first/gZJFT);

  printf("-------------L&S------------\n");
  printf("ZTT = %f +- %f percent\n",output.ZTT,output.dZTT/output.ZTT); 
  printf("QCD = %f +- %f percent\n",output.QCD,output.dQCD/output.QCD); 
  printf("W = %f +- %f percent\n",output.W,output.dW/output.W); 
  printf("ZLFT = %f +- %f percent\n",output.ZLFT,output.dZLFT/output.ZLFT); 
  printf("ZJFT = %f +- %f percent\n",output.ZJFT,output.dZJFT/output.ZJFT); 
  printf("TOP = %f +- %f percent\n",output.TOP,output.dTOP/output.TOP); 
  printf("VV = %f +- %f percent\n",output.VV,output.dVV/output.VV); 



   return output;
}




std::pair<float,float> getYield(TTree *t,std::string cut,std::string weight , float additionalError) {
  TH1F *hh = new TH1F("hh","h",1,1.,2.);
  hh->Sumw2();
  t->Draw("1>>hh",(weight+"*("+cut+")").c_str());
  float yield = hh->GetBinContent(1);
  float yieldErr = hh->GetBinError(1);

  float addErr = yield*additionalError;
  yieldErr = sqrt(yieldErr*yieldErr+addErr*addErr);
  delete hh;
  return std::make_pair(yield,yieldErr);
}

std::pair<float,float> scale(float n,float err, float factor,float factorErr) {
  float val = n*factor;
  float valErr = sqrt(n*n*factorErr*factorErr+err*err*factor*factor);

  return std::make_pair(val,valErr);
}
