{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEMMyields = new EventYield();

	EEMMyields->addFile("eleEleMuMuEventTreeID/eventTree","zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.08);  
	EEMMyields->addFile("eleEleMuMuEventTree/eventTree","zz-latest/ZZ4L.root","ZZ","__WEIGHT__",0,0.66);
	EEMMyields->addFile("eleEleMuMuEventTree/eventTree","zz-latest/DATA_StdIso.root","DATA","1",1,137);	

}
