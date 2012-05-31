#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "RooWorkspace.h"
#include "RooRealVar.h"
#include "RooAbsPdf.h"


void readdir(TDirectory *dir,optutl::CommandLineParser parser,RooWorkspace * w); 



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("mvaFile",optutl::CommandLineParser::kString,"MVA file");
   parser.addOption("vars",optutl::CommandLineParser::kStringVector,"variables");
   parser.addOption("signalPdfs",optutl::CommandLineParser::kStringVector,"signalPdfs");
   parser.addOption("bkgPdfs",optutl::CommandLineParser::kStringVector,"background Pdfs");
   parser.addOption("mvaName",optutl::CommandLineParser::kString,"mvaName","mva");

   parser.parseArguments (argc, argv);

   TFile * fin = new TFile(parser.stringValue("mvaFile").c_str());
   RooWorkspace *w = (RooWorkspace*) fin->Get("w");
 
   TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");


   readdir(f,parser,w);
   f->Close();

} 


void readdir(TDirectory *dir,optutl::CommandLineParser parser, RooWorkspace *w) 
{
   std::vector<std::string> vars = parser.stringVector("vars");
   std::vector<std::string> signalPdfs = parser.stringVector("signalPdfs");
   std::vector<std::string> bkgPdfs = parser.stringVector("bkgPdfs");
   std::string mvaName = parser.stringValue("mvaName");


  TDirectory *dirsav = gDirectory;
  TIter next(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)next())) {
    printf("Found key=%s \n",key->GetName());
    TObject *obj = key->ReadObj();

    if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
      dir->cd(key->GetName());
      TDirectory *subdir = gDirectory;
      readdir(subdir,parser,w);
      dirsav->cd();
    }
    else if(obj->IsA()->InheritsFrom(TTree::Class())) {
      TTree *t = (TTree*)obj;

      bool treeIsOK=true;
      float val[100];
      float mva=0.0;
      for(unsigned i=0;i<100;++i)
	val[i]=0.0;
      for(unsigned int i=0;i<vars.size();++i) {
	if(t->GetBranch(vars[i].c_str())==0)
	  treeIsOK=false;
	else
	  t->SetBranchAddress(vars[i].c_str(),&val[i]);
      }
      TBranch *newBranch = t->Branch(mvaName.c_str(),&mva,(mvaName+"/F").c_str());

      printf("Found tree -> weighting\n");
      if(treeIsOK) {
	for(Int_t i=0;i<t->GetEntries();++i)
	  {
	    
	    t->GetEntry(i);
	    //add the input
	    RooArgSet observables;
	    for(unsigned int j=0;j<vars.size();++j) {
	      w->var(vars[j].c_str())->setVal(val[j]);
	      observables.add(*w->var(vars[j].c_str()));
	    }
	    float LS = 0.0;
	    float LB = 0.0;

	    for(unsigned int j=0;j<signalPdfs.size();++j) {
	      float vall=1.0;
	      for(unsigned int k=0;k<vars.size();++k) {
		RooArgSet set;
		set.add(*w->var(vars[k].c_str()));
		vall*=w->pdf((signalPdfs[j]+"_"+vars[k]).c_str())->getVal();
		if(i==1) 
		  printf("sig=%f %f\n",w->pdf((signalPdfs[j]+"_"+vars[k]).c_str())->getVal(),w->pdf((signalPdfs[j]+"_"+vars[k]).c_str())->getNorm());

	      }
	      LS+=vall;
	    }
	    for(unsigned int j=0;j<bkgPdfs.size();++j) {
	      float vall=1.0;
	      for(unsigned int k=0;k<vars.size();++k) {
		RooArgSet set;
		set.add(*w->var(vars[k].c_str()));
		if(i==1) 
		  printf("bkg=%f %f\n",w->pdf((bkgPdfs[j]+"_"+vars[k]).c_str())->getVal(),w->pdf((bkgPdfs[j]+"_"+vars[k]).c_str())->getNorm());

		vall*=w->pdf((bkgPdfs[j]+"_"+vars[k]).c_str())->getVal();
	      }
	      LB+=vall;
	    }
	    if(i==1) 
	      printf("Ls=%f,Lb = %f \n",LS,LB);

	    mva = LS/(LS+LB);
	    newBranch->Fill();
	  }
	t->Write("",TObject::kOverwrite);
      }
    }
//     else if(obj->IsA()->InheritsFrom(TH1F::Class())) {
//       TH1F *h = (TH1F*)obj;
//       h->Sumw2();
//       printf("scaling histogram with %f entries\n",h->Integral());
//       float weight = parser.doubleValue("weight")/(ev);
//       h->Sumw2();
//       for( int i=1;i<=h->GetNbinsX();++i)
// 	h->SetBinContent(i,h->GetBinContent(i)*weight);
 
//       TDirectory *tmp = gDirectory;
//       h->SetDirectory(gDirectory);
//       h->Write("resultsWeighted");
//     }


  }

}
