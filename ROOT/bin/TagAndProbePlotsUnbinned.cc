#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 

#include "RooRealVar.h"
#include "RooVoigtian.h"
#include "RooPolynomial.h"
#include "RooKeysPdf.h"
#include "RooChebychev.h"
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
#include "RooNumConvPdf.h"
#include "RooMinuit.h"
#include "RooFitResult.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "TH1.h"
#include "TF1.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"



void setTDRStyle() {
  TStyle *tdrStyle = new TStyle("tdrStyle","Style for P-TDR");

// For the canvas:
  tdrStyle->SetCanvasBorderMode(0);
  tdrStyle->SetCanvasColor(kWhite);
  tdrStyle->SetCanvasDefH(300); //Height of canvas
  tdrStyle->SetCanvasDefW(350); //Width of canvas
  tdrStyle->SetCanvasDefX(0);   //POsition on screen
  tdrStyle->SetCanvasDefY(0);

// For the Pad:
  tdrStyle->SetPadBorderMode(0);
  // tdrStyle->SetPadBorderSize(Width_t size = 1);
  tdrStyle->SetPadColor(kWhite);
  tdrStyle->SetPadGridX(false);
  tdrStyle->SetPadGridY(false);
  tdrStyle->SetGridColor(0);
  tdrStyle->SetGridStyle(3);
  tdrStyle->SetGridWidth(1);

// For the frame:
  tdrStyle->SetFrameBorderMode(0);
  tdrStyle->SetFrameBorderSize(1);
  tdrStyle->SetFrameFillColor(0);
  tdrStyle->SetFrameFillStyle(0);
  tdrStyle->SetFrameLineColor(1);
  tdrStyle->SetFrameLineStyle(1);
  tdrStyle->SetFrameLineWidth(1);

// For the histo:
  // tdrStyle->SetHistFillColor(1);
  // tdrStyle->SetHistFillStyle(0);
  tdrStyle->SetHistLineColor(1);
  tdrStyle->SetHistLineStyle(0);
  tdrStyle->SetHistLineWidth(1);
  // tdrStyle->SetLegoInnerR(Float_t rad = 0.5);
  // tdrStyle->SetNumberContours(Int_t number = 20);

  tdrStyle->SetEndErrorSize(2);
  //tdrStyle->SetErrorMarker(20);
  tdrStyle->SetErrorX(0.);
  
  tdrStyle->SetMarkerStyle(20);

//For the fit/function:
  tdrStyle->SetOptFit(1);
  tdrStyle->SetFitFormat("5.4g");
  tdrStyle->SetFuncColor(2);
  tdrStyle->SetFuncStyle(1);
  tdrStyle->SetFuncWidth(1);

//For the date:
  tdrStyle->SetOptDate(0);
  // tdrStyle->SetDateX(Float_t x = 0.01);
  // tdrStyle->SetDateY(Float_t y = 0.01);

// For the statistics box:
  tdrStyle->SetOptFile(0);
  tdrStyle->SetOptStat(0); // To display the mean and RMS:   SetOptStat("mr");
  tdrStyle->SetStatColor(kWhite);
  tdrStyle->SetStatFont(42);
  tdrStyle->SetStatFontSize(0.025);
  tdrStyle->SetStatTextColor(1);
  tdrStyle->SetStatFormat("6.4g");
  tdrStyle->SetStatBorderSize(1);
  tdrStyle->SetStatH(0.1);
  tdrStyle->SetStatW(0.15);
  // tdrStyle->SetStatStyle(Style_t style = 1001);
  // tdrStyle->SetStatX(Float_t x = 0);
  // tdrStyle->SetStatY(Float_t y = 0);

// Margins:
  tdrStyle->SetPadTopMargin(0.1);
  tdrStyle->SetPadBottomMargin(0.13);
  tdrStyle->SetPadLeftMargin(0.16);
  tdrStyle->SetPadRightMargin(0.02);

// For the Global title:

  tdrStyle->SetOptTitle(1);
  tdrStyle->SetTitleFont(42);
  tdrStyle->SetTitleColor(1);
  tdrStyle->SetTitleTextColor(1);
  tdrStyle->SetTitleFillColor(10);
  tdrStyle->SetTitleFontSize(0.05);
  // tdrStyle->SetTitleH(0); // Set the height of the title box
  // tdrStyle->SetTitleW(0); // Set the width of the title box
  // tdrStyle->SetTitleX(0); // Set the position of the title box
  // tdrStyle->SetTitleY(0.985); // Set the position of the title box
  // tdrStyle->SetTitleStyle(Style_t style = 1001);
  // tdrStyle->SetTitleBorderSize(2);

// For the axis titles:

  tdrStyle->SetTitleColor(1, "XYZ");
  tdrStyle->SetTitleFont(42, "XYZ");
  tdrStyle->SetTitleSize(0.06, "XYZ");
  // tdrStyle->SetTitleXSize(Float_t size = 0.02); // Another way to set the size?
  // tdrStyle->SetTitleYSize(Float_t size = 0.02);
  tdrStyle->SetTitleXOffset(0.9);
  tdrStyle->SetTitleYOffset(1.25);
  // tdrStyle->SetTitleOffset(1.1, "Y"); // Another way to set the Offset

// For the axis labels:

  tdrStyle->SetLabelColor(1, "XYZ");
  tdrStyle->SetLabelFont(42, "XYZ");
  tdrStyle->SetLabelOffset(0.007, "XYZ");
  tdrStyle->SetLabelSize(0.05, "XYZ");

// For the axis:

  tdrStyle->SetAxisColor(1, "XYZ");
  tdrStyle->SetStripDecimals(kTRUE);
  tdrStyle->SetTickLength(0.03, "XYZ");
  tdrStyle->SetNdivisions(510, "XYZ");
  tdrStyle->SetPadTickX(1);  // To get tick marks on the opposite side of the frame
  tdrStyle->SetPadTickY(1);

// Change for log plots:
  tdrStyle->SetOptLogx(0);
  tdrStyle->SetOptLogy(0);
  tdrStyle->SetOptLogz(0);

// Postscript options:
  tdrStyle->SetPaperSize(20.,20.);
  // tdrStyle->SetLineScalePS(Float_t scale = 3);
  // tdrStyle->SetLineStyleString(Int_t i, const char* text);
  // tdrStyle->SetHeaderPS(const char* header);
  // tdrStyle->SetTitlePS(const char* pstitle);

  // tdrStyle->SetBarOffset(Float_t baroff = 0.5);
  // tdrStyle->SetBarWidth(Float_t barwidth = 0.5);
  // tdrStyle->SetPaintTextFormat(const char* format = "g");
   tdrStyle->SetPalette(1,0);
  // tdrStyle->SetTimeOffset(Double_t toffset);
  // tdrStyle->SetHistMinimumZero(kTRUE);

  tdrStyle->cd();

}


