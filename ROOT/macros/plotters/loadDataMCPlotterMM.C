{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/SimplePlotter.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	SimplePlotter *EEEEplotter = new SimplePlotter();

	EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/VV.root","EWK WW/WZ","__WEIGHT__",0,kRed+2,kRed+4);
	// EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/QCDJets.root","QCDjets","__WEIGHT__",0,kAzure-1,kRed+4);
	EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/DYJets.root","Z+jets","__WEIGHT__",0,kViolet-5,kRed+4);
	// EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/Z2or3Jets.root","Z+jets","__WEIGHT__",0,kViolet-5,kViolet+3);
	// EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/ZpBorC.root","Z+bc","__WEIGHT__",0,kViolet-2,kViolet+3);  
	EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/TOP.root","t#bar{t}","__WEIGHT__",0,kGreen+2,kGreen+2);
	EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/ZZ.root","EWK ZZ","__WEIGHT__",0,kOrange+7,kOrange+3);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH120.root","H(120)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH130.root","H(130)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH140.root","H(140)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH150.root","H(150)#rightarrow ZZ","__WEIGHT__",-1,kYellow,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH160.root","H(160)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH170.root","H(170)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH180.root","H(180)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH190.root","H(190)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/ggH200.root","H(200)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH250.root","H(250)#rightarrow ZZ","__WEIGHT__",-1,kOrange+10,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH300.root","H(300)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH350.root","H(350)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH400.root","H(400)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH450.root","H(450)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH500.root","H(500)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH550.root","H(550)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	// EEEEplotter->addFile("eleEleEleEleEventTree/eventTree","/scratch/iross/HZZ/6Jul/ggH600.root","H(600)#rightarrow ZZ","__WEIGHT__",-1,kOrange-2,kBlack);
	EEEEplotter->addFile("muMuTauTauEventTreeID/eventTree","/scratch/iross/HZZ/6Jul/MM_DATA.root","DATA","1",1,kBlack,1);
}
