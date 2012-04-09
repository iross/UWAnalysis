{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *MMEMyields = new EventYield();

	MMEMyields->addFile("muMuEleMuEventTreeID/eventTree","zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.12);  
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.18);
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","zz-latest/DATA_StdIso.root","DATA","1",1,137);
	
}