struct fitResult {
  double pass;
  double passError;
  double fail;
  double failError;
  double efficiency;
  double efficiencyError;
};



RooDataSet createDataSet(RooWorkspace *w,const std::string& prefix,const std::string& file,const std::string& treeDir,const std::string& weightString,const std::string& cut);
fitResult fit(RooWorkspace*,RooDataSet* );
fitResult fitMC(RooWorkspace*,RooDataSet* );
void createWorspace(RooWorkspace *w,const std::string& signalFile,const std::string& treeDir, const std::string& prefix, int constrainBackground,const std::string& cut);




int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);

  //  gROOT->SetStyle("Plain");
  setTDRStyle();
  
   optutl::CommandLineParser parser ("Calculates Cross section");

   //Input Files-------------------

   //Data
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   parser.addOption("signalFile",optutl::CommandLineParser::kString,"File with the signal","ZMM.root");
   parser.addOption("mcFile",optutl::CommandLineParser::kString,"File with the MC","MC.root");
   //DATA MC (for comparison)

   parser.addOption("dir",optutl::CommandLineParser::kString,"Directory","tagAndProbeMuonTagAndProbe");
   parser.addOption("mcDir",optutl::CommandLineParser::kString,"MC Directory","tagAndProbeMuonTagAndProbe");
   parser.addOption("prefix",optutl::CommandLineParser::kString,"Histogram Prefix","");
   parser.addOption("cut",optutl::CommandLineParser::kString,"Cut","");


   parser.addOption("constrainBackground",optutl::CommandLineParser::kInteger,"constrain Background to 0",1);

   //Parse Arguments!
   parser.parseArguments (argc, argv);
   std::string prefix =parser.stringValue("prefix"); 

   
   printf("FIXME!!!!\n");
   return 0;

   //Define the workspace
   RooWorkspace *w = new RooWorkspace("w","workspace");
   createWorspace(w,parser.stringValue("signalFile"),parser.stringValue("mcDir"),prefix,parser.integerValue("constrainBackground"),parser.stringValue("cut"));


   //Get MC and DATA samples
   RooDataSet mcSample= createDataSet(w,prefix,parser.stringValue("mcFile"),parser.stringValue("mcDir"),"__WEIGHT__",parser.stringValue("cut"));
   printf("MC sample created with %d entries\n",mcSample.numEntries());


   RooDataSet dataSample=createDataSet(w,prefix,parser.stringValue("dataFile"),parser.stringValue("dir"),"",parser.stringValue("cut"));
   printf("DATA sample created with %d entries-READY TO FIT!\n",dataSample.numEntries());

   //Now perform the fit
   fitResult resultDATA   =  fit(w,&dataSample);

    //draw
    RooPlot *frameDP = w->var("mass")->frame();
    dataSample.reduce((prefix+"==1").c_str())->plotOn(frameDP);
    w->pdf("pdf1")->plotOn(frameDP);
    w->pdf("pdf1")->plotOn(frameDP,Components(*w->pdf("background1")),LineStyle(kDashed));
    TCanvas *cDP = new TCanvas("cDP","CCCC");
    frameDP->Draw();
    cDP->SaveAs("DATAPass.png");
    delete cDP;
    delete frameDP;

    RooPlot *frameDF = w->var("mass")->frame();
    dataSample.reduce((prefix+"==0").c_str())->plotOn(frameDF);
    w->pdf("pdf2")->plotOn(frameDF);
    w->pdf("pdf2")->plotOn(frameDF,Components(*w->pdf("background2")),LineStyle(kDashed));
    TCanvas *cDF = new TCanvas("cDF","CCCC");
    frameDF->Draw();
    cDF->SaveAs("DATAFail.png");
    delete cDF;
    delete frameDF;



   fitResult resultMC     =  fitMC(w,&mcSample);

