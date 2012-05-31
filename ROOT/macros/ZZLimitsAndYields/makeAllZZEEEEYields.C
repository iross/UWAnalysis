{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleEleEleYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;
	
	// std::string EleEle ="eleele1Mass>60&&eleele1Pt1>20&&eleele1Pt2>10&&((eleele1Eta1<1.4442&&eleele1RelIso03B1<0.15)||(eleele1Eta1>1.566&&eleele1RelIso03E1<0.1))&&((eleele1Eta2<1.4442&&eleele1RelIso03B2<0.15)||(eleele1Eta2>1.566&&eleele1RelIso03E2<0.1))&&eleele1CiCTight1&5==5&&eleele1CiCTight2&5==5";
	// std::string IdIso =EleEle+"&&eleele2Pt1>7&&eleele2Pt2>7&&eleele2CiCTight1&1==1&&eleele2CiCTight2&1==1&&((eleele2Eta1<1.4442&&eleele2RelIso03B1<0.15)||(eleele2Eta1>1.566&&eleele2RelIso03E1<0.1))&&((eleele2Eta2<1.4442&&eleele2RelIso03B2<0.15)||(eleele2Eta2>1.566&&eleele2RelIso03E2<0.1))&&eleele2MissHits1<2&&eleele2MissHits2<2";
	// std::string selection =IdIso+"&&eleele2Charge==0";

	std::string LEleZ = "z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10&&z1Mass>60&&z1Mass<120";
	std::string SEEZcuts = "&&z2Charge==0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20";
	std::string SEEZcutsNoIso = "&&z2Charge==0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20";
	std::string selection=LEleZ+SEEZcuts;
	std::string selectionNoIso=LEleZ+SEEZcutsNoIso;

	//LP11
	// selection="z2Charge==0&&z1Mass>60&&z1Mass<120&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z2l1MissHits<2&&z2l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20";
	// selectionNoIso="z2Charge==0&&z1Mass>60&&z1Mass<120&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z2l1MissHits<2&&z2l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20";
	
	//post-LP11
	selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB<0.25&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&z2Mass>12";
	selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&z2Mass>12&&z2Mass>12";
	
	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");

	EEEEyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"eeee",massWindow,true);

}
