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



   //   parser.addOption("preselection",optutl::CommandLineParser::kString,"lepton veto cuts ","HLT_Any&&muTauPt1>15&&muTauPt2>20&&muTauChargeIso==0&&muTauGammaIso==0&&muTauNeutralIso==0&&muTauLooseIso&&abs(muTauEta1)<2.1&&abs(muTauEta2)<2.3&&muTauLeadCandMVA<0.6");
   parser.addOption("preselection",optutl::CommandLineParser::kString,"lepton veto cuts ","HLT_Any&&muTauPt1>15&&muTauPt2>20&&muTauRelPFIso<0.1&&muTauLooseIso&&abs(muTauEta1)<2.1&&abs(muTauEta2)<2.3&&muTauLeadCandMVA<0.6");
   parser.addOption("oshighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("oslowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("sshighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("sslowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("zmftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1<40&&muTauisMuon==1");
   parser.addOption("zjftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1<40&&muTauisMuon==0&&mumuSize>0&&mumuPt2>15");
   parser.addOption("ttbarSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauJetsBTag2Pt20>1");
   parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.03);
   parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.01);
   parser.addOption("wmnFactor",optutl::CommandLineParser::kDouble,"WMN factor",0.287);
   parser.addOption("wmnFactorErr",optutl::CommandLineParser::kDouble,"WMN factor error ",0.010);
   parser.addOption("wtnFactor",optutl::CommandLineParser::kDouble,"WTN Factor",0.250);
   parser.addOption("ttbarFactor",optutl::CommandLineParser::kDouble,"TTBarFactor",3.37);
   parser.addOption("ttbarFactorErr",optutl::CommandLineParser::kDouble,"TTBarFactor Error",0.03);
   parser.addOption("zmftFactor",optutl::CommandLineParser::kDouble,"zMuMuFactor1",0.000814);
   parser.addOption("zmftFactorErr",optutl::CommandLineParser::kDouble,"zMuMuFactor1",0.0003);
   parser.addOption("zjftFactor",optutl::CommandLineParser::kDouble,"zMuMuFactor2",0.80);
   parser.addOption("zjftFactorErr",optutl::CommandLineParser::kDouble,"zMuMuFactor2",0.02);
   parser.addOption("energyScale",optutl::CommandLineParser::kDouble,"energy Scale",0.98);
   parser.addOption("energyScaleErr",optutl::CommandLineParser::kDouble,"energy scale error ",0.02);

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
  w->factory("ss_high[0,1000]");
  w->factory("zmft[0,20000]");
  w->factory("zjft[0,1000]");
  w->factory("ttbarLow[0,1000]");
  w->factory("ttbarHigh[0,1000]");
  w->factory("qcdF[0,1000]");
  w->factory("wmnF[0,1000]");
  w->factory("zmftF[0,1000]");
  w->factory("zjftF[0,1000]");
  w->factory("ttbarF[0,1000]");
  w->factory("ss_qcd[0,1000]");


  //declare parameter of interest
  w->factory("os_tautau[50,350]");



  //Declare variables for shapes
  w->factory("muTauMass[0,400]");
  w->factory("fitType[os=1,ss=0]");

  w->factory("energyScale[0.9,1.1]");
  w->factory("expr::mass('(1./TMath::Sqrt(energyScale))*muTauMass',energyScale,muTauMass)");


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

  w->import(pdf,RenameVariable("muTauMass","mass"));

}





void setupShapes(optutl::CommandLineParser& parser,RooWorkspace * w)
{
   std::string preselection    = parser.stringValue("preselection");
   std::string os  = preselection+"&&"+parser.stringValue("oslowSelection")+"&&TYPE==";
   std::string ss  = preselection+"&&"+parser.stringValue("sslowSelection")+"&&TYPE==";


   createShape(parser,w,os+"1","zttPdf");
   createShape(parser,w,os+"2","qcdPdf");
   createShape(parser,w,os+"3&&muTauGenPt2>0","zmftPdf");
   createShape(parser,w,ss+"3&&muTauGenPt2<=0","zjftPdf");
   createShape(parser,w,os+"4","wmnPdf");
   createShape(parser,w,ss+"5","wtnPdf");
   createShape(parser,w,os+"6","ttbarPdf");

   w->var("muTauMass")->setRange(0,200.);
}



