#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include <math.h> 
#include "TMath.h" 
#include <limits>

void readdir(TDirectory *dir,optutl::CommandLineParser parser,char TreeToUse[]); 
float weightMuID(float leptonPt, float leptonEta);
float weightEleID(float leptonPt, float leptonEta) ;
float weightMuISOZ(float leptonPt, float leptonEta) ;
float weightEleISOZ(float leptonPt, float leptonEta) ;
float weightMuHLT8(float leptonPt, float leptonEta) ;
float weightMuHLT17(float leptonPt, float leptonEta) ;
float weightEleHLT8(float leptonPt, float leptonEta) ;
float weightEleHLT17(float leptonPt, float leptonEta) ;
float weightEleSIP(float leptonPt, float leptonEta);
float weightMuSIP(float leptonPt, float leptonEta);
float weightMuISOZ1(float leptonPt, float leptonEta) ;
float weightMuISOZ2(float leptonPt, float leptonEta) ;
float weightEleISOZ1(float leptonPt, float leptonEta) ;
float weightEleISOZ2(float leptonPt, float leptonEta) ;

float weightCalculator(float pt1,float eta1,float pt2,float eta2,float pt3,float eta3,float pt4,float eta4,char TreeToUse[],int EVENT) {

	float weight=1.0 ;

	if(std::string(TreeToUse).find("muMuTauTauEventTree")!= std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2) ;
//		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("muMuEleMuEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightEleID(pt3,eta3)*weightMuID(pt4,eta4) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2)*weightEleISOZ1(pt3,eta3)*weightMuISOZ1(pt4,eta4) ;
//		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("muMuEleTauEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightEleID(pt3,eta3) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2)*weightEleISOZ2(pt3,eta3);
//		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("muMuMuTauEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightMuID(pt3,eta3) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2)*weightMuISOZ2(pt3,eta3);
//		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	if(std::string(TreeToUse).find("eleEleTauTauEventTree")!= std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2) ;
//		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("eleEleEleMuEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightEleID(pt3,eta3)*weightMuID(pt4,eta4) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2)*weightEleISOZ1(pt3,eta3)*weightMuISOZ1(pt4,eta4) ;
//		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("eleEleEleTauEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightEleID(pt3,eta3) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2)*weightEleISOZ2(pt3,eta3);
//		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("eleEleMuTauEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightMuID(pt3,eta3) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2)*weightMuISOZ2(pt3,eta3);
//		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("eleEleEleEleEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightEleID(pt3,eta3)*weightEleID(pt4,eta4);
		weight = weight*weightEleSIP(pt1,eta1)*weightEleSIP(pt2,eta2)*weightEleSIP(pt3,eta3)*weightEleSIP(pt4,eta4);
		weight = weight*weightEleISOZ(pt1,eta1)*weightEleISOZ(pt2,eta2)*weightEleISOZ(pt3,eta3)*weightEleISOZ(pt4,eta4);
//		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2);
	}
	else if(std::string(TreeToUse).find("eleEleMuMuEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightMuID(pt3,eta3)*weightMuID(pt4,eta4);
		weight = weight*weightEleSIP(pt1,eta1)*weightEleSIP(pt2,eta2)*weightMuSIP(pt3,eta3)*weightMuSIP(pt4,eta4);
		weight = weight*weightEleISOZ(pt1,eta1)*weightEleISOZ(pt2,eta2)*weightMuISOZ(pt3,eta3)*weightMuISOZ(pt4,eta4);
//		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2);
	}
	else if(std::string(TreeToUse).find("muMuEleEleEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightEleID(pt3,eta3)*weightEleID(pt4,eta4);
		weight = weight*weightMuSIP(pt1,eta1)*weightMuSIP(pt2,eta2)*weightEleSIP(pt3,eta3)*weightEleSIP(pt4,eta4);
		weight = weight*weightMuISOZ(pt1,eta1)*weightMuISOZ(pt2,eta2)*weightEleISOZ(pt3,eta3)*weightEleISOZ(pt4,eta4);
//		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2);
	}
	else if(std::string(TreeToUse).find("muMuMuMuEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightMuID(pt3,eta3)*weightMuID(pt4,eta4);
		weight = weight*weightMuSIP(pt1,eta1)*weightMuSIP(pt2,eta2)*weightMuSIP(pt3,eta3)*weightMuSIP(pt4,eta4);
		weight = weight*weightMuISOZ(pt1,eta1)*weightMuISOZ(pt2,eta2)*weightMuISOZ(pt3,eta3)*weightMuISOZ(pt4,eta4);
//		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2);
	}

	return weight;
}


int main (int argc, char* argv[]) 
{
	optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
	parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__HLT__");
	parser.parseArguments (argc, argv);

	char TreeToUse[80]="first" ;

	TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");
	readdir(f,parser,TreeToUse);
	f->Close();

} 


void readdir(TDirectory *dir,optutl::CommandLineParser parser, char TreeToUse[]) 
{
	TDirectory *dirsav = gDirectory;
	TIter next(dir->GetListOfKeys());
	TKey *key;
	char stringA[80]="first"; 
	while ((key = (TKey*)next())) {

		printf("Found key=%s \n",key->GetName());
		if(!strcmp(stringA,TreeToUse)) sprintf(TreeToUse,"%s",key->GetName());
		printf("Strings %s %s \n",TreeToUse,stringA);
		TObject *obj = key->ReadObj();

		if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
			dir->cd(key->GetName());
			TDirectory *subdir = gDirectory;
			readdir(subdir,parser,TreeToUse);
			dirsav->cd();
		}
		else if(obj->IsA()->InheritsFrom(TTree::Class())) {
			TTree *t = (TTree*)obj;
			float weight = 1.0;
			TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());

			float pt1;
			float eta1;
			float pt2;
			float eta2;
			float pt3;
			float eta3;
			float pt4;
			float eta4;
			int EVENT;
			t->SetBranchAddress("z1l1Pt",&pt1);
			t->SetBranchAddress("z1l1Eta",&eta1);
			t->SetBranchAddress("z1l2Pt",&pt2);
			t->SetBranchAddress("z1l2Eta",&eta2);
			t->SetBranchAddress("z2l1Pt",&pt3);
			t->SetBranchAddress("z2l1Eta",&eta3);
			t->SetBranchAddress("z2l2Pt",&pt4);
			t->SetBranchAddress("z2l2Eta",&eta4);
			t->SetBranchAddress("EVENT",&EVENT);

			printf("Found tree -> weighting\n");
			for(Int_t i=0;i<t->GetEntries();++i)
			{
				t->GetEntry(i);
				weight=weightCalculator(pt1,eta1,pt2,eta2,pt3,eta3,pt4,eta4,TreeToUse,EVENT);

				newBranch->Fill();
			}

			t->Write("",TObject::kOverwrite);
			strcpy(TreeToUse,stringA) ;
		}
	}
}


