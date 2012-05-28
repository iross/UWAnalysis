#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 

#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TF1.h"
#include "TGraph.h"
#include "TMath.h"
#include "sstream"


void fillHistogram(std::string file,std::string tree,std::string selection,std::string weight,double factor,TH1F* h);
double chi2(TH1F* signal, TH1F* background,TH1F* data);
unsigned poissonFluctuation(int N);

int main (int argc, char* argv[]) 
{

  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Calculates Cross section");

   //Input Files-------------------

   //Data
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   parser.addOption("mcFiles",optutl::CommandLineParser::kStringVector,"Files with the MC");
   parser.addOption("weights",optutl::CommandLineParser::kStringVector,"weights");
   parser.addOption("lumi",optutl::CommandLineParser::kString,"Luminosity","21.9");
   parser.addOption("dir",optutl::CommandLineParser::kString,"Dir","muTauEventTree");
   parser.addOption("tree",optutl::CommandLineParser::kString,"Tree","eventTree");
   parser.addOption("scaleFactorMin",optutl::CommandLineParser::kDouble,"scaleFactorMin",0.9);
   parser.addOption("scaleFactorMax",optutl::CommandLineParser::kDouble,"scaleFactorMax",1.1);
   parser.addOption("scaleFactorStep",optutl::CommandLineParser::kDouble,"scaleFactorStep",0.01);
   parser.addOption("selection",optutl::CommandLineParser::kString,"preselection","muTauPt1>15&&muTauPt2>15");
   parser.addOption("minMass",optutl::CommandLineParser::kDouble,"minMass",35.);
   parser.addOption("maxMass",optutl::CommandLineParser::kDouble,"maxMass",80.);
   parser.addOption("bins",optutl::CommandLineParser::kInteger,"bins",9);
   parser.addOption("experiments",optutl::CommandLineParser::kInteger,"experiments",100);

   //Parse Arguments!
   parser.parseArguments (argc, argv);


   std::string lumi = parser.stringValue("lumi");

     

   TFile *fout = new TFile("energyScale.root","RECREATE");
   fout->cd();
   TGraph *Chi2 = new TGraph();
   Chi2->SetName("Chi2");

   TGraph *Kolmogorov = new TGraph();
   Kolmogorov->SetName("Kolmogorov");


   int POINT=0;

     std::vector<std::string> mcFiles = parser.stringVector("mcFiles");
     std::vector<std::string> mcWeights = parser.stringVector("weights");


     //Get Teh data
       TH1F * data = new TH1F("data","DATA Histogram",parser.integerValue("bins"),parser.doubleValue("minMass"),parser.doubleValue("maxMass"));
       fillHistogram(parser.stringValue("dataFile"),parser.stringValue("dir")+"/"+parser.stringValue("tree"),parser.stringValue("selection"),"1",1.0,data);

       //First Run the default
     for(double eScale = parser.doubleValue("scaleFactorMin");eScale<=parser.doubleValue("scaleFactorMax");eScale+=parser.doubleValue("scaleFactorStep")) {
       TH1F * mc = new TH1F("mc","MC",parser.integerValue("bins"),parser.doubleValue("minMass"),parser.doubleValue("maxMass"));
       mc->Sumw2();
       for(unsigned int i=0;i<mcFiles.size();++i) {
	 fillHistogram(mcFiles.at(i),parser.stringValue("dir")+"/"+parser.stringValue("tree"),parser.stringValue("selection"),lumi+"*("+mcWeights.at(i)+")",eScale,mc);
       }
       //GetKolmogorov Test and Chi2 test
       double chi2_result = data->Chi2Test(mc,"UW");
       double kolmogorov_result = data->KolmogorovTest(mc);
       Chi2->SetPoint(POINT,eScale,chi2_result);
       Kolmogorov->SetPoint(POINT,eScale,kolmogorov_result);
       POINT++;

       fout->cd();
       mc->Write(TString::Format("mass_%f",eScale));

       delete mc;
      
     }



     fout->cd();
     Chi2->Write();
     Kolmogorov->Write();


     ////Now perform pseudoexperiments
     TH1F *kolmogorovStatistics = new TH1F("kolStats","Kolmogorov Statistics",20, parser.doubleValue("scaleFactorMin"),parser.doubleValue("scaleFactorMax"));
     TH1F *chiStatistics = new TH1F("chiStats","Chi2 Statistics",20, parser.doubleValue("scaleFactorMin"),parser.doubleValue("scaleFactorMax"));
     for( int i=0;i<parser.integerValue("experiments");++i) {
       printf("Experiment %d is starting\n",i); 
       double maxp_K=0.0;
       double maxp_C=0.0;
       double maxe_K=0.0;
       double maxe_C=0.0;

       TH1F * fluctuatedData = new TH1F("fluctuatedData","MC",parser.integerValue("bins"),parser.doubleValue("minMass"),parser.doubleValue("maxMass"));
       //     unsigned fluctuation = poissonFluctuation(int(data->Integral()));
       fluctuatedData->FillRandom(data,(int)(data->Integral()));       
       printf("Original entries =%f Generated Entries=%f\n",data->Integral(),fluctuatedData->Integral());

       for(double eScale = parser.doubleValue("scaleFactorMin");eScale<=parser.doubleValue("scaleFactorMax");eScale+=parser.doubleValue("scaleFactorStep")) {
	 TH1F * mc = new TH1F("mc","MC",parser.integerValue("bins"),parser.doubleValue("minMass"),parser.doubleValue("maxMass"));
	 mc->Sumw2();
	 for(unsigned int i=0;i<mcFiles.size();++i) {
	   fillHistogram(mcFiles.at(i),parser.stringValue("dir")+"/"+parser.stringValue("tree"),parser.stringValue("selection"),lumi+"*("+mcWeights.at(i)+")",eScale,mc);
	 }
       //GetKolmogorov Test and Chi2 test
       double chi2_result = fluctuatedData->Chi2Test(mc,"UW");
       double kolmogorov_result = fluctuatedData->KolmogorovTest(mc);
       if(chi2_result>maxp_C) {maxp_C = chi2_result; maxe_C = eScale;}
      if(kolmogorov_result>maxp_K) {maxp_K = kolmogorov_result; maxe_K = eScale;}

       delete mc;
       }

       kolmogorovStatistics->Fill(maxe_K);
       chiStatistics->Fill(maxe_C);
       delete fluctuatedData;
     }


     fout->cd();
     kolmogorovStatistics->Write();
     chiStatistics->Write();

     delete data;


     fout->Close();

     



}




