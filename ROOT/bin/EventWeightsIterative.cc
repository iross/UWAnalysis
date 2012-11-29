#include "PhysicsTools/FWLite/interface/CommandLineParser.h"
//#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"

#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"
#include <math.h>

//Distribution from Fall 2011

std::vector<float> data;
std::vector<float> mc;
//edm::Lumi3DReWeighting *LumiWeights;


void readdir(TDirectory *dir,optutl::CommandLineParser parser,float ev,int doPU,bool doRho,TH1F* puWeight,TH1F* rhoWeight);

// https://mangano.web.cern.ch/mangano/dropBox/puRW_v3.txt
// Made for ICHEP dataset

float weightTruePileupV07toIchep52X(float input){
  float w[60] = {
    2.59113e-07,
    1.77107e-05,
    0.0263017,
    1.66396,
    0.16421,
    0.754166,
    2.84622,
    5.57103,
    8.66558,
    11.5716,
    11.8712,
    12.8102,
    10.3421,
    8.91019,
    7.614,
    6.10397,
    4.52745,
    3.26031,
    2.39558,
    1.83297,
    1.47821,
    1.26728,
    1.14716,
    1.06707,
    0.98066,
    0.860877,
    0.708281,
    0.539789,
    0.37652,
    0.237298,
    0.1338,
    0.0671236,
    0.0299236,
    0.0118723,
    0.00420968,
    0.00134235,
    0.000389563,
    0.000104892,
    2.69214e-05,
    6.79674e-06,
    1.73307e-06,
    4.52553e-07,
    1.21124e-07,
    3.29924e-08,
    9.10616e-09,
    2.53998e-09,
    7.16146e-10,
    2.03786e-10,
    5.84308e-11,
    1.68192e-11,
    4.8434e-12,
    1.38959e-12,
    3.96112e-13,
    1.11358e-13,
    3.17245e-14,
    5.34916e-15,
    0,
    0,
    0,
    0};

  //return w[(int)floor(input+0.5)];
  return w[(int)floor(input)];

    /*
     TH1F h("boh","boh",60,0.,60.);
     for(int k=0;k<60;k++){
     h.SetBinContent(k+1,w[k]);
     }
     return h.GetBinContent(h.FindBin(input));
    */
}


float weightTruePileupV07toHcp53X(float input){
  float w[60] = {
    0.0447136,
    0.11785,
    0.23825,
    1.08447,
    0.102575,
    0.454605,
    1.79761,
    4.00271,
    6.83281,
    9.83701,
    10.7966,
    12.2356,
    10.0247,
    8.49395,
    7.1125,
    5.69527,
    4.31256,
    3.19305,
    2.42035,
    1.91666,
    1.58485,
    1.36297,
    1.21166,
    1.09466,
    0.978941,
    0.84653,
    0.699235,
    0.548996,
    0.408673,
    0.288194,
    0.193367,
    0.124653,
    0.0781124,
    0.0479268,
    0.0287763,
    0.0167744,
    0.00941834,
    0.00507877,
    0.00264364,
    0.00134612,
    0.000682678,
    0.000351412,
    0.0001864,
    0.00010259,
    5.87818e-05,
    3.5033e-05,
    2.17116e-05,
    1.39777e-05,
    9.36123e-06,
    6.53328e-06,
    4.76598e-06,
    3.64139e-06,
    2.92018e-06,
    2.4602e-06,
    2.17291e-06,
    2.01107e-06,
    1.94392e-06,
    1.9598e-06,
    2.0583e-06,
    2.24895e-06};

  return w[(int)floor(input)];
}


float weightTruePileupV10toIchep53X(float input){
  float w[60] = {
    2.35693e-06,
    7.51928e-05,
    0.0263529,
    0.609947,
    0.737917,
    1.29365,
    0.994503,
    0.85454,
    1.01559,
    1.33243,
    1.72454,
    2.01264,
    2.00573,
    1.80333,
    1.56328,
    1.37452,
    1.24753,
    1.16481,
    1.11738,
    1.09701,
    1.08843,
    1.08796,
    1.09768,
    1.10763,
    1.09328,
    1.0339,
    0.92408,
    0.771537,
    0.59283,
    0.41266,
    0.256892,
    0.14188,
    0.0692543,
    0.029902,
    0.0114564,
    0.00391383,
    0.00120625,
    0.000341485,
    9.09127e-05,
    2.34008e-05,
    5.95438e-06,
    1.5122e-06,
    3.82094e-07,
    9.51794e-08,
    2.32205e-08,
    5.51698e-09,
    1.27267e-09,
    2.84346e-10,
    6.12799e-11,
    1.26731e-11,
    2.50309e-12,
    4.69797e-13,
    8.35153e-14,
    1.39452e-14,
    2.24718e-15,
    2.03841e-16,
    0,
    0,
    0,
    0};

  return w[(int)floor(input)];
}



