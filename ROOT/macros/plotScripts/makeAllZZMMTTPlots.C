{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuTauTauPlotter.C");

	std::string lumi="976";

	//     std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
	// std::string IdIso =MuMu+"&&tautauDecayFinding1&&tautauDecayFinding2&&tautauMediumIso1&&tautauMediumIso2";
	// std::string selectionNoSumPt=IdIso+"&&tautauPt1>15&&tautauPt2>15&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauCharge==0";
	// std::string selectionNoWindow =selectionNoSumPt+"&&(tautauPt1+tautauPt2)>40";
	// std::string selection = selectionNoWindow+"&&tautauMass>30&&tautauMass<80";
	
	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string STTZcuts = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selectionNoWindow=LMuZ+"&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selectionNoSumPt=LMuZ+"&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge==0";
	selection = LMuZ+STTZcuts;
	
	gROOT->ProcessLine(".!mkdir MMTTPlots");

	double ymax=0.12;
	TCanvas * mumuMassSel =   MMTTplotter->makeStackedPlot("z1Mass",selection,lumi,20,60,120,"Mass(#mu,#mu)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mumuMassSel->SaveAs("MMTTPlots/mumuMassSel.png");
	mumuMassSel->SaveAs("MMTTPlots/mumuMassSel.pdf");  

	ymax=0.1;
	TCanvas * tautauMassSel =   MMTTplotter->makeStackedPlot("z2Mass",selectionNoWindow,lumi,20,15,115,"Mass(#tau,#tau)","GeV/c",16,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	tautauMassSel->SaveAs("MMTTPlots/tautauMassSel.png");
	tautauMassSel->SaveAs("MMTTPlots/tautauMassSel.pdf");  

	ymax=0.1;
	TCanvas * Ht =   MMTTplotter->makeStackedPlot("z2l1Pt+z2l2Pt",selectionNoSumPt,lumi,15,10,160,"H_{T}(#tau+#tau)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	Ht->SaveAs("MMTTPlots/Ht.png");
	Ht->SaveAs("MMTTPlots/Ht.pdf");  

	TCanvas * mass4l =   MMTTplotter->makeStackedPlot("mass",selection,lumi,15,100,400,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("MMTTPlots/mass4l.png");
	mass4l->SaveAs("MMTTPlots/mass4l.pdf");
 
}

