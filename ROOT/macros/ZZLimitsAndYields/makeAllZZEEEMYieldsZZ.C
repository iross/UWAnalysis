{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleEleMuYielderZZ.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");
	std::string lumi="4680";

	bool massWindow=false;
	
	//set overlap corrected higgs yields
	//EEEMyields->setggH(0.0216324832,0.0890255482,0.1069236652,0.1227623174,0.1101355465,0.1126509066,0.1108824141,0.1066547453,0.11223501206,0.1073236822,0.1060235024,0.11725043141,0.10300271934,0.09252447871,0.080970801,0.06296702001,0.0516239211,0.0413842285,0.03557131456,0.02714556158,0.02285179198);
	//EEEMyields->setvbf(0.00189740175,0.0129822789,0.013336579,0.0166412994,0.0169607396,0.0198002399,0.01557072494,0.0160532448,0.01363485557,0.01437034588,0.01294685594,0.01034031302,0.0092875384,0.0071089192,0.00640577946,0.00658707632,0.00573344916,0.00585591142,0.00480787863,0.00461394958,0.00418412565);

	EEEMyields->setggH(0.0198058508578,0.0793228368225,0.0965096011894,0.106642472228,0.0974148000824,0.0986210481759,0.0981749344241,0.0947843195297,0.100519467665,0.0964586700383,0.096466379143,0.105651116109,0.0946677779076,0.0842463134337,0.0726644848617,0.0556270282952,0.0463200469923,0.0366535844796,0.0317652139065,0.0248139348353,0.0206622728688);
	EEEMyields->setvbf(0.00161538357461,0.010826522956,0.0122309352397,0.0144856969156,0.0152797494199,0.0167266866016,0.0138778903772,0.0142283836657,0.012668572506,0.0124386830475,0.0116784900888,0.00897128142027,0.00844209499251,0.00635363590901,0.00574563591452,0.00575294446888,0.00515620318518,0.00505648722457,0.00417753707615,0.00421601367247,0.00357502546263);


	//std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&elemuVBTFID&&elemuCiCTight1 &1==1&&elemuPt1>10&&elemuPt2>10&&elemuStandardRelIso2<0.15&&((elemuEta1<1.4442&&elemuRelIso03B<0.15)||(elemuEta1>1.566&&elemuRelIso03E<0.1)&&elemuMissHits<2)";
	// std::string selection =IdIso+"&&elemuCharge==0";

	std::string LEleZ = "z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string SEMZcuts = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25";
	std::string SEMZcutsNoIso = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0";
	std::string selection=LEleZ+SEMZcuts;
	std::string selectionNoIso=LEleZ+SEMZcutsNoIso;

	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2l1RelPfIsoRho<0.2&&z2l2RelPfIsoRho<0.25&&z2Charge==0";
	selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0";

	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB<0.25&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB<0.25&&z2Mass<90";
	selectionNoIso="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2Mass<90";

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");

	//new selection
	// selection="eleeleMass>70&&eleeleMass<110&&eleeleCiCLoose1&1==1&&eleeleCiCLoose2&1==1&&eleeleMissHits1<2&&eleeleMissHits2<2&&elemuMissHits<2&&elemuCiCLoose1&1==1&&elemuRelPFIso<0.2&&eleeleRelPFIso1<0.2&&eleeleRelPFIso2<0.2&&elemuPt1>10&&elemuPt2>10&&elemuCharge==0";

	EEEMyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"EEEM",massWindow); 
}

