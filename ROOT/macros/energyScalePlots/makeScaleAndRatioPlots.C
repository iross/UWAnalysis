makeScaleAndRatioPlots(TString lepton1,TString lepton2,TString mass,TString systematic,TString histogram,float min = 30 ,float max = 100., TString var = "visible Mass [GeV/c^{2}]",float rmin = 0.5 ,float rmax = 1.5  )
{

  gStyle->SetOptTitle(0);

  TString fileNameNominal = lepton1+"-"+lepton2+"-"+mass+"-nominal.root";
  TString fileNameUp      = lepton1+"-"+lepton2+"-"+mass+"-"+systematic+"Up.root";
  TString fileNameDown      = lepton1+"-"+lepton2+"-"+mass+"-"+systematic+"Down.root";


  TFile *fnominal = new TFile(fileNameNominal);
  TFile *fup = new TFile(fileNameUp);  
  TFile *fdown = new TFile(fileNameDown);

  TH1F * nominal =(TH1F*)fnominal->Get(histogram);
  TH1F * up =(TH1F*)fup->Get(histogram);
  TH1F * down =(TH1F*)fdown->Get(histogram);

  nominal->Scale(1./nominal->Integral());
  up->Scale(1./up->Integral());
  down->Scale(1./down->Integral());


  TCanvas *c1 = new TCanvas("c","cc",400,400);
  c1->cd();

  nominal->GetXaxis()->SetRangeUser(min-20,max+40);


  nominal->SetLineColor(kBlack);
  nominal->SetLineWidth(3);
  //  nominal->SetLineStyle(2);
  nominal->SetMarkerSize(0);

  up->SetLineColor(kRed);
  up->SetLineWidth(3);
  up->SetLineStyle(2);
  up->SetMarkerSize(0);

  down->SetLineColor(kBlue);
  down->SetLineWidth(3);
  down->SetLineStyle(3);
  down->SetMarkerSize(0);


  nominal->GetXaxis()->SetTitle(var);
  nominal->GetYaxis()->SetTitle("a.u");
  nominal->DrawNormalized("HIST");
  up->DrawNormalized("HIST,SAME");
  down->DrawNormalized("HIST,SAME");

  

  TLegend *l = new TLegend(0.6,0.6,0.8,0.8);
  l->AddEntry(nominal,"Nominal");
  l->AddEntry(up,"1 #sigma up");
  l->AddEntry(down,"1 #sigma down");
  l->SetFillColor(0);
  l->Draw();
  
  c->SaveAs(lepton1+"-"+lepton2+"-"+mass+"shifts"+systematic+".png");
  c->SaveAs(lepton1+"-"+lepton2+"-"+mass+"shifts"+systematic+".pdf");


  TH1F * nominalR = nominal->Clone(); 
  TH1F * upR = up->Clone();
  TH1F * downR = down->Clone();
  
  nominalR->GetYaxis()->SetTitle("Shifted/ Nominal");

  nominalR->SetName("nominalR");
  upR->SetName("upR");
  downR->SetName("downR");

  upR->Divide(nominalR);
  downR->Divide(nominalR);
  nominalR->Divide(nominalR);


  TCanvas *c2 = new TCanvas("c2","cc2",400,400);
  c2->cd();

  nominalR->GetXaxis()->SetRangeUser(min,max);
  nominalR->GetYaxis()->SetRangeUser(rmin,rmax);
  nominalR->Draw("HIST");
  upR->Draw("HIST,SAME");
  downR->Draw("HIST,SAME");

  TLegend *l2 = new TLegend(0.2,0.6,0.4,0.8);
  l2->AddEntry(nominalR,"Nominal");
  l2->AddEntry(upR,"1 #sigma up");
  l2->AddEntry(downR,"1 #sigma down");
  l2->SetFillColor(0);
  l2->Draw();


  c2->SaveAs(lepton1+"-"+lepton2+"-"+mass+"shifts"+systematic+"R.png");
  c2->SaveAs(lepton1+"-"+lepton2+"-"+mass+"shifts"+systematic+"R.pdf");




}
