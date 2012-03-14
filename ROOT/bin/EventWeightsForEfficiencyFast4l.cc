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
float weightMuISOZ1(float leptonPt, float leptonEta) ;
float weightMuISOZ2(float leptonPt, float leptonEta) ;
float weightEleISOZ1(float leptonPt, float leptonEta) ;
float weightEleISOZ2(float leptonPt, float leptonEta) ;
float weightMuHLT8(float leptonPt, float leptonEta) ;
float weightMuHLT17(float leptonPt, float leptonEta) ;
float weightEleHLT8(float leptonPt, float leptonEta) ;
float weightEleHLT17(float leptonPt, float leptonEta) ;


float weightCalculator(float pt1,float eta1,float pt2,float eta2,float pt3,float eta3,float pt4,float eta4,char TreeToUse[],int EVENT) {

	float weight=1.0 ;

	if(std::string(TreeToUse).find("muMuTauTauEventTree")!= std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2) ;
		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("muMuEleMuEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightEleID(pt3,eta3)*weightMuID(pt4,eta4) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2)*weightEleISOZ1(pt3,eta3)*weightMuISOZ1(pt4,eta4) ;
		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("muMuEleTauEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightEleID(pt3,eta3) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2)*weightEleISOZ2(pt3,eta3);
		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("muMuMuTauEventTree")!=std::string::npos)
	{
		weight = weight*weightMuID(pt1,eta1)*weightMuID(pt2,eta2)*weightMuID(pt3,eta3) ;
		weight = weight*weightMuISOZ1(pt1,eta1)*weightMuISOZ1(pt2,eta2)*weightMuISOZ2(pt3,eta3);
		weight = weight*weightMuHLT17(pt1,eta1)*weightMuHLT8(pt2,eta2) ;
	}
	if(std::string(TreeToUse).find("eleEleTauTauEventTree")!= std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2) ;
		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("eleEleEleMuEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightEleID(pt3,eta3)*weightMuID(pt4,eta4) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2)*weightEleISOZ1(pt3,eta3)*weightMuISOZ1(pt4,eta4) ;
		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("eleEleEleTauEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightEleID(pt3,eta3) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2)*weightEleISOZ2(pt3,eta3);
		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
	}
	else if(std::string(TreeToUse).find("eleEleMuTauEventTree")!=std::string::npos)
	{
		weight = weight*weightEleID(pt1,eta1)*weightEleID(pt2,eta2)*weightMuID(pt3,eta3) ;
		weight = weight*weightEleISOZ1(pt1,eta1)*weightEleISOZ1(pt2,eta2)*weightMuISOZ2(pt3,eta3);
		weight = weight*weightEleHLT17(pt1,eta1)*weightEleHLT8(pt2,eta2) ;
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

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.991;
		if(leptonPt>20&&leptonPt<=30) weight=0.995;
		if(leptonPt>30&&leptonPt<=50) weight=0.994;
		if(leptonPt>50) weight=0.994;
	}
	else
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.987;
		if(leptonPt>20&&leptonPt<=30) weight=0.985;
		if(leptonPt>30&&leptonPt<=50) weight=0.984;
		if(leptonPt>50) weight=0.984;
	}
	return weight ;
}  

float weightEleID(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=1.001;
		if(leptonPt>20&&leptonPt<=30) weight=0.983;
		if(leptonPt>30&&leptonPt<=40) weight=0.985;
		if(leptonPt>40&&leptonPt<=50) weight=0.987;
		if(leptonPt>50&&leptonPt<=60) weight=0.988;
		if(leptonPt>60) weight=0.991;
	}
	else if(abs(leptonEta) > 1.57)
	{
		if(leptonPt>10&&leptonPt<=20) weight=1.033;
		if(leptonPt>20&&leptonPt<=30) weight=1.001;
		if(leptonPt>30&&leptonPt<=40) weight=0.998;
		if(leptonPt>40&&leptonPt<=50) weight=0.992;
		if(leptonPt>50&&leptonPt<=60) weight=0.991;
		if(leptonPt>60) weight=0.970;
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
float weightMuHLT8(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.989;
		if(leptonPt>20&&leptonPt<=30) weight=0.986;
		if(leptonPt>30&&leptonPt<=50) weight=0.985;
		if(leptonPt>50) weight=0.985;
	}
	else
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.988;
		if(leptonPt>20&&leptonPt<=30) weight=0.981;
		if(leptonPt>30&&leptonPt<=50) weight=0.980;
		if(leptonPt>50) weight=0.976;
	}
	return weight ;
}  
float weightMuHLT17(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.982;
		if(leptonPt>20&&leptonPt<=30) weight=0.982;
		if(leptonPt>30&&leptonPt<=50) weight=0.982;
		if(leptonPt>50) weight=0.982;
	}
	else
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.955;
		if(leptonPt>20&&leptonPt<=30) weight=0.955;
		if(leptonPt>30&&leptonPt<=50) weight=0.960;
		if(leptonPt>50) weight=0.960;
	}
	return weight ;
}  
float weightEleHLT8(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.991;
		if(leptonPt>20&&leptonPt<=30) weight=0.997;
		if(leptonPt>30&&leptonPt<=40) weight=0.999;
		if(leptonPt>40&&leptonPt<=50) weight=0.998;
		if(leptonPt>50&&leptonPt<=60) weight=0.999;
		if(leptonPt>60) weight=0.998;
	}
	else if(abs(leptonEta) > 1.57)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.980;
		if(leptonPt>20&&leptonPt<=30) weight=0.999;
		if(leptonPt>30&&leptonPt<=40) weight=1.00;
		if(leptonPt>40&&leptonPt<=50) weight=0.999;
		if(leptonPt>50&&leptonPt<=60) weight=1.003;
		if(leptonPt>60) weight=0.989;
	}
	return weight ;
}  
float weightEleHLT17(float leptonPt, float leptonEta){
	float weight=1.0;

	if(abs(leptonEta) <= 1.44)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.996;
		if(leptonPt>20&&leptonPt<=30) weight=0.996;
		if(leptonPt>30&&leptonPt<=40) weight=1.000;
		if(leptonPt>40&&leptonPt<=50) weight=0.999;
		if(leptonPt>50&&leptonPt<=60) weight=0.998;
		if(leptonPt>60) weight=0.997;
	}
	else if(abs(leptonEta) > 1.57)
	{
		if(leptonPt>10&&leptonPt<=20) weight=0.987;
		if(leptonPt>20&&leptonPt<=30) weight=0.987;
		if(leptonPt>30&&leptonPt<=40) weight=1.001;
		if(leptonPt>40&&leptonPt<=50) weight=1.000;
		if(leptonPt>50&&leptonPt<=60) weight=1.002;
		if(leptonPt>60) weight=0.989;
	}
	return weight ;
}  
