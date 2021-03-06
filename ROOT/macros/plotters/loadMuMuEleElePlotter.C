{
    gROOT->ProcessLine(".L $CMSSW_BASE/src/UWAnalysis/ROOT/interactive/SimplePlotter.C");
    gROOT->ProcessLine(".L $CMSSW_BASE/src/UWAnalysis/ROOT/interactive/tdrstyle.C");
    setTDRStyle();

    SimplePlotter *MMEEplotter = new SimplePlotter();

    // TString DATADIR="/afs/hep.wisc.edu/cms/belknap/dataSamples/HZZ4l/samples/";
    TString DATADIR="/Users/austin/Desktop/HiggsZZ/HZZ/samples/";
    /*
       MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/VV.root","EWK WW/WZ","__WEIGHT__",0,kRed+2,kRed+4);
    // MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/Z.root","Z+jets","__WEIGHT__",0,kViolet-5,kViolet+3);
    MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/ZpBorC.root","","__WEIGHT__",0,kViolet-5,kViolet+3);  
    MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/Z2or3Jets.root","Z+jets","__WEIGHT__",0,kViolet-2,kViolet+5);  
    MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/TOP.root","t#bar{t}","__WEIGHT__",0,kGreen+2,kGreen+2);
    MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/ZZ.root","EWK ZZ","__WEIGHT__",0,kOrange+7,kOrange+3);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH120.root","H(120)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH130.root","H(130)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH140.root","H(140)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH150.root","H(150)#rightarrow ZZ","__WEIGHT__",-1,kYellow,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH160.root","H(160)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH170.root","H(170)#rightarrow ZZ,"__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH180.root","H(180)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH190.root","H(190)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH200.root","H(200)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH250.root","H(250)#rightarrow ZZ","__WEIGHT__",-1,kOrange+10,kBlack);
    // MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH300.root","H(300)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH350.root","H(350)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH400.root","H(400)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH450.root","H(450)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH500.root","H(500)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH550.root","H(550)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    // 	MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/higgs-latest/ggH600.root","H(600)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
    MMEEplotter->addFile("muMuEleEleEventTree/eventTree","sandbox/zzee-latest/DATA.root","DATA","1",1,kBlack,1);
    */

    MMEEplotter->addFile("muMuEleEleEventTreeFinal/eventTree",DATADIR+"DATA.root",  "Data","1",1,kBlack,1);
    // MMEEplotter->addFile("muMuEleEleEventTreeFinal/eventTree",DATADIR+"ggH125.root","H(125)","__WEIGHT__",-1,kWhite,kRed+1);
    // MMEEplotter->addFile("muMuEleEleEventTreeFinal/eventTree",DATADIR+"ZZ4l.root",  "ZZ","__WEIGHT__",0,kAzure-9,kBlack);
    //MMEEplotter->addFile("muMuEleEleEventTreeFinal/eventTree",DATADIR+"DYJets.root","Z+Jets","__WEIGHT__",0,kTeal-7,kBlack);


}
