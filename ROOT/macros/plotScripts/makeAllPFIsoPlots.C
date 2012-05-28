{
  gROOT->ProcessLine(".x UWAnalysis/ROOT/interactive/loadRooInteractiveLOCAL.C");
  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadPFIsoPlotter.C");

  std::string lumi="191";

  //SELECTION REQUIREMENTS

  std::string preselection= "HLT_Any&&vertices>0&&pt1>15&&pt2>15";

  std::string selectionSignal = "HLT_Any&&vertices>0&&pt1>20&&pt2>15&&(l1ChargeIso+l1NeutralIso)/pt1<0.2&&charge==0";

  std::string selectionBackground = "HLT_Any&&vertices>0&&pt1>20&&pt2>15&&(l1ChargeIso+l1NeutralIso)/pt1>0.3";

  std::string selectionSignalFinal = "HLT_Any&&vertices>0&&pt1>20&&pt2>15&&(l1ChargeIso+l1NeutralIso)/pt1<0.2&&charge==0&&mass>70&&mass<120&&pt2>20";

  std::string selectionBackgroundFinal = "HLT_Any&&vertices>0&&pt1>20&&pt2>15&&(l1ChargeIso+l1NeutralIso)/pt1>0.3&&(mass<70||mass>120)&&pt2>20";


  std::string selectionSignalMC = "2100*__WEIGHT__*("+selectionSignalFinal+")";
  std::string selectionBackgroundMC = "2100**__WEIGHT__*("+selectionBackgroundFinal+")";



   TCanvas *c1 = new TCanvas("c_pf_comparison","PF vs standard iso");
   c1->cd();
  

   TGraphErrors* data_pf = data->rocCurve(*data, "(l2ChargeIso+l2NeutralIso)/pt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlack,kYellow,1,"Prompt muon efficiency ","Non prompt muon efficiency","pf");

   TGraphErrors* data_pf_rho = data->rocCurve(*data, "(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kRed,kRed,1,"Prompt muon efficiency ","Non prompt muon efficiency","pfRho");

   TGraphErrors* data_pf_dB = data->rocCurve(*data, "(l2ChargeIso+max(l2NeutralIso-0.5*l2PUIso,0.0))/pt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kGreen,kGreen,1,"Prompt muon efficiency ","Non prompt muon efficiency","pfDB");


   TGraphErrors* data_pf_B = data->rocCurve(*data, "(l2ChargeIso+l2NeutralIso*l2ChargeIso/(l2ChargeIso+l2PUIso))/pt2", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kBlue,kBlue,1,"Prompt muon efficiency ","Non prompt muon efficiency","pfB");

   TGraphErrors* data_std = data->rocCurve(*data, "l2StdRelIso", '<', selectionBackgroundFinal, selectionSignalFinal,0.01,0.4, 0.01, kMagenta,kMagenta,1,"Prompt muon efficiency ","Non prompt muon efficiency","std");


   data_pf->Draw("AL");
   data_pf_rho->Draw("Lsame");
   data_pf_dB->Draw("Lsame");
   data_pf_B->Draw("Lsame");
   data_std->Draw("Lsame");
 

   TLegend *l  =new TLegend(0.2,0.7,0.85,0.95);
   l->AddEntry(data_pf,"PF(no corr)","l");
   l->AddEntry(data_pf_rho,"PF(#rho)","l");
   l->AddEntry(data_pf_dB,"PF(#Delta #beta)","l");
   l->AddEntry(data_pf_B,"PF(#beta)","l");
   l->AddEntry(data_std,"Sub-det(no corr)","l");

   l->SetBorderSize(0);
   l->SetFillStyle(0);
   l->Draw();

  

}
