#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TMatrixD.h"
#include "TVectorD.h"
#include "TDecompLU.h"
#include "TDecompSVD.h"
#include "TH1.h"
#include "TF1.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 


struct BkgOutput {
  float QCD;
  float EWK;
  float ZTT;
};

BkgOutput extractSignal(float N0, float N1, float N2, float eQCD1 ,float eQCD2, float eEWK1,float eEWK2,float eZTT1,float eZTT2);
unsigned poissonFluctuation(int N);




int main (int argc, char* argv[]) 
{

   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------

   //Data
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");

   parser.addOption("zttFile",optutl::CommandLineParser::kString,"File with Z tau tau","ZTT.root");
   parser.addOption("wmnFile",optutl::CommandLineParser::kString,"File with W mu nu","WMN.root");
   parser.addOption("qcdFile",optutl::CommandLineParser::kString,"File with QCD","QCD.root");
   parser.addOption("wtnFile",optutl::CommandLineParser::kString,"File with W ->tau nu","WTN.root");
   parser.addOption("zmmFile",optutl::CommandLineParser::kString,"File with Z -> mumu ","ZMM.root");
   parser.addOption("topFile",optutl::CommandLineParser::kString,"File with TTBAr","TOP.root");

   parser.addOption("preselection",optutl::CommandLineParser::kString,"PreSelection","muTauPt1>10&&muTauPt2>15&&HLT_Mu9&&muTauVBTFID&&muTauDecayFound&&muTauMuonVeto&&muTauMt1<40.&&muTauTriggerMatch&&mumuSize==0&&muTauRelPFIso<0.1");

   parser.addOption("selection1",optutl::CommandLineParser::kString,"Selection1","muTauLooseIso");
   parser.addOption("selection2",optutl::CommandLineParser::kString,"Selection2","muTauCharge==0");

   parser.addOption("eQCD1",optutl::CommandLineParser::kDouble,"eQCD1",-1.);
   parser.addOption("eQCD2",optutl::CommandLineParser::kDouble,"eQCD2",-1.);


   parser.addOption("eEWK1",optutl::CommandLineParser::kDouble,"eEWK1",-1.);
   parser.addOption("eEWK2",optutl::CommandLineParser::kDouble,"eEWK2",-1.);



   parser.addOption("eZTT1",optutl::CommandLineParser::kDouble,"eZTT1",-1.);
   parser.addOption("eZTT2",optutl::CommandLineParser::kDouble,"eZTT2",-1.);


   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","muTauEventTree/eventTree");
   parser.addOption("lumi",optutl::CommandLineParser::kDouble,"Luminosity",30.);
   parser.addOption("experiments",optutl::CommandLineParser::kInteger,"Pseudoexperiments",1);

   parser.parseArguments (argc, argv);


   //OPEN THE FILES------------------------------------------------
   TFile *out = new TFile("out.root","RECREATE");

    float weight=0;




     TFile *dataFile = new TFile(parser.stringValue("dataFile").c_str());
     TTree * dataTree = (TTree*)dataFile->Get(parser.stringValue("treeName").c_str());
     out->cd();
     TTree * data = dataTree->CopyTree(parser.stringValue("preselection").c_str());

     float  NDATA  =(float) data->GetEntries();
     float  NDATA1 =(float) data->GetEntries(parser.stringValue("selection1").c_str());
     float  NDATA2 =(float) data->GetEntries((parser.stringValue("selection1")+"&&"+parser.stringValue("selection2")).c_str());
     dataFile->Close();
    


    TFile *zttFile = new TFile(parser.stringValue("zttFile").c_str());
    TTree * zttTree = (TTree*)zttFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * ztt = zttTree->CopyTree(parser.stringValue("preselection").c_str());
    ztt->SetBranchAddress("__WEIGHT__",&weight);
    ztt->GetEntry(1);

    float ZTT  = weight*ztt->GetEntries();
    float ZTT1 = weight*ztt->GetEntries(parser.stringValue("selection1").c_str());
    float ZTT2 = weight*ztt->GetEntries((parser.stringValue("selection1")+"&&"+parser.stringValue("selection2")).c_str());


    zttFile->Close();


    printf("A\n");

    TFile *wmnFile = new TFile(parser.stringValue("wmnFile").c_str());
    TTree * wmnTree = (TTree*)wmnFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * wmn = wmnTree->CopyTree(parser.stringValue("preselection").c_str());
   wmn->SetBranchAddress("__WEIGHT__",&weight);
   wmn->GetEntry(1);

    float WMN  = weight*wmn->GetEntries();
    float WMN1 = weight*wmn->GetEntries(parser.stringValue("selection1").c_str());
    float WMN2 = weight*wmn->GetEntries((parser.stringValue("selection1")+"&&"+parser.stringValue("selection2")).c_str());


    //    wmn->SetDirectory(0);
    wmnFile->Close();

    printf("B\n");



    TFile *wtnFile = new TFile(parser.stringValue("wtnFile").c_str());
    TTree * wtnTree = (TTree*)wtnFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * wtn = wtnTree->CopyTree(parser.stringValue("preselection").c_str());
    wtn->SetBranchAddress("__WEIGHT__",&weight);
    wtn->GetEntry(1);

    float WTN  = weight*wtn->GetEntries();
    float WTN1 = weight*wtn->GetEntries(parser.stringValue("selection1").c_str());
    float WTN2 = weight*wtn->GetEntries((parser.stringValue("selection1")+"&&"+parser.stringValue("selection2")).c_str());

    wtnFile->Close();


    printf("C\n");


    TFile *zmmFile = new TFile(parser.stringValue("zmmFile").c_str());
    TTree * zmmTree = (TTree*)zmmFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * zmm = zmmTree->CopyTree(parser.stringValue("preselection").c_str());
    zmm->SetBranchAddress("__WEIGHT__",&weight);
    zmm->GetEntry(1);

    float ZMM  = weight*zmm->GetEntries();
    float ZMM1 = weight*zmm->GetEntries(parser.stringValue("selection1").c_str());
    float ZMM2 = weight*zmm->GetEntries((parser.stringValue("selection1")+"&&"+parser.stringValue("selection2")).c_str());

    printf("D\n");



    zmmFile->Close();




    TFile *topFile = new TFile(parser.stringValue("topFile").c_str());
    TTree * topTree = (TTree*)topFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * top = topTree->CopyTree(parser.stringValue("preselection").c_str());
    top->SetBranchAddress("__WEIGHT__",&weight);
    top->GetEntry(1);

    float TOP  = weight*top->GetEntries();
    float TOP1 = weight*top->GetEntries(parser.stringValue("selection1").c_str());
    float TOP2 = weight*top->GetEntries((parser.stringValue("selection1")+"&&"+parser.stringValue("selection2")).c_str());

    topFile->Close();


    printf("E\n");


    TFile *qcdFile = new TFile(parser.stringValue("qcdFile").c_str());
    TTree * qcdTree = (TTree*)qcdFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * qcd = qcdTree->CopyTree(parser.stringValue("preselection").c_str());
    qcd->SetBranchAddress("__WEIGHT__",&weight);
    qcd->GetEntry(1);
    float QCD  = weight*qcd->GetEntries();
    float QCD1 = weight*qcd->GetEntries(parser.stringValue("selection1").c_str());
    float QCD2 = weight*qcd->GetEntries((parser.stringValue("selection1")+"&&"+parser.stringValue("selection2")).c_str());

    qcdFile->Close();

    printf("F\n");


    float eQCD1 = parser.doubleValue("eQCD1");
    float eQCD2 = parser.doubleValue("eQCD2");


    float eEWK1 = parser.doubleValue("eEWK1");
    float eEWK2 = parser.doubleValue("eEWK2");


    float eZTT1 = parser.doubleValue("eZTT1");
    float eZTT2 = parser.doubleValue("eZTT2");

    printf("G\n");



    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //CREATE THE DATASETS FROM THE TREES
    ///////////////////////////////////////////////////////////////////////////////////// 






   //Now run pseudo experiments 
   printf("Starting pseudoexperiments\n");

   double lumi = parser.doubleValue("lumi");

   for(int i=0;i<parser.integerValue("experiments");++i)
     {
       printf("Experiment N=%d\n",i);
       
       
       std::cout << "Generating Events---"<<std::endl;
       
       
       float  zttTotal =(float) poissonFluctuation((int)(ZTT*lumi)); 
       float ztt1 = (float)( ZTT1*zttTotal/ZTT);
       float ztt2 = (float)( ZTT2*zttTotal/ZTT);
       
       float  zmmTotal = (float)poissonFluctuation((int)(ZMM*lumi)); 
       float zmm1 = (float)( ZMM1*zmmTotal/ZMM);
       float zmm2 = (float)( ZMM2*zmmTotal/ZMM);

       float  wmnTotal = (float)poissonFluctuation((int)(WMN*lumi)); 
       float wmn1 = (float)( WMN1*wmnTotal/WMN);
       float wmn2 = (float)( WMN2*wmnTotal/WMN);


       float  wtnTotal = (float)poissonFluctuation((int)(WTN*lumi)); 
       float wtn1 = (float)( WTN1*wtnTotal/WTN);
       float wtn2 = (float)( WTN2*wtnTotal/WTN);

       float  qcdTotal = (float)poissonFluctuation((int)(QCD*lumi)); 
       float qcd1 = (float)( QCD1*qcdTotal/QCD);
       float qcd2 = (float)( QCD2*qcdTotal/QCD);

       float  topTotal = (float)poissonFluctuation((int)(TOP*lumi)); 
       float top1 = (float)( TOP1*topTotal/TOP);
       float top2 = (float)( TOP2*topTotal/TOP);

       float  ewkTotal = zmmTotal+wtnTotal+wmnTotal+topTotal; 
       float ewk1 = zmm1+wtn1+wmn1+top1; 
       float ewk2 = zmm2+wtn2+wmn2+top2;


       float N0 = (zttTotal+ewkTotal+qcdTotal);
       float N1 = (ztt1+ewk1+qcd1);
       float N2 = (ztt2+ewk2+qcd2);

       printf("Exp.Effiicencies QCD %f %f\n",qcd1/qcdTotal,qcd2/qcd1);
       printf("Exp.Effiicencies EWK %f %f\n",ewk1/ewkTotal,ewk2/ewk1);
       printf("Exp.Effiicencies ZTT %f %f\n",ztt1/zttTotal,ztt2/ztt1);


       std::cout << "Z tau tau expected " << zttTotal <<std::endl;
       std::cout << "EWK/TOP expected " << ewkTotal <<std::endl;
       std::cout << "QCD expected " << qcdTotal <<std::endl;
       BkgOutput output ;
       
       if(eQCD1>0)
	  output = extractSignal(N0,N1,N2,eQCD1,eQCD2,eEWK1,eEWK2,eZTT1,eZTT2);
       else
	 output = extractSignal(N0,N1,N2,qcd1/qcdTotal,qcd2/qcd1,ewk1/ewkTotal,ewk2/ewk1,ztt1/zttTotal,ztt2/ztt1);
	 

       std::cout << "Z tau tau predicted " << output.ZTT <<std::endl;
       std::cout << "EWK/TOP prediced " << output.EWK<<std::endl;
       std::cout << "QCD predicted " << output.QCD <<std::endl;


//        std::cout <<"DATA"<<std::endl;
//        output = extractSignal(NDATA,NDATA1,NDATA2,qcd1/qcdTotal,qcd2/qcd1,ewk1/ewkTotal,ewk2/ewk1,ztt1/zttTotal,ztt2/ztt1);

//        std::cout << "Z tau tau predicted " << output.ZTT <<std::endl;
//        std::cout << "EWK/TOP prediced " << output.EWK<<std::endl;
//        std::cout << "QCD predicted " << output.QCD <<std::endl;


     }



   

  
   
     
}


