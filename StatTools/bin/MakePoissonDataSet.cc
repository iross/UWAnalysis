#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TStyle.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCategory.h"




int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);

   optutl::CommandLineParser parser ("Creates a RooDataSet From a Histogram");

   //Data
   parser.addOption("name",optutl::CommandLineParser::kString,"Name of the dataset");
   parser.addOption("counts",optutl::CommandLineParser::kDoubleVector,"Counts");

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   TFile *fout = TFile::Open(parser.stringValue("outputFile").c_str() ,"UPDATE");
   //Define the workspace
   RooWorkspace *w = (RooWorkspace*)fout->Get("w");
   std::vector<double> counts = parser.doubleVector("counts");
 

   RooArgSet variables("variables");

   //create the variables
   for(unsigned int i=0;i<counts.size();++i) {
     w->factory(TString::Format("N_%d[%f,0.,100000.]",i,counts[i]));
     variables.add(*w->var(TString::Format("N_%d",i)));
   }

   RooDataSet  *data = new RooDataSet(parser.stringValue("name").c_str(),"data",variables);
    data->add(variables);
    w->defineSet("variables",variables);
    w->import(*data);
    fout->cd(); 
    w->Write("w",TObject::kOverwrite);

 }

