{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleTauTauYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;

	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&tautauDecayFinding1&&tautauDecayFinding2&&tautauMediumIso1&&tautauMediumIso2";
	// std::string selectionNoSumPt=IdIso+"&&tautauPt1>15&&tautauPt2>15&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauCharge==0";
	// std::string selectionNoWindow =selectionNoSumPt+"&&(tautauPt1+tautauPt2)>40";
	// std::string selection = selectionNoWindow+"&&tautauMass>30&&tautauMass<80";

	std::string LEleZ = "z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string STTZcuts = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selection=LEleZ+STTZcuts;

	//new selection
	// selection="eleeleMass>70&&eleeleMass<110&&eleeleCiCLoose1&1==1&&eleeleCiCLoose2&1==1&&eleeleMissHits1<2&&eleeleMissHits2<2&&eleeleRelPFIso1<0.2&&eleeleRelPFIso2<0.2&&tautauMediumIso1&&tautauMediumIso2&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauMass>30&&tautauMass<80&&(tautauPt1+tautauPt2)>40&&tautauCharge==0";

	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1MediumIso&&z2l2MediumIso&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1AbsIso<2&&z2l2AbsIso<2&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");

	EETTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"EETT",massWindow);
  
}

