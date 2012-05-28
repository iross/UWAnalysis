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
   parser.addOption("resultsFile",optutl::CommandLineParser::kString,"Results File","fitResults.root");
   parser.addOption("model",optutl::CommandLineParser::kString,"Model","");
   parser.addOption("parameter",optutl::CommandLineParser::kString,"ParameterToPlot","mass");
   parser.addOption("channel",optutl::CommandLineParser::kString,"Channel","");
   parser.addOption("data",optutl::CommandLineParser::kString,"data","");
   parser.addOption("pdf",optutl::CommandLineParser::kString,"pdf","");
   parser.addOption("snapShot",optutl::CommandLineParser::kString,"SnapShot","");
   parser.addOption("category",optutl::CommandLineParser::kString,"Category","");
   parser.addOption("name",optutl::CommandLineParser::kString,"Name","fitResult");
   parser.addOption("slice",optutl::CommandLineParser::kString,"Slice","");

   parser.addOption("varTitle",optutl::CommandLineParser::kString,"variable title","visible Mass");
   parser.addOption("varUnit",optutl::CommandLineParser::kString,"variable unit","GeV/c^{2}");

   parser.addOption("components",optutl::CommandLineParser::kStringVector,"Components");
   parser.addOption("componentLabels",optutl::CommandLineParser::kStringVector,"ComponentLabels");
   parser.addOption("fillcolors",optutl::CommandLineParser::kIntegerVector,"Fill Colors");
   parser.addOption("linecolors",optutl::CommandLineParser::kIntegerVector,"Line Colors");

   parser.addOption("bins",optutl::CommandLineParser::kInteger,"bins",30);
   parser.addOption("min",optutl::CommandLineParser::kDouble,"min",0.);
   parser.addOption("max",optutl::CommandLineParser::kDouble,"max",300.);

   //Parse Arguments!
   parser.parseArguments (argc, argv);

   std::string resultsFile = parser.stringValue("resultsFile");
   std::string model       = parser.stringValue("model");
   std::string name        = parser.stringValue("name");
   std::string channel     = parser.stringValue("channel");
   std::string parameter   = parser.stringValue("parameter");
   std::string snapShot    = parser.stringValue("snapShot");
   std::string category    = parser.stringValue("category");
   std::string slice       = parser.stringValue("slice");
   std::vector<std::string>  components= parser.stringVector("components");
   std::vector<std::string>  componentLabels= parser.stringVector("componentLabels");
   std::vector<int>  fillColors= parser.integerVector("fillColors");
   std::vector<int>  lineColors= parser.integerVector("lineColors");

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

