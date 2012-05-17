#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include <math.h>
#include <boost/algorithm/string.hpp>
#include "HiggsAnalysis/CombinedLimit/interface/th1fmorph.h"
#include "HiggsAnalysis/CombinedLimit/interface/TH1Keys.h"
#include <TEfficiency.h>
#include <TMath.h>
#include <iostream>
#include <string>
#include <boost/lexical_cast.hpp>


struct BkgOutput {
  float DATA;

  float W;
  float dW;

  float WF;
  float dWF;


  float WSS;
  float dWSS;
  float WSDB;

  float QCD;
  float dQCD;

  float QCDSDB;


  float ZLFT;
  float dZLFT;

  float ZJFT;
  float dZJFT;

  float ZLFTSS;
  float dZLFTSS;

  float ZJFTSS;
  float dZJFTSS;
  float TOP;
  float dTOP;

  float VV;
  float dVV;

  float ZTT;
  float dZTT;


  float WCORR;
  float dWCORR;

  float WSSCORR;
  float dWSSCORR;

  float ZTTCORR;
  float dZTTCORR;


};



class DataCardCreator {
 public:

  DataCardCreator(optutl::CommandLineParser parser) {
    channel_ = parser.stringValue("channel");
    shifts_  = parser.stringVector("shifts");


    //create the name you need to add to the hisdtograms 
    //in the root file 
    for(unsigned int i=0;i<shifts_.size();++i) {
      std::string shiftL = shifts_.at(i);
      shiftL.resize(1);
      boost::to_lower(shiftL);
      shiftsPostFix_.push_back("CMS_scale_"+shiftL);
    }
      

    //read input files
    zttFile_ = parser.stringValue("zttFile");
    zllFile_ = parser.stringValue("zllFile");
    wFile_ = parser.stringValue("wFile");
    vvFile_ = parser.stringValue("vvFile");
    topFile_ = parser.stringValue("topFile");
    dataFile_ = parser.stringValue("dataFile");


    //read control and signal regions
    preSelection_ = parser.stringValue("preSelection");
    osSignalSelection_ = parser.stringValue("osSignalSelection");
    ssSignalSelection_ = parser.stringValue("ssSignalSelection");
    osWSelection_ = parser.stringValue("osWSelection");
    ssWSelection_ = parser.stringValue("ssWSelection");
    qcdSelection_ = parser.stringValue("qcdSelection");
    relaxedSelection_ = parser.stringValue("relaxedSelection");
    bSelection_ = parser.stringValue("bSelection");
    antibSelection_ = parser.stringValue("antibSelection");
    vbfSelection0_ = parser.stringValue("vbfSelection0");
    vbfSelection1_ = parser.stringValue("vbfSelection1");
    vbfSelection2_ = parser.stringValue("vbfSelection2");


    //read systematic uncertainties 
    luminosity_ = parser.doubleValue("luminosity");
    luminosityErr_ = parser.doubleValue("luminosityErr");
    muID_ = parser.doubleValue("muID");
    muIDErr_ = parser.doubleValue("muIDErr");
    bID_ = parser.doubleValue("bID");
    bIDErr_ = parser.doubleValue("bIDErr");
    bMisID_ = parser.doubleValue("bMisID");
    bMisIDErr_ = parser.doubleValue("bMisIDErr");
    eleID_ = parser.doubleValue("eleID");
    eleIDErr_ = parser.doubleValue("eleIDErr");
    tauID_ = parser.doubleValue("tauID");
    tauIDErr_ = parser.doubleValue("tauIDErr");
    zttScale_ = parser.doubleValue("zttScale");
    zttScaleErr_ = parser.doubleValue("zttScaleErr");

    //read the basic varibale you will put in the histogram
    variable_ = parser.stringValue("variable");

    //read the event weight for MC 
    weight_ = parser.stringValue("weight");

    //define the histogram binning
    bins_ = parser.integerValue("bins");
    min_ = parser.doubleValue("min");
    max_ = parser.doubleValue("max");




    //Define background uncertainty Errors
    topErr_ = parser.doubleValue("topErr");
    vvErr_ = parser.doubleValue("vvErr");
    zlftErr_ = parser.doubleValue("zlftErr");
    zlftFactor_ = parser.doubleValue("zlftFactor");

    zjftErr_ = parser.doubleValue("zjftErr");
    wFactorErr_ = parser.doubleValue("wFactorErr");
    qcdFactor_ = parser.doubleValue("qcdFactor");
    qcdFactorErr_ = parser.doubleValue("qcdFactorErr");
    bFactorZ_ = parser.doubleValue("bFactorZ");
    bFactorZErr_ = parser.doubleValue("bFactorZErr");
    bFactorW_ = parser.doubleValue("bFactorW");
    bFactorWErr_ = parser.doubleValue("bFactorWErr");

    vbfFactorZ_ = parser.doubleValue("vbfFactorZ");
    vbfFactorZErr_ = parser.doubleValue("vbfFactorZErr");
    vbfFactorW_ = parser.doubleValue("vbfFactorW");
    vbfFactorWErr_ = parser.doubleValue("vbfFactorWErr");

    boostFactorZ_ = parser.doubleValue("boostFactorZ");
    boostFactorZErr_ = parser.doubleValue("boostFactorZErr");
    boostFactorW_ = parser.doubleValue("boostFactorW");
    boostFactorWErr_ = parser.doubleValue("boostFactorWErr");

    vhFactorZ_ = parser.doubleValue("vhFactorZ");
    vhFactorZErr_ = parser.doubleValue("vhFactorZErr");
    vhFactorW_ = parser.doubleValue("vhFactorW");
    vhFactorWErr_ = parser.doubleValue("vhFactorWErr");


    dir_ = parser.stringValue("dir");


    //predefine te masses you are going to make 
    mssmMasses_.push_back("90");
    mssmMasses_.push_back("100");
    mssmMasses_.push_back("120");
    mssmMasses_.push_back("130");
    mssmMasses_.push_back("140");
    mssmMasses_.push_back("160");
    mssmMasses_.push_back("180");
    mssmMasses_.push_back("200");
    mssmMasses_.push_back("250");
    mssmMasses_.push_back("300");
    mssmMasses_.push_back("350");
    mssmMasses_.push_back("400");
    mssmMasses_.push_back("450");
    mssmMasses_.push_back("500");
    smMasses_.push_back("110");
    smMasses_.push_back("115");
    smMasses_.push_back("120");
    smMasses_.push_back("125");
    smMasses_.push_back("130");
    smMasses_.push_back("135");
    smMasses_.push_back("140");
    smMasses_.push_back("145");


    for(unsigned int i=110;i<=145;++i)
      smMassesDC_.push_back(boost::lexical_cast<std::string>(i));



    smSigma_.push_back(1.591);
    smSigma_.push_back(1.377);
    smSigma_.push_back(1.181);
    smSigma_.push_back(0.975);
    smSigma_.push_back(0.774);
    smSigma_.push_back(0.591);
    smSigma_.push_back(0.429);
    smSigma_.push_back(0.294);


    vbfSigma_.push_back(0.112);
    vbfSigma_.push_back(0.101);
    vbfSigma_.push_back(0.090);
    vbfSigma_.push_back(0.077);
    vbfSigma_.push_back(0.063);
    vbfSigma_.push_back(0.040);
    vbfSigma_.push_back(0.037);
    vbfSigma_.push_back(0.026);



    vhSigma_.push_back(0.118);
    vhSigma_.push_back(0.0971);
    vhSigma_.push_back(0.0801);
    vhSigma_.push_back(0.0620);
    vhSigma_.push_back(0.0467);
    vhSigma_.push_back(0.0340);
    vhSigma_.push_back(0.0234);
    vhSigma_.push_back(0.0153);


    mssmBBFraction_.push_back(0.5180);
    mssmBBFraction_.push_back(0.5661);
    mssmBBFraction_.push_back(0.6481);
    mssmBBFraction_.push_back(0.6497);
    mssmBBFraction_.push_back(0.6852);
    mssmBBFraction_.push_back(0.7399);
    mssmBBFraction_.push_back(0.7779);
    mssmBBFraction_.push_back(0.8047);
    mssmBBFraction_.push_back(0.8587);
    mssmBBFraction_.push_back(0.8916);
    mssmBBFraction_.push_back(0.9108);
    mssmBBFraction_.push_back(0.9216);
    mssmBBFraction_.push_back(0.9327);
    mssmBBFraction_.push_back(0.9415);




    scaleUp_ = parser.doubleValue("scaleUp");


    fout_ = new TFile(parser.stringValue("outputfile").c_str(),"RECREATE");

  }