float weightTruePileupV10toHcp53X(float input){
  float w[60] = {
    0.409409,
    0.527276,
    0.39328,
    0.507892,
    0.48029,
    0.787701,
    0.632356,
    0.618033,
    0.806089,
    1.14018,
    1.5788,
    1.93507,
    1.957,
    1.73004,
    1.46737,
    1.28278,
    1.18189,
    1.13388,
    1.12578,
    1.14415,
    1.16048,
    1.1618,
    1.15318,
    1.13405,
    1.09239,
    1.01915,
    0.914837,
    0.786744,
    0.644879,
    0.502039,
    0.371688,
    0.263586,
    0.18067,
    0.120472,
    0.0780184,
    0.0486113,
    0.0289039,
    0.0163367,
    0.00879674,
    0.00456046,
    0.0023098,
    0.00115977,
    0.000583207,
    0.000294815,
    0.000149865,
    7.62892e-05,
    3.87537e-05,
    1.96105e-05,
    9.87744e-06,
    4.95418e-06,
    2.47913e-06,
    1.23919e-06,
    6.19751e-07,
    3.10125e-07,
    1.54934e-07,
    7.71425e-08,
    3.8182e-08,
    1.87455e-08,
    9.10765e-09,
    9.19802e-09};
  return w[(int)floor(input)];
}









float weightTrue2011(float input){
  if(input>50)
    return 1;


  float w[50];


w[0]= 0.212929;
w[1]= 0.0208114;
w[2]= 0.0584048;
w[3]= 0.538898;
w[4]= 1.357;
w[5]= 1.49913;
w[6]= 1.42247;
w[7]= 1.35904;
w[8]= 1.29946;
w[9]= 1.27925;
w[10]= 1.37845;
w[11]= 1.71246;
w[12]= 1.5291;
w[13]= 1.35234;
w[14]= 1.22215;
w[15]= 1.0155;
w[16]= 1.01137;
w[17]= 0.395465;
w[18]= 0.230984;
w[19]= 0.109883;
w[20]= 0.0433739;
w[21]= 0.0111497;
w[22]= 0.00408801;
w[23]= 0.00115678;
w[24]= 0.000365505;
w[25]= 0.000112391;
w[26]= 3.83894e-05;
w[27]= 1.60651e-05;
w[28]= 4.81412e-06;
w[29]= 1.39717e-06;
w[30]= 1.92368e-06;
w[31]= 4.10748e-06;
w[32]= 2.33157e-05;
w[33]= 4.0181e-05;
w[34]= 4.87786e-05;
w[35]= 0.00194128;
w[36]= 8.97414e-05;
w[37]= 1;
w[38]= 1;
w[39]= 0.000162709;
w[40]= 1;
w[41]= 1;
w[42]= 1;
w[43]= 1;
w[44]= 1;
w[45]= 1;
w[46]= 1;
w[47]= 1;
w[48]= 1;
w[49]= 1;


 TH1F h("boh","boh",50,0.,50.);

 for(int k=0;k<50;k++){
   h.SetBinContent(k+1,w[k]);
 }

 return h.GetBinContent(h.FindBin(input));

}




