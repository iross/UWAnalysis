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
  float WEN;
  float WENErr;

  float TOP;
  float TOPErr;

  float WTN;
  float WTNErr;

  float QCD;
  float QCDErr;

  float ZEFT;
  float ZEFTErr;

  float ZJFT;
  float ZJFTErr;
  
  float VV;
  float VVErr;

};

BkgOutput extractSignal(float osHigh,float osLow,float sHigh,float ssLow,float zeft,float zjft,float ttbarHigh,float ttbarLow,float vvHigh,float vvLow,optutl::CommandLineParser parser);
float poissonFluctuation(Long_t N);

//float getFluctuatedEvents(TTree*,std:string selection);

int main (int argc, char* argv[]) 
{
  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------

   //Data
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   //   parser.addOption("preselection",optutl::CommandLineParser::kString,"lepton veto cuts ","HLT_Any&&abs(eleTauEta1)<2.1&&eleTauPt1>15&&eleTauPt2>20&&eleTauMissHits==0&&eleTauChargeIso==0&&eleTauGammaIso==0&&eleTauNeutralIso==0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&!(abs(eleTauConvDist)<0.1&&abs(eleTauDCotTheta)<0.05)");
   //   parser.addOption("preselection",optutl::CommandLineParser::kString,"lepton veto cuts ","HLT_Any&&abs(eleTauEta1)<2.1&&eleTauPt1>15&&eleTauPt2>20&&eleTauMissHits==0&&((eleTauRelIso04B<0.07&&abs(eleTauEta1)<1.44)||(eleTauRelIso04E<0.06&&abs(eleTauEta1)>1.44))&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&!(abs(eleTauConvDist)<0.1&&abs(eleTauDCotTheta)<0.05)");
   parser.addOption("preselection",optutl::CommandLineParser::kString,"lepton veto cuts ","HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&abs(eleTauEleIP)<0.02&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&eleTauMissHitsWW==0&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.442)");

   parser.addOption("oshighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","eleTauCharge==0&&eleTauMt1>60&&eleTauLeadCandMVA<-0.1&&dieleSize==0&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))");
   parser.addOption("oslowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","eleTauCharge==0&&eleTauMt1<40&&eleTauLeadCandMVA<-0.1&&dieleSize==0&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))");
   parser.addOption("sshighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","eleTauCharge!=0&&eleTauMt1>60&&eleTauLeadCandMVA<-0.1&&dieleSize==0&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))");
   parser.addOption("sslowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","eleTauCharge!=0&&eleTauMt1<40&&eleTauLeadCandMVA<-0.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))");
   parser.addOption("zeftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","eleTauCharge==0&&eleTauMt1<40&&dieleSize==1&&eleTauLeadCandMVA>-0.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass>0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP>0.08))");
   parser.addOption("zjftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","eleTauCharge!=0&&eleTauMt1<40&&eleTauLeadCandMVA<-0.1&&dieleSize==1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))");
   parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcd OSLS Ratio",1.08);
   parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcd OSLS Ratio Error",0.13);
   parser.addOption("wenFactor",optutl::CommandLineParser::kDouble,"WEN factor",0.28);
   parser.addOption("wenFactorErr",optutl::CommandLineParser::kDouble,"WEN Factor Error",0.0);
   parser.addOption("wtnFactor",optutl::CommandLineParser::kDouble,"WTN Factor",0.23);
   parser.addOption("wtnFactorErr",optutl::CommandLineParser::kDouble,"WTN Factor Error",0.0);
   parser.addOption("ttbarMCLow",optutl::CommandLineParser::kDouble,"TTBar From MC Low",2.6);
   parser.addOption("ttbarMCHigh",optutl::CommandLineParser::kDouble,"TTBar From MC High",7.4);
   parser.addOption("ttbarErr",optutl::CommandLineParser::kDouble,"TTBar Error(percent)",0.5);
   parser.addOption("vvMCLow",optutl::CommandLineParser::kDouble,"DiBoson From MC Low",0.8);
   parser.addOption("vvMCHigh",optutl::CommandLineParser::kDouble,"DiBoson From MC High",1.3);
   parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson Error(percent)",0.5);
   parser.addOption("zeftFactor",optutl::CommandLineParser::kDouble,"ZEEFactor1",0.017);
   parser.addOption("zeftFactorErr",optutl::CommandLineParser::kDouble,"ZEEFactor1",0.004);
   parser.addOption("zjftFactor",optutl::CommandLineParser::kDouble,"ZEEFactor2",2.5);
   parser.addOption("zjftFactorErr",optutl::CommandLineParser::kDouble,"ZEEFactor2",0.13);
   parser.addOption("energyScale",optutl::CommandLineParser::kDouble,"energy Scale",0.98);
   parser.addOption("energyScaleErr",optutl::CommandLineParser::kDouble,"energy scale error ",0.02);
   parser.addOption("experiments",optutl::CommandLineParser::kInteger,"experiments ",0);

   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","eleTauEventTree/eventTree");


   parser.parseArguments (argc, argv);


   //translate the parser selections 
   std::string preselection    = parser.stringValue("preselection");
   std::string oshighSelection = preselection+"&&"+parser.stringValue("oshighSelection");
   std::string oslowSelection  = preselection+"&&"+parser.stringValue("oslowSelection");
   std::string sshighSelection = preselection+"&&"+parser.stringValue("sshighSelection");
   std::string sslowSelection  = preselection+"&&"+parser.stringValue("sslowSelection");
   std::string zeftSelection   = preselection+"&&"+parser.stringValue("zeftSelection");
   std::string zjftSelection   = preselection+"&&"+parser.stringValue("zjftSelection");
   //std::string ttbarSelection  = preselection+"&&"+parser.stringValue("ttbarSelection");



   //Get file and tree
   TFile *f = new TFile(parser.stringValue("dataFile").c_str());
   TTree *t =(TTree*) f->Get(parser.stringValue("treeName").c_str());
   
   //calculate events in the regions

   float osHigh = t->GetEntries( oshighSelection.c_str());
   float osLow = t->GetEntries( oslowSelection.c_str());
   float ssHigh = t->GetEntries( sshighSelection.c_str());
   float ssLow = t->GetEntries( sslowSelection.c_str());
   float zeft = t->GetEntries( zeftSelection.c_str());
   float zjft = t->GetEntries( zjftSelection.c_str());
   //float ttbarHigh = t->GetEntries( (ttbarSelection+"&&"+oshighSelection).c_str());
   //float ttbarLow = t->GetEntries( (ttbarSelection+"&&"+oslowSelection).c_str());
   float ttbarHigh = parser.doubleValue("ttbarMCHigh");
   float ttbarLow = parser.doubleValue("ttbarMCLow");
   float vvHigh = parser.doubleValue("vvMCHigh");
   float vvLow = parser.doubleValue("vvMCLow");



   //create results tree
   TFile *fout = new TFile("results.root","RECREATE");
   TTree *results = new TTree("results","Results tree");
   float wenExpected=0;
   float wenExtracted=0;

   float wtnExpected=0;
   float wtnExtracted=0;

   float ttbarExpected=0;
   float ttbarExtracted=0;

   float qcdExpected=0;
   float qcdExtracted=0;

   float zeftExpected=0;
   float zeftExtracted=0;

   float zjftExpected=0;
   float zjftExtracted=0;

   results->Branch("wenExp",&wenExpected,"wenExp/F");
   results->Branch("wenExt",&wenExtracted,"wenExt/F");
   results->Branch("wenExp",&wtnExpected,"wtnExp/F");
   results->Branch("wenExt",&wtnExtracted,"wtnExt/F");
   results->Branch("ttbarExp",&ttbarExpected,"ttbarExp/F");
   results->Branch("ttbarExt",&ttbarExtracted,"ttbarExt/F");
   results->Branch("qcdExp",&qcdExpected,"qcdExp/F");
   results->Branch("qcdExt",&qcdExtracted,"qcdExt/F");
   results->Branch("zeftExp",&zeftExpected,"zeftExp/F");
   results->Branch("zeftExt",&zeftExtracted,"zeftExt/F");
   results->Branch("zjftExp",&zjftExpected,"zjftExp/F");
   results->Branch("zjftExt",&zjftExtracted,"zjftExt/F");

//   int nexperiments = parser.integerValue("experiments");
   
   BkgOutput out = extractSignal( osHigh, osLow, ssHigh, ssLow, zeft, zjft, ttbarHigh, ttbarLow, vvHigh, vvLow,parser);



   fout->Close();
}


