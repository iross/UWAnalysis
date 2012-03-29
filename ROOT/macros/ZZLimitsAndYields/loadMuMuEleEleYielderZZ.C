{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *MMEEyields = new EventYield();

	MMEEyields->addFile("muMuEleEleEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.03);  
	MMEEyields->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/ZZ4L.root","ZZ","__WEIGHT__",0,5.33);
	MMEEyields->addFile("muMuEleEleEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);

}
