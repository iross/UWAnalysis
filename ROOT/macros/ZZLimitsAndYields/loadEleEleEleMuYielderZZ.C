{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEEMyields = new EventYield();

	EEEMyields->addFile("eleEleEleMuEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.06);  
	EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.16);
	EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);

	// EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/ggH120_presFix.root","H120","__WEIGHT__",-1,137,"1.0*80","0.6*120");
	// EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/ggH130_presFix.root","H130","__WEIGHT__",-1,137,"1.0*90","0.6*130");
	// EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/ggH140_presFix.root","H140","__WEIGHT__",-1,137,"1.0*100","0.6*140");
	// EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/ggH150_presFix.root","H150","__WEIGHT__",-1,137,"1.0*100","0.6*150");
	// EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/ggH160_presFix.root","H160","__WEIGHT__",-1,137,"1.0*100","1.0*160");
	// EEEMyields->addFile("eleEleEleMuEventTree/eventTree","sandbox/zz-latest/ggH170_presFix.root","H170","__WEIGHT__",-1,137,"1.0*100","1.0*170");
}	
