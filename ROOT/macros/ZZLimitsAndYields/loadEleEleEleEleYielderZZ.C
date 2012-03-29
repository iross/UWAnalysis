{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEEEyields = new EventYield();

	EEEEyields->addFile("eleEleEleEleEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.18);  
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/zz-latest/ZZ4L.root","ZZ","__WEIGHT__",0,2.63);
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);

	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H120.root","H120","__WEIGHT__",-1,137,"1.0*110","1.0*120");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H130.root","H130","__WEIGHT__",-1,137,"1.0*115","1.0*135");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H140.root","H140","__WEIGHT__",-1,137,"1.0*125","1.0*150");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H150.root","H150","__WEIGHT__",-1,137,"1.0*140","1.0*165");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H160.root","H160","__WEIGHT__",-1,137,"1.0*140","1.0*170");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H170.root","H170","__WEIGHT__",-1,137,"1.0*150","1.0*175");
	
}
