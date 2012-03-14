#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooKeysPdf.h"
#include "RooPlot.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "RooStats/ProfileLikelihoodCalculator.h"
#include "RooStats/LikelihoodIntervalPlot.h"


using namespace RooFit;
using namespace RooStats;


void setupVariables(RooWorkspace * w);
void  createShape(optutl::CommandLineParser& parser,RooWorkspace * w,std::string cut,std::string name );
void setupShapes(optutl::CommandLineParser&,RooWorkspace * w);
void setupModel(optutl::CommandLineParser&,RooWorkspace * w);
RooDataSet createDataSet(optutl::CommandLineParser&,RooWorkspace *);
void fitDataSet(RooDataSet&,RooWorkspace*,bool);




int main (int argc, char* argv[]) 
{
  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------

   //Data
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   parser.addOption("mcFile",optutl::CommandLineParser::kString,"File with the MC","MC.root");



   parser.addOption("preselection",optutl::CommandLineParser::kString,"lepton veto cuts ","(HLT_Mu9_fired||HLT_Mu11_fired||HLT_Mu15_v1_fired)&&muTauPt1>20&&muTauJetPt2>20&&abs(muTauEta2)<2.3&&muTauRelPFIso<0.05&&muTauIDIsoCh==0&&muTauIDIsoGamma==0");
   parser.addOption("oshighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muonSize==1&muTauMt1>60");
   parser.addOption("oslowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muonSize==1&&muTauMt1<20");
   parser.addOption("zmftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","mumuSize==1&&mumuPt1>20&&mumuPt2>20&&muTauMt1<20&&muTauDecayFound&&muTauisMuon==1");
   parser.addOption("zjftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","mumuSize==1&&mumuPt1>20&&mumuPt2>20&&muTauMt1<20&&muTauDecayFound&&muTauisMuon==0");
   parser.addOption("ttbarSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauJetsBTag2Pt15>1");
   parser.addOption("wmnFactor",optutl::CommandLineParser::kDouble,"WMN factor",0.078);
   parser.addOption("wmnFactorErr",optutl::CommandLineParser::kDouble,"WMN factor error ",0.005);
   parser.addOption("wtnFactor",optutl::CommandLineParser::kDouble,"WTN Factor",0.250);
   parser.addOption("ttbarFactor",optutl::CommandLineParser::kDouble,"TTBarFactor",0.30);
   parser.addOption("ttbarFactorErr",optutl::CommandLineParser::kDouble,"TTBarFactor Error",0.02);
   parser.addOption("zmftFactor",optutl::CommandLineParser::kDouble,"zMuMuFactor1",0.000814);
   parser.addOption("zmftFactorErr",optutl::CommandLineParser::kDouble,"zMuMuFactor1",0.0003);
   parser.addOption("zjftFactor",optutl::CommandLineParser::kDouble,"zMuMuFactor2",0.80);
   parser.addOption("zjftFactorErr",optutl::CommandLineParser::kDouble,"zMuMuFactor2",0.02);
   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","muTauEventTree/eventTree");
   //   parser.addOption("lumi",optutl::CommandLineParser::kDouble,"Luminosity",36.);


   parser.parseArguments (argc, argv);


   //setup basic workspace
   RooWorkspace *w = new RooWorkspace("w","Workspace");
   setupVariables(w);


   //create a model with counting only 
   setupShapes(parser,w);
   setupModel(parser,w);

   //create a dataset on real data 
   RooDataSet dataset = createDataSet(parser,w);
   
   
   //fit the dataset
   fitDataSet(dataset,w,true);






}








void setupVariables(RooWorkspace * w) {
  //declare observables
  //(parameters to be integrated
  w->factory("os_high[0,1000]");
  w->factory("zmft[0,20000]");
  w->factory("zjft[0,1000]");
  w->factory("ttbarLow[0,1000]");
  w->factory("ttbarHigh[0,1000]");
  w->factory("wmnF[0,1000]");
  w->factory("zmftF[0,1000]");
  w->factory("zjftF[0,1000]");
  w->factory("ttbarF[0,1000]");
  w->factory("ss_qcd[0,1000]");


  //declare parameter of interest
  w->factory("os_tautau[50,350]");
  w->factory("os_qcd[0,1000]");



  //Declare variables for shapes
  w->factory("muTauMass[0,400]");
  w->factory("fitType[os=1,ss=0]");


}




