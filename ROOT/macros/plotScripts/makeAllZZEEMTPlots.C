{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadEleEleMuTauPlotter.C");

	std::string lumi="976";

	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&mutauPt1>10&&mutauPt2>15&&mutauDecayFinding&&mutauVBTFID&&mutauVLooseIso&&mutauStandardRelIso<0.15&&mutauEleVeto&&mutauMuVetoTight&&mutauCharge==0";
	// std::string selectionNoSumPt = IdIso+"30<=mutauMass&&mutauMass<=80";
	// std::string selectionNoWindow = IdIso+"(mutauPt1+mutauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(mutauPt1+mutauPt2)>30";
	
	std::string LEleZ = "z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string SMTZcuts = "&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30";
	std::string selectionNoWindow=LEleZ+"&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&(z2l2Pt+z2l1Pt)>30";
	std::string selectionNoSumPt=LEleZ+"&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	std::string selection=LEleZ+SMTZcuts;

	gROOT->ProcessLine(".!mkdir EEMTPlots");
	
	double ymax=0.2;
	TCanvas * eleeleMassSel =   EEMTplotter->makeStackedPlot("z1Mass",selection,lumi,20,60,120,"Mass(e,e)","GeV/c",61,0.9*ymax,0.85*ymax,0.6,0.6,false,0.0001,ymax);
	eleeleMassSel->SaveAs("EEMTPlots/eleeleMassSel.png");
	eleeleMassSel->SaveAs("EEMTPlots/eleeleMassSel.pdf");  

	TCanvas * mutauMassSel =   EEMTplotter->makeStackedPlot("z2Mass",selectionNoWindow,lumi,10,15,115,"Mass(#mu,#tau)","GeV/c",16,0.9*ymax,0.85*ymax,0.6,0.6,false,0.0001,ymax);
	mutauMassSel->SaveAs("EEMTPlots/mutauMassSel.png");
	mutauMassSel->SaveAs("EEMTPlots/mutauMassSel.pdf");  
	
	TCanvas * Ht =   EEMTplotter->makeStackedPlot("z2l1Pt+z2l2Pt",selectionNoSumPt,lumi,10,10,110,"H_{T}(#mu+#tau)","GeV/c",11,0.9*ymax,0.85*ymax,0.6,0.6,false,0.0001,ymax);
	Ht->SaveAs("EEMTPlots/Ht.png");
	Ht->SaveAs("EEMTPlots/Ht.pdf");  

	TCanvas * mass4l =   EEMTplotter->makeStackedPlot("mass",selection,lumi,15,100,400,"ZZ Invariant Mass","GeV/c",105,0.9*ymax,0.85*ymax,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("EEMTPlots/mass4l.png");
	mass4l->SaveAs("EEMTPlots/mass4l.pdf");
}