float weightMuID(float leptonPt, float leptonEta){
	float weight=1.0;

	if (leptonPt<10){
		if( abs(leptonEta) < 1.44) weight=1.021;
		else weight=0.971;
	} else if (leptonPt>10&&leptonPt<20){
		if (abs(leptonEta) < 0.90) weight=0.999;
		else if (abs(leptonEta) < 1.20) weight=0.984;
		else if (abs(leptonEta) < 1.6) weight=0.989;
		else if (abs(leptonEta) < 2.1) weight=0.987;
		else weight=0.985;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.90) weight=0.997;
		else if (abs(leptonEta) < 1.20) weight=1.000;
		else if (abs(leptonEta) < 1.6) weight=0.983;
		else if (abs(leptonEta) < 2.1) weight=0.986;
		else weight=0.984;
	} else if (leptonPt>30&&leptonPt<50){
		if (abs(leptonEta) < 0.90) weight=0.996;
		else if (abs(leptonEta) < 1.20) weight=0.994;
		else if (abs(leptonEta) < 1.6) weight=0.984;
		else if (abs(leptonEta) < 2.1) weight=0.983;
		else weight=0.987;
	} else {
		if (abs(leptonEta) < 0.90) weight=0.995;
		else if (abs(leptonEta) < 1.20) weight=0.994;
		else if (abs(leptonEta) < 1.6) weight=0.988;
		else if (abs(leptonEta) < 2.1) weight=0.981;
		else weight=0.991;
	}

	return weight ;
}  

