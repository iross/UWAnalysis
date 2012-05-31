
void makePretty(TGraphErrors * g,Color_t color,Int_t marker) {
  g->SetMarkerStyle(marker);
  g->SetMarkerColor(color);
  g->SetLineColor(color);
  g->SetLineWidth(2);
}


void makeRecoilPlots()
{
  TFile *f1 = TFile::Open("sandbox/recoil/MET_DATA.root");
  TFile *f2 = TFile::Open("sandbox/recoil/MET_MC.root");
  
  

  TGraphErrors * U1_resp_data = (TGraphErrors*)f1->Get("U1s_resp");
  TGraphErrors * U2_resp_data = (TGraphErrors*)f1->Get("U2s_resp");
  TGraphErrors * U1_res_data = (TGraphErrors*)f1->Get("U1s_res");
  TGraphErrors * U2_res_data = (TGraphErrors*)f1->Get("U2s_res");


  TGraphErrors * U1_resp_mc = (TGraphErrors*)f2->Get("U1s_resp");
  TGraphErrors * U2_resp_mc = (TGraphErrors*)f2->Get("U2s_resp");
  TGraphErrors * U1_res_mc = (TGraphErrors*)f2->Get("U1s_res");
  TGraphErrors * U2_res_mc = (TGraphErrors*)f2->Get("U2s_res");



  makePretty(U1_resp_data,kRed,20);
  makePretty(U1_resp_mc,kBlue,21);

  makePretty(U2_resp_data,kRed,20);
  makePretty(U2_resp_mc,kBlue,21);


  makePretty(U1_res_data,kRed,20);
  makePretty(U1_res_mc,kBlue,21);

  makePretty(U2_res_data,kRed,20);
  makePretty(U2_res_mc,kBlue,21);

  TLegend *l = new TLegend(0.6,0.6,0.9,0.8);
  l->AddEntry(U1_resp_data,"DATA","lp");
  l->AddEntry(U1_resp_mc,"Simulation","lp");
  l->SetBorderSize(0);
  l->SetFillColor(0);


  TCanvas *c1 = new TCanvas("c1");
  c1->cd();
  U1_resp_data->Draw("AP");
  U1_resp_data->GetXaxis()->SetTitle("Z p_{T}[GeV/c]");
  U1_resp_data->GetYaxis()->SetTitle("U_{1} response [GeV]");
  U1_resp_mc->Draw("Psame");
  l->Draw();

  TCanvas *c2 = new TCanvas("c2");
  c2->cd();
  U2_resp_data->Draw("AP");
  U2_resp_data->GetXaxis()->SetTitle("Z p_{T}[GeV/c]");
  U2_resp_data->GetYaxis()->SetTitle("U_{2} response [GeV]");
  U2_resp_mc->Draw("Psame");
  l->Draw();


  TCanvas *cc1 = new TCanvas("cc1");
  cc1->cd();
  U1_res_data->Draw("AP");
  U1_res_data->GetXaxis()->SetTitle("Z p_{T}[GeV/c]");
  U1_res_data->GetYaxis()->SetTitle("U_{1} resolution [GeV]");
  U1_res_mc->Draw("Psame");
  l->Draw();


  TCanvas *cc2 = new TCanvas("cc2");
  cc2->cd();
  U2_res_data->Draw("AP");
  U2_res_data->GetXaxis()->SetTitle("Z p_{T}[GeV/c]");
  U2_res_data->GetYaxis()->SetTitle("U_{2} resolution [GeV]");
  U2_res_mc->Draw("Psame");
  l->Draw();
  


}
