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
   parser.addOption("preFix",optutl::CommandLineParser::kString,"Shift preFix","");
   parser.addOption("channel",optutl::CommandLineParser::kString,"channel","");
   parser.addOption("coeffPostFix",optutl::CommandLineParser::kString,"Coefficient Post","Scale");
   parser.addOption("shifts",optutl::CommandLineParser::kStringVector,"Shifts i.e. Tau, Electron etc");
   parser.addOption("quadraticMorph",optutl::CommandLineParser::kDouble,"Quadratic Morph factor",1.0);

   //Parse Arguments!
   parser.parseArguments (argc, argv);


   typedef std::vector<std::string> StringVector;
   
   std::string inputFile       = parser.stringValue("inputFile");
   std::string prefix          = parser.stringValue("preFix");
   std::string channel         = parser.stringValue("channel");

   std::string coeffPostFix    = parser.stringValue("coeffPostFix");
   StringVector shifts = parser.stringVector("shifts");
   double qmorph = parser.doubleValue("quadraticMorph");

   RooArgSet pdfList;
   RooArgSet coeffs;

   //Open The file
   printf("Reading nominal file\n");
   TFile *f = TFile::Open(inputFile.c_str(),"UPDATE");
   RooWorkspace *w = (RooWorkspace*)f->Get("w");

   //Add the unshifted
   RooAbsPdf *pdf =  w->pdf((prefix+"_"+channel).c_str());
   pdfList.add(*pdf);

   for( unsigned int i=0;i<shifts.size();++i) {
     printf("processing shift %s\n ", shifts[i].c_str());
     RooAbsPdf *pdfU =  w->pdf((prefix+shifts[i]+"Up_"+channel).c_str());
     pdfList.add(*pdfU);
     RooAbsPdf *pdfD =  w->pdf((prefix+shifts[i]+"Down_"+channel).c_str());
     pdfList.add(*pdfD);
     //create a coefficient
     printf("creating coefficient %s\n",(shifts[i]+coeffPostFix).c_str() );
     if(w->var((shifts[i]+coeffPostFix).c_str())==0) 
       w->factory(TString::Format("%s[0.,-3.,3.]",(shifts[i]+coeffPostFix).c_str()));
     coeffs.add(*w->var((shifts[i]+coeffPostFix).c_str()));
   }
   printf("creating interpolated PDF\n");
   //create morphed PDF
   std::string pdfName = prefix+"Morph_"+channel;
   VerticalInterpPdf *morph = new VerticalInterpPdf(pdfName.c_str(), pdfName.c_str(), pdfList, coeffs, qmorph);
   w->import(*morph);
   printf("saving interpolated PDF\n");

   f->cd(); 
   w->Write("w",TObject::kOverwrite);
   f->Close();

}