float weightMuSIP(float leptonPt, float leptonEta){
	float weight=1.0;

	if (leptonPt<10){
		if( abs(leptonEta) < 1.44) weight=1.013;
		else weight=0.987;
	} else if (leptonPt>10&&leptonPt<20){
		if (abs(leptonEta) < 0.90) weight=1.000;
		else if (abs(leptonEta) < 1.20) weight=1.000;
		else if (abs(leptonEta) < 1.6) weight=0.999;
		else if (abs(leptonEta) < 2.1) weight=0.997;
		else weight=0.999;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.90) weight=1.000;
		else if (abs(leptonEta) < 1.20) weight=0.998;
		else if (abs(leptonEta) < 1.6) weight=0.997;
		else if (abs(leptonEta) < 2.1) weight=0.996;
		else weight=0.997;
	} else if (leptonPt>30&&leptonPt<50){
		if (abs(leptonEta) < 0.90) weight=0.999;
		else if (abs(leptonEta) < 1.20) weight=0.999;
		else if (abs(leptonEta) < 1.6) weight=0.999;
		else if (abs(leptonEta) < 2.1) weight=0.997;
		else weight=0.997;
	} else {
		if (abs(leptonEta) < 0.90) weight=0.999;
		else if (abs(leptonEta) < 1.20) weight=0.998;
		else if (abs(leptonEta) < 1.6) weight=0.997;
		else if (abs(leptonEta) < 2.1) weight=0.995;
		else weight=0.994;
	}

	return weight ;
}  

float weightEleID(float leptonPt, float leptonEta){
	float weight=1.0;
	if (leptonPt<15){
		if (abs(leptonEta) < 0.78) weight=1.008;
		else if (abs(leptonEta) < 1.44) weight=0.909;
		else if (abs(leptonEta) < 1.57) weight=0.917;
		else if (abs(leptonEta) < 2.00) weight=1.134;
		else weight=1.058;
	} else if (leptonPt>15&&leptonPt<20){
		if (abs(leptonEta) < 0.78) weight=0.989;
		else if (abs(leptonEta) < 1.44) weight=1.000;
		else if (abs(leptonEta) < 1.57) weight=1.001;
		else if (abs(leptonEta) < 2.00) weight=1.012;
		else weight=1.041;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.78) weight=0.985;
		else if (abs(leptonEta) < 1.44) weight=0.988;
		else if (abs(leptonEta) < 1.57) weight=0.980;
		else if (abs(leptonEta) < 2.00) weight=1.005;
		else weight=1.007;
	} else if (leptonPt>30&&leptonPt<40){
		if (abs(leptonEta) < 0.78) weight=0.987;
		else if (abs(leptonEta) < 1.44) weight=0.988;
		else if (abs(leptonEta) < 1.57) weight=1.005;
		else if (abs(leptonEta) < 2.00) weight=1.007;
		else weight=1.004;
	} else if (leptonPt>40&&leptonPt<50){
		if (abs(leptonEta) < 0.78) weight=0.988;
		else if (abs(leptonEta) < 1.44) weight=0.994;
		else if (abs(leptonEta) < 1.57) weight=0.988;
		else if (abs(leptonEta) < 2.00) weight=1.001;
		else weight=1.000;
	} else if (leptonPt>50&&leptonPt<60){
		if (abs(leptonEta) < 0.78) weight=0.987;
		else if (abs(leptonEta) < 1.44) weight=0.995;
		else if (abs(leptonEta) < 1.57) weight=0.971;
		else if (abs(leptonEta) < 2.00) weight=1.016;
		else weight=0.992;
	} else {
		if (abs(leptonEta) < 0.78) weight=0.983;
		else if (abs(leptonEta) < 1.44) weight=0.971;
		else if (abs(leptonEta) < 1.57) weight=0.939;
		else if (abs(leptonEta) < 2.00) weight=0.972;
		else weight=1.000;
	}
	return weight ;
}  

