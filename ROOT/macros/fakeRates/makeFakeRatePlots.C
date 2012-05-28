{
  TFile * fD = new TFile("sandbox/ztt-latest/DATA.root");
  TFile * fM = new TFile("sandbox/ztt-latest/QCD.root");
  TFile * fW = new TFile("sandbox/ztt-latest/WMN.root");


  TH1F *d_m_ref = (TH1F*)fD->Get("tauFakeRateMuEnriched/refPt");
  TH1F *d_m_dm = (TH1F*)fD->Get("tauFakeRateMuEnriched/leadingTrackFindingpt");
  TH1F *d_m_li = (TH1F*)fD->Get("tauFakeRateMuEnriched/byLooseIsolationpt");

  TH1F *d_w_ref = (TH1F*)fD->Get("tauFakeRatewJets/refPt");
  TH1F *d_w_dm = (TH1F*)fD->Get("tauFakeRatewJets/leadingTrackFindingpt");
  TH1F *d_w_li = (TH1F*)fD->Get("tauFakeRatewJets/byLooseIsolationpt");

  TH1F *w_w_ref = (TH1F*)fW->Get("tauFakeRatewJets/refPt");
  TH1F *w_w_dm = (TH1F*)fW->Get("tauFakeRatewJets/leadingTrackFindingpt");
  TH1F *w_w_li = (TH1F*)fW->Get("tauFakeRatewJets/byLooseIsolationpt");

  TH1F *m_m_ref = (TH1F*)fM->Get("tauFakeRateMuEnriched/refPt");
  TH1F *m_m_dm = (TH1F*)fM->Get("tauFakeRateMuEnriched/leadingTrackFindingpt");
  TH1F *m_m_li = (TH1F*)fM->Get("tauFakeRateMuEnriched/byLooseIsolationpt");


  TGraphAsymmErrors *d_m_fr_dm = new TGraphAsymmErrors();
  d_m_fr_dm->BayesDivide(d_m_dm,d_m_ref);
  TGraphAsymmErrors *d_m_fr_li = new TGraphAsymmErrors();
  d_m_fr_li->BayesDivide(d_m_li,d_m_ref);

  TGraphAsymmErrors *d_w_fr_dm = new TGraphAsymmErrors();
  d_w_fr_dm->BayesDivide(d_w_dm,d_w_ref);
  TGraphAsymmErrors *d_w_fr_li = new TGraphAsymmErrors();
  d_w_fr_li->BayesDivide(d_w_li,d_w_ref);

  TGraphAsymmErrors *m_m_fr_dm = new TGraphAsymmErrors();
  m_m_fr_dm->BayesDivide(m_m_dm,m_m_ref);
  TGraphAsymmErrors *m_m_fr_li = new TGraphAsymmErrors();
  m_m_fr_li->BayesDivide(m_m_li,m_m_ref);

  TGraphAsymmErrors *w_w_fr_dm = new TGraphAsymmErrors();
  w_w_fr_dm->BayesDivide(w_w_dm,w_w_ref);
  TGraphAsymmErrors *w_w_fr_li = new TGraphAsymmErrors();
  w_w_fr_li->BayesDivide(w_w_li,w_w_ref);


  TCanvas * c1 = new TCanvas("c1","Mu Enriched Fake Rate",400,400);

  d_m_fr_dm->GetYaxis()->SetRangeUser(0.001,1.);
  d_m_fr_dm->GetYaxis()->SetTitle("Background Efficiency");
  d_m_fr_dm->GetXaxis()->SetTitle("PF Jet p_{T} [GeV/c] ");
  d_m_fr_dm->SetMarkerColor(kRed);
  d_m_fr_dm->SetMarkerStyle(20);
  d_m_fr_dm->Draw("AP");
  m_m_fr_dm->SetMarkerColor(kBlue);
  m_m_fr_dm->SetMarkerStyle(20);
  m_m_fr_dm->Draw("Psame");
  d_m_fr_li->SetMarkerColor(kRed);
  d_m_fr_li->SetMarkerStyle(21);
  d_m_fr_li->Draw("Psame");
  m_m_fr_li->SetMarkerColor(kBlue);
  m_m_fr_li->SetMarkerStyle(21);
  m_m_fr_li->Draw("Psame");

  TLegend *l = new TLegend(0.4,0.4,0.6,0.6);
  l->AddEntry(d_m_fr_dm,"Decay Mode Finding(DATA)","p");
  l->AddEntry(m_m_fr_dm,"Decay Mode Finding(MC)","p");
  l->AddEntry(d_m_fr_li,"Loose Isolation(DATA)","p");
  l->AddEntry(m_m_fr_li,"Loose Isolation(MC)","p");
  l->Draw();

  c1->Draw();


  TCanvas * c2 = new TCanvas("c2","@+jets Fake Rate",400,400);

  d_w_fr_dm->GetYaxis()->SetRangeUser(0.001,1.);
  d_w_fr_dm->GetYaxis()->SetTitle("Background Efficiency");
  d_w_fr_dm->GetXaxis()->SetTitle("PF Jet p_{T} [GeV/c] ");
  d_w_fr_dm->SetMarkerColor(kRed);
  d_w_fr_dm->SetMarkerStyle(20);
  d_w_fr_dm->Draw("AP");
  w_w_fr_dm->SetMarkerColor(kBlue);
  w_w_fr_dm->SetMarkerStyle(20);
  w_w_fr_dm->Draw("Psame");
  d_w_fr_li->SetMarkerColor(kRed);
  d_w_fr_li->SetMarkerStyle(21);
  d_w_fr_li->Draw("Psame");
  w_w_fr_li->SetMarkerColor(kBlue);
  w_w_fr_li->SetMarkerStyle(21);
  w_w_fr_li->Draw("Psame");

  TLegend *ll = new TLegend(0.4,0.4,0.6,0.6);
  ll->AddEntry(d_w_fr_dm,"Decay Mode Finding(DATA)","p");
  ll->AddEntry(w_w_fr_dm,"Decay Mode Finding(MC)","p");
  ll->AddEntry(d_w_fr_li,"Loose Isolation(DATA)","p");
  ll->AddEntry(w_w_fr_li,"Loose Isolation(MC)","p");
  ll->Draw();

  c1->Draw();




  //numbers
  
  TH1F *m_m_sum = (TH1F*)fM->Get("tauFakeRateMuEnriched/rawSummary");
  TH1F *m_d_sum = (TH1F*)fD->Get("tauFakeRateMuEnriched/rawSummary");

  TH1F *w_m_sum = (TH1F*)fW->Get("tauFakeRatewJets/rawSummary");
  TH1F *w_d_sum = (TH1F*)fD->Get("tauFakeRatewJets/rawSummary");

  float effmm = m_m_sum->GetBinContent(5)/m_m_sum->GetBinContent(1);
  float deffmm = sqrt(effmm*(1-effmm)/m_m_sum->GetBinContent(1));

  float effmd = m_d_sum->GetBinContent(5)/m_d_sum->GetBinContent(1);
  float deffmd = sqrt(effmd*(1-effmd)/m_d_sum->GetBinContent(1));

  float effwm = w_m_sum->GetBinContent(5)/w_m_sum->GetBinContent(1);
  float deffwm = sqrt(effwm*(1-effwm)/w_m_sum->GetBinContent(1));

  float effwd = w_d_sum->GetBinContent(5)/w_d_sum->GetBinContent(1);
  float deffwd = sqrt(effwd*(1-effwd)/w_d_sum->GetBinContent(1));



  printf(" Muon Enriched MC = %f  +-%f\n" ,effmm,deffmm );
  printf(" Muon Enriched DATA = %f +-%f \n" ,effmd,deffmd );
  printf(" rho = %f +-%f \n" ,effmd/effmm,(effmd/effmm)*sqrt(deffmm*deffmm/(effmm*effmm)+deffmd*deffmd/(effmd*effmd) ));

  printf(" W Enriched MC = %f +-%f \n" ,effwm,deffwm );
  printf(" W Enriched DATA = %f +-%f \n" ,effwd,deffwd );
  printf(" rho = %f +-%f \n" ,effwd/effwm,(effwd/effwm)*sqrt(deffwm*deffwm/(effwm*effwm)+deffwd*deffwd/(effwd*effwd) ));

  





}
