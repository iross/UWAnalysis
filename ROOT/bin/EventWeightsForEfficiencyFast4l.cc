#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TF1.h"
#include <math.h>
#include "TMath.h"
#include <limits>
#include <string>
#include <sstream>

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

TH2F* eleCorrs;
TH2F* muCorrs;

void loadHistograms() {
    TFile *fe = new TFile("/afs/hep.wisc.edu/cms/iross/analysis/zz535/src/UWAnalysis/analysisScripts/Electron_scale_factors_IDISOSIP_combined.root");
    eleCorrs = (TH2F*)fe->Get("h_electron_scale_factor_RECO_ID_ISO_SIP");

  TFile *fm = new TFile("/afs/hep.wisc.edu/cms/iross/analysis/zz535/src/UWAnalysis/analysisScripts/muonid_hcp-05.10.2012-with-tk-v2.root");
  muCorrs = (TH2F*)fm->Get("TH2D_ALL_2012");

}

float rerangePt(float Pt){
    if (Pt>100.0) return 99.9;
    else return Pt;
}

float weightCalculator(float pt1,float eta1,float pt2,float eta2,float pt3,float eta3,float pt4,float eta4,char TreeToUse[]) {

    float weight=1.0 ;

    pt1 = rerangePt(pt1);
    pt2 = rerangePt(pt2);
    pt3 = rerangePt(pt3);
    pt4 = rerangePt(pt4);

    std::stringstream ss;
    std::string s;
    ss << TreeToUse;
    ss >> s;

    if(s.find("muMuMuMuEventTree") != std::string::npos)
    {
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt1,eta1));
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt2,eta2));
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt3,eta3));
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt4,eta4));
    }
    else if(s.find("muMuEleEleEventTree") != std::string::npos)
    {
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt1,eta1));
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt2,eta2));
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt3,eta3));
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt4,eta4));
    }
    else if(s.find("eleEleMuMuEventTree") != std::string::npos)
    {
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt1,eta1));
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt2,eta2));
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt3,eta3));
        weight *= muCorrs->GetBinContent(muCorrs->FindBin(pt4,eta4));
    }
    else if(s.find("eleEleEleEleEventTree") != std::string::npos)
    {
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt1,eta1));
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt2,eta2));
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt3,eta3));
        weight *= eleCorrs->GetBinContent(eleCorrs->FindBin(pt4,eta4));
    }

    return weight;
}


int main (int argc, char* argv[])
{
    optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
    parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__HLT__");
    parser.parseArguments (argc, argv);

    char TreeToUse[80]="first" ;

    loadHistograms();

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

            t->SetBranchAddress("z1l1Pt",&pt1);
            t->SetBranchAddress("z1l1Eta",&eta1);
            t->SetBranchAddress("z1l2Pt",&pt2);
            t->SetBranchAddress("z1l2Eta",&eta2);
            t->SetBranchAddress("z2l1Pt",&pt3);
            t->SetBranchAddress("z2l1Eta",&eta3);
            t->SetBranchAddress("z2l2Pt",&pt4);
            t->SetBranchAddress("z2l2Eta",&eta4);


            printf("Found tree -> weighting\n");
            for(Int_t i=0;i<t->GetEntries();++i)
            {
                t->GetEntry(i);
                weight=weightCalculator(pt1,eta1,pt2,eta2,pt3,eta3,pt4,eta4,TreeToUse);

                newBranch->Fill();
            }
            printf("Done weighting. Writing\n");

            t->Write("",TObject::kOverwrite);
            strcpy(TreeToUse,stringA) ;
        }
    }
}


float weightMuID(float leptonPt, float leptonEta){
    float weight=1.0;

    if(leptonEta <= 1.44)
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

    if(leptonEta <= 1.44)
    {
        if(leptonPt>10&&leptonPt<=20) weight=1.001;
        if(leptonPt>20&&leptonPt<=30) weight=0.983;
        if(leptonPt>30&&leptonPt<=40) weight=0.985;
        if(leptonPt>40&&leptonPt<=50) weight=0.987;
        if(leptonPt>50&&leptonPt<=60) weight=0.988;
        if(leptonPt>60) weight=0.991;
    }
    else if(leptonEta > 1.57)
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

    if(leptonEta <= 1.44)
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

    if(leptonEta <= 1.44)
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

    if(leptonEta <= 1.44)
    {
        if(leptonPt>10&&leptonPt<=20) weight=0.970;
        if(leptonPt>20&&leptonPt<=30) weight=0.990;
        if(leptonPt>30&&leptonPt<=40) weight=1.000;
        if(leptonPt>40&&leptonPt<=50) weight=0.998;
        if(leptonPt>50&&leptonPt<=60) weight=0.989;
        if(leptonPt>60) weight=0.997;
    }
    else if(leptonEta > 1.57)
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

    if(leptonEta <= 1.44)
    {
        if(leptonPt>10&&leptonPt<=20) weight=0.957;
        if(leptonPt>20&&leptonPt<=30) weight=0.979;
        if(leptonPt>30&&leptonPt<=40) weight=0.994;
        if(leptonPt>40&&leptonPt<=50) weight=0.995;
        if(leptonPt>50&&leptonPt<=60) weight=0.977;
        if(leptonPt>60) weight=0.987;
    }
    else if(leptonEta > 1.57)
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

    if(leptonEta <= 1.44)
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

    if(leptonEta <= 1.44)
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

    if(leptonEta <= 1.44)
    {
        if(leptonPt>10&&leptonPt<=20) weight=0.991;
        if(leptonPt>20&&leptonPt<=30) weight=0.997;
        if(leptonPt>30&&leptonPt<=40) weight=0.999;
        if(leptonPt>40&&leptonPt<=50) weight=0.998;
        if(leptonPt>50&&leptonPt<=60) weight=0.999;
        if(leptonPt>60) weight=0.998;
    }
    else if(leptonEta > 1.57)
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

    if(leptonEta <= 1.44)
    {
        if(leptonPt>10&&leptonPt<=20) weight=0.996;
        if(leptonPt>20&&leptonPt<=30) weight=0.996;
        if(leptonPt>30&&leptonPt<=40) weight=1.000;
        if(leptonPt>40&&leptonPt<=50) weight=0.999;
        if(leptonPt>50&&leptonPt<=60) weight=0.998;
        if(leptonPt>60) weight=0.997;
    }
    else if(leptonEta > 1.57)
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