float weightEleSIP(float leptonPt, float leptonEta){
	float weight=1.0;
	if (leptonPt<10){
		if (abs(leptonEta) < 1.44) weight=0.991;
		else if (abs(leptonEta) < 1.57) weight=0.951;
		else weight=0.991;
	} else if (leptonPt>10&&leptonPt<15){
		if (abs(leptonEta) < 0.78) weight=1.004;
		else if (abs(leptonEta) < 1.44) weight=0.997;
		else if (abs(leptonEta) < 1.57) weight=1.015;
		else if (abs(leptonEta) < 2.00) weight=0.993;
		else weight=0.998;
	} else if (leptonPt>15&&leptonPt<20){
		if (abs(leptonEta) < 0.78) weight=0.997;
		else if (abs(leptonEta) < 1.44) weight=0.997;
		else if (abs(leptonEta) < 1.57) weight=0.972;
		else if (abs(leptonEta) < 2.00) weight=0.992;
		else weight=0.995;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.78) weight=0.998;
		else if (abs(leptonEta) < 1.44) weight=0.994;
		else if (abs(leptonEta) < 1.57) weight=0.992;
		else if (abs(leptonEta) < 2.00) weight=0.986;
		else weight=0.981;
	} else if (leptonPt>30&&leptonPt<40){
		if (abs(leptonEta) < 0.78) weight=0.998;
		else if (abs(leptonEta) < 1.44) weight=0.993;
		else if (abs(leptonEta) < 1.57) weight=0.991;
		else if (abs(leptonEta) < 2.00) weight=0.988;
		else weight=0.985;
	} else if (leptonPt>40&&leptonPt<50){
		if (abs(leptonEta) < 0.78) weight=0.997;
		else if (abs(leptonEta) < 1.44) weight=0.993;
		else if (abs(leptonEta) < 1.57) weight=0.985;
		else if (abs(leptonEta) < 2.00) weight=0.992;
		else weight=0.979;
	} else if (leptonPt>50&&leptonPt<60){
		if (abs(leptonEta) < 0.78) weight=0.995;
		else if (abs(leptonEta) < 1.44) weight=0.998;
		else if (abs(leptonEta) < 1.57) weight=0.938;
		else if (abs(leptonEta) < 2.00) weight=0.970;
		else weight=0.964;
	} else {
		if (abs(leptonEta) < 0.78) weight=0.985;
		else if (abs(leptonEta) < 1.44) weight=0.986;
		else if (abs(leptonEta) < 1.57) weight=1.000;
		else if (abs(leptonEta) < 2.00) weight=0.957;
		else weight=0.943;
	}
	return weight ;
}  

float weightMuISOZ(float leptonPt, float leptonEta){
	float weight=1.0;

	if (leptonPt<10){
		if( abs(leptonEta) < 1.44) weight=1.002;
		else weight=0.996;
	} else if (leptonPt>10&&leptonPt<20){
		if (abs(leptonEta) < 0.90) weight=0.974;
		else if (abs(leptonEta) < 1.20) weight=0.991;
		else if (abs(leptonEta) < 1.6) weight=0.999;
		else if (abs(leptonEta) < 2.1) weight=0.998;
		else weight=1.001;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.90) weight=0.996;
		else if (abs(leptonEta) < 1.20) weight=0.999;
		else if (abs(leptonEta) < 1.6) weight=1.001;
		else if (abs(leptonEta) < 2.1) weight=0.999;
		else weight=1.000;
	} else if (leptonPt>30&&leptonPt<50){
		if (abs(leptonEta) < 0.90) weight=1.000;
		else if (abs(leptonEta) < 1.20) weight=1.000;
		else if (abs(leptonEta) < 1.6) weight=1.000;
		else if (abs(leptonEta) < 2.1) weight=1.000;
		else weight=0.999;
	} else {
		if (abs(leptonEta) < 0.90) weight=0.999;
		else if (abs(leptonEta) < 1.20) weight=1.001;
		else if (abs(leptonEta) < 1.6) weight=0.999;
		else if (abs(leptonEta) < 2.1) weight=0.999;
		else weight=1.000;
	}
	return weight ;
}  

