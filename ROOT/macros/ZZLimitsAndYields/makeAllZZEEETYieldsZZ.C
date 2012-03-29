{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleEleTauYielderZZ.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");
	std::string lumi="4680";

	bool massWindow=false;

	// set gg and vbf H yields
	// 180, 190, 200, .... 600
	//EEETyields->setggH(0.0674157707,0.1952593756,0.2141120673,0.2151721946,0.2262421234,0.227967578,0.2201104611,0.2048963261,0.1959664248,0.1985845504,0.2273311745,0.21504051517,0.19334849754,0.16898478606,0.1431622256,0.12116853189,0.0904395526,0.07653683322,0.06190993784,0.04871893335,0.03749171952);
	//EEETyields->setvbf(0.0071767214,0.024335096,0.0300554613,0.0323051962,0.0320914402,0.0301465708,0.03573835773,0.0329789553,0.02714070272,0.0274965087,0.02464700774,0.02148645796,0.0194233845,0.01581836935,0.01363334734,0.01269960633,0.01130068,0.00981905153,0.00944820978,0.00758817303,0.0078906044);
	EEETyields->setggH(0.072271632196,0.197700555032,0.218301764853,0.22969412142,0.230825431011,0.237274337636,0.222571251385,0.20562969218,0.196852084031,0.191244406558,0.213093785792,0.212554703351,0.188723065533,0.161843826671,0.137197336906,0.114967647183,0.0870008236965,0.0733031004483,0.0592416662247,0.0465415777615,0.0358404199187);
	EEETyields->setvbf(0.00815644848955,0.0245549536946,0.031744786376,0.0326062646795,0.033614772592,0.0313291002497,0.0363867419449,0.0333916980294,0.0265629920305,0.0281857205093,0.0247696653066,0.0209165369313,0.0185413278281,0.0150356330221,0.0133314172968,0.0118513783191,0.0106515894871,0.00962650308271,0.00912927489932,0.00778852454124,0.0072037108673);


	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&elemuCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// 
	// std::string IdIso =EleEle+"&&eletauPt1>10&&eletauPt2>15&&eletauDecayFinding&&eletauCiCTight1&1==1&&eletauVLooseIso&&((eletauEta1<1.4442&&eletauRelIso03B<0.07)||(eletauEta1>1.566&&eletauRelIso03E<0.06))&&(eletauConvDistance>0.02||eletauDcotTheta>0.02)&&eletauMissHits<1&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0";
	// std::string selectionNoSumPt=IdIso+"&&eletauMass>30&&eletauMass<80";
	// std::string selectionNoWindow=IdIso+"&&(eletauPt1+eletauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(eletauPt1+eletauPt2)>30";

	std::string LEleZ = "z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string SETZcuts = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIso&&z2l2Pvbf5&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30";
	std::string SETZcutsNoIso = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2Pt>15&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30";
	std::string selection=LEleZ+SETZcuts;
	std::string selectionNoIso=LEleZ+SETZcutsNoIso;

	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIso&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20";
	selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2AbsIso<3&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	selectionNoIso=="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");

	//new selection
	// selection="eleeleMass>70&&eleeleMass<110&&elemuCiCLoose1&1==1&&eleeleCiCLoose2&1==1&&eleeleMissHits1<2&&eleeleMissHits2<2&&eletauCiCTight1&1==1&&eletauLooseIso&&eletauMissHits==0&&eleeleRelPFIso1<0.2&&eleeleRelPFIso2<0.2&&eletauRelPFIso<0.15&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0&&eletauMass>30&&eletauMass<80&&(eletauPt1+eletauPt2)>30";

	EEETyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"EEET",massWindow); 
}

