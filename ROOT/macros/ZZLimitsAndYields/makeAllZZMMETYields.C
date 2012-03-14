{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuEleTauYielder.C");
	
	std::string lumi="1140";
	
	bool massWindow=false;
		
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
	selection="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2LooseIso&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20&&EVENT!=286336207";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>30&&z2l2Pt>20&&EVENT!=286336207";

	//post-LP11
//	selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2AbsIso<3&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
//	selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	
	//new selection
	// selection="mumuMass>70&&mumuMass<110&&eletauEleVeto&&eleeleCiCTight&1==1&&eletauLooseIso&&eletauRelPFIso<0.15&&eletauMissHits==0&&eletauMuVeto&&eletauCharge==0&&eletauMass>30&&eletauMass<80&&(eletauPt1+eletauPt2)>30";
	
	MMETyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMET",massWindow);

}
