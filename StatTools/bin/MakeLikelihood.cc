#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 

#include "RooRealVar.h"
#include "RooKeysPdf.h"
#include "RooPlot.h"
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "HiggsAnalysis/CombinedLimit/interface/VerticalInterpPdf.h"


void createWorspace(RooWorkspace *w,const std::string& signalFile,const std::string& treeDir, const std::string& prefix, int constrainBackground,const std::string& cut);




int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);

   optutl::CommandLineParser parser ("Creates a Morphed PDF from a set of shifted PDFs ");

   //Input Files-------------------

   //Data
   parser.addOption("inputFile",optutl::CommandLineParser::kString,"Input file","diTau.root");
   parser.addOption("inputPdfs",optutl::CommandLineParser::kStringVector,"inputPdfs");
   parser.addOption("name",optutl::CommandLineParser::kString,"name");

   //Parse Arguments!
   parser.parseArguments (argc, argv);


   typedef std::vector<std::string> StringVector;
   
   std::string inputFile          = parser.stringValue("inputFile");
   std::string name               = parser.stringValue("name");
   std::vector<std::string> pdfs  = parser.stringVector("inputPdfs");

   RooArgSet pdfList;
   RooArgSet coeffs;

   //Open The file
   printf("Reading nominal file\n");
   TFile *f = TFile::Open(inputFile.c_str(),"UPDATE");
   RooWorkspace *w = (RooWorkspace*)f->Get("w");

   TString outStr = TString::Format("PROD::%s(",name.c_str());
   for(unsigned int i=0;i<pdfs.size();++i)
     if(i==pdfs.size()-1) 
       outStr+=TString::Format("%s)",pdfs.at(i).c_str());
     else
       outStr+=TString::Format("%s,",pdfs.at(i).c_str());

   w->factory(outStr);
   w->Write("w",TObject::kOverwrite);
   f->Close();

}

