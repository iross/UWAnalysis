{

  gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadETauPlotter.C");

  std::string lumi="36";


  std::string selection ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";

  std::string selectionSS ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge!=0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";



  std::string selection_MtNotApplied ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";


  std::string selection_MtNotApplied_OS ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";

  std::string selection_MtNotApplied_SS ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge!=0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";


  std::string selection_QCD_Shape ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge!=0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.3)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.3))&&PVs>0&&eleTauMt1<40&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";

  std::string selection_ZEE_Shape = "HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA>-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&eleTauMt1<40&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize!=0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";
  std::string selection_WEN_Shape =   "HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&eleTauMt1>60&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";



   TCanvas * elePt =   plotter->makeStackedPlot("eleTauPt1",selection,lumi,20,15,115,"e p_{T}","GeV/c",18,2000,1000,0.6,0.6,true,0.1,10000);
 elePt->SaveAs("eTauPlots/elePt.png");
 elePt->SaveAs("eTauPlots/elePt.pdf");

  TCanvas * tauPt =   plotter->makeStackedPlot("eleTauPt2",selection,lumi,20,20,120,"#tau p_{T}","GeV/c",23,2000,1000,0.6,0.6,true,0.1,10000);
 tauPt->SaveAs("eTauPlots/tauPt.png");
 tauPt->SaveAs("eTauPlots/tauPt.pdf");
 tauPt->SaveAs("eTauPlots/tauPt.root");

  TCanvas * eleEta =   plotter->makeStackedPlot("eleTauEta1",selection,lumi,6,-2.1,2.1,"e #eta","",-2.0,230,220,0.6,0.6,false,0.1,250);
 eleEta->SaveAs("eTauPlots/eleEta.png");
 eleEta->SaveAs("eTauPlots/eleEta.pdf");
 eleEta->SaveAs("eTauPlots/eleEta.root");

  TCanvas * tauEta =   plotter->makeStackedPlot("eleTauEta2",selection,lumi,6,-2.3,2.3,"#tau #eta","",-2.1,230,220,0.6,0.6,false,0.1,250);
 tauEta->SaveAs("eTauPlots/tauEta.png");
 tauEta->SaveAs("eTauPlots/tauEta.pdf");
 tauEta->SaveAs("eTauPlots/tauEta.root");
 
  TCanvas * elePhi =   plotter->makeStackedPlot("eleTauPhi1",selection,lumi,6,-3.14,3.14,"e #phi","",-2.9,175,160,0.6,0.6,false,0.1,200);
 elePhi->SaveAs("eTauPlots/elePhi.png");
 elePhi->SaveAs("eTauPlots/elePhi.pdf");
 elePhi->SaveAs("eTauPlots/elePhi.root");

  TCanvas * tauPhi =   plotter->makeStackedPlot("eleTauPhi2",selection,lumi,6,-3.14,3.14,"#tau #phi","",-2.9,175,160,0.6,0.6,false,0.1,200);
 tauPhi->SaveAs("eTauPlots/tauPhi.png");
 tauPhi->SaveAs("eTauPlots/tauPhi.pdf");
 tauPhi->SaveAs("eTauPlots/tauPhi.root");

  TCanvas * mt =   plotter->makeStackedPlot("eleTauMt1",selection_MtNotApplied,lumi,12,0,120,"M_{T}(e,MET)","GeV/c^{2}",5,350,330,0.6,0.6,false,0.1,380,"mt");
 mt->SaveAs("eTauPlots/mt.png");
 mt->SaveAs("eTauPlots/mt.pdf");
 mt->SaveAs("eTauPlots/mt.root");


  TCanvas * mtOS =   plotter->makeStackedPlot("eleTauMt1",selection_MtNotApplied_OS,lumi,12,0,120,"M_{T}(e,MET)","GeV/c^{2}",5,295,270,0.6,0.6,false,0.1,350,"mtOS");
 mtOS->SaveAs("eTauPlots/mtOS.png");
 mtOS->SaveAs("eTauPlots/mtOS.pdf");
 mtOS->SaveAs("eTauPlots/mtOS.root");

 TCanvas * mtSS =   plotter->makeStackedPlot("eleTauMt1",selection_MtNotApplied_SS,lumi,12,0,120,"M_{T}(e,MET)","GeV/c^{2}",5,98,90,0.6,0.6,false,0.1,110,"mtSS");
 mtSS->SaveAs("eTauPlots/mtSS.png");
 mtSS->SaveAs("eTauPlots/mtSS.pdf");
 mtSS->SaveAs("eTauPlots/mtSS.root");
 
  TCanvas * met =   plotter->makeStackedPlot("eleTauMET",selection,lumi,20,0,100,"MET","GeV/c^{2}",40,82,70,0.6,0.6,false,0.1,200,"");
 met->SaveAs("eTauPlots/MET.png");
 met->SaveAs("eTauPlots/MET.pdf");
 met->SaveAs("eTauPlots/MET.root");

 TCanvas * metLOG =   plotter->makeStackedPlot("eleTauMET",selection,lumi,20,0,100,"MET","GeV/c^{2}",5,2000,1000,0.6,0.6,true,0.1,10000,"LOG");
 metLOG->SaveAs("eTauPlots/METLOG.png");
 metLOG->SaveAs("eTauPlots/METLOG.pdf");
 metLOG->SaveAs("eTauPlots/METLOG.root");

  TCanvas * dphi1 =   plotter->makeStackedPlot("abs(eleTauDPhi1MET)",selection,lumi,10,0,3.14,"#Delta #phi(e,MET)","rad",1.3,70,60,0.6,0.6,false,0.1,160,"");
 dphi1->SaveAs("eTauPlots/dphi1.png");
 dphi1->SaveAs("eTauPlots/dphi1.pdf");
 dphi1->SaveAs("eTauPlots/dphi1.root");

  TCanvas * dphi2 =   plotter->makeStackedPlot("abs(eleTauDPhi2MET)",selection,lumi,10,0,3.14,"#Delta #phi(#tau,MET)","rad",0.3,70,60,0.2,0.6,false,0.1,160,"");
 dphi2->SaveAs("eTauPlots/dphi2.png");
 dphi2->SaveAs("eTauPlots/dphi2.pdf");
 dphi2->SaveAs("eTauPlots/dphi2.root");

  TCanvas * prongs =   plotter->makeStackedPlot("eleTauProngs",selection,lumi,4,0,4,"# prongs","",0.2,590,550,0.6,0.6,false,0.1,700,"");
 prongs->SaveAs("eTauPlots/prongs.png");
 prongs->SaveAs("eTauPlots/prongs.pdf");
 prongs->SaveAs("eTauPlots/prongs.root");

  TCanvas * tauMass =   plotter->makeStackedPlot("eleTauHadMass",selection,lumi,10,0.14,1.7,"#tau Mass","GeV/c^{2}",0.2,140,130,0.6,0.6,false,0.1,150,"");
 tauMass->SaveAs("eTauPlots/tauMass.png");
 tauMass->SaveAs("eTauPlots/tauMass.pdf");
 tauMass->SaveAs("eTauPlots/tauMass.root");


  TCanvas * massDIFF =   plotter->makeStackedPlot("sv_KineMETPtMass/eleTauMass",selection,lumi,20,0.,4,"sv Mass / vis Mass","GeV/c^{2}",0.1,260,240,0.6,0.6,false,0.1,300,"");
 massDIFF->SaveAs("eTauPlots/massDIFF.png");
 massDIFF->SaveAs("eTauPlots/massDIFF.pdf");
 massDIFF->SaveAs("eTauPlots/massDIFF.root");

 TCanvas * mass =   plotter->makeStackedPlot("eleTauMass",selection,lumi,15,0,195,"visible Mass","GeV/c^{2}",10,190,175,0.6,0.6,false,0.1,210,"",true);
 mass->SaveAs("eTauPlots/mass.png");
 mass->SaveAs("eTauPlots/mass.pdf");
 mass->SaveAs("eTauPlots/mass.root");

 TCanvas * massSS =   plotter->makeStackedPlot("eleTauMass",selectionSS,lumi,15,0,195,"visible Mass","GeV/c^{2}",10,100,90,0.6,0.6,false,0.1,110,"SS",true);
 massSS->SaveAs("eTauPlots/massSS.png");
 massSS->SaveAs("eTauPlots/massSS.pdf");
 massSS->SaveAs("eTauPlots/massSS.root");


 TCanvas * massFG =   plotter->makeStackedPlot("eleTauMass",selection,lumi,30,0,195,"visible Mass","GeV/c^{2}",10,130,125,0.6,0.6,false,0.1,140,"FG",true);
 massFG->SaveAs("eTauPlots/massFG.png");
 massFG->SaveAs("eTauPlots/massFG.pdf");
 massFG->SaveAs("eTauPlots/massFG.root");


 TCanvas * massLOG =   plotter->makeStackedPlot("eleTauMass",selection,lumi,15,0,195,"visible Mass","GeV/c^{2}",10,2000,1000,0.6,0.6,true,0.1,10000,"LOG",true);
 massLOG->SaveAs("eTauPlots/massLOG.png");
 massLOG->SaveAs("eTauPlots/massLOG.pdf");
 massLOG->SaveAs("eTauPlots/massLOG.root");

 TCanvas * massSSLOG =   plotter->makeStackedPlot("eleTauMass",selectionSS,lumi,15,0,195,"visible Mass","GeV/c^{2}",10,2000,1000,0.6,0.6,true,0.1,10000,"SSLOG",true);
 massSSLOG->SaveAs("eTauPlots/massSSLOG.png");
 massSSLOG->SaveAs("eTauPlots/massSSLOG.pdf");
 massSSLOG->SaveAs("eTauPlots/massSSLOG.root");


 TCanvas * sv_mass =   plotter->makeStackedPlot("sv_KineMETPtMass",selection,lumi,25,0,500,"M(#tau^{+}#tau^{-})","GeV/c^{2}",175,80,68,0.6,0.6,false,0.1,200,"",true);
 sv_mass->SaveAs("eTauPlots/sv_mass.png");
 sv_mass->SaveAs("eTauPlots/sv_mass.pdf");
 sv_mass->SaveAs("eTauPlots/sv_mass.root");

 TCanvas * sv_massLOG =   plotter->makeStackedPlot("sv_KineMETPtMass",selection,lumi,20,0,600,"M(#tau^{+}#tau^{-})","GeV/c^{2}",10,2000,1000,0.6,0.6,true,0.1,10000,"LOG",true);
 sv_massLOG->SaveAs("eTauPlots/sv_massLOG.png");
 sv_massLOG->SaveAs("eTauPlots/sv_massLOG.pdf");
 sv_massLOG->SaveAs("eTauPlots/sv_massLOG.root");


 // TCanvas * massQCDShape =   plotter->makeStackedPlot("eleTauMass",selection_QCD_Shape,lumi,20,0,200,"visible Mass","GeV/c^{2}",10,215,200,0.6,0.6,false,0.1,250,"QCD",true);
 // massQCDShape->SaveAs("eTauPlots/massQCDShape.png");
 // massQCDShape->SaveAs("eTauPlots/massQCDShape.pdf");

 //   TCanvas * sv_massQCDShape =   plotter->makeStackedPlot("sv_KineMETPtMass",selection_QCD_Shape,lumi,20,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",10,215,200,0.6,0.6,false,0.1,250,"QCDSV",true);
 // sv_massQCDShape->SaveAs("eTauPlots/sv_massQCDShape.png");
 // sv_massQCDShape->SaveAs("eTauPlots/sv_massQCDShape.pdf");

 // TCanvas * massZEEShape =   plotterZENR->makeStackedPlot("eleTauMass",selection_ZEE_Shape,lumi,30,0,195,"visible Mass","GeV/c^{2}",5,65,60,0.6,0.6,false,0.1,80,"ZEE",true);
 // massZEEShape->SaveAs("eTauPlots/massZEEShape.png");
 // massZEEShape->SaveAs("eTauPlots/massZEEShape.pdf");

 //   TCanvas * sv_massZEEShape =   plotterZENR->makeStackedPlot("sv_KineMETPtMass",selection_ZEE_Shape,lumi,20,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",10,75,70,0.6,0.6,false,0.1,90,"ZEESV",true);
 // sv_massZEEShape->SaveAs("eTauPlots/sv_massZEEShape.png");
 // sv_massZEEShape->SaveAs("eTauPlots/sv_massZEEShape.pdf");


 TCanvas * massWENShape =   plotterWENR->makeStackedPlot("eleTauMass",selection_WEN_Shape,lumi,20,0,200,"visible Mass","GeV/c^{2}",5,33,30,0.6,0.6,false,0.1,40,"WEN",true);
 massWENShape->SaveAs("eTauPlots/massWENShape.png");
 massWENShape->SaveAs("eTauPlots/massWENShape.pdf");

 //   TCanvas * sv_massWENShape =   plotterWENR->makeStackedPlot("sv_KineMETPtMass",selection_WEN_Shape,lumi,20,0,400,"M(#tau^{+}#tau^{-})","GeV/c^{2}",5,33,30,0.6,0.6,false,0.1,40,"WENSV",true);
 // sv_massWENShape->SaveAs("eTauPlots/sv_massWENShape.png");
 // sv_massWENShape->SaveAs("eTauPlots/sv_massWENShape.pdf");



}

