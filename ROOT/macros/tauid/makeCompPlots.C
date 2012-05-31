void formatObject(TGraphAsymmErrors* g , Color_t color, int marker) {
  g->SetMarkerColor(color);
  g->SetMarkerStyle(marker);
}


void makeSetOfPlots(TFile *f, TString postfix,TString var, float min,float max,bool log,TString canvasName="",TString xtitle = " ref object p_{T}" , TString ytitle = "Efficiency")
{
  TCanvas *c = new TCanvas("c_"+postfix+canvasName,"a",400,400);
  c->cd();
  
  TString var2;
  if(var=="pt") var2 = "Pt";
  if(var=="vertices") var2 = "Vertices";


  TH1F *denom = f->Get("tauFakeRateMCeffthr15/ref"+var2); 
  TH1F *vl = f->Get("tauFakeRateMCeffthrPU15/byVLooseIsolationBeta"+var); 
  // TH1F *l = f->Get("tauFakeRateMCeffthr15/byVLooseIsolation"+var); 
  // TH1F *m = f->Get("tauFakeRateMCeffthrPU15/byLooseIsolationBeta"+var); 
  // TH1F *t = f->Get("tauFakeRateMCeffthr15/byLooseIsolation"+var); 


  TGraphAsymmErrors * eff_vl = new TGraphAsymmErrors;
  eff_vl->Divide(vl,denom);
  formatObject(eff_vl,kBlue,21);
  eff_vl->Draw("Psame");

  // TGraphAsymmErrors * eff_l = new TGraphAsymmErrors;
  // eff_l->Divide(l,denom);
  // formatObject(eff_l,kMagenta,22);
  // eff_l->Draw("Psame");

  // TGraphAsymmErrors * eff_m = new TGraphAsymmErrors;
  // eff_m->Divide(m,denom);
  // formatObject(eff_m,kGreen,23);

  // eff_m->Draw("Psame");

  // TGraphAsymmErrors * eff_t = new TGraphAsymmErrors;
  // eff_t->Divide(t,denom);
  // formatObject(eff_t,kBlack,24);
  // eff_t->Draw("Psame");

  if(log)
    c->SetLogy();

  return c;

}


makeEffPlots(TString file,TString plot,TString post = "pt", bool log = false, float min = 0.001, float max = 1.0,TString canvasName = "")
{
  TFile * f = TFile::Open(file);

  TCanvas *c1 = makeSetOfPlots(f, plot,post,min,max,log,canvasName);


  f->Close();

}
