{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *MMMMyields = new EventYield();

	MMMMyields->addFile("muMuMuMuEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.08);  
	MMMMyields->addFile("muMuMuMuEventTree/eventTree","sandbox/zz-latest/ZZ4L.root","ZZ","__WEIGHT__",0,3.78);
	MMMMyields->addFile("muMuMuMuEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);

}
