#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include <math.h> 
#include "TMath.h" 
#include <limits>


TH1F *LTau20;
TH1F *LTau15MC;
TH1F *MTau20;
TH1F *TTau20;

TH1F *LTau10;
TH1F *LTau10MC;
TH1F *LTau15;


void loadHistograms() {
  TFile *f = new TFile("EleTauEff.root");
  LTau20   = (TH1F*)f->Get("EffLooseTau20TH1F");
  MTau20   = (TH1F*)f->Get("EffMediumTau20TH1F");
  TTau20   = (TH1F*)f->Get("EffTightTau20TH1F");

  TFile *ff = new TFile("EleTauEff2.root");
  LTau15MC = (TH1F*)ff->Get("EffLooseTau15MCTH1F");

  TFile *fff = new TFile("MuTauEff.root");

  LTau10   = (TH1F*)fff->Get("EffLooseTau10TH1F");
  LTau15   = (TH1F*)f->Get("EffLooseTau15TH1F");
  LTau10MC = (TH1F*)f->Get("EffLooseTau10MCThinTH1F");



}


void readdir(TDirectory *dir,optutl::CommandLineParser parser); 


float weightETau(float pt1,float pt2,float eta1) {


  float loose   = LTau20->GetBinContent(LTau20->FindBin(pt2));
  float looseMC = LTau15MC->GetBinContent(LTau15MC->FindBin(pt2));

  float medium  = MTau20->GetBinContent(MTau20->FindBin(pt2));
  float tight   = TTau20->GetBinContent(MTau20->FindBin(pt2));


  //  return (0.52*loose+0.36*tight+0.12*medium)/(looseMC);
    return (0.52*loose+0.36*tight+0.12*medium);


}

float weightMuTau(float pt1,float pt2,float eta1) {


  float loose10   = LTau10->GetBinContent(LTau10->FindBin(pt2));
  float loose10MC = LTau10MC->GetBinContent(LTau10MC->FindBin(pt2));

  float loose15   = LTau15->GetBinContent(LTau15->FindBin(pt2));

  return (0.92*loose15+0.08*loose10)/(loose10MC);


}



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__HLT__");
   parser.addOption("finalState",optutl::CommandLineParser::kString,"Final state","mutau");
   parser.parseArguments (argc, argv);
   
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");

   loadHistograms();

   readdir(f,parser);
   f->Close();

} 


void readdir(TDirectory *dir,optutl::CommandLineParser parser) 
{
  TDirectory *dirsav = gDirectory;
  TIter next(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
    printf("Found key=%s \n",key->GetName());
    TObject *obj = key->ReadObj();

    if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      readdir(subdir,parser);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;
      float weight = 1.0;
      TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());

      float pt1;
      float eta1;
      float pt2;
      float eta2;


      t->SetBranchAddress("pt1",&pt1);
      t->SetBranchAddress("eta1",&eta1);
      t->SetBranchAddress("pt2",&pt2);
      t->SetBranchAddress("eta2",&eta2);
      
      std::string finalState = parser.stringValue("finalState");

      printf("Found tree -> weighting\n");
      for(Int_t i=0;i<t->GetEntries();++i)
	{
	  t->GetEntry(i);
	  weight=0;
	   if (finalState=="eleTau")
	    weight=weightETau(pt1,pt2,eta1);
	   else if(finalState=="muTau")
	     weight=weightMuTau(pt1,pt2,eta1);

	  newBranch->Fill();
	}

      t->Write("",TObject::kOverwrite);
    }
  }
}
