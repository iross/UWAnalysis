#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TProfile.h"
#include <vector>
#include <math.h>


class ShapeCreator {
public:
  ShapeCreator(TString filename , int bins, double min, double max ) 
  {
    bins_ = bins;
    min_ = min;
    max_ = max;

    f =  new TFile(filename,"recreate");
  }
  ~ShapeCreator() {}

  void close() {
    f->Close();
  }
  
  void makeShape(TString file, TString tree,TString var,TString preselection,TString weight,TString histoName,float norm = -1)
  {
    TFile *ff = new TFile(file);
    TTree *t = (TTree*)ff->Get(tree);
    f->cd();
    TH1F *h = new TH1F(histoName,histoName,bins_,min_,max_);
    h->Sumw2();
    t->Draw(var+">>"+histoName,"("+preselection+")*"+weight);
    if(norm>0.0)
      {
	h->Scale(norm/h->Integral());
      }

    h->Write();
    ff->Close();
  }


private:

  int bins_;
  double min_;
  double max_;

  TFile *f;

};
