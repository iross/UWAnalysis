{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadEleEleEleMuPlotter.C");

	std::string lumi="976";

	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&elemuVBTFID&&elemuCiCTight1 &1==1&&elemuPt1>10&&elemuPt2>10&&elemuStandardRelIso2<0.15&&((elemuEta1<1.4442&&elemuRelIso03B<0.15)||(elemuEta1>1.566&&elemuRelIso03E<0.1)&&elemuMissHits<2)";
	// std::string selection =IdIso+"&&elemuCharge==0";

	std::string LEleZ = "z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string SEMZcuts = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25";
	std::string selection=LEleZ+SEMZcuts;
	
	gROOT->ProcessLine(".!mkdir EEEMPlots");

	double ymax=0.06;
	TCanvas * eleeleMassSel =   EEEMplotter->makeStackedPlot("z1Mass",selection,lumi,30,60,120,"Mass(e,e)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleeleMassSel->SaveAs("EEEMPlots/eleeleMassSel.png");
	eleeleMassSel->SaveAs("EEEMPlots/eleeleMassSel.pdf");  

	TCanvas * elemuMassSel =   EEEMplotter->makeStackedPlot("z2Mass",selection,lumi,15,10,100,"Mass(e,#mu)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	elemuMassSel->SaveAs("EEEMPlots/elemuMassSel.png");
	elemuMassSel->SaveAs("EEEMPlots/elemuMassSel.pdf");  

	// TCanvas * elemuPt1 =   EEEMplotter->makeStackedPlot("z1l1Pt",selection,lumi,20,0,100,"e p_{T}","GeV/c",1,0.019,0.0175,0.6,0.6,false,0.0001,0.025);
	// elemuPt1->SaveAs("EEEMPlots/ePt.png");
	// elemuPt1->SaveAs("EEEMPlots/ePt.pdf");  
	// 
	// TCanvas * elemuPt2 =   EEEMplotter->makeStackedPlot("z1l2Pt",selection,lumi,20,0,100,"#mu p_{T}","GeV/c",1,0.0225,0.021,0.6,0.6,false,0.0001,0.025);
	// elemuPt2->SaveAs("EEEMPlots/muPt.png");
	// elemuPt2->SaveAs("EEEMPlots/muPt.pdf");  

	// TCanvas * elemuHt =   EEEMplotter->makeStackedPlot("z2l1Pt+z2l2Pt",selection,lumi,20,0,100,"#mu p_{T} + e p_{T}","GeV/c",1,0.0225,0.021,0.6,0.6,false,0.0001,0.025);
	// elemuPt2->SaveAs("EEEMPlots/muPt.png");
	// elemuPt2->SaveAs("EEEMPlots/muPt.pdf");

	TCanvas * mass4l =   EEEMplotter->makeStackedPlot("mass",selection,lumi,30,100,400,"ZZ Invariant Mass","GeV/c",105,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("EEEMPlots/mass4l.png");
	mass4l->SaveAs("EEEMPlots/mass4l.pdf");
}

