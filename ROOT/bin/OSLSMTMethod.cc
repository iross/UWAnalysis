#include "RooRealVar.h"
#include "RooGaussian.h"
#include "RooBifurGauss.h"
#include "RooExponential.h"
#include "RooAddPdf.h"
#include "RooHistPdf.h"
#include "RooDataSet.h"
#include "RooDataHist.h"
#include "RooGlobalFunc.h" 
#include "RooChi2Var.h"
#include "RooRealVar.h"
#include "RooLandau.h"
#include "RooGaussian.h"
#include "RooCBShape.h"
#include "RooNumConvPdf.h"
#include "RooMinuit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 


struct BkgOutput {
  float OSWInCore;
  float OSWInCoreErr;
  float SSWInCore;
  float SSWInCoreErr;
  float SSOtherInCore;
  float SSOtherInCoreErr;
  float OSOtherInCore;
  float OSOtherInCoreErr;
  float OSSignalInCore;
  float OSSignalInCoreErr;

};

BkgOutput extractSignal(TTree* data, float extrapFactor, float extrapFactorErr,float oslsFactor,float oslsFactorError,float coreLimit,float sidebandLimit,float wtnFactor);
RooDataSet* generateDSET(const RooAbsPdf& pdf,const RooRealVar& var,const RooRealVar& charge ,int N);


unsigned poissonFluctuation(int N);

void drawPDF(const RooHistPdf& ,const RooRealVar&,const TString& );


