{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadMuMuMuTauYielder.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");
	std::string lumi="4680";

	//	MMMTyields->setggH(0.047092073,0.1867528644,0.235538009,0.2482359426,0.235895397,0.2482972635,0.2263894778,0.219726504,0.22301796288,0.219902801,0.2376002515,0.2260597399,0.20894910978,0.17483936174,0.1482050436,0.11925228408,0.0885693521,0.07874857802,0.0574070596,0.05219855015,0.03744332268);
	//	MMMTyields->setvbf(0.0065585163,0.0270161358,0.0290068819,0.0421748014,0.0331424354,0.0384829984,0.03665728716,0.03169918995,0.02969012936,0.0258364499,0.02799870276,0.02021592106,0.0195139629,0.01518218205,0.01470375213,0.01360763834,0.01185818742,0.00933250894,0.00958911578,0.00857112163,0.0074099965);
	MMMTyields->setggH(0.0421622776393,0.164919647049,0.206782725003,0.226596675491,0.212393031316,0.228315753627,0.206113095156,0.20249847126,0.204658283782,0.197938095003,0.211413770922,0.206509657704,0.187554806348,0.158376105387,0.131831048772,0.106735483681,0.0820061585488,0.0714504354806,0.0524902562772,0.0474618865319,0.0340754227585);
	MMMTyields->setvbf(0.00597557603967,0.0243397289999,0.0263079357706,0.0391336452163,0.0315603434984,0.0353451713149,0.0336463732456,0.0309871448515,0.0275978696554,0.0241363290437,0.025042178218,0.0190698452536,0.0175694605974,0.0146996812164,0.013691892154,0.0125486391478,0.010399484648,0.00857015447594,0.0084647505584,0.00808996941853,0.00673810052602);


	bool massWindow=false;
	// 
	// std::string MuMu ="HLT_Any&&mumuMass>60&&mumuPt1>15&&mumuPt2>15";
	// 
	// std::string IdIso =MuMu+"&&mutauPt1>10&&mutauPt2>15&&mutauDecayFinding&&mutauVBTFID&&mutauVLooseIso&&mutauStandardRelIso<0.15&&mutauEleVeto&&mutauMuVetoTight&&mutauCharge==0";
	// std::string selectionNoSumPt = IdIso+"30<=mutauMass&&mutauMass<=80";
	// std::string selectionNoWindow = IdIso+"(mutauPt1+mutauPt2)>30";
	// std::string selection =selectionNoSumPt+"&&(mutauPt1+mutauPt2)>30";

	std::string LMuZ = "z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l2Pt>10&&z1l1Pt>20";
	std::string SMTZcuts = "&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2l2Pt>15&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30";
	std::string selection=LMuZ+SMTZcuts;

	//from ZZEventYields
	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.2&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30&&z2l2Pt>20";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z2l2EleVeto&&z2l2MuVetoTight&&z2Charge==0&&z2Mass>30&&z2Mass<80&&(z2l2Pt+z2l1Pt)>30&&z2l2Pt>20";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2AbsIso<3&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.2&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2MuVetoTight&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");
	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2LooseIsoCombDB&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	selectionNoIso="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2MuVetoTight&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//new selection
	// selection="mumuMass>70&&mumuMass<110&&mutauEleVeto&&mutauLooseIso&&mutauMuVetoTight&&mutauRelPFIso<0.2&&mutauCharge==0&&mutauMass>30&&mutauMass<80&&(mutauPt2+mutauPt1)>30";

	MMMTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"MMMT",massWindow);

}

