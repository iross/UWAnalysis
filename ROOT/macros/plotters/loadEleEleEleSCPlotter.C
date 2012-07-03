{
    gROOT->ProcessLine(".L /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/interactive/SimplePlotter.C+");
    gROOT->ProcessLine(".L /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/interactive/tdrstyle.C");
    setTDRStyle();

    SimplePlotter *EEESplotter = new SimplePlotter();

    EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/scratch/belknap/ZJets.root","Z+Jets","__WEIGHT__",0,kViolet-5,kViolet+3);
    EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/scratch/belknap/ggHZZ4l.root","H(125) #rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
}