BkgOutput extractSignal(float N0, float N1, float N2, float eQCD1 ,float eQCD2, float eEWK1,float eEWK2,float eZTT1,float eZTT2)
{

  printf("Effiicencies QCD %f %f\n",eQCD1,eQCD2);
  printf("Effiicencies EWK %f %f\n",eEWK1,eEWK2);
  printf("Effiicencies ZTT %f %f\n",eZTT1,eZTT2);


  TMatrixD  matrix(3,3);
  Double_t matrArray[] = {1. , 1. , 1.,
			  eQCD1,eEWK1,eZTT1,
			  eQCD1*eQCD2,eEWK1*eEWK2,eZTT1*eZTT2};
  matrix.SetMatrixArray(matrArray);
  TVectorD b(3);
  b(0) = N0;
  b(1) = N1;
  b(2) = N2;


//OK try the simple least square method
//First create the covariance matrix
  TMatrixD  covMatrix(3,3);
   Double_t covMatrArray[] = {1./N0 , 0. , 0.,
 			     0.,1./N1,0.0,
 			     0.0,0.0,1./N2};

//   Double_t covMatrArray[] = {1. , 0. , 0.,
// 			     0.,1.,0.0,
// 			     0.0,0.0,1};

  covMatrix.SetMatrixArray(covMatrArray);

  //OK now create the A_TD^2A
  printf("Matrix\n");
  matrix.Print();

  printf("Transpose Matrix\n");
  matrix.T().Print();


  printf("Covariant Matrix\n");
  covMatrix.Print();


  TMatrixD firstPart = (matrix.T())*covMatrix*matrix;

  printf("FirstPart\n");
  firstPart.Print();
  

    TDecompLU LU(firstPart);
    LU.SetTol(1e-8);
    TMatrixD firstPartInv = LU.Invert();

    printf("Inverted\n");
    firstPartInv.Print();


    printf("InversionTest\n");
    (firstPartInv*firstPart).Print();

  //Invert it
  //  Double_t det=0;
  // TMatrixD firstPartInv = firstPart.Invert(&det);
  // printf("Determinant=%f\n",det);

    printf("SecondPart\n");
    TMatrixD secondPart = (matrix.T())*covMatrix;
    secondPart.Print();


    printf("Final matrix \n");
    TMatrixD finalMatrix = firstPartInv*secondPart;
    finalMatrix.Print();
  //Now create the solution
    TVectorD solution = finalMatrix*b;
  //  TVectorD solution = (matrix.T()*matrix).Invert()*matrix.T()*b;



    //    TDecompLU LU2(matrix);
    //    Bool_t ok;
    //    solution = LU2.Solve(b,ok);

    //    if(!ok)
    //      printf("LU failed\n");



  BkgOutput output;



  //   output.QCD =eQCD1*eQCD2*solution(0);
  //   output.EWK = eEWK1*eEWK2*solution(1);
  //   output.ZTT = eZTT1*eZTT2*solution(2);

         output.QCD = solution(0);
    output.EWK = solution(1);
    output.ZTT = solution(2);

  return output;
  
}  



unsigned poissonFluctuation(int N)
{
  TF1 f("mypoisson","TMath::Poisson(x,[0])",0,5.*N);
  f.SetParameter(0,N);
  unsigned N2 = (unsigned)(f.GetRandom());
  return N2;
}

