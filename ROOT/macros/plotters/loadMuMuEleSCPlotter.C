{
    gROOT->ProcessLine(".L /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/interactive/SimplePlotter.C");
    gROOT->ProcessLine(".L /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/interactive/tdrstyle.C");
    setTDRStyle();

    SimplePlotter *MMESplotter = new SimplePlotter();

    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/dataSamples/ZJets.root","Z+Jets","__WEIGHT__",0,kViolet-5,kViolet+3);
    //EEESplotter->addFile("eleEleEleSCEventTree/eventTree","/afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/dataSamples/ggHZZ4l.root","H(125) #rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    //MMESplotter->addFile("eleEleEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ZJets.root","Z+Jets","__WEIGHT__",0,kViolet-5,kViolet+3);
    
    MMESplotter->addFile("muMuEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ZJets.root","Z+Jets","__WEIGHT__",0,kViolet-5,kViolet+3);
    //MMESplotter->addFile("muMuEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/TTJets.root","t#bar{t}","__WEIGHT__",0,kGreen+2,kGreen+2);
    MMESplotter->addFile("muMuEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/WZTo3LNu.root","WZ","__WEIGHT__",0,kRed+2,kRed+4);
    MMESplotter->addFile("muMuEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ZZ4l.root","EWK ZZ","__WEIGHT__",0,kOrange+7,kOrange+3);
    MMESplotter->addFile("muMuEleSCEventTree/eventTree","/Users/austin/Desktop/HiggsZZ/dataSamples/ggHZZ4l.root","H(125) #rightarrow ZZ","__WEIGHT__ * ( abs(gz1l1PdgId) == 13 && abs(gz1l2PdgId) == 13 && abs(gz2l1PdgId) == 11 && abs(gz2l2PdgId) == 11)",-1,kBlue-4,kBlack);
}
