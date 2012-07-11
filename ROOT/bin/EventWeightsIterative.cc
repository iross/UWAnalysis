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
edm::Lumi3DReWeighting *LumiWeights;



void readdir(TDirectory *dir,optutl::CommandLineParser parser,float ev,int doPU,bool doRho,TH1F* puWeight,TH1F* rhoWeight); 

float weightVtx2012(float input){
    float w[50];
    w[0]= 1;
    w[1]= 3.80188;
    w[2]= 7.43788;
    w[3]= 10.1007;
    w[4]= 11.5966;
    w[5]= 12.363;
    w[6]= 12.1842;
    w[7]= 10.8768;
    w[8]= 9.34933;
    w[9]= 7.97032;
    w[10]= 6.44093;
    w[11]= 5.13513;
    w[12]= 4.01773;
    w[13]= 3.10039;
    w[14]= 2.41549;
    w[15]= 1.90526;
    w[16]= 1.45678;
    w[17]= 1.10734;
    w[18]= 0.852742;
    w[19]= 0.653427;
    w[20]= 0.483757;
    w[21]= 0.350882;
    w[22]= 0.257672;
    w[23]= 0.188114;
    w[24]= 0.135134;
    w[25]= 0.105147;
    w[26]= 0.074528;
    w[27]= 0.0561453;
    w[28]= 0.0353962;
    w[29]= 0.0254212;
    w[30]= 0.0211541;
    w[31]= 0.0104266;
    w[32]= 0.0107742;
    w[33]= 0.00734512;
    w[34]= 0.00657981;
    w[35]= 0.00483097;
    w[36]= 0.00218257;
    w[37]= 0;
    w[38]= 0;
    w[39]= 0;
    w[40]= 0;
    w[41]= 0;
    w[42]= 0;
    w[43]= 0;
    w[44]= 0;
    w[45]= 0;
    w[46]= 0;
    w[47]= 0;
    w[48]= 0;
    w[49]= 0;

    TH1F h("boh","boh",50,0.,50.);

    for(int k=0;k<50;k++){
        h.SetBinContent(k+1,w[k]);
    }

    //h.Draw(); gPad->Update(); Wait();

    return h.GetBinContent(h.FindBin(input));

}



