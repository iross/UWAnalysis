{
	gROOT->ProcessLine(".x /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/macros/plotters/loadMuMuEleSCPlotter.C");

    std::string lumi = "20.0";

    std::string selection = "z2l2isEE && z1Charge == 0";

    double ymax = 3000;

	//TCanvas * esee = MMESplotter->makeStackedPlotMC("z1Mass",selection,lumi,20,50,200,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

    //double ymax = 10000;
	//TCanvas * esee = MMESplotter->makeStackedPlotMC("mass","z1Charge == 0 && z2l2isEE",lumi,20,50,200,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

    //std::string selection = "z1Charge == 0 && z2l2isEE && z1l1Pt > 10 && z1l2Pt > 10 && z2l1Pt > 12 && z2l2Pt > 5 && z2Mass > 10";
    //selection += "&& 70 < z1Mass && z1Mass < 120";

	//gROOT->ProcessLine(".!mkdir EEEMPlots");

    //TCanvas* test = MMESplotter->makeComparison("z1l1Pt",selection,"1",25,0,150,"p^{e}_{T} [GeV/c]");
    //TCanvas* test = MMESplotter->makeComparison("z1l2Pt",selection,"1",25,0,150,"p^{SC}_{T} [GeV/c]");
    //TCanvas* test = MMESplotter->makeComparison("z2l1Pt",selection,"1",25,0,150,"p^{#mu}_{T} [GeV/c]");
    //TCanvas* test = MMESplotter->makeComparison("z2l2Pt",selection,"1",25,0,150,"p^{#mu}_{T} [GeV/c]");
    //TCanvas* test = MMESplotter->makeComparison("z1Mass",selection,"1",20,40,120,"M_{ee}");
    //TCanvas* test = MMESplotter->makeComparison("z2Mass",selection,"1",20,40,120,"M_{ee}");
    //TCanvas* test = MMESplotter->makeComparison("mass",selection,"1",20,100,200,"M_{ee}");
    //selection += "&& z1l1Pt > 10 && z1l2Pt > 10";

    //TCanvas* test = MMESplotter->makeComparison("z1l1Eta",selection,"1",40,-4,4,"#eta");
    //TCanvas* test = MMESplotter->makeComparison("z1l2Eta",selection,"1",40,-4,4,"#eta");
    //TCanvas* test = MMESplotter->makeComparison("z2l1Eta",selection,"1",40,-4,4,"#eta");
    //TCanvas* test = MMESplotter->makeComparison("z2l2Eta",selection,"1",40,-4,4,"#eta");

    //TCanvas* test = MMESplotter->makeComparison("z1l1RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    //TCanvas* test = MMESplotter->makeComparison("z2l2RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    //TCanvas* test = MMESplotter->makeComparison("z2l1RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    selection += "&& z1l1RelPfIsoRho < 0.2 && z1l2RelPfIsoRho < 0.2 && z2l1RelPfIsoRho < 0.2";
    
    //TCanvas* test = MMESplotter->makeComparison("z2l2HE",selection,"1",20,0,1,"H/E");
    selection += "&& z2l2HE < 0.1";

    TCanvas* test = MMESplotter->makeComparison("z2l2sigmaIetaIeta",selection,"1",20,0,0.08,"sigma iEta iEta");
    //TCanvas* test = MMESplotter->makeComparison("z2l2e1x5/z1l2e5x5",selection,"1",25,0,1,"e1x5/e5x5");
    //TCanvas* test = MMESplotter->makeComparison("z2l2e2x5/z1l2e5x5",selection,"1",25,0,1,"e2x5/e5x5");
    selection += "&& z2l2sigmaIetaIeta < 0.038";

    //TCanvas* test = MMESplotter->makeComparison("mass",selection,"1",25,100,300,"M_{4l} [GeV/c^{2}]");

    //TCanvas* test = MMESplotter->makeComparison("z1Mass",selection,"1",20,40,120,"M_{eSC}");
    //TCanvas* test = MMESplotter->makeComparison("z2Mass",selection,"1",20,40,120,"M_{ee}");

    //selection += "&& z1l2hcalDepth2TowerSumEtConeDR03 < 0.5 && z1l2hcalDepth1TowerSumEtConeDR03 < 2 && z1l2hcalTowerSumEtConeDR03 < 2 && z1l2ecalRecHitSumEtDR03 < 2";
    //TCanvas* test = MMESplotter->makeComparison("z2l2ecalRecHitSumEtDR03",selection,"1",20,0,20,"ecalRecHitEtDR03 [GeV]");
    //TCanvas* test = MMESplotter->makeComparison("z2l2hcalTowerSumEtConeDR03",selection,"1",20,0,20,"hcalTowerSumEtConeDR03 [GeV]");
    //TCanvas* test = MMESplotter->makeComparison("z2l2hcalDepth1TowerSumEtConeDR03",selection,"1",20,0,20,"hcalDepth1TowerSumEtConeDR03 [GeV]");
    //TCanvas* test = MMESplotter->makeComparison("z2l2hcalDepth2TowerSumEtConeDR03",selection,"1",20,0,5,"hcalDepth2TowerSumEtConeDR03 [GeV]");

    TCanvas* test = MMESplotter->makeComparison("z2l2ecalRecHitSumEtDR03/z2l2Pt",selection,"1",25,0,1,"");
    //TCanvas* test = MMESplotter->makeComparison("z2l2hcalTowerSumEtConeDR03/z2l2Pt",selection,"1",25,0,1,"");
    //TCanvas* test = MMESplotter->makeComparison("z2l2hcalDepth1TowerSumEtConeDR03/z2l2Pt",selection,"1",25,0,1,"");
    //TCanvas* test = MMESplotter->makeComparison("z2l2hcalDepth2TowerSumEtConeDR03/z2l2Pt",selection,"1",25,0,1,"");

    selection += "&& z2l2ecalRecHitSumEtDR03/z2l2Pt < 0.1";

    TCanvas* test = MMESplotter->makeComparison("z2Mass",selection,"1",20,40,120,"M_{ee}");
    TCanvas* test = MMESplotter->makeComparison("z1Mass",selection,"1",20,40,120,"M_{eSC}");
    selection += "&& z1Mass > 70";
    
    //TCanvas* test = MMESplotter->makeComparison("z1Mass",selection,"1",20,40,120,"M_{eSC}");
    double ymax = 10;
	TCanvas * esee = MMESplotter->makeStackedPlotMC("mass",selection,lumi,6,100,160,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

    //std::cout << selection << std::endl;
}
