#include "UWAnalysis/StatTools/interface/DataCardCreator.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 





int main (int argc, char* argv[]) 
{




   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------
   parser.addOption("channel",optutl::CommandLineParser::kString,"Channel","mutau");
   parser.addOption("shifts",optutl::CommandLineParser::kStringVector,"shifts");
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   parser.addOption("zttFile",optutl::CommandLineParser::kString,"File with the ZTT","ZTT.root");
   parser.addOption("zllFile",optutl::CommandLineParser::kString,"File with the ZLL","ZLL.root");
   parser.addOption("wFile",optutl::CommandLineParser::kString,"File with the W","W.root");
   parser.addOption("vvFile",optutl::CommandLineParser::kString,"File with the VV","VV.root");
   parser.addOption("topFile",optutl::CommandLineParser::kString,"File with the TOP","TOP.root");
   parser.addOption("preselection",optutl::CommandLineParser::kString,"preselection","");
   parser.addOption("osSignalSelection",optutl::CommandLineParser::kString,"OS Signal ");
   parser.addOption("ssSignalSelection",optutl::CommandLineParser::kString,"SS Signal ");
   parser.addOption("osWSelection",optutl::CommandLineParser::kString,"OS Signal ");
   parser.addOption("ssWSelection",optutl::CommandLineParser::kString,"SS Signal ");
   parser.addOption("zLFTSelection",optutl::CommandLineParser::kString,"ZLFT Selection");
   parser.addOption("zJFTSelection",optutl::CommandLineParser::kString,"ZJFT Selection");
   parser.addOption("qcdSelection",optutl::CommandLineParser::kString,"QCD Selection");
   parser.addOption("bSelection",optutl::CommandLineParser::kString,"bSelection","(nJetsBTag3Pt20>0&&nJetsPt30<2)");
   parser.addOption("antibSelection",optutl::CommandLineParser::kString,"antibSelection","(nJetsBTag3Pt20==0&&nJetsPt30<2)");
   parser.addOption("vbfSelection0",optutl::CommandLineParser::kString,"vbfSelection0","(nJetsPt30==0)");
   parser.addOption("vbfSelection1",optutl::CommandLineParser::kString,"vbfSelection1","(nJetsPt30==1&&met>20&&pt>20)");
   parser.addOption("vbfSelection2",optutl::CommandLineParser::kString,"vbfSelection2","(nJetsPt30==2&&vbfDEta>3.5&&vbfMass>350)");
   parser.addOption("luminosity",optutl::CommandLineParser::kDouble,"Luminosity",189.);
   parser.addOption("luminosityErr",optutl::CommandLineParser::kDouble,"LuminosityErr",0.04);
   parser.addOption("variable",optutl::CommandLineParser::kString,"variable","mass");
   parser.addOption("weight",optutl::CommandLineParser::kString,"weigth","__WEIGHT__");
   parser.addOption("min",optutl::CommandLineParser::kDouble,"min",0.);
   parser.addOption("max",optutl::CommandLineParser::kDouble,"max",500.);
   parser.addOption("bins",optutl::CommandLineParser::kInteger,"bins",25);
   parser.addOption("binning",optutl::CommandLineParser::kDoubleVector,"binning");
   parser.addOption("topErr",optutl::CommandLineParser::kDouble,"TTBar Relative Error",0.5);
   parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson RelativeError",0.5);   
   parser.addOption("zLFTErr",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",0.5);
   parser.addOption("zJFTErr",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.5);
   parser.addOption("zttScale",optutl::CommandLineParser::kDouble,"Z tau tau scale",0.5);
   parser.addOption("zttScaleErr",optutl::CommandLineParser::kDouble,"Z tau tau scale error",0.5);
   parser.addOption("muID",optutl::CommandLineParser::kDouble,"Mu ID",0.5);
   parser.addOption("muIDErr",optutl::CommandLineParser::kDouble,"MuIDErr",0.5);
   parser.addOption("bID",optutl::CommandLineParser::kDouble,"B ID",0.5);
   parser.addOption("bIDErr",optutl::CommandLineParser::kDouble,"BIDErr",0.5);
   parser.addOption("bmisID",optutl::CommandLineParser::kDouble,"B MISID",0.5);
   parser.addOption("bmisIDErr",optutl::CommandLineParser::kDouble,"BMISIDErr",0.5);
   parser.addOption("bjecErr",optutl::CommandLineParser::kDouble,"BJecErr",0.5);
   parser.addOption("vbfJecErr",optutl::CommandLineParser::kDouble,"vbfJecErr",0.05);
   parser.addOption("vbfErr",optutl::CommandLineParser::kDouble,"vbfErr",0.1);
   parser.addOption("eleID",optutl::CommandLineParser::kDouble,"Ele ID",0.5);
   parser.addOption("eleIDErr",optutl::CommandLineParser::kDouble,"Ele IDErr",0.5);
   parser.addOption("tauID",optutl::CommandLineParser::kDouble,"Tau ID",0.5);
   parser.addOption("tauIDErr",optutl::CommandLineParser::kDouble,"Tau IDErr",0.5);
   parser.addOption("tauHLT",optutl::CommandLineParser::kDouble,"Tau ID",0.5);
   parser.addOption("tauHLTErr",optutl::CommandLineParser::kDouble,"Tau IDErr",0.5);
   parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.06);
   parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.02);
   parser.addOption("wFactorErr",optutl::CommandLineParser::kDouble,"W factor error ",0.00);
   parser.addOption("bFactor1",optutl::CommandLineParser::kDouble,"B factor 1 jet",0.00821);
   parser.addOption("bFactor2",optutl::CommandLineParser::kDouble,"B Factor 2 jets",0.016);
   parser.addOption("bFactorErr1",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.00035);
   parser.addOption("bFactorErr2",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.001);
   parser.addOption("vbfFactor1",optutl::CommandLineParser::kDouble,"B factor 1 jet",0.00123);
   parser.addOption("vbfFactor2",optutl::CommandLineParser::kDouble,"B Factor 2 jets",0.004);
   parser.addOption("vbfFactorErr1",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.00013);
   parser.addOption("vbfFactorErr2",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.00040);
   parser.addOption("dir",optutl::CommandLineParser::kString,"dir","../inputs/mutau");
   parser.addOption("abcdCoeffs",optutl::CommandLineParser::kStringVector,"abcdCoeffs");
   parser.addOption("bitmask",optutl::CommandLineParser::kIntegerVector,"bitmask");

   parser.parseArguments (argc, argv);

   std::vector<int> bitmask = parser.integerVector("bitMask");

   DataCardCreator creator(parser);

   if(parser.stringVector("abcdCoeffs").size()==0) { //Do L+tau

     //Inclusive

     printf("INCLUSIVE-------------------------------------\n");
     BkgOutput output = creator.runInclusive(parser.stringValue("preselection"),"_X");

     creator.makeHiggsShapes(parser.stringValue("preselection"),"_X");

     if(bitmask[0]==1)
       creator.makeMSSMLTauDataCard(output,"_X");



     if(bitmask[1]==1) {

     //No BTagging
       printf("NO BTAGGING-------------------------------------\n");

     BkgOutput outputNoB = creator.runInclusive(parser.stringValue("preselection")+"&&"+parser.stringValue("antibSelection"),"_NoB");

     creator.makeHiggsShapesNoBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("antibSelection"),"_NoB");
     creator.makeMSSMLTauDataCardNoBTag(outputNoB,"_NoB");
     
     
     //B Tagging
     printf("BTAGGING-------------------------------------\n");

     BkgOutput outputB = creator.runBTag(output,parser.stringValue("preselection")+"&&"+parser.stringValue("bSelection"),"_X","_B");

     creator.makeHiggsShapesBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("bSelection"),"_B");
     creator.makeMSSMLTauDataCardBTagged(outputB,"_B");
     }


     if(bitmask[2]==1) {
//      //VBF 0
       printf("VBF0-------------------------------------\n");

      BkgOutput outputVBF0 = creator.runInclusive(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection0"),"_SM0");

      creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection0"),"_SM0");
      creator.makeSMLTauDataCardNoVBF(outputVBF0,"_SM0");

//      //VBF
      printf("VBF1-------------------------------------\n");
 
      BkgOutput outputVBF1 = creator.runInclusive(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection1"),"_SM1");

      creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection1"),"_SM1");
      creator.makeSMLTauDataCardNoVBF(outputVBF1,"_SM1");


//      //VBF
      printf("VBF2-------------------------------------\n");

      BkgOutput outputVBF2 = creator.runVBF(output,parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection2"),"_X","_SM2");
      creator.makeHiggsShapesVBF(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection2"),"_SM2");
      creator.makeSMLTauDataCardVBF(outputVBF2,"_SM2");
     }

   }
   else {



     //Inclusive
     printf("INCLUSIVE------------------------------------------------------\n");
     BkgOutput output = creator.runEMu(parser.stringValue("preselection"),"_X");
     creator.makeHiggsShapes(parser.stringValue("preselection"),"_X");
     if(bitmask[0]==1)
       creator.makeMSSMEMuDataCard(output,"_X");

     if(bitmask[1]==1) {

     //No BTagging
     printf("NO BTAG------------------------------------------------------\n");

     BkgOutput outputNoB = creator.runEMu(parser.stringValue("preselection")+"&&"+parser.stringValue("antibSelection"),"_NoB");

     creator.makeHiggsShapesNoBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("antibSelection"),"_NoB");
     creator.makeMSSMEMuDataCardNoBTag(outputNoB,"_NoB");
     
     //B Tagging
     printf("BTAG------------------------------------------------------\n");


     BkgOutput outputB = creator.runEMuBTagged(output,parser.stringValue("preselection"),parser.stringValue("bSelection"),"_X","_B");
     creator.makeHiggsShapesBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("bSelection"),"_B");
     creator.makeMSSMEMuDataCardBTagged(outputB,"_B");
     }

     if(bitmask[2]==1) {
     //No VBF
     printf("SM0------------------------------------------------------\n");

     BkgOutput outputVBF0 = creator.runEMu(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection0"),"_SM0");
      creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection0"),"_SM0");
     creator.makeSMEMuDataCardNoVBF(outputVBF0,"_SM0");

     printf("SM1------------------------------------------------------\n");

     BkgOutput outputVBF1 = creator.runEMu(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection1"),"_SM1");
      creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection1"),"_SM1");
     creator.makeSMEMuDataCardNoVBF(outputVBF1,"_SM1");

     printf("SM2------------------------------------------------------\n");

     BkgOutput outputVBF2 = creator.runEMuVBF(output,parser.stringValue("preselection"),parser.stringValue("vbfSelection2"),"_X","_SM2");
      creator.makeHiggsShapesVBF(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection2"),"_SM2");
      creator.makeSMEMuDataCardVBF(outputVBF2,"_SM2");
     }
     creator.close();

   }
}