//    //draw
    RooPlot *frameMP = w->var("mass")->frame();
    dataSample.reduce((prefix+"==1").c_str())->plotOn(frameMP);
    w->pdf("pdf1")->plotOn(frameMP);
    w->pdf("pdf1")->plotOn(frameMP,Components(*w->pdf("background1")),LineStyle(kDashed));
    TCanvas *cMP = new TCanvas("cMP","CCCC");
    frameMP->Draw();
    cMP->SaveAs("MCPass.png");
    delete cMP;
    delete frameMP;

    RooPlot *frameMF = w->var("mass")->frame();
    dataSample.reduce((prefix+"==0").c_str())->plotOn(frameMF);
    w->pdf("pdf2")->plotOn(frameMF);
    w->pdf("pdf2")->plotOn(frameMF,Components(*w->pdf("background2")),LineStyle(kDashed));
    TCanvas *cMF = new TCanvas("cMF","CCCC");
    frameMF->Draw();
    cMF->SaveAs("MCFail.png");
    delete cMF;
    delete frameMF;
   
   float ratio = resultDATA.efficiency/resultMC.efficiency;
   float da = resultDATA.efficiencyError;
   float db = resultMC.efficiencyError;
   float aa =resultDATA.efficiency*resultDATA.efficiency;
   float bb =resultMC.efficiency*resultMC.efficiency;
   

   printf("rho=%f +-%f\n",ratio,ratio*sqrt(da*da/aa+db*db/bb));
   
}




