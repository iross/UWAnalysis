{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();
  
  SimplePlotter *plotter = new SimplePlotter();

    plotter->addFile("tagAndProbeMuonID/tagAndProbeTree","sandbox/tp-tmp/ZLL.root","ZLL","__WEIGHT__",0,kRed+2,kRed+4);
    plotter->addFile("tagAndProbeMuonID/tagAndProbeTree","sandbox/tp-tmp/DATA.root","DATA","1",1,kBlack,0);



}