float weightTrue2011to2012(float input){
  if(input>50)
    return 1;

  float w[50];

w[0]= 0.000443112;
w[1]= 0.000248044;
w[2]= 0.000273111;
w[3]= 0.00109511;
w[4]= 0.00195699;
w[5]= 0.00480746;
w[6]= 0.027013;
w[7]= 0.074795;
w[8]= 0.166231;
w[9]= 0.309545;
w[10]= 0.577657;
w[11]= 1.12488;
w[12]= 1.36899;
w[13]= 1.56925;
w[14]= 1.89846;
w[15]= 2.20828;
w[16]= 3.14112;
w[17]= 1.87712;
w[18]= 1.97062;
w[19]= 2.07067;
w[20]= 2.17791;
w[21]= 1.7176;
w[22]= 2.10953;
w[23]= 2.0805;
w[24]= 2.29498;
w[25]= 2.42189;
w[26]= 2.80303;
w[27]= 3.94091;
w[28]= 3.67917;
w[29]= 2.26081;
w[30]= 2.99726;
w[31]= 3.76553;
w[32]= 11.285;
w[33]= 10.2781;
w[34]= 6.73407;
w[35]= 148.182;
w[36]= 3.88144;
w[37]= 1;
w[38]= 1;
w[39]= 1.48128;
w[40]= 1;
w[41]= 1;
w[42]= 1;
w[43]= 1;
w[44]= 1;
w[45]= 1;
w[46]= 1;
w[47]= 1;
w[48]= 1;
w[49]= 1;


 TH1F h("boh","boh",50,0.,50.);

 for(int k=0;k<50;k++){
   h.SetBinContent(k+1,w[k]);
 }

 return h.GetBinContent(h.FindBin(input));

}

int main (int argc, char* argv[])
{
    optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
    parser.addOption("histoName",optutl::CommandLineParser::kString,"Counter Histogram Name","EventSummary");
    parser.addOption("weight",optutl::CommandLineParser::kDouble,"Weight to apply",1.0);
    parser.addOption("type",optutl::CommandLineParser::kInteger,"Type",0);
    parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__WEIGHT__");
    parser.addOption("extra",optutl::CommandLineParser::kString,"Extra options","");


    parser.parseArguments (argc, argv);


    //read PU info
    TH1F *puWeight=0;
    int doPU=0;
    TFile *fPU = new TFile("../puInfo.root");

    if(fPU!=0 && fPU->IsOpen()) {
        puWeight = (TH1F*)fPU->Get("weight");
        doPU=1;
        printf("ENABLING PU WEIGHTING USING VERTICES\n");

    }

    TFile *fPU2 = new TFile("../puInfo3D.root");
    TFile *fPU22 = new TFile("../puInfoMC3D.root");
    TFile *fPU3 = new TFile("../Weight3D.root");
    TFile *fPU4 = new TFile("Weight3D.root");

    if ( !fPU2->IsZombie() && !fPU22->IsZombie() && !fPU3->IsZombie() && !fPU4->IsZombie() )
    {

        if(fPU2!=0 && fPU2->IsOpen()&& fPU22!=0 && fPU22->IsOpen() && (!(fPU3!=0 && fPU3->IsOpen())) &&(!(fPU4!=0 && fPU4->IsOpen()))){
            doPU=2;
            printf("ENABLING PU WEIGHTING USING 3D- I HAVE TO CALCULATE WEIGHTS SORRY\n");
//            LumiWeights = new edm::Lumi3DReWeighting("../puInfoMC3D.root","../puInfo3D.root","pileup","pileup");
//            LumiWeights->weight3D_init(1.0);
        }
        else  if(fPU3!=0 && fPU3->IsOpen()) {
            doPU=2;
            printf("ENABLING PU WEIGHTING USING 3D with ready distribution\n");
            fPU3->Close();
//            LumiWeights = new edm::Lumi3DReWeighting(mc,data);
//            LumiWeights->weight3D_init("../Weight3D.root");
        }
        else   if(fPU4!=0 && fPU4->IsOpen()) {

            //searxch in this folder
            doPU=2;
            printf("ENABLING PU WEIGHTING USING 3D with  distribution you just made\n");
            fPU4->Close();
//            LumiWeights = new edm::Lumi3DReWeighting(mc,data);
//            LumiWeights->weight3D_init("Weight3D.root");

        }
    }



    //read PU info
    TH1F *rhoWeight=0;
    bool doRho=false;
    TFile *fRho = new TFile("../rhoInfo.root");

    if(fRho!=0 && fRho->IsOpen()) {
        rhoWeight = (TH1F*)fRho->Get("weight");
        doRho=true;
        printf("ENABLING Rho WEIGHTING\n");

    }


    TFile *f = new TFile(parser.stringValue("outputFile").c_str(),"UPDATE");

    TH1F* evC  = (TH1F*)f->Get(parser.stringValue("histoName").c_str());
    float ev = evC->GetBinContent(1);

    printf("Found  %f Events Counted\n",ev);

    //temp, hack, etc
    doPU=3;

    readdir(f,parser,ev,doPU,doRho,puWeight,rhoWeight);
    f->Close();
    if(fPU!=0 && fPU->IsOpen())
        fPU->Close();

    if(fPU2!=0 && fPU2->IsOpen())
        fPU2->Close();


}


