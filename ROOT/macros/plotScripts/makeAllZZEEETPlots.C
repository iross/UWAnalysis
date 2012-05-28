{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadEleEleEleTauPlotter.C");

	std::string lumi="976";

	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&elemuCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&eletauPt1>10&&eletauPt2>15&&eletauDecayFinding&&eletauCiCTight1&1==1&&eletauVLooseIso&&((eletauEta1<1.4442&&eletauRelIso03B<0.07)||(eletauEta1>1.566&&eletauRelIso03E<0.06))&&(eletauConvDistance>0.02||eletauDcotTheta>0.02)&&eletauMissHits<1&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0";
	// std::string selectionNoSumPt=IdIso+"&&eletauMass>30&&eletauMass<80";
	// std::string selectionNoWindow=IdIso+"&&(eletauPt1+eletauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(eletauPt1+eletauPt2)>30";
	
	std::string LEleZ = "z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string SETZcuts = "&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30";
	std::string selectionNoWindow=LEleZ+"&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&(z2l1Pt+z2l2Pt)>30";
	std::string selectionNoSumPt=LEleZ+"&&z2l2EleVeto&&z2l1CiCTight&9==9&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	std::string selection=LEleZ+SETZcuts;
	
	gROOT->ProcessLine(".!mkdir EEETPlots");

	double ymax=0.2;
	TCanvas * eleeleMassSel =   EEETplotter->makeStackedPlot("z1Mass",selection,lumi,20,60,120,"Mass(e,e)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleeleMassSel->SaveAs("EEETPlots/eleeleMassSel.png");
	eleeleMassSel->SaveAs("EEETPlots/eleeleMassSel.pdf");  

	ymax=0.24;
	TCanvas * eletauMassSel =   EEETplotter->makeStackedPlot("z2Mass",selectionNoWindow,lumi,20,15,115,"Mass(e,#tau)","GeV/c",16,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eletauMassSel->SaveAs("EEETPlots/eletauMassSel.png");
	eletauMassSel->SaveAs("EEETPlots/eletauMassSel.pdf");  
	// 
	// TCanvas * eletauPt1 =   EEETplotter->makeStackedPlot("z1l1Pt",selection,lumi,20,0,100,"e p_{T}","GeV/c",40,0.042,0.038,0.6,0.6,false,0.0001,0.1);
	// eletauPt1->SaveAs("EEETPlots/elePt.png");
	// eletauPt1->SaveAs("EEETPlots/elePt.pdf");  
	// 
	// TCanvas * eletauPt2 =   EEETplotter->makeStackedPlot("z1l2Pt",selection,lumi,20,0,100,"#tau p_{T}","GeV/c",40,0.042,0.038,0.6,0.6,false,0.0001,0.1);
	// eletauPt2->SaveAs("EEETPlots/tauPt.png");
	// eletauPt2->SaveAs("EEETPlots/tauPt.pdf");  

	ymax=0.08;
	TCanvas * Ht =   EEETplotter->makeStackedPlot("z2l1Pt+z2l2Pt",selectionNoSumPt,lumi,20,10,110,"H_{T}(#tau+e)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	Ht->SaveAs("EEETPlots/Ht.png");
	Ht->SaveAs("EEETPlots/Ht.pdf");  

	ymax=0.08;
	TCanvas * mass4l =   EEETplotter->makeStackedPlot("mass",selection,lumi,30,100,400,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("EEETPlots/mass4l.png");
	mass4l->SaveAs("EEETPlots/mass4l.pdf");
}

