{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEMTyields = new EventYield();

	EEMTyields->addFile("eleEleMuTauEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.07);  
	EEMTyields->addFile("eleEleMuTauEventTree/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.246);
	EEMTyields->addFile("eleEleMuTauEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);
	
	EEMTyields->addFile("eleEleMuTauEventTreeTauUp/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tUp","__WEIGHT__",10,0.07);  
	EEMTyields->addFile("eleEleMuTauEventTreeTauUp/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tUp","__WEIGHT__",10,0.246);
	
	EEMTyields->addFile("eleEleMuTauEventTreeTauDown/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tDown","__WEIGHT__",10,0.07);  
	EEMTyields->addFile("eleEleMuTauEventTreeTauDown/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tDown","__WEIGHT__",10,0.246);

}
