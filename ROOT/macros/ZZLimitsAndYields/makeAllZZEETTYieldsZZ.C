{

	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/loadEleEleTauTauYielderZZ.C");
	gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");
	std::string lumi="4680";

	bool massWindow=false;

	//EETTyields->setggH(0.03591404185,0.1135885942,0.1294256954,0.1377170218,0.1583380885,0.1701631851,0.1715344195,0.1566189225,0.16365417954,0.1600095918,0.1705867538,0.18677805828,0.15660879682,0.14652565887,0.1203894472,0.09681933965,0.0743658252,0.06409630452,0.05187304554,0.04203829601,0.03252190944);
	//EETTyields->setvbf(0.0033607256,0.0152871072,0.0200519249,0.0231133498,0.0229924564,0.0254876488,0.03022282548,0.0293602514,0.02339958732,0.02388184022,0.02189798338,0.01918594614,0.0145996899,0.01420426715,0.01203575154,0.01124820262,0.01037191206,0.00975186315,0.00702751332,0.00765281683,0.00720982585);
	EETTyields->setggH(0.0344713151301,0.11300810217,0.132841851878,0.139308425031,0.150848502599,0.16140560233,0.163020199288,0.151719881286,0.153216216942,0.149838682695,0.160498549577,0.174735740765,0.151109388295,0.137776981014,0.114435690593,0.0906705480378,0.070724856673,0.060162719296,0.0481658576664,0.0389164656241,0.0302996170634);
	EETTyields->setvbf(0.00350147084478,0.0168161212401,0.0201935562229,0.0227262403035,0.0246042105596,0.0248493305605,0.029827983716,0.0289235985998,0.0241492213824,0.0233520092594,0.0216073256357,0.0179661965838,0.0145130255072,0.0139684081329,0.0121093980643,0.0107672111484,0.00982084812634,0.00898793655788,0.00697661484625,0.00713077880875,0.00694219823285);


	// std::string EleEle ="eleeleMass>60&&eleelePt1>20&&eleelePt2>10&&((eleeleEta1<1.4442&&eleeleRelIso03B1<0.15)||(eleeleEta1>1.566&&eleeleRelIso03E1<0.1))&&((eleeleEta2<1.4442&&eleeleRelIso03B2<0.15)||(eleeleEta2>1.566&&eleeleRelIso03E2<0.1))&&eleeleCiCTight1&5==5&&eleeleCiCTight2&5==5";
	// std::string IdIso =EleEle+"&&tautauDecayFinding1&&tautauDecayFinding2&&tautauMediumIso1&&tautauMediumIso2";
	// std::string selectionNoSumPt=IdIso+"&&tautauPt1>15&&tautauPt2>15&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauCharge==0";
	// std::string selectionNoWindow =selectionNoSumPt+"&&(tautauPt1+tautauPt2)>40";
	// std::string selection = selectionNoWindow+"&&tautauMass>30&&tautauMass<80";

	std::string LEleZ = "z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
	std::string STTZcuts = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0";
	std::string selection=LEleZ+STTZcuts;

	//new selection
	// selection="eleeleMass>70&&eleeleMass<110&&eleeleCiCLoose1&1==1&&eleeleCiCLoose2&1==1&&eleeleMissHits1<2&&eleeleMissHits2<2&&eleeleRelPFIso1<0.2&&eleeleRelPFIso2<0.2&&tautauMediumIso1&&tautauMediumIso2&&tautauEleVeto1&&tautauEleVeto2&&tautauMuVeto1&&tautauMuVeto2&&tautauMass>30&&tautauMass<80&&(tautauPt1+tautauPt2)>40&&tautauCharge==0";

	//LP11
	selection="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1MediumIso&&z2l2MediumIso&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20";
	std::string selectionNoIso="z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&(z2l1Pt+z2l2Pt)>40&&z2Charge==0&&z2l1Pt>20&&z2l2Pt>20";

	selection="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIsoCombDB&&z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	selectionNoIso="dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//post-LP11
	//selection="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1AbsIso<2&&z2l2AbsIso<2&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	//selectionNoIso="HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	gROOT->ProcessLine(".!mkdir -p hzz2l2t/");

	EETTyields->eventYield("mass",selection,selectionNoIso,lumi,30,0,8000,"EETT",massWindow);

}

