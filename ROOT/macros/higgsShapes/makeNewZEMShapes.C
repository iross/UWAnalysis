makeZEMShapes(TString filename,TString tree,TString var,int bins,float min,float max)
{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/ShapeCreator.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  ShapeCreator * visNom = new ShapeCreator(filename,bins,min,max);


  TString preselection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&eleMuMissHitsWW==0";


  visNom->makeShape("sandbox/zem-latest/ZTTPOWHEG2.root",tree,var,preselection,"__WEIGHT__*36","ZTT");
  visNom->makeShape("sandbox/zem-latest/TOP.root",tree,var,preselection,"__WEIGHT__*36","TTBar");
  visNom->makeShape("sandbox/zem-latest/EWK.root",tree,var,preselection,"__WEIGHT__*36","EWK");
  visNom->makeShape("sandbox/zem-latest/FAKES.root",tree,var,preselection,"__WEIGHT__*36","FAKES");

  visNom->makeShape("sandbox/zem-latest/DATA.root","eleMuEventTreeNominal/eventTree",var,preselection,"1.0","DATA");



  visNom->makeShape("sandbox/zem-latest/ggH90.root",tree,var,preselection,"__WEIGHT__*36","GGH90");
  visNom->makeShape("sandbox/zem-latest/ggH100.root",tree,var,preselection,"__WEIGHT__*36","GGH100");
  visNom->makeShape("sandbox/zem-latest/ggH120.root",tree,var,preselection,"__WEIGHT__*36","GGH120");
  visNom->makeShape("sandbox/zem-latest/ggH130.root",tree,var,preselection,"__WEIGHT__*36","GGH130");
  visNom->makeShape("sandbox/zem-latest/ggH140.root",tree,var,preselection,"__WEIGHT__*36","GGH140");
  visNom->makeShape("sandbox/zem-latest/ggH160.root",tree,var,preselection,"__WEIGHT__*36","GGH160");
  visNom->makeShape("sandbox/zem-latest/ggH180.root",tree,var,preselection,"__WEIGHT__*36","GGH180");


  visNom->makeShape("sandbox/zem-latest/ggH200.root",tree,var,preselection,"__WEIGHT__*36","GGH200");
  visNom->makeShape("sandbox/zem-latest/ggH250.root",tree,var,preselection,"__WEIGHT__*36","GGH250");
  visNom->makeShape("sandbox/zem-latest/ggH300.root",tree,var,preselection,"__WEIGHT__*36","GGH300");
  visNom->makeShape("sandbox/zem-latest/ggH350.root",tree,var,preselection,"__WEIGHT__*36","GGH350");

  visNom->makeShape("sandbox/zem-latest/ggH400.root",tree,var,preselection,"__WEIGHT__*36","GGH400");
  visNom->makeShape("sandbox/zem-latest/ggH450.root",tree,var,preselection,"__WEIGHT__*36","GGH450");
  visNom->makeShape("sandbox/zem-latest/ggH500.root",tree,var,preselection,"__WEIGHT__*36","GGH500");


  visNom->makeShape("sandbox/zem-latest/bbA90.root",tree,var,preselection,"__WEIGHT__*36","BBA90");
  visNom->makeShape("sandbox/zem-latest/bbA100.root",tree,var,preselection,"__WEIGHT__*36","BBA100");
  visNom->makeShape("sandbox/zem-latest/bbA120.root",tree,var,preselection,"__WEIGHT__*36","BBA120");
  visNom->makeShape("sandbox/zem-latest/bbA130.root",tree,var,preselection,"__WEIGHT__*36","BBA130");
  visNom->makeShape("sandbox/zem-latest/bbA140.root",tree,var,preselection,"__WEIGHT__*36","BBA140");
  visNom->makeShape("sandbox/zem-latest/bbA160.root",tree,var,preselection,"__WEIGHT__*36","BBA160");
  visNom->makeShape("sandbox/zem-latest/bbA180.root",tree,var,preselection,"__WEIGHT__*36","BBA180");

  visNom->makeShape("sandbox/zem-latest/bbA200.root",tree,var,preselection,"__WEIGHT__*36","BBA200");
  visNom->makeShape("sandbox/zem-latest/bbA250.root",tree,var,preselection,"__WEIGHT__*36","BBA250");
  visNom->makeShape("sandbox/zem-latest/bbA300.root",tree,var,preselection,"__WEIGHT__*36","BBA300");
  visNom->makeShape("sandbox/zem-latest/bbA350.root",tree,var,preselection,"__WEIGHT__*36","BBA350");

  visNom->makeShape("sandbox/zem-latest/bbA400.root",tree,var,preselection,"__WEIGHT__*36","BBA400");
  visNom->makeShape("sandbox/zem-latest/bbA450.root",tree,var,preselection,"__WEIGHT__*36","BBA450");
  visNom->makeShape("sandbox/zem-latest/bbA500.root",tree,var,preselection,"__WEIGHT__*36","BBA500");


  visNom->close();


}
