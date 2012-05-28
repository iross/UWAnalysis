makeZMTShapes(TString filename,TString tree,TString var,int bins,float min,float max)
{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/ShapeCreator.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  ShapeCreator * visNom = new ShapeCreator(filename,bins,min,max);


  TString preselection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&mumuSize==0&&PVs>0";


  TString preselectionQCD = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&muTauRelPFIso<0.3&&muTauisMuon==0&&muTauMt1<40&&muTauCharge!=0&&mumuSize==0&&PVs>0";

  TString preselectionZMM = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&muTauRelPFIso<0.1&&muTauisMuon==1&&mumuSize==1&&muTauMt1<40&&muTauCharge==0&&PVs>0";




  visNom->makeShape("sandbox/ztt-latest/ZTTPOWHEG4.root",tree,var,preselection,"__WEIGHT__*36","ZTT");
  visNom->makeShape("sandbox/ztt-latest/ZTTPOWHEG3.root",tree,var,preselection,"__WEIGHT__*36","ZTTZ2");
  visNom->makeShape("sandbox/ztt-latest/ZTT.root",tree,var,preselection,"__WEIGHT__*36","ZTTD6T");
  visNom->makeShape("sandbox/ztt-latest/QCD.root",tree,var,preselection,"__WEIGHT__*36","QCD");
  visNom->makeShape("sandbox/ztt-latest/WMNZ2.root",tree,var,preselection,"__WEIGHT__*36","WMN");
  visNom->makeShape("sandbox/ztt-latest/WTNZ2.root",tree,var,preselection,"__WEIGHT__*36","WTN");
  visNom->makeShape("sandbox/ztt-latest/ZMMPOWHEG.root",tree,var,preselection,"__WEIGHT__*36","ZMM0");
  visNom->makeShape("sandbox/ztt-latest/ZMMPOWHEG.root",tree,var,preselection+"&&muTauGenPt2>0","__WEIGHT__*36","ZMM1");  
  visNom->makeShape("sandbox/ztt-latest/ZMMPOWHEG.root",tree,var,preselection+"&&muTauGenPt2<=0","__WEIGHT__*36","ZMM2");
  visNom->makeShape("sandbox/ztt-latest/TOP.root",tree,var,preselection,"__WEIGHT__*36","TTBar");
  visNom->makeShape("sandbox/ztt-latest/VV.root",tree,var,preselection,"__WEIGHT__*36","DiBoson");


  visNom->makeShape("sandbox/ztt-latest/DATA.root","muTauEventTreeNominal/eventTree",var,preselection,"1.0","DATA");


  //DATA DRIVEN
  visNom->makeShape("sandbox/ztt-latest/DATA.root","muTauEventTree/eventTree",var,preselectionQCD,"1","QCDD");
  visNom->makeShape("sandbox/ztt-latest/DATA.root","muTauEventTree/eventTree",var,preselectionZMM,"1","ZMMD");

  printf("starting Higgs\n");
  visNom->makeShape("sandbox/ztt-latest/ggH90.root",tree,var,preselection,"__WEIGHT__","GGH90");
  visNom->makeShape("sandbox/ztt-latest/ggH100.root",tree,var,preselection,"__WEIGHT__","GGH100");
  visNom->makeShape("sandbox/ztt-latest/ggH120.root",tree,var,preselection,"__WEIGHT__","GGH120");
  visNom->makeShape("sandbox/ztt-latest/ggH130.root",tree,var,preselection,"__WEIGHT__","GGH130");
  visNom->makeShape("sandbox/ztt-latest/ggH140.root",tree,var,preselection,"__WEIGHT__","GGH140");
  visNom->makeShape("sandbox/ztt-latest/ggH160.root",tree,var,preselection,"__WEIGHT__","GGH160");
  visNom->makeShape("sandbox/ztt-latest/ggH180.root",tree,var,preselection,"__WEIGHT__","GGH180");
  visNom->makeShape("sandbox/ztt-latest/ggH200.root",tree,var,preselection,"__WEIGHT__","GGH200");
  visNom->makeShape("sandbox/ztt-latest/ggH250.root",tree,var,preselection,"__WEIGHT__","GGH250");
  visNom->makeShape("sandbox/ztt-latest/ggH300.root",tree,var,preselection,"__WEIGHT__","GGH300");
  visNom->makeShape("sandbox/ztt-latest/ggH350.root",tree,var,preselection,"__WEIGHT__","GGH350");
  visNom->makeShape("sandbox/ztt-latest/ggH400.root",tree,var,preselection,"__WEIGHT__","GGH400");
  visNom->makeShape("sandbox/ztt-latest/ggH450.root",tree,var,preselection,"__WEIGHT__","GGH450");
  visNom->makeShape("sandbox/ztt-latest/ggH500.root",tree,var,preselection,"__WEIGHT__","GGH500");

  visNom->makeShape("sandbox/ztt-latest/bbA90.root",tree,var,preselection,"__WEIGHT__","BBA90");
  visNom->makeShape("sandbox/ztt-latest/bbA100.root",tree,var,preselection,"__WEIGHT__","BBA100");
  visNom->makeShape("sandbox/ztt-latest/bbA120.root",tree,var,preselection,"__WEIGHT__","BBA120");
  visNom->makeShape("sandbox/ztt-latest/bbA130.root",tree,var,preselection,"__WEIGHT__","BBA130");
  visNom->makeShape("sandbox/ztt-latest/bbA140.root",tree,var,preselection,"__WEIGHT__","BBA140");
  visNom->makeShape("sandbox/ztt-latest/bbA160.root",tree,var,preselection,"__WEIGHT__","BBA160");
  visNom->makeShape("sandbox/ztt-latest/bbA180.root",tree,var,preselection,"__WEIGHT__","BBA180");
  visNom->makeShape("sandbox/ztt-latest/bbA200.root",tree,var,preselection,"__WEIGHT__","BBA200");
  visNom->makeShape("sandbox/ztt-latest/bbA250.root",tree,var,preselection,"__WEIGHT__","BBA250");
  visNom->makeShape("sandbox/ztt-latest/bbA300.root",tree,var,preselection,"__WEIGHT__","BBA300");
  visNom->makeShape("sandbox/ztt-latest/bbA350.root",tree,var,preselection,"__WEIGHT__","BBA350");
  visNom->makeShape("sandbox/ztt-latest/bbA400.root",tree,var,preselection,"__WEIGHT__","BBA400");
  visNom->makeShape("sandbox/ztt-latest/bbA450.root",tree,var,preselection,"__WEIGHT__","BBA450");
  visNom->makeShape("sandbox/ztt-latest/bbA500.root",tree,var,preselection,"__WEIGHT__","BBA500");




  visNom->close();


}
