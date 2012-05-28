{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuEleEleYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;

  // std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
  // std::string IdIso =MuMu+"&&eleelePt1>7&&eleelePt2>7&&eleeleCiCTight1&1==1&&eleeleCiCTight2&1==1&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleMissHits1<2&&eleeleMissHits2<2";
  // std::string selection =IdIso+"&&eleeleCharge==0";

	//"z1Mass>60&&z1Mass<120&&z2Charge==0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z \
	  //2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20"

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20&&z1Mass>60&&z1Mass<120";
	std::string SEEZcuts = "&&z2Charge==0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20";
	std::string selection=LMuZ+SEEZcuts;

	//straight from ZZEventYields
	//LP11
	selection="z2Charge==0&&z1Mass>60&&z1Mass<120&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20";
	std::string selectionNoIso="z2Charge==0&&z1Mass>60&&z1Mass<120&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20";
	
	//post-LP
	selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB<0.25&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&z2Mass>20";
	selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&z2Mass>20";
	gROOT->ProcessLine(".!mkdir -p DataDrivenCards/MMEE");

	//new selection
	// selection="mumuMass>60&&mumuMass<120&&eleeleCharge==0&&eleeleCiCLoose1&1==1&&eleeleCiCLoose2&1==1&&eleeleMissHits1<2&&eleeleMissHits2<2&&eleeleRelPFIso1<0.2&&eleeleRelPFIso2<0.2";
	
	MMEEyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"mmee",massWindow,true);
  
}
