#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooPlot.h"
#include "RooMinuit.h"
#include "TCanvas.h"
#include "TGraphErrors.h"
#include "TROOT.h"
#include "TFile.h"
#include "TProfile.h"
#include "TAxis.h"
#include "TTree.h"
#include "TF1.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "Math/GenVector/DisplacementVector3D.h" 
#include "RooStats/LikelihoodIntervalPlot.h"

typedef ROOT::Math::DisplacementVector3D<ROOT::Math::Cartesian3D<double>,ROOT::Math::DefaultCoordinateSystemTag> Vector;

int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------

   //Data

   parser.addOption("dataFile",optutl::CommandLineParser::kString,"dataFile");
   parser.addOption("tree",optutl::CommandLineParser::kString,"tree","mumuEventTree/eventTree");
   parser.addOption("weight",optutl::CommandLineParser::kString,"");
   parser.addOption("cut",optutl::CommandLineParser::kString,"");
   parser.addOption("bins",optutl::CommandLineParser::kInteger,"bins",25);
   parser.addOption("min",optutl::CommandLineParser::kDouble,"min",0.0);
   parser.addOption("max",optutl::CommandLineParser::kDouble,"max",100.0);

   parser.parseArguments (argc, argv);

   string inputFile = parser.stringValue("dataFile");
   string tree    = parser.stringValue("tree");
   string weight  = parser.stringValue("weight");
   string cut     = parser.stringValue("cut");
   int bins       = parser.integerValue("bins");
   double min     = parser.doubleValue("min");
   double max     = parser.doubleValue("max");

   //open output file
   TFile * fout=  new TFile(parser.stringValue("outputFile").c_str(),"RECREATE");

   //get the tree
   TFile * f=  new TFile(parser.stringValue("dataFile").c_str());
   TTree *t  = (TTree*)f->Get(parser.stringValue("tree").c_str());

   //skim it 
   fout->cd();
   TTree *skimmedTree = t->CopyTree(cut.c_str());

   //loop on it 
   float pt=0.0;
   float px=0.0;
   float py=0.0;
   float rPx=0.0;
   float rPy=0.0;
   float w=1.0;

   skimmedTree->SetBranchAddress("pt",&pt);
   skimmedTree->SetBranchAddress("px",&px);
   skimmedTree->SetBranchAddress("py",&py);
   skimmedTree->SetBranchAddress("recoilPx",&rPx);
   skimmedTree->SetBranchAddress("recoilPy",&rPy);
   if(skimmedTree->FindBranch(weight.c_str())!=0)
     skimmedTree->SetBranchAddress(weight.c_str(),&w);

   

   //create an axis for navigation
   TAxis *nav = new TAxis(bins,min,max);




   //book histograms
   std::vector<TH1F*> histogramsU1;
   std::vector<TH1F*> histogramsU2;
   for( int j=0;j<=bins;++j) {
     histogramsU1.push_back(new TH1F(TString::Format("h1_%d",j),"h",100,-400,50));
     histogramsU2.push_back(new TH1F(TString::Format("h2_%d",j),"h",100,-100,100));
   }


   for(int i=0;i<skimmedTree->GetEntries();++i) {
     skimmedTree->GetEntry(i);

     //create the vectors
     Vector zV(px,py,0.0);
     Vector rV(rPx,rPy,0.0);
     //a vertical vector to the Z momentum
     Vector zVV(-py,px,0.0);

     //get the projections
     float U1 = rV.Dot(zV)/zV.r();
     float U2 = rV.Dot(zVV)/zVV.r();

     
     //find bin
     int bin = nav->FindBin(pt);

     //fill histograms
     histogramsU1[bin-1]->Fill(U1,w);
     histogramsU2[bin-1]->Fill(U2,w);
   }


   //dump histograms
   fout->cd();
   for(int i=0;i<=bins;++i){
     histogramsU1[i]->Write();
     histogramsU2[i]->Write();
   }



   //fit simply
   TGraphErrors *U1s_response =  new TGraphErrors();
   TGraphErrors *U1s_resolution =  new TGraphErrors();
   TGraphErrors *U2s_response =  new TGraphErrors();
   TGraphErrors *U2s_resolution =  new TGraphErrors();
   
   
   for(int i=0;i<bins;++i){
     U1s_response->SetPoint(i,nav->GetBinCenter(i+1),histogramsU1[i]->GetMean());
     U1s_response->SetPointError(i,nav->GetBinWidth(i),histogramsU1[i]->GetMeanError());
     U2s_response->SetPoint(i,nav->GetBinCenter(i+1),histogramsU2[i]->GetMean());
     U2s_response->SetPointError(i,nav->GetBinWidth(i+1),histogramsU2[i]->GetMeanError());

   U1s_resolution->SetPoint(i,nav->GetBinCenter(i+1),histogramsU1[i]->GetRMS());
     U1s_resolution->SetPointError(i,nav->GetBinWidth(i+1),histogramsU1[i]->GetRMSError());
     U2s_resolution->SetPoint(i,nav->GetBinCenter(i+1),histogramsU2[i]->GetRMS());
     U2s_resolution->SetPointError(i,nav->GetBinWidth(i+1),histogramsU2[i]->GetRMSError());

   }

   //fit histograms 


   //double gauss
   TF1 *dg = new TF1("dg","gaus(0)",min,max);
   dg->SetParameters(1.,1.,1.,1.,1.,1.);


   //make output histograms
   TGraphErrors *U1_response =  new TGraphErrors();
   TGraphErrors *U1_resolution =  new TGraphErrors();
   TGraphErrors *U2_response =  new TGraphErrors();
   TGraphErrors *U2_resolution =  new TGraphErrors();

  
   for(int i=0;i<bins;++i){
     dg->SetParameter(1,histogramsU1[i]->GetMean());
     dg->SetParameter(1,histogramsU1[i]->GetRMS());
     histogramsU1[i]->Fit(dg,"","",min,max);
     U1_response->SetPoint(i,nav->GetBinCenter(i+1),dg->Mean(-400,50));
     U1_resolution->SetPoint(i,nav->GetBinCenter(i+1),sqrt(dg->Variance(-100,100)));
     dg->SetParameter(1,histogramsU2[i]->GetMean());
     dg->SetParameter(1,histogramsU2[i]->GetRMS());
     histogramsU2[i]->Fit(dg,"","",min,max);
     U2_response->SetPoint(i,nav->GetBinCenter(i+1),dg->Mean(-400,50));
     U2_resolution->SetPoint(i,nav->GetBinCenter(i+1),sqrt(dg->Variance(-100,100)));
   }

   U1_response->Write("U1_resp");
   U2_response->Write("U2_resp");
   U1_resolution->Write("U1_res");
   U2_resolution->Write("U2_res");

   U1s_response->Write("U1s_resp");
   U2s_response->Write("U2s_resp");
   U1s_resolution->Write("U1s_res");
   U2s_resolution->Write("U2s_res");
   


   printf("Creating parameterization\n");

   printf("Response of U1-------------------------------\n");
   U1s_response->Fit("pol1");

   printf("Response of U2-------------------------------\n");
   U2s_response->Fit("pol0");

   printf("Resolution of U1-------------------------------\n");
   U1s_resolution->Fit("pol2");

   printf("Resolution of U2-------------------------------\n");
   U2s_resolution->Fit("pol2");





   fout->Close();
   f->Close();


     

			      
   



}


