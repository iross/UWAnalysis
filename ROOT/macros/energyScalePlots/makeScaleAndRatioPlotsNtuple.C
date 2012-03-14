makeScaleDATAMCComparison(TString fileMC,TString fileDATA,TString cut,TString tree, TString syst,TString mcCut ="36*__WEIGHT__",int bins=20,float min = 30 ,float max = 100., TString var = "tauHadMass",TString label = "#tau Mass [GeV/c^{2}]",float rmin = 0.5 ,float rmax = 1.5)
{

  gStyle->SetOptTitle(0);

  //read files
  TFile *mc = TFile::Open(fileMC);
  TFile *d = TFile::Open(fileDATA);

  //read trees
  TTree * dataTree = (TTree*)d->Get(tree+"Nominal/eventTree");
  TTree * mcTreeNominal = (TTree*)mc->Get(tree+"Nominal/eventTree");
  TTree * mcTreeUp = (TTree*)mc->Get(tree+syst+"Up/eventTree");
  TTree * mcTreeDown = (TTree*)mc->Get(tree+syst+"Down/eventTree");
  
  TH1F * nominal = new TH1F("nominal","",bins,min,max);
  TH1F * up = new TH1F("up","",bins,min,max);
  TH1F * down = new TH1F("down","",bins,min,max);
  TH1F * data = new TH1F("data","",bins,min,max);

  data->Sumw2();
  up->Sumw2();
  down->Sumw2();
  nominal->Sumw2();

  dataTree->Draw(var+">>data",cut,"goff");

  mcTreeNominal->Draw("1.0*"+var+">>nominal","("+cut+")*"+mcCut,"goff");
  // mcTreeUp->Draw(var+">>up","("+cut+")*"+mcCut,"goff");
  // mcTreeDown->Draw(var+">>down","("+cut+")*"+mcCut,"goff");

  mcTreeNominal->Draw("1.06*"+var+">>up","("+cut+")*"+mcCut,"goff");
  mcTreeNominal->Draw("0.93*"+var+">>down","("+cut+")*"+mcCut,"goff");

  printf("Histograms filled\n");

  nominal->Scale(1./nominal->Integral());
  data->Scale(1./data->Integral());
  up->Scale(1./up->Integral());
  down->Scale(1./down->Integral());

  TCanvas *c1 = new TCanvas("c","cc",400,400);
  c1->cd();

  nominal->SetLineColor(kBlack);
  nominal->SetLineWidth(3);
  nominal->SetMarkerSize(0);

  up->SetLineColor(kRed);
  up->SetLineWidth(3);
  up->SetLineStyle(5);
  up->SetMarkerSize(0);

  down->SetLineColor(kBlue);
  down->SetLineWidth(3);
  down->SetLineStyle(7);
  down->SetMarkerSize(0);

  data->SetMarkerStyle(20);
  data->SetMarkerColor(kBlack);

  nominal->GetXaxis()->SetTitle(label);
  nominal->GetYaxis()->SetTitle("a.u");
  nominal->DrawNormalized("HIST");
  up->DrawNormalized("HIST,SAME");
  down->DrawNormalized("HIST,SAME");
  data->DrawNormalized("SAME");
 

  TLegend *l = new TLegend(0.6,0.6,0.8,0.8);
  l->AddEntry(nominal,"Nominal");
  l->AddEntry(up,"2 #sigma up");
  l->AddEntry(down,"2 #sigma down");
  l->AddEntry(data,"DATA");
  l->SetFillColor(0);
  l->SetBorderSize(0);
  l->Draw();

   TH1F * nominalR = nominal->Clone(); 
   TH1F * upR = up->Clone();
   TH1F * downR = down->Clone();
  
   nominalR->GetYaxis()->SetTitle("(MC-DATA)/DATA ");

   nominalR->SetName("nominalR");
   upR->SetName("upR");
   downR->SetName("downR");

   upR->Add(data,-1.);
   //   upR->Divide(data);
   downR->Add(data,-1.);
   //   downR->Divide(data);
   nominalR->Add(data,-1.);
   //   nominalR->Divide(data);


   TCanvas *c2 = new TCanvas("c2","cc2",400,400);
   c2->cd();

   nominalR->GetXaxis()->SetRangeUser(min,max);
   nominalR->GetYaxis()->SetRangeUser(rmin,rmax);
   nominalR->Draw("HIST");
   upR->Draw("HIST,SAME");
   downR->Draw("HIST,SAME");

   TLegend *l2 = new TLegend(0.2,0.6,0.4,0.8);
   l2->AddEntry(nominalR,"Nominal");
   l2->AddEntry(upR,"2 #sigma up");
   l2->AddEntry(downR,"2 #sigma down");
   l2->SetFillColor(0);
   l2->Draw();


  // c2->SaveAs(lepton1+"-"+lepton2+"-"+mass+"shifts"+systematic+"R.png");
  // c2->SaveAs(lepton1+"-"+lepton2+"-"+mass+"shifts"+systematic+"R.pdf");




}
