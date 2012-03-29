{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleMuTauYielderZZ.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");
	std::string lumi="4680";

	bool massWindow=false;

	//EEMTyields->setggH(0.0436000576,0.1794225752,0.1963324138,0.2082059674,0.2097533813,0.2140949029,0.2132145553,0.1994125118,0.20303097788,0.2071856632,0.2283927494,0.2163464802,0.19201637184,0.15562283646,0.1332867736,0.11039569479,0.0830905762,0.07075717084,0.05434089898,0.04625659583,0.0363022924);
	//EEMTyields->setvbf(0.00482244205,0.0222920483,0.0275429682,0.0297080984,0.0341847591,0.0330439657,0.0350667564,0.02669180525,0.02732216173,0.0278113429,0.02653623854,0.02113562364,0.0167315723,0.01421382695,0.01308113588,0.01173867676,0.01103832694,0.00997601931,0.00890139392,0.00838340316,0.00771401365);

	EEMTyields->setggH(0.0392914270725,0.159483910915,0.173711578319,0.1879577474,0.193180023839,0.194410371189,0.193770204352,0.183503676682,0.181081988598,0.186613461717,0.205291768727,0.20268673815,0.177424735535,0.144455966647,0.12137230809,0.100853886904,0.0783989121719,0.0661802630268,0.0510891408018,0.0425320618505,0.0338494044329);
	EEMTyields->setvbf(0.00489933990294,0.0212650352449,0.0252577315842,0.0276720480735,0.0325641029878,0.0292050366165,0.0334330905994,0.0264945450253,0.0258030951889,0.0256047260287,0.0240423439534,0.0190736058653,0.0159061754543,0.0132587303218,0.012216344206,0.0111869256844,0.0103950926713,0.00910122587795,0.00805649607507,0.00769566194918,0.00715591997794);


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

	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2LooseIsoCombDB&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	selectionNoIso="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2MuVetoTight&&z2l2Pt>10&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2AbsIso<3&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.2&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2MuVetoTight&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0";
	EEMTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"EEMT",massWindow);
}