  void makeMSSMLTauDataCard(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<mssmMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mA"+mssmMasses_[m]+".txt").c_str(),"w");
      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+".root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGH%s        BBH%s        ZTT           QCD           W             ZJ            ZL            TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4             5             6             7\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("GGH"+mssmMasses_[m],postfix),getYield("BBH"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.W,out.ZJFT,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -             -             -             -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t    lnN   %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"CMS_eff_e    lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -             -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    fprintf(pfile,"CMS_htt_ttbarNorm  lnN      -             -             -             -             -             -             -              %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm  lnN      -             -             -             -             -             -             -              -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_WNorm lnN      -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),1+out.dW/out.W);
    fprintf(pfile,"CMS_htt_%s_ZJFTNorm  lnN      -             -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"CMS_htt_%s_ZLFTNorm  lnN      -             -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);
    fprintf(pfile,"CMS_htt_%s_QCDNorm gmN   %d   -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"CMS_htt_%s_QCDSyst lnN        -             -             -             %.3f          -             -             -              -              -      QCD Background Systematics\n",(channel_).c_str(),1.+qcdFactorErr_/qcdFactor_);

    for(unsigned int j=0;j<shifts_.size();++j)
	fprintf(pfile,"%s    shape    1             1             1             -             -             -             -              -              -      shape\n",shiftsPostFix_[j].c_str());

    fprintf(pfile,"CMS_scale_met lnN  1.05          1.05          -             -             -             -             -              1.02          1.03      MET Scale\n");
    fprintf(pfile,"CMS_scale_j   lnN  1.05          1.05          -             -             -             -             -              1.02          1.03      Jet Scale\n");


    fclose(pfile);
    }
  
 

  }



  void makeMSSMEMuDataCard(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<mssmMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mA"+mssmMasses_[m]+".txt").c_str(),"w");
      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+".root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s            %s            %s   \n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGH%s        BBH%s        ZTT         FAKES            TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4          \n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f       \n",
	     getYield("GGH"+mssmMasses_[m],postfix),getYield("BBH"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -             -             -           luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f          %.3f          %.3f          -        %.3f          %.3f          muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e    lnN   %.3f          %.3f          %.3f          -         %.3f          %.3f         Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -             -             %.3f          -             -          -         ZTT Scale  \n",1+zttScaleErr_/zttScale_);
    fprintf(pfile,"CMS_htt_ttbarNorm  lnN      -             -             -             -           %.3f     -    TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm  lnN      -             -             -             -             -     %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_FAKENorm lnN        -             -             -             %.3f          -             -       FAKE Background Systematics\n",(channel_).c_str(),1.+out.dQCD/out.QCD);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    1             1             1             -             -             -      shape\n",shiftsPostFix_[j].c_str());

    fprintf(pfile,"CMS_scale_met lnN  1.05          1.05          -             -           1.02          1.03      MET Scale\n");
    fprintf(pfile,"CMS_scale_j   lnN  1.05          1.05          -             -           1.02          1.03      Jet Scale\n");


    fclose(pfile);
    }
  }



  void makeMSSMLTauDataCardNoBTag(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<mssmMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mA"+mssmMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+".root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s             %s            %s             %s                 %s            %s            %s             %s           %s            %s              %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGHNoJet%s   GGHJet%s        BBHNoJet%s     BBHJet%s     BBHBJet%s           ZTT           QCD           W             ZJ            ZL            TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -4              -3           -2              -1            0                 1             2             3             4             5            6             7  \n");
      fprintf(pfile,"rate           %.3f            %.3f          %.3f         %.3f          %.3f             %.3f          %.3f          %.3f          %.3f          %.3f          %.3f            %.3f\n",
	      getYield("GGHNoJet"+mssmMasses_[m],postfix),getYield("GGHJet"+mssmMasses_[m],postfix),getYield("BBHNoJet"+mssmMasses_[m],postfix),getYield("BBHJet"+mssmMasses_[m],postfix),getYield("BBHBJet"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.W,out.ZJFT,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN %.3f           %.3f          %.3f           %.3f           %.3f              -             -             -             -             -             -             -          luminosity\n",
		1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f          %.3f          %.3f          %.3f           %.3f             %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	        1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t    lnN   %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"CMS_eff_e    lnN   %.3f          %.3f          %.3f          %.3f          %.3f          %.3f             -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -             -             -               -            -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
      fprintf(pfile,"CMS_htt_zttExtrap_nob  lnN   -             -             -               -            -             %.8f          -             -             -          -          -              -         ZTT Scale  \n",
	     1+out.dZTTCORR/out.ZTTCORR);

    for(unsigned int j=0;j<shifts_.size();++j)
	fprintf(pfile,"%s    shape    1.0             1.0             1.0             1.0             1.0             1.0             -             -             -             -              -              -      shape\n",shiftsPostFix_[j].c_str());


    fprintf(pfile,"CMS_htt_%s_QCDNorm gmN %d      -             -             -             -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"CMS_htt_%s_QCDSyst lnN        -             -             -             -          -                      -          %.3f        -              -              -            -           -      QCD Background Systematics\n",(channel_).c_str(),1.+qcdFactorErr_/qcdFactor_);
    fprintf(pfile,"CMS_htt_ttbarNorm  lnN      -             -            -             -              -              -             -             -             -             -              %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm  lnN      -             -             -             -             -              -             -             -             -             -              -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_WNorm   lnN        -             -             -             -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),(int)1+out.dW/out.W);
    fprintf(pfile,"CMS_htt_%s_ZJFTNorm  lnN      -            -             -             -              -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"CMS_htt_%s_ZLFTNorm  lnN      -             -            -            -               -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);

    fprintf(pfile,"CMS_eff_b      lnN      -             -             -             -             %.3f          -             -              -              -             -              %.3f           -    BTag efficiency \n",1-bIDErr_/bID_,1-bIDErr_/bID_);
    fprintf(pfile,"CMS_fake_b   lnN      -             %.3f          -             %.3f           -             -             -             -             -             -              -              -     BTag MisTag \n",1-bMisIDErr_/bMisID_,1-bMisIDErr_/bMisID_);


    fprintf(pfile,"CMS_scale_j      lnN      0.98            0.98             0.98             0.98             0.98          -             -              -            -                -             0.93              0.97      Jet Scale \n");
    fprintf(pfile,"CMS_scale_met      lnN      -             -             -             -             -          -             -              -              -             -            1.03          1.04   MET scale \n");

    fclose(pfile);
    }
  
 

  }



  void makeMSSMEMuDataCardNoBTag(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<mssmMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mA"+mssmMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+".root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s             %s            %s             %s                 %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGHNoJet%s   GGHJet%s        BBHNoJet%s     BBHJet%s     BBHBJet%s           ZTT           FAKES           TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -4              -3           -2              -1            0                 1             2             3             4\n");
      fprintf(pfile,"rate           %.3f            %.3f          %.3f         %.3f          %.3f             %.3f          %.3f          %.3f             %.3f\n",
	      getYield("GGHNoJet"+mssmMasses_[m],postfix),getYield("GGHJet"+mssmMasses_[m],postfix),getYield("BBHNoJet"+mssmMasses_[m],postfix),getYield("BBHJet"+mssmMasses_[m],postfix),getYield("BBHBJet"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN %.3f           %.3f          %.3f           %.3f           %.3f              -             -             -             -             -             -             -          luminosity\n",
		1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f          %.3f          %.3f          %.3f           %.3f             %.3f          -                 %.3f          %.3f       muon ID /HLT\n",
	        1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e    lnN   %.3f          %.3f          %.3f          %.3f          %.3f          %.3f             -             %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -             -             -               -            -             %.3f          -             -                -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_);
      fprintf(pfile,"CMS_htt_zttExtrap_nob lnN   -             -             -               -            -             %.3f          -             -                -         ZTT Scale  \n",
	     1+out.dZTTCORR/out.ZTTCORR);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    1.0             1.0             1.0             1.0             1.0             1.0            -             -           shape\n",shiftsPostFix_[j].c_str());
    fprintf(pfile,"CMS_htt_%s_FakeNorm lnN          -               -               -                -                -       -     %.3f           -              -               QCD Background Systematics\n",(channel_).c_str(),1.+qcdFactorErr_/qcdFactor_);

    fprintf(pfile,"CMS_htt_ttbarNorm  lnN      -             -            -             -              -              -             -             %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm  lnN      -             -             -             -             -              -             -             -           %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_eff_b      lnN            -             -             -             -             %.3f          -             -              %.3f           -    BTag efficiency \n",1-bIDErr_/bID_,1-bIDErr_/bID_);
    fprintf(pfile,"CMS_fake_b   lnN              -             %.3f          -             %.3f           -            -             -              -              -     BTag MisTag \n",1-bMisIDErr_/bMisID_,1-bMisIDErr_/bMisID_);



    fprintf(pfile,"CMS_scale_j      lnN      0.98            0.98             0.98             0.98             0.98          -             -                 0.93              0.97      Jet Scale \n");
    fprintf(pfile,"CMS_scale_met      lnN      -             -                -                -                 -            -             -                 1.03          1.04   MET scale \n");

    fclose(pfile);
    }
  
 

  }



  void makeZTTLTauDataCard(BkgOutput out,std::string postfix) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+".txt").c_str(),"w");
      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+".root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin             %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process         ZTT           QCD           W             ZJ            ZL            TT            VV\n");
      fprintf(pfile,"process          0             1             2             3             4             5             6\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f           %.3f\n",
	     out.ZTT,out.QCD,out.W,out.ZJFT,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN    %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t    lnN     %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e    lnN       %.3f          -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
      fprintf(pfile,"CMS_htt_ttbarNorm  lnN       -             -             -             -             -              %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
      fprintf(pfile,"CMS_htt_DiBosonNorm  lnN    -             -             -             -             -              -              %.3f   DiBoson background \n",1+out.dVV/out.VV);

    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape            1             -             -             -             -              -              -      shape\n",shiftsPostFix_[j].c_str());
    fprintf(pfile,"CMS_htt_%s_QCDNorm gmN   %d   -            %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"CMS_htt_%s_QCDSyst lnN        -             %.3f          -             -             -              -              -      QCD Background Systematics\n",(channel_).c_str(),1.+qcdFactorErr_/qcdFactor_);
    fprintf(pfile,"CMS_htt_%s_WNorm     lnN      -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),1+out.dW/out.W);
    fprintf(pfile,"CMS_htt_%s_ZJetFakeTau  lnN  -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"CMS_htt_%s_ZLeptonFakeTau  lnN -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);
    fclose(pfile);

  }




  void makeSMLTauDataCardNoVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin       %s        %s            %s            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process   VH%s     SM%s        VBF%s        ZTT           QCD           W             ZJ            ZL            TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process   -2     -1            0             1             2             3             4             5             6             7\n");
      fprintf(pfile,"rate      %.3f     %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	      getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.W,out.ZJFT,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN    %.3f        %.3f          %.3f          -             -             -             -             -             -             -          luminosity\n",
		1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);      
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f     %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
		1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t    lnN    %.3f      %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
		1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"CMS_eff_e    lnN      %.3f       %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	      1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -         -             -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
      fprintf(pfile,"CMS_htt_zttExtrap_sm0 lnN   -         -             -             %.8f          -             -           -          -          -              -         ZTT Extrapolation  \n",
	     1+out.dZTTCORR/out.ZTTCORR);
    fprintf(pfile,"CMS_htt_ttbarNorm      lnN    -       -             -             -             -             -             -             -              %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm     lnN  -           -             -             -             -             -             -             -              -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_WNorm       lnN      -        -             -             -             -             %.3f          -             -              -              -      W Background \n",channel_.c_str(),1+out.dW/out.W);
    fprintf(pfile,"CMS_htt_%s_QCDNorm gmN     %d   -        -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"CMS_htt_%s_QCDSyst lnN          -       -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),1+qcdFactorErr_/qcdFactor_);
    fprintf(pfile,"CMS_htt_%s_ZJetFakeTau lnN      -        -             -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"CMS_htt_%s_ZLeptonFakeTau   lnN  -        -             -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);

       for(unsigned int j=0;j<shifts_.size();++j)
	     fprintf(pfile,"%s    shape    1             1             1             1             -             -             -             -              -             -   -      shape\n",shiftsPostFix_[j].c_str());

    fprintf(pfile,"CMS_scale_j           lnN  0.96        0.99          0.92          -            -              -        -         -          0.94            0.97    Jet scale\n");
    fprintf(pfile,"CMS_scale_met           lnN  1.05        1.05          1.05          -            -             -     1.05      1.05          1.02            1.06    Met scale\n");
       
    fprintf(pfile,"pdf_qqbar            lnN  -        -          1.08          -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"pdf_vh               lnN  1.08     -            -           -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN  -    1.08       -             -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"QCDscale_ggH         lnN  -    1.12       -             -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"QCDscale_qqH         lnN  -    -          1.035         -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"UEPS                 lnN  0.96    0.96       0.96          -            -              -        -         -          -            -    PDF VBF\n");


    fclose(pfile);
    }
  

  }


  void makeSMEMuDataCardNoVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin       %s     %s            %s            %s            %s         %s           %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process   VH%s     SM%s        VBF%s          ZTT           FAKES        TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process   -2      -1            0             1             2             3            4\n");
      fprintf(pfile,"rate      %.3f     %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	      getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN    %.3f    %.3f          %.3f          -             -             -             -             -             -             -          luminosity\n",
		1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);      
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f   %.3f          %.3f          %.3f          -         %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e    lnN    %.3f      %.3f          %.3f          %.3f          -           %.3f          %.3f       Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -         -             -             %.3f          -             -         -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_);
      fprintf(pfile,"CMS_htt_zttExtrap_sm0 lnN   -         -             -             %.3f          -             -         -         ZTT Scale  \n",
	     1+out.dZTTCORR/out.ZTTCORR);
    fprintf(pfile,"CMS_htt_ttbarNorm      lnN  -         -             -             -             -              %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm     lnN -         -             -             -             -           -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_FakeNorm    lnN  -         -             -             -             %.3f          -             -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
       for(unsigned int j=0;j<shifts_.size();++j)
	   fprintf(pfile,"%s    shape    1             1             1               1             -             -             -        shape\n",shiftsPostFix_[j].c_str());

    fprintf(pfile,"CMS_scale_j           lnN  0.96        0.99          0.92          -            -              0.94            0.97    Jet scale\n");
    fprintf(pfile,"CMS_scale_met           lnN  1.05        1.05          1.05          -            -              1.02            1.06    Met scale\n");
    fprintf(pfile,"pdf_qqbar            lnN  -    -          1.08          -            -              -            -    PDF VBF\n");
    fprintf(pfile,"pdf_vh               lnN  1.08    -       -          -            -              -            -    PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN  -    1.08       -             -            -              -            -    PDF VBF\n");
    fprintf(pfile,"QCDscale_ggH         lnN  -    1.12       -             -            -              -            -    PDF VBF\n");
    fprintf(pfile,"QCDscale_qqH         lnN  -    -          1.035         -            -              -            -    PDF VBF\n");
    fprintf(pfile,"UEPS                 lnN  0.96    0.96       0.96          -            -              -            -    PDF VBF\n");
    fclose(pfile);
    }
  

  }



  void makeSMLTauDataCardVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s           %s            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        VH%s        SM%s        VBF%s        ZTT           QCD           W             ZLL             TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process        -2           -1            0            1             2           3             4             5             6  \n");
      fprintf(pfile,"rate           %.3f        %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.W,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f     %.3f          %.3f          -             -             -             -            -             -          luminosity\n",
		1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      for(unsigned int j=0;j<shifts_.size();++j)
	  fprintf(pfile,"%s    shape    1   1     1       1         -           -          -         -        -                 shape(Ignore small ones that cause instabilities)\n",shiftsPostFix_[j].c_str());
	  
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f  %.3f          %.3f          %.3f          -             -             %.3f            %.3f          %.3f       muon ID /HLT\n",
		1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t     lnN   %.3f   %.3f          %.3f          %.3f          -             -             -                     %.3f          %.3f        Tau IDf\n",
		1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e       lnN %.3f   %.3f          %.3f          %.3f          -             -             %.3f               %.3f           %.3f      Electron ID\n",
		1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
      if(zttScale_!=0)
	fprintf(pfile,"CMS_htt_zttNorm lnN   -             -             -             %.3f          -             -             %.3f                    -              -         ZTT Scale  \n",
		1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);

    /////////FIXPOINT
      fprintf(pfile,"CMS_htt_ztt_extrap_vbf lnN   -                 -             -             %.3f          -             -                %.3f          -              -         ZTT Extrapolation  \n",
	      1+out.dZTTCORR/out.ZTTCORR,1+vbfFactorZErr_/vbfFactorZ_);
    fprintf(pfile,"CMS_htt_ttbarNorm          lnN   -   -             -             -             -             -             -                           %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm        lnN    -  -             -             -             -             -             -                           -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_QCDSyst             lnN -       -             -             -             %.3f          -             -             -                            -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"CMS_htt_W_extrap_vbf           lnN  -    -             -             -             -             %.3f          -             -                            -      W Extrapolation \n",1+vbfFactorWErr_/vbfFactorW_);
    fprintf(pfile,"CMS_htt_%s_WNorm                  lnN   -   -             -             -             -             %.3f          -             -              -              -      W Background \n",channel_.c_str(),1+out.dWCORR/out.WCORR);
    fprintf(pfile,"CMS_htt_ZLL                  lnN   -   -             -             -             -             -          %.3f           -              -      Z(l->tau)   background\n",1+out.dZLFT/out.ZLFT);

    fprintf(pfile,"CMS_scale_j         lnN  1.20        1.03          1.08          -            -              -         -          1.15            1.10    Jet scale\n");
    fprintf(pfile,"CMS_scale_met       lnN  1.05        1.05          1.05          -            -              -      1.05       1.10            1.10    Met scale\n");

    fprintf(pfile,"pdf_qqbar            lnN -     -          1.08          -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN -     1.08       -             -            -              -        -         -          -            -    PDF GGH\n");
    fprintf(pfile,"pdf_vh               lnN 1.08   -         -             -            -              -        -         -          -            -    PDF GGH\n");
    fprintf(pfile,"QCDscale_ggH2in      lnN  -   1.30        -         -            -              -        -         -          -            -    QCD scale \n");
    fprintf(pfile,"QCDscale_qqH         lnN  -    -          1.04         -            -              -        -         -          -            -    QCD scale VBF\n");
    fprintf(pfile,"UEPS                 lnN  1.04    1.04       1.04          -            -              -        -         -          -            -    UEPS VBF\n");
    fclose(pfile);
    }
  
 

  }




  void makeSMEMuDataCardVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s           %s            %s            %s            %s            %s            %s        \n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process   VH%s     SM%s        VBF%s        ZTT           FAKES         TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process   -2     -1            0            1             2           3             4\n");
      fprintf(pfile,"rate      %.3f     %.3f          %.3f         %.3f          %.3f          %.3f       %.3f\n",
	     getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f    %.3f          %.3f          -             -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      for(unsigned int j=0;j<shifts_.size();++j)
	fprintf(pfile,"%s    shape    1      1     1       1         -               -        -     -            shape(Ignore small ones that cause instabilities)\n",shiftsPostFix_[j].c_str());

      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f   %.3f          %.3f          %.3f          -             %.3f          %.3f       muon ID /HLT\n",
		1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t     lnN   %.3f  %.3f          %.3f          %.3f          -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e     lnN   %.3f   %.3f          %.3f          %.3f          -            %.3f           %.3f      Electron ID\n",
		1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
      if(zttScale_!=0)
	fprintf(pfile,"CMS_htt_zttNorm lnN   -  -             -             %.3f          -              -              -         ZTT Scale  \n",
		1+zttScaleErr_/zttScale_);
    /////////FIXPOINT
      fprintf(pfile,"CMS_htt_ztt_extrap_vbf lnN  -     -          -             %.3f          -            -              -         ZTT Extrapolation  \n",
	      1+out.dZTTCORR/out.ZTTCORR);
    fprintf(pfile,"CMS_htt_ttbarNorm          lnN   -   -             -             -             -         %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm        lnN   -   -             -             -             -          -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_FakeNorm        lnN   -   -             -             -             %.3f          -             -       FAKE Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);

    fprintf(pfile,"CMS_scale_j         lnN  1.20        1.03          1.08          -            -              1.15            1.10    Jet scale\n");
    fprintf(pfile,"CMS_scale_met       lnN  1.05        1.05          1.05          -            -              1.10            1.10    Met scale\n");


    fprintf(pfile,"pdf_qqbar            lnN   -   -          1.08          -            -              -        -       PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN   -   1.08       -             -            -              -        -       PDF GGH\n");
    fprintf(pfile,"pdf_vh               lnN   1.08 -         -             -            -              -        -       PDF GGH\n");
    fprintf(pfile,"QCDscale_ggH2in      lnN   -   1.30       -         -            -              -        -           QCD scale \n");
    fprintf(pfile,"QCDscale_qqH         lnN   -   -          1.04         -            -              -        -        QCD scale VBF\n");
    fprintf(pfile,"UEPS                 lnN   1.04   1.04       1.04          -            -              -        -       UEPS VBF\n");
    fclose(pfile);
    }
  
 

  }







  void makeSMLTauDataCardBoost(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin          %s             %s            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process   VH%s      SM%s        VBF%s        ZTT           QCD           W             ZLL             TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process    -2       -1            0            1             2           3             4             5             6  \n");
      fprintf(pfile,"rate       %.3f    %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	 getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.W,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f   %.3f          %.3f          -             -             -             -            -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);

      for(unsigned int j=0;j<shifts_.size();++j)
	  fprintf(pfile,"%s    shape    1     1     1       1         -           -          -         -        -                 shape(Ignore small ones that cause instabilities)\n",shiftsPostFix_[j].c_str());

      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f    %.3f          %.3f          %.3f          -             -             %.3f            %.3f          %.3f       muon ID /HLT\n",
		1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t     lnN   %.3f   %.3f          %.3f          %.3f          -             -             -                     %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e       lnN %.3f    %.3f          %.3f          %.3f          -             -             %.3f               %.3f           %.3f      Electron ID\n",
		1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
      if(zttScale_!=0)
	fprintf(pfile,"CMS_htt_zttNorm lnN   -     -             -             %.3f          -             -             %.3f                    -              -         ZTT Scale  \n",
		1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);

    /////////FIXPOINT
      fprintf(pfile,"CMS_htt_ztt_extrap_boost lnN    - -             -             %.3f          -             -                %.3f          -              -         ZTT Extrapolation  \n",
	      1+out.dZTTCORR/out.ZTTCORR,1+boostFactorZErr_/boostFactorZ_);
    fprintf(pfile,"CMS_htt_ttbarNorm          lnN   -   -             -             -             -             -             -                           %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm        lnN    -  -             -             -             -             -             -                           -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_QCDSyst             lnN -       -             -             -             %.3f          -             -             -                            -      QCD Background\n",channel_.c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"CMS_htt_W_extrap_boost           lnN -      -             -             -             -             %.3f          -             -                            -      W Extrapolation \n",1+boostFactorWErr_/boostFactorW_);
    fprintf(pfile,"CMS_htt_%s_WNorm                  lnN  -    -             -             -             -             %.3f          -             -              -              -      W Background \n",channel_.c_str(),1+out.dWCORR/out.WCORR);
    fprintf(pfile,"CMS_htt_ZLL                  lnN    -  -             -             -             -             -          %.3f           -              -      Z(l->tau)   background\n",1+out.dZLFT/out.ZLFT);

    fprintf(pfile,"CMS_scale_j         lnN  1.02        1.02          1.05          -            -              -         -          1.03            1.08    Jet scale\n");
    fprintf(pfile,"CMS_scale_met       lnN  1.05        1.05          1.05          -            -              -      1.05       1.07            1.06    Met scale\n");
    fprintf(pfile,"pdf_qqbar            lnN      -         -          1.08          -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN      -       1.08       -             -            -              -        -         -          -            -    PDF GGH\n");
    fprintf(pfile,"pdf_vh               lnN      1.08    -          -             -            -              -        -         -          -            -    PDF GGH\n");
    fprintf(pfile,"QCDscale_ggH1in      lnN     -        1.25       -         -            -              -        -         -          -            -    QCD scale \n");
    fprintf(pfile,"QCDscale_qqH         lnN      -        -          1.04         -            -              -        -         -          -            -    QCD scale VBF\n");
    fprintf(pfile,"UEPS                 lnN      1.04     1.04       1.04          -            -              -        -         -          -            -    UEPS VBF\n");
    fclose(pfile);
    }
  
 

  }






  void makeSMLTauDataCardVH(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin          %s             %s            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process   VH%s      SM%s        VBF%s        ZTT           QCD           W             ZLL             TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process    -2       -1            0            1             2           3             4             5             6  \n");
      fprintf(pfile,"rate       %.3f    %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	 getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.W,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f   %.3f          %.3f          -             -             -             -            -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);

      for(unsigned int j=0;j<shifts_.size();++j)
	  fprintf(pfile,"%s    shape    1     1     1       1         -           -          -         -        -                 shape(Ignore small ones that cause instabilities)\n",shiftsPostFix_[j].c_str());
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f    %.3f          %.3f          %.3f          -             -             %.3f            %.3f          %.3f       muon ID /HLT\n",
		1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t     lnN   %.3f   %.3f          %.3f          %.3f          -             -             -                     %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e       lnN %.3f    %.3f          %.3f          %.3f          -             -             %.3f               %.3f           %.3f      Electron ID\n",
		1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
      if(zttScale_!=0)
	fprintf(pfile,"CMS_htt_zttNorm lnN   -     -             -             %.3f          -             -             %.3f                    -              -         ZTT Scale  \n",
		1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);

    /////////FIXPOINT
      fprintf(pfile,"CMS_htt_ztt_extrap_vh lnN    - -             -             %.3f          -             -                %.3f          -              -         ZTT Extrapolation  \n",
	      1+out.dZTTCORR/out.ZTTCORR,1+vhFactorZErr_/vhFactorZ_);
    fprintf(pfile,"CMS_htt_ttbarNorm          lnN   -   -             -             -             -             -             -                           %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm        lnN    -  -             -             -             -             -             -                           -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_QCDSyst             lnN -       -             -             -             %.3f          -             -             -                            -      QCD Background\n",channel_.c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"CMS_htt_W_extrap_boost           lnN -      -             -             -             -             %.3f          -             -                            -      W Extrapolation \n",1+vhFactorWErr_/vhFactorW_);
    fprintf(pfile,"CMS_htt_%s_WNorm                  lnN  -    -             -             -             -             %.3f          -             -              -              -      W Background \n",channel_.c_str(),1+out.dWCORR/out.WCORR);
    fprintf(pfile,"CMS_htt_ZLL                  lnN    -  -             -             -             -             -          %.3f           -              -      Z(l->tau)   background\n",1+out.dZLFT/out.ZLFT);

    fprintf(pfile,"CMS_scale_j         lnN  1.04        1.07          1.04          -            -              -         -          1.02            1.02    Jet scale\n");
    fprintf(pfile,"CMS_scale_met       lnN  1.05        1.05          1.05          -            -              -      1.05       1.06            1.04    Met scale\n");
    fprintf(pfile,"pdf_qqbar            lnN      -         -          1.08          -            -              -        -         -          -            -    PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN      -       1.08       -             -            -              -        -         -          -            -    PDF GGH\n");
    fprintf(pfile,"pdf_vh               lnN      1.08    -          -             -            -              -        -         -          -            -    PDF GGH\n");
    fprintf(pfile,"QCDscale_ggH1in      lnN     -        1.25       -         -            -              -        -         -          -            -    QCD scale \n");
    fprintf(pfile,"QCDscale_qqH         lnN      -        -          1.04         -            -              -        -         -          -            -    QCD scale VBF\n");
    fprintf(pfile,"UEPS                 lnN      1.04     1.04       1.04          -            -              -        -         -          -            -    UEPS VBF\n");
    fclose(pfile);
    }
  
 

  }




  void makeSMEMuDataCardBoost(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s               %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        VH%s           SM%s        VBF%s        ZTT           FAKES         TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process        -2              -1            0            1             2           3             4       \n");
      fprintf(pfile,"rate           %.3f            %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f     %.3f          %.3f          -             -             -             -     luminosity\n",
	   1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      for(unsigned int j=0;j<shifts_.size();++j)
	fprintf(pfile,"%s    shape    1    1     1       -         -           -    -                shape(Ignore small ones that cause instabilities)\n",shiftsPostFix_[j].c_str());

      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f    %.3f          %.3f          %.3f          -                 %.3f          %.3f       muon ID /HLT\n",
		1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e       lnN   %.3f   %.3f          %.3f          %.3f          -               %.3f           %.3f      Electron ID\n",
		1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
      if(zttScale_!=0)
	fprintf(pfile,"CMS_htt_zttNorm lnN   -      -             -             %.3f          -                      -              -         ZTT Scale  \n",
		1+zttScaleErr_/zttScale_);

    fprintf(pfile,"CMS_scale_j         lnN  1.02        1.02          1.05          -            -              1.03            1.08    Jet scale\n");
    fprintf(pfile,"CMS_scale_met       lnN  1.05        1.05          1.05          -            -              1.07            1.06    Met scale\n");

    /////////FIXPOINT
      fprintf(pfile,"CMS_htt_ztt_extrap_boost lnN   -    -             -             %.3f          -               -              -         ZTT Extrapolation  \n",
	      1+out.dZTTCORR/out.ZTTCORR);
    fprintf(pfile,"CMS_htt_ttbarNorm          lnN   -   -             -             -             -            %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm        lnN   -   -             -             -             -             -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_FakeNorm        lnN  -     -             -             -             %.3f          -             -     Fake  Background\n",channel_.c_str(),1+qcdFactorErr_/qcdFactor_);
    fprintf(pfile,"pdf_qqbar            lnN     -   -          1.08          -            -             -            -    PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN    -    1.08       -             -            -             -            -    PDF GGH\n");
    fprintf(pfile,"pdf_vh               lnN    1.08 -          -             -            -             -            -    PDF GGH\n");
    fprintf(pfile,"QCDscale_ggH1in      lnN   -    1.25       -         -            -                 -            -    QCD scale \n");
    fprintf(pfile,"QCDscale_qqH         lnN   -     -          1.04         -            -              -            -    QCD scale VBF\n");
    fprintf(pfile,"UEPS                 lnN   1.04   1.04       1.04          -            -             -            -    UEPS VBF\n");
    fclose(pfile);
    }
  
 

  }







  void makeSMEMuDataCardVH(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMassesDC_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMassesDC_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s               %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        VH%s           SM%s        VBF%s        ZTT           FAKES         TT            VV\n",smMassesDC_[m].c_str(),smMassesDC_[m].c_str(),smMassesDC_[m].c_str());
      fprintf(pfile,"process        -2              -1            0            1             2           3             4       \n");
      fprintf(pfile,"rate           %.3f            %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("VH"+smMassesDC_[m],postfix),getYield("SM"+smMassesDC_[m],postfix),getYield("VBF"+smMassesDC_[m],postfix),out.ZTT,out.QCD,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f     %.3f          %.3f          -             -             -             -     luminosity\n",
	   1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      for(unsigned int j=0;j<shifts_.size();++j)
	fprintf(pfile,"%s    shape    1    1     1       -         -           -    -                shape(Ignore small ones that cause instabilities)\n",shiftsPostFix_[j].c_str());

      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f    %.3f          %.3f          %.3f          -                 %.3f          %.3f       muon ID /HLT\n",
		1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e       lnN   %.3f   %.3f          %.3f          %.3f          -               %.3f           %.3f      Electron ID\n",
		1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
      if(zttScale_!=0)
	fprintf(pfile,"CMS_htt_zttNorm lnN   -      -             -             %.3f          -                      -              -         ZTT Scale  \n",
		1+zttScaleErr_/zttScale_);

    /////////FIXPOINT
      fprintf(pfile,"CMS_htt_ztt_extrap_vh lnN   -    -             -             %.3f          -               -              -         ZTT Extrapolation  \n",
	      1+out.dZTTCORR/out.ZTTCORR);
    fprintf(pfile,"CMS_htt_ttbarNorm          lnN   -   -             -             -             -            %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm        lnN   -   -             -             -             -             -              %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_FakeNorm        lnN  -     -             -             -             %.3f          -             -     Fake  Background\n",channel_.c_str(),1+qcdFactorErr_/qcdFactor_);


    fprintf(pfile,"CMS_scale_j         lnN  1.04        1.07          1.04          -            -             1.02            1.02    Jet scale\n");
    fprintf(pfile,"CMS_scale_met       lnN  1.05        1.05          1.05          -            -             1.06            1.04    Met scale\n");

    fprintf(pfile,"pdf_qqbar            lnN     -   -          1.08          -            -             -            -    PDF VBF\n");
    fprintf(pfile,"pdf_gg               lnN    -    1.08       -             -            -             -            -    PDF GGH\n");
    fprintf(pfile,"pdf_vh               lnN    1.08 -          -             -            -             -            -    PDF GGH\n");
    fprintf(pfile,"QCDscale_ggH1in      lnN   -    1.25       -         -            -                 -            -    QCD scale \n");
    fprintf(pfile,"QCDscale_qqH         lnN   -     -          1.04         -            -              -            -    QCD scale VBF\n");
    fprintf(pfile,"UEPS                 lnN   1.04   1.04       1.04          -            -             -            -    UEPS VBF\n");
    fclose(pfile);
    }
  
 

  }




  void makeMSSMLTauDataCardBTagged(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<mssmMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mA"+mssmMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+".root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s            %s            %s             %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGH%s        BBH%s        ZTT           QCD           W             ZLL             TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4             5              6\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	      getYield("GGH"+mssmMasses_[m],postfix),getYield("BBH"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.W,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -             -             -             -              -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauID_!=0)
	fprintf(pfile,"CMS_eff_t    lnN   %.3f          %.3f          %.3f          -             -             -             -             %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"CMS_eff_e    lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f                 Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -             -             %.3f          -             -             %.3f          %.3f          -                 ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    //FIXPOINTTTT
    fprintf(pfile,"CMS_htt_ztt_extrap_btag lnN   -             -             %.3f          -             -             %.3f        -          -         ZTT Extrapolation\n", 1+out.dZTTCORR/out.ZTTCORR,1+bFactorZErr_/bFactorZ_);
    fprintf(pfile,"CMS_htt_w_extrap_btag lnN   -             -                -             -            %.3f          -             -          -       W Extrapolation\n", 1+bFactorWErr_/bFactorW_);
    fprintf(pfile,"CMS_htt_ttbarNorm  lnN      -             -             -             -             -             -             %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm  lnN      -             -             -             -             -             -             -            %.3f   DiBoson background \n",1+out.dVV/out.VV);
    fprintf(pfile,"CMS_htt_%s_ZLLTNorm  lnN      -             -             -             -             -               %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);

    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    1             1             1            -             -             -             -              -      shape\n",shiftsPostFix_[j].c_str());

    fprintf(pfile,"CMS_htt_%s_QCDNorm  lnN         -             -             -             %.3f          -             -             -                          -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"CMS_htt_%s_WNorm    lnN      -             -             -             -             %.3f          -             -                         -      W Backghround \n",channel_.c_str(),1+out.dWCORR/out.WCORR);

    fprintf(pfile,"CMS_eff_b      lnN      -             %.3f          -             -             -             -                         %.3f           -     BTag efficiency \n",1+bIDErr_/bID_,1+bIDErr_/bID_);
    fprintf(pfile,"CMS_fake_b      lnN      %.3f          -             -             -             -             -                       -              -     BTag MisTag \n",1+bMisIDErr_/bMisID_);


    fprintf(pfile,"CMS_scale_j      lnN     1.04           1.02             -             -             -             -                       1.10              1.03     Jet Scale \n");
    fprintf(pfile,"CMS_scale_met    lnN     1.05           1.05             -             -             -             -                       1.01              1.03     MET SCale \n");

    fclose(pfile);
    }

  }




  void makeMSSMEMuDataCardBTagged(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<mssmMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mA"+mssmMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+".root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGH%s        BBH%s        ZTT           FAKES           TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4 \n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	      getYield("GGH"+mssmMasses_[m],postfix),getYield("BBH"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -             -             -             -              -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"CMS_eff_m     lnN   %.3f          %.3f          %.3f          -             %.3f          %.3f     muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(eleID_!=0)
	fprintf(pfile,"CMS_eff_e    lnN   %.3f          %.3f          %.3f          -              %.3f          %.3f              Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"CMS_htt_zttNorm lnN   -             -             %.3f          -             %.3f          %.3f     ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    //FIXPOINTTTT
    fprintf(pfile,"CMS_htt_ztt_extrap_btag lnN   -             -             %.3f          -       -          -         ZTT Extrapolation\n", 1+out.dZTTCORR/out.ZTTCORR);
    fprintf(pfile,"CMS_htt_ttbarNorm  lnN      -             -             -             -         %.3f           -      TTbar background  \n",1+out.dTOP/out.TOP);
    fprintf(pfile,"CMS_htt_DiBosonNorm  lnN     -             -             -             -             -         %.3f   DiBoson background \n",1+out.dVV/out.VV);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    1             1             1             -             -             -       shape\n",shiftsPostFix_[j].c_str());
    fprintf(pfile,"CMS_htt_%s_FakeNorm  lnN        -             -            -             %.3f          -             -          QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"CMS_eff_b      lnN      -             %.3f          -             -                 %.3f           -     BTag efficiency \n",1+bIDErr_/bID_,1+bIDErr_/bID_);
    fprintf(pfile,"CMS_fake_b      lnN      %.3f          -             -             -             -             -      BTag MisTag \n",1+bMisIDErr_/bMisID_);

    fprintf(pfile,"CMS_scale_j      lnN     1.04           1.02             -             -            1.10              1.03     Jet Scale \n");
    fprintf(pfile,"CMS_scale_met    lnN     1.05           1.05             -             -            1.01              1.03     MET SCale \n");


    fclose(pfile);
    }

  }





  void makeHiggsShapesAll(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;
    float legCorr=1.0;

    if(muID_!=0&&eleID_!=0) {legCorr*=muID_*eleID_;}
    if(muID_!=0&&eleID_==0) {legCorr*=muID_*tauID_;}
    if(muID_==0&&eleID_!=0) {legCorr*=eleID_*tauID_;}


    for(unsigned int i=0;i<mssmMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr,prefix);
      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr,prefix);
    }

    for(unsigned int i=0;i<smMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"sm"+smMasses_[i]+".root","SM"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*smSigma_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"vbf"+smMasses_[i]+".root","VBF"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*vbfSigma_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"vh"+smMasses_[i]+".root","VH"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*vhSigma_[i],prefix);


    }
    interpolateHistogramAndShifts(prefix);

  }


  void makeHiggsShapesSM(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;

    float legCorr=1.0;

    if(muID_!=0&&eleID_!=0) {legCorr*=muID_*eleID_;}
    if(muID_!=0&&eleID_==0) {legCorr*=muID_*tauID_;}
    if(muID_==0&&eleID_!=0) {legCorr*=eleID_*tauID_;}

    for(unsigned int i=0;i<smMasses_.size();++i) {
      if(channel_!="eleMu") {
		tmp= createHistogramAndShifts(dir_+"sm"+smMasses_[i]+".root","SM"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*__HQT__*"+weight_),luminosity_*legCorr*smSigma_[i],prefix);
      }
      else {
	  if(prefix=="_SM1" ||prefix=="_SM3"||prefix=="_SM2")
	    tmp= createHistogramAndShifts(dir_+"sm"+smMasses_[i]+".root","SM"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*0.6*"+weight_),luminosity_*legCorr*smSigma_[i],prefix);
	  else
	    tmp= createHistogramAndShifts(dir_+"sm"+smMasses_[i]+".root","SM"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*smSigma_[i],prefix);
	  }
      tmp= createHistogramAndShifts(dir_+"vbf"+smMasses_[i]+".root","VBF"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*vbfSigma_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"vh"+smMasses_[i]+".root","VH"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*vhSigma_[i],prefix);
    }
    interpolateHistogramAndShifts(prefix);
  }


  void makeHiggsShapesBTag(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;

    float legCorr=1.0;

    if(muID_!=0&&eleID_!=0) {legCorr*=muID_*eleID_;}
    if(muID_!=0&&eleID_==0) {legCorr*=muID_*tauID_;}
    if(muID_==0&&eleID_!=0) {legCorr*=eleID_*tauID_;}


    for(unsigned int i=0;i<mssmMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*bID_,prefix);
      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*bMisID_,prefix);
    }
  }


  void makeHiggsShapesNoBTag(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;

    float legCorr=1.0;
    if(muID_!=0&&eleID_!=0) {legCorr*=muID_*eleID_;}
    if(muID_!=0&&eleID_==0) {legCorr*=muID_*tauID_;}
    if(muID_==0&&eleID_!=0) {legCorr*=eleID_*tauID_;}


    for(unsigned int i=0;i<mssmMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBHNoJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20==0&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr,prefix);
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBHBJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20Matched>0&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*(1/bID_),prefix);
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBHJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20NotMatched>0&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*bMisID_,prefix);

      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGHNoJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20==0&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr,prefix);
      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGHJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20>0&&"+osSignalSelection_+")*"+weight_),luminosity_*legCorr*bMisID_,prefix);

    }
  }



  BkgOutput runOSLSMT(std::string preSelection,std::string prefix,std::string zShape) {

    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;


    //create Z->tautau 
    std::pair<float,float> zttYield       = createHistogramAndShifts(zttFile_,"ZTTTMP",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);

    if(zShape.size()==0) {
      std::pair<float,float> zttShape       = createHistogramAndShifts(zttFile_,"ZTT",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
    }
    else
      {
	//create correction factor for MT and Pzeta cuts
	std::pair<float,float> dataWCut_Before       = createHistogramAndShifts(zShape,"ZTTWCut",("("+preSelection+")*__CORR__*embeddedWeight*__UNFOLD__/HLT_Any"),1.0,prefix);
	std::pair<float,float> zttShape       = createHistogramAndShifts(zShape,"ZTT",("("+preSelection+"&&"+osSignalSelection_+")*__CORR__*__UNFOLD__*embeddedWeight/HLT_Any"),1.0,prefix);

	std::pair<float,float> mcWCut_Before    = createHistogramAndShifts(zttFile_,"ZTTWCutMC",("("+preSelection+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);
	float corrector = (zttShape.first/dataWCut_Before.first) / (zttYield.first/mcWCut_Before.first);
	zttYield = std::make_pair(zttYield.first*corrector,zttYield.second*corrector);
	renormalizeHistogram(channel_+prefix,"ZTT",zttYield.first);
      }
    //create TTbar
    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
    //Create TTbar in Sideband
    std::pair<float,float> topYieldSdb    = createHistogramAndShifts(topFile_,"TT_SDB",("("+preSelection+"&&"+osWSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);

    std::pair<float,float> topSSYield       = createHistogramAndShifts(topFile_,"TTSS",("("+preSelection+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
    //Create TTbar in Sideband
    std::pair<float,float> topSSYieldSdb    = createHistogramAndShifts(topFile_,"TTSS_SDB",("("+preSelection+"&&"+ssWSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);

    //create Diboson
    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
    //create Diboson in sideband
    std::pair<float,float> vvYieldSdb     = createHistogramAndShifts(vvFile_,"VV_SDB",("("+preSelection+"&&"+osWSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);

    std::pair<float,float> zlftYield;
    if(channel_=="muTau")
          zlftYield  = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus==0&&genPt2>1)*"+weight_),luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix,false);
    else
          zlftYield  = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus==0&&genPt2>1)*(1/(HLT_Any*__CORR__))*"+weight_),luminosity_*leg1Corr*zlftFactor_*zttScale_,prefix,false);

    std::pair<float,float> zjftYield      = createHistogramAndShifts(zllFile_,"ZJ",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus==0&&genPt2<1)*"+weight_),luminosity_*leg1Corr*zttScale_,prefix);
    std::pair<float,float> zlftSSYield    = createHistogramAndShifts(zllFile_,"ZL_SS",("("+preSelection+"&&"+ssSignalSelection_+"&&genTaus==0&&genPt2>1)*"+weight_),luminosity_*leg1Corr*zttScale_,prefix);
    std::pair<float,float> zjftSSYield    = createHistogramAndShifts(zllFile_,"ZJ_SS",("("+preSelection+"&&"+ssSignalSelection_+"&&genTaus==0&&genPt2<1)*"+weight_),luminosity_*leg1Corr*zttScale_,prefix,false);
    std::pair<float,float> wMCYield       = createHistogramAndShifts(wFile_,"W",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr,prefix,false);
    std::pair<float,float> wMCSSYield       = createHistogramAndShifts(wFile_,"WSS",("("+preSelection+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*leg1Corr,prefix);
    std::pair<float,float> dataY         = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataYRounded  = std::make_pair(rintf(dataY.first),dataY.second);
    renormalizeHistogram(channel_+prefix,"data_obs",dataYRounded.first);
    std::pair<float,float> dataYield      = convertToPoisson(dataYRounded);
 
    std::pair<float,float> dataSSY          = createHistogramAndShifts(dataFile_,"data_obs_ss","("+preSelection+"&&"+ssSignalSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataSSYield      = convertToPoisson(dataSSY);

    std::pair<float,float> dataYSdb     = createHistogramAndShifts(dataFile_,"data_obs_sdb","("+preSelection+"&&"+osWSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataYieldSdb      = convertToPoisson(dataYSdb);

    std::pair<float,float> dataSSYSdb = createHistogramAndShifts(dataFile_,"data_obs_ss_sdb","("+preSelection+"&&"+ssWSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataSSYieldSdb = convertToPoisson(dataSSYSdb);


    //shape creation for QCD ==== SUBTRACT THE BAD GUYS!
    std::pair<float,float> dataQCDControl = createHistogramAndShifts(dataFile_,"QCD",qcdSelection_,scaleUp_,prefix);
    std::pair<float,float> zllQCDControl = createHistogramAndShifts(zllFile_,"ZLLQCD","("+qcdSelection_+"&&genTaus==0)*"+weight_,luminosity_*leg1Corr*zttScale_,prefix);
    std::pair<float,float> ttQCDControl = createHistogramAndShifts(topFile_,"TOPQCD","("+qcdSelection_+")*"+weight_,luminosity_*leg1Corr*tauID_,prefix);
    subtractHistogram(channel_+prefix,"QCD","ZLLQCD");
    subtractHistogram(channel_+prefix,"QCD","TOPQCD");

    //Inflate the errors(note that currently there are only statistical on templates+ Add here the background estimates)
    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);

    std::pair<float,float> topInflSSYield  = inflateError(topSSYield,topErr_);
    printf("TTbar events in SS signal region = %f + %f \n",topInflSSYield.first,topInflSSYield.second);

    std::pair<float,float> topInflYieldSdb  = inflateError(topYieldSdb,topErr_);
    printf("TTbar events in sideband region = %f + %f \n",topYieldSdb.first,topInflYieldSdb.second);

    std::pair<float,float> topInflSSYieldSdb  = inflateError(topSSYieldSdb,topErr_);
    printf("TTbar events in SS sideband region = %f + %f \n",topSSYieldSdb.first,topInflSSYieldSdb.second);

    std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
    printf("Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);

    std::pair<float,float> vvInflYieldSdb  = inflateError(vvYieldSdb,vvErr_);
    printf("Diboson events in sideband region = %f + %f \n",vvYieldSdb.first,vvInflYieldSdb.second);
    
    std::pair<float,float> zlftInflYield  = inflateError(zlftYield,zlftErr_);
    printf("Z (l->tau) in signal region = %f + %f \n",zlftInflYield.first,zlftInflYield.second);
    
    std::pair<float,float> zjftInflYield  = inflateError(zjftYield,zjftErr_);
    printf("Z (j->tau) in signal region = %f + %f \n",zjftInflYield.first,zjftInflYield.second);
    
    std::pair<float,float> zlftInflSSYield  = inflateError(zlftSSYield,zlftErr_);
    printf("Z (l->tau) in SS region = %f + %f \n",zlftInflSSYield.first,zlftInflSSYield.second);
    
    std::pair<float,float> zjftInflSSYield  = inflateError(zjftSSYield,zjftErr_);
    printf("Z (j->tau) in SS region = %f + %f \n",zjftInflSSYield.first,zjftInflSSYield.second);


    //Measure W factor from your corrected MC 
    std::pair<float,float> wFactor = extractWFactor(wFile_,preSelection);
    printf("W extrapolation factor as measured in corrected MC = %f +- %f\n",wFactor.first,wFactor.second);
   

    //Runi OS+LS + MT method
    printf("1. Subtract TTbar and diboson from sideband");
    std::pair<float,float> osWHigh = std::make_pair(TMath::Nint(dataYieldSdb.first-topInflYieldSdb.first-vvInflYieldSdb.first),
						      sqrt(dataYieldSdb.second*dataYieldSdb.second+topInflYieldSdb.second*topInflYieldSdb.second+vvInflYieldSdb.second*vvInflYieldSdb.second));
    printf("OS W in sideband  =%f -%f -%f  = %f +- %f \n",dataYieldSdb.first,topInflYieldSdb.first,vvInflYieldSdb.first,osWHigh.first,osWHigh.second);
     
    printf("2. Extrapolate W in the low MT region\n");
    std::pair<float,float> osWLow = std::make_pair(osWHigh.first*wFactor.first,
						     sqrt(osWHigh.first*osWHigh.first*wFactor.second*wFactor.second+osWHigh.second*osWHigh.second*wFactor.first*wFactor.first));
      
    printf("OS W  in core  =%f *%f  = %f +- %f \n",osWHigh.first,wFactor.first,osWLow.first,osWLow.second);
      
    printf("3. Repeat for SS : first subtract TTbar W\n");
    std::pair<float,float> ssWHigh = std::make_pair(TMath::Nint(dataSSYieldSdb.first-topInflSSYieldSdb.first),
						      sqrt(dataSSYieldSdb.second*dataSSYieldSdb.second+topInflSSYieldSdb.second*topInflSSYieldSdb.second));

    std::pair<float,float> ssWLow = std::make_pair(ssWHigh.first*wFactor.first,
						   sqrt(ssWHigh.second*ssWHigh.second*wFactor.first*wFactor.first+wFactor.second*wFactor.second*ssWHigh.first*ssWHigh.first));
          
    printf("4. From all SS events subtract W and Z jet fakes tau/TTbar to get QCD ");
    std::pair<float,float> ssQCD = std::make_pair(TMath::Nint(dataSSYield.first-ssWLow.first-zlftInflSSYield.first-zjftInflSSYield.first-topInflSSYield.first),
						  sqrt(dataSSYield.second*dataSSYield.second+ssWLow.second*ssWLow.second+zlftInflSSYield.second*zlftInflSSYield.second+zjftInflSSYield.second*zjftInflSSYield.second+topInflSSYield.second*topInflSSYield.second));

      if(ssQCD.first<0) {
	ssQCD.first=0.0000001;
	ssQCD.second=1.8;
      }
      
      printf("SS QCD in  core  =%f -%f -%f -%f -%f = %f +- %f \n",dataSSYield.first,ssWLow.first,zjftInflSSYield.first,zlftInflSSYield.first,topInflSSYield.first,ssQCD.first,ssQCD.second);
      
      printf("5. Extrapolate SS QCD -> OS QCD ");
      std::pair<float,float> osQCD = std::make_pair(ssQCD.first*qcdFactor_,sqrt(ssQCD.second*ssQCD.second*qcdFactor_*qcdFactor_+qcdFactorErr_*qcdFactorErr_*ssQCD.first*ssQCD.first));
      printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,qcdFactor_,osQCD.first,osQCD.second);
           
      float background    = osQCD.first+osWLow.first+topInflYield.first+vvInflYield.first+zlftInflYield.first+zjftInflYield.first+zttYield.first;
      float backgroundErr = sqrt(osQCD.second*osQCD.second+osWLow.second*osWLow.second+topInflYield.second*topInflYield.second+vvInflYield.second*vvInflYield.second+zlftInflYield.second*zlftInflYield.second+zjftInflYield.second*zjftInflYield.second+zttYield.second*zttYield.second);
      printf("BACKGROUND=%f +-%f \n",background,backgroundErr);


      ///LATEX->Here since we want it for the note add all errors , even those that will go separate in the datacard
      printf("LATEX ------------------------------------\n");
      printf("Total & %.2f & %.2f & %.2f & %.2f \\\\ \n", dataYield.first, dataYieldSdb.first, dataSSYield.first, dataSSYieldSdb.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", vvInflYield.first, quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_), vvInflYieldSdb.first, quadrature(vvInflYieldSdb.first,vvInflYieldSdb.second,muIDErr_,eleIDErr_,tauIDErr_));
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", topInflYield.first,quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_), topInflYieldSdb.first, quadrature(topInflYieldSdb.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_));
      printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zjftInflYield.first, quadrature(zjftInflYield.first,zjftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_), zjftInflSSYield.first,quadrature(zjftInflSSYield.first,zjftInflSSYield.second,muIDErr_,eleIDErr_,zttScaleErr_));
      printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zlftInflYield.first, quadrature(zlftInflYield.first,zlftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_),zlftInflSSYield.first,quadrature(zlftInflSSYield.first,zlftInflSSYield.second,muIDErr_,eleIDErr_,zttScaleErr_));
      printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow.first, osWLow.second, osWHigh.first, osWHigh.second, ssWLow.first, ssWLow.second, dataSSYieldSdb.first, dataSSYieldSdb.second);
      printf("QCD & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zttYield.first,quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_));

      float fullBackgroundErr = sqrt(pow(quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)+
				       pow(quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_),2)+
				       pow(quadrature(zjftInflYield.first,zjftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_),2)+
				       pow(quadrature(zlftInflYield.first,zlftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_),2)+
				       pow(osQCD.second,2)+
				       pow(osWLow.second,2)+
				       pow(quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2));

      printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,sqrt(pow(quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)+
										       pow(quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_),2)+
										       pow(quadrature(zjftInflYield.first,zjftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_),2)+
										       pow(quadrature(zlftInflYield.first,zlftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_),2)+
										       pow(osQCD.second,2)+
										       pow(osWLow.second,2)+
										       pow(quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)));



      //create a histogram with the error for plotting reasons and only
      TH1F *err = new TH1F("BKGErr","",1,0,1);
      err->SetBinContent(1,fullBackgroundErr/background);
      fout_->cd((channel_+prefix).c_str());
      err->Write();

      BkgOutput output;
      output.DATA = dataYield.first;
      output.W = osWLow.first;
      output.dW = osWLow.second;
      output.WSDB = osWHigh.first;
     
      output.WCORR = output.W/wMCYield.first;
      output.dWCORR = output.dW/wMCYield.first;
      printf("W correction factor =  %f +-%f\n",output.WCORR,output.dWCORR);

      output.WSS = ssWLow.first;
      output.dWSS = ssWLow.second;

      output.WSSCORR = output.WSS/wMCSSYield.first;
      output.dWSSCORR = output.dWSS/wMCSSYield.first;
      printf("W correction factor =  %f +-%f\n",output.WSSCORR,output.dWSSCORR);
      
      output.QCD = osQCD.first;
      output.dQCD = osQCD.second;
      output.QCDSDB = ssQCD.first;

      output.ZLFT = zlftInflYield.first;
      output.dZLFT =zlftInflYield.second;
      output.ZLFTSS = zlftInflSSYield.first;
      output.dZLFTSS =zlftInflSSYield.second;

      output.ZJFT = zjftInflYield.first;
      output.dZJFT =zjftInflYield.second;
      output.ZJFTSS = zjftInflSSYield.first;
      output.dZJFTSS =zjftInflSSYield.second;
      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;

      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;

      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;
      
      output.WF = wFactor.first;
      output.dWF = wFactor.second;

      //now renormalize the histograms that you extracted from OS/LS+MT Method

      renormalizeHistogram(channel_+prefix,"QCD",osQCD.first);
      renormalizeHistogram(channel_+prefix,"W",osWLow.first);

      return output;
  }







  BkgOutput runMinimalExtrapolation(std::string preSelection,std::string categorySelection,std::string prefix,float zExtrap_, float zExtrapErr_,float topExtrap,float topExtrapErr,BkgOutput inclusive, std::string zShape) {

    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;


    float zExtrap = zExtrap_;
    float zExtrapErr = zExtrapErr_;

      BkgOutput output;


      output.ZTTCORR=zExtrap;
      output.dZTTCORR=zExtrapErr;


    //create Z->tautau 
    std::pair<float,float> zttYield       = createHistogramAndShifts(zttFile_,"ZTTTMP",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*zExtrap*leg1Corr*tauID_,prefix);
    if(zShape.size()==0) {
      std::pair<float,float> zttShape       = createHistogramAndShifts(zttFile_,"ZTT",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*zExtrap*leg1Corr*tauID_,prefix);
    }
    else
      {
	printf("You have embedded samples.Calculating corrections on the fly overidding the crappy ones you gave me!\n");
	std::pair<float,float> zttShape       = createHistogramAndShifts(zShape,"ZTT",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+")*__CORR__*__UNFOLD__*embeddedWeight/HLT_Any"),leg1Corr*tauID_,prefix,true);
	std::pair<float,float> zttShapePre    = createHistogramAndShifts(zShape,"ZTTPre",("("+preSelection+"&&"+osSignalSelection_+")*__CORR__*__UNFOLD__*embeddedWeight/HLT_Any"),leg1Corr*tauID_,prefix,true);

	//take into account the inclusive correction factor
	std::pair<float,float> zttYieldWCut       = createHistogramAndShifts(zttFile_,"ZTTWCut",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix);


	float corr = zttShape.first/zttShapePre.first;
	printf("Efficiency for embedding =%f\n",corr);
	printf("Efficiency for MC        =%f\n",zttYield.first/inclusive.ZTT);

	zttYield = std::make_pair(inclusive.ZTT*corr,inclusive.dZTT*corr);


	//correct the yield to account for the Pzeta cut from embedding
	//	zttYield = std::make_pair(zttYield.first*inclusive.ZTT/zttYieldWCut.first,zttYield.second*inclusive.ZTT/zttYieldWCut.first);
	renormalizeHistogram(channel_+prefix,"ZTT",zttYield.first);
      }
    //create TTbar
    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);
    //Create TTbar in Sideband
    std::pair<float,float> topYieldSdb    = createHistogramAndShifts(topFile_,"TT_SDB",("("+preSelection+"&&"+osWSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);

    std::pair<float,float> topSSYield       = createHistogramAndShifts(topFile_,"TTSS",("("+preSelection+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);
    //Create TTbar in Sideband
    std::pair<float,float> topSSYieldSdb    = createHistogramAndShifts(topFile_,"TTSS_SDB",("("+preSelection+"&&"+ssWSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);

    //create Diboson
    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);
    //create Diboson in sideband
    std::pair<float,float> vvYieldSdb     = createHistogramAndShifts(vvFile_,"VV_SDB",("("+preSelection+"&&"+osWSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix);

    std::pair<float,float> zlftYield;
    if(channel_=="eleTau")
      zlftYield      = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+"&&genTaus==0&&genPt2>1)*(1./(HLT_Any*__CORR__))*"+weight_),luminosity_*leg1Corr*zlftFactor_*zttScale_*zExtrap,prefix);
    else
      zlftYield      = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+"&&genTaus==0&&genPt2>1)*"+weight_),luminosity_*leg1Corr*zlftFactor_*zttScale_*zExtrap,prefix);

    std::pair<float,float> zjftYield      = createHistogramAndShifts(zllFile_,"ZJ",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+"&&genTaus==0&&genPt2<1)*"+weight_),luminosity_*leg1Corr*zttScale_*zExtrap,prefix);


    std::pair<float,float> zlftSSYield    = createHistogramAndShifts(zllFile_,"ZL_SS",("("+preSelection+"&&"+ssSignalSelection_+"&&"+categorySelection+"&&genTaus==0&&genPt2>1)*"+weight_),luminosity_*leg1Corr*zttScale_*zExtrap,prefix,false);
    std::pair<float,float> zjftSSYield    = createHistogramAndShifts(zllFile_,"ZJ_SS",("("+preSelection+"&&"+ssSignalSelection_+"&&"+categorySelection+"&&genTaus==0&&genPt2<1)*"+weight_),luminosity_*leg1Corr*zttScale_*zExtrap,prefix);
    std::pair<float,float> wMCYield       = createHistogramAndShifts(wFile_,"WMC",("("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix);
    std::pair<float,float> wShape       = createHistogramAndShifts(wFile_,"W",("("+relaxedSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix,false);
    std::pair<float,float> wMCSSYield       = createHistogramAndShifts(wFile_,"WSS",("("+preSelection+"&&"+ssSignalSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr,prefix);
    std::pair<float,float> dataY         = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+"&&"+categorySelection+")",scaleUp_,prefix);
    std::pair<float,float> dataYRounded  = std::make_pair(rintf(dataY.first),dataY.second);
    renormalizeHistogram(channel_+prefix,"data_obs",dataYRounded.first);
    std::pair<float,float> dataYield      = convertToPoisson(dataYRounded);
 
    std::pair<float,float> dataSSY          = createHistogramAndShifts(dataFile_,"data_obs_ss","("+preSelection+"&&"+ssSignalSelection_+"&&"+categorySelection+")",scaleUp_,prefix);
    std::pair<float,float> dataSSYield      = convertToPoisson(dataSSY);

    std::pair<float,float> dataYSdb     = createHistogramAndShifts(dataFile_,"data_obs_sdb","("+preSelection+"&&"+osWSelection_+"&&"+categorySelection+")",scaleUp_,prefix);
    std::pair<float,float> dataYieldSdb      = convertToPoisson(dataYSdb);

    std::pair<float,float> dataSSYSdb = createHistogramAndShifts(dataFile_,"data_obs_ss_sdb","("+preSelection+"&&"+ssWSelection_+"&&"+categorySelection+")",scaleUp_,prefix);
    std::pair<float,float> dataSSYieldSdb = convertToPoisson(dataSSYSdb);


    //shape creation for QCD ==== SUBTRACT THE BAD GUYS!
    std::pair<float,float> dataQCDControl = createHistogramAndShifts(dataFile_,"QCD",qcdSelection_+"&&"+categorySelection,scaleUp_,prefix);
    std::pair<float,float> zllQCDControl = createHistogramAndShifts(zllFile_,"ZLLQCD","("+qcdSelection_+"&&"+categorySelection+"&&genTaus==0)*"+weight_,luminosity_*leg1Corr*zExtrap*zttScale_,prefix);
    std::pair<float,float> ttQCDControl = createHistogramAndShifts(topFile_,"TOPQCD","("+qcdSelection_+"&&"+categorySelection+")*"+weight_,luminosity_*leg1Corr*tauID_,prefix);
    subtractHistogram(channel_+prefix,"QCD","ZLLQCD");
    subtractHistogram(channel_+prefix,"QCD","TOPQCD");

    //Inflate the errors(note that currently there are only statistical on templates+ Add here the background estimates)
    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);

    std::pair<float,float> topInflSSYield  = inflateError(topSSYield,topErr_);
    printf("TTbar events in SS signal region = %f + %f \n",topInflSSYield.first,topInflSSYield.second);

    std::pair<float,float> topInflYieldSdb  = inflateError(topYieldSdb,topErr_,topExtrapErr);
    printf("TTbar events in sideband region = %f + %f \n",topYieldSdb.first,topInflYieldSdb.second);

    std::pair<float,float> topInflSSYieldSdb  = inflateError(topSSYieldSdb,topErr_,topExtrapErr);
    printf("TTbar events in SS sideband region = %f + %f \n",topSSYieldSdb.first,topInflSSYieldSdb.second);

    std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
    printf("Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);

    std::pair<float,float> vvInflYieldSdb  = inflateError(vvYieldSdb,vvErr_);
    printf("Diboson events in sideband region = %f + %f \n",vvYieldSdb.first,vvInflYieldSdb.second);
    
    std::pair<float,float> zlftInflYield  = inflateError(zlftYield,zlftErr_);
    printf("Z (l->tau) in signal region = %f + %f \n",zlftInflYield.first,zlftInflYield.second);
    
    std::pair<float,float> zjftInflYield  = inflateError(zjftYield,zjftErr_);
    printf("Z (j->tau) in signal region = %f + %f \n",zjftInflYield.first,zjftInflYield.second);
    
    std::pair<float,float> zlftInflSSYield  = inflateError(zlftSSYield,zlftErr_,zExtrapErr);
    printf("Z (l->tau) in SS region = %f + %f \n",zlftInflSSYield.first,zlftInflSSYield.second);
    
    std::pair<float,float> zjftInflSSYield  = inflateError(zjftSSYield,zjftErr_,zExtrapErr);
    printf("Z (j->tau) in SS region = %f + %f \n",zjftInflSSYield.first,zjftInflSSYield.second);


    //Measure W factor from your corrected MC 
    std::pair<float,float> wFactor = extractWFactor(wFile_,preSelection);
    printf("W extrapolation factor as measured in corrected MC = %f +- %f\n",wFactor.first,wFactor.second);
   

    //Run OS+LS + MT method
    printf("1. Subtract TTbar and diboson from sideband");
    std::pair<float,float> osWHigh = std::make_pair(TMath::Nint(dataYieldSdb.first-topInflYieldSdb.first-vvInflYieldSdb.first),
						      sqrt(dataYieldSdb.second*dataYieldSdb.second+topInflYieldSdb.second*topInflYieldSdb.second+vvInflYieldSdb.second*vvInflYieldSdb.second));
    printf("OS W in sideband  =%f -%f -%f  = %f +- %f \n",dataYieldSdb.first,topInflYieldSdb.first,vvInflYieldSdb.first,osWHigh.first,osWHigh.second);
     
    printf("2. Extrapolate W in the low MT region\n");
    std::pair<float,float> osWLow = std::make_pair(osWHigh.first*wFactor.first,
						     sqrt(osWHigh.first*osWHigh.first*wFactor.second*wFactor.second+osWHigh.second*osWHigh.second*wFactor.first*wFactor.first));
      
    printf("OS W  in core  =%f *%f  = %f +- %f \n",osWHigh.first,wFactor.first,osWLow.first,osWLow.second);
      
    printf("3. Repeat for SS : first subtract TTbar W\n");
    std::pair<float,float> ssWHigh = std::make_pair(TMath::Nint(dataSSYieldSdb.first-topInflSSYieldSdb.first),
						      sqrt(dataSSYieldSdb.second*dataSSYieldSdb.second+topInflSSYieldSdb.second*topInflSSYieldSdb.second));

    std::pair<float,float> ssWLow = std::make_pair(ssWHigh.first*wFactor.first,
						   sqrt(ssWHigh.second*ssWHigh.second*wFactor.first*wFactor.first+wFactor.second*wFactor.second*ssWHigh.first*ssWHigh.first));
          
    printf("4. From all SS events subtract W and Z jet fakes tau/TTbar to get QCD ");
    std::pair<float,float> ssQCD = std::make_pair(TMath::Nint(dataSSYield.first-ssWLow.first-zlftInflSSYield.first-zjftInflSSYield.first-topInflSSYield.first),
						  sqrt(dataSSYield.second*dataSSYield.second+ssWLow.second*ssWLow.second+zlftInflSSYield.second*zlftInflSSYield.second+zjftInflSSYield.second*zjftInflSSYield.second+topInflSSYield.second*topInflSSYield.second));

      if(ssQCD.first<0) {
	ssQCD.first=0.0000001;
	ssQCD.second=1.8;
      }
      
      printf("SS QCD in  core  =%f -%f -%f -%f -%f = %f +- %f \n",dataSSYield.first,ssWLow.first,zjftInflSSYield.first,zlftInflSSYield.first,topInflSSYield.first,ssQCD.first,ssQCD.second);
      
      printf("5. Extrapolate SS QCD -> OS QCD ");
      std::pair<float,float> osQCD = std::make_pair(ssQCD.first*qcdFactor_,sqrt(ssQCD.second*ssQCD.second*qcdFactor_*qcdFactor_+qcdFactorErr_*qcdFactorErr_*ssQCD.first*ssQCD.first));
      printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,qcdFactor_,osQCD.first,osQCD.second);
           
      float background    = osQCD.first+osWLow.first+topInflYield.first+vvInflYield.first+zlftInflYield.first+zjftInflYield.first+zttYield.first;
      float backgroundErr = sqrt(osQCD.second*osQCD.second+osWLow.second*osWLow.second+topInflYield.second*topInflYield.second+vvInflYield.second*vvInflYield.second+zlftInflYield.second*zlftInflYield.second+zjftInflYield.second*zjftInflYield.second+zttYield.second*zttYield.second);
      printf("BACKGROUND=%f +-%f \n",background,backgroundErr);


      ///LATEX->Here since we want it for the note add all errors , even those that will go separate in the datacard
      printf("LATEX ------------------------------------\n");
      printf("Total & %.2f & %.2f & %.2f & %.2f \\\\ \n", dataYield.first, dataYieldSdb.first, dataSSYield.first, dataSSYieldSdb.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", vvInflYield.first, quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_), vvInflYieldSdb.first, quadrature(vvInflYieldSdb.first,vvInflYieldSdb.second,muIDErr_,eleIDErr_,tauIDErr_));
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", topInflYield.first,quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_,topExtrapErr), topInflYieldSdb.first, quadrature(topInflYieldSdb.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_,topExtrapErr));
      printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zjftInflYield.first, quadrature(zjftInflYield.first,zjftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr), zjftInflSSYield.first,quadrature(zjftInflSSYield.first,zjftInflSSYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr));
      printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zlftInflYield.first, quadrature(zlftInflYield.first,zlftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr),zlftInflSSYield.first,quadrature(zlftInflSSYield.first,zlftInflSSYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr));
      printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow.first, osWLow.second, osWHigh.first, osWHigh.second, ssWLow.first, ssWLow.second, dataSSYieldSdb.first, dataSSYieldSdb.second);
      printf("QCD & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zttYield.first,quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_,zExtrapErr));
      float fullBackgroundErr = sqrt(pow(quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)+
										       pow(quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_,topExtrapErr),2)+
										       pow(quadrature(zjftInflYield.first,zjftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr),2)+
										       pow(quadrature(zlftInflYield.first,zlftInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr),2)+
										       pow(osQCD.second,2)+
										       pow(osWLow.second,2)+
				     pow(quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_,zExtrapErr),2));
      printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,fullBackgroundErr);



      //create a histogram with the error for plotting reasons and only
      TH1F *err = new TH1F("BKGErr","",1,0,1);
      err->SetBinContent(1,fullBackgroundErr/background);
      fout_->cd((channel_+prefix).c_str());
      err->Write();



      output.DATA = dataYield.first;
      output.W = osWLow.first;
      output.dW = osWLow.second;
      output.WSDB = osWHigh.first;
     
      output.WCORR = output.W/wMCYield.first;
      output.dWCORR = output.dW/wMCYield.first;
      printf("W correction factor =  %f +-%f\n",output.WCORR,output.dWCORR);

      output.WSS = ssWLow.first;
      output.dWSS = ssWLow.second;

      output.WSSCORR = output.WSS/wMCSSYield.first;
      output.dWSSCORR = output.dWSS/wMCSSYield.first;
      printf("W correction factor =  %f +-%f\n",output.WSSCORR,output.dWSSCORR);
      
      output.QCD = osQCD.first;
      output.dQCD = osQCD.second;
      output.QCDSDB = ssQCD.first;

      output.ZLFT = zlftInflYield.first;
      output.dZLFT =zlftInflYield.second;
      output.ZLFTSS = zlftInflSSYield.first;
      output.dZLFTSS =zlftInflSSYield.second;

      output.ZJFT = zjftInflYield.first;
      output.dZJFT =zjftInflYield.second;
      output.ZJFTSS = zjftInflSSYield.first;
      output.dZJFTSS =zjftInflSSYield.second;
      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;

      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;

      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;
      
      output.WF = wFactor.first;
      output.dWF = wFactor.second;

      

      //now renormalize the histograms that you extracted from OS/LS+MT Method

      renormalizeHistogram(channel_+prefix,"QCD",osQCD.first);
      renormalizeHistogram(channel_+prefix,"W",osWLow.first);

      return output;
  }





  BkgOutput runABCD(std::string preSelection,std::string catSelection,std::string prefix,float zExtrap,float zExtrapErr,float topExtrap,float topExtrapErr,std::string zShape = "") {
    BkgOutput output;


    //create Z->tautau 
    std::pair<float,float> zttYield       = createHistogramAndShifts(zttFile_,"ZTTTMP",("("+preSelection+"&&"+catSelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*muID_*zExtrap*eleID_,prefix);

    if(zShape.size()==0) {
      std::pair<float,float> zttShape     = createHistogramAndShifts(zttFile_,"ZTT",("("+preSelection+"&&"+catSelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*muID_*zExtrap*eleID_,prefix);
	output.ZTTCORR=zExtrap;
	output.dZTTCORR=zExtrapErr;
    }
    else {
	printf("You have embedded samples.Calculating corrections on the fly overidding the crappy ones you gave me!\n");
	std::pair<float,float> zttPreMC     = createHistogramAndShifts(zttFile_,"ZTTMCPre",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*muID_*eleID_,prefix);
	std::pair<float,float> zttPreYield  = createHistogramAndShifts(zShape,"ZTTTMPInc",("("+preSelection+"&&"+osSignalSelection_+")*embeddedWeight"),muID_*eleID_,prefix);
	std::pair<float,float> zttShape       = createHistogramAndShifts(zShape,"ZTTTMPPRE",("("+preSelection+"&&"+catSelection+"&&"+osSignalSelection_+")*embeddedWeight"),muID_*eleID_,prefix);
	std::pair<float,float> zttHisto       = createHistogramAndShifts(zShape,"ZTT",("("+preSelection+"&&"+catSelection+"&&"+osSignalSelection_+")*embeddedWeight"),muID_*eleID_,prefix);

	//creating Correction Factor on the fly:
	double corr = zttShape.first/zttPreYield.first;
	double corrErr =max(TEfficiency::ClopperPearson((int)zttPreYield.first,(int)zttShape.first,0.68,true)-corr,corr-TEfficiency::ClopperPearson((int)zttPreYield.first,(int)zttShape.first,0.68,false));
	  
	zttYield = std::make_pair(zttPreMC.first*corr,sqrt(zttPreMC.second*zttPreMC.second*corr*corr+zttPreMC.first*zttPreMC.first*corrErr*corrErr));

	printf("New Correction factor = %f +- %f\n",corr,corrErr);
	renormalizeHistogram(channel_+prefix,"ZTT",zttPreMC.first*corr);
	  
	output.ZTTCORR=corr;
	output.dZTTCORR=corrErr;
    }

    //create TTbar
    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+catSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*muID_*eleID_*topExtrap,prefix);
    //Create TTbar in Sideband
    std::pair<float,float> topSSYield       = createHistogramAndShifts(topFile_,"TTSS",("("+preSelection+"&&"+catSelection+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*muID_*eleID_*topExtrap,prefix);
    //create Diboson
    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+osSignalSelection_+"&&"+catSelection+")*"+weight_),luminosity_*muID_*eleID_,prefix);
    std::pair<float,float> vvSSYield        = createHistogramAndShifts(vvFile_,"VVSS",("("+preSelection+"&&"+catSelection+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*muID_*eleID_,prefix);

    //create VJets
    std::pair<float,float> wYield       = createHistogramAndShifts(wFile_,"W",("("+preSelection+"&&"+catSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*(muID_+eleID_)*topExtrap/2.,prefix);
    std::pair<float,float> wSSYield       = createHistogramAndShifts(wFile_,"WSS",("("+preSelection+"&&"+catSelection+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*(muID_+eleID_)/2*topExtrap,prefix);
    std::pair<float,float> zYield       = createHistogramAndShifts(zllFile_,"Z",("("+preSelection+"&&"+catSelection+"&&"+osSignalSelection_+"&&genTaus==0)*"+weight_),luminosity_*(muID_+eleID_)*topExtrap/2.,prefix);
    std::pair<float,float> zSSYield       = createHistogramAndShifts(zllFile_,"ZSS",("("+preSelection+"&&"+catSelection+"&&"+ssSignalSelection_+"&&genTaus==0)*"+weight_),luminosity_*(muID_+eleID_)/2*topExtrap,prefix);
    //Add them
    std::pair<float,float> vYield = std::make_pair(wYield.first+zYield.first,quadrature(wYield.first+zYield.first,sqrt(wYield.second*wYield.second+zYield.second*zYield.second),zjftErr_));
    std::pair<float,float> vSSYield = std::make_pair(wSSYield.first+zSSYield.first,quadrature(wSSYield.first+zSSYield.first,sqrt(wSSYield.second*wSSYield.second+zSSYield.second*zSSYield.second),zjftErr_));



    //oooook Now create the four regions:


    // OS+Isolated
    std::pair<float,float> dataY         = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+"&&"+catSelection+")",scaleUp_,prefix);
    std::pair<float,float> dataYRounded  = std::make_pair(rintf(dataY.first),dataY.second);
    renormalizeHistogram(channel_+prefix,"data_obs",dataYRounded.first);
    std::pair<float,float> dataYield      = convertToPoisson(dataYRounded);

    // OS+NonIsolated
    std::pair<float,float> dataYSdb       = createHistogramAndShifts(dataFile_,"data_sdb","("+preSelection+"&&"+osWSelection_+"&&"+catSelection+")",scaleUp_,prefix);
    std::pair<float,float> dataYieldSdb      = convertToPoisson(dataYSdb);

    //SS+Isolated
    //    std::pair<float,float> dataSSY        = createHistogramAndShifts(dataFile_,"data_sdb","("+preSelection+"&&"+ssSignalSelection_+"&&"+catSelection+")",scaleUp_,prefix);
    std::pair<float,float> dataSSY        = createHistogramAndShifts(dataFile_,"data_sdb","("+preSelection+"&&"+ssSignalSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataSSYield    = convertToPoisson(dataSSY);

    //SS+NonIsolated
    //    std::pair<float,float> dataSSYSdb        = createHistogramAndShifts(dataFile_,"data_sdb","("+preSelection+"&&"+ssWSelection_+"&&"+catSelection+")",scaleUp_,prefix);
    std::pair<float,float> dataSSYSdb        = createHistogramAndShifts(dataFile_,"data_sdb","("+preSelection+"&&"+ssWSelection_+")",scaleUp_,prefix);


    std::pair<float,float> dataSSYieldSdb = convertToPoisson(dataSSYSdb);


    //shape creation for Fakes
    std::pair<float,float> dataFAKEControl = createHistogramAndShifts(dataFile_,"FAKES",qcdSelection_,scaleUp_,prefix);
    std::pair<float,float> ttFAKEControl = createHistogramAndShifts(topFile_,"TOPFAKES","("+qcdSelection_+"&&"+catSelection+")*"+weight_,luminosity_*muID_*eleID_,prefix);
    subtractHistogram(channel_+prefix,"FAKES","TOPFAKES");



    //Inflate the errors(note that currently there are only statistical on templates+ Add here the background estimates)
    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);

    std::pair<float,float> topInflSSYield  = inflateError(topSSYield,topErr_);
    printf("TTbar events in SS signal region = %f + %f \n",topInflSSYield.first,topInflSSYield.second);

    std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
    printf("Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);

    std::pair<float,float> vvInflSSYield  = inflateError(vvSSYield,vvErr_);
    printf("Diboson events in SS region = %f + %f \n",vvInflSSYield.first,vvInflSSYield.second);
    
    //Run ABCD Method
    printf("1. Subtract TTbar ,V+Jets and diboson from SS region");
    std::pair<float,float> C = std::make_pair(TMath::Nint(dataSSYield.first-topInflSSYield.first-vvInflSSYield.first-vSSYield.first),
						      sqrt(dataSSYield.second*dataSSYield.second+topInflSSYield.second*topInflSSYield.second+vvInflSSYield.second*vvInflSSYield.second+vSSYield.second*vSSYield.second));
    printf("SS FAKES  =%f -%f -%f  = %f +- %f \n",dataSSYield.first,topInflSSYield.first,vvInflSSYield.first,C.first,C.second);

    printf("ABCD Method---------------\n");
    printf("B: OS Anti-isolated = %f +- %f\n",dataYieldSdb.first,dataYieldSdb.second);
    printf("C: SS Isolated      = %f +- %f \n",C.first,C.second);
    printf("D: SS Anti-isolated  = %f +- %f \n",dataSSYieldSdb.first,dataSSYieldSdb.second);

    
    std::pair<float,float> A = std::make_pair((dataYieldSdb.first*C.first/dataSSYieldSdb.first),sqrt(pow(C.first*dataYieldSdb.second/dataSSYieldSdb.first,2)+
												     pow(dataYieldSdb.first*C.second/dataSSYieldSdb.first,2)+
												     pow(dataYieldSdb.first*C.first*dataSSYieldSdb.second/(dataSSYieldSdb.first*dataSSYieldSdb.first),2)));

    

    printf("QCD in Signal region = %f +- %f\n",A.first,A.second);

    printf("Add the other fakes from MC\n");
    std::pair<float,float> Fakes = std::make_pair(A.first+vYield.first+0.0001,sqrt(A.second*A.second+vYield.second*vYield.second));
    printf("Fakes in Signal region = %f +- %f\n",Fakes.first,Fakes.second);
    


      ///LATEX->Here since we want it for the note add all errors , even those that will go separate in the datacard
      printf("LATEX ------------------------------------\n");
      printf("Total & %.2f & %.2f  \\\\ \n", dataYield.first,  dataSSYieldSdb.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", vvInflYield.first, quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_), vvInflSSYield.first, quadrature(vvInflSSYield.first,vvInflSSYield.second,muIDErr_,eleIDErr_));
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f \\\\ \n", topInflYield.first,quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,topExtrapErr), topInflSSYield.first, quadrature(topInflSSYield.first,topInflSSYield.second,muIDErr_,eleIDErr_*topExtrapErr));
      printf("Fakes & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f \\\\ \n", Fakes.first, Fakes.second, C.first, C.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - \\\\ \n", zttYield.first,quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr));
      printf("Total Background & %.2f $\\pm$ %.2f &  - \\\\ \n",vvInflYield.first+topInflYield.first+Fakes.first+zttYield.first,sqrt(pow(quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_),2)+
										       pow(quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,topExtrapErr),2)+
										       pow(Fakes.second,2)+
										       pow(quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr),2)));

      output.DATA = dataYield.first;

      output.QCD = Fakes.first;
      output.dQCD = Fakes.second;

      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;

      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;


      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;
      


      renormalizeHistogram(channel_+prefix,"FAKES",Fakes.first);



      return output;
  }











  BkgOutput runFullExtrapolation(std::string preSelection,std::string categorySelection,std::string prefix, BkgOutput inclusive,float zExtrap,float zExtrapErr,float wExtrap,float wExtrapErr,float topExtrap,float topExtrapErr,std::string zShape_="",std::string wShape_="") {

    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;

      BkgOutput output;

      output.ZTTCORR=zExtrap;
      output.dZTTCORR=zExtrapErr;


    std::pair<float,float> zttYield       = createHistogramAndShifts(zttFile_,"ZTTTMP",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_*zExtrap,prefix,true);

    if(zShape_.size()==0) {
      std::pair<float,float> zttShape       = createHistogramAndShifts(zttFile_,"ZTT",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_*zExtrap,prefix,true);

    }
    else
      {

	printf("You have embedded samples.Calculating corrections on the fly overidding the crappy ones you gave me!\n");
	std::pair<float,float> zttShape       = createHistogramAndShifts(zShape_,"ZTT",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+")*__CORR__*__UNFOLD__*embeddedWeight/HLT_Any"),leg1Corr*tauID_,prefix,true);

	std::pair<float,float> zttShapePre    = createHistogramAndShifts(zShape_,"ZTTPre",("("+preSelection+"&&"+osSignalSelection_+")*__CORR__*__UNFOLD__*embeddedWeight/HLT_Any"),leg1Corr*tauID_,prefix,true);

	std::pair<float,float> zttYieldWCut   = createHistogramAndShifts(zttFile_,"ZTTTMP",("("+preSelection+"&&"+osSignalSelection_+"&&genTaus>0)*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_,prefix,false);

	float corr = zttShape.first/zttShapePre.first;
	double corrErr =max(TEfficiency::ClopperPearson((int)zttShapePre.first,(int)zttShape.first,0.68,true)-corr,corr-TEfficiency::ClopperPearson((int)zttShapePre.first,(int)zttShape.first,0.68,false));
	zttYield = std::make_pair(inclusive.ZTT*corr,inclusive.ZTT*corrErr);
	renormalizeHistogram(channel_+prefix,"ZTT",inclusive.ZTT*corr);
	output.ZTTCORR=corr;
	output.dZTTCORR=corrErr;
      }

    if(prefix=="_B")
      std::pair<float,float> topShape       = createHistogramAndShifts(topFile_,"TT",("("+relaxedSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix,true,false);
    else
      std::pair<float,float> topShape       = createHistogramAndShifts(topFile_,"TT",("("+relaxedSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix,true,true);

    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TTTMP",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);
    renormalizeHistogram(channel_+prefix,"TT",topYield.first);

    std::pair<float,float> topSSYield       = createHistogramAndShifts(topFile_,"TTSS",("("+preSelection+"&&"+categorySelection+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*topExtrap,prefix);

    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_,prefix,true,true);


      std::pair<float,float> zllShape      = createHistogramAndShifts(zttFile_,"ZLL",("("+preSelection_+"&&"+osSignalSelection_+"&&genTaus==0)*"+weight_),luminosity_*leg1Corr*zttScale_,prefix,false,false);


    std::pair<float,float> zllYield      = createHistogramAndShifts(zttFile_,"ZLTMP",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+"&&genTaus==0)*"+weight_),luminosity_*leg1Corr*zExtrap*zttScale_,prefix,false);
    zllYield=std::make_pair(zllYield.first,zllYield.first*sqrt( pow(zllShape.second/zllShape.first,2)+pow(zExtrapErr/zExtrap,2)));
    renormalizeHistogram(channel_+prefix,"ZLL",zllYield.first);

    std::pair<float,float> zllSSYield    = createHistogramAndShifts(zttFile_,"ZL_SS",("("+preSelection+"&&"+categorySelection+"&&"+ssSignalSelection_+"&&genTaus==0)*"+weight_),luminosity_*leg1Corr*zExtrap*zttScale_,prefix,false);

    
     if(wShape_.size()==0) {
       std::pair<float,float> wShape      = createHistogramAndShifts(wFile_,"W",("("+relaxedSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*wExtrap*inclusive.WCORR,prefix,false,true);
       }
     else
        {
	  std::pair<float,float> wShape      = createHistogramAndShifts(wShape_,"W",("("+relaxedSelection_+"&&"+categorySelection+")*"+weight_),luminosity_*leg1Corr*wExtrap*inclusive.WCORR,prefix,false,true);
	}


      std::pair<float,float> wYield      = createHistogramAndShifts(wFile_,"WTMP",("("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*wExtrap*inclusive.WCORR,prefix,false);

    //Trick:For W_SS yield use the OS/SS ratio as measured in inclusive for W
    std::pair<float,float> wSSYield = std::make_pair(wYield.first*inclusive.WSS/inclusive.W,wYield.second*inclusive.WSS/inclusive.W);
    //    std::pair<float,float> wSSYield     = createHistogramAndShifts(wFile_,"WSSTMP",("("+preSelection+"&&"+categorySelection+"&&"+ssSignalSelection_+")*"+weight_),luminosity_*leg1Corr*wExtrap*inclusive.WSSCORR,prefix);
    renormalizeHistogram(channel_+prefix,"W",wYield.first);

    std::pair<float,float> dataY         = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+categorySelection+"&&"+osSignalSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataYRounded  = std::make_pair(rintf(dataY.first),dataY.second);
    renormalizeHistogram(channel_+prefix,"data_obs",dataYRounded.first);
    std::pair<float,float> dataYield      = convertToPoisson(dataYRounded);
 
    std::pair<float,float> dataSSY          = createHistogramAndShifts(dataFile_,"data_obs_ss","("+preSelection+"&&"+categorySelection+"&&"+ssSignalSelection_+")",scaleUp_,prefix);
    std::pair<float,float> dataSSYield      = convertToPoisson(dataSSY);


    std::pair<float,float> dataQCDControl = createHistogramAndShifts(dataFile_,"QCD",qcdSelection_+"&&"+categorySelection,scaleUp_,prefix,false,true);
    std::pair<float,float> dataQCDControlInc = createHistogramAndShifts(dataFile_,"QCDC",qcdSelection_,scaleUp_,prefix,false,true);

    
    float qcdPass=dataQCDControl.first;
    float qcdAll=dataQCDControlInc.first;

	
    if(channel_=="eleTau"&&prefix!="_SM3") {
      std::pair<float,float> zllQCDControl = createHistogramAndShifts(zttFile_,"ZLLQCD","("+qcdSelection_+"&&"+categorySelection+"&&genTaus==0)*"+weight_,luminosity_*leg1Corr*zExtrap*zttScale_,prefix,false,true);
      std::pair<float,float> zllQCDControlInc = createHistogramAndShifts(zttFile_,"ZLLQCDC","("+qcdSelection_+"&&genTaus==0)*"+weight_,luminosity_*leg1Corr*zExtrap*zttScale_,prefix,false,true);

      qcdPass-=zllQCDControl.first;
      if(qcdPass<0) qcdPass=0.0001;
      qcdAll-=zllQCDControlInc.first;
      if(qcdAll<0) qcdAll=0.0001;
      subtractHistogram(channel_+prefix,"QCD","ZLLQCD");
      subtractHistogram(channel_+prefix,"QCDC","ZLLQCDC");
    }

    //Estimate QCD extrapolation factor
    float qcdFactor = qcdPass/qcdAll;
    float qcdFactorErr = TEfficiency::ClopperPearson(qcdAll,qcdPass,0.68,true)-qcdFactor; 

    std::pair<float,float> osQCD = std::make_pair(inclusive.QCD*qcdFactor,sqrt(inclusive.QCD*inclusive.QCD*qcdFactorErr*qcdFactorErr+qcdFactor*qcdFactor*inclusive.dQCD*inclusive.dQCD));
    

    //Inflate the errors
    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);

    std::pair<float,float> topInflSSYield  = inflateError(topSSYield,topErr_,topExtrapErr);
    printf("TTbar events in SS region = %f + %f \n",topInflSSYield.first,topInflSSYield.second);

    std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
    printf("Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);
    
    std::pair<float,float> zllInflYield  = inflateError(zllYield,zlftErr_,zjftErr_);
    printf("Z ->ll in signal region = %f + %f \n",zllInflYield.first,zllInflYield.second);

    std::pair<float,float> zllInflSSYield  = inflateError(zllSSYield,zjftErr_);
    printf("Z ->ll in SS region = %f + %f \n",zllInflSSYield.first,zllInflSSYield.second);

    std::pair<float,float> wInflYield  = inflateError(wYield,inclusive.dWCORR);
    printf("W in signal region = %f + %f \n",wInflYield.first,wInflYield.second);

    std::pair<float,float> wInflSSYield  = inflateError(wSSYield,inclusive.dWSSCORR,wExtrapErr);
    printf("W in SS region = %f + %f \n",wInflSSYield.first,wInflSSYield.second);


    //Estimate QCD!
      printf("OS QCD in  core  =%f *%f = %f +- %f \n",inclusive.QCD,qcdFactor,osQCD.first,osQCD.second);
           
      float background    = osQCD.first+wInflYield.first+topInflYield.first+vvInflYield.first+zllInflYield.first+zttYield.first;
      float backgroundErr = sqrt(osQCD.second*osQCD.second+wInflYield.second*wInflYield.second+topInflYield.second*topInflYield.second+vvInflYield.second*vvInflYield.second+zllInflYield.second*zllInflYield.second+zttYield.second*zttYield.second);
      printf("BACKGROUND=%f +-%f \n",background,backgroundErr);


      ///LATEX
      printf("LATEX ------------------------------------\n");

      printf("Total & %.2f  \\\\ \n", dataYield.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f  \\\\ \n", vvInflYield.first, quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_));
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f \\\\ \n", topInflYield.first,quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_,topExtrapErr));
      printf("$Zll & %.2f $\\pm$ %.2f  \\\\ \n", zllInflYield.first, quadrature(zllInflYield.first,zllInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr));
      printf("$W+jets$ & %.2f $\\pm$ %.2f   \\\\ \n", wInflYield.first, quadrature(wInflYield.first,wInflYield.second,wExtrapErr));
      printf("QCD & %.2f $\\pm$ %.2f \\\\ \n", osQCD.first, osQCD.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zttYield.first,quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_,zExtrapErr));
      float fullBackgroundErr = sqrt(pow(quadrature(vvInflYield.first,vvInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_),2)+
										       pow(quadrature(topInflYield.first,topInflYield.second,muIDErr_,eleIDErr_,tauIDErr_),2)+
										       pow(quadrature(zllInflYield.first,zllInflYield.second,muIDErr_,eleIDErr_,zttScaleErr_,zExtrapErr),2)+
										       pow(osQCD.second,2)+
										       pow(quadrature(wInflYield.first,wInflYield.second,wExtrapErr),2)+
				                                                       pow(quadrature(zttYield.first,zttYield.second,muIDErr_,eleIDErr_,zttScaleErr_,tauIDErr_,zExtrapErr),2));
      printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,fullBackgroundErr);



      //create a histogram with the error for plotting reasons and only
      TH1F *err = new TH1F("BKGErr","",1,0,1);
      err->SetBinContent(1,fullBackgroundErr/background);
      fout_->cd((channel_+prefix).c_str());
      err->Write();



      output.DATA = dataYield.first;
      output.W = wInflYield.first;
      output.dW = wInflYield.second;
      
      output.WSS = wInflSSYield.first;
      output.dWSS =wInflYield.second;
      
      output.QCD = osQCD.first;
      output.dQCD = osQCD.second;

      output.ZLFT = zllInflYield.first;
      output.dZLFT =zllInflYield.second;
      output.ZLFTSS = zllInflSSYield.first;
      output.dZLFTSS =zllInflSSYield.second;

      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;
      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;
      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;
      
      output.WCORR = inclusive.WCORR;
      output.dWCORR = inclusive.dWCORR;
      
      //now renormalize the data driven histograms
      renormalizeHistogram(channel_+prefix,"QCD",osQCD.first);

      return output;
  }





  void convertToCutAndCount(std::string dir,std::string histogram) {
    TH1F * h = (TH1F*) fout_->Get((dir+"/"+histogram).c_str());
    
     Double_t error=0.0;
     float yield = h->IntegralAndError(1,h->GetNbinsX(),error,"");

     for( int i=1;i<h->GetNbinsX();++i) {
       h->SetBinContent(i,10000.);
     }

     h->Scale(yield/h->Integral());

     fout_->cd(dir.c_str());
     h->Write("",TObject::kOverwrite);

  }




  std::pair<float,float> inflateError(std::pair<float,float> input,float error, float error2 =0.0, float error3 = 0.0 ) {
      float value = input.first;
      float err = sqrt(input.second*input.second+(input.first*error)*(input.first*error)+(input.first*error2)*(input.first*error2)+(input.first*error3)*(input.first*error3));
      
      if(err>value) {
	err=0.99*value;
	printf("Found error above value -> Setting error to value\n");
      }

      return std::make_pair(value,err);
    }



    std::pair<float,float> makeHistogram(TTree* tree,std::string folder,std::string name,std::string cut,float scaleFactor = 1.) {

   if(fout_->Get(folder.c_str())==0)
     fout_->mkdir(folder.c_str());
     TH1F *h=0;

     if(binning_.size()==0)
       h= new TH1F(name.c_str(),name.c_str(),bins_,min_,max_);
     else 
       h = new TH1F(name.c_str(),name.c_str(),binning_.size()-1,&binning_[0]);
     h->Sumw2();

     tree->Draw((variable_+">>"+name).c_str(),cut.c_str());

     h->Scale(scaleFactor);
     //     printf("Created Histogram %s with entries=%f\n",name.c_str(),h->Integral());
    fout_->cd(folder.c_str());
     h->Write();

     Double_t error=0.0;
     float yield = h->IntegralAndError(1,h->GetNbinsX(),error,"");
     return std::make_pair(yield,error);
  }


    std::pair<float,float> makeTHKeys(TTree* tree,std::string folder,std::string name,std::string cut,float scaleFactor = 1.) {

   if(fout_->Get(folder.c_str())==0)
     fout_->mkdir(folder.c_str());



     TH1Keys *h=0;

     if(binning_.size()==0)
       h= new TH1Keys("tmp","tmp",bins_,min_,max_,"a",0.5);
     else 
       h = new TH1Keys("tmp","tmp",binning_.size()-1,&binning_[0],"a",0.5);
     tree->Draw((variable_+">>tmp").c_str(),cut.c_str());
     
     if(h->Integral()==0.000) {
       printf("Keys for %s failed, retrying\n",name.c_str());
       delete h;
     if(binning_.size()==0)
       h= new TH1Keys("tmp","tmp",bins_,min_,max_,"a",0.5);
     else 
       h = new TH1Keys("tmp","tmp",binning_.size()-1,&binning_[0],"a",0.5);
     tree->Draw((variable_+">>tmp").c_str(),cut.c_str());

     if(h->Integral()==0.0) {
       printf("KEYS FAILED AGAIN \n");
       
     }
     }

     //now get the yield
     TH1F *hh=0;
     if(binning_.size()==0)
       hh= new TH1F("tmp2",name.c_str(),bins_,min_,max_);
     else 
       hh = new TH1F("tmp2",name.c_str(),binning_.size()-1,&binning_[0]);
     tree->Draw((variable_+">>tmp2").c_str(),cut.c_str());
     hh->Scale(scaleFactor);
     Double_t error=0.0;
     float yield = hh->IntegralAndError(1,hh->GetNbinsX(),error,"");
     
     fout_->cd(folder.c_str());
     TH1F * histo =(TH1F*) h->GetHisto();
     histo->Scale(yield/histo->Integral());
     histo->SetName(name.c_str());
     histo->Write();


     delete h;
     delete hh;

     return std::make_pair(yield,error);
  }


  void renormalizeHistogram(std::string folder, std::string histo, float yield)
  {
    
    TH1F * h =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    double scaleFactor = yield/h->Integral();


    h->Scale(scaleFactor);
    fout_->cd(folder.c_str());
    h->Write(h->GetName(),TObject::kOverwrite);

    for(unsigned int i=0;i<shifts_.size();++i) {
      TH1F * hh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Up").c_str());
      if(hh!=0) {
	hh->Scale(scaleFactor);
	fout_->cd(folder.c_str());
	hh->Write(hh->GetName(),TObject::kOverwrite);
      }
      else
	{
	  printf("Shift not found = %s\n",(folder+"/"+histo+"_"+shiftsPostFix_[i]+"Up").c_str());
	}


      TH1F * hhh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Down").c_str());
      if(hhh!=0) {
	hhh->Scale(scaleFactor);
	fout_->cd(folder.c_str());
	hhh->Write(hhh->GetName(),TObject::kOverwrite);
      }
      else
	{
	  printf("Shift not found\n");
	}


    }

  }

  void subtractHistogram(std::string folder, std::string histo1, std::string histo2)
  {
    TH1F * h1 =(TH1F*) fout_->Get((folder+"/"+histo1).c_str());
    TH1F * h2 =(TH1F*) fout_->Get((folder+"/"+histo2).c_str());
    h1->Add(h2,-1.);

    for(int i=1;i<h1->GetNbinsX();++i)
      if(h1->GetBinContent(i)<0)
	h1->SetBinContent(i,0.00001);

    fout_->cd(folder.c_str());
    h1->Write(h1->GetName(),TObject::kOverwrite);
  }

  void scaleHistogram(std::string folder, std::string histo, float scaleFactor)
  {
    TH1F * h =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    h->Scale(scaleFactor);
    fout_->cd(folder.c_str());
    h->Write(h->GetName(),TObject::kOverwrite);
    fout_->cd();
    for(unsigned int i=0;i<shifts_.size();++i) {
      TH1F * hh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Up").c_str());
      if(hh!=0) {

	hh->Scale(scaleFactor);
	fout_->cd(folder.c_str());
	hh->Write(hh->GetName(),TObject::kOverwrite);
	fout_->cd();

      }

      TH1F * hhh =(TH1F*) fout_->Get((folder+"/"+histo+"_"+shiftsPostFix_[i]+"Down").c_str());
      if(hhh!=0) {
	hhh->Scale(scaleFactor);
	fout_->cd(folder.c_str());
	hhh->Write(hhh->GetName(),TObject::kOverwrite);
	fout_->cd();
      }
      
    }
  }

  std::pair<float,float> convertToPoisson(std::pair<float,float> measurement) {
    float yield = measurement.first;
    float CLHi = TMath::ChisquareQuantile(1-0.32/2,2*yield+2)/2.;
    float CLLo = TMath::ChisquareQuantile(0.32/2,2*yield)/2.;
    printf("Yield =%f Lo=%f Hi=%f\n",measurement.first,CLLo,CLHi);
    return std::make_pair(measurement.first,(CLHi-CLLo)/2.);

  }

  std::pair<float,float> createHistogramAndShifts(std::string file,std::string name, std::string cut,float scaleFactor = 1, std::string postfix = "",bool normUC  = true, bool keys=false,bool ShapeUncertainty=true) {
    TFile *f  = new TFile(file.c_str());
    if(f==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *t= (TTree*)f->Get((channel_+"EventTree/eventTree").c_str());
    if(t==0) printf("Not Tree Found in file %s\n",file.c_str());

    std::pair<float,float> yield;

    if(!keys)
      yield =makeHistogram(t,channel_+postfix,name,cut,scaleFactor);
    else
      yield =makeTHKeys(t,channel_+postfix,name,cut,scaleFactor);




    //now the shifts
    std::pair<float,float> tmpYield;
    for(unsigned int i=0;i<shifts_.size();++i) {

      TTree *ts= (TTree*)f->Get((channel_+"EventTree"+shifts_[i]+"Up/eventTree").c_str());
      if(ts!=0) {
	if(!keys)
	  tmpYield = makeHistogram(ts,channel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",cut,scaleFactor);
	else
	  tmpYield = makeTHKeys(ts,channel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",cut,scaleFactor);

	if(!normUC)
	  scaleHistogram(channel_+postfix,name+"_"+shiftsPostFix_[i]+"Up",yield.first/tmpYield.first);

      }
      TTree *td= (TTree*)f->Get((channel_+"EventTree"+shifts_[i]+"Down/eventTree").c_str());
      if(td!=0) {
	if(!keys)
	  tmpYield = makeHistogram(td,channel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",cut,scaleFactor);
	else
	  tmpYield = makeTHKeys(td,channel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",cut,scaleFactor);

	if(!normUC)
	  scaleHistogram(channel_+postfix,name+"_"+shiftsPostFix_[i]+"Down",yield.first/tmpYield.first);

      }
    }
    f->Close();
    return yield;
  }




  void interpolate(std::string name1,std::string name2,std::string shiftFix,std::string postfix) {
    std::string sf;
    if(shiftFix.size()>0)
      sf="_"+shiftFix;
    else
      sf="";

    TH1F *f1 =(TH1F*) fout_->Get((channel_+postfix+"/SM"+name1+sf).c_str());
    TH1F *f2 =(TH1F*) fout_->Get((channel_+postfix+"/SM"+name2+sf).c_str());
    TH1F *f3 =(TH1F*) fout_->Get((channel_+postfix+"/VBF"+name1+sf).c_str());
    TH1F *f4 =(TH1F*) fout_->Get((channel_+postfix+"/VBF"+name2+sf).c_str());
    TH1F *f5 =(TH1F*) fout_->Get((channel_+postfix+"/VH"+name1+sf).c_str());
    TH1F *f6 =(TH1F*) fout_->Get((channel_+postfix+"/VH"+name2+sf).c_str());


      for(unsigned int j=1;j<5;++j) 
	{

	  double m1= boost::lexical_cast<double>(name1);
	  double m2= boost::lexical_cast<double>(name2);
	  int mint = boost::lexical_cast<int>(name1);


	  //interpolate yield
	  float yield1 =f1->Integral()+ (f2->Integral()-f1->Integral())*((float)(mint+j)-m1)/(m2-m1);
	  float yield2 =f3->Integral()+ (f4->Integral()-f3->Integral())*((float)(mint+j)-m1)/(m2-m1);
	  float yield3 =f5->Integral()+ (f6->Integral()-f5->Integral())*((float)(mint+j)-m1)/(m2-m1);

	  TH1F *ff1;
	  TH1F *ff2;
	  TH1F *ff3;

	  fout_->cd(TString::Format("%s",(channel_+postfix).c_str()));

	  
	  ff1 = th1fmorph(TString::Format("SM%d%s_temp",mint+j,sf.c_str()),"",f1,f2, m1,m2,m1+(float)j,yield1,0);
	  ff2 = th1fmorph(TString::Format("VBF%d%s_temp",mint+j,sf.c_str()),"",f3,f4,m1,m2,m1+(float)j,yield2,0);
	  ff3 = th1fmorph(TString::Format("VH%d%s_temp",mint+j,sf.c_str()),"",f5,f6,m1,m2,m1+(float)j,yield3,0);

	  TH1F * fff1;
  	  if(binning_.size()==0)
	    fff1= new TH1F(TString::Format("SM%d%s",mint+j,sf.c_str()),"",bins_,min_,max_);
	  else 
	    fff1 = new TH1F(TString::Format("SM%d%s",mint+j,sf.c_str()),"",binning_.size()-1,&binning_[0]);
	  fff1->Sumw2();

	  TH1F * fff2;
  
	  if(binning_.size()==0)
	    fff2= new TH1F(TString::Format("VBF%d%s",mint+j,sf.c_str()),"",bins_,min_,max_);
	  else 
	    fff2 = new TH1F(TString::Format("VBF%d%s",mint+j,sf.c_str()),"",binning_.size()-1,&binning_[0]);
	  fff2->Sumw2();

	  TH1F * fff3;
  
	  if(binning_.size()==0)
	    fff3= new TH1F(TString::Format("VH%d%s",mint+j,sf.c_str()),"",bins_,min_,max_);
	  else 
	    fff3 = new TH1F(TString::Format("VH%d%s",mint+j,sf.c_str()),"",binning_.size()-1,&binning_[0]);
	  fff3->Sumw2();


	  for(int k=1;k<=ff1->GetNbinsX();++k)
	    fff1->SetBinContent(k,ff1->GetBinContent(k));

	  for(int k=1;k<=ff2->GetNbinsX();++k)
	    fff2->SetBinContent(k,ff2->GetBinContent(k));

	  for(int k=1;k<=ff3->GetNbinsX();++k)
	    fff3->SetBinContent(k,ff3->GetBinContent(k));


	  fout_->cd((channel_+postfix).c_str());
	  fff1->Write(TString::Format("SM%d%s",mint+j,sf.c_str()));
 	  fff2->Write(TString::Format("VBF%d%s",mint+j,sf.c_str()));
 	  fff3->Write(TString::Format("VH%d%s",mint+j,sf.c_str()));
	  
	  fout_->cd();

	}

  }



  void interpolateHistogramAndShifts(std::string postfix = "") {
    for(unsigned int i=0;i<smMasses_.size()-1;++i) {
	interpolate(smMasses_[i],smMasses_[i+1],"",postfix);
	printf("Nominal interpolated\n");
	for(unsigned int j=0;j<shifts_.size();++j) {
	
	    interpolate(smMasses_[i],smMasses_[i+1],shiftsPostFix_[j]+"Up",postfix);
	    interpolate(smMasses_[i],smMasses_[i+1],shiftsPostFix_[j]+"Down",postfix);

	}
    }
  }



  void close() {
    fout_->Close();
  }




  std::pair<float,float> extractWFactor(std::string file,std::string preselection) {
    TFile *f  = new TFile (file.c_str());
    TTree *t = (TTree*)f->Get((channel_+"EventTree/eventTree").c_str());

    float high = (float)t->GetEntries((preselection+"&&"+osWSelection_).c_str());
    float low  = (float)t->GetEntries((preselection+"&&"+osSignalSelection_).c_str());

    float factor = low/high;
    float factorerrStat = factor*sqrt(1/high + 1/low);
    float factorerrSyst = factor*wFactorErr_;
    float factorErr = sqrt(factorerrStat*factorerrStat+factorerrSyst*factorerrSyst);

    return std::make_pair(factor,factorErr);   

  }


  float quadrature(float value, float error, float e0 = 0.0, float e1 = 0.0 ,float e2 = 0.0, float e3 = 0.0 ,float e4 = 0.0, float e5 = 0.0 ) {
    return sqrt(error*error+(e0*e0+e1*e1+e2*e2+e3*e3+e4*e4+e5*e5)*value*value);
  }

  float getYield(std::string name,std::string postFix) {
    TH1F *h = (TH1F*)fout_->Get((channel_+postFix+"/"+name).c_str());
    return h->Integral();
  }


  
  void copyHistogram(std::string folderSrc,std::string name,std::string folderDest) {
   if(fout_->Get(folderDest.c_str())==0)
     fout_->mkdir(folderDest.c_str());
   //check if it exists
   
   TH1F * h = (TH1F*)fout_->Get((folderSrc+"/"+name).c_str());
   if(h!=0) {
     TH1F *hC =(TH1F*) h->Clone();
     fout_->cd(folderDest.c_str());
     hC->Write();
   }
  }

  void copyHistograms(std::string folderSrc,std::string name,std::string folderDest) {
    copyHistogram(folderSrc,name,folderDest);
    for(unsigned int i=0;i<shifts_.size();++i) {
      copyHistogram(folderSrc,name+"_"+shiftsPostFix_[i]+"Up",folderDest);
      copyHistogram(folderSrc,name+"_"+shiftsPostFix_[i]+"Down",folderDest);
    }
  }

  std::pair<float,float> scaleYield(float value, float error , float factor, float factorErr) {
    float output = value*factor;
    float outputErr = sqrt(value*value*factorErr*factorErr+factor*factor*error*error);
    return std::make_pair(output,outputErr);
  }






  void printSignalEfficiency() {
    for(unsigned int i=0;i<mssmMasses_.size();++i) {
      //    printf("InclusiveGGH%s = %f\n",mssmMasses_[i].c_str(),getYield("GGH"+mssmMasses_[i],"_X")/((1-mssmBBFraction_[i])*luminosity_));
      //    printf("InclusiveBBH%s = %f\n",mssmMasses_[i].c_str(),getYield("BBH"+mssmMasses_[i],"_X")/((mssmBBFraction_[i])*luminosity_));

    printf("NoB  GGH%s = %f\n",mssmMasses_[i].c_str(),(getYield("GGHNoJet"+mssmMasses_[i],"_NoB")+getYield("GGHJet"+mssmMasses_[i],"_NoB"))/((1-mssmBBFraction_[i])*luminosity_));
    printf("NoB  BBH%s = %f\n",mssmMasses_[i].c_str(),(getYield("BBHNoJet"+mssmMasses_[i],"_NoB")+getYield("BBHJet"+mssmMasses_[i],"_NoB")+getYield("BBHBJet"+mssmMasses_[i],"_NoB"))/((mssmBBFraction_[i])*luminosity_));

    printf("B  GGH%s = %f\n",mssmMasses_[i].c_str(),(getYield("GGH"+mssmMasses_[i],"_B")+getYield("GGH"+mssmMasses_[i],"_B"))/((1-mssmBBFraction_[i])*luminosity_));
    printf("B  BBH%s = %f\n",mssmMasses_[i].c_str(),(getYield("BBH"+mssmMasses_[i],"_B")+getYield("BBH"+mssmMasses_[i],"_B"))/((mssmBBFraction_[i])*luminosity_));

  }

    //    printf("Standard Model-----------------------------\n");
    //  for(unsigned int i=0;i<smMasses_.size();++i) {
    //    printf("Inclusive GGH%s = %f\n",smMasses_[i].c_str(),getYield("SM"+smMasses_[i],"_X")/((smSigma_[i])*luminosity_));
    //    printf("Inclusive VBF%s = %f\n",smMasses_[i].c_str(),getYield("VBF"+smMasses_[i],"_X")/((vbfSigma_[i])*luminosity_));


    //    printf("No VBF GGH%s = %f\n",smMasses_[i].c_str(),getYield("SM"+smMasses_[i],"_SM0")/((smSigma_[i])*luminosity_));
    //    printf("No VBF VBF%s = %f\n",smMasses_[i].c_str(),getYield("VBF"+smMasses_[i],"_SM0")/((vbfSigma_[i])*luminosity_));
    //
    //    printf("VBF GGH%s = %f\n",smMasses_[i].c_str(),getYield("SM"+smMasses_[i],"_SM2")/((smSigma_[i])*luminosity_));
    //    printf(" VBF VBF%s = %f\n",smMasses_[i].c_str(),getYield("VBF"+smMasses_[i],"_SM2")/((vbfSigma_[i])*luminosity_));
    //  }
}



  void setBinning(const std::vector<double>& binning) {
    binning_ = binning;
  }


 private:
  std::string channel_;
  std::vector<std::string> shifts_;
  std::vector<std::string> shiftsPostFix_;

  //files
  TFile *fout_;
  std::string zttFile_;
  std::string zllFile_;
  std::string wFile_;
  std::string vvFile_;
  std::string topFile_;
  std::string dataFile_;
  ///////////////////////

  //selections of regions
  std::string preSelection_;
  std::string osSignalSelection_;
  std::string ssSignalSelection_;
  std::string osWSelection_;
  std::string ssWSelection_;
  std::string qcdSelection_;
  std::string bSelection_;
  std::string antibSelection_;
  std::string vbfSelection0_;
  std::string vbfSelection1_;
  std::string vbfSelection2_;
  std::string relaxedSelection_;

  //Luminosity and efficiency corrections
  float luminosity_;
  float luminosityErr_;
  float  muID_   ;      
  float muIDErr_;      
  float eleID_ ;       
  float eleIDErr_;     
  float tauID_  ;      
  float tauIDErr_;     
  float zttScale_;     
  float zttScaleErr_;  

  float scaleUp_;

  //histogram options
  std::string variable_;
  int bins_;
  float min_;
  float max_;
  std::vector<double> binning_;
  std::string weight_;

  //external parameters
  float topErr_;
  float vvErr_;
  float zlftErr_;
  float zlftFactor_;
  float zjftErr_;
  float wFactorErr_;
  float qcdFactor_;
  float qcdFactorErr_;


  float bFactorZ_;
  float bFactorZErr_;
  float bFactorW_;
  float bFactorWErr_;

  float vbfFactorZ_;
  float vbfFactorZErr_;
  float vbfFactorW_;
  float vbfFactorWErr_;


  float boostFactorZ_;
  float boostFactorZErr_;
  float boostFactorW_;
  float boostFactorWErr_;

  float vhFactorZ_;
  float vhFactorZErr_;
  float vhFactorW_;
  float vhFactorWErr_;


  float bID_;
  float bIDErr_;
  float bMisID_;
  float bMisIDErr_;

std::vector<std::string> mssmMasses_;
std::vector<std::string> smMasses_;
std::vector<std::string> smMassesDC_;

std::vector<float> mssmBBFraction_;
std::vector<float> smSigma_;
std::vector<float> vbfSigma_;
std::vector<float> vhSigma_;

std::string dir_;





};




