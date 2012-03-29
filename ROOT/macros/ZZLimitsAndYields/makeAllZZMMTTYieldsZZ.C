{
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuTauTauYielderZZ.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");

	std::string lumi="4680";

	bool massWindow=false;

	//	MMTTyields->setggH(0.0326956346,0.1202432584,0.1566209576,0.1705310024,0.1860601361,0.1746813891,0.160854069,0.1719119235,0.17334567824,0.1686184596,0.2019111587,0.19511454886,0.17475572712,0.1530546352,0.1208613742,0.10480291569,0.08002831,0.06754198356,0.05190816206,0.04435349439,0.03129456836);
	//	MMTTyields->setvbf(0.0039487238,0.0180259335,0.0201123951,0.0264877148,0.0313851477,0.0255541538,0.03298078219,0.03138233945,0.03148073066,0.02324930106,0.02309336822,0.016825624,0.0185782775,0.0164004103,0.01178269038,0.01166181578,0.01134896122,0.01010115023,0.00879857954,0.00895637076,0.0077439597);
	MMTTyields->setggH(0.0297185817623,0.109535189946,0.14830559383,0.155363363926,0.17238189406,0.157843720367,0.149276048445,0.155597421397,0.155994969017,0.155604119603,0.183116572458,0.180893457517,0.16037098246,0.143613829739,0.11074350503,0.0953131501843,0.0752956680071,0.0626893866142,0.0477471398714,0.0403009885148,0.0294042639415);
	MMTTyields->setvbf(0.00359700688542,0.0177079936205,0.018974833389,0.0257892369541,0.027883093616,0.025197846195,0.0302399446026,0.0298407586382,0.0293295791194,0.0231777029494,0.0214261152286,0.0162922297011,0.0175997331342,0.015699295336,0.0115154769413,0.0113656714973,0.0105480569087,0.00920286769852,0.00821369029197,0.0083232438068,0.00712401761289);


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

	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIsoCombDB&&z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	selectionNoIso="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//new selection
	// selection="mumuMass>70&&mumuMass<110&&tautauEleVeto1&&tautauMediumIso1&&tautauMediumIso2&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauMass>30&&tautauMass<80&&(tautauPt1+tautauPt2)>40&&tautauCharge==0";

	MMTTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMTT",massWindow); 
}