void fillHistogram(std::string file,std::string tree,std::string selection,std::string weight,double fctr,TH1F* h)
{
  TFile *f = new TFile(file.c_str());
  TTree *t =(TTree*)f->Get(tree.c_str());
  TH1F *tmp = new TH1F("tmp","tmp",h->GetNbinsX(),h->GetXaxis()->GetXmin(),h->GetXaxis()->GetXmax());
  tmp->Sumw2();

  std::ostringstream str;
  str << fctr;
  std::string factor = str.str();

  std::string formulaE1 = "(TMath::Sqrt(muTauPx1*muTauPx1+muTauPy1*muTauPy1+muTauPz1*muTauPz1+0.104*0.104))";
  std::string formulaE2 = "(TMath::Sqrt("+factor+"*"+factor+"*(muTauPx2*muTauPx2+muTauPy2*muTauPy2+muTauPz2*muTauPz2)+muTauHadMass*muTauHadMass))";

  std::string formula2="-(muTauPx1+"+factor+"*muTauPx2)*(muTauPx1+"+factor+"*muTauPx2)-(muTauPy1+"+factor+"*muTauPy2)*(muTauPy1+"+factor+"*muTauPy2)-(muTauPz1+"+factor+"*muTauPz2)*(muTauPz1+"+factor+"*muTauPz2)";

  std::string formulaSq= "("+formulaE1+"+"+formulaE2+")*("+formulaE1+"+"+formulaE2+")"+formula2;
  std::string formula="TMath::Sqrt("+formulaSq+")>>tmp";

  //  printf("formula=%s\n",formula.c_str());
 
  t->Draw(formula.c_str(),(weight+"*("+selection+")").c_str());
  h->Add(tmp);
  tmp->Delete();

  f->Close();
}  



unsigned poissonFluctuation(int N)
{
  TF1 f("mypoisson","TMath::Poisson(x,[0])",0,5.*N);
  f.SetParameter(0,N);
  unsigned N2 = (unsigned)(f.GetRandom());
  return N2;
}
