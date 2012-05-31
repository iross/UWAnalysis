#include "UWAnalysis/ROOT/interactive/bandUtils.cxx"



#include <TCanvas.h>
#include <TLegend.h>
#include <TLine.h>
#include <TGraphAsymmErrors.h>
#include <TH1F.h>
#include <TFile.h>
#include <TLatex.h>


void doBands(TString inputFile,TString name) {
  TFile *f = new TFile("bands.root","UPDATE");
  f->cd();
  makeBands(f,name,inputFile);
  f->Close();
}


class LimitPlotter {

 public:
  LimitPlotter() {
    c = new TCanvas("c","c",600,450);
    c->cd();
  }

  void addMSSMFrame() {
  TH1F *frame = c->DrawFrame(90.,0.01,500.,500.);
  frame->GetXaxis()->SetTitle("m_{A} [GeV]");
  frame->GetYaxis()->SetTitle("#sigma 95 % CL [pb]");
  frame->Draw();
    l = new TLegend(0.6,0.6,0.9,0.9);

}  

  void addSMFrame() {
  TH1F *frame = c->DrawFrame(110.,0.01,145.,20.);
  frame->GetXaxis()->SetTitle("m_{H} [GeV]");
  frame->GetYaxis()->SetTitle("#sigma 95 % CL / #sigma_{SM}");
  frame->Draw();

    l = new TLegend(0.6,0.6,0.9,0.75);
}  

  void addPValueFrame(float min = 90.,float max = 500.) {
  TH1F *frame = c->DrawFrame(min,1e-7,max,0.5);
  frame->GetXaxis()->SetTitle("m_{H} [GeV]");
  frame->GetYaxis()->SetTitle("background p-value");
  frame->Draw();

  l = new TLegend(0.7,0.2,0.9,0.4);
  
  }

  void addLine(TString file,TString name,TString legend,Color_t color,Int_t linestyle = 0,Int_t linewidth = 3) 
  {
    TFile * f = new TFile(file);
    TGraphAsymmErrors *obs = (TGraphAsymmErrors*)f->Get(name);
    obs->SetLineColor(color);
    obs->SetLineStyle(linestyle);
    obs->SetLineWidth(linewidth);
    obs->Draw("LXsame");
    if(legend!="") {
      l->AddEntry(obs,legend,"l");
    }
  }


  void addBand(TString file,TString name,TString expected = "Expected(CLs)",TString observed = "Observed CLs") 
  {
    TFile * f = new TFile(file);
    TGraphAsymmErrors *b95 = (TGraphAsymmErrors*)f->Get(name+"_median_95");
    b95->SetTitle("");
    b95->SetFillColor(kYellow);
    b95->SetLineWidth(3);
    b95->SetMarkerSize(1.5);
    b95->Draw("3");
    TGraphAsymmErrors  *b68 = (TGraphAsymmErrors*)f->Get(name+"_median");
    b68->SetTitle("");
    b68->SetFillColor(kGreen);
    b68->SetLineWidth(3);
    b68->SetLineStyle(5);
    b68->Draw("3same");
    b68->Draw("LXsame");
    b95->GetYaxis()->Draw("same");
    l->AddEntry(b95,expected,"lpf");
    addLine(file,name+"_obs",observed,kBlack,0,4);
  }

  void addSMLine() {
    TLine *a = new TLine(110.,1.,145.,1.);
    a->SetLineColor(kBlack);
    a->SetLineWidth(3);
    a->Draw();
  }

  void addPValueLines(float min, float max) {
    TLine *l1 = new TLine(min,0.158655,max,0.158655);
    TLine *l2 = new TLine(min,2.27501319481792155e-02,max,2.27501319481792155e-02);
    TLine *l3 = new TLine(min,1.34989803163009588e-03,max,1.34989803163009588e-03);
    TLine *l4 = new TLine(min,3.16712418331199785e-05,max,3.16712418331199785e-05);
    TLine *l5 = new TLine(min,2.86651571879194494e-07,max,2.86651571879194494e-07);

    l1->SetLineColor(kRed);
    l2->SetLineColor(kRed);
    l3->SetLineColor(kRed);
    l4->SetLineColor(kRed);
    l5->SetLineColor(kRed);

    l1->SetLineWidth(3);
    l2->SetLineWidth(3);
    l3->SetLineWidth(3);
    l4->SetLineWidth(3);
    l5->SetLineWidth(3);


    l1->SetLineStyle(4);
    l2->SetLineStyle(4);
    l3->SetLineStyle(4);
    l4->SetLineStyle(4);
    l5->SetLineStyle(4);

    l1->Draw();
    l2->Draw();
    l3->Draw();
    l4->Draw();
    l5->Draw();

    TLatex *t1 = new TLatex(max+15,0.158655,"1 #sigma");
    t1->SetTextColor(kRed);
    t1->Draw();

    TLatex *t2 = new TLatex(max+15,2.27501319481792155e-02,"2 #sigma");
    t2->SetTextColor(kRed);
    t2->Draw();

    TLatex *t3 = new TLatex(max+15,1.34989803163009588e-03,"3 #sigma");
    t3->SetTextColor(kRed);
    t3->Draw();

    TLatex *t4 = new TLatex(max+15,3.16712418331199785e-05,"4 #sigma");
    t4->SetTextColor(kRed);
    t4->Draw();

    TLatex *t5 = new TLatex(max+15,2.86651571879194494e-07,"5 #sigma");
    t5->SetTextColor(kRed);
    t5->Draw();


  }

  void DrawAll(bool log = true) {

    l->SetBorderSize(0);
     l->SetFillColor(0);
     l->SetFillStyle(0);

    l->Draw();

    if(log) {
      c->SetLogy();
    }

    c->Draw();



  }

  void Save(TString name) {
    c->SaveAs(name+".png");
    c->SaveAs(name+".pdf");
    c->SaveAs(name+".root");
  }


 private:
  TCanvas *c ;
  TLegend *l ;

};
