{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuEleTauYielderZZ.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");	
	std::string lumi="4680";

	bool massWindow=false;

	//	MMETyields->setggH(0.063665636,0.1759601604,0.2196908592,0.2285103434,0.2346503247,0.2388702902,0.2354212939,0.2194020724,0.22389169382,0.2231980556,0.2426390228,0.24049528606,0.2097377773,0.17567916056,0.149883658,0.12942898446,0.0980270963,0.08644821672,0.06324044956,0.05355559431,0.04126247124);
	//	MMETyields->setvbf(0.0063769835,0.0256628413,0.0268222044,0.0326031668,0.039275879,0.034188599,0.03695331243,0.03195205935,0.03182003917,0.03231239754,0.02506044512,0.02376658306,0.0214723965,0.0188890133,0.01307868577,0.0130107421,0.01132354926,0.01118956119,0.00976963949,0.00907145543,0.00811643);
	MMETyields->setggH(0.0707629277803,0.18479251277,0.226166278398,0.22563364354,0.232427884433,0.244635174759,0.231182427114,0.217366662781,0.221584769007,0.214438745069,0.234978145189,0.234105572285,0.203787810913,0.171199118611,0.142046254566,0.121636594569,0.0940606897939,0.0817101187283,0.0614773219888,0.0509199735853,0.0390490540976);
	MMETyields->setvbf(0.0076484317684,0.0286663544418,0.0296175313345,0.034534582243,0.040601418939,0.0348488310841,0.0379362683427,0.0333530549217,0.0318205689954,0.0324516329103,0.0257916312382,0.0223131280934,0.0211747914508,0.0179073410128,0.0134359488135,0.012433227865,0.0106779300675,0.0108022516391,0.00912753860637,0.00889206191803,0.00771679192174);


	// std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
	// 
	// std::string IdIso =MuMu+"&&eletauPt1>10&&eletauPt2>15&&eletauDecayFinding&&eleeleCiCTight&1==1&&eletauVLooseIso&&((eletauEta1<1.4442&&eletauRelIso03B<0.07)||(eletauEta1>1.566&&eletauRelIso03E<0.06))&&(eletauConvDistance>0.02||eletauDcotTheta>0.02)&&eletauMissHits<1&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0";
	// std::string selectionNoSumPt=IdIso+"&&eletauMass>30&&eletauMass<80";
	// std::string selectionNoWindow=IdIso+"&&(eletauPt1+eletauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(eletauPt1+eletauPt2)>30";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SETZcuts = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30";
	std::string selection=LMuZ+SETZcuts;

	//from ZZEventYields
	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIso&&z2l1RelPfIsoRho<0.10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20&&EVENT!=286336207";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20&&EVENT!=286336207";

	//post-LP11
	//	selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2AbsIso<3&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//	selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&EVENT!=286336207";
	selectionNoIso="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&EVENT!=286336207";
	//new selection
	// selection="mumuMass>70&&mumuMass<110&&eletauEleVeto&&eleeleCiCTight&1==1&&eletauLooseIso&&eletauRelPFIso<0.15&&eletauMissHits==0&&eletauMuVeto&&eletauCharge==0&&eletauMass>30&&eletauMass<80&&(eletauPt1+eletauPt2)>30";

	MMETyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMET",massWindow);

}
