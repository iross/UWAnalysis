{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuMuTauPlotter.C");

	std::string lumi="976";

	// std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
	// std::string IdIso =MuMu+"&&mutauPt1>10&&mutauPt2>15&&mutauDecayFinding&&mutauVBTFID&&mutauVLooseIso&&mutauStandardRelIso<0.15&&mutauEleVeto&&mutauMuVetoTight&&mutauCharge==0";
	// std::string selectionNoSumPt = IdIso+"30<=mutauMass&&mutauMass<=80";
	// std::string selectionNoWindow = IdIso+"(mutauPt1+mutauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(mutauPt1+mutauPt2)>30";
	
	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SMTZcuts = "&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30";
	std::string selectionNoWindow=LMuZ+"&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&(z2l2Pt+z2l1Pt)>30";
	std::string selectionNoSumPt=LMuZ+"&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	std::string selection=LMuZ+SMTZcuts;

	gROOT->ProcessLine(".!mkdir MMMTPlots");

	double ymax=0.22;
	TCanvas * mumuMassSel =   MMMTplotter->makeStackedPlot("z1Mass",selection,lumi,30,60,120,"Mass(#mu,#mu)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mumuMassSel->SaveAs("MMMTPlots/mumuMassSel.png");
	mumuMassSel->SaveAs("MMMTPlots/mumuMassSel.pdf");  

	ymax=0.2;
	TCanvas * mutauMassSel =   MMMTplotter->makeStackedPlot("z2Mass",selectionNoWindow,lumi,20,15,115,"Mass(#mu,#tau)","GeV/c",16,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mutauMassSel->SaveAs("MMMTPlots/mutauMassSel.png");
	mutauMassSel->SaveAs("MMMTPlots/mutauMassSel.pdf");

	TCanvas * Ht =   MMMTplotter->makeStackedPlot("z2l1Pt+z2l1Pt",selectionNoSumPt,lumi,15,10,160,"H_{T}(#tau+#mu)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	Ht->SaveAs("MMMTPlots/Ht.png");
	Ht->SaveAs("MMMTPlots/Ht.pdf");

	ymax=0.12;
	TCanvas * mass4l =   MMMTplotter->makeStackedPlot("mass",selection,lumi,15,100,400,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("MMMTPlots/mass4l.png");
	mass4l->SaveAs("MMMTPlots/mass4l.pdf");
}

