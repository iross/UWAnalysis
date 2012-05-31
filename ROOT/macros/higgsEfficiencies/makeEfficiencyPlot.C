double efficiency(TFile * f, TString h);

void makeEfficiencyPlot(TString  file) {
  TFile *f = new TFile(file);
  
  const int N=14;

  float mass[] = {90.,100.,120.,130.,140.,160.,180.,200.,250.,300.,350.,400.,450.,500.};
  TString GGH[] = {"GGH90","GGH100","GGH120","GGH130","GGH140","GGH160","GGH180","GGH200","GGH250","GGH300","GGH350","GGH400","GGH450","GGH500"};
  TString BBA[] = {"BBA90","BBA100","BBA120","BBA130","BBA140","BBA160","BBA180","BBA200","BBA250","BBA300","BBA350","BBA400","BBA450","BBA500"};

  float ggh[14];
  float bba[14];

  for(unsigned int i=0;i<14;++i) {
    ggh[i] = efficiency(f,GGH[i]);
    bba[i] = efficiency(f,BBA[i]);
  }

  TGraph *bbaG = new TGraph(N,mass,bba);
  TGraph *gghG = new TGraph(N,mass,ggh);

  bbaG->SetMarkerColor(kRed);
  bbaG->SetLineColor(kRed);
  gghG->SetLineWidth(2);
  bbaG->SetMarkerStyle(20);
  bbaG->SetMarkerSize(1.0);

  gghG->SetMarkerColor(kBlack);
  gghG->SetLineColor(kBlack);
  gghG->SetLineStyle(2);
  gghG->SetLineWidth(2);
  gghG->SetMarkerStyle(21);
  gghG->SetMarkerSize(1.0);

  bbaG->GetXaxis()->SetTitle("m(A) [GeV/c^{2}]"); 
  bbaG->GetYaxis()->SetTitle("Acceptance x Efficiency"); 

  bbaG->Draw("APL");
  gghG->Draw("PLsame");

  TLegend *l = new TLegend(0.3,0.3,0.5,0.5);
  l->AddEntry(bbaG,"gg#rightarrow bb#Phi #rightarrow #tau #tau","lp");
  l->AddEntry(gghG,"gg#rightarrow #Phi #rightarrow #tau #tau","lp");
  l->SetBorderSize(0);
  l->SetFillColor(kWhite);
  l->SetFillStyle(0);


  l->Draw();

  

}


double efficiency(TFile * f, TString h)
{
  TH1F * histo = (TH1F*)f->Get(h);
  return histo->Integral();
}