void createWorspace(RooWorkspace *w,const std::string& signalFile,const std::string& treeDir, const std::string& prefix, int constrainBackground,const std::string& cut) {
  using namespace RooFit;


   //Create a common variable for the invariant mass
   w->factory("mass[91,60,115]");
   w->var("mass")->setPlotLabel("l^{+} l^{-} Mass [GeV/c^{2}]");
   //create an energyScaleShift
   //   w->factory("scale[1.0,0.95,1.05]");

   
   //CREATE THE CATEGORY
   w->factory(TString::Format("%s[pass=1,fail=0]",prefix.c_str()));
   //define tthe __WEIGHT__ for MC
   w->factory("__WEIGHT__[0.5,0.,100]");

   //define the fit coefficients dependin if the pass or fail will have background  
  if(constrainBackground==1) {
    w->factory("NpassB[0.]");
    w->factory("b1[0.]");
    w->factory("b2[-0.5,-1,0.]");
    w->factory("NfailB[100,0.,20000000.]");
  }
  else if(constrainBackground==-1) {
    w->factory("NpassB[100.,0.,20000000.]");
    w->factory("b1[-0.5,-1,0.]");
    w->factory("b2[0.]");
    w->factory("NfailB[0]");
  }
  else if(constrainBackground==0) {
    w->factory("NpassB[0.]");
    w->factory("b1[-0.5,-1,0.]");
    w->factory("b2[0.]");
    w->factory("NfailB[0]");
  }
  else
    {
      w->factory("b1[-0.5,-1,0.]");
      w->factory("b2[-0.5,-1,0.]");
      w->factory("NpassB[100.,0.,20000000.]");
      w->factory("NfailB[100,0.,20000000.]");
    }

  
  //declare backgroundpdfs
  w->factory("Exponential::background1(mass,b1)");
  w->factory("Exponential::background2(mass,b2)");

  printf("Background pdfs decalred\n");

  //Create signal PDFs from Z->mumu MC

  TFile *f = new TFile(signalFile.c_str());
  TTree *t = (TTree*)f->Get((treeDir+"/tagAndProbeTree").c_str());
  TFile *ftmp = new TFile("tmp.root","RECREATE");
  ftmp->cd();
  TTree*treePass = t->CopyTree(("__WEIGHT__*("+prefix+"==1&&"+cut+")").c_str(),"",5000);
  TTree*treeFail = t->CopyTree(("__WEIGHT__*("+prefix+"==0&&"+cut+")").c_str(),"",5000);
  //  TTree*treeBoth = t->CopyTree(("__WEIGHT__*("+prefix+">=0&&"+cut+")").c_str(),"",5000);

  RooRealVar * mass = w->var("mass");
  RooDataSet dataPass("ds", "dss", treePass, RooArgSet(*mass));
  RooDataSet dataFail("dsf", "dssf", treeFail, RooArgSet(*mass));
  //  RooDataSet dataBoth("dsf", "dssf", treeBoth, RooArgSet(*mass));

  RooKeysPdf pdf1("passPDF", "Pass PDF", *mass,  dataPass,RooKeysPdf::MirrorBoth,1.0);
  RooKeysPdf pdf2("failPDF", "Fail PDF", *mass,  dataFail,RooKeysPdf::MirrorBoth,1.0);

  w->import(pdf1);
  w->import(pdf2);
  delete treePass;
  delete treeFail;
  //  delete treeBoth;
  f->Close();
  ftmp->Close();
  printf("PDFs created\n");

  RooPlot * Frame1 = w->var("mass")->frame() ;
  pdf1.plotOn(Frame1);
  TCanvas *cc = new TCanvas();
  cc->cd();
  Frame1->Draw();
  cc->SaveAs("passPdf.png");
  delete cc;
  delete Frame1;

  RooPlot * Frame2 = w->var("mass")->frame() ;
  pdf2.plotOn(Frame2);
  TCanvas *ccc = new TCanvas();
  ccc->cd();
  Frame2->Draw();
  ccc->SaveAs("failPdf.png");
  delete ccc;
  delete Frame2;



  //create the number of signal and efficiency vars
  w->factory("N[1000.,0.,20000000.]");
  w->factory("eff[0.80,0.,1.00]");
 
  //create the coefficients
  w->factory("expr::coeffPass('N*eff',N,eff)");
  w->factory("expr::coeffFail('N*(1.-eff)',N,eff)");
 

  //Now create simultanous pdf

  w->factory("SUM::pdf1(coeffPass*passPDF,NpassB*background1)");
  w->factory("SUM::pdf2(coeffFail*failPDF,NfailB*background2)");
  printf("Pass and fail PDF created\n");
  w->factory(TString::Format("SIMUL::fullPdf(%s,pass=pdf1,fail=pdf2)",prefix.c_str()));
  printf("Created Simultaneious PDF\n");

}


fitResult fit(RooWorkspace* w,  RooDataSet *data )
{ 
  using namespace RooFit;
  w->pdf("fullPdf")->fitTo(*data,SumW2Error(kFALSE));
  printf("Efficiency = %f +- %f\n",w->var("eff")->getVal(),w->var("eff")->getError());
  fitResult result;
  result.efficiency = w->var("eff")->getVal();
  result.efficiencyError = w->var("eff")->getError();
  return result;
}

fitResult fitMC(RooWorkspace* w,  RooDataSet *data )
{ 
  using namespace RooFit;
  w->pdf("fullPdf")->fitTo(*data,SumW2Error(kTRUE));
  printf("Efficiency = %f +- %f\n",w->var("eff")->getVal(),w->var("eff")->getError());
  fitResult result;
  result.efficiency = w->var("eff")->getVal();
  result.efficiencyError = w->var("eff")->getError();
  return result;
}







RooDataSet createDataSet(RooWorkspace *w,const std::string& var,const std::string& file,const std::string& treeDir,const std::string& weightString,const std::string& cut)
{
  TFile *f = new TFile(file.c_str());
  TTree *t = (TTree*)f->Get((treeDir+"/tagAndProbeTree").c_str());

  TFile* ff = new TFile("tmp.root","RECREATE");
  TTree *t2 = t->CopyTree(cut.c_str());
 

  RooCategory * varV = w->cat(var.c_str());
  RooRealVar * mass = w->var("mass");
  if(weightString.size()!=0) {
    return RooDataSet("ds", "dss", t2, RooArgSet(*w->cat(var.c_str()),*w->var("mass"),*w->var("__WEIGHT__")),0,"__WEIGHT__");

  }
  else {
    RooDataSet data("dsd", "dsd", t2, RooArgSet(*varV,*mass));
    return data;
  }

  delete t2;
  ff->Close();
}




