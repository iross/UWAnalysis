{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuEleMuPlotter.C");

	std::string lumi="976";

	// std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
	// std::string IdIso =MuMu+"&&elemuVBTFID&&elemuCiCTight&1==1&&elemuPt1>10&&elemuPt2>10&&elemuStandardRelIso2<0.15&&((elemuEta1<1.4442&&elemuRelIso03B<0.15)||(elemuEta1>1.566&&elemuRelIso03E<0.1)&&elemuMissHits<2)";
	// std::string selection =IdIso+"&&elemuCharge==0";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SEMZcuts = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25";
	std::string selection = LMuZ+SEMZcuts;

	gROOT->ProcessLine(".!mkdir MMEMPlots");

	double ymax=0.08;
	TCanvas * mumuMassSel =   MMEMplotter->makeStackedPlot("z1Mass",selection,lumi,20,60,120,"Mass(#mu,#mu)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mumuMassSel->SaveAs("MMEMPlots/mumuMassSel.png");
	mumuMassSel->SaveAs("MMEMPlots/mumuMassSel.pdf");  

	TCanvas * elemuMassSel =   MMEMplotter->makeStackedPlot("z2Mass",selection,lumi,20,15,115,"Mass(e,#mu)","GeV/c",16,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	elemuMassSel->SaveAs("MMEMPlots/elemuMassSel.png");
	elemuMassSel->SaveAs("MMEMPlots/elemuMassSel.pdf");  

	ymax=0.06;
	TCanvas * Ht =   MMEMplotter->makeStackedPlot("z2l1Pt+z2l2Pt",selection,lumi,20,10,110,"H_{T}(#mu+e)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	Ht->SaveAs("MMEMPlots/Ht.png");
	Ht->SaveAs("MMEMPlots/Ht.pdf");  

	TCanvas * mass4l =   MMEMplotter->makeStackedPlot("mass",selection,lumi,20,100,500,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("MMEMPlots/mass4l.png");
	mass4l->SaveAs("MMEMPlots/mass4l.pdf");
}

