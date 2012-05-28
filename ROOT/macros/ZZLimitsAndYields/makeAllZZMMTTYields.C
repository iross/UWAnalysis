{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuTauTauYielder.C");


	std::string lumi="1140";
	
	bool massWindow=false;

	//     std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
	// std::string IdIso =MuMu+"&&tautauDecayFinding1&&tautauDecayFinding2&&tautauMediumIso1&&tautauMediumIso2";
	// std::string selectionNoSumPt=IdIso+"&&tautauPt1>15&&tautauPt2>15&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauCharge==0";
	// std::string selectionNoWindow =selectionNoSumPt+"&&(tautauPt1+tautauPt2)>40";
	// std::string selection = selectionNoWindow+"&&tautauMass>30&&tautauMass<80";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string STTZcuts = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selection = LMuZ+STTZcuts;

	//straight from ZZEventYields

	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20";

	//post-LP11
//	selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1AbsIso<2&&z2l2AbsIso<2&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
//	selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");

	//new selection
	// selection="mumuMass>70&&mumuMass<110&&tautauEleVeto1&&tautauMediumIso1&&tautauMediumIso2&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauMass>30&&tautauMass<80&&(tautauPt1+tautauPt2)>40&&tautauCharge==0";

	MMTTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMTT",massWindow); 
}

