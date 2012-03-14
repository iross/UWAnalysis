{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
  gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
  setTDRStyle();


  SimplePlotter *plotterMC = new SimplePlotter();

   plotterMC->addFile("tree","sandbox/gen-level/mu-tau-powheg.root"," POWHEG","1.0",0,kRed);
   plotterMC->addFile("tree","sandbox/gen-level/mu-tau-pythia.root"," PYTHIA","1.0",0,kBlack);



















}
