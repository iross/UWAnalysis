{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadEleEleTauTauPlotter.C");

	std::string lumi="976";
	
	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&tautauDecayFinding1&&tautauDecayFinding2&&tautauMediumIso1&&tautauMediumIso2";
	// std::string selectionNoSumPt=IdIso+"&&tautauPt1>15&&tautauPt2>15&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauCharge==0";
	// std::string selectionNoWindow =selectionNoSumPt+"&&(tautauPt1+tautauPt2)>40";
	// std::string selection = selectionNoWindow+"&&tautauMass>30&&tautauMass<80";
	
	std::string LEleZ = "z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string STTZcuts = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selectionNoSumPt=LEleZ+"&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge==0";
	std::string selectionNoWindow=LEleZ+"&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selection=LEleZ+STTZcuts;
	
	gROOT->ProcessLine(".!mkdir EETTPlots");

	double ymax=0.1;
	TCanvas * eleeleMassSel =   EETTplotter->makeStackedPlot("z1Mass",selection,lumi,20,60,120,"Mass(e,e)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleeleMassSel->SaveAs("EETTPlots/eleeleMassSel.png");
	eleeleMassSel->SaveAs("EETTPlots/eleeleMassSel.pdf");  

	ymax=0.16;
	TCanvas * tautauMassSel =   EETTplotter->makeStackedPlot("z2Mass",selectionNoWindow,lumi,10,20,120,"Mass(#tau,#tau)","GeV/c",21,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	tautauMassSel->SaveAs("EETTPlots/tautauMassSel.png");
	tautauMassSel->SaveAs("EETTPlots/tautauMassSel.pdf");  

	// TCanvas * tautauPt1 =   EETTplotter->makeStackedPlot("z1l1Pt",selection,lumi,20,0,110,"Leading #tau p_{T}","GeV/c",1,0.16,0.17,0.6,0.6,false,0.0001,0.2);
	// tautauPt1->SaveAs("EETTPlots/tautauPt1.png");
	// tautauPt1->SaveAs("EETTPlots/tautauPt1.pdf");  
	// 
	// TCanvas * tautauPt2 =   EETTplotter->makeStackedPlot("z1l2Pt",selection,lumi,20,0,110,"Second Leading #tau p_{T}","GeV/c",40,0.14,0.12,0.6,0.6,false,0.0001,0.3);
	// tautauPt2->SaveAs("EETTPlots/tautauPt2.png");
	// tautauPt2->SaveAs("EETTPlots/tautauPt2.pdf");  
	ymax=0.1;
	TCanvas * Ht1 =   EETTplotter->makeStackedPlot("z2l1Pt+z2l2Pt",selectionNoSumPt,lumi,18,10,100,"H_{T}(#tau+#tau)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	Ht1->SaveAs("EETTPlots/Ht1.png");
	Ht1->SaveAs("EETTPlots/Ht1.pdf");  

	ymax=0.1;
	TCanvas * mass4l =   EETTplotter->makeStackedPlot("mass",selection,lumi,15,100,400,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("EETTPlots/mass4l.png");
	mass4l->SaveAs("EETTPlots/mass4l.pdf");

}

