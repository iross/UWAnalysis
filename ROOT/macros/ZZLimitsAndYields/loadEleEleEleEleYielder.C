{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYields.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *EEEEyields = new EventYield();

	EEEEyields->addFile("eleEleEleEleEventTreeID/eventTree","sandbox/zz-latest/DYJets.root","Zjets","__WEIGHT__",0,0.18);  
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/zz-latest/ZZ4L.root","ZZ","__WEIGHT__",0,2.63);
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/zz-latest/DATA.root","DATA","1",1,137);

	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H120.root","H120","__WEIGHT__",-1,137,"1.0*110","1.0*120");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H130.root","H130","__WEIGHT__",-1,137,"1.0*115","1.0*135");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H140.root","H140","__WEIGHT__",-1,137,"1.0*125","1.0*150");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H150.root","H150","__WEIGHT__",-1,137,"1.0*140","1.0*165");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H160.root","H160","__WEIGHT__",-1,137,"1.0*140","1.0*170");
	// EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/H170.root","H170","__WEIGHT__",-1,137,"1.0*150","1.0*175");
	
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH115.root","ggH115","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH120.root","ggH120","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH130.root","ggH130","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH140.root","ggH140","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH150.root","ggH150","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH160.root","ggH160","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH170.root","ggH170","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH180.root","ggH180","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH190.root","ggH190","__WEIGHT__",-1,137,"1.0*160","1.0*200");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH200.root","ggH200","__WEIGHT__",-1,137,"1.0*180","1.0*220");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH210.root","ggH210","__WEIGHT__",-1,137,"1.0*184","1.0*232");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH220.root","ggH220","__WEIGHT__",-1,137,"1.0*188","1.0*244");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH230.root","ggH230","__WEIGHT__",-1,137,"1.0*192","1.0*256");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH250.root","ggH250","__WEIGHT__",-1,137,"1.0*200","1.0*280");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH275.root","ggH275","__WEIGHT__",-1,137,"1.0*225","1.0*315");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH300.root","ggH300","__WEIGHT__",-1,137,"1.0*250","1.0*350");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH325.root","ggH325","__WEIGHT__",-1,137,"1.0*235","1.0*375");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH350.root","ggH350","__WEIGHT__",-1,137,"1.0*220","1.0*400");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH375.root","ggH375","__WEIGHT__",-1,137,"1.0*260","1.0*425");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH400.root","ggH400","__WEIGHT__",-1,137,"1.0*300","1.0*450");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH425.root","ggH425","__WEIGHT__",-1,137,"1.0*335","1.0*475");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH450.root","ggH450","__WEIGHT__",-1,137,"1.0*370","1.0*500");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH475.root","ggH475","__WEIGHT__",-1,137,"1.0*335","1.0*550");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH500.root","ggH500","__WEIGHT__",-1,137,"1.0*300","1.0*600");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH525.root","ggH525","__WEIGHT__",-1,137,"1.0*300","1.0*600");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH550.root","ggH550","__WEIGHT__",-1,137,"1.0*300","1.0*600");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH575.root","ggH575","__WEIGHT__",-1,137,"1.0*275","1.0*700");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/ggH600.root","ggH600","__WEIGHT__",-1,137,"1.0*250","1.0*800");
	
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf115.root","vbf115","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf120.root","vbf120","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf130.root","vbf130","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf140.root","vbf140","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf150.root","vbf150","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf160.root","vbf160","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf170.root","vbf170","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf180.root","vbf180","__WEIGHT__",-1,137,"1.0*160","1.0*190");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf190.root","vbf190","__WEIGHT__",-1,137,"1.0*160","1.0*200");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf200.root","vbf200","__WEIGHT__",-1,137,"1.0*180","1.0*220");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf210.root","vbf210","__WEIGHT__",-1,137,"1.0*184","1.0*232");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf220.root","vbf220","__WEIGHT__",-1,137,"1.0*188","1.0*244");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf230.root","vbf230","__WEIGHT__",-1,137,"1.0*192","1.0*256");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf250.root","vbf250","__WEIGHT__",-1,137,"1.0*200","1.0*280");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf275.root","vbf275","__WEIGHT__",-1,137,"1.0*225","1.0*315");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf300.root","vbf300","__WEIGHT__",-1,137,"1.0*250","1.0*350");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf325.root","vbf325","__WEIGHT__",-1,137,"1.0*235","1.0*375");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf350.root","vbf350","__WEIGHT__",-1,137,"1.0*220","1.0*400");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf375.root","vbf375","__WEIGHT__",-1,137,"1.0*260","1.0*425");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf400.root","vbf400","__WEIGHT__",-1,137,"1.0*300","1.0*450");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf425.root","vbf425","__WEIGHT__",-1,137,"1.0*335","1.0*475");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf450.root","vbf450","__WEIGHT__",-1,137,"1.0*370","1.0*500");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf475.root","vbf475","__WEIGHT__",-1,137,"1.0*335","1.0*550");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf500.root","vbf500","__WEIGHT__",-1,137,"1.0*300","1.0*600");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf525.root","vbf525","__WEIGHT__",-1,137,"1.0*300","1.0*600");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf550.root","vbf550","__WEIGHT__",-1,137,"1.0*300","1.0*600");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf575.root","vbf575","__WEIGHT__",-1,137,"1.0*275","1.0*700");
	EEEEyields->addFile("eleEleEleEleEventTree/eventTree","sandbox/higgs-latest/vbf600.root","vbf600","__WEIGHT__",-1,137,"1.0*250","1.0*800");
}
