void makeSetOfPlots(TFile *f, TString postfix,float min,float max,bool log,TString canvasName="")
{
  TCanvas *c = new TCanvas("c_"+postfix+canvasName,"a",400,400);
  c->cd();

  TH1F *denom = f->Get("tauFakeRateMC"+postfix+"/refPt"); 
  TH1F *dm = f->Get("tauFakeRateMC"+postfix+"/leadingTrackFindingpt"); 
  TH1F *vl = f->Get("tauFakeRateMC"+postfix+"/byVLooseIsolationpt"); 
  TH1F *l = f->Get("tauFakeRateMC"+postfix+"/byLooseIsolationpt"); 
  TH1F *m = f->Get("tauFakeRateMC"+postfix+"/byMediumIsolationpt"); 
  TH1F *t = f->Get("tauFakeRateMC"+postfix+"/byTightIsolationpt"); 

  TGraphAsymmErrors * eff_dm = new TGraphAsymmErrors;
  eff_dm->Divide(dm,denom);
  eff_dm->Draw("AP");
  eff_dm->GetYaxis()->SetRangeUser(min,max);



  TGraphAsymmErrors * eff_vl = new TGraphAsymmErrors;
  eff_vl->Divide(vl,denom);
  eff_vl->Draw("Psame");

  TGraphAsymmErrors * eff_l = new TGraphAsymmErrors;
  eff_l->Divide(l,denom);
  eff_l->Draw("Psame");

  TGraphAsymmErrors * eff_m = new TGraphAsymmErrors;
  eff_m->Divide(m,denom);
  eff_m->Draw("Psame");

  TGraphAsymmErrors * eff_t = new TGraphAsymmErrors;
  eff_t->Divide(t,denom);
  eff_t->Draw("Psame");

  if(log)
    c->SetLogy();

  return c;

}


makeEffPlots(TString file,TString plot,bool log = false, float min = 0.001, float max = 1.0,TString canvasName = "")
{
  TFile * f = TFile::Open(file);

  TCanvas *c1 = makeSetOfPlots(f, plot,min,max,log,canvasName);


  f->Close();

}
