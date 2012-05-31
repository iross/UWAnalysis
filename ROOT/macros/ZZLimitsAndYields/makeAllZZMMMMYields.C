{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuMuMuYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;

	// std::string MuMu ="mumu1Mass>60&&mumu1Pt1>20&&mumu1Pt2>10 && mumu1StandardRelIso1<0.15 && mumu1StandardRelIso2<0.15";
	// std::string IdIso =MuMu+"&&mumu2VBTFID1&&mumu2VBTFID2&&mumu2Pt1>5&&mumu2Pt2>5&&mumu2StandardRelIso1<0.15&&mumu2StandardRelIso2<0.15";
	// std::string selection =IdIso+"&&mumu2Charge==0";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SMMZcuts = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20";
	std::string selection=LMuZ+SMMZcuts;

	//straight from ZZEventYields
	//LP11
	selection="z1Mass>60&&z1Mass<120&&z2Charge==0&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.25&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z2Charge==0&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20";
	
	//post-LP11
	selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB<0.25&&(z2l1Pt+z2l2Pt)>20&&z2Mass>20";
	selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&(z2l1Pt+z2l2Pt)>20&&z2Mass>20";
	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	
	//new selection
	// selection = "mumu1Mass>60&&mumu1Mass<120&&mumu2Charge==0";

	MMMMyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"mmmm",massWindow,true);

}

