{
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/eventYields.C+");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	setTDRStyle();

	EventYield *MMEMyields = new EventYield();

	MMEMyields->addFile("muMuEleMuEventTreeID/eventTree","sandbox/zz-latest/DYJets.root","Zjets","__WEIGHT__",0,0.12);  
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ZZ4L.root","ZZ","__WEIGHT__",0,0.18);
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/DATA.root","DATA","1",1,137);
	
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH120.root","H120","__WEIGHT__",-1,"70","170");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH130.root","H130","__WEIGHT__",-1,"80","180");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH140.root","H140","__WEIGHT__",-1,"90","190");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH150.root","H150","__WEIGHT__",-1,"100","200");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH160.root","H160","__WEIGHT__",-1,"110","210");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH170.root","H170","__WEIGHT__",-1,"120","220");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH180.root","H180","__WEIGHT__",-1,"130","230");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH190.root","H190","__WEIGHT__",-1,"140","240");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH200.root","H200","__WEIGHT__",-1,"100","400");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH250.root","H250","__WEIGHT__",-1,"200","300");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH300.root","H300","__WEIGHT__",-1,"250","350");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH350.root","H350","__WEIGHT__",-1,"300","400");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH400.root","H400","__WEIGHT__",-1,"350","450");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH450.root","H450","__WEIGHT__",-1,"400","500");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH500.root","H500","__WEIGHT__",-1,"450","550");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH550.root","H550","__WEIGHT__",-1,"500","600");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH600.root","H600","__WEIGHT__",-1,"550","650");

	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH120_presFix.root","H120","__WEIGHT__",-1,137,"0.6*80","0.6*120");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH130_presFix.root","H130","__WEIGHT__",-1,137,"0.6*90","0.6*130");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH140_presFix.root","H140","__WEIGHT__",-1,137,"0.6*100","0.6*140");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH150_presFix.root","H150","__WEIGHT__",-1,137,"0.6*100","0.6*150");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH160_presFix.root","H160","__WEIGHT__",-1,137,"1.0*100","1.0*160");
	// MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/zz-latest/ggH170_presFix.root","H170","__WEIGHT__",-1,137,"1.0*100","1.0*170");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH180.root","ggH180","__WEIGHT__",-1,137,"1.0*110","1.0*180");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH190.root","ggH190","__WEIGHT__",-1,137,"1.0*110","1.0*180");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH200.root","ggH200","__WEIGHT__",-1,137,"1.0*110","1.0*190");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH210.root","ggH210","__WEIGHT__",-1,137,"1.0*114","1.0*202");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH220.root","ggH220","__WEIGHT__",-1,137,"1.0*118","1.0*214");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH230.root","ggH230","__WEIGHT__",-1,137,"1.0*122","1.0*226");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH250.root","ggH250","__WEIGHT__",-1,137,"1.0*130","1.0*250");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH275.root","ggH275","__WEIGHT__",-1,137,"1.0*125","1.0*275");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH300.root","ggH300","__WEIGHT__",-1,137,"1.0*120","1.0*300");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH325.root","ggH325","__WEIGHT__",-1,137,"1.0*130","1.0*340");	
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH350.root","ggH350","__WEIGHT__",-1,137,"1.0*140","1.0*380");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH375.root","ggH375","__WEIGHT__",-1,137,"1.0*140","1.0*410");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH400.root","ggH400","__WEIGHT__",-1,137,"1.0*140","1.0*440");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH425.root","ggH425","__WEIGHT__",-1,137,"1.0*140","1.0*480");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH450.root","ggH450","__WEIGHT__",-1,137,"1.0*140","1.0*520");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH475.root","ggH475","__WEIGHT__",-1,137,"1.0*150","1.0*530");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH500.root","ggH500","__WEIGHT__",-1,137,"1.0*160","1.0*540");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH525.root","ggH525","__WEIGHT__",-1,137,"1.0*170","1.0*570");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH550.root","ggH550","__WEIGHT__",-1,137,"1.0*180","1.0*600");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH575.root","ggH575","__WEIGHT__",-1,137,"1.0*190","1.0*630");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/ggH600.root","ggH600","__WEIGHT__",-1,137,"1.0*200","1.0*660");
	
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf180.root","vbf180","__WEIGHT__",-1,137,"1.0*110","1.0*180");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf190.root","vbf190","__WEIGHT__",-1,137,"1.0*110","1.0*180");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf200.root","vbf200","__WEIGHT__",-1,137,"1.0*110","1.0*190");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf210.root","vbf210","__WEIGHT__",-1,137,"1.0*114","1.0*202");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf220.root","vbf220","__WEIGHT__",-1,137,"1.0*118","1.0*214");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf230.root","vbf230","__WEIGHT__",-1,137,"1.0*122","1.0*226");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf250.root","vbf250","__WEIGHT__",-1,137,"1.0*130","1.0*250");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf275.root","vbf275","__WEIGHT__",-1,137,"1.0*125","1.0*275");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf300.root","vbf300","__WEIGHT__",-1,137,"1.0*120","1.0*300");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf325.root","vbf325","__WEIGHT__",-1,137,"1.0*130","1.0*340");	
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf350.root","vbf350","__WEIGHT__",-1,137,"1.0*140","1.0*380");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf375.root","vbf375","__WEIGHT__",-1,137,"1.0*140","1.0*410");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf400.root","vbf400","__WEIGHT__",-1,137,"1.0*140","1.0*440");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf425.root","vbf425","__WEIGHT__",-1,137,"1.0*140","1.0*480");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf450.root","vbf450","__WEIGHT__",-1,137,"1.0*140","1.0*520");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf475.root","vbf475","__WEIGHT__",-1,137,"1.0*150","1.0*530");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf500.root","vbf500","__WEIGHT__",-1,137,"1.0*160","1.0*540");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf525.root","vbf525","__WEIGHT__",-1,137,"1.0*170","1.0*570");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf550.root","vbf550","__WEIGHT__",-1,137,"1.0*180","1.0*600");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf575.root","vbf575","__WEIGHT__",-1,137,"1.0*190","1.0*630");
	MMEMyields->addFile("muMuEleMuEventTree/eventTree","sandbox/higgs-latest/vbf600.root","vbf600","__WEIGHT__",-1,137,"1.0*200","1.0*660");
}
