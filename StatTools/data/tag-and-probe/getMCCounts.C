getMCCounts(TString fileName,TString treeName,TString preselection,TString selection,TString w = "__WEIGHT__")
{
  TFile *f =TFile::Open(fileName);
  TTree *t = (TTree*)f->Get(treeName);

  TH1D *n = new TH1D("n","n",1,1.,2.);
  TH1D *d = new TH1D("d","d",1,1.,2.);

  float entries = (float)t->GetEntries(preselection);

  t->Draw("1.5>>d",w+"*"+preselection);
  t->Draw("1.5>>n",w+"*"++selection);

  n->Scale(entries);
  d->Scale(entries);
  
  float eff = n->Integral()/d->Integral();
  printf("Eff = %f +- %f\n",eff,sqrt(eff*(1-eff)/entries));
  




}
