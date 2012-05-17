
#include "UWAnalysis/StatTools/interface/DataCardCreator.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 


int main (int argc, char* argv[]) 
{




   optutl::CommandLineParser parser ("Background subtrcation ");

   //Input Files-------------------
   parser.addOption("channel",optutl::CommandLineParser::kString,"Channel  ","mutau");
   parser.addOption("shifts",optutl::CommandLineParser::kStringVector,"Systematic Shifts(Supported Tau,Jet,Unc and whatever else in the tree) ");
   parser.addOption("dataFile",optutl::CommandLineParser::kString,"File with the data","DATA.root");
   parser.addOption("zttFile",optutl::CommandLineParser::kString,"File with the ZTT","ZTT.root");
   parser.addOption("zEmbeddedSample",optutl::CommandLineParser::kString,"File with the ZTT+2jets","");
   parser.addOption("wThreeJetsFile",optutl::CommandLineParser::kString,"File with the W+3jets","");
   parser.addOption("zllFile",optutl::CommandLineParser::kString,"File with the ZLL","ZLL.root");
   parser.addOption("wFile",optutl::CommandLineParser::kString,"File with the W","W.root");
   parser.addOption("vvFile",optutl::CommandLineParser::kString,"File with the VV","VV.root");
   parser.addOption("topFile",optutl::CommandLineParser::kString,"File with the TOP","TOP.root");
   parser.addOption("preselection",optutl::CommandLineParser::kString,"preselection","");
   parser.addOption("osSignalSelection",optutl::CommandLineParser::kString,"OS Signal ");
   parser.addOption("ssSignalSelection",optutl::CommandLineParser::kString,"SS Signal ");
   parser.addOption("osWSelection",optutl::CommandLineParser::kString,"OS W sideband defintion ");
   parser.addOption("ssWSelection",optutl::CommandLineParser::kString,"SS W sideband definition ");
   parser.addOption("qcdSelection",optutl::CommandLineParser::kString,"QCD Shape definition");
   parser.addOption("relaxedSelection",optutl::CommandLineParser::kString,"Relaxed Selection");
   parser.addOption("bSelection",optutl::CommandLineParser::kString,"Btagging Requirement for MSSM ","(nJetsBTag3Pt20>0&&nJetsPt30<2)");
   parser.addOption("antibSelection",optutl::CommandLineParser::kString,"Anti Btagging requirement for MSSM","(nJetsBTag3Pt20==0&&nJetsPt30<2)");
   parser.addOption("vbfSelection0",optutl::CommandLineParser::kString,"SM Category 0 ","((nJetsPt30==0)||(nJetsPt30==1&&highestJetPt<150)))");
   parser.addOption("vbfSelection1",optutl::CommandLineParser::kString,"SM category 1","(nJetsPt30==1&&highestJetPt>150)");
   parser.addOption("vbfSelection2",optutl::CommandLineParser::kString,"SM Category 2","(nJetsPt30>=2&&vbfDEta>4&&vbfMass>400&&vbfNJetsGap30==0)");
   parser.addOption("vbfSelection3",optutl::CommandLineParser::kString,"SM Category 3","(nJetsPt30==2&&mJJ>70&&mJJ<120&&ptJJ>150)");
   parser.addOption("luminosity",optutl::CommandLineParser::kDouble,"Luminosity",189.);
   parser.addOption("luminosityErr",optutl::CommandLineParser::kDouble,"LuminosityErr",0.04);
   parser.addOption("variable",optutl::CommandLineParser::kString,"Shape variable ","mass");
   parser.addOption("weight",optutl::CommandLineParser::kString,"Weight for MC (Multiply Weight Factors here for efficiencies)","__WEIGHT__");
   parser.addOption("min",optutl::CommandLineParser::kDouble,"Minimum value",0.);
   parser.addOption("max",optutl::CommandLineParser::kDouble,"Maximum Value ",500.);
   parser.addOption("bins",optutl::CommandLineParser::kInteger,"Number of Bins",50);
   parser.addOption("binningHighStat",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");
   parser.addOption("binningLowStat",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");
   //   parser.addOption("binningVBF",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");
   //   parser.addOption("binningBoost",optutl::CommandLineParser::kDoubleVector,"Define Custom Variable Binning");
   parser.addOption("topErr",optutl::CommandLineParser::kDouble,"TTBar Relative Error",0.075);
   parser.addOption("vvErr",optutl::CommandLineParser::kDouble,"DiBoson RelativeError",0.3);   
   parser.addOption("zLFTErr",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",0.25);
   parser.addOption("zLFTFactor",optutl::CommandLineParser::kDouble,"Z Muon fakes tau error",1.06);
   parser.addOption("zJFTErr",optutl::CommandLineParser::kDouble,"Z Jet fakes tau Error",0.2);
   parser.addOption("zttScale",optutl::CommandLineParser::kDouble,"Z tau tau scale",1.003);
   parser.addOption("zttScaleErr",optutl::CommandLineParser::kDouble,"Z tau tau scale error",0.033);
   parser.addOption("muID",optutl::CommandLineParser::kDouble,"Mu ID",1.0);
   parser.addOption("muIDErr",optutl::CommandLineParser::kDouble,"MuIDErr",0.02);
   parser.addOption("bID",optutl::CommandLineParser::kDouble,"B ID",0.94);
   parser.addOption("bIDErr",optutl::CommandLineParser::kDouble,"BIDErr",0.10);
   parser.addOption("bmisID",optutl::CommandLineParser::kDouble,"B MISID",1.21);
   parser.addOption("bmisIDErr",optutl::CommandLineParser::kDouble,"BMISIDErr",0.17);
   parser.addOption("eleID",optutl::CommandLineParser::kDouble,"Ele ID",0.0);
   parser.addOption("eleIDErr",optutl::CommandLineParser::kDouble,"Ele IDErr",0.00);
   parser.addOption("tauID",optutl::CommandLineParser::kDouble,"Tau ID",1.0);
   parser.addOption("tauIDErr",optutl::CommandLineParser::kDouble,"Tau IDErr",0.06);
   parser.addOption("qcdFactor",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio",1.06);
   parser.addOption("qcdFactorErr",optutl::CommandLineParser::kDouble,"qcs OSLS Ratio Error",0.02);
   parser.addOption("wFactorErr",optutl::CommandLineParser::kDouble,"W factor error ",0.06);
   parser.addOption("bFactorZ",optutl::CommandLineParser::kDouble,"B factor Z",0.941);
   parser.addOption("bFactorW",optutl::CommandLineParser::kDouble,"B Factor W",0.941);
   parser.addOption("bFactorZErr",optutl::CommandLineParser::kDouble,"Probability of Z +1 b Error",0.011);
   parser.addOption("bFactorWErr",optutl::CommandLineParser::kDouble,"Probability of W+ 1 b Error",0.05);
   parser.addOption("vbfFactorZ",optutl::CommandLineParser::kDouble,"VBF factor for Z",1.);
   parser.addOption("vbfFactorW",optutl::CommandLineParser::kDouble,"VBF Factor for W",1.);
   parser.addOption("vbfFactorZErr",optutl::CommandLineParser::kDouble,"VBF factor for Z Error",0.1);
   parser.addOption("vbfFactorWErr",optutl::CommandLineParser::kDouble,"VBF factor for WError",0.1);
   parser.addOption("boostFactorZ",optutl::CommandLineParser::kDouble,"Boost factor for Z",1.);
   parser.addOption("boostFactorW",optutl::CommandLineParser::kDouble,"Boost Factor for W",1.);
   parser.addOption("boostFactorZErr",optutl::CommandLineParser::kDouble,"Boost factor for ZErr",0.15);
   parser.addOption("boostFactorWErr",optutl::CommandLineParser::kDouble,"Boost  factor for W Error",0.15);
   parser.addOption("vhFactorZ",optutl::CommandLineParser::kDouble,"VH factor for Z",0.93);
   parser.addOption("vhFactorW",optutl::CommandLineParser::kDouble,"VH Factor for W",0.93);
   parser.addOption("vhFactorZErr",optutl::CommandLineParser::kDouble,"VH factor for ZErr",0.01);
   parser.addOption("vhFactorWErr",optutl::CommandLineParser::kDouble,"VH  factor for W Error",0.01);

   parser.addOption("dir",optutl::CommandLineParser::kString,"dir","../inputs/mutau");
   parser.addOption("bitmask",optutl::CommandLineParser::kIntegerVector,"Choose what to run");
   parser.addOption("scaleUp",optutl::CommandLineParser::kDouble,"scale up for extrapolation to higher lumi",1.0);

   parser.parseArguments (argc, argv);
   std::vector<int> bitmask = parser.integerVector("bitMask");
   DataCardCreator creator(parser);

   printf("Binning HighSTat has %d entries ,LowStat has %d entries\n",(int)parser.doubleVector("binningHighStat").size(),(int)parser.doubleVector("binningLowStat").size());



   if(parser.stringValue("channel")!="eleMu") {

     //Inclusive
     //setHighStat Binning
     creator.setBinning(parser.doubleVector("binningHighStat"));
     
     printf("INCLUSIVE-------------------------------------\n");
     BkgOutput output = creator.runOSLSMT(parser.stringValue("preselection"),"_X",parser.stringValue("zEmbeddedSample"));
     creator.makeHiggsShapesAll(parser.stringValue("preselection"),"_X");
     if(bitmask[0]==1)
       creator.makeMSSMLTauDataCard(output,"_X");
     
     
     
     
     if(bitmask[1]==1) {
       //No BTagging
       printf("NO BTAGGING-------------------------------------\n");
       BkgOutput outputNoB = creator.runMinimalExtrapolation(parser.stringValue("preselection"),parser.stringValue("antibSelection"),"_NoB",
							     1.,
							     0.0,
							     1./parser.doubleValue("bID"),
							     parser.doubleValue("bIDErr")/parser.doubleValue("bID"),
							     output,							     
							     parser.stringValue("zEmbeddedSample")
       );
       creator.makeHiggsShapesNoBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("antibSelection"),"_NoB");
       creator.makeMSSMLTauDataCardNoBTag(outputNoB,"_NoB");
       
       
       //B Tagging
       creator.setBinning(parser.doubleVector("binningLowStat"));
       printf("BTAGGING-------------------------------------\n");
       BkgOutput outputB = creator.runFullExtrapolation(parser.stringValue("preselection"),parser.stringValue("bSelection"),"_B",output,
						    parser.doubleValue("bFactorZ"),
						    parser.doubleValue("bFactorZErr"),
						    parser.doubleValue("bFactorW"),
						    parser.doubleValue("bFactorWErr"),
						    parser.doubleValue("bID"),
						    parser.doubleValue("bIDErr"),
						    parser.stringValue("zEmbeddedSample")
						    );
       creator.makeHiggsShapesBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("bSelection"),"_B");
       creator.makeMSSMLTauDataCardBTagged(outputB,"_B");
     }
     
     if(bitmask[2]==1) {
       creator.setBinning(parser.doubleVector("binningHighStat"));
       printf("SM Category 0-------------------------------------\n");
       BkgOutput outputSM0 = creator.runMinimalExtrapolation(parser.stringValue("preselection"),parser.stringValue("vbfSelection0"),"_SM0",1.0,0.0,1.0,0.0,output,parser.stringValue("zEmbeddedSample"));


       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection0"),"_SM0");
       creator.makeSMLTauDataCardNoVBF(outputSM0,"_SM0");
       
       creator.setBinning(parser.doubleVector("binningLowStat"));
       printf("SM category 1 -------------------------------------\n");
       BkgOutput outputSM1 = creator.runFullExtrapolation(parser.stringValue("preselection"),parser.stringValue("vbfSelection1"),"_SM1",output,
						    parser.doubleValue("boostFactorZ"),
						      parser.doubleValue("boostFactorZErr"),
						      parser.doubleValue("boostFactorW"),
						      parser.doubleValue("boostFactorWErr"),
						      1.0,0.0,
						      parser.stringValue("zEmbeddedSample")
						      );
       
       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection1"),"_SM1");
       creator.makeSMLTauDataCardBoost(outputSM1,"_SM1");
       

       printf("SM category 2-------------------------------------\n");
       creator.setBinning(parser.doubleVector("binningLowStat"));
       
       BkgOutput outputSM2 = creator.runFullExtrapolation(parser.stringValue("preselection"),parser.stringValue("vbfSelection2"),"_SM2",output,
						      parser.doubleValue("vbfFactorZ"),
						      parser.doubleValue("vbfFactorZErr"),
						      parser.doubleValue("vbfFactorW"),
						      parser.doubleValue("vbfFactorWErr"),
						      1.0,0.0,
						      parser.stringValue("zEmbeddedSample"),
						      parser.stringValue("wThreeJetsFile")
						      
						      );
       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection2"),"_SM2");
       creator.makeSMLTauDataCardVBF(outputSM2,"_SM2");




       printf("SM category 3-------------------------------------\n");
       creator.setBinning(parser.doubleVector("binningLowStat"));
       
       BkgOutput outputSM3 = creator.runFullExtrapolation(parser.stringValue("preselection"),parser.stringValue("vbfSelection3"),"_SM3",output,
						      parser.doubleValue("vhFactorZ"),
						      parser.doubleValue("vhFactorZErr"),
						      parser.doubleValue("vhFactorW"),
						      parser.doubleValue("vhFactorWErr"),
						      1.0,0.0,
						      parser.stringValue("zEmbeddedSample"),
						      parser.stringValue("wThreeJetsFile")
						      );
       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection3"),"_SM3");
       creator.makeSMLTauDataCardVH(outputSM3,"_SM3");



     }
     

     if(bitmask.size()<4||bitmask[3]==1) {
       creator.setBinning(parser.doubleVector("binningHighStat"));
       printf("Z -> tau tau cross section-------------------------------------\n");
       BkgOutput outputZTT = creator.runOSLSMT(parser.stringValue("preselection"),"_ZTT",parser.stringValue("zEmbeddedSample"));
       creator.makeZTTLTauDataCard(output,"_ZTT");
     }

   }

   else { ///////////////////////E+MU
     //Inclusive
     //setHighStat Binning
     creator.setBinning(parser.doubleVector("binningHighStat"));
     
     printf("INCLUSIVE-------------------------------------\n");
     BkgOutput output = creator.runABCD(parser.stringValue("preselection"),parser.stringValue("preselection"),"_X",1.0,0.0,1.0,0.0,parser.stringValue("zEmbeddedSample"));
     creator.makeHiggsShapesAll(parser.stringValue("preselection"),"_X");
     if(bitmask[0]==1)
       creator.makeMSSMEMuDataCard(output,"_X");
     
     
     if(bitmask[1]==1) {
       //No BTagging
       printf("NO BTAGGING-------------------------------------\n");
       BkgOutput outputNoB = creator.runABCD(parser.stringValue("preselection"),parser.stringValue("antibSelection"),"_NoB",
					     1.,
					     parser.doubleValue("bFactorZErr")/parser.doubleValue("bFactorZ"),
					     1.,
					     0.0//,
					     //					     parser.stringValue("zEmbeddedSample")
					     );
       creator.makeHiggsShapesNoBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("antibSelection"),"_NoB");
       creator.makeMSSMEMuDataCardNoBTag(outputNoB,"_NoB");
       
       
       //B Tagging
       creator.setBinning(parser.doubleVector("binningLowStat"));
       printf("BTAGGING-------------------------------------\n");
       BkgOutput outputB = creator.runABCD(parser.stringValue("preselection"),parser.stringValue("bSelection"),"_B",
					   parser.doubleValue("bFactorZ"),
					   parser.doubleValue("bFactorZErr"),
					   parser.doubleValue("bID"),
					   parser.doubleValue("bIDErr")//,
					   //					   parser.stringValue("zEmbeddedSample")
					   );
       creator.makeHiggsShapesBTag(parser.stringValue("preselection")+"&&"+parser.stringValue("bSelection"),"_B");
       creator.makeMSSMEMuDataCardBTagged(outputB,"_B");
     }
     
     if(bitmask[2]==1) {
       creator.setBinning(parser.doubleVector("binningHighStat"));
       printf("SM Category 0-------------------------------------\n");
       BkgOutput outputSM0 = creator.runABCD(parser.stringValue("preselection"),parser.stringValue("vbfSelection0"),"_SM0",1.0,0.0,1.0,0.0);
       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection0"),"_SM0");
       creator.makeSMEMuDataCardNoVBF(outputSM0,"_SM0");
       
       creator.setBinning(parser.doubleVector("binningLowStat"));
       printf("SM category 1 -------------------------------------\n");
       BkgOutput outputSM1 = creator.runABCD(parser.stringValue("preselection"),parser.stringValue("vbfSelection1"),"_SM1",
					     parser.doubleValue("boostFactorZ"),
					     parser.doubleValue("boostFactorZErr"),
					     1.0,0.0,
					     parser.stringValue("zEmbeddedSample")
					     );
       
       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection1"),"_SM1");
       creator.makeSMEMuDataCardBoost(outputSM1,"_SM1");
       

       printf("SM category 2-------------------------------------\n");
       creator.setBinning(parser.doubleVector("binningLowStat"));
       
       BkgOutput outputSM2 = creator.runABCD(parser.stringValue("preselection"),parser.stringValue("vbfSelection2"),"_SM2",
					     parser.doubleValue("vbfFactorZ"),
					     parser.doubleValue("vbfFactorZErr"),
					     1.0,0.0,
					     parser.stringValue("zEmbeddedSample") 
					     );
       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection2"),"_SM2");
       creator.makeSMEMuDataCardVBF(outputSM2,"_SM2");



       printf("SM category 3-------------------------------------\n");
       creator.setBinning(parser.doubleVector("binningLowStat"));
       
       BkgOutput outputSM3 = creator.runABCD(parser.stringValue("preselection"),parser.stringValue("vbfSelection3"),"_SM3",
					     parser.doubleValue("vhFactorZ"),
					     parser.doubleValue("vhFactorZErr"),
					     1.0,0.0,
					     parser.stringValue("zEmbeddedSample") 
					     );
       creator.makeHiggsShapesSM(parser.stringValue("preselection")+"&&"+parser.stringValue("vbfSelection3"),"_SM3");
       creator.makeSMEMuDataCardVH(outputSM3,"_SM3");


     }


//      if(bitmask.size()<4||bitmask[3]==1) {
//        creator.setBinning(parser.doubleVector("binningHighStat"));
//        printf("Z -> tau tau cross section-------------------------------------\n");
//        BkgOutput outputZTT = creator.runOSLSMT(parser.stringValue("preselection"),"_ZTT",1.0,0.0,1.0,0.0);
//        creator.makeZTTLTauDataCard(output,"_ZTT");
//      }

   }


   //   creator.printSignalEfficiency();

     creator.close();
}

