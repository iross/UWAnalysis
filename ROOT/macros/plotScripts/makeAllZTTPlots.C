{

  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuTauPlotter.C");

  std::string lumi="36";

  //SELECTION REQUIREMENTS

  std::string selection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.1&muTauisMuon==0&&muTauCharge==0&&muTauMt1<40";

      std::string selection_MtNotApplied = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.1&muTauisMuon==0";

      std::string selection_MtNotApplied_OS = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.1&muTauisMuon==0&&muTauCharge==0";

      std::string selection_MtNotApplied_SS = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.1&muTauisMuon==0&&muTauCharge!=0";

      std::string selection_QCD_Shape = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.3&muTauisMuon==0&&muTauCharge!=0&&muTauMt1<40.";

      std::string selection_ZMM_Shape = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==1&&muTauRelPFIso<0.1&muTauisMuon==1&&muTauCharge==0&&muTauMt1<40.";

     std::string selection_WMN_Shape = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.1&muTauisMuon==0&&muTauCharge==0&&muTauMt1>60.";

     std::string selection_ZMM_Enriched = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==1&&muTauRelPFIso<0.1&muTauisMuon==0&&muTauCharge!=0&&muTauMt1<40.";

      std::string selection_TOP_Enriched = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&PVs>0&&mumuSize==0&&muTauRelPFIso<0.1&muTauisMuon==0&&muTauCharge==0&&muTauMt1<40.&&muTauJetsBTag2Pt20>1";




 //   TCanvas * muPtLIN =   plotter->makeStackedPlot("muTauPt1",selection,lumi,20,15,115,"#mu p_{T}","GeV/c",22,280,270,0.6,0.6,false,0.1,300);
 // muPtLIN->SaveAs("muPtLIN.png");
 // muPtLIN->SaveAs("muPtLIN.pdf");

 //  TCanvas * tauPtLIN =   plotter->makeStackedPlot("muTauPt2",selection,lumi,20,20,120,"#tau p_{T}","GeV/c",22,280,270,0.6,0.6,false,0.1,300);
 // tauPtLIN->SaveAs("tauPtLIN.png");
 // tauPtLIN->SaveAs("tauPtLIN.pdf");

   TCanvas * muPt =   plotter->makeStackedPlot("muTauPt1",selection,lumi,20,15,115,"#mu p_{T}","GeV/c",22,4000,1000,0.6,0.6,true,0.1,10000);
 muPt->SaveAs("muPt.png");
 muPt->SaveAs("muPt.pdf");
 muPt->SaveAs("muPt.root");

  TCanvas * tauPt =   plotter->makeStackedPlot("muTauPt2",selection,lumi,20,20,120,"#tau p_{T}","GeV/c",22,4000,1000,0.6,0.6,true,0.1,10000);
 tauPt->SaveAs("tauPt.png");
 tauPt->SaveAs("tauPt.pdf");
 tauPt->SaveAs("tauPt.root");

  TCanvas * muEta =   plotter->makeStackedPlot("muTauEta1",selection,lumi,20,-2.1,2.1,"#mu #eta","",-2.0,80,75,0.6,0.65,false,0.0,90);
 muEta->SaveAs("muEta.png");
 muEta->SaveAs("muEta.pdf");
 muEta->SaveAs("muEta.root");

  TCanvas * tauEta =   plotter->makeStackedPlot("muTauEta2",selection,lumi,20,-2.3,2.3,"#tau #eta","",-2.1,80,75,0.6,0.65,false,0.1,90);
 tauEta->SaveAs("tauEta.png");
 tauEta->SaveAs("tauEta.pdf");
 tauEta->SaveAs("tauEta.root");

  TCanvas * muPhi =   plotter->makeStackedPlot("muTauPhi1",selection,lumi,20,-3.14,3.14,"#mu #phi","",-3.0,80,75,0.6,0.65,false,0.1,90);
 muPhi->SaveAs("muPhi.png");
 muPhi->SaveAs("muPhi.pdf");
 muPhi->SaveAs("muPhi.root");

  TCanvas * tauPhi =   plotter->makeStackedPlot("muTauPhi2",selection,lumi,20,-3.14,3.14,"#tau #phi","",-3.1,80,75,0.6,0.65,false,0.1,90);
 tauPhi->SaveAs("tauPhi.png");
 tauPhi->SaveAs("tauPhi.pdf");
 tauPhi->SaveAs("tauPhi.root");

  TCanvas * mt =   plotter->makeStackedPlot("muTauMt1",selection_MtNotApplied,lumi,12,0,120,"M_{T}(#mu,MET)","GeV/c^{2}",8,420,400,0.6,0.6,false,0.1,450,"mt");
 mt->SaveAs("mt.png");
 mt->SaveAs("mt.pdf");
 mt->SaveAs("mt.root");


  TCanvas * mtOS =   plotter->makeStackedPlot("muTauMt1",selection_MtNotApplied_OS,lumi,12,0,120,"M_{T}(#mu,MET)","GeV/c^{2}",10,350,320,0.6,0.6,false,0.1,400,"mtOS");
 mtOS->SaveAs("mtOS.png");
 mtOS->SaveAs("mtOS.pdf");
 mtOS->SaveAs("mtOS.root");

 TCanvas * mtSS =   plotter->makeStackedPlot("muTauMt1",selection_MtNotApplied_SS,lumi,12,0,120,"M_{T}(#mu,MET)","GeV/c^{2}",5,90,85,0.6,0.6,false,0.1,100,"mtSS");
 mtSS->SaveAs("mtSS.png");
 mtSS->SaveAs("mtSS.pdf");
 mtSS->SaveAs("mtSS.root");


  TCanvas * met =   plotter->makeStackedPlot("muTauMET",selection,lumi,20,0,100,"MET","GeV/c^{2}",40,80,70,0.6,0.6,false,0.1,180,"");
 met->SaveAs("MET.png");
 met->SaveAs("MET.pdf");
 met->SaveAs("MET.root");

 TCanvas * metLOG =   plotter->makeStackedPlot("muTauMET",selection,lumi,20,0,100,"MET","GeV/c^{2}",5,9000,2000,0.6,0.6,true,0.1,100000,"LOG");
 metLOG->SaveAs("METLOG.png");
 metLOG->SaveAs("METLOG.pdf");
 metLOG->SaveAs("METLOG.root");

  TCanvas * dphi1 =   plotter->makeStackedPlot("abs(muTauDPhi1MET)",selection,lumi,20,0,3.14,"#Delta #phi(#mu,MET)","rad",0.02,120,110,0.65,0.6,false,0.1,150,"");
 dphi1->SaveAs("dphi1.png");
 dphi1->SaveAs("dphi1.pdf");
 dphi1->SaveAs("dphi1.root");

  TCanvas * dphi2 =   plotter->makeStackedPlot("abs(muTauDPhi2MET)",selection,lumi,20,0,3.14,"#Delta #phi(#tau,MET)","rad",0.02,120,110,0.55,0.6,false,0.1,150,"");
 dphi2->SaveAs("dphi2.png");
 dphi2->SaveAs("dphi2.pdf");
 dphi2->SaveAs("dphi2.root");

  TCanvas * prongs =   plotter->makeStackedPlot("muTauProngs",selection,lumi,5,0,5,"# prongs","",0.1,700,650,0.6,0.6,false,0.1,800,"");
 prongs->SaveAs("prongs.png");
 prongs->SaveAs("prongs.pdf");
 prongs->SaveAs("prongs.root");

  TCanvas * tauMass =   plotter->makeStackedPlot("muTauHadMass",selection,lumi,10,0.14,1.7,"#tau Mass","GeV/c^{2}",0.2,140,120,0.6,0.6,false,0.1,150,"");
 tauMass->SaveAs("tauMass.png");
 tauMass->SaveAs("tauMass.pdf");
 tauMass->SaveAs("tauMass.root");


  TCanvas * massDIFF =   plotter->makeStackedPlot("sv_KineMETPtMass/muTauMass",selection,lumi,40,0.,4,"sv Mass / sv Mass","GeV/c^{2}",0.1,120,100,0.6,0.6,false,0.1,150,"");
 massDIFF->SaveAs("massDIFF.png");
 massDIFF->SaveAs("massDIFF.pdf");
 massDIFF->SaveAs("massDIFF.root");

 TCanvas * mass =   plotter->makeStackedPlot("muTauMass",selection,lumi,20,0,200,"visible Mass","GeV/c^{2}",90,80,60,0.6,0.6,false,0.1,180,"mass",true);
 mass->SaveAs("mass.png");
 mass->SaveAs("mass.pdf");
 mass->SaveAs("mass.root");

 TCanvas * massOP =   plotter->makeStackedNormalizedPlot("muTauMass",selection+"&&muTauProngs==1&&muTauGammas==0",lumi,6,0,120,"visible Mass","GeV/c^{2}",90,80,60,0.6,0.6,false,0.1,180,"massOP",true);
 massOP->SaveAs("massOP.png");
 massOP->SaveAs("massOP.pdf");
 massOP->SaveAs("massOP.root");


 TCanvas * massOPP =   plotter->makeStackedNormalizedPlot("muTauMass",selection+"&&muTauProngs==1&&muTauGammas>0",lumi,6,0,120,"visible Mass","GeV/c^{2}",90,80,60,0.6,0.6,false,0.1,180,"massOPP",true);
 massOPP->SaveAs("massOPP.png");
 massOPP->SaveAs("massOPP.pdf");
 massOPP->SaveAs("massOPP.root");

 TCanvas * massTP =   plotter->makeStackedNormalizedPlot("muTauMass",selection+"&&muTauProngs==3",lumi,6,0,120,"visible Mass","GeV/c^{2}",90,80,60,0.6,0.6,false,0.1,180,"massTP",true);
 massTP->SaveAs("massTP.png");
 massTP->SaveAs("massTP.pdf");
 massTP->SaveAs("massTP.root");


 TCanvas * decayMode =   plotter->makeStackedNormalizedPlot("muTauProngs+(muTauGammas>0)-1",selection,lumi,3,0,3,"Decay Mode","",90,80,60,0.6,0.6,false,0.1,180,"decayMode",true);
 decayMode->SaveAs("decayMode.png");
 decayMode->SaveAs("decayMode.pdf");
 decayMode->SaveAs("decayMode.root");





 TCanvas * massFG =   plotter->makeStackedPlot("muTauMass",selection,lumi,40,0,200,"visible Mass","GeV/c^{2}",70,60,60,0.6,0.6,false,0.1,100,"massFG",true);
 massFG->SaveAs("massFG.png");
 massFG->SaveAs("massFG.pdf");
 massFG->SaveAs("massFG.root");


 TCanvas * massLOG =   plotter->makeStackedPlot("muTauMass",selection,lumi,20,0,200,"visible Mass","GeV/c^{2}",10,5000,2000,0.6,0.6,true,0.1,10000,"massLOG",true);
 massLOG->SaveAs("massLOG.png");
 massLOG->SaveAs("massLOG.pdf");
 massLOG->SaveAs("massLOG.root");


 TCanvas * massSS =   plotter->makeStackedPlot("muTauMass",selection_MtNotApplied_SS+"&&muTauMt1<40",lumi,20,0,200,"visible Mass","GeV/c^{2}",100,70,60,0.6,0.6,false,0.1,120,"massSSS",true);
 massSS->SaveAs("massSS.png");
 massSS->SaveAs("massSS.pdf");
 massSS->SaveAs("massSS.root");


 TCanvas * massSSLOG =   plotter->makeStackedPlot("muTauMass",selection_MtNotApplied_SS+"&&muTauMt1<40",lumi,20,0,200,"visible Mass","GeV/c^{2}",10,5000,3000,0.6,0.6,true,0.1,10000,"massSSLOG",true);
 massSSLOG->SaveAs("massSSLOG.png");
 massSSLOG->SaveAs("massSSLOG.pdf");
 massSSLOG->SaveAs("massSSLOG.root");

 TCanvas * sv_mass =   plotter->makeStackedPlot("sv_KineMETPtMass",selection,lumi,20,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",140,70,60,0.6,0.6,false,0.1,220,"sv",true);
 sv_mass->SaveAs("sv_mass.png");
 sv_mass->SaveAs("sv_mass.pdf");
 sv_mass->SaveAs("sv_mass.root");

 TCanvas * sv_massLOG =   plotter->makeStackedPlot("sv_KineMETPtMass",selection,lumi,20,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",10,5000,3000,0.6,0.6,true,0.1,10000,"LOG",true);
 sv_massLOG->SaveAs("sv_massLOG.png");
 sv_massLOG->SaveAs("sv_massLOG.pdf");
 sv_massLOG->SaveAs("sv_massLOG.root");


 // TCanvas * massQCDShape =   plotter->makeStackedPlot("muTauMass",selection_QCD_Shape,lumi,20,0,200,"visible Mass","GeV/c^{2}",5,220,210,0.6,0.6,false,0.1,230,"QCD");
 // massQCDShape->SaveAs("massQCDShape.png");
 // massQCDShape->SaveAs("massQCDShape.pdf");

 //   TCanvas * sv_massQCDShape =   plotter->makeStackedPlot("sv_KineMETPtMass",selection_QCD_Shape,lumi,20,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",5,220,210,0.6,0.6,false,0.1,230,"QCDSV");
 // sv_massQCDShape->SaveAs("sv_massQCDShape.png");
 // sv_massQCDShape->SaveAs("sv_massQCDShape.pdf");

  TCanvas * massZMMShape =   plotterZENR->makeStackedPlot("muTauMass",selection_ZMM_Shape,lumi,50,0,200,"visible Mass","GeV/c^{2}",5,6800,6000,0.6,0.6,false,0.1,7000,"ZMM");
  massZMMShape->SaveAs("massZMMShape.png");
  massZMMShape->SaveAs("massZMMShape.pdf");

 //   TCanvas * sv_massZMMShape =   plotterZENR->makeStackedPlot("sv_KineMETPtMass",selection_ZMM_Shape,lumi,50,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",5,2800,2600,0.6,0.6,false,0.1,3000,"ZMMSV");
 // sv_massZMMShape->SaveAs("sv_massZMMShape.png");
 // sv_massZMMShape->SaveAs("sv_massZMMShape.pdf");


 TCanvas * massWMNShape =   plotterWENR->makeStackedPlot("muTauMass",selection_WMN_Shape,lumi,20,0,200,"visible Mass","GeV/c^{2}",5,80,75,0.6,0.6,false,0.1,90,"WMN");
  massWMNShape->SaveAs("massWMNShape.png");
  massWMNShape->SaveAs("massWMNShape.pdf");

 //   TCanvas * sv_massWMNShape =   plotterWENR->makeStackedPlot("sv_KineMETPtMass",selection_WMN_Shape,lumi,20,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",5,80,75,0.6,0.6,false,0.1,90,"WMNSV");
 // sv_massWMNShape->SaveAs("sv_massWMNShape.png");
 // sv_massWMNShape->SaveAs("sv_massWMNShape.pdf");


 TCanvas * massZMMEnriched =   plotterZENR->makeStackedPlot("muTauMass",selection_ZMM_Enriched,lumi,20,0,200,"visible Mass","GeV/c^{2}",5,10,8,0.6,0.6,false,0.1,12,"ZMM");
  massZMMEnriched->SaveAs("massZMMEnriched.png");
  massZMMEnriched->SaveAs("massZMMEnriched.pdf");

 // TCanvas * massTOPEnriched =   plotterTOPENR->makeStackedPlot("muTauMass",selection_TOP_Enriched,lumi,20,0,200,"visible Mass","GeV/c^{2}",5,10,8,0.6,0.6,false,0.1,12,"TOP");
 // massTOPEnriched->SaveAs("massTOPEnriched.png");
 // massTOPEnriched->SaveAs("massTOPEnriched.pdf");



}
