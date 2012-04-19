#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "PhysicsTools/Utilities/interface/Lumi3DReWeighting.h"
#include "PhysicsTools/Utilities/interface/LumiReWeighting.h"
#include "TFile.h"
#include "TROOT.h"
#include "TKey.h"
#include "TTree.h"
#include "TH1F.h"

//Distribution from Fall 2011

std::vector<float> data;
std::vector<float> mc;
edm::Lumi3DReWeighting *LumiWeights;
edm::LumiReWeighting *LumiWeightsOld;


 Double_t weightsMC_[50] = {
   0.00905444,
   0.019661,
   0.0321446,
   0.0435141,
   0.0527906,
   0.0590329,
   0.061598,
   0.061749,
   0.0592039,
   0.0569448,
   0.0535766,
   0.0494074,
   0.0458052,
   0.0422751,
   0.0389909,
   0.0356777,
   0.0330786,
   0.0304045,
   0.0275734,
   0.0249792,
   0.0226811,
   0.020367,
   0.0181379,
   0.0161678,
   0.0141187,
   0.0120066,
   0.0104015,
   0.00893944,
   0.00755337,
   0.00628831,
   0.00529026,
   0.00435321,
   0.00364318,
   0.00287814,
   0.00224511,
   0.00174809,
   0.00143807,
   0.00111205,
   0.000795039,
   0.000643032,
   0.000463023,
   0.000363018,
   0.000269013,
   0.00020101,
   0.000135007,
   0.000103005,
   6.80033e-05,
   5.40026e-05,
   4.90024e-05,
     2.50012e-05
 };


 Double_t weights_[50] = {
   0.00268287,
   0.0111378,
   0.0253649,
   0.0426735,
   0.0595703,
   0.0727177,
   0.0810381,
   0.0842113,
   0.0833151,
   0.0795788,
   0.0738552,
   0.0672576,
   0.0599305,
   0.0522761,
   0.0442358,
   0.0370232,
   0.030315,
   0.0243174,
   0.0189967,
   0.0145095,
   0.0107956,
   0.00779958,
   0.00555043,
   0.00381755,
   0.00257767,
   0.00169383,
   0.00108528,
   0.000661581,
   0.000409454,
   0.000254036,
   0.000151171,
   8.96485e-05,
   5.26011e-05,
   2.82925e-05,
   1.61978e-05,
   9.68528e-06,
   1.01147e-05,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
   0,
     0
 };



//68mb
//  Double_t weightsMC_[50] = {
//     0.00290212,
//     0.0123985,
//     0.0294783,
//     0.0504491,
//     0.0698525,
//     0.0836611,
//     0.0905799,
//     0.0914388,
//     0.0879379,
//     0.0817086,
//     0.073937,
//     0.0653785,
//     0.0565162,
//     0.047707,
//     0.0392591,
//     0.0314457,
//     0.0244864,
//     0.018523,
//     0.013608,
//     0.00970977,
//     0.00673162,
//     0.00453714,
//     0.00297524,
//     0.00189981,
//     0.00118234,
//     0.000717854,
//     0.00042561,
//     0.000246653,
//     0.000139853,
//     7.76535E-05,
//     4.22607E-05,
//     2.25608E-05,
//     1.18236E-05,
//     6.0874E-06,
//     6.04852E-06,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0,
//     0
//   };

void readdir(TDirectory *dir,optutl::CommandLineParser parser,float ev,int doPU,bool doRho,TH1F* puWeight,TH1F* rhoWeight); 



int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("histoName",optutl::CommandLineParser::kString,"Counter Histogram Name","EventSummary");
   parser.addOption("weight",optutl::CommandLineParser::kDouble,"Weight to apply",1.0);
   parser.addOption("type",optutl::CommandLineParser::kInteger,"Type",0);
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__WEIGHT__");
   parser.addOption("doOneD",optutl::CommandLineParser::kInteger,"Do OneD",0);

   
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
   else if(parser.integerValue("doOneD")) {
     doPU=3;
     std::vector<float> mc;
     std::vector<float> data;

     for(int i=0;i<50;++i) {
       mc.push_back(weightsMC_[i]);
       data.push_back(weights_[i]);
     }


     LumiWeightsOld = new edm::LumiReWeighting(mc,data);

     
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
      TBranch *typeBranch = t->Branch("TYPE",&type,"TYPE/I");
      int vertices;
      float bxm=0;
      float bx=0;
      float bxp=0;

      if(doPU==1)
	t->SetBranchAddress("vertices",&vertices);
      else if(doPU==2 ||doPU==3) {
	t->SetBranchAddress("puBXminus",&bxm);
	t->SetBranchAddress("puBX0",&bx);
	t->SetBranchAddress("puBXplus",&bxp);
      }

      float rho=0.0;
      if(doRho)
	t->SetBranchAddress("Rho",&rho);

      printf("Found tree -> weighting\n");
      for(Int_t i=0;i<t->GetEntries();++i)
	{
	  t->GetEntry(i);
	  weight = parser.doubleValue("weight")/(ev);
	  if(doPU==1) {
	    int bin=puWeight->FindBin(vertices);
	    if(bin>puWeight->GetNbinsX())
	      {
		printf("Overflow using max bin\n");
		bin = puWeight->GetNbinsX();
	      }
	    weight*=puWeight->GetBinContent(bin);
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
		//temp. commented todo: revert when bx info is in ntuples.
	    //weight*=LumiWeightsOld->weight(bx);
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
