{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  SimplePlotter *plotter = new SimplePlotter();

  plotter->addFile("muMuEventTree/eventTree","sandbox/zmm-latest/QCD.root","QCD","__WEIGHT__",0,kViolet-5,kViolet+3);

  plotter->addFile("muMuEventTree/eventTree","sandbox/zmm-latest/EWK.root","ewk/t#bar{t}","__WEIGHT__",0,kOrange+7,kOrange+3);

   plotter->addFile("muMuEventTree/eventTree","sandbox/zmm-latest/ZMMPOWHEG.root","Z #rightarrow #mu #mu","__WEIGHT__",0,kOrange-2,kBlack);




      // plotter->addFile("muMuEventTree/eventTree","sandbox/zmm-latest/ggH120.root","#Phi(120) #rightarrow #tau #tau","39.73*__WEIGHT__",-1,kGreen+2,kGreen+2,1001);
      // plotter->addFile("muMuEventTree/eventTree","sandbox/ztt-latest/bbA120.root","","64.93*__WEIGHT__",-1,kGreen+2,kGreen+2,1001); 
      // plotter->addFile("muMuEventTree/eventTree","sandbox/zmm-latest/ggH130.root","","2.96*__WEIGHT__",-1,kGreen+2,kGreen+2);
      // plotter->addFile("muMuEventTree/eventTree","sandbox/zmm-latest/bbA130.root","","1.04*__WEIGHT__",-1,kGreen+2,kGreen+2);

   plotter->addFile("muMuEventTree/eventTree","sandbox/zmm-latest/DATA.root","DATA","1",1,kBlack,0);



}
