{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEMTyields = new EventYield();

	EEMTyields->addFile("eleEleMuTauEventTreeID/eventTree","zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.07);  
	EEMTyields->addFile("eleEleMuTauEventTree/eventTree","zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.246);
	EEMTyields->addFile("eleEleMuTauEventTree/eventTree","zz-latest/DATA_StdIso.root","DATA","1",1,137);
	
	EEMTyields->addFile("eleEleMuTauEventTreeTauUp/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tUp","__WEIGHT__",10,0.07);  
	EEMTyields->addFile("eleEleMuTauEventTreeTauUp/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tUp","__WEIGHT__",10,0.246);
	
	EEMTyields->addFile("eleEleMuTauEventTreeTauDown/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tDown","__WEIGHT__",10,0.07);  
	EEMTyields->addFile("eleEleMuTauEventTreeTauDown/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tDown","__WEIGHT__",10,0.246);

}
