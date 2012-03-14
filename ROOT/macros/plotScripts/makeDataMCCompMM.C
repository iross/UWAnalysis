{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadDataMCPlotterMM.C");


	std::string lumi="976";
	// std::string lumi="253.6";

	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&eleeleCiCTight1&15==15&&eleeleCiCTight2&15==15";
	// std::string MuMu = "mumuMass>60&&mumuVBTFID1&&mumuVBTFID2&&tautauVLooseIso1&&tautauVLooseIso2";
	  // std::string IdIso =EleEle+"&&eletauPt1>15&&eletauPt2>15&&eletauDecayFinding&&eletauCiCTight1&5==5&&eletauVLooseIso&&((eletauEta1<1.4442&&eletauRelIso03B<0.07)||(eletauEta1>1.566&&eletauRelIso03E<0.06))&&(eletauConvDistance>0.02||eletauDcotTheta>0.02)&&eletauMissHits<1";

	  // std::string selection =IdIso+"&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0&&eletauMass>30&&eletauMass<80&&(eletauPt1+eletauPt2)>30";

	  // std::string NoHt = IdIso+"&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0&&eletauMass>30&&eletauMass<80";
	  // std::string NoMassWin = IdIso+"&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0&&(eletauPt1+eletauPt2)>30";

	// std::string selection = MuMu;
	
	// std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
	// std::string IdIso =MuMu+"&&tautauDecayFinding1&&tautauDecayFinding2";//"&&tautauVLooseIso1&&tautauVLooseIso2";
	// std::string selectionNoSumPt=IdIso+"&&tautauPt1>15&&tautauPt2>15&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauCharge==0";
	// std::string selection =selectionNoSumPt+"&&(tautauPt1+tautauPt2)>40";
	
	
	double ymax;
	//No iso, no vetoes
	std::string selection="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>15&&z2l2Pt>15";
	
	// selection="z1Mass>70&&z1Mass<110&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>15&&z2l2Pt>15";
	
	gROOT->ProcessLine(".!mkdir -p plots/DataMCPlots");

	ymax=900;
	TCanvas * eleele1MassSel =   EEEEplotter->makeStackedPlot("z1Mass",selection,lumi,30,60,120,"Leading Z Mass(#mu,#mu)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleele1MassSel->SaveAs("plots/DataMCPlots/mmtt_mumuMassSel.png");
	eleele1MassSel->SaveAs("plots/DataMCPlots/mmtt_mumuMassSel.pdf");  

	ymax=600;
	TCanvas * eleele2MassSel =   EEEEplotter->makeStackedPlot("z2Mass",selection,lumi,15,0,150,"Second Z Mass(#tau,#tau)","GeV/c",1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleele2MassSel->SaveAs("plots/DataMCPlots/mmtt_tautauMassSel.png");
	eleele2MassSel->SaveAs("plots/DataMCPlots/mmtt_tautauMassSel.pdf"); 
	
	ymax=500;
	TCanvas * mass4l =   EEEEplotter->makeStackedPlot("mass",selection,lumi,30,0,600,"ZZ Invariant Mass","GeV/c",1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("plots/DataMCPlots/mmtt_mass4l.png");
	mass4l->SaveAs("plots/DataMCPlots/mmtt_mass4l.pdf");
  
}

