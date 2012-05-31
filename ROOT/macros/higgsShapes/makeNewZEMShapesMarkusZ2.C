makeZEMShapes(TString filename,TString tree,TString var,int bins,float min,float max)
{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/ShapeCreator.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  ShapeCreator * visNom = new ShapeCreator(filename,bins,min,max);


  TString preselection = "((HLT_Mu9_wasRun==1&&HLT_Mu9_prescale==1&&HLT_Mu9_fired==1)||(HLT_Mu15_v1_wasRun==1&&HLT_Mu15_v1_prescale==1&&HLT_Mu15_v1_fired==1))&&eleMuMissHitsWW==0";


  visNom->makeShape("sandbox/zem-latest/ZTTPOWHEG2.root",tree,var,preselection,"__WEIGHT__*36","ZTT",102.046);//check your mail for thisd 
  visNom->makeShape("sandbox/zem-latest/TOP.root",tree,var,preselection,"__WEIGHT__*36","TTBar",7.57717);
  visNom->makeShape("sandbox/zem-latest/EWK.root",tree,var,preselection,"__WEIGHT__*36","EWK",3.25348);
  visNom->makeShape("sandbox/zem-latest/FAKES.root",tree,var,preselection,"__WEIGHT__*36","FAKES",4.16012);

  visNom->makeShape("sandbox/zem-latest/DATA-Markus.root","eleMuEventTreeNominal/eventTree",var,preselection,"1.0","DATA");



  visNom->makeShape("sandbox/zem-latest/ggH90.root",tree,var,preselection,"__WEIGHT__*36","GGH90",0.00375239);
  visNom->makeShape("sandbox/zem-latest/ggH100.root",tree,var,preselection,"__WEIGHT__*36","GGH100",0.00429091);
  visNom->makeShape("sandbox/zem-latest/ggH120.root",tree,var,preselection,"__WEIGHT__*36","GGH120",0.00553993);
  visNom->makeShape("sandbox/zem-latest/ggH130.root",tree,var,preselection,"__WEIGHT__*36","GGH130",0.0053);
  visNom->makeShape("sandbox/zem-latest/ggH140.root",tree,var,preselection,"__WEIGHT__*36","GGH140",0.00571818);
  visNom->makeShape("sandbox/zem-latest/ggH160.root",tree,var,preselection,"__WEIGHT__*36","GGH160",0.00616258);
  visNom->makeShape("sandbox/zem-latest/ggH180.root",tree,var,preselection,"__WEIGHT__*36","GGH180",0.00560158);


  visNom->makeShape("sandbox/zem-latest/ggH200.root",tree,var,preselection,"__WEIGHT__*36","GGH200",0.00525455);
  visNom->makeShape("sandbox/zem-latest/ggH250.root",tree,var,preselection,"__WEIGHT__*36","GGH250",0.00422871);
  visNom->makeShape("sandbox/zem-latest/ggH300.root",tree,var,preselection,"__WEIGHT__*36","GGH300",0.00371818);
  visNom->makeShape("sandbox/zem-latest/ggH350.root",tree,var,preselection,"__WEIGHT__*36","GGH350",0.0032);

  visNom->makeShape("sandbox/zem-latest/ggH400.root",tree,var,preselection,"__WEIGHT__*36","GGH400",0.00265714);
  visNom->makeShape("sandbox/zem-latest/ggH450.root",tree,var,preselection,"__WEIGHT__*36","GGH450",0.00258894);
  visNom->makeShape("sandbox/zem-latest/ggH500.root",tree,var,preselection,"__WEIGHT__*36","GGH500",0.0017);


  visNom->makeShape("sandbox/zem-latest/bbA90.root",tree,var,preselection,"__WEIGHT__*36","BBA90",0.003929);
  visNom->makeShape("sandbox/zem-latest/bbA100.root",tree,var,preselection,"__WEIGHT__*36","BBA100",0.00445455);
  visNom->makeShape("sandbox/zem-latest/bbA120.root",tree,var,preselection,"__WEIGHT__*36","BBA120",0.00566922);
  visNom->makeShape("sandbox/zem-latest/bbA130.root",tree,var,preselection,"__WEIGHT__*36","BBA130",0.00610899);
  visNom->makeShape("sandbox/zem-latest/bbA140.root",tree,var,preselection,"__WEIGHT__*36","BBA140",0.00652727);
  visNom->makeShape("sandbox/zem-latest/bbA160.root",tree,var,preselection,"__WEIGHT__*36","BBA160",0.0061074);
  visNom->makeShape("sandbox/zem-latest/bbA180.root",tree,var,preselection,"__WEIGHT__*36","BBA180",0.00681558);

  visNom->makeShape("sandbox/zem-latest/bbA200.root",tree,var,preselection,"__WEIGHT__*36","BBA200",0.00597273);
  visNom->makeShape("sandbox/zem-latest/bbA250.root",tree,var,preselection,"__WEIGHT__*36","BBA250",0.00505455);
  visNom->makeShape("sandbox/zem-latest/bbA300.root",tree,var,preselection,"__WEIGHT__*36","BBA300",0.00444545);
  visNom->makeShape("sandbox/zem-latest/bbA350.root",tree,var,preselection,"__WEIGHT__*36","BBA350",0.00386071);

  visNom->makeShape("sandbox/zem-latest/bbA400.root",tree,var,preselection,"__WEIGHT__*36","BBA400",0.00342222);
  visNom->makeShape("sandbox/zem-latest/bbA450.root",tree,var,preselection,"__WEIGHT__*36","BBA450",0.00258735);
  visNom->makeShape("sandbox/zem-latest/bbA500.root",tree,var,preselection,"__WEIGHT__*36","BBA500",0.00261667);


  visNom->close();


}