float weightTrue2012(float input){
    float w[240];

    w[0]= 1;
    w[1]= 1;
    w[2]= 0.347666;
    w[3]= 0.057976;
    w[4]= 1;
    w[5]= 1;
    w[6]= 0.137942;
    w[7]= 0.294455;
    w[8]= 1;
    w[9]= 1;
    w[10]= 40.3919;
    w[11]= 82.8298;
    w[12]= 5.37189;
    w[13]= 4.37917;
    w[14]= 1.6547;
    w[15]= 0.356916;
    w[16]= 0.149961;
    w[17]= 0.308492;
    w[18]= 0.448437;
    w[19]= 0.985068;
    w[20]= 1.70673;
    w[21]= 2.05223;
    w[22]= 3.91311;
    w[23]= 7.59393;
    w[24]= 9.015;
    w[25]= 9.80387;
    w[26]= 16.3888;
    w[27]= 12.634;
    w[28]= 18.3578;
    w[29]= 15.9372;
    w[30]= 12.3494;
    w[31]= 13.3148;
    w[32]= 11.5551;
    w[33]= 10.3918;
    w[34]= 13.6576;
    w[35]= 16.7288;
    w[36]= 11.2055;
    w[37]= 9.2393;
    w[38]= 11.8338;
    w[39]= 9.93147;
    w[40]= 10.2127;
    w[41]= 11.6627;
    w[42]= 9.58372;
    w[43]= 10.2706;
    w[44]= 9.65236;
    w[45]= 8.05543;
    w[46]= 8.56992;
    w[47]= 7.82601;
    w[48]= 6.2448;
    w[49]= 6.0204;
    w[50]= 5.73699;
    w[51]= 3.82455;
    w[52]= 4.11483;
    w[53]= 3.80724;
    w[54]= 2.80522;
    w[55]= 2.5295;
    w[56]= 2.40911;
    w[57]= 1.88277;
    w[58]= 1.7617;
    w[59]= 1.6591;
    w[60]= 1.34511;
    w[61]= 1.28253;
    w[62]= 1.17393;
    w[63]= 1.04343;
    w[64]= 1.00926;
    w[65]= 0.938607;
    w[66]= 0.819199;
    w[67]= 0.808301;
    w[68]= 0.76742;
    w[69]= 0.71474;
    w[70]= 0.660683;
    w[71]= 0.617037;
    w[72]= 0.584368;
    w[73]= 0.569824;
    w[74]= 0.520834;
    w[75]= 0.499416;
    w[76]= 0.466491;
    w[77]= 0.441786;
    w[78]= 0.416934;
    w[79]= 0.382706;
    w[80]= 0.374871;
    w[81]= 0.340864;
    w[82]= 0.316502;
    w[83]= 0.289858;
    w[84]= 0.279737;
    w[85]= 0.259175;
    w[86]= 0.239653;
    w[87]= 0.231895;
    w[88]= 0.205767;
    w[89]= 0.197748;
    w[90]= 0.184162;
    w[91]= 0.169218;
    w[92]= 0.151916;
    w[93]= 0.141958;
    w[94]= 0.133088;
    w[95]= 0.1228;
    w[96]= 0.111687;
    w[97]= 0.108772;
    w[98]= 0.0950744;
    w[99]= 0.0900744;
    w[100]= 0.0830298;
    w[101]= 0.073475;
    w[102]= 0.0721913;
    w[103]= 0.0645228;
    w[104]= 0.0608371;
    w[105]= 0.0545954;
    w[106]= 0.0507149;
    w[107]= 0.0472908;
    w[108]= 0.0430741;
    w[109]= 0.0411351;
    w[110]= 0.0365306;
    w[111]= 0.0358602;
    w[112]= 0.0323509;
    w[113]= 0.0278717;
    w[114]= 0.030378;
    w[115]= 0.0271282;
    w[116]= 0.0228582;
    w[117]= 0.0237096;
    w[118]= 0.0206375;
    w[119]= 0.0172051;
    w[120]= 0.0183614;
    w[121]= 0.0171222;
    w[122]= 0.0137028;
    w[123]= 0.0156479;
    w[124]= 0.0139941;
    w[125]= 0.0118807;
    w[126]= 0.0125868;
    w[127]= 0.0109447;
    w[128]= 0.0100195;
    w[129]= 0.0114331;
    w[130]= 0.00869947;
    w[131]= 0.00803327;
    w[132]= 0.00847969;
    w[133]= 0.00766411;
    w[134]= 0.00631771;
    w[135]= 0.00936503;
    w[136]= 0.00719816;
    w[137]= 0.00578185;
    w[138]= 0.00866226;
    w[139]= 0.00533518;
    w[140]= 0.00588251;
    w[141]= 0.00799922;
    w[142]= 0.00838576;
    w[143]= 0.00407795;
    w[144]= 0.00996993;
    w[145]= 0.00709169;
    w[146]= 0.0083646;
    w[147]= 0.00930319;
    w[148]= 0.00461932;
    w[149]= 0.0043938;
    w[150]= 0.00970057;
    w[151]= 0.0103579;
    w[152]= 0.00413702;
    w[153]= 0.0197785;
    w[154]= 0.00524003;
    w[155]= 0.012463;
    w[156]= 0.00492797;
    w[157]= 1;
    w[158]= 1;
    w[159]= 1;
    w[160]= 1;
    w[161]= 0.00293528;
    w[162]= 0.0022864;
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



float weightObs2012(float input){
    if(input>60) return 1;
    float w[60];

    w[0]= 5.51579;
    w[1]= 23.681;
    w[2]= 5.63752;
    w[3]= 5.5426;
    w[4]= 5.69802;
    w[5]= 8.27157;
    w[6]= 8.3319;
    w[7]= 9.37605;
    w[8]= 9.31188;
    w[9]= 8.63289;
    w[10]= 8.42798;
    w[11]= 7.9449;
    w[12]= 6.74402;
    w[13]= 5.8732;
    w[14]= 4.97027;
    w[15]= 4.06721;
    w[16]= 3.53469;
    w[17]= 2.9148;
    w[18]= 2.38501;
    w[19]= 1.83915;
    w[20]= 1.51014;
    w[21]= 1.20599;
    w[22]= 0.995973;
    w[23]= 0.7824;
    w[24]= 0.637576;
    w[25]= 0.5222;
    w[26]= 0.426538;
    w[27]= 0.33403;
    w[28]= 0.279654;
    w[29]= 0.224268;
    w[30]= 0.181267;
    w[31]= 0.156933;
    w[32]= 0.126441;
    w[33]= 0.10488;
    w[34]= 0.0897339;
    w[35]= 0.0725403;
    w[36]= 0.0627614;
    w[37]= 0.0511912;
    w[38]= 0.0434455;
    w[39]= 0.0379792;
    w[40]= 0.0322443;
    w[41]= 0.0267919;
    w[42]= 0.0236232;
    w[43]= 0.0193673;
    w[44]= 0.0178114;
    w[45]= 0.014522;
    w[46]= 0.0127276;
    w[47]= 0.0104719;
    w[48]= 0.010401;
    w[49]= 0.00838839;
    w[50]= 0.00776264;
    w[51]= 0.00612802;
    w[52]= 0.00579364;
    w[53]= 0.00441753;
    w[54]= 0.00425444;
    w[55]= 0.00408069;
    w[56]= 0.00376297;
    w[57]= 0.00278731;
    w[58]= 0.00281234;
    w[59]= 0.00250684;


    TH1F h("boh","boh",60,0.,60.);

    for(int k=0;k<60;k++){
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


float weightObs2011(float input){
    if(input>50) 
        return 1;


    float w[50];

    w[0]= 0.275778;
    w[1]= 0.568981;
    w[2]= 0.871748;
    w[3]= 1.04549;
    w[4]= 1.24298;
    w[5]= 1.30918;
    w[6]= 1.38978;
    w[7]= 1.40581;
    w[8]= 1.36702;
    w[9]= 1.33929;
    w[10]= 1.31885;
    w[11]= 1.28368;
    w[12]= 1.23507;
    w[13]= 1.1645;
    w[14]= 1.09878;
    w[15]= 0.983055;
    w[16]= 0.897501;
    w[17]= 0.769105;
    w[18]= 0.663561;
    w[19]= 0.555837;
    w[20]= 0.449835;
    w[21]= 0.362963;
    w[22]= 0.285554;
    w[23]= 0.225824;
    w[24]= 0.172468;
    w[25]= 0.133716;
    w[26]= 0.100067;
    w[27]= 0.0744128;
    w[28]= 0.0533928;
    w[29]= 0.0387526;
    w[30]= 0.0279365;
    w[31]= 0.020139;
    w[32]= 0.0140052;
    w[33]= 0.0096249;
    w[34]= 0.00685049;
    w[35]= 0.00466485;
    w[36]= 0.00343693;
    w[37]= 0.00232104;
    w[38]= 0.0015562;
    w[39]= 0.00114197;
    w[40]= 0.000801995;
    w[41]= 0.000588331;
    w[42]= 0.00054092;
    w[43]= 0.000404105;
    w[44]= 0.000451338;
    w[45]= 0.000446844;
    w[46]= 0.000515178;
    w[47]= 0.000618579;
    w[48]= 0.00100209;
    w[49]= 0.000910643;




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

    w[0]= 0.00038657;
    w[1]= 0.000218788;
    w[2]= 0.000397666;
    w[3]= 0.0294631;
    w[4]= 0.0347075;
    w[5]= 0.00130288;
    w[6]= 0.00734151;
    w[7]= 0.0585764;
    w[8]= 0.202286;
    w[9]= 0.386594;
    w[10]= 0.609991;
    w[11]= 1.0591;
    w[12]= 1.30646;
    w[13]= 1.56364;
    w[14]= 1.9688;
    w[15]= 2.38067;
    w[16]= 3.52793;
    w[17]= 2.14187;
    w[18]= 2.18393;
    w[19]= 2.16427;
    w[20]= 2.13778;
    w[21]= 1.59687;
    w[22]= 1.88185;
    w[23]= 1.80741;
    w[24]= 1.96543;
    w[25]= 2.05768;
    w[26]= 2.36497;
    w[27]= 3.29516;
    w[28]= 3.03962;
    w[29]= 1.84058;
    w[30]= 2.39978;
    w[31]= 2.96095;
    w[32]= 8.70667;
    w[33]= 7.77485;
    w[34]= 4.9914;
    w[35]= 107.562;
    w[36]= 2.75765;
    w[37]= 1;
    w[38]= 1;
    w[39]= 0.983563;
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


float weightObs2011to2012(float input){
    if(input>50) 
        return 1;

    float w[50];


    w[0]= 0.0121356;
    w[1]= 0.0246885;
    w[2]= 0.037522;
    w[3]= 0.0485752;
    w[4]= 0.0715009;
    w[5]= 0.106066;
    w[6]= 0.170489;
    w[7]= 0.265134;
    w[8]= 0.388504;
    w[9]= 0.55317;
    w[10]= 0.760111;
    w[11]= 0.993055;
    w[12]= 1.23993;
    w[13]= 1.47616;
    w[14]= 1.72221;
    w[15]= 1.87659;
    w[16]= 2.06585;
    w[17]= 2.12259;
    w[18]= 2.19142;
    w[19]= 2.19928;
    w[20]= 2.1409;
    w[21]= 2.09124;
    w[22]= 2.00891;
    w[23]= 1.96039;
    w[24]= 1.87013;
    w[25]= 1.83577;
    w[26]= 1.76492;
    w[27]= 1.71206;
    w[28]= 1.62761;
    w[29]= 1.58973;
    w[30]= 1.56587;
    w[31]= 1.56501;
    w[32]= 1.52982;
    w[33]= 1.49671;
    w[34]= 1.53403;
    w[35]= 1.51912;
    w[36]= 1.6401;
    w[37]= 1.62962;
    w[38]= 1.60443;
    w[39]= 1.70723;
    w[40]= 1.68598;
    w[41]= 1.6409;
    w[42]= 1.82793;
    w[43]= 1.47647;
    w[44]= 1.5941;
    w[45]= 1.3992;
    w[46]= 1.35456;
    w[47]= 1.3272;
    w[48]= 1.73311;
    w[49]= 1.2656;


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
            LumiWeights = new edm::Lumi3DReWeighting("../puInfoMC3D.root","../puInfo3D.root","pileup","pileup");
            LumiWeights->weight3D_init(1.0);
        }
        else  if(fPU3!=0 && fPU3->IsOpen()) {
            doPU=2;
            printf("ENABLING PU WEIGHTING USING 3D with ready distribution\n");
            fPU3->Close();
            LumiWeights = new edm::Lumi3DReWeighting(mc,data);
            LumiWeights->weight3D_init("../Weight3D.root");
        }
        else   if(fPU4!=0 && fPU4->IsOpen()) {

            //searxch in this folder
            doPU=2;
            printf("ENABLING PU WEIGHTING USING 3D with  distribution you just made\n");
            fPU4->Close();
            LumiWeights = new edm::Lumi3DReWeighting(mc,data);
            LumiWeights->weight3D_init("Weight3D.root");

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
                    float w = LumiWeights->weight3D( bxm,bx,bxp);
                    if(i==1)
                        printf("PU WEIGHT = %f\n",w);
                    weight*=w;
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
