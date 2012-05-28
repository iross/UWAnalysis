{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuEleElePlotter.C");

	std::string lumi="976";

	// std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
	// std::string IdIso =MuMu+"&&eleelePt1>7&&eleelePt2>7&&eleeleCiCTight1&1==1&&eleeleCiCTight2&1==1&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleMissHits1<2&&eleeleMissHits2<2";
	// std::string selection =IdIso+"&&eleeleCharge==0";

	std::string LMuZ = "z1Mass<120&&z1Mass>60&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SEEZcuts = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l1CiCTight&9==9&&z2l2CiCTight&9==9&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20&&z2Mass>60&&z2Mass<120";
	std::string selection=LMuZ+SEEZcuts;
	
	gROOT->ProcessLine(".!mkdir MMEEPlots");

	double ymax=4;
	TCanvas * mumuMassSel =   MMEEplotter->makeStackedPlot("z1Mass",selection,lumi,20,60,120,"Mass(#mu,#mu)","GeV/c",61,0.9*ymax,0.85*ymax,0.6,0.6,false,0.0001,ymax);
	mumuMassSel->SaveAs("MMEEPlots/mumuMassSel.png");
	mumuMassSel->SaveAs("MMEEPlots/mumuMassSel.pdf");  

	ymax=3;
	TCanvas * eleeleMassSel =   MMEEplotter->makeStackedPlot("z2Mass",selection,lumi,20,60,120,"Mass(e,e)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleeleMassSel->SaveAs("MMEEPlots/eleeleMassSel.png");
	eleeleMassSel->SaveAs("MMEEPlots/eleeleMassSel.pdf");  

	ymax=3;
	TCanvas * mass4l =   MMEEplotter->makeStackedPlot("mass",selection,lumi,15,150,300,"ZZ Invariant Mass","GeV/c",151,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("MMEEPlots/mass4l.png");
	mass4l->SaveAs("MMEEPlots/mass4l.pdf");
}

