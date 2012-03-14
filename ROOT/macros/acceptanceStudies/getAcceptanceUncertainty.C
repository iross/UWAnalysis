float getEvents(TFile* f, TString hist)
{
  TH1F *h = (TH1F*)f->Get(hist);
  return h->Integral();
} 


float getAcceptanceUncertainty(TString dir,TString l1, TString l2,TString syst,TString t)
{
  TFile *fN  = TFile::Open(dir+l1+"-"+l2+"-mvis-nominal.root");
  TFile *fU  = TFile::Open(dir+l1+"-"+l2+"-mvis-"+syst+"Up.root");
  TFile *fD  = TFile::Open(dir+l1+"-"+l2+"-mvis-"+syst+"Down.root");



  float r1 =fabs(getEvents(fU,t)-getEvents(fN, t))/getEvents(fN, t); 
  float r2 =fabs(getEvents(fD,t)-getEvents(fN, t))/getEvents(fN, t);

  
  printf("Unc = %f \%\n",TMath::Max(r1,r2)*100);
  return TMath::Max(r1,r2);
}

