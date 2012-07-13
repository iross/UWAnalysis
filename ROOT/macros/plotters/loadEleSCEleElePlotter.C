{
    gROOT->ProcessLine(".L /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/interactive/SimplePlotter.C");
    gROOT->ProcessLine(".L /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/interactive/tdrstyle.C");
    setTDRStyle();

    SimplePlotter *EEESplotter = new SimplePlotter();

    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/dataSamples/ZJets.root","Z+Jets","__WEIGHT__",0,kViolet-5,kViolet+3);
    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/dataSamples/ggHZZ4l.root","H(125) #rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);

    EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ZJets.root","Z+Jets","__WEIGHT__",0,kViolet-5,kViolet+3);
    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/TTJets.root","t#bar{t}","__WEIGHT__",0,kGreen+2,kGreen+2);
    EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/WZTo3LNu.root","WZ","__WEIGHT__",0,kRed+2,kRed+4);
    EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ZZ4l.root","EWK ZZ","__WEIGHT__",0,kOrange+7,kOrange+3);
    EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ggHZZ4l.root","H(125) #rightarrow ZZ","__WEIGHT__",-1,kBlue-4,kBlack);

    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ZJets.root","Z+Jets","1",0,kViolet-5,kViolet+3);
    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/TTJets.root","t#bar{t}","1",0,kGreen+2,kGreen+2);
    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/WZTo3LNu.root","WZ","1",0,kRed+2,kRed+4);
    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ZZ4l.root","EWK ZZ","1",0,kOrange+7,kOrange+3);
    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ggHZZ4l.root","H(125) #rightarrow ZZ","1",-1,kOrange-2,kBlack);
}
