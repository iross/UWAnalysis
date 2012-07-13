{
	gROOT->ProcessLine(".x /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/macros/plotters/loadEleEleEleSCPlotter.C");

    std::string lumi = "20.0";

    std::string selection = "z1l2isEE && z2Charge == 0";

    double ymax = 3000;

	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z1Mass",selection,lumi,20,50,200,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

    //double ymax = 10000;
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("mass","z1Charge == 0 && z2l2isEE",lumi,20,50,200,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

    //std::string selection = "z1Charge == 0 && z2l2isEE && z1l1Pt > 10 && z1l2Pt > 10 && z2l1Pt > 12 && z2l2Pt > 5 && z2Mass > 10";
    selection += "&& z1l1MissHits < 1 && z2l2MissHits < 1 && z2l1MissHits < 1";
    selection += "&& z1l1CiCLoose&9 == 9 && z2l2CiCTight&9 == 9 && z2l1CiCTight&9 == 9";
    //selection += "&& 70 < z1Mass && z1Mass < 120";

	//gROOT->ProcessLine(".!mkdir EEEMPlots");

    TCanvas* test = EEESplotter->makeComparison("z1l1Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");
    TCanvas* test = EEESplotter->makeComparison("z1l2Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");
    TCanvas* test = EEESplotter->makeComparison("z2l1Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");
    TCanvas* test = EEESplotter->makeComparison("z2l2Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");
    TCanvas* test = EEESplotter->makeComparison("z1Mass",selection,"1",20,40,120,"M_{ee}");
    TCanvas* test = EEESplotter->makeComparison("z2Mass",selection,"1",20,40,120,"M_{ee}");
    TCanvas* test = EEESplotter->makeComparison("mass",selection,"1",20,100,200,"M_{ee}");

    //TCanvas* test = EEESplotter->makeComparison("z1l1Eta",selection,"1",40,-4,4,"#eta");
    //TCanvas* test = EEESplotter->makeComparison("z1l2Eta",selection,"1",40,-4,4,"#eta");
    //TCanvas* test = EEESplotter->makeComparison("z2l1Eta",selection,"1",40,-4,4,"#eta");
    //TCanvas* test = EEESplotter->makeComparison("z2l2Eta",selection,"1",40,-4,4,"#eta");

    //TCanvas* test = EEESplotter->makeComparison("z1l1RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    //TCanvas* test = EEESplotter->makeComparison("z2l2RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    //TCanvas* test = EEESplotter->makeComparison("z2l1RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    //selection += "&& z1l1RelPfIsoRho < 0.2 && z2l2RelPfIsoRho < 0.2 && z2l1RelPfIsoRho < 0.2";
    
    //TCanvas* test = EEESplotter->makeComparison("z2l2sigmaIetaIeta",selection,"1",20,0,0.08,"sigma iEta iEta");
    //TCanvas* test = EEESplotter->makeComparison("z2l2e1x5/z2l2e5x5",selection,"1",25,0,1,"e1x5/e5x5");
    //TCanvas* test = EEESplotter->makeComparison("z2l2e2x5/z2l2e5x5",selection,"1",25,0,1,"e2x5/e5x5");

    //TCanvas* test = EEESplotter->makeComparison("mass",selection,"1",25,100,300,"M_{4l} [GeV/c^{2}]");

    //selection += "&& z2l2hcalTowerSumEtConeDR03 < 10";
    //TCanvas* test = EEESplotter->makeComparison("z1l2ecalRecHitSumEtDR03",selection,"1",20,0,50,"ecalRecHitEtDR03 [GeV]");
    //TCanvas* test = EEESplotter->makeComparison("z1l2hcalTowerSumEtConeDR03",selection,"1",20,0,40,"hcalTowerSumEtConeDR03 [GeV]");
    //TCanvas* test = EEESplotter->makeComparison("z1l2hcalDepth1TowerSumEtConeDR03",selection,"1",20,0,40,"hcalDepth1TowerSumEtConeDR03 [GeV]");
    //TCanvas* test = EEESplotter->makeComparison("z1l2hcalDepth2TowerSumEtConeDR03",selection,"1",20,0,5,"hcalDepth2TowerSumEtConeDR03 [GeV]");

    //TCanvas* test = EEESplotter->makeComparison("z2l2ecalRecHitSumEtDR03/z2l2Pt",selection,"1",20,0,1,"");
    //TCanvas* test = EEESplotter->makeComparison("z2l2hcalTowerSumEtConeDR03/z2l2Pt",selection,"1",20,0,1,"");
    //TCanvas* test = EEESplotter->makeComparison("z2l2hcalDepth1TowerSumEtConeDR03/z2l2Pt",selection,"1",20,0,1,"");
    //TCanvas* test = EEESplotter->makeComparison("z2l2hcalDepth2TowerSumEtConeDR03/z2l2Pt",selection,"1",20,0,1,"");

    //selection += "&& z2l2ecalRecHitSumEtDR03";
    
    //double ymax = 10000;
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("mass",selection,lumi,20,50,200,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

    //TCanvas* test = EEESplotter->makeComparison("z1Mass",selection,"1",40,0,120,"M_{ee}");
    //TCanvas* test = EEESplotter->makeComparison("z2Mass",selection,"1",40,0,120,"M_{ee}");

	//double ymax=4000.0;
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2Pt",selection,lumi,20,0,100,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z1l2Eta",selection,lumi,20,-4.0,4.0,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z1Mass",selection,lumi,10,40,120,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z1l1RelPfIsoRho",selection,lumi,10,0,1,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    //selection += "&& z1l1RelPfIsoRho < 0.2";
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z1l2RelPfIsoRho",selection,lumi,10,0,1,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    //selection += "&& z1l2RelPfIsoRho < 0.2";
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l1RelPfIsoRho",selection,lumi,20,0,2,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    //selection += "&& z2l1RelPfIsoRho < 0.2";

    //ymax = 40;
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2sigmaIetaIeta",selection,lumi,25,0,0.08,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2e1x5/z2l2e5x5",selection,lumi,25,0,1.0,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2e2x5/z2l2e5x5",selection,lumi,25,0,1.0,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	

    //selection += "&& ( z2l2e1x5/z2l2e5x5 > 0.3 || z2l2e2x5/z2l2e5x5 > 0.6 ) && z2l2hcalDepth2TowerSumEtConeDR03 < 1 && z2l2ecalRecHitSumEtDR03 < 3.5";

    //ymax = 200;
    //TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2hcalDepth1TowerSumEtConeDR03",selection,lumi,20,0,40,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    //TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2hcalDepth2TowerSumEtConeDR03",selection,lumi,20,0,5,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    //TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2ecalRecHitSumEtDR03",selection,lumi,20,0,50,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    //TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2hcalTowerSumEtConeDR03",selection,lumi,20,0,40,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z1Mass",selection,lumi,20,40,120,"M_{ee}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
  

	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2e1x5/z2l2e5x5",selection,lumi,25,0.0,1.0,"Shower Shape","e1x5/e5x5",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	//TCanvas * eees = EEESplotter->makeStackedPlotMC("z2l2sigmaIetaIeta",selection,lumi,50,0.0,0.08,"Shower Shape","sigmaIetaIeta",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
}