float weightEleISOZ(float leptonPt, float leptonEta){
	float weight=1.0;
	if (leptonPt<10){
		if (abs(leptonEta)<1.44) weight=0.975;
		else if (abs(leptonEta)<1.57) weight=0.877;
		else if (abs(leptonEta)<2.50) weight=1.010;
	}
	else if (leptonPt>10&&leptonPt<15){
		if (abs(leptonEta) < 0.78) weight=0.977;
		else if (abs(leptonEta) < 1.44) weight=0.995;
		else if (abs(leptonEta) < 1.57) weight=1.007;
		else if (abs(leptonEta) < 2.00) weight=0.992;
		else weight=0.999;
	} else if (leptonPt>15&&leptonPt<20){
		if (abs(leptonEta) < 0.78) weight=0.989;
		else if (abs(leptonEta) < 1.44) weight=0.997;
		else if (abs(leptonEta) < 1.57) weight=0.985;
		else if (abs(leptonEta) < 2.00) weight=1.004;
		else weight=1.001;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.78) weight=0.997;
		else if (abs(leptonEta) < 1.44) weight=0.999;
		else if (abs(leptonEta) < 1.57) weight=0.999;
		else if (abs(leptonEta) < 2.00) weight=1.001;
		else weight=0.998;
	} else if (leptonPt>30&&leptonPt<40){
		if (abs(leptonEta) < 0.78) weight=1.003;
		else if (abs(leptonEta) < 1.44) weight=1.004;
		else if (abs(leptonEta) < 1.57) weight=1.005;
		else if (abs(leptonEta) < 2.00) weight=1.002;
		else weight=1.000;
	} else if (leptonPt>40&&leptonPt<50){
		if (abs(leptonEta) < 0.78) weight=1.000;
		else if (abs(leptonEta) < 1.44) weight=1.000;
		else if (abs(leptonEta) < 1.57) weight=1.000;
		else if (abs(leptonEta) < 2.00) weight=1.000;
		else weight=1.000;
	} else if (leptonPt>50&&leptonPt<60){
		if (abs(leptonEta) < 0.78) weight=0.997;
		else if (abs(leptonEta) < 1.44) weight=0.998;
		else if (abs(leptonEta) < 1.57) weight=1.004;
		else if (abs(leptonEta) < 2.00) weight=0.995;
		else weight=1.000;
	} else {
		if (abs(leptonEta) < 0.78) weight=0.998;
		else if (abs(leptonEta) < 1.44) weight=1.002;
		else if (abs(leptonEta) < 1.57) weight=1.000;
		else if (abs(leptonEta) < 2.00) weight=0.991;
		else weight=1.000;
	}

	return weight ;
}  

float weightMuHLT8(float leptonPt, float leptonEta){
	float weight=1.0;

	if (leptonPt<20){
		if (abs(leptonEta) < 0.90) weight=0.986;
		else if (abs(leptonEta) < 1.20) weight=0.985;
		else if (abs(leptonEta) < 1.6) weight=0.997;
		else if (abs(leptonEta) < 2.1) weight=0.988;
		else weight=0.978;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.90) weight=0.986;
		else if (abs(leptonEta) < 1.20) weight=0.985;
		else if (abs(leptonEta) < 1.6) weight=0.989;
		else if (abs(leptonEta) < 2.1) weight=0.982;
		else weight=0.972;
	} else if (leptonPt>30&&leptonPt<50){
		if (abs(leptonEta) < 0.90) weight=0.986;
		else if (abs(leptonEta) < 1.20) weight=0.983;
		else if (abs(leptonEta) < 1.6) weight=0.985;
		else if (abs(leptonEta) < 2.1) weight=0.982;
		else weight=0.966;
	} else {
		if (abs(leptonEta) < 0.90) weight=0.986;
		else if (abs(leptonEta) < 1.20) weight=0.982;
		else if (abs(leptonEta) < 1.6) weight=0.982;
		else if (abs(leptonEta) < 2.1) weight=0.976;
		else weight=0.961;
	}

	return weight ;
}  

