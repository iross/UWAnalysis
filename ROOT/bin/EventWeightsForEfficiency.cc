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





void readdir(TDirectory *dir,TFile * corrs,optutl::CommandLineParser parser); 



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__HLT__");
   parser.addOption("file",optutl::CommandLineParser::kString,"File","corrections.root");
   parser.addOption("correctors",optutl::CommandLineParser::kStringVector,"Correctors");
   parser.addOption("weights",optutl::CommandLineParser::kDoubleVector,"weights");
   parser.addOption("eta",optutl::CommandLineParser::kString,"eta variable","eta1");
   parser.addOption("pt",optutl::CommandLineParser::kString,"pt variable","pt1");
   parser.addOption("barrelEndcap",optutl::CommandLineParser::kInteger,"Separate Barrel,Endcap",0);
   parser.parseArguments (argc, argv);
   
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");
   TFile *fc = new TFile(parser.stringValue("file").c_str());
   readdir(f,fc,parser);
   f->Close();
   fc->Close();
} 


void readdir(TDirectory *dir,TFile* corrs,optutl::CommandLineParser parser) 
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
      readdir(subdir,corrs,parser);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;
      float weight = 1.0;
      TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());

      float pt;
      float eta;

      t->SetBranchAddress(parser.stringValue("eta").c_str(),&eta);
      t->SetBranchAddress(parser.stringValue("pt").c_str(),&pt);
      
      std::vector<double> weights = parser.doubleVector("weights");
      std::vector<std::string> correctors = parser.stringVector("correctors");
	
      printf("Found tree -> weighting\n");
      for(Int_t i=0;i<t->GetEntries();++i)
	{
	  t->GetEntry(i);
	  weight=0.0;
	  float p=pt;
	  if(p>50.) p=50.;

	  for(unsigned int j=0;j<weights.size();++j) {
	    std::string c = correctors.at(j);
	    if(parser.integerValue("barrelEndcap")>0) {
	    if(fabs(eta)<1.442)
	      c+="EB";
	    else
	      c+="EE";
	    }
	    TF1* correctorr = (TF1*) corrs->Get(c.c_str());
	    weight+=weights[j]*correctorr->Eval(p);
	  }

	  newBranch->Fill();
	}

      t->Write("",TObject::kOverwrite);
    }
  }
}
