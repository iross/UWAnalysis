{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotters/loadMuMuMuMuPlotter.C");

	std::string lumi="976";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SMMZcuts = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20";
	std::string selection=LMuZ+SMMZcuts;
	selection="z1Mass>60&&z1Mass<120&&z2Charge==0&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.25&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20&&z1l2Pt>10&&z2l1Pt>5&&z2l2Pt>5";
	
	gROOT->ProcessLine(".!mkdir MMMMPlots");

	double ymax=5.2;
	TCanvas * mumu1MassSel =   MMMMplotter->makeStackedPlot("z1Mass",selection,lumi,20,60,120,"Leading Z Mass(#mu,#mu)","GeV/c",61,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mumu1MassSel->SaveAs("MMMMPlots/mumu1MassSel.png");
	mumu1MassSel->SaveAs("MMMMPlots/mumu1MassSel.pdf");  
	
	ymax=3;
	TCanvas * mumu2MassSel =   MMMMplotter->makeStackedPlot("z2Mass",selection,lumi,20,10,110,"Second Z Mass(#mu,#mu)","GeV/c",11,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mumu2MassSel->SaveAs("MMMMPlots/mumu2MassSel.png");
	mumu2MassSel->SaveAs("MMMMPlots/mumu2MassSel.pdf");  

	ymax=3;
	TCanvas * mass4l =   MMMMplotter->makeStackedPlot("mass",selection,lumi,30,100,400,"ZZ Invariant Mass","GeV/c",101,ymax*0.9,ymax*0.85,0.6,0.6,false,0.0001,ymax);
	mass4l->SaveAs("MMMMPlots/mass4l.png");
	mass4l->SaveAs("MMMMPlots/mass4l.pdf");
	
}

