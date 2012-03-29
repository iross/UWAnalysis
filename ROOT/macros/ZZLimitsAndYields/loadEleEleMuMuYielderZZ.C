{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEMMyields = new EventYield();

	EEMMyields->addFile("eleEleMuMuEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.08);  
	EEMMyields->addFile("eleEleMuMuEventTree/eventTree","sandbox/zz-latest/ZZ4L.root","ZZ","__WEIGHT__",0,0.66);
	EEMMyields->addFile("eleEleMuMuEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);	

}