float weightMuHLT17(float leptonPt, float leptonEta){
	float weight=1.0;

	if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.90) weight=0.983;
		else if (abs(leptonEta) < 1.20) weight=0.980;
		else if (abs(leptonEta) < 1.6) weight=0.979;
		else if (abs(leptonEta) < 2.1) weight=0.962;
		else weight=0.923;
	} else if (leptonPt>30&&leptonPt<50){
		if (abs(leptonEta) < 0.90) weight=0.984;
		else if (abs(leptonEta) < 1.20) weight=0.978;
		else if (abs(leptonEta) < 1.6) weight=0.977;
		else if (abs(leptonEta) < 2.1) weight=0.966;
		else weight=0.925;
	} else {
		if (abs(leptonEta) < 0.90) weight=0.984;
		else if (abs(leptonEta) < 1.20) weight=0.978;
		else if (abs(leptonEta) < 1.6) weight=0.976;
		else if (abs(leptonEta) < 2.1) weight=0.963;
		else weight=0.929;
	}

	return weight ;
}  

float weightEleHLT8(float leptonPt, float leptonEta){
	float weight=1.0;

	if (leptonPt<15){
		if (abs(leptonEta) < 0.78) weight=0.968;
		else if (abs(leptonEta) < 1.44) weight=0.987;
		else if (abs(leptonEta) < 1.57) weight=1.028;
		else if (abs(leptonEta) < 2.00) weight=0.948;
		else weight=0.969;
	} else if (leptonPt>15&&leptonPt<20){
		if (abs(leptonEta) < 0.78) weight=0.990;
		else if (abs(leptonEta) < 1.44) weight=0.992;
		else if (abs(leptonEta) < 1.57) weight=1.031;
		else if (abs(leptonEta) < 2.00) weight=0.971;
		else weight=0.994;
	} else if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.78) weight=0.991;
		else if (abs(leptonEta) < 1.44) weight=0.995;
		else if (abs(leptonEta) < 1.57) weight=1.013;
		else if (abs(leptonEta) < 2.00) weight=0.971;
		else weight=0.994;
	} else if (leptonPt>30&&leptonPt<40){
		if (abs(leptonEta) < 0.78) weight=0.996;
		else if (abs(leptonEta) < 1.44) weight=1.000;
		else if (abs(leptonEta) < 1.57) weight=1.045;
		else if (abs(leptonEta) < 2.00) weight=1.001;
		else weight=0.997;
	} else if (leptonPt>40&&leptonPt<50){
		if (abs(leptonEta) < 0.78) weight=0.996;
		else if (abs(leptonEta) < 1.44) weight=0.998;
		else if (abs(leptonEta) < 1.57) weight=1.003;
		else if (abs(leptonEta) < 2.00) weight=1.000;
		else weight=0.993;
	} else if (leptonPt>50&&leptonPt<60){
		if (abs(leptonEta) < 0.78) weight=0.996;
		else if (abs(leptonEta) < 1.44) weight=0.999;
		else if (abs(leptonEta) < 1.57) weight=0.979;
		else if (abs(leptonEta) < 2.00) weight=0.999;
		else weight=0.999;
	} else {
		if (abs(leptonEta) < 0.78) weight=0.995;
		else if (abs(leptonEta) < 1.44) weight=0.993;
		else if (abs(leptonEta) < 1.57) weight=1.045;
		else if (abs(leptonEta) < 2.00) weight=0.996;
		else weight=0.978;
	}
	return weight ;
}  
float weightEleHLT17(float leptonPt, float leptonEta){
	float weight=1.0;
	if (leptonPt>20&&leptonPt<30){
		if (abs(leptonEta) < 0.78) weight=0.989;
		else if (abs(leptonEta) < 1.44) weight=0.994;
		else if (abs(leptonEta) < 1.57) weight=1.016;
		else if (abs(leptonEta) < 2.00) weight=1.006;
		else weight=0.965;
	} else if (leptonPt>30&&leptonPt<40){
		if (abs(leptonEta) < 0.78) weight=0.998;
		else if (abs(leptonEta) < 1.44) weight=1.002;
		else if (abs(leptonEta) < 1.57) weight=1.020;
		else if (abs(leptonEta) < 2.00) weight=1.004;
		else weight=0.998;
	} else if (leptonPt>40&&leptonPt<50){
		if (abs(leptonEta) < 0.78) weight=0.996;
		else if (abs(leptonEta) < 1.44) weight=0.999;
		else if (abs(leptonEta) < 1.57) weight=0.994;
		else if (abs(leptonEta) < 2.00) weight=1.002;
		else weight=0.993;
	} else if (leptonPt>50&&leptonPt<60){
		if (abs(leptonEta) < 0.78) weight=0.995;
		else if (abs(leptonEta) < 1.44) weight=0.997;
		else if (abs(leptonEta) < 1.57) weight=0.956;
		else if (abs(leptonEta) < 2.00) weight=0.998;
		else weight=0.995;
	} else {
		if (abs(leptonEta) < 0.78) weight=0.994;
		else if (abs(leptonEta) < 1.44) weight=0.995;
		else if (abs(leptonEta) < 1.57) weight=0.999;
		else if (abs(leptonEta) < 2.00) weight=0.996;
		else weight=0.978;
	}
	return weight ;
}
float weightMuISOZ1(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.961;
		if(leptonPt>20&&leptonPt<=30) weight=0.987;
		if(leptonPt>30&&leptonPt<=50) weight=0.998;
		if(leptonPt>50) weight=0.998;
	}
	else
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.969;
		if(leptonPt>20&&leptonPt<=30) weight=0.994;
		if(leptonPt>30&&leptonPt<=50) weight=0.998;
		if(leptonPt>50) weight=1.0;
	}
	return weight ;
}  
float weightMuISOZ2(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.921;
		if(leptonPt>20&&leptonPt<=30) weight=0.960;
		if(leptonPt>30&&leptonPt<=50) weight=0.982;
		if(leptonPt>50) weight=0.991;
	}
	else
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.929;
		if(leptonPt>20&&leptonPt<=30) weight=0.965;
		if(leptonPt>30&&leptonPt<=50) weight=0.987;
		if(leptonPt>50) weight=0.991;
	}
	return weight ;
}  
float weightEleISOZ1(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.970;
		if(leptonPt>20&&leptonPt<=30) weight=0.990;
		if(leptonPt>30&&leptonPt<=40) weight=1.000;
		if(leptonPt>40&&leptonPt<=50) weight=0.998;
		if(leptonPt>50&&leptonPt<=60) weight=0.989;
		if(leptonPt>60) weight=0.997;
	}
	else if(abs(leptonEta) > 1.57)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.951;
		if(leptonPt>20&&leptonPt<=30) weight=0.976;
		if(leptonPt>30&&leptonPt<=40) weight=0.980;
		if(leptonPt>40&&leptonPt<=50) weight=0.984;
		if(leptonPt>50&&leptonPt<=60) weight=0.977;
		if(leptonPt>60) weight=0.963;
	}
	return weight ;
}  
float weightEleISOZ2(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.957;
		if(leptonPt>20&&leptonPt<=30) weight=0.979;
		if(leptonPt>30&&leptonPt<=40) weight=0.994;
		if(leptonPt>40&&leptonPt<=50) weight=0.995;
		if(leptonPt>50&&leptonPt<=60) weight=0.977;
		if(leptonPt>60) weight=0.987;
	}
	else if(abs(leptonEta) > 1.57)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.924;
		if(leptonPt>20&&leptonPt<=30) weight=0.964;
		if(leptonPt>30&&leptonPt<=40) weight=0.976;
		if(leptonPt>40&&leptonPt<=50) weight=0.980;
		if(leptonPt>50&&leptonPt<=60) weight=0.977;
		if(leptonPt>60) weight=0.956;
	}
	return weight ;
}  
