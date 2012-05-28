{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuMuTauYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;
	// 
	// std::string MuMu ="HLT_Any&&mumuMass>60&&mumuPt1>15&&mumuPt2>15";
	// 
	// std::string IdIso =MuMu+"&&mutauPt1>10&&mutauPt2>15&&mutauDecayFinding&&mutauVBTFID&&mutauVLooseIso&&mutauStandardRelIso<0.15&&mutauEleVeto&&mutauMuVetoTight&&mutauCharge==0";
	// std::string selectionNoSumPt = IdIso+"30<=mutauMass&&mutauMass<=80";
	// std::string selectionNoWindow = IdIso+"(mutauPt1+mutauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(mutauPt1+mutauPt2)>30";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SMTZcuts = "&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30";
	std::string selection=LMuZ+SMTZcuts;

	//from ZZEventYields
	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30&&z2l2Pt>20";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l2MuVetoTight&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30&&z2l2Pt>20";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2AbsIso<3&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.2&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2MuVetoTight&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	
	//new selection
	// selection="mumuMass>70&&mumuMass<110&&mutauEleVeto&&mutauLooseIso&&mutauMuVetoTight&&mutauRelPFIso<0.2&&mutauCharge==0&&mutauMass>30&&mutauMass<80&&(mutauPt2+mutauPt1)>30";
	
	MMMTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMMT",massWindow);

}

