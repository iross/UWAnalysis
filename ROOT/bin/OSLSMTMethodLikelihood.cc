#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
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
void setupCountingModel(RooWorkspace * w);
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


   parser.addOption("preselection",optutl::CommandLineParser::kString,"lepton veto cuts ","HLT_Any&&muTauPt1>15&&muTauPt2>20&&muTauRelPFIso<0.1&&muTauLooseIso&&abs(muTauEta1)<2.1&&abs(muTauEta2)<2.3&&muTauLeadCandMVA<0.6");
   parser.addOption("oshighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("oslowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("sshighSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1>60&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("sslowSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1<40&&muTauisMuon==0&&(!(mumuSize>0&&mumuPt2>15))");
   parser.addOption("zmftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge==0&&muTauMt1<40&&muTauisMuon==1");
   parser.addOption("zjftSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauCharge!=0&&muTauMt1<40&&muTauisMuon==0&&mumuSize>0&&mumuPt2>15");
   parser.addOption("ttbarSelection",optutl::CommandLineParser::kString,"lepton veto cuts ","muTauJetsBTag2Pt20>1");
   parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.06);
   parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.02);
   parser.addOption("wmnFactor",optutl::CommandLineParser::kDouble,"WMN factor",0.287);
   parser.addOption("wmnFactorErr",optutl::CommandLineParser::kDouble,"WMN factor error ",0.010);
   parser.addOption("wtnFactor",optutl::CommandLineParser::kDouble,"WTN Factor",0.250);
   parser.addOption("ttbarFactor",optutl::CommandLineParser::kDouble,"TTBarFactor",3.37);
   parser.addOption("ttbarFactorErr",optutl::CommandLineParser::kDouble,"TTBarFactor Error",0.03);
   parser.addOption("zmftFactor",optutl::CommandLineParser::kDouble,"zMuMuFactor1",0.00084);
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
   setupCountingModel(w);

   //create a dataset on real data 
   RooDataSet dataset = createDataSet(parser,w);
   
   
   //fit the dataset
   fitDataSet(dataset,w,true);




}




RooDataSet createDataSet(optutl::CommandLineParser& parser,RooWorkspace *w ) {



   //read Tree
  TFile *f = new TFile(parser.stringValue("dataFile").c_str());
  TTree *t = (TTree*)f->Get(parser.stringValue("treeName").c_str());


   printf("Creating RooDataset with Real Data\n");
   RooArgSet observables;


   std::string preselection    = parser.stringValue("preselection");
   std::string oshighSelection = preselection+"&&"+parser.stringValue("oshighSelection");
   std::string oslowSelection  = preselection+"&&"+parser.stringValue("oslowSelection");
   std::string sshighSelection = preselection+"&&"+parser.stringValue("sshighSelection");
   std::string sslowSelection  = preselection+"&&"+parser.stringValue("sslowSelection");
   std::string zmftSelection   = preselection+"&&"+parser.stringValue("zmftSelection");
   std::string zjftSelection   = preselection+"&&"+parser.stringValue("zjftSelection");
   std::string ttbarSelection  = preselection+"&&"+parser.stringValue("ttbarSelection");


   //set values of the oservables
   w->var("obs_os_low")->setVal(t->GetEntries(oslowSelection.c_str()));
   w->var("obs_os_high")->setVal(t->GetEntries(oshighSelection.c_str()));
   w->var("obs_ss_low")->setVal(t->GetEntries(sslowSelection.c_str()));
   w->var("obs_ss_high")->setVal(t->GetEntries(sshighSelection.c_str()));
   w->var("obs_zmft")->setVal(t->GetEntries(zmftSelection.c_str()));
   w->var("obs_zjft")->setVal(t->GetEntries(zjftSelection.c_str()));
   w->var("obs_ttbarLow")->setVal(t->GetEntries((ttbarSelection+"&&"+oslowSelection).c_str()));
   w->var("obs_ttbarHigh")->setVal(t->GetEntries((ttbarSelection+"&&"+oshighSelection).c_str()));

   w->var("obs_qcdF")->setVal(parser.doubleValue("qcdFactor"));
   w->var("obs_qcdFErr")->setVal(parser.doubleValue("qcdFactorErr"));
   w->var("obs_wmnF")->setVal(parser.doubleValue("wmnFactor"));
   w->var("obs_wmnFErr")->setVal(parser.doubleValue("wmnFactorErr"));
   w->var("obs_wtnF")->setVal(parser.doubleValue("wtnFactor"));
   w->var("obs_zmftF")->setVal(parser.doubleValue("zmftFactor"));
   w->var("obs_zmftFErr")->setVal(parser.doubleValue("zmftFactorErr"));
   w->var("obs_zjftF")->setVal(parser.doubleValue("zjftFactor"));
   w->var("obs_zjftFErr")->setVal(parser.doubleValue("zjftFactorErr"));
   w->var("obs_ttbarF")->setVal(parser.doubleValue("ttbarFactor"));
   w->var("obs_ttbarFErr")->setVal(parser.doubleValue("ttbarFactorErr"));


   observables.add(*w->var("obs_os_low"));
   observables.add(*w->var("obs_os_high"));
   observables.add(*w->var("obs_ss_low"));
   observables.add(*w->var("obs_ss_high"));
   observables.add(*w->var("obs_zmft"));
   observables.add(*w->var("obs_zjft"));
   observables.add(*w->var("obs_ttbarLow"));
   observables.add(*w->var("obs_ttbarHigh"));
   observables.add(*w->var("obs_qcdF"));
   observables.add(*w->var("obs_qcdFErr"));
   observables.add(*w->var("obs_wmnF"));
   observables.add(*w->var("obs_wmnFErr"));
   observables.add(*w->var("obs_wtnF"));
   observables.add(*w->var("obs_zmftF"));
   observables.add(*w->var("obs_zmftFErr"));
   observables.add(*w->var("obs_zjftF"));
   observables.add(*w->var("obs_zjftFErr"));
   observables.add(*w->var("obs_ttbarF"));
   observables.add(*w->var("obs_ttbarFErr"));

   RooDataSet dataset("dataset","Real DATA",observables);
   dataset.add(observables);



   f->Close();
   return dataset; 


}







