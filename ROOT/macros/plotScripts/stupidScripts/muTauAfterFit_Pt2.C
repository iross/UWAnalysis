#include <iostream>

#include <TH1F.h>
#include <TFile.h>
#include <TROOT.h>
#include <TString.h>
#include <TSystem.h>
#include <Rtypes.h>

#include <TAxis.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAttLine.h>
#include <TPaveText.h>

#include "HttStyles.h"

/*
  setup the example as follows:
  root -l 
  .L MitStyleRemix.cc++
  .L MitLimits/Higgs2Tau/test/exampleMonitorStyles.C++ 
  exampleMonitorStyles.C()
*/

// re-fill histograms (this is only a little helper for the example histogram)
TH1F* refill(TH1F* hin)
{
  TH1F* hout = (TH1F*)hin->Clone(); hout->Clear();
  for(int i=0; i<hout->GetNbinsX(); ++i){
    hout->SetBinContent(i+1, hin->GetBinContent(i+1));
    hout->SetBinError  (i+1, 0.);
  }
  return hout;
}

// rescale histograms according to fit
void rescale(TH1F* hin, unsigned int idx)
{
  double lumi                  = 1.0090; // +0.15 * 1.06
  double CMS_eff_m             = 1.0047; // +0.47 * 1.01
  double CMS_eff_t             = 0.9550; // -0.75 * 1.06 
  double CMS_scale_j           = 0.9696; // -0.76 * 0.96
  double CMS_htt_zttNorm       = 1.0318; // +1.06 * 1.03
  double CMS_htt_ttbarNorm     = 0.9337; // -0.65 * 1.102
  double CMS_htt_DiBosonNorm   = 0.2800; // -0.72 * 2.00
  double CMS_htt_QCDNorm       = 0.9952; // -0.08 * 1.06
  double CMS_htt_QCDSyst       = 1.0220; // +1.16 * 1.019
  double CMS_htt_WNorm         = 1.1906; // +0.41 * 0.535
  double CMS_htt_WSyst         = 1.0183; // +0.29 * 1.063
  double CMS_htt_ZJFake        = 0.9924; // -0.06 * 1.126
  double CMS_htt_ZLFake        = 1.0390; // +0.15 * 1.260
  double pdf_gg                = 1.0561; // +1.87 * 1.03
  double pdf_qqbar             = 1.0561; // +1.87 * 1.03
  double QCDScale_qqH          = 1.2244; // +1.87 * 1.12
  double QCDScale_ggH          = 1.0654; // +1.87 * 1.035
  double ueps                  = 1.0748; // +1.87 * 0.96

  switch(idx){
  case 1: //ZTT 
    hin->Scale(CMS_eff_m*CMS_eff_t*CMS_htt_zttNorm*CMS_scale_j); break;
  case 2: // QCD
    hin->Scale(CMS_htt_QCDNorm*CMS_htt_QCDSyst); break;
  case 3: // W
    hin->Scale(CMS_htt_WNorm*CMS_htt_WSyst*CMS_scale_j); break;
  case 4: // ZJ
    hin->Scale(CMS_eff_m*CMS_htt_zttNorm*CMS_htt_ZJFake*CMS_scale_j); break;
  case 5: // ZL
    hin->Scale(CMS_eff_m*CMS_htt_zttNorm*CMS_htt_ZLFake*CMS_scale_j); break;
  case 6: // TT
    hin->Scale(CMS_eff_t*CMS_eff_m*CMS_htt_ttbarNorm*CMS_scale_j); break;
  case 7: // VV
    hin->Scale(CMS_eff_t*CMS_eff_m*CMS_htt_DiBosonNorm*CMS_scale_j); break;
  case 8: // ggH
    hin->Scale(lumi*CMS_eff_t*CMS_eff_m*CMS_scale_j*pdf_gg*QCDScale_ggH*ueps); break;
  case 9: // qqH
    hin->Scale(lumi*CMS_eff_t*CMS_eff_m*CMS_scale_j*pdf_qqbar*QCDScale_qqH*ueps); break;
  default :
    std::cout << "error histograms not known?!?" << std::endl;
  }
}

