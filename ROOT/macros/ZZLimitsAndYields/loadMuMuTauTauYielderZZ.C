{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *MMTTyields = new EventYield();

	MMTTyields->addFile("muMuTauTauEventTreeID/eventTree","zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.066);  
	MMTTyields->addFile("muMuTauTauEventTree/eventTree","zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.142);
	MMTTyields->addFile("muMuTauTauEventTree/eventTree","zz-latest/DATA_StdIso.root","DATA","1",1,137);
	
	MMTTyields->addFile("muMuTauTauEventTreeTauUp/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tUp","__WEIGHT__",10,0.066);  
	MMTTyields->addFile("muMuTauTauEventTreeTauUp/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tUp","__WEIGHT__",10,0.142);
	
	MMTTyields->addFile("muMuTauTauEventTreeTauDown/eventTree","zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tDown","__WEIGHT__",10,0.066);  
	MMTTyields->addFile("muMuTauTauEventTreeTauDown/eventTree","zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tDown","__WEIGHT__",10,0.142);

}
