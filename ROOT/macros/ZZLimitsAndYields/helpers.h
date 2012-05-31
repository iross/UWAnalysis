#include "TH1F.h"
#include "TH2F.h"
#include "THStack.h"
#include "TTree.h"
#include "TChain.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TProfile.h"
#include <vector>
#include <math.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

std::string returnEEEECuts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB<0.25&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&z2Mass>12";
	}	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnEEMMCuts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB<0.25&&(z2l1Pt+z2l2Pt)>20&&z2Mass>20";
	} else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnMMEECuts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB<0.25&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&z2Mass>20";
	}	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnMMMMCuts(std::string cutType="selection"){
	if (cutType=="selection"){
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB<0.25&&(z2l1Pt+z2l2Pt)>20&&z2Mass>20";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnEEETCuts(std::string cutType="selection"){
	if (cutType=="selection"){
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2AbsIso<3&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnEEEMCuts(std::string cutType="selection"){
	if (cutType=="selection"){
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB<0.25&&z2Mass>30&&z2Mass<80";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnEEMTCuts(std::string cutType="selection"){
	if (cutType=="selection"){
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2AbsIso<3&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.2&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnEETTCuts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1AbsIso<2&&z2l2AbsIso<2&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnMMETCuts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l1CiCSuperTight&1==1&&z2l2AbsIso<3&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnMMEMCUts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB<0.25&&z2Mass>30&&z2Mass<80";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnMMMTCuts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l2EleVeto&&z2l2AbsIso<3&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.2&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

std::string returnMMTTCuts(std::string cutType="selection"){
	if (cutType=="selection") {
		return "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1AbsIso<2&&z2l2AbsIso<2&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80"; 
	}
	else std::cout << "Not a valid cut type!" << std::endl;
}