int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


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

   parser.addOption("preselection",optutl::CommandLineParser::kString,"PreSelection","muTauPt1>10&&muTauPt2>20&&HLT_Mu9&&muTauVBTFID&&muTauMuonVeto&&muTauLooseIso&&muTauRelPFIso<0.1&&muTauMt1<100.&&muTauTriggerMatch&&mumuSize==0&&muTauDecayFound");
   parser.addOption("sidebandLimit",optutl::CommandLineParser::kDouble,"sidebandLimit",60.);
   parser.addOption("coreLimit",optutl::CommandLineParser::kDouble,"core Limit",40.0);
   parser.addOption("qcdOSLS",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.03);
   parser.addOption("wmnFactor",optutl::CommandLineParser::kDouble,"WMN factor",-1.);
   parser.addOption("wtnFactor",optutl::CommandLineParser::kDouble,"W TauNuFactor",0.272);
   parser.addOption("qcdOSLSError",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.01);
   parser.addOption("treeName",optutl::CommandLineParser::kString,"tree Name","muTauEventTree/eventTree");
   parser.addOption("lumi",optutl::CommandLineParser::kDouble,"Luminosity",15.);
   parser.addOption("experiments",optutl::CommandLineParser::kInteger,"Pseudoexperiments",1);

   parser.parseArguments (argc, argv);


   //OPEN THE FILES------------------------------------------------
   TFile *out = new TFile("out.root","RECREATE");

    float weight=0;



    TFile *dataFile = new TFile(parser.stringValue("dataFile").c_str());
    TTree * dataTree = (TTree*)dataFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * data = dataTree->CopyTree(parser.stringValue("preselection").c_str());
    dataFile->Close();

    TFile *zttFile = new TFile(parser.stringValue("zttFile").c_str());
    TTree * zttTree = (TTree*)zttFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * ztt = zttTree->CopyTree(parser.stringValue("preselection").c_str());
    ztt->SetBranchAddress("__WEIGHT__",&weight);
    ztt->GetEntry(1);
    float zttWeightOS = weight*ztt->GetEntries("muTauCharge==0");
    float zttWeightSS = weight*ztt->GetEntries("muTauCharge!=0");
    float zttWeightTot = weight*ztt->GetEntries();

    zttFile->Close();




    TFile *wmnFile = new TFile(parser.stringValue("wmnFile").c_str());
    TTree * wmnTree = (TTree*)wmnFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * wmn = wmnTree->CopyTree(parser.stringValue("preselection").c_str());
   wmn->SetBranchAddress("__WEIGHT__",&weight);
   
   wmn->GetEntry(1);
   float wmnWeightOS = weight*wmn->GetEntries("muTauCharge==0");
   float wmnWeightSS = weight*wmn->GetEntries("muTauCharge!=0");
   float wmnWeightTot = weight*wmn->GetEntries();

    //    wmn->SetDirectory(0);
    wmnFile->Close();


    //caluclate extrapolation factor

   char sidebandPreselection[200];
   char corePreselection[200];


   sprintf(corePreselection,"muTauMt1<=%f",parser.doubleValue("coreLimit"));
   sprintf(sidebandPreselection,"muTauMt1>%f",parser.doubleValue("sidebandLimit"));

   //////Caluclate extrapolating factor!
   char sidebandWPreselection[200];
   char coreWPreselection[200];
   sprintf(coreWPreselection,"(muTauMt1<=%f)",parser.doubleValue("coreLimit"));
   sprintf(sidebandWPreselection,"(muTauMt1>%f)",parser.doubleValue("sidebandLimit"));
   TH1F* ht1 = new TH1F("wMT1","MT",20,0,100);
   wmn->Draw("muTauMt1>>wMT1",coreWPreselection,"goff");
   TH1F* ht2 = new TH1F("wMT2","MT",20,0,100);
   wmn->Draw("muTauMt1>>wMT2",sidebandWPreselection,"goff");
   
   double extrapFactor = (ht1->Integral()/ht2->Integral());
   double extrapFactorErr =extrapFactor*sqrt(1./ht1->Integral()+1./ht2->Integral());
   printf("extrapolation factor = %f +- %f\n",extrapFactor,extrapFactorErr);

   if(parser.doubleValue("wmnFactor")>0.)
     extrapFactor = parser.doubleValue("wmnFactor");


    TFile *wtnFile = new TFile(parser.stringValue("wtnFile").c_str());
    TTree * wtnTree = (TTree*)wtnFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * wtn = wtnTree->CopyTree(parser.stringValue("preselection").c_str());
    wtn->SetBranchAddress("__WEIGHT__",&weight);
    wtn->GetEntry(1);

   float wtnWeightOS = weight*wtn->GetEntries("muTauCharge==0");
   float wtnWeightSS = weight*wtn->GetEntries("muTauCharge!=0");
   float wtnWeightTot = weight*wtn->GetEntries();

    wtnFile->Close();

    TFile *zmmFile = new TFile(parser.stringValue("zmmFile").c_str());
    TTree * zmmTree = (TTree*)zmmFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * zmm = zmmTree->CopyTree(parser.stringValue("preselection").c_str());
    zmm->SetBranchAddress("__WEIGHT__",&weight);
    zmm->GetEntry(1);

   float zmmWeightOS = weight*zmm->GetEntries("muTauCharge==0");
   float zmmWeightSS = weight*zmm->GetEntries("muTauCharge!=0");
   float zmmWeightTot = weight*zmm->GetEntries();
    zmmFile->Close();




    TFile *topFile = new TFile(parser.stringValue("topFile").c_str());
    TTree * topTree = (TTree*)topFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * top = topTree->CopyTree(parser.stringValue("preselection").c_str());
    top->SetBranchAddress("__WEIGHT__",&weight);
    top->GetEntry(1);

    float topWeightOS = weight*top->GetEntries("muTauCharge==0");
    float topWeightSS = weight*top->GetEntries("muTauCharge!=0");
    float topWeightTot = weight*top->GetEntries();

    //    top->SetDirectory(0);
    topFile->Close();




    TFile *qcdFile = new TFile(parser.stringValue("qcdFile").c_str());
    TTree * qcdTree = (TTree*)qcdFile->Get(parser.stringValue("treeName").c_str());
    out->cd();
    TTree * qcd = qcdTree->CopyTree(parser.stringValue("preselection").c_str());
    qcd->SetBranchAddress("__WEIGHT__",&weight);
    qcd->GetEntry(1);

    float qcdWeightOS  = weight*qcd->GetEntries("muTauCharge==0");
    float qcdWeightSS  = weight*qcd->GetEntries("muTauCharge!=0");
    float qcdWeightTot = weight*qcd->GetEntries();
    qcdFile->Close();





    //////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////
    //CREATE THE DATASETS FROM THE TREES
    ///////////////////////////////////////////////////////////////////////////////////// 


    //Define the variables of the dataset
   RooRealVar muTauMt1("muTauMt1","muTauMt1",0.,120.);
   RooRealVar muTauCharge("muTauCharge","muTauCharge",-2.,2.);

   RooDataSet zttDSETOS("zttDSETOS", "ztt dataset OS", ztt, RooArgSet(muTauMt1,muTauCharge),"muTauCharge==0");
   RooDataSet zttDSETSS("zttDSETSS", "ztt dataset SS", ztt, RooArgSet(muTauMt1,muTauCharge),"muTauCharge!=0");
   RooDataHist zttHISTOS ("zttHISTOS","ztt HIST",RooArgSet(muTauMt1),zttDSETOS, 1.0);
   RooDataHist zttHISTSS ("zttHISTSS","ztt HIST",RooArgSet(muTauMt1),zttDSETSS, 1.0);
   RooHistPdf  zttPDFOS("zttPDFOS", "ztt PDF", RooArgSet(muTauMt1),zttHISTOS,0);
   RooHistPdf  zttPDFSS("zttPDFSS", "ztt PDF", RooArgSet(muTauMt1),zttHISTSS,0);
   drawPDF(zttPDFOS,muTauMt1,"ztt_os.png");
   drawPDF(zttPDFSS,muTauMt1,"ztt_ss.png");

   RooDataSet wmnDSETOS("wmnDSETOS", "wmn dataset OS", wmn, RooArgSet(muTauMt1,muTauCharge),"muTauCharge==0");
   RooDataSet wmnDSETSS("wmnDSETSS", "wmn dataset SS", wmn, RooArgSet(muTauMt1,muTauCharge),"muTauCharge!=0");
   RooDataHist wmnHISTOS ("wmnHISTOS","wmn HIST",RooArgSet(muTauMt1),wmnDSETOS, 1.0);
   RooDataHist wmnHISTSS ("wmnHISTSS","wmn HIST",RooArgSet(muTauMt1),wmnDSETSS, 1.0);
   RooHistPdf  wmnPDFOS("wmnPDFOS", "wmn PDF", RooArgSet(muTauMt1),wmnHISTOS,0);
   RooHistPdf  wmnPDFSS("wmnPDFSS", "wmn PDF", RooArgSet(muTauMt1),wmnHISTSS,0);
   drawPDF(wmnPDFOS,muTauMt1,"wmn_os.png");
   drawPDF(wmnPDFSS,muTauMt1,"wmn_ss.png");


   RooDataSet zmmDSETOS("zmmDSETOS", "zmm dataset OS", zmm, RooArgSet(muTauMt1,muTauCharge),"muTauCharge==0");
   RooDataSet zmmDSETSS("zmmDSETSS", "zmm dataset SS", zmm, RooArgSet(muTauMt1,muTauCharge),"muTauCharge!=0");
   RooDataHist zmmHISTOS ("zmmHISTOS","zmm HIST",RooArgSet(muTauMt1),zmmDSETOS, 1.0);
   RooDataHist zmmHISTSS ("zmmHISTSS","zmm HIST",RooArgSet(muTauMt1),zmmDSETSS, 1.0);
   RooHistPdf  zmmPDFOS("zmmPDFOS", "zmm PDF", RooArgSet(muTauMt1),zmmHISTOS,0);
   RooHistPdf  zmmPDFSS("zmmPDFSS", "zmm PDF", RooArgSet(muTauMt1),zmmHISTSS,0);
   drawPDF(zmmPDFOS,muTauMt1,"zmm_os.png");
   drawPDF(zmmPDFSS,muTauMt1,"zmm_ss.png");

   RooDataSet wtnDSETOS("wtnDSETOS", "wtn dataset OS", wtn, RooArgSet(muTauMt1,muTauCharge),"muTauCharge==0");
   RooDataSet wtnDSETSS("wtnDSETSS", "wtn dataset SS", wtn, RooArgSet(muTauMt1,muTauCharge),"muTauCharge!=0");
   RooDataHist wtnHISTOS ("wtnHISTOS","wtn HIST",RooArgSet(muTauMt1),wtnDSETOS, 1.0);
   RooDataHist wtnHISTSS ("wtnHISTSS","wtn HIST",RooArgSet(muTauMt1),wtnDSETSS, 1.0);
   RooHistPdf  wtnPDFOS("wtnPDFOS", "wtn PDF", RooArgSet(muTauMt1),wtnHISTOS,0);
   RooHistPdf  wtnPDFSS("wtnPDFSS", "wtn PDF", RooArgSet(muTauMt1),wtnHISTSS,0);
   drawPDF(wtnPDFOS,muTauMt1,"wtn_os.png");
   drawPDF(wtnPDFSS,muTauMt1,"wtn_ss.png");

   RooDataSet qcdDSETOS("qcdDSETOS", "qcd dataset OS", qcd, RooArgSet(muTauMt1,muTauCharge),"muTauCharge==0");
   RooDataSet qcdDSETSS("qcdDSETSS", "qcd dataset SS", qcd, RooArgSet(muTauMt1,muTauCharge),"muTauCharge!=0");
   RooDataHist qcdHISTOS ("qcdHISTOS","qcd HIST",RooArgSet(muTauMt1),qcdDSETOS, 1.0);
   RooDataHist qcdHISTSS ("qcdHISTSS","qcd HIST",RooArgSet(muTauMt1),qcdDSETSS, 1.0);
   RooHistPdf  qcdPDFOS("qcdPDFOS", "qcd PDF", RooArgSet(muTauMt1),qcdHISTOS,0);
   RooHistPdf  qcdPDFSS("qcdPDFSS", "qcd PDF", RooArgSet(muTauMt1),qcdHISTSS,0);
   drawPDF(qcdPDFOS,muTauMt1,"qcd_os.png");
   drawPDF(qcdPDFSS,muTauMt1,"qcd_ss.png");


   RooDataSet topDSETOS("topDSETOS", "top dataset OS", top, RooArgSet(muTauMt1,muTauCharge),"muTauCharge==0");
   RooDataSet topDSETSS("topDSETSS", "top dataset SS", top, RooArgSet(muTauMt1,muTauCharge),"muTauCharge!=0");
   RooDataHist topHISTOS ("topHISTOS","top HIST",RooArgSet(muTauMt1),topDSETOS, 1.0);
   RooDataHist topHISTSS ("topHISTSS","top HIST",RooArgSet(muTauMt1),topDSETSS, 1.0);
   RooHistPdf  topPDFOS("topPDFOS", "top PDF", RooArgSet(muTauMt1),topHISTOS,0);
   RooHistPdf  topPDFSS("topPDFSS", "top PDF", RooArgSet(muTauMt1),topHISTSS,0);
   drawPDF(topPDFOS,muTauMt1,"top_os.png");
   drawPDF(topPDFSS,muTauMt1,"top_ss.png");


   //Extract background from DATA




   //bOOK hISTOGRAMS
   TH1F * NOUT = new TH1F("NOUT","W OUT",200,0,800);
   TH1F * NIN = new TH1F("NIN","W IN",200,0,800);
   TH1F * PULL = new TH1F("PULL","PULL",200,-0.5,0.5);

   TH1F * WOUT = new TH1F("WOUT","W OUT",200,0,200);
   TH1F * WIN = new TH1F("WIN","W IN",200,0,200);
   TH1F * WPULL = new TH1F("WPULL","WPULL",200,-20,20);


   TH1F * SIGMA = new TH1F("SIGMA","SIGMA",100,0,100);


   //Now run pseudo experiments 
   printf("Starting pseudoexperiments\n");

   double lumi = parser.doubleValue("lumi");

   for(int i=0;i<parser.integerValue("experiments");++i)
     {
       printf("Experiment N=%d\n",i);

       //Create events according to the luminosity
       cout << "Generating Events---"<<std::endl;

       muTauCharge=0.0;
       unsigned  zttTotal = poissonFluctuation(zttWeightTot*lumi); 
       RooDataSet* newZTTOS = generateDSET(zttPDFOS,muTauMt1,muTauCharge ,(int)(zttTotal*(zttWeightOS/zttWeightTot)));
       muTauCharge=-1.0;
       RooDataSet* newZTTSS = generateDSET(zttPDFSS,muTauMt1,muTauCharge ,(int)(zttTotal*(zttWeightSS/zttWeightTot)));
       
       cout <<"ZTT OS In Core = "<<newZTTOS->reduce(corePreselection)->numEntries() <<std::endl;
       cout <<"ZTT SS In Core = "<<newZTTSS->reduce(corePreselection)->numEntries() <<std::endl;

       RooAbsData *trimmedDSET = newZTTOS->reduce(corePreselection);
       float IN = trimmedDSET->numEntries();
       delete trimmedDSET;

       muTauCharge=0.0;
       unsigned  wmnTotal = poissonFluctuation(wmnWeightTot*lumi); 
       RooDataSet* newWMNOS = generateDSET(wmnPDFOS,muTauMt1,muTauCharge ,(int)(wmnTotal*(wmnWeightOS/wmnWeightTot)));
       muTauCharge=-1.0;
       RooDataSet* newWMNSS = generateDSET(wmnPDFSS,muTauMt1,muTauCharge ,(int)(wmnTotal*(wmnWeightSS/wmnWeightTot)));
       
       cout <<"WMN OS In Core = "<<newWMNOS->reduce(corePreselection)->numEntries() <<std::endl;
       cout <<"WMN SS In Core = "<<newWMNSS->reduce(corePreselection)->numEntries() <<std::endl;


       muTauCharge=0.0;
       unsigned  wtnTotal = poissonFluctuation(wtnWeightTot*lumi); 
       RooDataSet* newWTNOS = generateDSET(wtnPDFOS,muTauMt1,muTauCharge ,(int)(wtnTotal*(wtnWeightOS/wtnWeightTot)));
       muTauCharge=-1.0;
       RooDataSet* newWTNSS = generateDSET(wtnPDFSS,muTauMt1,muTauCharge ,(int)(wtnTotal*(wtnWeightSS/wtnWeightTot)));
       
       cout <<"WTN OS In Core = "<<newWTNOS->reduce(corePreselection)->numEntries() <<std::endl;
       cout <<"WTN SS In Core = "<<newWTNSS->reduce(corePreselection)->numEntries() <<std::endl;


       muTauCharge=0.0;
       unsigned  zmmTotal = poissonFluctuation(zmmWeightTot*lumi); 
       RooDataSet* newZMMOS = generateDSET(zmmPDFOS,muTauMt1,muTauCharge ,(int)(zmmTotal*(zmmWeightOS/zmmWeightTot)));
       muTauCharge=-1.0;
       RooDataSet* newZMMSS = generateDSET(zmmPDFSS,muTauMt1,muTauCharge ,(int)(zmmTotal*(zmmWeightSS/zmmWeightTot)));
       
       cout <<"ZMM OS In Core = "<<newZMMOS->reduce(corePreselection)->numEntries() <<std::endl;
       cout <<"ZMM SS In Core = "<<newZMMSS->reduce(corePreselection)->numEntries() <<std::endl;

       muTauCharge=0.0;
       unsigned  qcdTotal = poissonFluctuation(qcdWeightTot*lumi); 
       RooDataSet* newQCDOS = generateDSET(qcdPDFOS,muTauMt1,muTauCharge ,(int)(qcdTotal*(qcdWeightOS/qcdWeightTot)));
       muTauCharge=-1.0;
       RooDataSet* newQCDSS = generateDSET(qcdPDFSS,muTauMt1,muTauCharge ,(int)(qcdTotal*(qcdWeightSS/qcdWeightTot)));
       
       cout <<"QCD OS In Core = "<<newQCDOS->reduce(corePreselection)->numEntries() <<std::endl;
       cout <<"QCD SS In Core = "<<newQCDSS->reduce(corePreselection)->numEntries() <<std::endl;

       muTauCharge=0.0;
       unsigned  topTotal = poissonFluctuation(topWeightTot*lumi); 
       RooDataSet* newTOPOS = generateDSET(topPDFOS,muTauMt1,muTauCharge ,(int)(topTotal*(topWeightOS/topWeightTot)));
       muTauCharge=-1.0;
       RooDataSet* newTOPSS = generateDSET(topPDFSS,muTauMt1,muTauCharge ,(int)(topTotal*(topWeightSS/topWeightTot)));
       
       cout <<"TOP OS In Core = "<<newTOPOS->reduce(corePreselection)->numEntries() <<std::endl;
       cout <<"TOP SS In Core = "<<newTOPSS->reduce(corePreselection)->numEntries() <<std::endl;

       newZTTOS->append(*newZTTSS);
       newZTTOS->append(*newWMNOS);
       newZTTOS->append(*newWMNSS);
       newZTTOS->append(*newWTNOS);
       newZTTOS->append(*newWTNSS);
       newZTTOS->append(*newZMMOS);
       newZTTOS->append(*newZMMSS);
       newZTTOS->append(*newQCDOS);
       newZTTOS->append(*newQCDSS);
       newZTTOS->append(*newTOPOS);
       newZTTOS->append(*newTOPSS);

	 

        TTree *copyT = (TTree*)newZTTOS->tree()->Clone();

        BkgOutput output = extractSignal(copyT, extrapFactor, extrapFactorErr,parser.doubleValue("qcdOSLS"),parser.doubleValue("qcdOSLSError"),parser.doubleValue("coreLimit"),parser.doubleValue("sidebandLimit"),parser.doubleValue("wtnFactor"));

   printf("Predicted = %f +- %f\n",output.OSSignalInCore,output.OSSignalInCoreErr);

	NIN->Fill(IN);
	NOUT->Fill(output.OSSignalInCore);
	PULL->Fill((output.OSSignalInCore-IN)/IN);
	SIGMA->Fill(output.OSSignalInCoreErr);

	WIN->Fill(newWMNOS->reduce(corePreselection)->numEntries()+newWMNSS->reduce(corePreselection)->numEntries()+newWTNOS->reduce(corePreselection)->numEntries()+newWTNSS->reduce(corePreselection)->numEntries());
	WOUT->Fill(output.OSWInCore+output.SSWInCore);
	WPULL->Fill(output.OSWInCore+output.SSWInCore-newWMNOS->reduce(corePreselection)->numEntries()-newWMNSS->reduce(corePreselection)->numEntries()-newWTNOS->reduce(corePreselection)->numEntries()-newWTNSS->reduce(corePreselection)->numEntries());
       
        delete copyT;
        delete newZTTOS;
        delete newWMNOS;
        delete newWTNOS;
        delete newZMMOS;
        delete newQCDOS;
        delete newTOPOS;
        delete newZTTSS;
        delete newWMNSS;
        delete newWTNSS;
        delete newZMMSS;
        delete newQCDSS;
        delete newTOPSS;
	 
     }


   printf("Running on DATA\n");

   BkgOutput data_output = extractSignal(data, extrapFactor, extrapFactorErr,parser.doubleValue("qcdOSLS"),parser.doubleValue("qcdOSLSError"),parser.doubleValue("coreLimit"),parser.doubleValue("sidebandLimit"),parser.doubleValue("wtnFactor"));

   printf("Signal = %f +- %f\n",data_output.OSSignalInCore,data_output.OSSignalInCoreErr);

   printf("PULL= %f +-%f\n",PULL->GetMean(),PULL->GetRMS());
   printf("W PULL= %f +-%f\n",WPULL->GetMean(),WPULL->GetRMS());

   TFile *fout = new TFile("STATISTICS.root","RECREATE");
   fout->cd();
   NIN->Write();
   NOUT->Write();
   PULL->Write();
   WIN->Write();
   WOUT->Write();
   WPULL->Write();

   SIGMA->Write();
   fout->Close();
  
   

   delete NIN;
   delete NOUT;
   delete PULL;
   delete SIGMA;

     
}


