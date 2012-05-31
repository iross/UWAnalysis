{

  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadETauPlotter.C");

  std::string lumi="1.560";

  //SELECTION REQUIREMENTS

  std::string selection = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoDeltaBeta<2.0&&diLeptons==0&&pZeta>-20&&tauElectronVeto&&abs(eta1)<2.1&&abs(dz)<0.2&&lTrigger&&tauTrigger";

  std::string selectionB = "HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&abs(dz)<0.2&&tauElectronVeto&&abs(eta1)<2.1&&nJetsBTag3Pt20>0&&nJetsPt30<2";

  std::string selectionNOB = "pt1>20&&HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&abs(dz)<0.2&&tauElectronVeto&&abs(eta1)<2.1&&nJetsBTag3Pt20==0&&nJetsPt30<2";


  std::string selectionSM0 = "pt1>20&&HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&abs(dz)<0.2&&tauElectronVeto&&abs(eta1)<2.1&&nJetsPt30<2&&mt1<40";

  std::string selectionSM1 = "pt1>20&&HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&abs(dz)<0.2&&tauElectronVeto&&abs(eta1)<2.1&&nJetsPt30==1&&met>20&&pt>20&&mt1<40";

  std::string selectionSM2 = "pt1>20&&HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&pZeta>-20&&abs(dz)<0.2&&tauElectronVeto&&abs(eta1)<2.1&&nJetsPt30==2&&vbfDEta>3.5&&vbfMass>350";


  std::string selectionNoPz = "pt1>20&&HLT_Any&&vertices>0&lPfRelIsoDeltaBeta<0.1&&tauAbsIsoRho<2.0&&diLeptons==0&&abs(dz)<0.2&&tauElectronVeto&&abs(eta1)<2.1";


 TCanvas * mass =   plotter->makeStackedPlot("mass",selection,lumi,20,0,200,"visible Mass","GeV/c^{2}",98,200,150,0.6,0.6,false,0.1,800,"mass",true);
 mass->SaveAs("eTauPlots/mass.png");
 mass->SaveAs("eTauPlots/mass.pdf");
 mass->SaveAs("eTauPlots/mass.root");

 // TCanvas * massNOB =   plotterOS->makeStackedPlot("mass",selectionNOB,lumi,40,0,200,"visible Mass","GeV/c^{2}",98,200,150,0.6,0.6,false,0.1,400,"massNOB",true);
 // massNOB->SaveAs("eTauPlots/massNOB.png");
 // massNOB->SaveAs("eTauPlots/massNOB.pdf");
 // massNOB->SaveAs("eTauPlots/massNOB.root");

 // TCanvas * massSM0 =   plotterOS->makeStackedPlot("mass",selectionSM0,lumi,40,0,200,"visible Mass","GeV/c^{2}",80,250,200,0.6,0.6,false,0.1,500,"massSM0",true);
 // massSM0->SaveAs("eTauPlots/massSM0.png");
 // massSM0->SaveAs("eTauPlots/massSM0.pdf");
 // massSM0->SaveAs("eTauPlots/massSM0.root");

 // TCanvas * massSM1 =   plotterOS->makeStackedPlot("mass",selectionSM1,lumi,10,0,200,"visible Mass","GeV/c^{2}",80,50,40,0.6,0.6,false,0.1,100,"massSM1",true);
 // massSM1->SaveAs("eTauPlots/massSM1.png");
 // massSM1->SaveAs("eTauPlots/massSM1.pdf");
 // massSM1->SaveAs("eTauPlots/massSM1.root");

 // TCanvas * massSM2 =   plotterOS->makeStackedPlot("mass",selectionSM2,lumi,10,0,200,"visible Mass","GeV/c^{2}",80,4,3,0.6,0.6,false,0.001,8,"massSM2",true);
 // massSM2->SaveAs("eTauPlots/massSM2.png");
 // massSM2->SaveAs("eTauPlots/massSM2.pdf");
 // massSM2->SaveAs("eTauPlots/massSM2.root");



  TCanvas * massB =   plotter->makeStackedPlot("mass",selectionB,lumi,20,0,400,"visible Mass","GeV/c^{2}",150,20,15,0.6,0.6,false,0.1,40,"massB",true);
  massB->SaveAs("eTauPlots/massB.png");
  massB->SaveAs("eTauPlots/massB.pdf");
  massB->SaveAs("eTauPlots/massB.root");


 // TCanvas * muPt =   plotterOS->makeStackedPlot("pt1",selection,lumi,40,15,115,"e p_{T}","GeV/c",45,200,150,0.6,0.6,false,0.1,500,"muPt",true);
 // muPt->SaveAs("eTauPlots/muPt.png");
 // muPt->SaveAs("eTauPlots/muPt.pdf");
 // muPt->SaveAs("eTauPlots/muPt.root");

 // TCanvas * tauPt =   plotterOS->makeStackedPlot("pt2",selection,lumi,40,20,120,"#tau p_{T}","GeV/c",45,200,150,0.6,0.6,false,0.1,600,"tauPt",true);
 // tauPt->SaveAs("eTauPlots/tauPt.png");
 // tauPt->SaveAs("eTauPlots/tauPt.pdf");
 // tauPt->SaveAs("eTauPlots/tauPt.root");


 // TCanvas * PZ =   plotterOS->makeStackedPlot("pZeta",selectionNoPz,lumi,30,-140,40,"P_{\zeta} - 1.5 P_{\zeta}^{vis}","GeV",-135,350,300,0.2,0.6,false,0.1,1100,"PZ",true);
 // PZ->SaveAs("eTauPlots/PzAll.png");
 // PZ->SaveAs("eTauPlots/PzAll.pdf");
 // PZ->SaveAs("eTauPlots/PzAll.root");


 // TCanvas * bjets =   plotterOS->makeStackedPlot("nJetsBTag3Pt20",selection,lumi,5,0,5,"# b -tagged Jets","",0.1,50000,10000,0.6,0.6,true,0.1,100000,"bjets",true);
 // bjets->SaveAs("eTauPlots/bjets.png");
 // bjets->SaveAs("eTauPlots/bjets.pdf");
 // bjets->SaveAs("eTauPlots/bjets.root");


 // TCanvas * vbfDEta =   plotterOS->makeStackedPlot("vbfDEta",selection+"&&nJetsPt30==2&&vbfDEta>0",lumi,8,0,8,"#Delta #eta(jj)","",0.1,24,20,0.6,0.6,false,0.1,25,"vbfDEta",true);
 // vbfDEta->SaveAs("eTauPlots/deta.png");
 // vbfDEta->SaveAs("eTauPlots/deta.pdf");
 // vbfDEta->SaveAs("eTauPlots/deta.root");

 // TCanvas * vbfMass =   plotterOS->makeStackedPlot("vbfMass",selection+"&&nJetsPt30==2&&vbfDEta>0",lumi,10,0,1000,"M(jj)","GeV",0.1,24,20,0.6,0.6,false,0.1,25,"vbfmass",true);
 // vbfMass->SaveAs("eTauPlots/vbfmass.png");
 // vbfMass->SaveAs("eTauPlots/vbfmass.pdf");
 // vbfMass->SaveAs("eTauPlots/vbfmass.root");





}
