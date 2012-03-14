{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleMuTauYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;

	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&mutauPt1>10&&mutauPt2>15&&mutauDecayFinding&&mutauVBTFID&&mutauVLooseIso&&mutauStandardRelIso<0.15&&mutauEleVeto&&mutauMuVetoTight&&mutauCharge==0";
	// std::string selectionNoSumPt = IdIso+"30<=mutauMass&&mutauMass<=80";
	// std::string selectionNoWindow = IdIso+"(mutauPt1+mutauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(mutauPt1+mutauPt2)>30";

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	
	//new selection
	// selection="eleeleMass>70&&eleeleMass<110&&eleeleCiCLoose1&1==1&&eleeleCiCLoose2&1==1&&eleeleMissHits1<2&&eleeleMissHits2<2&&eleeleRelPFIso1<0.2&&eleeleRelPFIso2<0.2&&mutauLooseIso&&mutauRelPFIso<0.2&&mutauEleVeto&&mutauMuVetoTight&&mutauCharge==0&&mutauMass>30&&mutauMass<80&&(mutauPt2+mutauPt1)>30";

	std::string LEleZ = "z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string SMTZcuts = "&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30";
	std::string selection=LEleZ+SMTZcuts;
	
	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2LooseIso&&z2l1RelPfIsoRho<0.2&&z2l2EleVeto&&z2l2MuVetoTight&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20&&z2Mass>30&&z2Mass<80";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2EleVeto&&z2l2MuVetoTight&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20&&z2Mass>30&&z2Mass<80";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2AbsIso<3&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.2&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2MuVetoTight&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0";
	EEMTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"EEMT",massWindow);
}

