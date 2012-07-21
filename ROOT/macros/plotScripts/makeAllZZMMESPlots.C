{
	gROOT->ProcessLine(".x /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/macros/plotters/loadMuMuEleSCPlotter.C");

    std::string lumi = "20.0";

    //std::string selection = "z1Charge == 0 && z1l1Pt > 20 && z1l2Pt > 10 && z2l1Pt > 10 && z1l1RelPfIsoRho < 0.2 && z1l2RelPfIsoRho < 0.2 && z2l1RelPfIsoRho < 0.2";
    std::string selection = "z1Charge == 0 && z2l2isEE && z1l1Pt > 7 && z1l2Pt > 7 && z2l1Pt > 12 && z2l2Pt > 7 && z2Mass > 10";

	//gROOT->ProcessLine(".!mkdir EEEMPlots");

	double ymax=2000.0;

    //TCanvas* test = MMESplotter->makeComparison("z1l1Pt",selection,"1",20,0,120,"M_{ee}");
    //TCanvas* test = MMESplotter->makeComparison("z1l2Pt",selection,"1",20,0,120,"M_{ee}");
    //TCanvas* test = MMESplotter->makeComparison("z2l1Pt",selection,"1",20,0,120,"M_{ee}");
    //TCanvas* test = MMESplotter->makeComparison("z2l2Pt",selection,"1",20,0,120,"M_{ee}");

    selection += "&& z2l1RelPfIsoRho < 0.15";
    TCanvas* test = MMESplotter->makeComparison("z1l1RelPfIsoRho",selection,"1",20,0,1,"Rel Pf Iso");
    TCanvas* test = MMESplotter->makeComparison("z1l2RelPfIsoRho",selection,"1",20,0,1,"Rel Pf Iso");
    TCanvas* test = MMESplotter->makeComparison("z2l1RelPfIsoRho",selection,"1",20,0,1,"Rel Pf Iso");

    TCanvas* test = MMESplotter->makeComparison("z1Pt",selection,"1",20,0,100,"pT");
    TCanvas* test = MMESplotter->makeComparison("z2Pt",selection,"1",20,0,100,"pT");
    TCanvas* test = MMESplotter->makeComparison("z1Eta",selection,"1",20,-4.0,4.0,"#eta");
    TCanvas* test = MMESplotter->makeComparison("z2Eta",selection,"1",20,-4.0,4.0,"#eta");
	
    ymax = 200;
	TCanvas * mmes = MMESplotter->makeStackedPlotMC("mass",selection,lumi,20,100,150,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

	//TCanvas * mmes = MMESplotter->makeStackedPlotMC("z2l2e1x5/z2l2e5x5",selection,lumi,25,0.0,1.0,"Shower Shape","e1x5/e5x5",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	//TCanvas * mmes = MMESplotter->makeStackedPlotMC("z2l2sigmaIetaIeta",selection,lumi,50,0.0,0.08,"Shower Shape","sigmaIetaIeta",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
}
