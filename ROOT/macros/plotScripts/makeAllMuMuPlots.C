{

  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuPlotter.C");

  std::string lumi="1.090";

  //SELECTION REQUIREMENTS


  std::string preselection="HLT_Any&&vertices>0&&charge==0&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>60&&mass<120";

  std::string preselectionB="HLT_Any&&vertices>0&&charge==0&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>60&&mass<120&&nJetsBTag3Pt20>0&&nJetsPt30<2&&met<20";

  std::string preselectionF="HLT_Any&&vertices>0&&charge==0&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>60&&mass<120";


  std::string preselectionFV="HLT_Any&&vertices>0&&charge==0&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>60&&mass<120&&nJetsPt30==2&&vbfDEta>2.5&&vbfMass>300&&nJetsBTag3Pt20==0";


  std::string selection="HLT_Any&&vertices>0&&charge==0&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>70&&mass<110&&met<20";

  std::string selectionB="HLT_Any&&vertices>0&&charge==0&&mass>70&&mass<110&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>70&&mass<120&&nJetsBTag3Pt20>0&&nJetsPt30<2&&met<20";

  std::string selectionF="HLT_Any&&vertices>0&&charge==0&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>70&&mass<110";


  std::string selectionFV="HLT_Any&&vertices>0&&charge==0&&(l1ChargeIso+max(l1NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt1<0.2&&(l2ChargeIso+max(l2NeutralIso-Rho*3.14*0.4*0.4,0.0))/pt2<0.2&&mass>70&&mass<110&&nJetsPt30==2&&vbfDEta>2.5&&vbfMass>300&&nJetsBTag3Pt20==0";



  TCanvas *denominator = plotter->makeStackedPlot("mass",preselection,lumi,100,60,120,"#mu#mu Mass","GeV/c^{2}",62,300000,100000,0.6,0.65,true,0.1,800000.,"D",true);
  denominator->SaveAs("mumuDataDriven/denominator.png");
  denominator->SaveAs("mumuDataDriven/denominator.pdf");
  denominator->SaveAs("mumuDataDriven/denominator.root");

  TCanvas *numerator = plotter->makeStackedPlot("mass",preselectionB,lumi,100,60,120,"#mu#mu Mass","GeV/c^{2}",62,300000,100000,0.6,0.65,true,0.1,800000.,"N",true);
  numerator->SaveAs("mumuDataDriven/numerator.png");
  numerator->SaveAs("mumuDataDriven/numerator.pdf");
  numerator->SaveAs("mumuDataDriven/numerator.root");

  TCanvas *denominatorF = plotter->makeStackedPlot("mass",preselectionF,lumi,100,60,120,"#mu#mu Mass","GeV/c^{2}",62,300000,100000,0.6,0.65,true,0.1,800000.,"D",true);
  denominatorF->SaveAs("mumuDataDriven/denominatorV.png");
  denominatorF->SaveAs("mumuDataDriven/denominatorV.pdf");
  denominatorF->SaveAs("mumuDataDriven/denominatorV.root");

  TCanvas *numeratorFV = plotter->makeStackedPlot("mass",preselectionFV,lumi,100,60,120,"#mu#mu Mass","GeV/c^{2}",62,300000,100000,0.6,0.65,true,0.1,800000.,"N",true);
  numeratorFV->SaveAs("mumuDataDriven/numeratorV.png");
  numeratorFV->SaveAs("mumuDataDriven/numeratorV.pdf");
  numeratorFV->SaveAs("mumuDataDriven/numeratorV.root");






}
