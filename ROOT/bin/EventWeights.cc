#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"


int main (int argc, char* argv[]) 
{
   optutl::CommandLineParser parser ("Sets Event Weights in the ntuple");
   parser.addOption("treeName",optutl::CommandLineParser::kString,"Tree Name","eventTree");
   parser.addOption("dirName",optutl::CommandLineParser::kString,"Dir Name","muTauEventTree");
   parser.addOption("histoName",optutl::CommandLineParser::kString,"Counter Histogram Name","EventSummary");
   parser.addOption("weight",optutl::CommandLineParser::kDouble,"Weight to apply",1.0);
   parser.addOption("type",optutl::CommandLineParser::kInteger,"Type",0);
   parser.addOption("branch",optutl::CommandLineParser::kString,"Branch","__WEIGHT__");


   parser.parseArguments (argc, argv);

   std::string dirName = parser.stringValue("dirName");
 
   TFile f(parser.stringValue("outputFile").c_str(),"update");
   TTree *t = (TTree*)f.Get((dirName+"/"+parser.stringValue("treeName")).c_str());
   TH1F* evC  = (TH1F*)f.Get(parser.stringValue("histoName").c_str());

   float ev = evC->GetBinContent(1);
   printf("Found  %f Events Counted\n",ev);

   float weight;
   int type;
   TBranch *newBranch = t->Branch(parser.stringValue("branch").c_str(),&weight,(parser.stringValue("branch")+"/F").c_str());
   TBranch *typeBranch = t->Branch("TYPE",&type,"TYPE/I");

  for(Int_t i=0;i<t->GetEntries();++i)
    {
      t->GetEntry(i);
      weight = parser.doubleValue("weight")/(ev);
      type = parser.integerValue("type");

      newBranch->Fill();
      typeBranch->Fill();
    }

  f.cd();
  f.cd(dirName.c_str());
  t->Write("",TObject::kOverwrite);

  //OK Now the counting histo
  //  evC->Sumw2();
  //  evC->Scale(parser.doubleValue("weight")/ev);
  //  f.cd();
  //  f.cd("summary");
  //  evC->Write("results",TObject::kOverwrite);

  f.Close();

} 
