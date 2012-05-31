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


  TH1F *denom = f->Get("tauFakeRateMC"+postfix+"/ref"+var2); 
  TH1F *dm = f->Get("tauFakeRateMC"+postfix+"/decayModeFinding"+var); 
  TH1F *vl = f->Get("tauFakeRateMC"+postfix+"/byVLooseIsolation"+var); 
  TH1F *l = f->Get("tauFakeRateMC"+postfix+"/byLooseIsolation"+var); 
  TH1F *m = f->Get("tauFakeRateMC"+postfix+"/byMediumIsolation"+var); 
  TH1F *t = f->Get("tauFakeRateMC"+postfix+"/byTightIsolation"+var); 

  TGraphAsymmErrors * eff_dm = new TGraphAsymmErrors;
  
  // eff_dm->Divide(dm,denom);
  // formatObject(eff_dm,kRed,20);

  // eff_dm->Draw("AP");
  // eff_dm->GetYaxis()->SetTitle(ytitle);
  // eff_dm->GetXaxis()->SetTitle(xtitle);
  // eff_dm->GetYaxis()->SetRangeUser(min,max);
  

  TGraphAsymmErrors * eff_vl = new TGraphAsymmErrors;
  eff_vl->Divide(vl,dm);
  formatObject(eff_vl,kBlue,21);
  eff_vl->Draw("AP");

  TGraphAsymmErrors * eff_l = new TGraphAsymmErrors;
  eff_l->Divide(l,dm);
  formatObject(eff_l,kMagenta,22);
  eff_l->Draw("Psame");

  TGraphAsymmErrors * eff_m = new TGraphAsymmErrors;
  eff_m->Divide(m,dm);
  formatObject(eff_m,kGreen,23);

  eff_m->Draw("Psame");

  TGraphAsymmErrors * eff_t = new TGraphAsymmErrors;
  eff_t->Divide(t,dm);
  formatObject(eff_t,kBlack,24);
  eff_t->Draw("Psame");

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