RooDataSet createDataSet(optutl::CommandLineParser& parser,RooWorkspace *w ) {
   //read Tree
  TFile *f = new TFile(parser.stringValue("dataFile").c_str());
  TTree *t = (TTree*)f->Get(parser.stringValue("treeName").c_str());

   printf("Creating RooDataset with Real Data\n");

   std::string preselection    = parser.stringValue("preselection");
   std::string oslowSelection = preselection+"&&"+parser.stringValue("oslowSelection");
   std::string sslowSelection = preselection+"&&"+parser.stringValue("sslowSelection");


   TFile *ff = new TFile("tmp.root","RECREATE");
   ff->cd();
   TTree *treeOS =t->CopyTree(oslowSelection.c_str()); 
   TTree *treeSS =t->CopyTree(sslowSelection.c_str()); 
   //now make datasets for the two regions and fork them together for simultaneous fit 
   RooDataSet dataOS("dataOS", "OS Data", treeOS, RooArgSet(*w->var("muTauMass")));
   RooDataSet dataSS("dataSS", "SS Data", treeSS, RooArgSet(*w->var("muTauMass")));
   RooDataSet dataset("data","data",RooArgSet(*w->var("muTauMass")),Index(*w->cat("fitType")),Import("os",dataOS),Import("ss",dataSS)); 

   delete treeOS;
   delete treeSS;

   ff->Close();
   f->Close();

   return dataset; 


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
   std::string sshighSelection = preselection+"&&"+parser.stringValue("sshighSelection");
   std::string sslowSelection  = preselection+"&&"+parser.stringValue("sslowSelection");
   std::string zmftSelection   = preselection+"&&"+parser.stringValue("zmftSelection");
   std::string zjftSelection   = preselection+"&&"+parser.stringValue("zjftSelection");
   std::string ttbarSelection  = preselection+"&&"+parser.stringValue("ttbarSelection");




  //first define the poisson counting
  //for each region that is on its own and it is approximated by Poisson stats
   w->factory(TString::Format("Poisson::os_high_counting(%d,os_high)",(int)t->GetEntries(oshighSelection.c_str())));
   w->factory(TString::Format("Poisson::ss_high_counting(%d,ss_high)",(int)t->GetEntries(sshighSelection.c_str())));
   w->factory(TString::Format("Poisson::zmft_counting(%d,zmft)",(int)t->GetEntries(zmftSelection.c_str())));
   w->factory(TString::Format("Poisson::zjft_counting(%d,zjft)",(int)t->GetEntries(zjftSelection.c_str())));
   w->factory(TString::Format("Poisson::ttbarLow_counting(%d,ttbarLow)",(int)t->GetEntries((ttbarSelection+"&&"+oslowSelection).c_str())));
   w->factory(TString::Format("Poisson::ttbarHigh_counting(%d,ttbarHigh)",(int)t->GetEntries((ttbarSelection+"&&"+oshighSelection).c_str())));
  
   //then define the gaussians for the factor uncertainties
   w->factory(TString::Format("Gaussian::unc_qcdF(%f,qcdF,%f)",parser.doubleValue("qcdFactor"),parser.doubleValue("qcdFactorErr")));
   w->factory(TString::Format("Gaussian::unc_wmnF(%f,wmnF,%f)",parser.doubleValue("wmnFactor"),parser.doubleValue("wmnFactorErr")));
   w->factory(TString::Format("Gaussian::unc_zmftF(%f,zmftF,%f)",parser.doubleValue("zmftFactor"),parser.doubleValue("zmftFactorErr")));
   w->factory(TString::Format("Gaussian::unc_zjftF(%f,zjftF,%f)",parser.doubleValue("zjftFactor"),parser.doubleValue("zjftFactorErr")));
   w->factory(TString::Format("Gaussian::unc_ttbarF(%f,ttbarF,%f)",parser.doubleValue("ttbarFactor"),parser.doubleValue("ttbarFactorErr")));
   w->factory(TString::Format("Gaussian::unc_scale(%f,energyScale,%f)",parser.doubleValue("energyScale"),parser.doubleValue("energyScaleErr")));


   w->factory("expr::os_qcd('qcdF*ss_qcd',qcdF,ss_qcd)");
   w->factory("expr::os_wmn('(os_high-ttbarHigh*ttbarF)*wmnF',os_high,ttbarHigh,ttbarF,wmnF)");
   w->factory(TString::Format("expr::os_wtn('os_wmn*%f',os_wmn)",parser.doubleValue("wtnFactor")));
   w->factory("expr::os_zmft('zmft*zmftF',zmft,zmftF)");
   w->factory("expr::os_zjft('zjft*zjftF',zjft,zjftF)");
   w->factory("expr::os_ttbar('ttbarLow*ttbarF',ttbarLow,ttbarF)");
   w->factory("expr::ss_wmn('ss_high*wmnF',ss_high,wmnF)");
   w->factory(TString::Format("expr::ss_wtn('ss_wmn*%f',ss_wmn)",parser.doubleValue("wtnFactor")));

   


   //Now make the shape models
   w->factory("SUM::osPDF(os_tautau*zttPdf,os_qcd*qcdPdf,os_wmn*wmnPdf,os_wtn*wtnPdf,os_zmft*zmftPdf,os_zjft*zjftPdf,os_ttbar*ttbarPdf)");
   w->factory("SUM::ssPDF(ss_qcd*qcdPdf,ss_wmn*wmnPdf,ss_wtn*wtnPdf,os_zjft*zjftPdf)");
   
   //Now multiply together the count models
   w->factory("PROD::countPDF(os_high_counting,ss_high_counting,zmft_counting,zjft_counting,ttbarLow_counting,ttbarHigh_counting,unc_qcdF,unc_wmnF,unc_zmftF,unc_zjftF,unc_ttbarF,unc_scale)");

   //Now define the simultaneous
   w->factory("SIMUL::shapePDF(fitType,os=osPDF,ss=ssPDF)");
   
   w->factory("PROD::model(shapePDF,countPDF)");


   double os_high = t->GetEntries(oshighSelection.c_str());
   double os_high_max = os_high+5*sqrt(os_high);
   double os_high_min = os_high - 5*sqrt(os_high) >0 ? os_high - 5*sqrt(os_high) :0;
   w->var("os_high")->setVal(os_high);
   w->var("os_high")->setRange(os_high_min,os_high_max);

   double ss_high = t->GetEntries(sshighSelection.c_str());
   double ss_high_max = ss_high+5*sqrt(ss_high);
   double ss_high_min = ss_high - 5*sqrt(ss_high) >0 ? ss_high - 5*sqrt(ss_high) :0;
   w->var("ss_high")->setVal(ss_high);
   w->var("ss_high")->setRange(ss_high_min,ss_high_max);

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

   double qcdF = parser.doubleValue("qcdFactor");
   double qcdF_max = qcdF+5*parser.doubleValue("qcdFactorErr");
   double qcdF_min = qcdF-5*parser.doubleValue("qcdFactorErr")>0 ? qcdF-5*parser.doubleValue("qcdFactorErr") : 0.0; 
   w->var("qcdF")->setVal(qcdF);
   w->var("qcdF")->setRange(qcdF_min,qcdF_max);

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




  
  w->var("ss_qcd")->setVal(t->GetEntries(sslowSelection.c_str())/2.);
  w->var("ss_qcd")->setRange(0.0,t->GetEntries(sslowSelection.c_str()));
  w->var("os_tautau")->setRange(0.0,t->GetEntries(oslowSelection.c_str()));
  w->var("os_tautau")->setVal(t->GetEntries(oslowSelection.c_str())/2.);
  
  

}



void fitDataSet(RooDataSet& data,RooWorkspace* w,bool verbose)
{

  w->pdf("model")->fitTo(data);

  if(verbose) {

   RooAbsData *os_data = data.reduce(RooArgSet(*w->var("muTauMass")),"fitType==1");
   RooAbsData *ss_data = data.reduce(RooArgSet(*w->var("muTauMass")),"fitType==0");

   RooPlot *frame3 = w->var("muTauMass")->frame();
   os_data->plotOn(frame3,Binning(20,0.,200.));
   w->pdf("osPDF")->plotOn(frame3);


   TCanvas *ccc = new TCanvas("ccc","cc");
   frame3->Draw();
   ccc->SaveAs("OS_FIT.png");
   delete ccc;
   

   RooPlot *frame4 = w->var("muTauMass")->frame();
   ss_data->plotOn(frame4,Binning(20,0.,200.));
   w->pdf("ssPDF")->plotOn(frame4);

   TCanvas *cccc = new TCanvas("cccc","cc");
   frame4->Draw();
   cccc->SaveAs("SS_FIT.png");
   delete cccc;


   
   delete os_data;
   delete ss_data;
   delete frame3;


  }

}