void setupVariables(RooWorkspace * w) {
  //declare observables
  w->factory("obs_os_low[0,1000]");
  w->factory("obs_os_high[0,1000]");
  w->factory("obs_ss_low[0,1000]");
  w->factory("obs_ss_high[0,1000]");
  w->factory("obs_zmft[0,20000]");
  w->factory("obs_zjft[0,1000]");
  w->factory("obs_ttbarLow[0,1000]");
  w->factory("obs_ttbarHigh[0,1000]");


  //declare observed factors and errors
  w->factory("obs_qcdF[0,1000]");
  w->factory("obs_qcdFErr[0,1000]");
  w->factory("obs_wmnF[0,1000]");
  w->factory("obs_wmnFErr[0,1000]");
  w->factory("obs_wtnF[0,1000]");
  w->factory("obs_zmftF[0,1000]");
  w->factory("obs_zmftFErr[0,1000]");
  w->factory("obs_zjftF[0,1000]");
  w->factory("obs_zjftFErr[0,1000]");
  w->factory("obs_ttbarF[0,1000]");
  w->factory("obs_ttbarFErr[0,1000]");

  //declare nuisances
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
  w->factory("os_tautau[250,350]");



  //Declare variables for shapes
  w->factory("mass[0,300]");
  w->factory("sign[os=1,ss=0]");



}

void setupCountingModel(RooWorkspace * w) 
{

  //declare parameters of interest 
  //actuallly only one - the others are nuisannces as well
  //However they are not varied for the systematics


  //define the background estimation expressions
  w->factory("expr::os_low('os_tautau+qcdF*ss_qcd+(os_high-ttbarHigh*ttbarF)*wmnF*(1+obs_wtnF)+zmft*zmftF+zjft*zjftF+ttbarLow*ttbarF',os_tautau,qcdF,ss_qcd,os_high,ttbarHigh,ttbarF,wmnF,obs_wtnF,zmft,zmftF,zjft,zjftF,ttbarLow)");

  w->factory("expr::ss_low('ss_qcd+ss_high*wmnF*(1+obs_wtnF)+zjft*zjftF',ss_qcd,ss_high,wmnF,obs_wtnF,zjft,zjftF)");




  //first define the poisson counting
  //for each region that is on its own

  w->factory("Poisson::os_low_counting(obs_os_low,os_low)");
  w->factory("Poisson::ss_low_counting(obs_ss_low,ss_low)");
  w->factory("Poisson::os_high_counting(obs_os_high,os_high)");
  w->factory("Poisson::ss_high_counting(obs_ss_high,ss_high)");
  w->factory("Poisson::zmft_counting(obs_zmft,zmft)");
  w->factory("Poisson::zjft_counting(obs_zjft,zjft)");
  w->factory("Poisson::ttbarLow_counting(obs_ttbarLow,ttbarLow)");
  w->factory("Poisson::ttbarHigh_counting(obs_ttbarHigh,ttbarHigh)");
  
  //then define the gaussians for the factor uncertainties
  w->factory("Gaussian::unc_qcdF(obs_qcdF,qcdF,obs_qcdFErr)");
  w->factory("Gaussian::unc_wmnF(obs_wmnF,wmnF,obs_wmnFErr)");
  w->factory("Gaussian::unc_zmftF(obs_zmftF,zmftF,obs_zmftFErr)");
  w->factory("Gaussian::unc_zjftF(obs_zjftF,zjftF,obs_zjftFErr)");
  w->factory("Gaussian::unc_ttbarF(obs_ttbarF,ttbarF,obs_ttbarFErr)");




  //then multiply everyhting 
  w->factory("PROD::model(os_low_counting,ss_low_counting,os_high_counting,ss_high_counting,zmft_counting,zjft_counting,ttbarLow_counting,ttbarHigh_counting,unc_qcdF,unc_wmnF,unc_zmftF,unc_zjftF,unc_ttbarF)");
  

    
}