void readdir(TDirectory *dir,optutl::CommandLineParser parser,float ev,int doPU,bool doRho,TH1F *puWeight,TH1F *rhoWeight)
{
    TDirectory *dirsav = gDirectory;
    TIter next(dir->GetListOfKeys());
    TKey *key;
    while ((key = (TKey*)next())) {
        printf("Found key=%s \n",key->GetName());
        TObject *obj = key->ReadObj();

        if (obj->IsA()->InheritsFrom(TDirectory::Class())) {
            dir->cd(key->GetName());
            TDirectory *subdir = gDirectory;
            readdir(subdir,parser,ev,doPU,doRho,puWeight,rhoWeight);
            dirsav->cd();
        }
        else if(obj->IsA()->InheritsFrom(TTree::Class())) {
            TTree *t = (TTree*)obj;
            float weight = parser.doubleValue("weight")/(ev);
            int   type = parser.integerValue("type");


            TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
            TBranch *noPUBranch = t->Branch((parser.stringValue("branch")+"noPU").c_str(),&weight,(parser.stringValue("branch")+"noPU/F").c_str());
            TBranch *typeBranch = t->Branch("TYPE",&type,"TYPE/I");
            int vertices;
            float bxm=0;
            float bx=0;
            float bxp=0;
            float truth=0;

            if(doPU==1)
                t->SetBranchAddress("vertices",&vertices);
            else if(doPU==2) {
                t->SetBranchAddress("puBXminus",&bxm);
                t->SetBranchAddress("puBX0",&bx);
                t->SetBranchAddress("puBXplus",&bxp);
            }

            float rho=0.0;
            if(doRho)
                t->SetBranchAddress("Rho",&rho);
            if(doPU==3)
                t->SetBranchAddress("puTruth",&truth);

            printf("Found tree -> weighting\n");
            for(Int_t i=0;i<t->GetEntries();++i)
            {
                t->GetEntry(i);
                weight = parser.doubleValue("weight")/(ev);
                noPUBranch->Fill();
                if(doPU==1) {
                    int bin=puWeight->FindBin(vertices);
                    if(bin>puWeight->GetNbinsX())
                    {
                        printf("Overflow using max bin\n");
                        bin = puWeight->GetNbinsX();
                    }
                    //                    weight*=puWeight->GetBinContent(bin);
                    //temp hack, etc
                    if (parser.stringValue("extra")=="2011to2012"){
                        weight*=weightTrue2011to2012(bin);
                    } else {
                        weight*=weightTrue2011(bin);
                    }
                    if(i==1)
                        printf("PU WEIGHT = %f\n",puWeight->GetBinContent(puWeight->FindBin(vertices)));

                }
                else if(doPU==2) {
//                    float w = LumiWeights->weight3D( bxm,bx,bxp);
//                    if(i==1)
//                        printf("PU WEIGHT = %f\n",w);
//                    weight*=w;
                }
                else if(doPU==3) {
                    weight*=weightTrue2011(truth);
                }
                if(doRho) {
                    weight*=rhoWeight->GetBinContent(rhoWeight->FindBin(rho));
                    if(i==1)
                        printf("RHO WEIGHT = %f\n",rhoWeight->GetBinContent(rhoWeight->FindBin(rho)));
                }

                newBranch->Fill();
                typeBranch->Fill();
            }
            t->Write("",TObject::kOverwrite);
        }
        //     else if(obj->IsA()->InheritsFrom(TH1F::Class())) {
        //       TH1F *h = (TH1F*)obj;
        //       h->Sumw2();
        //       printf("scaling histogram with %f entries\n",h->Integral());
        //       float weight = parser.doubleValue("weight")/(ev);
        //       h->Sumw2();
        //       for( int i=1;i<=h->GetNbinsX();++i)
        // 	h->SetBinContent(i,h->GetBinContent(i)*weight);

        //       TDirectory *tmp = gDirectory;
        //       h->SetDirectory(gDirectory);
        //       h->Write("resultsWeighted");
        //     }


    }

}
