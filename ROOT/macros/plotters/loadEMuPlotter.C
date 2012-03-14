{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  SimplePlotter *plotter = new SimplePlotter();


     plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/TOP.root","t #bar{t}","__WEIGHT__",0,kGray);
     plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/VV.root","Electroweak","__WEIGHT__",0,24);
     plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/FAKES.root","Fakes","__WEIGHT__",0,32);
     plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/ZTT.root","Z #rightarrow #tau #tau","__WEIGHT__",0,30);

      plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/ggH120.root","#Phi(120) #rightarrow #tau #tau","21.5/110000",-1,5,1001);
      plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/bbA120.root","","31.6/110000",-1,5,1001);
      plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/ggH130.root","","2.66/110000",-1,5);
      plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/bbA130.root","","0.93/106400",-1,5);
     plotter->addFile("eleMuEventTree/eventTree","sandbox/zem-latest/DATA-Markus.root","DATA","1",1,kBlack);



}
