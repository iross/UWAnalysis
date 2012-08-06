{
	gROOT->ProcessLine(".x /afs/hep.wisc.edu/cms/belknap/UWTest/src/UWAnalysis/ROOT/macros/plotters/loadEleEleEleSCPlotter.C");

    std::string lumi = "20.0";

    std::string selection = "z2l2isEE && z1Charge == 0";

    selection += "&& z1l1MissHits < 1 && z1l2MissHits < 1 && z2l1MissHits < 1";
    selection += "&& z1l1CiCLoose&9 == 9 && z1l2CiCLoose&9 == 9 && z2l1CiCTight&9 == 9";

    //TCanvas* test = EEESplotter->makeComparison("z1l1Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");
    //TCanvas* test = EEESplotter->makeComparison("z1l2Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");
    //TCanvas* test = EEESplotter->makeComparison("z2l1Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");
    //TCanvas* test = EEESplotter->makeComparison("z2l2Pt",selection,"1",25,0,150,"p_{T} [GeV/c]");

    //TCanvas* test = EEESplotter->makeComparison("z1l1RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    //TCanvas* test = EEESplotter->makeComparison("z1l2RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    //TCanvas* test = EEESplotter->makeComparison("z2l1RelPfIsoRho",selection,"1",10,0,0.5,"Rel Pf Iso");
    selection += "&& z1l1RelPfIsoRho < 0.4 && z1l2RelPfIsoRho < 0.4 && z2l1RelPfIsoRho < 0.4";

    TCanvas* test = EEESplotter->makeComparison("z2l2HE",selection,"1",20,0,1,"H/E");
    selection += "&& z2l2HE < 0.1";

    TCanvas* test = EEESplotter->makeComparison("z2l2sigmaIetaIeta",selection,"1",20,0,0.08,"sigma iEta iEta");
    selection += "&& z2l2sigmaIetaIeta < 0.04";

    TCanvas* test = EEESplotter->makeComparison("z2l2ecalRecHitSumEtDR03/z2l2Pt",selection,"1",25,0,1,"");
    selection += "&& z2l2ecalRecHitSumEtDR03/z2l2Pt < 0.05";

    TCanvas* test = EEESplotter->makeComparison("z1Mass",selection,"1",20,40,120,"M_{ee}");
    TCanvas* test = EEESplotter->makeComparison("z2Mass",selection,"1",20,40,120,"M_{eSC}");
    selection += "&& z2Mass < 70";
    
    double ymax = 5;
	TCanvas * eees = EEESplotter->makeStackedPlotMC("mass",selection,lumi,6,100,160,"M_{4l}","GeV/c^{2}",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);

    std::cout << selection << std::endl;
}