BkgOutput extractSignal(float osHigh,float osLow,float ssHigh,float ssLow,float zeft,float zjft,float ttbarHigh,float ttbarLow,float vvHigh,float vvLow,optutl::CommandLineParser parser)
{

  BkgOutput output;

  printf("total os high events = %f\n",osHigh);
  printf("total ss high events = %f\n",ssHigh);

  printf("total os low events = %f\n",osLow);
  printf("total ss low events = %f\n",ssLow);
  
   printf("VV from MC\n");
   double VVLow = vvLow;
   double VVLowErr = vvLow*parser.doubleValue("vvErr");
   printf("OS signal MT< = %f +- %f \n",VVLow, VVLowErr);
   output.VV = VVLow;
   output.VVErr = VVLowErr;


   double VVHigh = vvHigh;
   double VVHighErr = vvHigh*parser.doubleValue("vvErr");
   printf("OS signal MT> = %f +- %f \n",VVHigh, VVHighErr);



   //extrapolate TTbar events in MT>40
//    printf("Extrapolating TTbar background\n");
//    printf("control region Mt > =%f\n",ttbarHigh);
//    printf("control region Mt < =%f\n",ttbarLow);

   //double topLow = ttbarLow*parser.doubleValue("ttbarFactor");
   printf("TTbar from MC\n");
   double topLow = ttbarLow;
   double topLowErr = ttbarLow*parser.doubleValue("ttbarErr");
   printf("OS signal MT< = %f +- %f \n",topLow, topLowErr);
   output.TOP = topLow;
   output.TOPErr = topLowErr;


   double topHigh = ttbarHigh;
   double topHighErr = ttbarHigh*parser.doubleValue("ttbarErr");
   printf("OS signal MT> = %f +- %f \n",topHigh, topHighErr);


   printf("Extrapolating Z , electron fakes tau  background\n");
   printf("control region = %f \n",zeft);
   double zeftLow = zeft*parser.doubleValue("zeftFactor");
   double zeftLowErr = sqrt(zeft*parser.doubleValue("zeftFactor")*parser.doubleValue("zeftFactor")+ zeft*zeft*parser.doubleValue("zeftFactorErr")*parser.doubleValue("zeftFactorErr"));
   printf(" signal region %f*%f = %f +- %f \n",zeft,parser.doubleValue("zeftFactor"),zeftLow, zeftLowErr);
   output.ZEFT = zeftLow;
   output.ZEFTErr = zeftLowErr;

   printf("Extrapolating Z , jet fakes tau  background\n");
   printf("control region =%f\n",zjft);
   double zjftLow = zjft*parser.doubleValue("zjftFactor");
   double zjftLowErr = sqrt(zjft*parser.doubleValue("zjftFactor")*parser.doubleValue("zjftFactor")+ zjft*zjft*parser.doubleValue("zjftFactorErr")*parser.doubleValue("zjftFactorErr"));
   printf(" signal region = %f +- %f \n",zjftLow, zjftLowErr);
   output.ZJFT = zjftLow;
   output.ZJFTErr = zjftLowErr;
   
   printf("1. Subtract TTbar and VV from sideband");

   float osWHigh = osHigh-topHigh-VVHigh;
   float osWHighErr = sqrt(osWHigh+topHighErr*topHighErr+VVHighErr*VVHighErr);
   
   printf("OS W in sideband  =%f -%f  = %f +- %f \n",osHigh,topHigh,osWHigh,osWHighErr);

   printf("2. Extrapolate W in the low MT region\n");
   float osWLow = osWHigh*parser.doubleValue("wenFactor");
   float osWLowErr = sqrt(osWHigh*osWHigh*parser.doubleValue("wenFactorErr")*parser.doubleValue("wenFactorErr")+osWHighErr*osWHighErr*parser.doubleValue("wenFactor")*parser.doubleValue("wenFactor"));
   output.WEN = osWLow;
   output.WENErr = osWLowErr;

   printf("OS W e nu in core  =%f *%f  = %f +- %f \n",osWHigh,parser.doubleValue("wenFactor"),osWLow,osWLowErr);
   
   printf("3. Extrapolate W ->tau nu from W -> munu using MC \n");
   float osWTLow = osWLow*parser.doubleValue("wtnFactor");
   float osWTLowErr = sqrt(osWLowErr*osWLowErr*parser.doubleValue("wtnFactor")*parser.doubleValue("wtnFactor")+osWLow*osWLow*parser.doubleValue("wtnFactorErr")*parser.doubleValue("wtnFactorErr"));
   printf("OS W tau nu in core  =%f *%f  = %f +- %f \n",osWLow,parser.doubleValue("wtnFactor"),osWTLow,osWTLowErr);
   output.WTN = osWTLow;
   output.WTNErr = osWTLowErr;
   
   
   printf("4. Repeat for SS : first extrapolate W\n");
   float ssWLow = ssHigh*parser.doubleValue("wenFactor");
   float ssWLowErr = sqrt(ssHigh*ssHigh*parser.doubleValue("wenFactorErr")*parser.doubleValue("wenFactorErr")+ssHigh*parser.doubleValue("wenFactor")*parser.doubleValue("wenFactor"));
   printf("SS W e nu in core  =%f *%f  = %f +- %f \n",ssHigh,parser.doubleValue("wenFactor"),ssWLow,ssWLowErr);

   printf("5. Extrapolate W ->tau nu from W -> munu using MC \n");
   float ssWTLow = ssWLow*parser.doubleValue("wtnFactor");
   float ssWTLowErr = sqrt(ssWLowErr*ssWLowErr*parser.doubleValue("wtnFactor")*parser.doubleValue("wtnFactor")+ssWLow*ssWLow*parser.doubleValue("wtnFactorErr")*parser.doubleValue("wtnFactorErr"));
   printf("SS W tau nu in core  =%f *%f  = %f +- %f \n",ssWLow,parser.doubleValue("wtnFactor"),ssWTLow,ssWTLowErr);

   
   printf("6. From all SS events subtract W and Z jet fakes tau to get QCD ");
   float ssQCDLow = ssLow-ssWLow-ssWTLow-zjftLow;
   float ssQCDLowErr = sqrt(ssLow+ssWLowErr*ssWLowErr+ssWTLowErr*ssWTLowErr+zjftLowErr*zjftLowErr);
   printf("SS QCD in  core  =%f -%f -%f -%f  = %f +- %f \n",ssLow,ssWLow,ssWTLow,zjftLow,ssQCDLow,ssQCDLowErr);


   printf("7. Extrapolate OS QCD ");
   float osQCDLow = ssQCDLow*parser.doubleValue("qcdFactor");
   float osQCDLowErr = sqrt(ssQCDLowErr*ssQCDLowErr*parser.doubleValue("qcdFactor")*parser.doubleValue("qcdFactor")+parser.doubleValue("qcdFactorErr")*parser.doubleValue("qcdFactorErr")*ssQCDLow*ssQCDLow);
   output.QCD = osQCDLow;
   output.QCDErr = osQCDLowErr;

   printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCDLow,parser.doubleValue("qcdFactor"),osQCDLow,osQCDLowErr);

   printf("BACKGROUND=%f +-%f \n",osQCDLow+osWLow+osWTLow+ttbarLow+VVLow+zeftLow+zjftLow,sqrt(osQCDLowErr*osQCDLowErr+
                                                                                     osWLowErr*osWLowErr+
                                                                                     osWTLowErr*osWTLowErr+
                                                                                     topLowErr*topLowErr+
                                                                                     VVLowErr*VVLowErr+
                                                                                     zeftLowErr*zeftLowErr+
											      zjftLowErr*zjftLowErr));


   
   printf("Z=%f +-%f \n",osLow-osQCDLow-osWLow-osWTLow-ttbarLow-VVLow-zeftLow-zjftLow,sqrt(osLow+osQCDLowErr*osQCDLowErr+
										     osWLowErr*osWLowErr+
										     osWTLowErr*osWTLowErr+
										     topLowErr*topLowErr+
										     VVLowErr*VVLowErr+
										     zeftLowErr*zeftLowErr+
										     zjftLowErr*zjftLowErr));
   printf(" \n \n ");									     				     
   printf("Total & %.2f & %.2f & %.2f & %.2f \\\\ \n", osLow, osHigh, ssLow, ssHigh);
   printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", VVLow, VVLowErr, VVHigh, VVHighErr);
   printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", topLow, topLowErr, topHigh, topHighErr);
   printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zjftLow, zjftLowErr, zjftLow, zjftLowErr);
   printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zeftLow, zeftLowErr);
   printf("$W^{\\tau \\nu}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osWTLow, osWTLowErr, ssWTLow, ssWTLowErr);
   printf("$W^{l \\nu}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow, osWLowErr, osWHigh, osWHighErr, ssWLow, ssWLowErr, ssHigh, sqrt(ssHigh));
   printf("QCD & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osQCDLow, osQCDLowErr, ssQCDLow, ssQCDLowErr);
   printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",osQCDLow+osWLow+osWTLow+ttbarLow+VVLow+zeftLow+zjftLow,
   																			sqrt(osQCDLowErr*osQCDLowErr+
                                                                                     osWLowErr*osWLowErr+
                                                                                     osWTLowErr*osWTLowErr+
                                                                                     topLowErr*topLowErr+
                                                                                     VVLowErr*VVLowErr+
                                                                                     zeftLowErr*zeftLowErr+
											      									 zjftLowErr*zjftLowErr));
   

   return output;
}


float poissonFluctuation(Long_t N)
{
  TF1 f("mypoisson","TMath::Poisson(x,[0])",0,N);
  f.SetParameter(0,N);
  unsigned N2 = (unsigned)(f.GetRandom());
  return (float) N2;
}


// float getFluctuatedEvents(TTree* tree ,std:string selection,std::string lumi ) {
//   TH1F * pvs = new TH1F("pvs","PVs",10,0,1000);
//   tree->Draw("PVs>>pvs",("__WEIGHT__*"+lumi+ "("+selection+")").c_str());
//   Long_t events = (Long_t)pvs->Integral();

//   return poissonFluctuation(events);

// }