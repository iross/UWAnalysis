{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuEleMuYielder.C");

	std::string lumi="1140";
	
	bool massWindow=false;

  // std::string MuMu ="mumuMass>60&&mumuPt1>20&&mumuPt2>10 && mumuStandardRelIso1<0.15 && mumuStandardRelIso2<0.15";
  // std::string IdIso =MuMu+"&&elemuVBTFID&&elemuCiCTight&1==1&&elemuPt1>10&&elemuPt2>10&&elemuStandardRelIso2<0.15&&((elemuEta1<1.4442&&elemuRelIso03B<0.15)||(elemuEta1>1.566&&elemuRelIso03E<0.1)&&elemuMissHits<2)";
  // std::string selection =IdIso+"&&elemuCharge==0";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SEMZcuts = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25";
	std::string selection = LMuZ+SEMZcuts;

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	
	//from ZZEventYields
	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25&&z2Charge==0";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB<0.25&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//new selection
	// selection="mumuMass>70&&mumuMass<110&&elemuPt1>10&&elemuPt2>10&&elemuCiCLoose&1==1&&elemuMissHits<2&&elemuRelPFIso<0.2&&elemuCharge==0"

	MMEMyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMEM",massWindow);
  
}

