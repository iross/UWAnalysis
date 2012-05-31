#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "RooWorkspace.h"
#include "RooDataSet.h"
#include "RooRealVar.h"
#include "RooCategory.h"
#include <RooStats/ProfileLikelihoodCalculator.h>
#include <RooStats/LikelihoodInterval.h>
#include <RooStats/LikelihoodIntervalPlot.h>
#include <RooStats/HLFactory.h>
#include <RooStats/HypoTestResult.h>
#include <Math/MinimizerOptions.h>
#include "HiggsAnalysis/CombinedLimit/interface/VerticalInterpPdf.h"

#include "UWAnalysis/StatTools/interface/plotter.h"


int main (int argc, char* argv[]) 
{
  using namespace RooFit;
  gROOT->SetBatch(kTRUE);

   optutl::CommandLineParser parser ("Performs Fit Plot");

   //Data
   parser.addOption("file",optutl::CommandLineParser::kString,"Results File","fitResults.root");
   parser.addOption("snapshot",optutl::CommandLineParser::kString,"Snapshot","");
   parser.addOption("components",optutl::CommandLineParser::kStringVector,"Components");
   parser.addOption("names",optutl::CommandLineParser::kStringVector,"names");
   parser.addOption("observable",optutl::CommandLineParser::kString,"observable");

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   std::string resultsFile = parser.stringValue("resultsFile");
   std::string snapShot    = parser.stringValue("snapshot");
   std::vector<std::string>  components= parser.stringVector("components");
   std::vector<std::string>  names= parser.stringVector("names");

   int   bins    = parser.integerValue("bins");
   float min     = parser.doubleValue("min");
   float max     = parser.doubleValue("max");


   //load the workspace
   TFile * fin = TFile::Open(resultsFile.c_str());
   RooWorkspace *w  =(RooWorkspace*) fin ->Get("w");

   //load snapShot
   if(snapShot.size()>0)
     w->loadSnapshot(snapShot.c_str());
   
   //create a plotter
   plotter * myPlotter = new plotter(w,channel,model,parameter,category,parser.stringValue("pdf"),parser.stringValue("data"));

   //assign the components
   for(unsigned int i=0;i<components.size();++i) {
     std::string c = components[i];
     std::string cc = componentLabels[i];
     replace(c.begin(),c.end(),'|',',');
     replace(cc.begin(),cc.end(),'|','#');
      myPlotter->addComponent(cc,c,fillColors.at(i),lineColors.at(i));
   }

   //cosmetics
   myPlotter->setCosmetics(parser.stringValue("varTitle"),parser.stringValue("varUnit"));
     printf("creating plot\n");

   //make the plot
   RooPlot *plot = myPlotter->producePlot(slice,bins,min,max);


   TCanvas *c = new TCanvas("c");
   c->cd();
   plot->Draw();
   c->SaveAs(("plots/"+name+".png").c_str());
   c->SaveAs(("plots/"+name+".pdf").c_str());
   c->SaveAs(("plots/"+name+".cxx").c_str());
   c->SaveAs(("plots/"+name+".root").c_str());
   c->SetLogy();
   c->SaveAs(("plots/"+name+"LOG.png").c_str());
   c->SaveAs(("plots/"+name+"LOG.pdf").c_str());
   c->SaveAs(("plots/"+name+"LOG.cxx").c_str());
   c->SaveAs(("plots/"+name+"LOG.root").c_str());


   delete plot;
   delete c;
   fin->Close();
   delete myPlotter;
}

