{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYieldsCrossSection.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *MMETyields = new EventYield();

	MMETyields->addFile("muMuEleTauEventTreeID/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets","__WEIGHT__",0,0.12);  
	MMETyields->addFile("muMuEleTauEventTree/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ","__WEIGHT__",0,0.318);
	MMETyields->addFile("muMuEleTauEventTree/eventTree","sandbox/zz-latest/DATA_dR03.root","DATA","1",1,137);
	
	MMETyields->addFile("muMuEleTauEventTreeTauUp/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tUp","__WEIGHT__",10,0.12);  
	MMETyields->addFile("muMuEleTauEventTreeTauUp/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tUp","__WEIGHT__",10,0.318);
	
	MMETyields->addFile("muMuEleTauEventTreeTauDown/eventTree","sandbox/zz-latest/DYJetsTemp.root","Zjets_CMS_scale_tDown","__WEIGHT__",10,0.12);  
	MMETyields->addFile("muMuEleTauEventTreeTauDown/eventTree","sandbox/zz-latest/ZZ4L_pythia.root","ZZ_CMS_scale_tDown","__WEIGHT__",10,0.318);
}
