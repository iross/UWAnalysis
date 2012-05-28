{

  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuTauPlotter.C");

  std::string lumi="1.379";

  //SELECTION REQUIREMENTS

  std::string selection = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&lTrigger>0&&tauTrigger>0&&abs(dz)<0.2";

  std::string selectionB = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&nJetsBTag3Pt20>0&&nJetsPt30<2";

  std::string selectionNOB = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&nJetsBTag3Pt20==0&&nJetsPt30<2";

  std::string selectionSM0 = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&nJetsPt30<2&&mt1<40";

  std::string selectionSM1 = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&abs(dz)<0.2&&nJetsPt30==1&&pt>100&&met>100&&mt1<40&&highestJetPt>100";

 std::string selectionSM2 = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&pZeta>-20&&charge==0&&nJetsPt30==2&&vbfDEta>3.5&&vbfMass>350&&mt1<40";


  std::string selectionNoPZ = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&abs(dz)<0.2";

  std::string selectionNoPZOS = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&charge==0&&abs(dz)<0.2";

  std::string selectionNoPZSS = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&charge!=0";


 TCanvas * mass =   plotter->makeStackedPlot("sv_NSVPsMEtLogM_fit",selection,lumi,50,0,500,"m_{#tau#tau}","GeV/c^{2}",5,5000,4500,0.6,0.6,false,0.1,5500,"sv_NSVPsMEtLogM_fit",true);
 mass->SaveAs("muTauPlots/mass.png");
 mass->SaveAs("muTauPlots/mass.pdf");
 mass->SaveAs("muTauPlots/mass.root");

  TCanvas * massNOB =   plotter->makeStackedPlot("sv_NSVPsMEtLogM_fit",selectionNOB,lumi,50,0,500,"m_{#tau#tau}","GeV/c^{2}",5,5000,5500,0.6,0.6,false,0.1,5500,"massNOB",true);
  massNOB->SaveAs("muTauPlots/massNOB.png");
  massNOB->SaveAs("muTauPlots/massNOB.pdf");
  massNOB->SaveAs("muTauPlots/massNOB.root");



  TCanvas * massB =   plotter->makeStackedPlot("sv_NSVPsMEtLogM_fit",selectionB,lumi,20,0,400,"m_{#tau#tau}","GeV/c^{2}",150,100,85,0.6,0.6,false,0.1,200,"massB",true);
  massB->SaveAs("muTauPlots/massB.png");
  massB->SaveAs("muTauPlots/massB.pdf");
  massB->SaveAs("muTauPlots/massB.root");




  TCanvas * massSM0 =   plotter->makeStackedPlot("sv_NSVPsMEtLogM_fit",selectionSM0,lumi,50,0,500,"m_{#tau#tau}","GeV/c^{2}",80,400,300,0.6,0.6,false,0.1,5000,"massSM0",true);
  massSM0->SaveAs("muTauPlots/massSM0.png");
  massSM0->SaveAs("muTauPlots/massSM0.pdf");
  massSM0->SaveAs("muTauPlots/massSM0.root");

  TCanvas * massSM1 =   plotter->makeStackedPlot("sv_NSVPsMEtLogM_fit",selectionSM1,lumi,20,0,400,"m_{#tau#tau}","GeV/c^{2}",80,50,40,0.6,0.6,false,0.1,100,"massSM1",true);
  massSM1->SaveAs("muTauPlots/massSM1.png");
  massSM1->SaveAs("muTauPlots/massSM1.pdf");
  massSM1->SaveAs("muTauPlots/massSM1.root");

  TCanvas * massSM2 =   plotter->makeStackedPlot("sv_NSVPsMEtLogM_fit",selectionSM2,lumi,20,0,400,"m_{#tau#tau}","GeV/c^{2}",80,4,3,0.6,0.6,false,0.001,20,"massSM2",true);
  massSM2->SaveAs("muTauPlots/massSM2.png");
  massSM2->SaveAs("muTauPlots/massSM2.pdf");
  massSM2->SaveAs("muTauPlots/massSM2.root");


  TCanvas * muPt =   plotter->makeStackedPlot("pt1",selection,lumi,50,15,115,"#mu p_{T}","GeV/c",45,350,250,0.6,0.6,false,0.1,700,"muPt",true);
  muPt->SaveAs("muTauPlots/muPt.png");
  muPt->SaveAs("muTauPlots/muPt.pdf");
  muPt->SaveAs("muTauPlots/muPt.root");

  TCanvas * tauPt =   plotter->makeStackedPlot("pt2",selection,lumi,50,20,120,"#tau p_{T}","GeV/c",45,350,250,0.6,0.6,false,0.1,700,"tauPt",true);
  tauPt->SaveAs("muTauPlots/tauPt.png");
  tauPt->SaveAs("muTauPlots/tauPt.pdf");
  tauPt->SaveAs("muTauPlots/tauPt.root");

  TCanvas * MET =   plotter->makeStackedPlot("met",selectionNoPZ,lumi,50,0,100,"Missing E_{T}","GeV",45,350,250,0.6,0.6,false,0.1,700,"Pz",true);
  MET->SaveAs("muTauPlots/met.png");
  MET->SaveAs("muTauPlots/met.pdf");
  MET->SaveAs("muTauPlots/met.root");

  MET->SaveAs("muTauPlots/met.root");


  //  TCanvas * MT =   plotter->makeStackedPlot("mt1",selectionNoPZ,lumi,40,0,120,"M_{T}(#mu,MET)","GeV",10,350,250,0.6,0.6,false,0.1,700,"MT",true);
//  MT->SaveAs("muTauPlots/mt.png");
//  MT->SaveAs("muTauPlots/mt.pdf");
//  MT->SaveAs("muTauPlots/mt.root");



  TCanvas * PZ =   plotter->makeStackedPlot("pZeta",selectionNoPZ,lumi,20,-140,40,"P_{\zeta} - 1.5 P_{\zeta}^{vis}","GeV",-135,350,300,0.2,0.6,false,0.1,1100,"PZ",true);
  PZ->SaveAs("muTauPlots/PzAll.png");
  PZ->SaveAs("muTauPlots/PzAll.pdf");
  PZ->SaveAs("muTauPlots/PzAll.root");



  TCanvas * Mt =   plotter->makeStackedPlot("pZeta",selectionNoPZOS,lumi,30,-140,40,"P_{\zeta} - 1.5 P_{\zeta}^{vis}","GeV",-135,350,300,0.2,0.6,false,0.1,1100,"Mt",true);
  Mt->SaveAs("muTauPlots/Pz.png");
  Mt->SaveAs("muTauPlots/Pz.pdf");
  Mt->SaveAs("muTauPlots/Pz.root");

  TCanvas * MtSS =   plotter->makeStackedPlot("pZeta",selectionNoPZSS,lumi,30,-140,40,"P_{\zeta} - 1.5 P_{\zeta}^{vis}","GeV",-130,150,100,0.2,0.6,false,0.1,400,"MtSS",true);
  MtSS->SaveAs("muTauPlots/PzSS.png");
  MtSS->SaveAs("muTauPlots/PzSS.pdf");
  MtSS->SaveAs("muTauPlots/PzSS.root");



  TCanvas * bjets =   plotter->makeStackedPlot("nJetsBTag3Pt20",selection,lumi,5,0,5,"# b -tagged Jets","",0.1,50000,10000,0.6,0.6,true,0.1,100000,"bjets",true);
  bjets->SaveAs("muTauPlots/bjets.png");
  bjets->SaveAs("muTauPlots/bjets.pdf");
  bjets->SaveAs("muTauPlots/bjets.root");


  TCanvas * vbfDEta =   plotter->makeStackedPlot("vbfDEta",selection+"&&nJetsPt30==2&&vbfDEta>0",lumi,8,0,8,"#Delta #eta(jj)","",0.1,44,40,0.6,0.6,false,0.1,50,"vbfDEta",true);
  vbfDEta->SaveAs("muTauPlots/deta.png");
  vbfDEta->SaveAs("muTauPlots/deta.pdf");
  vbfDEta->SaveAs("muTauPlots/deta.root");

  TCanvas * vbfMass =   plotter->makeStackedPlot("vbfMass",selection+"&&nJetsPt30==2&&vbfDEta>0",lumi,10,0,1000,"M(jj)","GeV",0.1,44,40,0.6,0.6,false,0.1,50,"vbfmass",true);
  vbfMass->SaveAs("muTauPlots/vbfmass.png");
  vbfMass->SaveAs("muTauPlots/vbfmass.pdf");
  vbfMass->SaveAs("muTauPlots/vbfmass.root");

}
