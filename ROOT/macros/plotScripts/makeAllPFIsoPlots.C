{
  gROOT->ProcessLine(".x UWAnalysis/ROOT/interactive/loadRooInteractiveLOCAL.C");
  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadPFIsoPlotter.C");

  std::string lumi="36";

  //SELECTION REQUIREMENTS

  std::string preselection= "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuPt1>15&&mumuPt2>15";


  std::string selectionSignal = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&(mumuChargeIso1+mumuNeutralIso1)/mumuPt1<0.2&&mumuPt1>20&&mumuPt2>15&&mumuCharge==0";

  std::string selectionBackground = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&(mumuChargeIso1+mumuNeutralIso1)/mumuPt1>0.3&&mumuPt1>15&&mumuPt2>15";




  std::string selectionSignalFinal = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&(mumuChargeIso1+mumuNeutralIso1)/mumuPt1<0.2&&mumuPt1>20&&mumuPt2>15&&mumuCharge==0&&mumuMass>75.&&mumuMass<115.";

  std::string selectionBackgroundFinal = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&(mumuChargeIso1+mumuNeutralIso1)/mumuPt1>0.3&&mumuPt1>15&&mumuPt2>15&&(mumuMass<70||mumuMass>115)";


  std::string selectionSignalMC = "__WEIGHT__*("+selectionSignalFinal+")";
  std::string selectionBackgroundMC = "__WEIGHT__*("+selectionBackgroundFinal+")";



  TCanvas *c1 = new TCanvas("c_pf_comparison","PF vs standard iso");
  c1->cd();
  

  TGraphErrors* data_pf_04_05_05 = data->rocCurve(*data, "(mumuChargeIso2+mumuNeutralIso2)/mumuPt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kYellow,1,"Prompt muon efficiency ","Non prompt muon efficiency","pf_04_05_05");

  TGraphErrors* data_standard = data->rocCurve(*data, "mumuRelStdIso2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kGreen,2,"Prompt muon efficiency ","Non prompt muon efficiency","standard");
 
  data_pf_04_05_05->Draw("3A");

  data->addLabel(c1,"CMS Preliminary 2010",0.5,0.05,0.04);
  data->addLabel(c1,"L_{int} = 36 pb^{-1}, #sqrt{s} = 7 TeV",0.5,0.045,0.04);

  data_pf_04_05_05->Draw("XLsame");
  data_standard->Draw("3same");
  data_standard->Draw("XLsame");

  TLegend *l  =new TLegend(0.2,0.7,0.85,0.95);
  l->AddEntry(data_pf_04_05_05,"Particle based(#DeltaR=0.4)","lf");
  l->AddEntry(data_standard,"Subdetector based(#DeltaR=0.3)","lf");
  l->SetBorderSize(0);
  l->SetFillStyle(0);
  l->Draw();





  TCanvas *c2 = new TCanvas("c_pf_comparison03","PF vs standard iso03");
  c2->cd();
  

  TGraphErrors* data_pf_03_05_05 = data->rocCurve(*data, "(mumuChargeIso032+mumuNeutralIso032)/mumuPt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kYellow,1,"Prompt muon efficiency ","Non prompt muon efficiency","pf_03_05_05");
 
  data_pf_03_05_05->Draw("3A");

  data->addLabel(c2,"CMS Preliminary 2010",0.5,0.05,0.04);
  data->addLabel(c2,"L_{int} = 36 pb^{-1}, #sqrt{s} = 7 TeV",0.5,0.045,0.04);

  data_pf_03_05_05->Draw("XLsame");
  data_standard->Draw("3same");
  data_standard->Draw("XLsame");

  TLegend *l2  =new TLegend(0.2,0.7,0.85,0.95);
  l2->AddEntry(data_pf_03_05_05,"Particle based(#DeltaR=0.3)","lf");
  l2->AddEntry(data_standard,"Subdetector based(#DeltaR=0.3)","lf");
  l2->SetBorderSize(0);
  l2->SetFillStyle(0);
  l2->Draw();



  TCanvas *c3 = new TCanvas("c_pf_cone_comparison","PF cone comparison");
  c3->cd();

  TGraphErrors* data_pf_03_05_05_2 = data->rocCurve(*data, "(mumuChargeIso032+mumuNeutralIso032)/mumuPt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kGreen,2,"Prompt muon efficiency ","Non prompt muon efficiency","pf_03_05_05_2");
  

  TGraphErrors* data_pf_05_05_05 = data->rocCurve(*data, "(mumuChargeIso032+mumuNeutralIso052)/mumuPt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kCyan,4,"Prompt muon efficiency ","Non prompt muon efficiency","pf_05_05_05");
 
  data_pf_04_05_05->Draw("3A");

  data->addLabel(c3,"CMS Preliminary 2010",0.5,0.05,0.04);
  data->addLabel(c3,"L_{int} = 36 pb^{-1}, #sqrt{s} = 7 TeV",0.5,0.045,0.04);

  data_pf_04_05_05->Draw("XLsame");
  data_pf_03_05_05_2->Draw("3same");
  data_pf_03_05_05_2->Draw("XLsame");
  data_pf_05_05_05->Draw("3same");
  data_pf_05_05_05->Draw("XLsame");

  TLegend *l3  =new TLegend(0.2,0.7,0.65,0.85);
  l3->AddEntry(data_pf_03_05_05_2,"(#DeltaR=0.3)","lf");
  l3->AddEntry(data_pf_04_05_05,"(#DeltaR=0.4)","lf");
  l3->AddEntry(data_pf_05_05_05,"(#DeltaR=0.5)","lf");
  l3->SetBorderSize(0);
  l3->SetFillStyle(0);
  l3->Draw();


  TCanvas *c4 = new TCanvas("c_thresholds","Threshold");
  c4->cd();
  

  TGraphErrors* data_pf_04_1_05 = data->rocCurve(*data, "(mumuChargeIsoHigh2+mumuNeutralIso2)/mumuPt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kGreen,2,"Prompt muon efficiency ","Non prompt muon efficiency","pf_03_05_05");

  TGraphErrors* data_pf_04_1_1 = data->rocCurve(*data, "(mumuChargeIsoHigh2+mumuNeutralIsoHigh2)/mumuPt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kCyan,4,"Prompt muon efficiency ","Non prompt muon efficiency","pf_03_05_05");

  TGraphErrors* data_pf_04_05_1 = data->rocCurve(*data, "(mumuChargeIso2+mumuNeutralIsoHigh2)/mumuPt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kRed,5,"Prompt muon efficiency ","Non prompt muon efficiency","pf_03_05_05");


 
  data_pf_04_05_05->Draw("3A");

  data->addLabel(c4,"CMS Preliminary 2010",0.5,0.05,0.04);
  data->addLabel(c4,"L_{int} = 36 pb^{-1}, #sqrt{s} = 7 TeV",0.5,0.045,0.04);

  data_pf_04_05_05->Draw("XLsame");
  data_pf_04_1_05->Draw("3same");
  data_pf_04_1_05->Draw("XLsame");
  data_pf_04_1_1->Draw("3same");
  data_pf_04_1_1->Draw("XLsame");
  data_pf_04_05_1->Draw("3same");
  data_pf_04_05_1->Draw("XLsame");


  TLegend *l4  =new TLegend(0.2,0.7,0.85,0.95);
  l4->AddEntry(data_pf_04_05_05,"charged>0.5 ,neutral>0.5","lf");
  l4->AddEntry(data_pf_04_05_1,"charged>0.5 , neutral>1.0","lf");
  l4->AddEntry(data_pf_04_1_05,"charged>1.0 , neutral>0.5","lf");
  l4->AddEntry(data_pf_04_1_1,"charged>1.0 , neutral>1.0","lf");
  l4->SetBorderSize(0);
  l4->SetFillStyle(0);
  l4->Draw();


  TCanvas *c5 = new TCanvas("c_datavsmc","PFDATA MC");
  c5->cd();
  

  TGraphErrors* mc_pf_04_05_05 = mc->rocCurve(*mc, "(mumuChargeIso2+mumuNeutralIso2)/mumuPt2", '<', selectionBackgroundMC, selectionSignalMC,0.01,0.4, 0.01, kBlue,kYellow,1,"Prompt muon efficiency ","Non prompt muon efficiency","mc_04_05_05");

  mc_pf_04_05_05->Draw("AL");
  data_pf_04_05_05->Draw("Psame");
  data->addLabel(c5,"CMS Preliminary 2010",0.5,0.05,0.04);
  data->addLabel(c5,"L_{int} = 36 pb^{-1}, #sqrt{s} = 7 TeV",0.5,0.045,0.04);

 

  TLegend *l5  =new TLegend(0.2,0.7,0.85,0.95);
  l5->AddEntry(data_pf_04_05_05,"Data","p");
  l5->AddEntry(mc_pf_04_05_05,"Simulation","l");
  l5->SetBorderSize(0);
  l5->SetFillStyle(0);
  l5->Draw();

  TCanvas *c6 = new TCanvas("c_datavsmcSUBDET","STDDATA MC");
  c6->cd();
  

  TGraphErrors* mc_standard = mc->rocCurve(*mc, "mumuRelStdIso2", '<', selectionBackgroundMC, selectionSignalMC,0.01,0.4, 0.01, kBlue,kYellow,1,"Prompt muon efficiency ","Non prompt muon efficiency","mc_04_05_05");

  mc_standard->Draw("AL");
  data_standard->Draw("Psame");
  data->addLabel(c6,"CMS Preliminary 2010",0.5,0.05,0.04);
  data->addLabel(c6,"L_{int} = 36 pb^{-1}, #sqrt{s} = 7 TeV",0.5,0.045,0.04);

 

  TLegend *l6  =new TLegend(0.2,0.7,0.85,0.95);
  l6->AddEntry(data_standard,"Data","p");
  l6->AddEntry(mc_standard,"Simulation","l");
  l6->SetBorderSize(0);
  l6->SetFillStyle(0);
  l6->Draw();





  
  


}
