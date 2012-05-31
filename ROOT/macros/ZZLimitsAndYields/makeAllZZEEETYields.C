{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleEleTauYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;

	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&elemuCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// 
	// std::string IdIso =EleEle+"&&eletauPt1>10&&eletauPt2>15&&eletauDecayFinding&&eletauCiCTight1&1==1&&eletauVLooseIso&&((eletauEta1<1.4442&&eletauRelIso03B<0.07)||(eletauEta1>1.566&&eletauRelIso03E<0.06))&&(eletauConvDistance>0.02||eletauDcotTheta>0.02)&&eletauMissHits<1&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0";
	// std::string selectionNoSumPt=IdIso+"&&eletauMass>30&&eletauMass<80";
	// std::string selectionNoWindow=IdIso+"&&(eletauPt1+eletauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(eletauPt1+eletauPt2)>30";
	
	std::string LEleZ = "z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string SETZcuts = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIso&&z2l2Pt>15&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30";
	std::string SETZcutsNoIso = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2Pt>15&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30";
	std::string selection=LEleZ+SETZcuts;
	std::string selectionNoIso=LEleZ+SETZcutsNoIso;
	
	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIso&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20";
	selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20";
	
	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2AbsIso<3&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	
	//new selection
	// selection="eleeleMass>70&&eleeleMass<110&&elemuCiCLoose1&1==1&&eleeleCiCLoose2&1==1&&eleeleMissHits1<2&&eleeleMissHits2<2&&eletauCiCTight1&1==1&&eletauLooseIso&&eletauMissHits==0&&eleeleRelPFIso1<0.2&&eleeleRelPFIso2<0.2&&eletauRelPFIso<0.15&&eletauEleVeto&&eletauMuVeto&&eletauCharge==0&&eletauMass>30&&eletauMass<80&&(eletauPt1+eletauPt2)>30";
	
	EEETyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"EEET",massWindow); 
}

