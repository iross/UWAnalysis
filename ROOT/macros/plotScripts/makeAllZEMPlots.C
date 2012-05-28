{

  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadEMuPlotter.C");

  std::string lumi="1.429";

  //SELECTION REQUIREMENTS

  std::string selection = "HLT_Any&&vertices>0&&((HLT_Mu17_Ele8_CaloIdL_fired>0&&pt1>10&&pt2>20)||(HLT_Mu8_Ele17_CaloIdL_fired>0&&pt1>20&&pt2>10))&&l1RelPfIsoDeltaBeta<0.25&&l2RelPFIsoDeltaBeta<0.25&&pZeta>-20&&diLeptons1==0&&diLeptons2==0";

 TCanvas * mass =   plotter->makeStackedPlot("mass",selection,lumi,40,0,200,"visible Mass","GeV/c^{2}",80,80,70,0.6,0.6,false,0.1,160,"mass",true);
 mass->SaveAs("eMuPlots/mass.png");
 mass->SaveAs("eMuPlots/mass.pdf");
 mass->SaveAs("eMuPlots/mass.root");


}
