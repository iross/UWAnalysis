double efficiency(TString file, TString tree, TString preselection,TString selection);





void makeCutEfficiencyPlot(TString  tree, TString dir,TString selection,TString preselection) {

  const int N=14;

  TString ggHF[] = {"ggH90.root","ggH100.root","ggH120.root","ggH130.root","ggH140.root","ggH160.root","ggH180.root","ggH200.root","ggH250.root","ggH300.root","ggH350.root","ggH400.root","ggH450.root","ggH500.root"};
  TString bbAF[] = {"bbA90.root","bbA100.root","bbA120.root","bbA130.root","bbA140.root","bbA160.root","bbA180.root","bbA200.root","bbA250.root","bbA300.root","bbA350.root","bbA400.root","bbA450.root","bbA500.root"};
  float mass[] = {90.,100.,120.,130.,140.,160.,180.,200.,250.,300.,350.,400.,450.,500.};

  float ggh[14];
  float bba[14];

  for(unsigned int i=0;i<14;++i) {
    ggh[i] = efficiency(dir+"/"+ggHF[i],tree,preselection,selection);
    bba[i] = efficiency(dir+"/"+bbAF[i],tree,preselection,selection);

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
  bbaG->GetYaxis()->SetTitle("Efficiency"); 

  bbaG->Draw("APL");
  gghG->Draw("PLsame");

  TLegend *l = new TLegend(0.3,0.3,0.5,0.5);
  l->AddEntry(bbaG,"bbA #rightarrow #tau #tau","lp");
  l->AddEntry(gghG,"ggH #rightarrow #tau #tau","lp");
  l->SetBorderSize(0);
  l->SetFillColor(kWhite);
  l->SetFillStyle(0);


  l->Draw();

  

}


double efficiency(TString file,TString tree,  TString preselection,TString selection)
{
  TFile * f=  new TFile(file);
  TTree *t = (TTree*)f->Get(tree);

  float denominator = (float)t->GetEntries(preselection);
  float numerator   = (float)t->GetEntries(preselection+"&&"+selection);
  f->Close();
  return numerator/denominator;

}