void  createShape(optutl::CommandLineParser& parser,RooWorkspace * w,std::string cut,std::string name)
{

   TFile *f = new TFile(parser.stringValue("mcFile").c_str());
   TTree *t = (TTree*)f->Get(parser.stringValue("treeName").c_str());

   TFile *fo = new TFile("tmp.root","RECREATE");
   fo->cd();
   TTree *tree = t->CopyTree(cut.c_str());

   RooDataSet data("ds", "dss", tree, RooArgSet(*w->var("muTauMass")));
   RooKeysPdf pdf(name.c_str(), "PDF", *w->var("muTauMass"),  data,RooKeysPdf::MirrorBoth,1.5);
   delete tree;
   fo->Close();
   f->Close();
   printf("Shape : %s created\n",name.c_str());

  RooPlot * Frame1 = w->var("muTauMass")->frame() ;
  pdf.plotOn(Frame1);
  TCanvas *cc = new TCanvas();
  cc->cd();
  Frame1->Draw();
  cc->SaveAs((name+".png").c_str());
  delete cc;
  delete Frame1;

  w->import(pdf);


}





void setupShapes(optutl::CommandLineParser& parser,RooWorkspace * w)
{
   std::string preselection    = parser.stringValue("preselection");
   std::string os  = preselection+"&&"+parser.stringValue("oslowSelection")+"&&TYPE==";



   createShape(parser,w,os+"1","zttPdf");
   createShape(parser,w,os+"2","qcdPdf");
   createShape(parser,w,os+"3&&muTauGenPt2>0","zmftPdf");
   createShape(parser,w,os+"3&&muTauGenPt2<=0","zjftPdf");
   createShape(parser,w,os+"4","wmnPdf");
   createShape(parser,w,os+"5","wtnPdf");
   createShape(parser,w,os+"6","ttbarPdf");

   w->var("muTauMass")->setRange(0,110.);
}



RooDataSet createDataSet(optutl::CommandLineParser& parser,RooWorkspace *w ) {
   //read Tree
  TFile *f = new TFile(parser.stringValue("dataFile").c_str());
  TTree *t = (TTree*)f->Get(parser.stringValue("treeName").c_str());

   printf("Creating RooDataset with Real Data\n");

   std::string preselection    = parser.stringValue("preselection");
   std::string oslowSelection = preselection+"&&"+parser.stringValue("oslowSelection");


   TFile *ff = new TFile("tmp.root","RECREATE");
   ff->cd();
   TTree *treeOS =t->CopyTree(oslowSelection.c_str()); 

   //now make datasets for the two regions and fork them together for simultaneous fit 
   RooDataSet dataOS("dataOS", "OS Data", treeOS, RooArgSet(*w->var("muTauMass")));

   delete treeOS;


   ff->Close();
   f->Close();

   return dataOS; 


}




