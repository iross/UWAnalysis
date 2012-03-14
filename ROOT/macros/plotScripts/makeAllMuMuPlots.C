{

  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuPlotter.C");

  std::string lumi="36";

  //SELECTION REQUIREMENTS

  std::string preselection= "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuPt1>15&&mumuPt2>15";


  std::string selectionSignal = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&(mumuChargeIso1+mumuNeutralIso1)/mumuPt1<0.2&&mumuPt1>20&&mumuPt2>15&&mumuCharge==0";

  std::string selectionBackground = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&(mumuChargeIso1+mumuNeutralIso1)/mumuPt1>0.3&&mumuPt1>15&&mumuPt2>15";



  TCanvas * massSignal =   plotter->makeStackedPlot("mumuMass",selectionSignal,lumi,60,35,155,"#mu #mu Mass","GeV/c^{2}",40,100000,10000,0.6,0.6,true,0.1,1000000,"signal",true);
 massSignal->SaveAs("mumuPlots/massSignal.png");
 massSignal->SaveAs("mumuPlots/massSignal.pdf");
 massSignal->SaveAs("mumuPlots/massSignal.root");


 TCanvas * massBackground =   plotter->makeStackedPlot("mumuMass",selectionBackground,lumi,60,35,155,"#mu #mu Mass","GeV/c^{2}",40,100000,10000,0.6,0.6,true,0.1,1000000,"bkg",true);
 massBackground->SaveAs("mumuPlots/massBackground.png");
 massBackground->SaveAs("mumuPlots/massBackground.pdf");
 massBackground->SaveAs("mumuPlots/massBackground.root");

 TCanvas * isolation =   plotter->makeStackedPlot("(mumuChargeIso2+mumuNeutralIso2)/mumuPt2",preselection,lumi,50,0,1.0,"#Sigma PF E_{T} [0.4] / p_{T}","",40,100000,10000,0.6,0.6,true,0.1,1000000,"iso",true);
 isolation->SaveAs("mumuPlots/isolation.png");
 isolation->SaveAs("mumuPlots/isolation.pdf");
 isolation->SaveAs("mumuPlots/isolation.root");





}
