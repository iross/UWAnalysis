{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuEleMuYielderZZ.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");
	std::string lumi="4680";

	bool massWindow=false;

	//MMEMyields->setggH(0.02453967055,0.0904868722,0.1191883575,0.1267917308,0.122451544,0.1225545727,0.1165329562,0.1235215131,0.12168566678,0.1238520594,0.1244370778,0.13151182236,0.11311241746,0.1009387745,0.0814007006,0.07757532548,0.0546953664,0.04854170246,0.03854192136,0.03200427776,0.02341436318);
	//MMEMyields->setvbf(0.00306351875,0.0154055472,0.0125341997,0.0178377314,0.0188757029,0.0202832401,0.01621796946,0.017200543,0.01536523765,0.0154180962,0.01334097726,0.01052744446,0.0085830319,0.0088193808,0.00676873414,0.00657474587,0.00675935012,0.00554825224,0.00519205099,0.00486188633,0.00507435265);
	MMEMyields->setggH(0.0221735848185,0.0800495376897,0.106283214284,0.115763063563,0.108517629662,0.110295658457,0.105899985268,0.111151078947,0.110170242551,0.10982882267,0.113808045407,0.116249046517,0.104794954727,0.0908510722221,0.0729823558357,0.0682383577071,0.0499588016524,0.0433892423292,0.0352039700038,0.0283855573746,0.0213090976121);
	MMEMyields->setvbf(0.00271648302643,0.0138439417415,0.0115147018399,0.0162278662206,0.0172977952575,0.017977844243,0.0147851791465,0.0157192145963,0.0140437378418,0.0144100682569,0.0125627407821,0.00962065926591,0.00789787948467,0.0079354013277,0.00624812982123,0.00618364972071,0.0059503902849,0.00508815507473,0.00455871849396,0.00438273756589,0.00459315846783);


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

	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB<0.25&&z2Mass<90";
	selectionNoIso="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2Mass<90";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB<0.25&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//new selection
	// selection="mumuMass>70&&mumuMass<110&&elemuPt1>10&&elemuPt2>10&&elemuCiCLoose&1==1&&elemuMissHits<2&&elemuRelPFIso<0.2&&elemuCharge==0"

	MMEMyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMEM",massWindow);

}

