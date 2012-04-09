{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EETTyields = new EventYield();

	EETTyields->addFile("eleEleTauTauEventTreeID/eventTree","zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.084);  
	EETTyields->addFile("eleEleTauTauEventTree/eventTree","zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.123);
	EETTyields->addFile("eleEleTauTauEventTree/eventTree","zz-latest/DATA_StdIso.root","DATA","1",1,137);
	
	EETTyields->addFile("eleEleTauTauEventTreeTauUp/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tUp","__WEIGHT__",10,0.084);  
	EETTyields->addFile("eleEleTauTauEventTreeTauUp/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tUp","__WEIGHT__",10,0.123);
	
	EETTyields->addFile("eleEleTauTauEventTreeTauDown/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tDown","__WEIGHT__",10,0.084);  
	EETTyields->addFile("eleEleTauTauEventTreeTauDown/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tDown","__WEIGHT__",10,0.123);
}	
