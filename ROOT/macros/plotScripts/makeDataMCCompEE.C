{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadDataMCPlotterEE.C");

	std::string lumi="976";
	// std::string lumi="253.6";

	// std::string selection = MuMu;

	//selection used for eetautau/mumutautau plots in note -- with 22May-MC and 23May-Data
	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&tautauDecayFinding1&&tautauDecayFinding2&&tautauPt1>15&&tautauPt2>15"; //
	// std::string selection =IdIso+"&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauCharge==0&&(tautauPt1+tautauPt2)>40"; //&&tautauMass>30&&tautauMass<80

	std::string LEleZ = "z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string STTZcuts = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string STTZcutsNoIsoNoWindowNoVeto = "&&z2l1Pt>15&&z2l2Pt>15&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selectionNoSumPt=LEleZ+"&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge==0";
	std::string selectionNoWindow=LEleZ+"&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selection=LEleZ+STTZcutsNoIsoNoWindowNoVeto;
	
	// selection="z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>15&&z2l2Pt>15&&z1Mass>70&&z1Mass<110&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";

	// selection="z1Mass>70&&z1Mass<110&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";

	std::cout << "Selection used: \t" << selection << std::endl;

	gROOT->ProcessLine(".!mkdir -p plots/DataMCPlots");

	double ymax;

	ymax=900;
	TCanvas * eleele1MassSel =   EEEEplotter->makeStackedPlot("z1Mass",selection,lumi,30,60,120,"Leading Z Mass(e,e)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleele1MassSel->SaveAs("plots/DataMCPlots/eett_eleeleMassSel.png");
	eleele1MassSel->SaveAs("plots/DataMCPlots/eett_eleeleMassSel.pdf");  

	ymax=400;
	TCanvas * eleele2MassSel =   EEEEplotter->makeStackedPlot("z2Mass",selection,lumi,15,0,150,"Second Z Mass(#tau,#tau)","GeV/c",1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	eleele2MassSel->SaveAs("plots/DataMCPlots/eett_tautauMassSel.png");
	eleele2MassSel->SaveAs("plots/DataMCPlots/eett_tautauMassSel.pdf"); 

	ymax=500;
	TCanvas * mass4l =   EEEEplotter->makeStackedPlot("mass",selection,lumi,30,0,600,"ZZ Invariant Mass","GeV/c",1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("plots/DataMCPlots/eett_mass4l.png");
	mass4l->SaveAs("plots/DataMCPlots/eett_mass4l.pdf");
  
}

