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
   parser.addOption("A",optutl::CommandLineParser::kString,"A");
   parser.addOption("B",optutl::CommandLineParser::kString,"B");
   parser.addOption("C",optutl::CommandLineParser::kString,"C");
   parser.addOption("D",optutl::CommandLineParser::kString,"D");
   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","eleMuEventTree/eventTree");
   parser.parseArguments (argc, argv);


   //translate the parser selections 
   std::string preselection    = parser.stringValue("preselection");
   std::string As               = preselection+"&&"+parser.stringValue("A");
   std::string Bs               = preselection+"&&"+parser.stringValue("B");
   std::string Cs               = preselection+"&&"+parser.stringValue("C");
   std::string Ds               = preselection+"&&"+parser.stringValue("D");

   //Get file and tree
   TFile *f = new TFile(parser.stringValue("dataFile").c_str());
   TTree *t =(TTree*) f->Get(parser.stringValue("treeName").c_str());
   
   //calculate events in the regions

   float A = t->GetEntries( As.c_str());
   float B = t->GetEntries( Bs.c_str());
   float C = t->GetEntries( Cs.c_str());
   float D = t->GetEntries( Ds.c_str());

   printf("A=%f B=%f C=%f D=%f\n",A,B,C,D);

   float background = C*B/D;
   float backgrounderr = background*sqrt(1/C+1/D+1/B);

   printf("Background=%f +- %f\n",background,backgrounderr);

  float gQCD = background*background/(backgrounderr*backgrounderr);
  printf("QCD (Gamma function) = %f , %f \n",gQCD,background/gQCD);





}

