{
	gROOT->ProcessLine(".x /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/macros/plotters/loadEleEleEleSCPlotter.C");

    std::string lumi = "20.0";

    std::string selection = "z1Charge == 0 && z1l1Pt > 20 && z1l2Pt > 10 && z2l1Pt > 10 && z2l2isEE && z1l1RelPfIsoRho < 0.2 && z1l2RelPfIsoRho < 0.2 && z2l1RelPfIsoRho < 0.2";

	//gROOT->ProcessLine(".!mkdir EEEMPlots");

	double ymax=6000.0;
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z1Mass",selection,lumi,30,60,120,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2e1x5/z2l2e5x5",selection,lumi,25,0.0,1.0,"Shower Shape","e1x5/e5x5",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2sigmaIetaIeta",selection,lumi,50,0.0,0.08,"Shower Shape","sigmaIetaIeta",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
}
