{
  float  eff_hps[] = {0.242,0.359,0.494};
  float  eff_tanc[] = {0.353,0.475,0.574};
  float  eff_tanc_new[] = {0.238,0.370,0.477};

  float  eff_tdr[] = {0.4};

  float  fr_hps[] = {0.00094,0.00189,0.00468};
  float  fr_tanc[] = {0.00318,0.00603,0.0101};
  float  fr_tanc_new[] = {0.00088,0.00238,0.00477};




  float  fr_tdr[] = {0.02};

  TGraph *hps = new TGraph(3,eff_hps,fr_hps);
  TGraph *tanc = new TGraph(3,eff_tanc,fr_tanc);
  TGraph *tanc_new = new TGraph(3,eff_tanc_new,fr_tanc_new);
  TGraph *tdr = new TGraph(1,eff_tdr,fr_tdr);


  tdr->SetMarkerColor(kGreen);
  hps->SetMarkerColor(kRed);
  tanc->SetMarkerColor(kBlue);
  tanc_new->SetMarkerColor(kMagenta);

  hps->SetLineColor(kRed);
  tanc->SetLineColor(kBlue);
  tanc_new->SetLineColor(kMagenta);

  tdr->SetLineColor(kGreen);

  hps->SetLineWidth(2);
  tanc->SetLineWidth(2);
  tanc_new->SetLineWidth(2);
  tdr->SetLineWidth(2);


  hps->SetMarkerStyle(21);
  tanc->SetMarkerStyle(20);
  tanc_new->SetMarkerStyle(22);
  tdr->SetMarkerStyle(29);


  TLegend * l = new TLegend(0.4,0.4,0.6,0.6);
  l->AddEntry(hps,"HPS","P");
  l->AddEntry(tanc,"OLD TaNC","P");
  l->AddEntry(tanc_new,"NEW TaNC","P");
  l->AddEntry(tdr,"PTDR","P");

  hps->GetXaxis()->SetTitle("Signal Efficiency");
  hps->GetYaxis()->SetTitle("QCD Fake rate");

  hps->GetXaxis()->SetRangeUser(0.,0.8);

  tanc->Draw("APL");
  hps->Draw("PLSAME");
  tanc_new->Draw("PLSAME");
  tdr->Draw("PSAME");


  l->Draw("SAME");
}
