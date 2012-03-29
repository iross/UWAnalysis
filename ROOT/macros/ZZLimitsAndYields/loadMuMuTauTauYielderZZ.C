{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *MMTTyields = new EventYield();

	MMTTyields->addFile("muMuTauTauEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.066);  
	MMTTyields->addFile("muMuTauTauEventTree/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.142);
	MMTTyields->addFile("muMuTauTauEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);
	
	MMTTyields->addFile("muMuTauTauEventTreeTauUp/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tUp","__WEIGHT__",10,0.066);  
	MMTTyields->addFile("muMuTauTauEventTreeTauUp/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tUp","__WEIGHT__",10,0.142);
	
	MMTTyields->addFile("muMuTauTauEventTreeTauDown/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tDown","__WEIGHT__",10,0.066);  
	MMTTyields->addFile("muMuTauTauEventTreeTauDown/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tDown","__WEIGHT__",10,0.142);

}
