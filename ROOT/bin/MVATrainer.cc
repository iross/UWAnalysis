#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include <math.h>
#include "TMVA/Factory.h"
#include "TMVA/Tools.h"


int main (int argc, char* argv[]) 
{

  gROOT->SetBatch(kTRUE);
  gROOT->SetStyle("Plain");


   optutl::CommandLineParser parser ("Trains MVA methods");


   //Background Template Invariant mass
   parser.addOption("variables",optutl::CommandLineParser::kStringVector,"Variables");
   parser.addOption("treeName",optutl::CommandLineParser::kString,"treeName");
   parser.addOption("signalFiles",optutl::CommandLineParser::kStringVector,"signalFiles");
   parser.addOption("backgroundFiles",optutl::CommandLineParser::kStringVector,"backgroundFiles");
   parser.addOption("preselection",optutl::CommandLineParser::kString,"preselection");

   parser.parseArguments (argc, argv);


   std::vector<std::string> variables = parser.stringVector("variables");
   std::vector<std::string> signalFiles = parser.stringVector("signalFiles");
   std::vector<std::string> backgroundFiles = parser.stringVector("backgroundFiles");

   TFile * fout =TFile::Open(parser.stringValue("outputFile").c_str(),"RECREATE");
   fout->cd();
   using namespace TMVA;
   Factory * factory = new TMVA::Factory("TMVAFactory",fout,"!V:!Silent:Transformations=I;D;P;G:AnalysisType=multiclass");

   //add variables
   for(unsigned int i=0;i<variables.size();++i) {
     TString varName(variables.at(i).c_str()); 
     factory->AddVariable(varName);
   }
   //add trees we will use democratic treatment 
   //so book the minimum entries


   for(unsigned int i=0;i<signalFiles.size();++i) {
     TFile *f = new TFile(signalFiles.at(i).c_str());
     TTree *t = (TTree*)f->Get(parser.stringValue("treeName").c_str());
     fout->cd();
     TTree *tN =t->CopyTree(parser.stringValue("preselection").c_str()); 
     factory->AddTree(tN,"signal");
     f->Close();
   }

   for(unsigned int i=0;i<backgroundFiles.size();++i) {
     TFile *f = new TFile(backgroundFiles.at(i).c_str());
     TTree *t = (TTree*)f->Get(parser.stringValue("treeName").c_str());
     fout->cd();
     TTree *tN =t->CopyTree(parser.stringValue("preselection").c_str()); 
     factory->AddTree(tN,TString::Format("bkg%d",i));
     f->Close();
   }
   
   //prepare training data
   factory->PrepareTrainingAndTestTree("","","nTrain_Signal=0:nTrain_Background=0:SplitMode=Random:NormMode=NumEvents:!V");
   
   //book methods
   
   //Likelihood
   factory->BookMethod( TMVA::Types::kLikelihood, "Likelihood",
			"H:!V:TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmoothBkg[1]=10:NSmooth=1:NAvEvtPerBin=50" ); 
   
   //Decorrelated Likelihood
//    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodD",
// 			"!H:!V:!TransformOutput:PDFInterpol=Spline2:NSmoothSig[0]=20:NSmoothBkg[0]=20:NSmooth=5:NAvEvtPerBin=50:VarTransform=Decorrelate" ); 
//    //KEys likelihood
//    factory->BookMethod( TMVA::Types::kLikelihood, "LikelihoodKDE",
// 			"!H:!V:!TransformOutput:PDFInterpol=KDE:KDEtype=Gauss:KDEiter=Adaptive:KDEFineFactor=0.3:KDEborder=None:NAvEvtPerBin=50" ); 
   //Neural Network      
//    factory->BookMethod( TMVA::Types::kMLP, "MLP", "H:!V:NeuronType=tanh:VarTransform=N:NCycles=600:HiddenLayers=N+5:TestRate=5:!UseRegulator" );
   

   //Boosted decision tree
    factory->BookMethod( TMVA::Types::kBDT, "BDTG",
 			"!H:!V:NTrees=400:nEventsMin=400:MaxDepth=3:BoostType=Grad:Shrinkage=0.1:UseBaggedGrad:GradBaggingFunction=0.50:nCuts=20:NNodesMax=8" );


   // Train MVAs using the set of training events
   factory->TrainAllMethods();

   // ---- Evaluate all MVAs using the set of test events
   factory->TestAllMethods();

   // ----- Evaluate and compare performance of all configured MVAs
   factory->EvaluateAllMethods();

   fout->Close();


}