void fitDataSet(RooDataSet& data,RooWorkspace* w,bool verbose)
{
  

  //first we need to constrain the nuisances to parameters near the mean value +-5 sigma 
  //so that the algorithm runs in reasonable time 

  const RooArgSet* datavals = data.get(); 

  cout << "observed Z enriched evs"<<datavals->getRealValue("obs_zmft")<<std::endl;

  w->var("os_high")->setVal(datavals->getRealValue("obs_os_high"));
  w->var("ss_high")->setVal(datavals->getRealValue("obs_ss_high"));
  w->var("zmft")->setVal(datavals->getRealValue("obs_zmft"));
  w->var("zjft")->setVal(datavals->getRealValue("obs_zjft"));
  w->var("ttbarLow")->setVal(datavals->getRealValue("obs_ttbarLow"));
  w->var("ttbarHigh")->setVal(datavals->getRealValue("obs_ttbarHigh"));
  w->var("qcdF")->setVal(datavals->getRealValue("obs_qcdF"));
  w->var("wmnF")->setVal(datavals->getRealValue("obs_wmnF"));
  w->var("zmftF")->setVal(datavals->getRealValue("obs_zmftF"));
  w->var("zjftF")->setVal(datavals->getRealValue("obs_zjftF"));
  w->var("ttbarF")->setVal(datavals->getRealValue("obs_ttbarF"));


  double os_high1 = datavals->getRealValue("obs_os_high") -5*sqrt(datavals->getRealValue("obs_os_high")) >0 ? datavals->getRealValue("obs_os_high") -5*sqrt(datavals->getRealValue("obs_os_high")) : 0.0;
  double os_high2 = datavals->getRealValue("obs_os_high") +5*sqrt(datavals->getRealValue("obs_os_high"));
  w->var("os_high")->setRange(os_high1,os_high2 );
  
  double ss_high1 = datavals->getRealValue("obs_ss_high") -5*sqrt(datavals->getRealValue("obs_ss_high")) >0 ? datavals->getRealValue("obs_ss_high") -5*sqrt(datavals->getRealValue("obs_ss_high")) : 0.0;
  double ss_high2 = datavals->getRealValue("obs_ss_high") +5*sqrt(datavals->getRealValue("obs_ss_high"));
  w->var("ss_high")->setRange(ss_high1,ss_high2);
  
  double zmft1 = datavals->getRealValue("obs_zmft") -5*sqrt(datavals->getRealValue("obs_zmft")) >0 ? datavals->getRealValue("obs_zmft") -5*sqrt(datavals->getRealValue("obs_zmft")) : 0.0;
  double zmft2 = datavals->getRealValue("obs_zmft") +5*sqrt(datavals->getRealValue("obs_zmft"));
  w->var("zmft")->setRange(zmft1,zmft2);
  
  double zjft1 = datavals->getRealValue("obs_zjft") -5*sqrt(datavals->getRealValue("obs_zjft")) >0 ? datavals->getRealValue("obs_zjft") -5*sqrt(datavals->getRealValue("obs_zjft")) : 0.0;
  double zjft2 = datavals->getRealValue("obs_zjft") +5*sqrt(datavals->getRealValue("obs_zjft"));
  w->var("zjft")->setRange(zjft1,zjft2);
  
  double ttbarLow1 = datavals->getRealValue("obs_ttbarLow") -5*sqrt(datavals->getRealValue("obs_ttbarLow")) >0 ? datavals->getRealValue("obs_ttbarLow") -5*sqrt(datavals->getRealValue("obs_ttbarLow")) : 0.0;
  double ttbarLow2 = datavals->getRealValue("obs_ttbarLow") +5*sqrt(datavals->getRealValue("obs_ttbarLow"));
  w->var("ttbarLow")->setRange(ttbarLow1,ttbarLow2);
  
  double ttbarHigh1 = datavals->getRealValue("obs_ttbarHigh") -5*sqrt(datavals->getRealValue("obs_ttbarHigh")) >0 ? datavals->getRealValue("obs_ttbarHigh") -5*sqrt(datavals->getRealValue("obs_ttbarHigh")) : 0.0;
  double ttbarHigh2 = datavals->getRealValue("obs_ttbarHigh") +5*sqrt(datavals->getRealValue("obs_ttbarHigh"));
  w->var("ttbarHigh")->setRange(ttbarHigh1,ttbarHigh2);
  
  double qcdF1 = datavals->getRealValue("obs_qcdF") -5*datavals->getRealValue("obs_qcdFErr") >0 ? datavals->getRealValue("obs_qcdF") -5*datavals->getRealValue("obs_qcdFErr") : 0.0;
  double qcdF2 = datavals->getRealValue("obs_qcdF") +5*datavals->getRealValue("obs_qcdFErr");
  w->var("qcdF")->setRange(qcdF1,qcdF2);
  
  double wmnF1 = datavals->getRealValue("obs_wmnF") -5*datavals->getRealValue("obs_wmnFErr") >0 ? datavals->getRealValue("obs_wmnF") -5*datavals->getRealValue("obs_wmnFErr") : 0.0;
  double wmnF2 = datavals->getRealValue("obs_wmnF") +5*datavals->getRealValue("obs_wmnFErr");
  w->var("wmnF")->setRange(wmnF1,wmnF2);

  double zmftF1 = datavals->getRealValue("obs_zmftF") -5*datavals->getRealValue("obs_zmftFErr") >0 ? datavals->getRealValue("obs_zmftF") -5*datavals->getRealValue("obs_zmftFErr") : 0.0;
  double zmftF2 = datavals->getRealValue("obs_zmftF") +5*datavals->getRealValue("obs_zmftFErr");
  w->var("zmftF")->setRange(zmftF1,zmftF2);
  
  
  double zjftF1 = datavals->getRealValue("obs_zjftF") -5*datavals->getRealValue("obs_zjftFErr") >0 ? datavals->getRealValue("obs_zjftF") -5*datavals->getRealValue("obs_zjftFErr") : 0.0;
  double zjftF2 = datavals->getRealValue("obs_zjftF") +5*datavals->getRealValue("obs_zjftFErr");
  w->var("zjftF")->setRange(zjftF1,zjftF2);

  double ttbarF1 = datavals->getRealValue("obs_ttbarF") -5*datavals->getRealValue("obs_ttbarFErr") >0 ? datavals->getRealValue("obs_ttbarF") -5*datavals->getRealValue("obs_ttbarFErr") : 0.0;
  double ttbarF2 = datavals->getRealValue("obs_ttbarF") +5*datavals->getRealValue("obs_ttbarFErr");
  w->var("ttbarF")->setRange(ttbarF1,ttbarF2);
  
  w->var("ss_qcd")->setVal(datavals->getRealValue("obs_ss_low")/2.);
  w->var("ss_qcd")->setRange(0.0,datavals->getRealValue("obs_ss_low"));
  w->var("os_tautau")->setRange(0.0,datavals->getRealValue("obs_os_low"));
  w->var("os_tautau")->setVal(datavals->getRealValue("obs_os_low")/2.);
  

  //fit !
  //  w->pdf("model")->fitTo(data,SumW2Error(kFALSE));
 
//   //create -LOGL
   RooAbsReal *nll = w->pdf("model")->createNLL(data);
   RooMinuit(*nll).migrad();


   

   RooPlot *frame = w->var("os_tautau")->frame(Range(250,350));
   nll->plotOn(frame,ShiftToZero());
   TCanvas *c = new TCanvas("c","cc");
   c->cd();
   frame->Draw();
   c->SaveAs("interval.png");
   delete c;
   delete frame;
   delete nll;
  
  
//   //Create Likelihood interval
//   RooArgSet poi;
//   poi.add(*w->var("os_tautau"));
//   ProfileLikelihoodCalculator plc(data,*w->pdf("model"),poi,0.32);

//   //Now Fit!
//   w->pdf("model")->fitTo(data,NumCPU(2),SumW2Error(kFALSE));

//   LikelihoodInterval * interval = plc.GetInterval();

//   double lowerLimit=interval->LowerLimit(*w->var("os_tautau"));
//   double upperLimit=interval->UpperLimit(*w->var("os_tautau"));

//   printf("LowerLimit = %f \n",lowerLimit);
//   printf("UpperLimit = %f \n",upperLimit);


//   if(verbose) {
//     printf("Making PL plot\n");
//     LikelihoodIntervalPlot plot(interval);
//     plot.SetRange(w->var("os_tautau")->getVal()-2*lowerLimit,w->var("os_tautau")->getVal()+2*upperLimit);
//     plot.SetNPoints(10);
//     TCanvas *c = new TCanvas("c","cc");
//     c->cd();
//     plot.Draw();
//     c->SaveAs("interval.png");
//     delete c;
  
  
//   }

//     delete interval;

}

