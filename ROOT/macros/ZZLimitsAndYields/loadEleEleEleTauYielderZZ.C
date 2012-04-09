{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEETyields = new EventYield();

	EEETyields->addFile("eleEleEleTauEventTreeID/eventTree","zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.24);
	EEETyields->addFile("eleEleEleTauEventTree/eventTree","zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.318);
	EEETyields->addFile("eleEleEleTauEventTree/eventTree","zz-latest/DATA_StdIso.root","DATA","1",1,137);
	
	EEETyields->addFile("eleEleEleTauEventTreeTauUp/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tUp","__WEIGHT__",10,0.24);
	EEETyields->addFile("eleEleEleTauEventTreeTauUp/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tUp","__WEIGHT__",10,0.318);

	EEETyields->addFile("eleEleEleTauEventTreeTauDown/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tDown","__WEIGHT__",10,0.24);
	EEETyields->addFile("eleEleEleTauEventTreeTauDown/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tDown","__WEIGHT__",10,0.318);
}
