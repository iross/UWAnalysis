makeZETShapes(TString filename,TString tree,TString var,int bins,float min,float max)
{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/ShapeCreator.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  ShapeCreator * visNom = new ShapeCreator(filename,bins,min,max);

  std::string preselection ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";


 std::string preselectionQCD ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge!=0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.3)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.3))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";

 std::string preselectionZEE ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA>-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIso<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIso<0.04))&&eleTauMt1<40&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize!=0&&abs(eleTauEta1)<2.1&&(!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55))&&(!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08))";



 visNom->makeShape("sandbox/zet-latest/ZTTD6TPH.root",tree,var,preselection,"__WEIGHT__*36","ZTT");
 visNom->makeShape("sandbox/zet-latest/ZTTPH.root",tree,var,preselection,"__WEIGHT__*36","ZTTZ2");
 visNom->makeShape("sandbox/zet-latest/QCD.root",tree,var,preselection,"__WEIGHT__*36","QCD");
 visNom->makeShape("sandbox/zet-latest/WEN.root",tree,var,preselection,"__WEIGHT__*36","WEN");
 visNom->makeShape("sandbox/zet-latest/WTN.root",tree,var,preselection,"__WEIGHT__*36","WTN");
 visNom->makeShape("sandbox/zet-latest/ZEE.root",tree,var,preselection,"__WEIGHT__*36","ZEE0");
 visNom->makeShape("sandbox/zet-latest/ZEE.root",tree,var,preselection+"&&eleTauGenPt2>0","__WEIGHT__*36","ZEE1");  
 visNom->makeShape("sandbox/zet-latest/ZEE.root",tree,var,preselection+"&&eleTauGenPt2<=0","__WEIGHT__*36","ZEE2");
 visNom->makeShape("sandbox/zet-latest/TOP.root",tree,var,preselection,"__WEIGHT__*36","TTBar");
 visNom->makeShape("sandbox/zet-latest/VV.root",tree,var,preselection,"__WEIGHT__*36","DiBoson");
 visNom->makeShape("sandbox/zet-latest/DATA.root","eleTauEventTree/eventTree",var,preselection,"1","DATA");


  //DATA DRIVEN
  visNom->makeShape("sandbox/zet-latest/DATA.root","eleTauEventTree/eventTree",var,preselectionQCD,"1","QCDD");
  visNom->makeShape("sandbox/zet-latest/DATA.root","eleTauEventTree/eventTree",var,preselectionZEE,"1","ZEED");

  visNom->makeShape("sandbox/zet-latest/ggH90.root",tree,var,preselection,"__WEIGHT__","GGH90");
  visNom->makeShape("sandbox/zet-latest/ggH100.root",tree,var,preselection,"__WEIGHT__","GGH100");
  visNom->makeShape("sandbox/zet-latest/ggH120.root",tree,var,preselection,"__WEIGHT__","GGH120");
  visNom->makeShape("sandbox/zet-latest/ggH130.root",tree,var,preselection,"__WEIGHT__","GGH130");
  visNom->makeShape("sandbox/zet-latest/ggH140.root",tree,var,preselection,"__WEIGHT__","GGH140");
  visNom->makeShape("sandbox/zet-latest/ggH160.root",tree,var,preselection,"__WEIGHT__","GGH160");
  visNom->makeShape("sandbox/zet-latest/ggH180.root",tree,var,preselection,"__WEIGHT__","GGH180");
  visNom->makeShape("sandbox/zet-latest/ggH200.root",tree,var,preselection,"__WEIGHT__","GGH200");
  visNom->makeShape("sandbox/zet-latest/ggH250.root",tree,var,preselection,"__WEIGHT__","GGH250");
  visNom->makeShape("sandbox/zet-latest/ggH300.root",tree,var,preselection,"__WEIGHT__","GGH300");
  visNom->makeShape("sandbox/zet-latest/ggH350.root",tree,var,preselection,"__WEIGHT__","GGH350");
  visNom->makeShape("sandbox/zet-latest/ggH400.root",tree,var,preselection,"__WEIGHT__","GGH400");
  visNom->makeShape("sandbox/zet-latest/ggH450.root",tree,var,preselection,"__WEIGHT__","GGH450");
  visNom->makeShape("sandbox/zet-latest/ggH500.root",tree,var,preselection,"__WEIGHT__","GGH500");


  visNom->makeShape("sandbox/zet-latest/bbA90.root",tree,var,preselection,"__WEIGHT__","BBA90");
  visNom->makeShape("sandbox/zet-latest/bbA100.root",tree,var,preselection,"__WEIGHT__","BBA100");
  visNom->makeShape("sandbox/zet-latest/bbA120.root",tree,var,preselection,"__WEIGHT__","BBA120");
  visNom->makeShape("sandbox/zet-latest/bbA130.root",tree,var,preselection,"__WEIGHT__","BBA130");
  visNom->makeShape("sandbox/zet-latest/bbA140.root",tree,var,preselection,"__WEIGHT__","BBA140");
  visNom->makeShape("sandbox/zet-latest/bbA160.root",tree,var,preselection,"__WEIGHT__","BBA160");
  visNom->makeShape("sandbox/zet-latest/bbA180.root",tree,var,preselection,"__WEIGHT__","BBA180");
  visNom->makeShape("sandbox/zet-latest/bbA200.root",tree,var,preselection,"__WEIGHT__","BBA200");
  visNom->makeShape("sandbox/zet-latest/bbA250.root",tree,var,preselection,"__WEIGHT__","BBA250");
  visNom->makeShape("sandbox/zet-latest/bbA300.root",tree,var,preselection,"__WEIGHT__","BBA300");
  visNom->makeShape("sandbox/zet-latest/bbA350.root",tree,var,preselection,"__WEIGHT__","BBA350");
  visNom->makeShape("sandbox/zet-latest/bbA400.root",tree,var,preselection,"__WEIGHT__","BBA400");
  visNom->makeShape("sandbox/zet-latest/bbA450.root",tree,var,preselection,"__WEIGHT__","BBA450");
  visNom->makeShape("sandbox/zet-latest/bbA500.root",tree,var,preselection,"__WEIGHT__","BBA500");




  visNom->close();


}