void setupModel(optutl::CommandLineParser& parser,RooWorkspace * w)
{
  //define the background estimation expressions
  //For the extrapolating regions we use Poisson Counting


   //read Tree
  TFile *f = new TFile(parser.stringValue("dataFile").c_str());
  TTree *t = (TTree*)f->Get(parser.stringValue("treeName").c_str());

   std::string preselection    = parser.stringValue("preselection");
   std::string oshighSelection = preselection+"&&"+parser.stringValue("oshighSelection");
   std::string oslowSelection  = preselection+"&&"+parser.stringValue("oslowSelection");
   std::string zmftSelection   = preselection+"&&"+parser.stringValue("zmftSelection");
   std::string zjftSelection   = preselection+"&&"+parser.stringValue("zjftSelection");
   std::string ttbarSelection  = preselection+"&&"+parser.stringValue("ttbarSelection");




  //first define the poisson counting
  //for each region that is on its own and it is approximated by Poisson stats
   w->factory(TString::Format("Poisson::os_high_counting(%d,os_high)",t->GetEntries(oshighSelection.c_str())));
   w->factory(TString::Format("Poisson::zmft_counting(%d,zmft)",t->GetEntries(zmftSelection.c_str())));
   w->factory(TString::Format("Poisson::zjft_counting(%d,zjft)",t->GetEntries(zjftSelection.c_str())));
   w->factory(TString::Format("Poisson::ttbarLow_counting(%d,ttbarLow)",t->GetEntries((ttbarSelection+"&&"+oslowSelection).c_str())));
   w->factory(TString::Format("Poisson::ttbarHigh_counting(%d,ttbarHigh)",t->GetEntries((ttbarSelection+"&&"+oshighSelection).c_str())));
  
   //then define the gaussians for the factor uncertainties
   w->factory(TString::Format("Gaussian::unc_wmnF(%f,wmnF,%f)",parser.doubleValue("wmnFactor"),parser.doubleValue("wmnFactorErr")));
   w->factory(TString::Format("Gaussian::unc_zmftF(%f,zmftF,%f)",parser.doubleValue("zmftFactor"),parser.doubleValue("zmftFactorErr")));
   w->factory(TString::Format("Gaussian::unc_zjftF(%f,zjftF,%f)",parser.doubleValue("zjftFactor"),parser.doubleValue("zjftFactorErr")));
   w->factory(TString::Format("Gaussian::unc_ttbarF(%f,ttbarF,%f)",parser.doubleValue("ttbarFactor"),parser.doubleValue("ttbarFactorErr")));


   w->factory("expr::os_wmn('(os_high-ttbarHigh*ttbarF)*wmnF',os_high,ttbarHigh,ttbarF,wmnF)");
   w->factory(TString::Format("expr::os_wtn('os_wmn*%f',os_wmn)",parser.doubleValue("wtnFactor")));
   w->factory("expr::os_zmft('zmft*zmftF',zmft,zmftF)");
   w->factory("expr::os_zjft('zjft*zjftF',zjft,zjftF)");
   w->factory("expr::os_ttbar('ttbarLow*ttbarF',ttbarLow,ttbarF)");

   


   //Now make the shape models
   w->factory("SUM::osPDF(os_tautau*zttPdf,os_qcd*qcdPdf,os_wmn*wmnPdf,os_wtn*wtnPdf,os_zmft*zmftPdf,os_zjft*zjftPdf,os_ttbar*ttbarPdf)");

   
   //Now multiply together the count models
   w->factory("PROD::countPDF(os_high_counting,zmft_counting,zjft_counting,ttbarLow_counting,ttbarHigh_counting,unc_wmnF,unc_zmftF,unc_zjftF,unc_ttbarF)");

   
   w->factory("PROD::model(osPDF,countPDF)");


   double os_high = t->GetEntries(oshighSelection.c_str());
   double os_high_max = os_high+5*sqrt(os_high);
   double os_high_min = os_high - 5*sqrt(os_high) >0 ? os_high - 5*sqrt(os_high) :0;
   w->var("os_high")->setVal(os_high);
   w->var("os_high")->setRange(os_high_min,os_high_max);



   double zmft = t->GetEntries(zmftSelection.c_str());
   double zmft_max = zmft+5*sqrt(zmft);
   double zmft_min = zmft - 5*sqrt(zmft) >0 ? zmft - 5*sqrt(zmft) :0;
   w->var("zmft")->setVal(zmft);
   w->var("zmft")->setRange(zmft_min,zmft_max);



   double zjft = t->GetEntries(zjftSelection.c_str());
   double zjft_max = zjft+5*sqrt(zjft);
   double zjft_min = zjft - 5*sqrt(zjft) >0 ? zjft - 5*sqrt(zjft) :0;
   w->var("zjft")->setVal(zjft);
   w->var("zjft")->setRange(zjft_min,zjft_max);


   double ttbarLow = t->GetEntries((ttbarSelection+"&&"+oslowSelection).c_str());
   if(ttbarLow==0) ttbarLow=1;
   double ttbarLow_max = ttbarLow+5*sqrt(ttbarLow);
   double ttbarLow_min = ttbarLow - 5*sqrt(ttbarLow) >0 ? ttbarLow - 5*sqrt(ttbarLow) :0;
   w->var("ttbarLow")->setVal(ttbarLow);
   w->var("ttbarLow")->setRange(ttbarLow_min,ttbarLow_max);

   double ttbarHigh = t->GetEntries((ttbarSelection+"&&"+oshighSelection).c_str());
   if(ttbarHigh==0) ttbarHigh=1;
   double ttbarHigh_max = ttbarHigh+5*sqrt(ttbarHigh);
   double ttbarHigh_min = ttbarHigh - 5*sqrt(ttbarHigh) >0 ? ttbarHigh - 5*sqrt(ttbarHigh) :0;
   w->var("ttbarHigh")->setVal(ttbarHigh);
   w->var("ttbarHigh")->setRange(ttbarHigh_min,ttbarHigh_max);

   double wmnF = parser.doubleValue("wmnFactor");
   double wmnF_max = wmnF+5*parser.doubleValue("wmnFactorErr");
   double wmnF_min = wmnF-5*parser.doubleValue("wmnFactorErr")>0 ? wmnF-5*parser.doubleValue("wmnFactorErr") : 0.0; 
   w->var("wmnF")->setVal(wmnF);
   w->var("wmnF")->setRange(wmnF_min,wmnF_max);


   double zmftF = parser.doubleValue("zmftFactor");
   double zmftF_max = zmftF+5*parser.doubleValue("zmftFactorErr");
   double zmftF_min = zmftF-5*parser.doubleValue("zmftFactorErr")>0 ? zmftF-5*parser.doubleValue("zmftFactorErr") : 0.0; 
   w->var("zmftF")->setVal(zmftF);
   w->var("zmftF")->setRange(zmftF_min,zmftF_max);

   double zjftF = parser.doubleValue("zjftFactor");
   double zjftF_max = zjftF+5*parser.doubleValue("zjftFactorErr");
   double zjftF_min = zjftF-5*parser.doubleValue("zjftFactorErr")>0 ? zjftF-5*parser.doubleValue("zjftFactorErr") : 0.0; 
   w->var("zjftF")->setVal(zjftF);
   w->var("zjftF")->setRange(zjftF_min,zjftF_max);

   double ttbarF = parser.doubleValue("ttbarFactor");
   double ttbarF_max = ttbarF+5*parser.doubleValue("ttbarFactorErr");
   double ttbarF_min = ttbarF-5*parser.doubleValue("ttbarFactorErr")>0 ? ttbarF-5*parser.doubleValue("ttbarFactorErr") : 0.0; 
   w->var("ttbarF")->setVal(ttbarF);
   w->var("ttbarF")->setRange(ttbarF_min,ttbarF_max);




  
  w->var("os_tautau")->setRange(0.0,t->GetEntries(oslowSelection.c_str()));
  w->var("os_tautau")->setVal(t->GetEntries(oslowSelection.c_str())/2.);
  w->var("os_qcd")->setRange(0.0,t->GetEntries(oslowSelection.c_str()));
  w->var("os_qcd")->setVal(t->GetEntries(oslowSelection.c_str())/2.);
  
  

}



void fitDataSet(RooDataSet& data,RooWorkspace* w,bool verbose)
{

  w->pdf("model")->fitTo(data);

  if(verbose) {


   RooPlot *frame3 = w->var("muTauMass")->frame();
   data.plotOn(frame3,Binning(20,0.,200.));
   w->pdf("osPDF")->plotOn(frame3);
   TCanvas *ccc = new TCanvas("ccc","cc");
   frame3->Draw();
   ccc->SaveAs("OS_FIT.png");
   delete ccc;
   delete frame3;


  }

}
