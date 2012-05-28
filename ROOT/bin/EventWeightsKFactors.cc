#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH1D.h"

//Distribution from Fall 2011

std::vector<float> data;
std::vector<float> mc;
edm::Lumi3DReWeighting *LumiWeights;



void readdir(TDirectory *dir,TH1D* kfactor); 



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("mass",optutl::CommandLineParser::kString,"HiggsMass","EventSummary");
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__WEIGHT__");

   
   parser.parseArguments (argc, argv);
   
   TFile *fH = new TFile(("/afs/cern.ch/user/j/jueugste/public/html/kfactors/Kfactors_"+parser.stringValue("mass")+"_AllScales.root").c_str());

   TH1D *weight = (TH1D*)fH->Get(("kfactors/kfact_mh"+parser.stringValue("mass")+"_ren"+parser.stringValue("mass")+"_fac"+parser.stringValue("mass")).c_str());
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");


   readdir(f,weight);
   f->Close();
   fH->Close();

} 


void readdir(TDirectory *dir,TH1D *weight) 
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
      readdir(subdir,weight);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;
      float hqtweight=1.0;
      TBranch *newBranch = t->Branch("__HQT__",&hqtweight,"__HQT__/F");
      float pt;
      t->SetBranchAddress("higgsPt",&pt);
      for(Int_t i=0;i<t->GetEntries();++i)
	{
	  t->GetEntry(i);
	  hqtweight= weight->GetBinContent(weight->FindBin(pt));
	  newBranch->Fill();
	}
      t->Write("",TObject::kOverwrite);
    }

  }

}
