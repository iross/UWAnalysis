#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"

//Distribution from Fall 2011

std::vector<float> data;
std::vector<float> mc;
//edm::Lumi3DReWeighting *LumiWeights;


void readdir(TDirectory *dir,optutl::CommandLineParser parser,float ev,int doPU,bool doRho,TH1F* puWeight,TH1F* rhoWeight); 

// https://mangano.web.cern.ch/mangano/dropBox/puRW_v3.txt
// Made for ICHEP dataset

float weightTrue2012(float input){
    float w[240];

    w[0]= 1;
    w[1]= 1;
    w[2]= 0.222451;
    w[3]= 0.0658851;
    w[4]= 1;
    w[5]= 1;
    w[6]= 0.150902;
    w[7]= 0.202205;
    w[8]= 1;
    w[9]= 1;
    w[10]= 1.50116;
    w[11]= 2.79375;
    w[12]= 0.198341;
    w[13]= 0.246893;
    w[14]= 0.28116;
    w[15]= 0.449377;
    w[16]= 0.553276;
    w[17]= 1.48919;
    w[18]= 2.15249;
    w[19]= 3.62415;
    w[20]= 4.33041;
    w[21]= 3.57192;
    w[22]= 4.99603;
    w[23]= 7.79303;
    w[24]= 8.04276;
    w[25]= 8.05557;
    w[26]= 12.9364;
    w[27]= 9.9036;
    w[28]= 14.6975;
    w[29]= 13.3387;
    w[30]= 10.9734;
    w[31]= 12.6077;
    w[32]= 11.5617;
    w[33]= 10.8107;
    w[34]= 14.5043;
    w[35]= 17.8497;
    w[36]= 11.8817;
    w[37]= 9.6805;
    w[38]= 12.2255;
    w[39]= 10.1117;
    w[40]= 10.2482;
    w[41]= 11.5398;
    w[42]= 9.35737;
    w[43]= 9.90259;
    w[44]= 9.19216;
    w[45]= 7.57377;
    w[46]= 7.94847;
    w[47]= 7.15578;
    w[48]= 5.63016;
    w[49]= 5.35972;
    w[50]= 5.05791;
    w[51]= 3.35313;
    w[52]= 3.60582;
    w[53]= 3.35256;
    w[54]= 2.49496;
    w[55]= 2.28219;
    w[56]= 2.21227;
    w[57]= 1.76362;
    w[58]= 1.68533;
    w[59]= 1.62149;
    w[60]= 1.34263;
    w[61]= 1.30646;
    w[62]= 1.21918;
    w[63]= 1.10347;
    w[64]= 1.08544;
    w[65]= 1.0251;
    w[66]= 0.907123;
    w[67]= 0.905997;
    w[68]= 0.869217;
    w[69]= 0.816708;
    w[70]= 0.76043;
    w[71]= 0.714367;
    w[72]= 0.679723;
    w[73]= 0.665294;
    w[74]= 0.609956;
    w[75]= 0.586386;
    w[76]= 0.548999;
    w[77]= 0.521088;
    w[78]= 0.4929;
    w[79]= 0.453545;
    w[80]= 0.44546;
    w[81]= 0.406266;
    w[82]= 0.378486;
    w[83]= 0.347898;
    w[84]= 0.337097;
    w[85]= 0.313674;
    w[86]= 0.291392;
    w[87]= 0.283346;
    w[88]= 0.25272;
    w[89]= 0.244178;
    w[90]= 0.228673;
    w[91]= 0.211327;
    w[92]= 0.19084;
    w[93]= 0.179408;
    w[94]= 0.169234;
    w[95]= 0.157131;
    w[96]= 0.143818;
    w[97]= 0.140968;
    w[98]= 0.124021;
    w[99]= 0.118273;
    w[100]= 0.109751;
    w[101]= 0.0977754;
    w[102]= 0.0967206;
    w[103]= 0.0870401;
    w[104]= 0.0826372;
    w[105]= 0.0746777;
    w[106]= 0.0698592;
    w[107]= 0.0656062;
    w[108]= 0.0601853;
    w[109]= 0.057892;
    w[110]= 0.0517871;
    w[111]= 0.0512109;
    w[112]= 0.0465423;
    w[113]= 0.0403982;
    w[114]= 0.0443631;
    w[115]= 0.0399185;
    w[116]= 0.0338933;
    w[117]= 0.0354274;
    w[118]= 0.0310775;
    w[119]= 0.0261122;
    w[120]= 0.0280878;
    w[121]= 0.0264014;
    w[122]= 0.021299;
    w[123]= 0.0245197;
    w[124]= 0.0221076;
    w[125]= 0.0189236;
    w[126]= 0.0202148;
    w[127]= 0.0177248;
    w[128]= 0.0163634;
    w[129]= 0.0188307;
    w[130]= 0.0144512;
    w[131]= 0.0134599;
    w[132]= 0.0143315;
    w[133]= 0.0130668;
    w[134]= 0.0108666;
    w[135]= 0.0162516;
    w[136]= 0.0126035;
    w[137]= 0.0102154;
    w[138]= 0.0154442;
    w[139]= 0.00959973;
    w[140]= 0.0106827;
    w[141]= 0.0146624;
    w[142]= 0.0155156;
    w[143]= 0.00761674;
    w[144]= 0.0187999;
    w[145]= 0.0135013;
    w[146]= 0.0160794;
    w[147]= 0.0180586;
    w[148]= 0.00905508;
    w[149]= 0.00869858;
    w[150]= 0.0193968;
    w[151]= 0.0209201;
    w[152]= 0.0084405;
    w[153]= 0.0407657;
    w[154]= 0.0109116;
    w[155]= 0.0262218;
    w[156]= 0.0104767;
    w[157]= 1;
    w[158]= 1;
    w[159]= 1;
    w[160]= 1;
    w[161]= 0.00658031;
    w[162]= 0.0051814;
    w[163]= 1;
    w[164]= 1;
    w[165]= 1;
    w[166]= 1;
    w[167]= 1;
    w[168]= 1;
    w[169]= 1;
    w[170]= 1;
    w[171]= 1;
    w[172]= 1;
    w[173]= 1;
    w[174]= 1;
    w[175]= 1;
    w[176]= 1;
    w[177]= 1;
    w[178]= 1;
    w[179]= 1;
    w[180]= 1;
    w[181]= 1;
    w[182]= 1;
    w[183]= 1;
    w[184]= 1;
    w[185]= 1;
    w[186]= 1;
    w[187]= 1;
    w[188]= 1;
    w[189]= 1;
    w[190]= 1;
    w[191]= 1;
    w[192]= 1;
    w[193]= 1;
    w[194]= 1;
    w[195]= 1;
    w[196]= 1;
    w[197]= 1;
    w[198]= 1;
    w[199]= 1;
    w[200]= 1;
    w[201]= 1;
    w[202]= 1;
    w[203]= 1;
    w[204]= 1;
    w[205]= 1;
    w[206]= 1;
    w[207]= 1;
    w[208]= 1;
    w[209]= 1;
    w[210]= 1;
    w[211]= 1;
    w[212]= 1;
    w[213]= 1;
    w[214]= 1;
    w[215]= 1;
    w[216]= 1;
    w[217]= 1;
    w[218]= 1;
    w[219]= 1;
    w[220]= 1;
    w[221]= 1;
    w[222]= 1;
    w[223]= 1;
    w[224]= 1;
    w[225]= 1;
    w[226]= 1;
    w[227]= 1;
    w[228]= 1;
    w[229]= 1;
    w[230]= 1;
    w[231]= 1;
    w[232]= 1;
    w[233]= 1;
    w[234]= 1;
    w[235]= 1;
    w[236]= 1;
    w[237]= 1;
    w[238]= 1;
    w[239]= 1;




    TH1F h("boh","boh",240,0.,80.);

    for(int k=0;k<240;k++){
        h.SetBinContent(k+1,w[k]);
    }

    //h.Draw(); gPad->Update(); Wait();

    return h.GetBinContent(h.FindBin(input));

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

    std::cout << "2011->2012 weights being applied" << std::endl;
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

    std::cout << doRho << std::endl;
    std::cout << puWeight << std::endl;
    std::cout << rhoWeight << std::endl;

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
                        weight*=weightTrue2012(bin);
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
                    weight*=weightTrue2012(truth);
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
