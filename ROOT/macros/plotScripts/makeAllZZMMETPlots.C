{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuEleTauPlotter.C");

	std::string lumi="976";

	// std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";

	// std::string IdIso =MuMu+"&&eletauPt1>10&&eletauPt2>15&&eletauDecayFinding&&eleeleCiCTight&1==1&&eletauVLooseIso&&((eletauEta1<1.4442&&eletauRelIso03B<0.07)||(eletauEta1>1.566&&eletauRelIso03E<0.06))&&(eletauConvDistance>0.02||eletauDcotTheta>0.02)&&eletauMissHits<1&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0";
	// std::string selectionNoSumPt=IdIso+"&&eletauMass>30&&eletauMass<80";
	// std::string selectionNoWindow=IdIso+"&&(eletauPt1+eletauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(eletauPt1+eletauPt2)>30";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SETZcuts = "&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30";
	std::string SETZcutsNoWindow="&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&(z2l1Pt+z2l2Pt)>30";
	std::string SETZcutsNoSumPt="&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	std::string selectionNoWindow=LMuZ+SETZcutsNoWindow;
	std::string selectionNoSumPt=LMuZ+SETZcutsNoSumPt;
	std::string selection=LMuZ+SETZcuts;
	
	gROOT->ProcessLine(".!mkdir MMETPlots");

	double ymax=0.15;
	TCanvas * mumuMassSel =   MMETplotter->makeStackedPlot("z1Mass",selection,lumi,30,60,120,"Mass(#mu,#mu)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mumuMassSel->SaveAs("MMETPlots/mumuMassSel.png");
	mumuMassSel->SaveAs("MMETPlots/mumuMassSel.pdf");  

	ymax=0.6;
	TCanvas * eletauMassSel =   MMETplotter->makeStackedPlot("z2Mass",selectionNoWindow,lumi,20,25,125,"Mass(e,#tau)","GeV/c",26,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eletauMassSel->SaveAs("MMETPlots/eletauMassSel.png");
	eletauMassSel->SaveAs("MMETPlots/eletauMassSel.pdf");  

	ymax=0.1;
	TCanvas * Ht =   MMETplotter->makeStackedPlot("(z2l1Pt+z2l2Pt)",selectionNoSumPt,lumi,20,10,110,"H_{T}(#tau+e)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	Ht->SaveAs("MMETPlots/HT.png");
	Ht->SaveAs("MMETPlots/HT.pdf");  

	ymax=0.08;
	TCanvas * mass4l =   MMETplotter->makeStackedPlot("mass",selection,lumi,30,100,400,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("MMETPlots/mass4l.png");
	mass4l->SaveAs("MMETPlots/mass4l.pdf");
}

