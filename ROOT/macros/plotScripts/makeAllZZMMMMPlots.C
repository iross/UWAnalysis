{
	gROOT->ProcessLine(".x $CMSSW_BASE/src/UWAnalysis/ROOT/macros/plotters/loadMuMuMuMuPlotter.C");

	std::string lumi="4.8";

    /*
	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SMMZcuts = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20";
	std::string selection=LMuZ+SMMZcuts;
	selection="z1Mass>60&&z1Mass<120&&z2Charge==0&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.25&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20&&z1l2Pt>10&&z2l1Pt>5&&z2l2Pt>5";
	*/

	gROOT->ProcessLine(".!mkdir MMMMPlots");

    std::string selection="40 < z1Mass && z1Mass < 120 && 12 < z2Mass && z2Mass < 120 && mass > 100";
	
	gROOT->ProcessLine(".!mkdir MMMMPlots");
	double ymax=22;
	// TCanvas * eleele1MassSel =   MMMMplotter->makeStackedPlot("z1Mass",selection,lumi,32,40,120,"Leading Z Mass(e,e)","GeV/c",41,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	// eleele1MassSel->SaveAs("MMMMPlots/z1Mass.png");
	// eleele1MassSel->SaveAs("MMMMPlots/z1Mass.pdf");  
	// 
	// ymax = 18;
	// TCanvas * eleele2MassSel =   MMMMplotter->makeStackedPlot("z2Mass",selection,lumi,44,10,120,"Second Z Mass(e,e)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	// eleele2MassSel->SaveAs("MMMMPlots/z2Mass.png");
	// eleele2MassSel->SaveAs("MMMMPlots/z2Mass.pdf");  
	
	// TCanvas * eleele2Pt1 =   MMMMplotter->makeStackedPlot("eleele2Pt1",selection,lumi,20,0,100,"Leading e p_{T}","GeV/c",1,0.4,0.37,0.6,0.6,false,0.0001,0.5);
	// eleele2Pt1->SaveAs("MMMMPlots/ePt1.png");
	// eleele2Pt1->SaveAs("MMMMPlots/ePt1.pdf");  
	// 
	// TCanvas * eleele2Pt2 =   MMMMplotter->makeStackedPlot("eleele2Pt2",selection,lumi,20,0,100,"Second e p_{T}","GeV/c",1,0.4,0.37,0.6,0.6,false,0.0001,0.5);
	// eleele2Pt2->SaveAs("MMMMPlots/ePt2.png");
	// eleele2Pt2->SaveAs("MMMMPlots/ePt2.pdf");  
	ymax=10;
	TCanvas * mass4l =   MMMMplotter->makeStackedPlot("mass",selection,lumi,52,80,600,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	// mass4l->SaveAs("MMMMPlots/mass4l.png");
	// mass4l->SaveAs("MMMMPlots/mass4l.pdf");

    // ymax = 30;
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z1l1RelPfIsoRho",selection,lumi,20,0,0.4,"z1l1 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z1l1Iso.png");
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z1l2RelPfIsoRho",selection,lumi,20,0,0.4,"z1l2 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z1l2Iso.png");
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z2l1RelPfIsoRho",selection,lumi,20,0,0.4,"z2l1 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z2l1Iso.png");
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z2l2RelPfIsoRho",selection,lumi,20,0,0.4,"z2l2 Rel Iso","",0.025,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z2l2Iso.png");

    // ymax - 20;
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z1l1SIP",selection,lumi,20,0,4,"z1l1 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z1l1SIP.png");
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z1l2SIP",selection,lumi,20,0,4,"z1l2 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z1l2SIP.png");
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z2l1SIP",selection,lumi,20,0,4,"z2l1 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z2l1SIP.png");
    // TCanvas *plot = MMMMplotter->makeStackedPlot("z2l2SIP",selection,lumi,20,0,4,"z2l2 SIP","",0.1,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
    // plot->SaveAs("MMMMPlots/z2l2SIP.png");
	
}

