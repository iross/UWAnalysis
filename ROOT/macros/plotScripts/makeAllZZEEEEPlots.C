{
	gROOT->ProcessLine(".x $CMSSW_BASE/src/UWAnalysis/ROOT/macros/plotters/loadEleEleEleElePlotter.C");

	std::string lumi="4.8";

	// std::string EleEle ="eleele1Mass>60&&eleele1Pt1>20&&eleele1Pt2>10&&((eleele1Eta1<1.4442&&eleele1RelIso03B1<0.15)||(eleele1Eta1>1.566&&eleele1RelIso03E1<0.1))&&((eleele1Eta2<1.4442&&eleele1RelIso03B2<0.15)||(eleele1Eta2>1.566&&eleele1RelIso03E2<0.1))&&eleele1CiCTight1&5==5&&eleele1CiCTight2&5==5";
	// std::string IdIso =EleEle+"&&eleele2Pt1>7&&eleele2Pt2>7&&eleele2CiCTight1&1==1&&eleele2CiCTight2&1==1&&((eleele2Eta1<1.4442&&eleele2RelIso03B1<0.15)||(eleele2Eta1>1.566&&eleele2RelIso03E1<0.1))&&((eleele2Eta2<1.4442&&eleele2RelIso03B2<0.15)||(eleele2Eta2>1.566&&eleele2RelIso03E2<0.1))&&eleele2MissHits1<2&&eleele2MissHits2<2";
	// std::string selection =IdIso+"&&eleele2Charge==0";

	//std::string LEleZ = "z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	//std::string SEEZcuts = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l1CiCTight&9==9&&z2l2CiCTight&9==9&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20";

	//std::string selection=LEleZ+SEEZcuts;
    
    std::string selection="40 < z1Mass && z1Mass < 120 && 12 < z2Mass && z2Mass < 120 && mass > 100";
	
	gROOT->ProcessLine(".!mkdir EEEEPlots");
	double ymax=22;
	// TCanvas * eleele1MassSel =   EEEEplotter->makeStackedPlot("z1Mass",selection,lumi,32,40,120,"Leading Z Mass(e,e)","GeV/c",41,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	// eleele1MassSel->SaveAs("EEEEPlots/eleele1MassSel.png");
	// eleele1MassSel->SaveAs("EEEEPlots/eleele1MassSel.pdf");  
	// 
	// ymax = 18;
	// TCanvas * eleele2MassSel =   EEEEplotter->makeStackedPlot("z2Mass",selection,lumi,44,10,120,"Second Z Mass(e,e)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	// eleele2MassSel->SaveAs("EEEEPlots/eleele2MassSel.png");
	// eleele2MassSel->SaveAs("EEEEPlots/eleele2MassSel.pdf");  
	
	// TCanvas * eleele2Pt1 =   EEEEplotter->makeStackedPlot("eleele2Pt1",selection,lumi,20,0,100,"Leading e p_{T}","GeV/c",1,0.4,0.37,0.6,0.6,false,0.0001,0.5);
	// eleele2Pt1->SaveAs("EEEEPlots/ePt1.png");
	// eleele2Pt1->SaveAs("EEEEPlots/ePt1.pdf");  
	// 
	// TCanvas * eleele2Pt2 =   EEEEplotter->makeStackedPlot("eleele2Pt2",selection,lumi,20,0,100,"Second e p_{T}","GeV/c",1,0.4,0.37,0.6,0.6,false,0.0001,0.5);
	// eleele2Pt2->SaveAs("EEEEPlots/ePt2.png");
	// eleele2Pt2->SaveAs("EEEEPlots/ePt2.pdf");  
	ymax=16;
	TCanvas * mass4l =   EEEEplotter->makeStackedPlot("mass",selection,lumi,52,80,600,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	// mass4l->SaveAs("EEEEPlots/mass4l.png");
	// mass4l->SaveAs("EEEEPlots/mass4l.pdf");

    // ymax = 20;
    // TCanvas *plot = EEEEplotter->makeStackedPlot("z1l1RelPfIsoRho",selection,lumi,20,0,0.4,"z1l1 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z1l1Iso.png");
    // TCanvas *plot = EEEEplotter->makeStackedPlot("z1l2RelPfIsoRho",selection,lumi,20,0,0.4,"z1l2 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z1l2Iso.png");
    // TCanvas *plot = EEEEplotter->makeStackedPlot("z2l1RelPfIsoRho",selection,lumi,20,0,0.4,"z2l1 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z2l1Iso.png");
    // TCanvas *plot = EEEEplotter->makeStackedPlot("z2l2RelPfIsoRho",selection,lumi,20,0,0.4,"z2l2 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z2l2Iso.png");

    // TCanvas *plot = EEEEplotter->makeStackedPlot("z1l1SIP",selection,lumi,20,0,4,"z1l1 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z1l1SIP.png");
    // TCanvas *plot = EEEEplotter->makeStackedPlot("z1l2SIP",selection,lumi,20,0,4,"z1l2 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z1l2SIP.png");
    // TCanvas *plot = EEEEplotter->makeStackedPlot("z2l1SIP",selection,lumi,20,0,4,"z2l1 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z2l1SIP.png");
    // TCanvas *plot = EEEEplotter->makeStackedPlot("z2l2SIP",selection,lumi,20,0,4,"z2l2 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("EEEEPlots/z2l2SIP.png");
}