// examples macro
void 
muTauAfterFit_Pt2(bool scaled = true, bool log = true)
{
  // defining the common canvas, axes pad styles
  SetStyle();

  // open example histogram file
  TFile* exampleFile = new TFile("more/muTauPT2.root");

  //load example histograms
  TH1F* data = (TH1F*)exampleFile->Get("muTau_X/data_obs");
  if(data) {InitHist(data, "#bf{#tau p_{T} [GeV]}", "#bf{Events}"); InitData(data);} else{std::cout << "can't find hitogram " << "muTau_X/data_obs" << std::endl;}

  TH1F* Fakes =  refill((TH1F*)exampleFile->Get("muTau_X/QCD"))              ; InitHist(Fakes, "", "", kMagenta-10, 1001);                   
  TH1F* EWK1  =  refill((TH1F*)exampleFile->Get("muTau_X/W"  ))              ; InitHist(EWK1 , "", "", kRed    + 2, 1001);
  TH1F* EWK2  =  refill((TH1F*)exampleFile->Get("muTau_X/ZJ" ))              ; InitHist(EWK2 , "", "", kRed    + 2, 1001);
  TH1F* EWK3  =  refill((TH1F*)exampleFile->Get("muTau_X/ZL" ))              ; InitHist(EWK3 , "", "", kRed    + 2, 1001);
  TH1F* EWK   =  refill((TH1F*)exampleFile->Get("muTau_X/VV" ))              ; InitHist(EWK  , "", "", kRed    + 2, 1001);
  TH1F* ttbar =  refill((TH1F*)exampleFile->Get("muTau_X/TT" ))              ; InitHist(ttbar, "", "", kBlue   - 8, 1001);
  TH1F* Ztt   =  refill((TH1F*)exampleFile->Get("muTau_X/ZTT"))              ; InitHist(Ztt  , "", "", kOrange - 4, 1001);
  TH1F* ggH   =  refill((TH1F*)exampleFile->Get("muTau_X/SM120" ))           ; InitSignal(ggH); ggH ->Scale(10*16.63*0.071*29.671/ggH ->Integral());
  TH1F* qqH   =  refill((TH1F*)exampleFile->Get("muTau_X/VBF120"))           ; InitSignal(qqH); qqH ->Scale(10*1.269*0.071* 2.147/qqH ->Integral());
 
  if(scaled){
    rescale(Fakes, 2); 
    rescale(EWK1 , 3); 
    rescale(EWK2 , 4); 
    rescale(EWK3 , 5); 
    rescale(EWK  , 7); 
    rescale(ttbar, 6); 
    rescale(Ztt  , 1);
    rescale(ggH  , 8); 
    rescale(qqH  , 9);  
  }
  if(log){
    qqH  ->Add(ggH  );
    Fakes->Add(qqH  );
    EWK1 ->Add(Fakes);
    EWK2 ->Add(EWK1 );
    EWK3 ->Add(EWK2 );
    EWK  ->Add(EWK3 );
    ttbar->Add(EWK  );
    Ztt  ->Add(ttbar);
  }
  else{
    EWK1 ->Add(Fakes);
    EWK2 ->Add(EWK1 );
    EWK3 ->Add(EWK2 );
    EWK  ->Add(EWK3 );
    ttbar->Add(EWK  );
    Ztt  ->Add(ttbar);
    ggH  ->Add(Ztt  );
    qqH  ->Add(ggH  );
  }
  // define canvas
  TCanvas *canv = MakeCanvas("canv", "histograms", 600, 600);

  canv->cd();
  if(log){
    canv->SetLogy(1);
    data->SetMinimum(5.0);
    data->SetMaximum(100000.);
  }
  else{
    data->SetMaximum(9000.);
  }
  data->SetNdivisions(505);
  data->Draw("e");

  if(log){
    Ztt->Draw("same");
    ttbar->Draw("same");
    EWK->Draw("same");
    Fakes->Draw("same");
    qqH->Draw("same");
  }
  else{
    qqH->Draw("same");
    Ztt->Draw("same");
    ttbar->Draw("same");
    EWK->Draw("same");
    Fakes->Draw("same");
  }
  data->Draw("esame");
  canv->RedrawAxis();

  CMSPrelim("#tau_{#mu}#tau_{h}", 0.45, 0.75);
  
  TLegend* leg = new TLegend(0.45, 0.45, 0.9, 0.75);
  SetLegendStyle(leg);
  leg->AddEntry(qqH  , "(10x) H#rightarrow#tau#tau" , "L" );
  leg->AddEntry(data , "Observed"                , "LP");
  leg->AddEntry(Ztt  , "Z#rightarrow#tau#tau"    , "F" );
  leg->AddEntry(ttbar, "t#bar{t}"                , "F" );
  leg->AddEntry(EWK  , "Electroweak"             , "F" );
  leg->AddEntry(Fakes, "QCD"                     , "F" );
  leg->Draw();

  TPaveText* mssm  = new TPaveText(0.78, 0.70, 0.90, 0.74, "NDC");
  mssm->SetBorderSize(   0 );
  mssm->SetFillStyle(    0 );
  mssm->SetTextAlign(   12 );
  mssm->SetTextSize ( 0.04 );
  mssm->SetTextColor(    1 );
  mssm->SetTextFont (   62 );
  mssm->AddText("m_{H}=120");
  mssm->Draw();

  if(log){
     canv->Print("mutau_Pt2_LOG.pdf"); 
     canv->Print("mutau_Pt2_LOG.png"); 

  }
}