BkgOutput extractSignal(TTree* data, float extrapFactor, float extrapFactorErr,float oslsFactor,float oslsFactorErr,float coreLimit,float sidebandLimit,float wtnFactor)
{


   char sidebandPreselectionOS[200];
   char sidebandPreselectionSS[200];
   char corePreselectionOS[200];
   char corePreselectionSS[200];


   sprintf(sidebandPreselectionOS,"muTauCharge==0&&muTauMt1>%f",sidebandLimit);
   sprintf(sidebandPreselectionSS,"muTauCharge!=0&&muTauMt1>%f",sidebandLimit);
   sprintf(corePreselectionOS,"muTauCharge==0&&muTauMt1<=%f",coreLimit);
   sprintf(corePreselectionSS,"muTauCharge!=0&&muTauMt1<=%f",coreLimit);

   Long_t OS_SDB = data->GetEntries(sidebandPreselectionOS);
   Long_t SS_SDB = data->GetEntries(sidebandPreselectionSS);

   Long_t OS_CORE = data->GetEntries(corePreselectionOS);
   Long_t SS_CORE = data->GetEntries(corePreselectionSS);

   BkgOutput outputStruct;


   std::cout <<"OS_CORE="<<OS_CORE<<" SS_CORE = "<<SS_CORE<<" OS SDB = "<<OS_SDB<<" SS_SDB = " << SS_SDB <<std::endl;

   //Find  extrapolated W events in core
   outputStruct.OSWInCore=(1.+wtnFactor)*OS_SDB*extrapFactor;
   outputStruct.OSWInCoreErr=sqrt(OS_SDB*OS_SDB*extrapFactorErr*extrapFactorErr+OS_SDB*extrapFactor*extrapFactor);
   outputStruct.SSWInCore=(1.+wtnFactor)*SS_SDB*extrapFactor;
   outputStruct.SSWInCoreErr=sqrt(SS_SDB*SS_SDB*extrapFactorErr*extrapFactorErr+SS_SDB*extrapFactor*extrapFactor);


   std::cout <<"OSW_CORE="<<outputStruct.OSWInCore <<"+-"<<outputStruct.OSWInCoreErr<<std::endl;

   //subtract the W events in core from all SS events in core to find the QCD remnant
   outputStruct.SSOtherInCore = SS_CORE-outputStruct.SSWInCore;
   outputStruct.SSOtherInCoreErr = sqrt(SS_CORE+outputStruct.SSWInCoreErr*outputStruct.SSWInCoreErr);

   //Now multiply by the OSLS factor and get the OS background except W in core
   outputStruct.OSOtherInCore = outputStruct.SSOtherInCore*oslsFactor;
   outputStruct.OSOtherInCoreErr = sqrt(outputStruct.SSOtherInCore*outputStruct.SSOtherInCore*oslsFactorErr*oslsFactorErr+outputStruct.SSOtherInCoreErr*outputStruct.SSOtherInCoreErr*oslsFactor*oslsFactor);
   std::cout <<"OS_QCD="<<outputStruct.OSOtherInCore <<"+-"<<outputStruct.OSOtherInCoreErr<<std::endl;

   outputStruct.OSSignalInCore = OS_CORE-outputStruct.OSWInCore-outputStruct.OSOtherInCore;
   outputStruct.OSSignalInCoreErr = sqrt(OS_CORE+outputStruct.OSWInCoreErr*outputStruct.OSWInCoreErr+outputStruct.OSOtherInCoreErr*outputStruct.OSOtherInCoreErr);

   return outputStruct;
}

unsigned poissonFluctuation(int N)
{
  TF1 f("mypoisson","TMath::Poisson(x,[0])",0,5.*N);
  f.SetParameter(0,N);
  unsigned N2 = (unsigned)(f.GetRandom());
  return N2;
}

RooDataSet* generateDSET(const RooAbsPdf& pdf,const RooRealVar& var,const RooRealVar& charge ,int N)
{  
  //create poisson fluctuation
  RooDataSet *d = pdf.generate(RooArgSet(var),N);
  //create the sign and merge them
  RooDataSet ds("ds","ds",RooArgSet(charge)) ;
  for(int j=0;j<N;++j)
    {
      ds.add(RooArgSet(charge));
    }
  d->merge(&ds);
  return d;
}



void drawPDF(const RooHistPdf& pdf,const RooRealVar& var,const TString& fname)
{
  RooPlot * Frame = var.frame() ;
  pdf.plotOn(Frame) ;
  TCanvas *ccc = new TCanvas();
  ccc->cd();
  Frame->Draw();
  ccc->SaveAs(fname);
  Frame->Delete();

}
