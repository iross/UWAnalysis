#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"


int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("treeName",optutl::CommandLineParser::kString,"Tree Name","eventTree");
   parser.addOption("dirName",optutl::CommandLineParser::kString,"Dir Name","muTauEventTree");
   parser.addOption("histoFile",optutl::CommandLineParser::kString,"HistogramFile","");
   parser.addOption("histoName",optutl::CommandLineParser::kString,"Ref Histogram Name","");
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__PU__");
   parser.addOption("srcBranch",optutl::CommandLineParser::kString,"srcBranch","PVs");


   parser.parseArguments (argc, argv);

   std::string dirName = parser.stringValue("dirName");
   std::string histoFile = parser.stringValue("histoFile");

   TFile hf(histoFile.c_str());
   TH1F* wHisto  = (TH1F*)hf.Get(parser.stringValue("histoName").c_str());
   TFile f(parser.stringValue("outputFile").c_str(),"update");
   TTree *t = (TTree*)f.Get((dirName+"/"+parser.stringValue("treeName")).c_str());
   float weight=0.;
   TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
  
   int src=0.;
   t->SetBranchAddress(parser.stringValue("srcBranch").c_str(),&src);

  for(Int_t i=0;i<t->GetEntries();++i)
    {
      t->GetEntry(i);
      Int_t binN =wHisto->GetXaxis()->FindBin(src);
      if(binN==0) weight=0;
      if(binN==wHisto->GetNbinsX()) weight=0;

      weight = wHisto->GetBinContent(binN);
      newBranch->Fill();

    }

  f.cd();
  f.cd(dirName.c_str());
  t->Write("",TObject::kOverwrite);

  f.Close();
  hf.Close();
} 
