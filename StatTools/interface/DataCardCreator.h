#include "TCanvas.h"
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TChain.h"
#include "TH1.h"
#include "TF1.h"
#include "PhysicsTools/FWLite/interface/CommandLineParser.h" 
#include <math.h>


#include <TMath.h>

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


};



class DataCardCreator {
 public:

  DataCardCreator(optutl::CommandLineParser parser) {
    channel_ = parser.stringValue("channel");
    shifts_  = parser.stringVector("shifts");
    zttFile_ = parser.stringValue("zttFile");
    zllFile_ = parser.stringValue("zllFile");
    wFile_ = parser.stringValue("wFile");
    vvFile_ = parser.stringValue("vvFile");
    topFile_ = parser.stringValue("topFile");
    dataFile_ = parser.stringValue("dataFile");
    preSelection_ = parser.stringValue("preSelection");
    osSignalSelection_ = parser.stringValue("osSignalSelection");
    ssSignalSelection_ = parser.stringValue("ssSignalSelection");
    osWSelection_ = parser.stringValue("osWSelection");
    ssWSelection_ = parser.stringValue("ssWSelection");
    zlftSelection_ = parser.stringValue("zlftSelection");
    zjftSelection_ = parser.stringValue("zjftSelection");
    qcdSelection_ = parser.stringValue("qcdSelection");
    bSelection_ = parser.stringValue("bSelection");
    antibSelection_ = parser.stringValue("antibSelection");


    luminosity_ = parser.doubleValue("luminosity");
    muID_ = parser.doubleValue("muID");
    muIDErr_ = parser.doubleValue("muIDErr");
    bID_ = parser.doubleValue("bID");
    bIDErr_ = parser.doubleValue("bIDErr");
    bMisID_ = parser.doubleValue("bMisID");
    bMisIDErr_ = parser.doubleValue("bMisIDErr");
    bJecErr_ = parser.doubleValue("bJecErr");

    eleID_ = parser.doubleValue("eleID");
    eleIDErr_ = parser.doubleValue("eleIDErr");
    tauID_ = parser.doubleValue("tauID");
    tauIDErr_ = parser.doubleValue("tauIDErr");
    tauHLT_ = parser.doubleValue("tauHLT");
    tauHLTErr_ = parser.doubleValue("tauHLTErr");
    zttScale_ = parser.doubleValue("zttScale");
    zttScaleErr_ = parser.doubleValue("zttScaleErr");
    luminosityErr_ = parser.doubleValue("luminosityErr");

    variable_ = parser.stringValue("variable");
    weight_ = parser.stringValue("weight");
    bins_ = parser.integerValue("bins");
    min_ = parser.doubleValue("min");
    max_ = parser.doubleValue("max");
    binning_ = parser.doubleVector("binning");
    topErr_ = parser.doubleValue("topErr");
    vvErr_ = parser.doubleValue("vvErr");
    zlftErr_ = parser.doubleValue("zlftErr");
    zjftErr_ = parser.doubleValue("zjftErr");

    vbfErr_ = parser.doubleValue("vbfErr");
    vbfJecErr_ = parser.doubleValue("vbfJecErr");


    abcdCoeffs_ = parser.stringVector("abcdCoeffs");


    wFactorErr_ = parser.doubleValue("wFactorErr");



    qcdFactor_ = parser.doubleValue("qcdFactor");
    qcdFactorErr_ = parser.doubleValue("qcdFactorErr");
    bFactor1_ = parser.doubleValue("bFactor1");
    bFactorErr1_ = parser.doubleValue("bFactorErr1");
    bFactor2_ = parser.doubleValue("bFactor1");
    bFactorErr2_ = parser.doubleValue("bFactorErr1");

    vbfFactor1_ = parser.doubleValue("vbfFactor1");
    vbfFactorErr1_ = parser.doubleValue("vbfFactorErr1");
    vbfFactor2_ = parser.doubleValue("vbfFactor1");
    vbfFactorErr2_ = parser.doubleValue("vbfFactorErr1");


    dir_ = parser.stringValue("dir");

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


    smMasses_.push_back("115");

    smSigma_.push_back(1.394);
    vbfSigma_.push_back(0.102);


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
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauHLT_!=0)
	fprintf(pfile,"tauHLT   lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       tau HLT\n",
	       1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_);
      if(tauID_!=0)
	fprintf(pfile,"tauID    lnN   %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             -             0.5             0.5             0.5              0.5              0.5      shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd gmN   %d   -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"%s_dw     gmN %d   -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),(int)out.WSDB,out.WF);
    fprintf(pfile,"%s_dwSys lnN      -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),1+out.dWF/out.WF);
    fprintf(pfile,"%s_dzj1  lnN      -             -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dzl1  lnN      -             -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -             -             -             -             -             -              %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -             -             -              -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fclose(pfile);
    }
  
 

  }



  void makeSMLTauDataCardNoVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        SM%s        VBF%s        ZTT           QCD           W             ZJ            ZL            TT            VV\n",smMasses_[m].c_str(),smMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4             5             6             7\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("SM"+smMasses_[m],postfix),getYield("VBF"+smMasses_[m],postfix),out.ZTT,out.QCD,out.W,out.ZJFT,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -             -             -             -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauHLT_!=0)
	fprintf(pfile,"tauHLT   lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       tau HLT\n",
	       1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_);
      if(tauID_!=0)
	fprintf(pfile,"tauID    lnN   %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             -             0.5             0.5             0.5              0.5              0.5      shape\n",shifts_[j].c_str());

    fprintf(pfile,"%s_dqcd gmN   %d   -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"%s_dw     gmN %d   -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),(int)out.WSDB,out.WF);
    fprintf(pfile,"%s_dwSys lnN      -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),1+out.dWF/out.WF);
    fprintf(pfile,"%s_dzj1  lnN      -             -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dzl1  lnN      -             -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -             -             -             -             -             -              %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -             -             -              -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"jec     lnN      %.3f          %.3f          %.3f            -              %.3f        %.3f          %.3f          %.3f             %.3f    JEC for<2 jets \n",1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_);
    fprintf(pfile,"vbf     lnN       -            %.3f          -              -             -              -            -               -              -      VBF uncertainty \n",1-vbfErr_);

    fclose(pfile);
    }
  

  }


  void makeSMLTauDataCardVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        SM%s        VBF%s        ZTT           QCD           W             ZJ            ZL            TT            VV\n",smMasses_[m].c_str(),smMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4             5             6             7\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("SM"+smMasses_[m],postfix),getYield("VBF"+smMasses_[m],postfix),out.ZTT,out.QCD,out.W,out.ZJFT,out.ZLFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -             -             -             -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauHLT_!=0)
	fprintf(pfile,"tauHLT   lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       tau HLT\n",
	       1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_);
      if(tauID_!=0)
	fprintf(pfile,"tauID    lnN   %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    //    for(unsigned int j=0;j<shifts_.size();++j)
    //      fprintf(pfile,"%s    shape    1             1             1             -             1             1             1              1              1      shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd gmN %d      -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"%s_dw   lnN      -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),1+out.dW/out.W);
    fprintf(pfile,"%s_dzj1  lnN      -             -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dzl1  lnN      -             -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -             -             -             -             -             -              %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -             -             -              -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"jec     lnN      %.3f          %.3f          %.3f            -              %.3f        %.3f          %.3f          %.3f             %.3f    JEC for<2 jets \n",1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_);
    fprintf(pfile,"vbf     lnN      -             %.3f          -              -             -              -            -               -              -      VBF uncertainty \n",1+vbfErr_);

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
      fprintf(pfile,"bin            %s            %s            %s            %s            %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGH%s        BBH%s        ZTT           QCD            VJETS          TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4             5 \n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("GGH"+mssmMasses_[m],postfix),getYield("BBH"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.ZJFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -             -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -            %.3f          %.3f           %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauHLT_!=0)
	fprintf(pfile,"tauHLT   lnN   %.3f          %.3f          %.3f          -             %.3f             %.3f          %.3f       tau HLT\n",
	       1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_);
      if(tauID_!=0)
	fprintf(pfile,"tauID    lnN   %.3f          %.3f          %.3f          -             -            %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN    %.3f          %.3f          %.3f          -             %.3f           %.3f          %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -               -              -         -           ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             -             0.5             0.5             0.5           shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd      lnN      -             -             -             %.3f          -             -              -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"%s_dvjs    lnN      -             -             -             -             %.3f          -               -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dtt      lnN      -             -             -             -             -             %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv      lnN      -             -             -             -             -             -             %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
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
	fprintf(pfile,"lumi     lnN %.3f           %.3f          %3.f           %.3f           %.3f              -             -             -             -             -             -             -          luminosity\n",
		1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          %.3f           %.3f             %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	        1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauHLT_!=0)
	fprintf(pfile,"tauHLT   lnN   %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       tau HLT\n",
	       1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_);
      if(tauID_!=0)
	fprintf(pfile,"tauID    lnN   %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN   %.3f          %.3f          %.3f          %.3f          %.3f          %.3f             -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             -               -            -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             0.5             0.5             0.5             -             0.5             0.5             0.5              0.5              0.5      shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd gmN %d      -             -             -             -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"%s_dw   gmN %d      -             -             -             -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),(int)out.WSDB,out.WF);
    fprintf(pfile,"%s_dwSyst   lnN      -             -             -             -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),1+out.dWF/out.WF);

    fprintf(pfile,"%s_dzj1  lnN      -            -             -             -              -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dzl1  lnN      -             -            -            -               -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -            -             -              -              -             -             -             -             -              %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -              -             -             -             -             -              -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"bID      lnN      -             -             -             -             %.3f          -             -              -              -             -              %.3f           -    BTag efficiency \n",1-bIDErr_/bID_,1-bIDErr_/bID_);
    fprintf(pfile,"bMisID   lnN      -             %.3f          -             %.3f           -             -             -             -             -             -              -              -     BTag MisTag \n",1-bMisIDErr_/bMisID_,1-bMisIDErr_/bMisID_);
    fprintf(pfile,"JES      lnN      %.3f          %.3f         %.3f           %.3f           %.3f          -             -             -             -             -              -              -     JES in acceptance  \n",1-bJecErr_,1+bJecErr_,1-bJecErr_,1+bJecErr_,1+bJecErr_);



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
      fprintf(pfile,"bin            %s            %s             %s            %s             %s                 %s            %s            %s             %s           %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGHNoJet%s   GGHJet%s        BBHNoJet%s     BBHJet%s     BBHBJet%s           ZTT           QCD          VJETS          TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -4              -3           -2              -1            0                 1             2             3              4             5  \n");
      fprintf(pfile,"rate           %.3f            %.3f          %.3f         %.3f          %.3f             %.3f           %.3f          %.3f          %.3f            %.3f\n",
	      getYield("GGHNoJet"+mssmMasses_[m],postfix),getYield("GGHJet"+mssmMasses_[m],postfix),getYield("BBHNoJet"+mssmMasses_[m],postfix),getYield("BBHJet"+mssmMasses_[m],postfix),getYield("BBHBJet"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.ZJFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN %.3f           %.3f          %3.f           %.3f           %.3f              -             -             -               -             -          luminosity\n",
		1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_,1+luminosityErr_);
      
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          %.3f           %.3f             %.3f          -             -                %.3f          %.3f       muon ID /HLT\n",
	        1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(eleID_!=0)
	fprintf(pfile,"eleID    lnN   %.3f          %.3f          %.3f          %.3f          %.3f          %.3f             -             -                 %.3f           %.3f      Electron ID\n",
		1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             -               -            -                %.3f          -             -             %.3f          %.3f       ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape     0.5             0.5             0.5               0.5             0.5               0.5             -                0.5             0.5             0.5       shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd lnN      -             -             -               -             -               -             %.3f               -             -             -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"%s_dzj1  lnN      -            -             -             -              -             -             -                    %.3f          -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -            -             -              -              -             -                    -            %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -              -             -             -             -                   %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"bID      lnN      -             -             -             -             %.3f           -             -             -              %.3f                 -    BTag efficiency \n",1-bIDErr_/bID_,1-bIDErr_/bID_);
    fprintf(pfile,"bMisID   lnN      -             %.3f          -             %.3f           -             -             -             -              -                   -     BTag MisTag \n",1-bMisIDErr_/bMisID_,1-bMisIDErr_/bMisID_);
    fprintf(pfile,"JES      lnN      %.3f          %.3f         %.3f           %.3f           %.3f          -             -             -              -                    -     JES in acceptance  \n",1-bJecErr_,1+bJecErr_,1-bJecErr_,1+bJecErr_,1+bJecErr_);

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
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
      if(tauHLT_!=0)
	fprintf(pfile,"tauHLT   lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f          %.3f       tau HLT\n",
	       1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_,1+tauHLTErr_/tauHLT_);
      if(tauID_!=0)
	fprintf(pfile,"tauID    lnN   %.3f          %.3f          %.3f          -             -             -             -             %.3f          %.3f        Tau IDf\n",
	       1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_,1+tauIDErr_/tauID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN   %.3f          %.3f          %.3f          -             -             %.3f          %.3f          %.3f           %.3f      Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -             -             %.3f          %.3f          -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_,1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             -             0.5             0.5             0.5              0.5              0.5      shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd  gmN %d      -             -             -             %.3f          -             -             -              -              -      QCD Background\n",(channel_+postfix).c_str(),(int)out.QCDSDB,qcdFactor_);
    fprintf(pfile,"%s_dw    lnN      -             -             -             -             %.3f          -             -              -              -      W Backghround \n",(channel_+postfix).c_str(),1+out.dW/out.W);
    fprintf(pfile,"%s_dzj1  lnN      -             -             -             -             -             %.3f          -              -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dzl1  lnN      -             -             -             -             -             -             %.3f           -              -      Z(l->tau)   background\n",(channel_+postfix).c_str(),1+out.dZLFT/out.ZLFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -             -             -             -             -             -              %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -             -             -              -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"bID      lnN      -             %.3f          -             -             -             -             -              %.3f           -     BTag efficiency \n",1+bIDErr_/bID_,1+bIDErr_/bID_);
    fprintf(pfile,"bMisID   lnN      %.3f          -             -             -             -             -             -              -              -     BTag MisTag \n",1+bMisIDErr_/bMisID_);
    fprintf(pfile,"JES      lnN      %.3f          %.3f          -             -             -             -             -              -              -     JES in acceptance  \n",1+bJecErr_,1+bJecErr_);


    fclose(pfile);
    }

  }








  void makeSMEMuDataCardVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s             %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        SM%s        VBF%s        ZTT           QCD              VJETS            TT            VV\n",smMasses_[m].c_str(),smMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4              5\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("SM"+smMasses_[m],postfix),getYield("VBF"+smMasses_[m],postfix),out.ZTT,out.QCD,out.ZJFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -              -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -             -          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN     %.3f          %.3f          %.3f          -             -          %.3f          %.3f        Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -             -             -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             -             0.5             0.5              0.5      shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd  lnN      -             -             -             %.3f          -            -              -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"%s_dvj   lnN      -             -             -             -             %.3f         -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -             -             -             -            %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -            -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"jec      lnN     %.3f          %.3f          %.3f            -           %.3f          %.3f          %.3f    JEC for<2 jets \n",1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_);
    fprintf(pfile,"vbf     lnN      %.3f          -          -              -               -               -              -      VBF uncertainty \n",1+vbfErr_);
    fclose(pfile);
    }

  }

  void makeSMEMuDataCardNoVBF(BkgOutput out,std::string postfix) {
    for(unsigned int m = 0;m<smMasses_.size();++m) {
      FILE *pfile = fopen(("datacards/"+channel_+postfix+"_mH"+smMasses_[m]+".txt").c_str(),"w");

      fprintf(pfile,"imax 1\n");
      fprintf(pfile,"jmax *\n");
      fprintf(pfile,"kmax *\n");
      fprintf(pfile,"shapes *  *    %s  $CHANNEL/$PROCESS $CHANNEL/$PROCESS_$SYSTEMATIC \n",(channel_+"SM.root").c_str());
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      fprintf(pfile,"observation %d\n",(int)out.DATA);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      std::string ch = channel_+postfix;
      fprintf(pfile,"bin            %s            %s            %s            %s             %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        SM%s        VBF%s        ZTT           QCD              VJETS            TT            VV\n",smMasses_[m].c_str(),smMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4              5\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("SM"+smMasses_[m],postfix),getYield("VBF"+smMasses_[m],postfix),out.ZTT,out.QCD,out.ZJFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -              -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -             -          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN     %.3f          %.3f          %.3f          -             -          %.3f          %.3f        Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -             -             -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             -             0.5             0.5              0.5      shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd  lnN      -             -             -             %.3f          -            -              -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"%s_dvj   lnN      -             -             -             -             %.3f         -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -             -             -             -            %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -            -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"jec      lnN     %.3f          %.3f          %.3f            -           %.3f          %.3f          %.3f    JEC for<2 jets \n",1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_,1+vbfJecErr_);
    fprintf(pfile,"vbf     lnN      %.3f          -          -              -               -               -              -      VBF uncertainty \n",1-vbfErr_);
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
      fprintf(pfile,"bin            %s            %s            %s            %s             %s            %s            %s\n",ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str(),ch.c_str());
      fprintf(pfile,"process        GGH%s        BBH%s        ZTT           QCD              VJETS            TT            VV\n",mssmMasses_[m].c_str(),mssmMasses_[m].c_str());
      fprintf(pfile,"process        -1            0             1             2             3             4              5\n");
      fprintf(pfile,"rate           %.3f          %.3f          %.3f          %.3f          %.3f          %.3f          %.3f\n",
	     getYield("GGH"+mssmMasses_[m],postfix),getYield("BBH"+mssmMasses_[m],postfix),out.ZTT,out.QCD,out.ZJFT,out.TOP,out.VV);
      fprintf(pfile,"------------------------------------------------------------------------------------------------------------------------------------\n");
      if(luminosityErr_!=0)
	fprintf(pfile,"lumi     lnN   %.3f          %.3f          -             -              -             -             -          luminosity\n",
	   1+luminosityErr_,1+luminosityErr_);
      if(muID_!=0)
	fprintf(pfile,"muID     lnN   %.3f          %.3f          %.3f          -             -          %.3f          %.3f       muon ID /HLT\n",
	       1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_,1+muIDErr_/muID_);
    if(eleID_!=0)
      fprintf(pfile,"eleID    lnN     %.3f          %.3f          %.3f          -             -          %.3f          %.3f        Electron ID\n",
	     1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_,1+eleIDErr_/eleID_);
    if(zttScale_!=0)
      fprintf(pfile,"zttScale lnN   -             -             %.3f          -             -             -              -         ZTT Scale  \n",
	     1+zttScaleErr_/zttScale_);
    for(unsigned int j=0;j<shifts_.size();++j)
      fprintf(pfile,"%s    shape    0.5             0.5             0.5             -             0.5             0.5              0.5      shape\n",shifts_[j].c_str());
    fprintf(pfile,"%s_dqcd  lnN      -             -             -             %.3f          -            -              -      QCD Background\n",(channel_+postfix).c_str(),1+out.dQCD/out.QCD);
    fprintf(pfile,"%s_dvj   lnN      -             -             -             -             %.3f         -              -      Z(jet->tau) background\n",(channel_+postfix).c_str(),1+out.dZJFT/out.ZJFT);
    fprintf(pfile,"%s_dtt1  lnN      -             -             -             -             -            %.3f           -      TTbar background  \n",(channel_+postfix).c_str(),1+out.dTOP/out.TOP);
    fprintf(pfile,"%s_dvv1  lnN      -             -             -             -             -            -              %.3f   DiBoson background \n",(channel_+postfix).c_str(),1+out.dVV/out.dVV);
    fprintf(pfile,"bID      lnN      -             %.3f          -             -             -            %.3f           -     BTag efficiency \n",1+bIDErr_/bID_,1+bIDErr_/bID_);
    fprintf(pfile,"bMisID   lnN      %.3f          -             -             -             -            -              -     BTag MisTag \n",1+bMisIDErr_/bMisID_);
    fprintf(pfile,"JES      lnN      %.3f          %.3f          -             -             -            -              -     JES in acceptance  \n",1+bJecErr_,1+bJecErr_);

    fclose(pfile);
    }

  }





  float getYield(std::string name,std::string postFix) {
    TH1F *h = (TH1F*)fout_->Get((channel_+postFix+"/"+name).c_str());
    return h->Integral();
  }


  void makeHiggsShapes(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;
    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;


    for(unsigned int i=0;i<mssmMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*mssmBBFraction_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*(1.-mssmBBFraction_[i]),prefix);
    }

    for(unsigned int i=0;i<smMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"sm"+smMasses_[i]+".root","SM"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*smSigma_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"vbf"+smMasses_[i]+".root","VBF"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*vbfSigma_[i],prefix);
    }


  }


  void makeHiggsShapesSM(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;
    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;


    for(unsigned int i=0;i<smMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"sm"+smMasses_[i]+".root","SM"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*smSigma_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"vbf"+smMasses_[i]+".root","VBF"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*vbfSigma_[i],prefix);
    }
  }


  void makeHiggsShapesVBF(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;
    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;


    for(unsigned int i=0;i<smMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"sm"+smMasses_[i]+".root","SM"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*smSigma_[i],prefix);
      convertToCutAndCount(channel_+prefix,"SM"+smMasses_[i]);
      tmp= createHistogramAndShifts(dir_+"vbf"+smMasses_[i]+".root","VBF"+smMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_*vbfSigma_[i],prefix);
      convertToCutAndCount(channel_+prefix,"VBF"+smMasses_[i]);

    }
  }


  void makeHiggsShapesBTag(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;
    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;


    for(unsigned int i=0;i<mssmMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*bID_*tauID_*tauHLT_*mssmBBFraction_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGH"+mssmMasses_[i],("("+preselection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*bMisID_*tauHLT_*(1.-mssmBBFraction_[i]),prefix);
    }
  }


  void makeHiggsShapesNoBTag(std::string preselection,std::string prefix) {
    std::pair<float,float> tmp;
    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;


    for(unsigned int i=0;i<mssmMasses_.size();++i) {
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBHNoJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20==0&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*bID_*tauID_*tauHLT_*mssmBBFraction_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBHBJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20Matched>0&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*bID_*tauID_*tauHLT_*mssmBBFraction_[i],prefix);
      tmp= createHistogramAndShifts(dir_+"bbA"+mssmMasses_[i]+".root","BBHJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20NotMatched>0&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*bID_*tauID_*tauHLT_*mssmBBFraction_[i],prefix);

      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGHNoJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20==0&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*bMisID_*tauHLT_*(1.-mssmBBFraction_[i]),prefix);
      tmp= createHistogramAndShifts(dir_+"ggH"+mssmMasses_[i]+".root","GGHJet"+mssmMasses_[i],("("+preselection+"&&nTaggableJetsPt20>0&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*bMisID_*tauHLT_*(1.-mssmBBFraction_[i]),prefix);

    }
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



  BkgOutput runInclusive(std::string preSelection,std::string prefix) {

    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;



    std::pair<float,float> zttYield       = createHistogramAndShifts(zttFile_,"ZTT",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_*tauHLT_,prefix);
    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*leg1Corr*tauID_*tauHLT_,prefix);
    std::pair<float,float> topYieldSdb    = createHistogramAndShifts(topFile_,"TT_SDB",("("+preSelection+"&&"+osWSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_,prefix);
    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_,prefix);
    std::pair<float,float> vvYieldSdb     = createHistogramAndShifts(vvFile_,"VV_SDB",("("+preSelection+"&&"+osWSelection_+")*"+weight_),luminosity_*leg1Corr*tauID_*tauHLT_,prefix);
    std::pair<float,float> zlftYield      = createHistogramAndShifts(zllFile_,"ZL",("("+preSelection+"&&"+osSignalSelection_+"&&"+zlftSelection_+")*"+weight_),luminosity_*leg1Corr*tauHLT_*zttScale_,prefix);
    std::pair<float,float> zjftYield      = createHistogramAndShifts(zllFile_,"ZJ",("("+preSelection+"&&"+osSignalSelection_+"&&"+zjftSelection_+")*"+weight_),luminosity_*leg1Corr*tauHLT_*zttScale_,prefix);
    std::pair<float,float> zlftSSYield    = createHistogramAndShifts(zllFile_,"ZL_SS",("("+preSelection+"&&"+ssSignalSelection_+"&&"+zlftSelection_+")*"+weight_),luminosity_*leg1Corr*tauHLT_*zttScale_,prefix);
    std::pair<float,float> zjftSSYield    = createHistogramAndShifts(zllFile_,"ZJ_SS",("("+preSelection+"&&"+ssSignalSelection_+"&&"+zjftSelection_+")*"+weight_),luminosity_*leg1Corr*tauHLT_*zttScale_,prefix);
    std::pair<float,float> wMCYield       = createHistogramAndShifts(wFile_,"W",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*leg1Corr*tauHLT_,prefix);

    std::pair<float,float> dataY      = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+")",1.0,prefix);
    std::pair<float,float> dataYield      = convertToPoisson(dataY);
 
    std::pair<float,float> dataSSY          = createHistogramAndShifts(dataFile_,"data_obs_ss","("+preSelection+"&&"+ssSignalSelection_+")",1.0,prefix);
    std::pair<float,float> dataSSYield      = convertToPoisson(dataSSY);

    std::pair<float,float> dataYSdb     = createHistogramAndShifts(dataFile_,"data_obs_sdb","("+preSelection+"&&"+osWSelection_+")",1.0,prefix);
    std::pair<float,float> dataYieldSdb      = convertToPoisson(dataYSdb);

    std::pair<float,float> dataSSYSdb = createHistogramAndShifts(dataFile_,"data_obs_ss_sdb","("+preSelection+"&&"+ssWSelection_+")",1.0,prefix);
    std::pair<float,float> dataSSYieldSdb = convertToPoisson(dataSSYSdb);


    std::pair<float,float> dataQCDControl = createHistogramAndShifts(dataFile_,"QCD",qcdSelection_,1.0,prefix);

      //Inflate the errors
      std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
      printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);

      std::pair<float,float> topInflYieldSdb  = inflateError(topYieldSdb,topErr_);
      printf("TTbar events in sideband region = %f + %f \n",topYieldSdb.first,topInflYieldSdb.second);

      std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
      printf("Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);

      std::pair<float,float> vvInflYieldSdb  = inflateError(topYieldSdb,vvErr_);
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
      printf("W extrapolation factor = %f +- %f\n",wFactor.first,wFactor.second);

      

      //Run OS+LS + MT method
      printf("1. Subtract TTbar and diboson from sideband");
      std::pair<float,float> osWHigh = std::make_pair(TMath::Nint(dataYieldSdb.first-topInflYieldSdb.first-vvInflYieldSdb.first),
						      sqrt(dataYieldSdb.second*dataYieldSdb.second+topInflYieldSdb.second*topInflYieldSdb.second+vvInflYieldSdb.second*vvInflYieldSdb.second));
      printf("OS W in sideband  =%f -%f -%f  = %f +- %f \n",dataYieldSdb.first,topInflYieldSdb.first,vvInflYieldSdb.first,osWHigh.first,osWHigh.second);
     
      printf("2. Extrapolate W in the low MT region\n");
      std::pair<float,float> osWLow = std::make_pair(osWHigh.first*wFactor.first,
						     sqrt(osWHigh.first*osWHigh.first*wFactor.second*wFactor.second+osWHigh.second*osWHigh.second*wFactor.first*wFactor.first));
      
      printf("OS W  in core  =%f *%f  = %f +- %f \n",osWHigh.first,wFactor.first,osWLow.first,osWLow.second);
      
      printf("3. Repeat for SS : first extrapolate W\n");
      std::pair<float,float> ssWLow = std::make_pair(dataSSYieldSdb.first*wFactor.first,
						     sqrt(dataSSYieldSdb.second*dataSSYieldSdb.second*wFactor.first*wFactor.first+wFactor.second*wFactor.second*dataSSYieldSdb.first*dataSSYieldSdb.first));
      
      
      printf("4. From all SS events subtract W and Z jet fakes tau to get QCD ");
      std::pair<float,float> ssQCD = std::make_pair(TMath::Nint(dataSSYield.first-ssWLow.first-zlftInflSSYield.first-zjftInflSSYield.first),
						    sqrt(dataSSYield.second*dataSSYield.second+ssWLow.second*ssWLow.second+zlftInflSSYield.second*zlftInflSSYield.second+zjftInflSSYield.second*zjftInflSSYield.second));

      if(ssQCD.first<0) {
	ssQCD.first=0.0000001;
	ssQCD.second=1.8;
      }
      
      printf("SS QCD in  core  =%f -%f -%f -%f = %f +- %f \n",dataSSYield.first,ssWLow.first,zjftInflSSYield.first,zlftInflSSYield.first,ssQCD.first,ssQCD.second);
      
      printf("5. Extrapolate SS QCD -> OS QCD ");
      std::pair<float,float> osQCD = std::make_pair(ssQCD.first*qcdFactor_,sqrt(ssQCD.second*ssQCD.second*qcdFactor_*qcdFactor_+qcdFactorErr_*qcdFactorErr_*ssQCD.first*ssQCD.first));
     
      printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,qcdFactor_,osQCD.first,osQCD.second);
            
      float background    = osQCD.first+osWLow.first+topInflYield.first+vvInflYield.first+zlftInflYield.first+zjftInflYield.first+zttYield.first;
      float backgroundErr = sqrt(osQCD.second*osQCD.second+osWLow.second*osWLow.second+topInflYield.second*topInflYield.second+vvInflYield.second*vvInflYield.second+zlftInflYield.second*zlftInflYield.second+zjftInflYield.second*zjftInflYield.second+zttYield.second*zttYield.second);
      printf("BACKGROUND=%f +-%f \n",background,backgroundErr);



      ///LATEX
      printf("LATEX ------------------------------------\n");

      printf("Total & %.2f & %.2f & %.2f & %.2f \\\\ \n", dataYield.first, dataYieldSdb.first, dataSSYield.first, dataSSYieldSdb.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", vvInflYield.first, vvInflYield.second, vvInflYieldSdb.first, vvInflYieldSdb.second);
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & - & - \\\\ \n", topInflYield.first, topInflYield.second, topInflYieldSdb.first, topInflYieldSdb.second);
      printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zjftInflYield.first, zjftInflYield.second, zjftInflSSYield.first, zjftInflSSYield.second);
      printf("$Z^{ll}$ & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", zlftInflYield.first, zlftInflYield.second,zlftInflSSYield.first, zlftInflSSYield.second);
      printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", osWLow.first, osWLow.second, osWHigh.first, osWHigh.second, ssWLow.first, ssWLow.second, dataSSYieldSdb.first, dataSSYieldSdb.second);
      printf("QCD & %.2f $\\pm$ %.2f & - & %.2f $\\pm$ %.2f & - \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - & - & - \\\\ \n", zttYield.first, zttYield.second);
      printf("Total Background & %.2f $\\pm$ %.2f & - & - & - \\\\ \n",background,backgroundErr);

      BkgOutput output;

      output.DATA = dataYield.first;
      output.W = osWLow.first;
      output.dW = osWLow.second;
      output.WSDB = osWHigh.first;


      output.WSS = ssWLow.first;
      output.dWSS = ssWLow.second;
      
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

      

      //now renormalize the data driven histograms
      renormalizeHistogram(channel_+prefix,"QCD",osQCD.first);
      renormalizeHistogram(channel_+prefix,"W",osWLow.first);


      return output;
  }








  BkgOutput runEMu(std::string preSelection,std::string prefix) {

    std::pair<float,float> zttYield       = createHistogramAndShifts(zttFile_,"ZTT",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*muID_*eleID_,prefix);
    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*muID_*eleID_,prefix);
    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*muID_*eleID_,prefix);
    std::pair<float,float> vjetsYield     = createHistogramAndShifts(zllFile_,"VJETS",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*muID_*eleID_*zttScale_,prefix);
    std::pair<float,float> qcdYield       = abcdMethod(dataFile_,preSelection,preSelection);
    std::pair<float,float> dataQCDControl = createHistogramAndShifts(dataFile_,"QCD",qcdSelection_,1.0,prefix);
    renormalizeHistogram(channel_+prefix,"QCD",qcdYield.first);

    std::pair<float,float> dataY          = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+")",1.0,prefix);
    std::pair<float,float> dataYield      = convertToPoisson(dataY);
    

      //Inflate the errors
    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);

    std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);
    printf("Diboson events in signal region = %f + %f \n",vvInflYield.first,vvInflYield.second);

    std::pair<float,float> vjetsInflYield  = inflateError(vjetsYield,zjftErr_);
    printf("V+jets  in signal region = %f + %f \n",vjetsInflYield.first,vjetsInflYield.second);


    float background = vvInflYield.first+topInflYield.first+vjetsInflYield.first+qcdYield.first+zttYield.first;
    float backgroundErr =sqrt( vvInflYield.second*vvInflYield.second+
			       topInflYield.second*topInflYield.second+
			       vjetsInflYield.second*vjetsInflYield.second+
			       qcdYield.second*qcdYield.second+
			       zttYield.second*zttYield.second);

      ///LATEX
      printf("LATEX ------------------------------------\n");

      printf("Total & %.2f \\\\ \n", dataYield.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f \\\\ \n", vvInflYield.first, vvInflYield.second);
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f \\\\ \n", topInflYield.first, topInflYield.second);
      printf("$V+jets$ & %.2f $\\pm$ %.2f  \\\\ \n", vjetsInflYield.first, vjetsInflYield.second);
      printf("QCD & %.2f $\\pm$ %.2f \\\\ \n", qcdYield.first,qcdYield.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f \\\\ \n", zttYield.first, zttYield.second);
      printf("Total Background & %.2f $\\pm$ %.2f  \\\\ \n",background,backgroundErr);
      BkgOutput output;

      output.DATA = dataYield.first;

      
      output.QCD = qcdYield.first;
      output.dQCD = qcdYield.second;
      output.ZJFT = vjetsInflYield.first;
      output.dZJFT =vjetsInflYield.second;
      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;
      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;
      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;

      return output;
  }






  BkgOutput runEMuBTagged(BkgOutput inclusive, std::string prePreSelection,std::string bSelection,std::string prefix,std::string postfix) {

    std::string preSelection = prePreSelection+"&&"+bSelection;

    copyHistograms(channel_+prefix,"ZTT",channel_+postfix);
    copyHistograms(channel_+prefix,"VJETS",channel_+postfix);
    copyHistograms(channel_+prefix,"QCD",channel_+postfix);

    scaleHistogram(channel_+postfix,"ZTT",bFactor1_);
    scaleHistogram(channel_+postfix,"VJETS",bFactor1_);


    //scale the yields
    std::pair<float,float> zttYield =scaleYield(inclusive.ZTT,inclusive.dZTT,bFactor1_,bFactorErr1_);
    std::pair<float,float> vjetsYield =scaleYield(inclusive.ZJFT,inclusive.dZJFT,bFactor2_,bFactorErr2_);

    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*muID_*bID_*eleID_,postfix);
    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*muID_*eleID_*bID_,postfix);

    std::pair<float,float> qcdYield       = abcdMethod(dataFile_,prePreSelection,bSelection);
    renormalizeHistogram(channel_+postfix,"QCD",qcdYield.first);

    std::pair<float,float> dataY       = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+")",1.0,postfix);
    std::pair<float,float> dataYield   = convertToPoisson(dataY);


      //Inflate the errors
    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);



    float background = vvInflYield.first+topInflYield.first+vjetsYield.first+qcdYield.first+zttYield.first;
    float backgroundErr =sqrt( vvInflYield.second*vvInflYield.second+
			       topInflYield.second*topInflYield.second+
			       vjetsYield.second*vjetsYield.second+
			       qcdYield.second*qcdYield.second+
			       zttYield.second*zttYield.second);

      ///LATEX
      printf("LATEX ------------------------------------\n");

      printf("Total & %.2f \\\\ \n", dataYield.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f \\\\ \n", vvInflYield.first, vvInflYield.second);
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f \\\\ \n", topInflYield.first, topInflYield.second);
      printf("$V+jets$ & %.2f $\\pm$ %.2f  \\\\ \n", vjetsYield.first, vjetsYield.second);
      printf("QCD & %.2f $\\pm$ %.2f \\\\ \n", qcdYield.first,qcdYield.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f \\\\ \n", zttYield.first, zttYield.second);
      printf("Total Background & %.2f $\\pm$ %.2f  \\\\ \n",background,backgroundErr);
      BkgOutput output;

      output.DATA = dataYield.first;
     
      output.QCD = qcdYield.first;
      output.dQCD = qcdYield.second;
      output.ZJFT = vjetsYield.first;
      output.dZJFT =vjetsYield.second;
      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;
      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;
      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;

      return output;
  }





  BkgOutput runEMuVBF(BkgOutput inclusive, std::string prePreSelection,std::string bSelection,std::string prefix,std::string postfix) {

    std::string preSelection = prePreSelection+"&&"+bSelection;

    copyHistograms(channel_+prefix,"ZTT",channel_+postfix);
    copyHistograms(channel_+prefix,"VJETS",channel_+postfix);
    copyHistograms(channel_+prefix,"QCD",channel_+postfix);

    scaleHistogram(channel_+postfix,"ZTT",vbfFactor1_);
    scaleHistogram(channel_+postfix,"VJETS",vbfFactor1_);


    //scale the yields
    std::pair<float,float> zttYield =scaleYield(inclusive.ZTT,inclusive.dZTT,vbfFactor1_,vbfFactorErr1_);
    std::pair<float,float> vjetsYield =scaleYield(inclusive.ZJFT,inclusive.dZJFT,vbfFactor2_,vbfFactorErr2_);

    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*muID_*eleID_,postfix);
    std::pair<float,float> vvYield        = createHistogramAndShifts(vvFile_,"VV",("("+preSelection+"&&"+osSignalSelection_+")*"+weight_),luminosity_*zttScale_*muID_*eleID_,postfix);

    std::pair<float,float> qcdYield       = abcdMethod(dataFile_,prePreSelection,bSelection);
    renormalizeHistogram(channel_+postfix,"QCD",qcdYield.first);

    std::pair<float,float> dataY          = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+")",1.0,postfix);
    std::pair<float,float> dataYield      = convertToPoisson(dataY);


      //Inflate the errors
    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    std::pair<float,float> vvInflYield  = inflateError(vvYield,vvErr_);



    float background = vvInflYield.first+topInflYield.first+vjetsYield.first+qcdYield.first+zttYield.first;
    float backgroundErr =sqrt( vvInflYield.second*vvInflYield.second+
			       topInflYield.second*topInflYield.second+
			       vjetsYield.second*vjetsYield.second+
			       qcdYield.second*qcdYield.second+
			       zttYield.second*zttYield.second);

      ///LATEX
      printf("LATEX ------------------------------------\n");

      printf("Total & %.2f \\\\ \n", dataYield.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f \\\\ \n", vvInflYield.first, vvInflYield.second);
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f \\\\ \n", topInflYield.first, topInflYield.second);
      printf("$V+jets$ & %.2f $\\pm$ %.2f  \\\\ \n", vjetsYield.first, vjetsYield.second);
      printf("QCD & %.2f $\\pm$ %.2f \\\\ \n", qcdYield.first,qcdYield.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f \\\\ \n", zttYield.first, zttYield.second);
      printf("Total Background & %.2f $\\pm$ %.2f  \\\\ \n",background,backgroundErr);
      BkgOutput output;

      output.DATA = dataYield.first;
     
      output.QCD = qcdYield.first;
      output.dQCD = qcdYield.second;
      output.ZJFT = vjetsYield.first;
      output.dZJFT =vjetsYield.second;
      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;
      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;
      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;

      return output;
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
      copyHistogram(folderSrc,name+"_"+shifts_[i]+"Up",folderDest);
      copyHistogram(folderSrc,name+"_"+shifts_[i]+"Down",folderDest);
    }
  }

  std::pair<float,float> scaleYield(float value, float error , float factor, float factorErr) {
    float output = value*factor;
    float outputErr = sqrt(value*value*factorErr*factorErr+factor*factor*error*error);
    return std::make_pair(output,outputErr);
  }

  BkgOutput runBTag(BkgOutput inclusive,std::string preSelection,std::string prefix, std::string postfix) {

    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;

    //lets copy the histograms we want 
    copyHistograms(channel_+prefix,"ZTT",channel_+postfix);
    copyHistograms(channel_+prefix,"ZL",channel_+postfix);
    copyHistograms(channel_+prefix,"ZJ",channel_+postfix);
    copyHistograms(channel_+prefix,"W",channel_+postfix);
    copyHistograms(channel_+prefix,"QCD",channel_+postfix);

    scaleHistogram(channel_+postfix,"ZTT",bFactor1_);
    scaleHistogram(channel_+postfix,"ZL",bFactor1_);
    scaleHistogram(channel_+postfix,"ZJ",bFactor2_);
    scaleHistogram(channel_+postfix,"W",bFactor2_);

    //scale the yields
    std::pair<float,float> zttYield =scaleYield(inclusive.ZTT,inclusive.dZTT,bFactor1_,bFactorErr1_);
    std::pair<float,float> zlftYield =scaleYield(inclusive.ZLFT,inclusive.dZLFT,bFactor1_,bFactorErr1_);
    std::pair<float,float> zjftYield =scaleYield(inclusive.ZJFT,inclusive.dZJFT,bFactor2_,bFactorErr2_);
    std::pair<float,float> zlftSSYield =scaleYield(inclusive.ZLFTSS,inclusive.dZLFTSS,bFactor1_,bFactorErr1_);
    std::pair<float,float> zjftSSYield =scaleYield(inclusive.ZJFTSS,inclusive.dZJFTSS,bFactor2_,bFactorErr2_);

    std::pair<float,float> wYield =scaleYield(inclusive.W,inclusive.dW,bFactor1_,bFactorErr1_);
    std::pair<float,float> wSSYield =scaleYield(inclusive.WSS,inclusive.dWSS,bFactor1_,bFactorErr1_);

    //Top is treated differently
    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT","("+preSelection+"&&"+osSignalSelection_+")*"+weight_,luminosity_*leg1Corr*tauID_*bID_*tauHLT_,postfix);
    std::pair<float,float> topSSYield     = createHistogramAndShifts(topFile_,"TT_SS","("+preSelection+"&&"+ssSignalSelection_+")*"+weight_,luminosity_*leg1Corr*tauID_*bID_*tauHLT_,postfix);

    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);
    std::pair<float,float> topInflSSYield  = inflateError(topSSYield,topErr_);
    printf("TTbar events in SS region = %f + %f \n",topInflSSYield.first,topInflSSYield.second);

    std::pair<float,float> vvYield       = createHistogramAndShifts(vvFile_,"VV","("+preSelection+"&&"+osSignalSelection_+")*"+weight_,luminosity_*leg1Corr*tauID_*tauHLT_,postfix);
    std::pair<float,float> vvInflYield   = inflateError(vvYield,vvErr_);




    //create the data histograms
    std::pair<float,float> dataY      = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+")",1.0,postfix);
    std::pair<float,float> dataYield   = convertToPoisson(dataY);

    std::pair<float,float> dataSSY    = createHistogramAndShifts(dataFile_,"data_obs_ss","("+preSelection+"&&"+ssSignalSelection_+")",1.0,postfix);
    std::pair<float,float> dataSSYield   = convertToPoisson(dataSSY);


    //Run OS+LS + MT method
    
      printf("1. From SS events remove TTbar and Z+jets and W \n");
      std::pair<float,float> ssQCD = std::make_pair(TMath::Nint(dataSSYield.first-zlftSSYield.first-zjftSSYield.first-topInflSSYield.first-wSSYield.first),
						    sqrt(dataSSYield.second*dataSSYield.second+zlftSSYield.second*zlftSSYield.second-zjftSSYield.second*zjftSSYield.second+topInflSSYield.second*topInflSSYield.second+wSSYield.second*wSSYield.second));

      if(ssQCD.first<0) {
	ssQCD.first=0.000001;
	ssQCD.second=1.83;
      }

      printf("5. Extrapolate SS QCD -> OS QCD ");
      std::pair<float,float> osQCD = std::make_pair(ssQCD.first*qcdFactor_,sqrt(ssQCD.second*ssQCD.second*qcdFactor_*qcdFactor_+qcdFactorErr_*qcdFactorErr_*ssQCD.first*ssQCD.first));
      printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,qcdFactor_,osQCD.first,osQCD.second);

           
      float background    = osQCD.first+wYield.first+topInflYield.first+vvInflYield.first+zlftYield.first+zjftYield.first+zttYield.first;
      float backgroundErr = sqrt(osQCD.second*osQCD.second+wYield.second*wYield.second+topInflSSYield.second*topInflSSYield.second+vvInflYield.second*vvInflYield.second+zlftYield.second*zlftYield.second+zjftYield.second*zjftYield.second+zttYield.second*zttYield.second);
      printf("BACKGROUND=%f +-%f \n",background,backgroundErr);

      renormalizeHistogram(channel_+postfix,"QCD",osQCD.first);


      ///LATEX
      printf("LATEX ------------------------------------\n");

      printf("Total & %.2f & %.2f \\\\ \n", dataYield.first,dataSSYield.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f & -  \\\\ \n", vvInflYield.first, vvInflYield.second);
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", topInflYield.first, topInflYield.second, topInflSSYield.first, topInflSSYield.second);
      printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f  \\\\ \n", zjftYield.first, zjftYield.second, zjftSSYield.first, zjftSSYield.second);
      printf("$Z^{ll}$ & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f  \\\\ \n", zlftYield.first, zlftYield.second,zlftSSYield.first, zlftSSYield.second);
      printf("$W+jets$ & %.2f $\\pm$ %.2f &%.2f $\\pm$ %.2f    \\\\ \n", wYield.first, wYield.second,wSSYield.first,wSSYield.second);
      printf("QCD & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f  \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - \\\\ \n", zttYield.first, zttYield.second);
      printf("Total Background & %.2f $\\pm$ %.2f & - \\\\ \n",background,backgroundErr);
      BkgOutput output;

      output.DATA = dataYield.first;
      output.W = wYield.first;
      output.dW = wYield.second;
      output.QCD = osQCD.first;
      output.dQCD = osQCD.second;
      output.QCDSDB = ssQCD.first;
      output.ZLFT = zlftYield.first;
      output.dZLFT =zlftYield.second;
      output.ZLFTSS = zlftSSYield.first;
      output.dZLFTSS =zlftSSYield.second;

      output.ZJFT = zjftYield.first;
      output.dZJFT =zjftYield.second;
      output.ZJFTSS = zjftSSYield.first;
      output.dZJFTSS =zjftSSYield.second;
  
      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;
      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;
      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;

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




  BkgOutput runVBF(BkgOutput inclusive,std::string preSelection,std::string prefix, std::string postfix) {

    float leg1Corr=1.0;
    if(muID_!=0) leg1Corr*=muID_;
    if(eleID_!=0) leg1Corr*=eleID_;

    //lets copy the histograms we want 
    copyHistograms(channel_+prefix,"ZTT",channel_+postfix);
    copyHistograms(channel_+prefix,"ZL",channel_+postfix);
    copyHistograms(channel_+prefix,"ZJ",channel_+postfix);
    copyHistograms(channel_+prefix,"W",channel_+postfix);
    copyHistograms(channel_+prefix,"QCD",channel_+postfix);

    scaleHistogram(channel_+postfix,"ZTT",vbfFactor1_);
    scaleHistogram(channel_+postfix,"ZL",vbfFactor1_);
    scaleHistogram(channel_+postfix,"ZJ",vbfFactor2_);
    scaleHistogram(channel_+postfix,"W",vbfFactor2_);


    convertToCutAndCount(channel_+postfix,"ZTT");
    convertToCutAndCount(channel_+postfix,"ZL");
    convertToCutAndCount(channel_+postfix,"ZJ");
    convertToCutAndCount(channel_+postfix,"W");
    convertToCutAndCount(channel_+postfix,"QCD");


    //scale the yields
    std::pair<float,float> zttYield =scaleYield(inclusive.ZTT,inclusive.dZTT,vbfFactor1_,vbfFactorErr1_);
    std::pair<float,float> zlftYield =scaleYield(inclusive.ZLFT,inclusive.dZLFT,vbfFactor1_,vbfFactorErr1_);
    std::pair<float,float> zjftYield =scaleYield(inclusive.ZJFT,inclusive.dZJFT,vbfFactor2_,vbfFactorErr2_);
    std::pair<float,float> zlftSSYield =scaleYield(inclusive.ZLFTSS,inclusive.dZLFTSS,vbfFactor1_,vbfFactorErr1_);
    std::pair<float,float> zjftSSYield =scaleYield(inclusive.ZJFTSS,inclusive.dZJFTSS,vbfFactor2_,vbfFactorErr2_);

    std::pair<float,float> wYield =scaleYield(inclusive.W,inclusive.dW,vbfFactor1_,vbfFactorErr1_);
    std::pair<float,float> wSSYield =scaleYield(inclusive.WSS,inclusive.dWSS,vbfFactor1_,vbfFactorErr1_);

    //Top is treated differently
    std::pair<float,float> topYield       = createHistogramAndShifts(topFile_,"TT","("+preSelection+"&&"+osSignalSelection_+")*"+weight_,luminosity_*leg1Corr*tauID_*bID_*tauHLT_,postfix);
    std::pair<float,float> topSSYield     = createHistogramAndShifts(topFile_,"TT_SS","("+preSelection+"&&"+ssSignalSelection_+")*"+weight_,luminosity_*leg1Corr*tauID_*bID_*tauHLT_,postfix);
    convertToCutAndCount(channel_+postfix,"TT");


    std::pair<float,float> topInflYield  = inflateError(topYield,topErr_);
    printf("TTbar events in signal region = %f + %f \n",topInflYield.first,topInflYield.second);
    std::pair<float,float> topInflSSYield  = inflateError(topSSYield,topErr_);
    printf("TTbar events in SS region = %f + %f \n",topInflSSYield.first,topInflSSYield.second);



    std::pair<float,float> vvYield       = createHistogramAndShifts(vvFile_,"VV","("+preSelection+"&&"+osSignalSelection_+")*"+weight_,luminosity_*leg1Corr*tauID_*tauHLT_,postfix);
    convertToCutAndCount(channel_+postfix,"VV");

    std::pair<float,float> vvInflYield   = inflateError(vvYield,vvErr_);




    //create the data histograms
    std::pair<float,float> dataY      = createHistogramAndShifts(dataFile_,"data_obs","("+preSelection+"&&"+osSignalSelection_+")",1.0,postfix);
    std::pair<float,float> dataYield   = convertToPoisson(dataY);

    std::pair<float,float> dataSSY        = createHistogramAndShifts(dataFile_,"data_obs_ss","("+preSelection+"&&"+ssSignalSelection_+")",1.0,postfix);
    std::pair<float,float> dataSSYield    = convertToPoisson(dataSSY);

    convertToCutAndCount(channel_+postfix,"data_obs");

    //Run OS+LS + MT method
    
      printf("1. From SS events remove TTbar and Z+jets and W \n");
      std::pair<float,float> ssQCD = std::make_pair(TMath::Nint(dataSSYield.first-zlftSSYield.first-zjftSSYield.first-topInflSSYield.first-wSSYield.first),
						    sqrt(dataSSYield.second*dataSSYield.second+zlftSSYield.second*zlftSSYield.second-zjftSSYield.second*zjftSSYield.second+topInflSSYield.second*topInflSSYield.second+wSSYield.second*wSSYield.second));

      if(ssQCD.first<0) {
	ssQCD.first=0.000001;
	ssQCD.second=1.83;
      }


      printf("5. Extrapolate SS QCD -> OS QCD ");
      std::pair<float,float> osQCD = std::make_pair(ssQCD.first*qcdFactor_,sqrt(ssQCD.second*ssQCD.second*qcdFactor_*qcdFactor_+qcdFactorErr_*qcdFactorErr_*ssQCD.first*ssQCD.first));
      printf("OS QCD in  core  =%f *%f = %f +- %f \n",ssQCD.first,qcdFactor_,osQCD.first,osQCD.second);

           
      float background    = osQCD.first+wYield.first+topInflYield.first+vvInflYield.first+zlftYield.first+zjftYield.first+zttYield.first;
      float backgroundErr = sqrt(osQCD.second*osQCD.second+wYield.second*wYield.second+topInflSSYield.second*topInflSSYield.second+vvInflYield.second*vvInflYield.second+zlftYield.second*zlftYield.second+zjftYield.second*zjftYield.second+zttYield.second*zttYield.second);
      printf("BACKGROUND=%f +-%f \n",background,backgroundErr);

      renormalizeHistogram(channel_+postfix,"QCD",osQCD.first);


      ///LATEX
      printf("LATEX ------------------------------------\n");

      printf("Total & %.2f & %.2f \\\\ \n", dataYield.first,dataSSYield.first);
      printf("Di-Boson & %.2f $\\pm$ %.2f & -  \\\\ \n", vvInflYield.first, vvInflYield.second);
      printf("$t\\bar{t}$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f  \\\\ \n", topInflYield.first, topInflYield.second, topInflSSYield.first, topInflSSYield.second);
      printf("$Z^{l+jet}$ & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f  \\\\ \n", zjftYield.first, zjftYield.second, zjftSSYield.first, zjftSSYield.second);
      printf("$Z^{ll}$ & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f  \\\\ \n", zlftYield.first, zlftYield.second,zlftSSYield.first, zlftSSYield.second);
      printf("$W+jets$ & %.2f $\\pm$ %.2f & %.2f $\\pm$ %.2f    \\\\ \n", wYield.first, wYield.second,wSSYield.first,wSSYield.second);
      printf("QCD & %.2f $\\pm$ %.2f &  %.2f $\\pm$ %.2f  \\\\ \n", osQCD.first, osQCD.second, ssQCD.first, ssQCD.second);
      printf("$Z\\rightarrow\\tau\\tau$ & %.2f $\\pm$ %.2f & - \\\\ \n", zttYield.first, zttYield.second);
      printf("Total Background & %.2f $\\pm$ %.2f & - \\\\ \n",background,backgroundErr);
      BkgOutput output;

      output.DATA = dataYield.first;
      output.W = wYield.first;
      output.dW = wYield.second;
      output.QCD = osQCD.first;
      output.QCDSDB = ssQCD.first;
      output.dQCD = osQCD.second;
      output.ZLFT = zlftYield.first;
      output.dZLFT =zlftYield.second;
      output.ZLFTSS = zlftSSYield.first;
      output.dZLFTSS =zlftSSYield.second;

      output.ZJFT = zjftYield.first;
      output.dZJFT =zjftYield.second;
      output.ZJFTSS = zjftSSYield.first;
      output.dZJFTSS =zjftSSYield.second;
  
      output.TOP = topInflYield.first;
      output.dTOP = topInflYield.second;
      output.VV = vvInflYield.first;
      output.dVV = vvInflYield.second;
      output.ZTT = zttYield.first;
      output.dZTT = zttYield.second;

      return output;
  }






    std::pair<float,float> inflateError(std::pair<float,float> input,float error) {
      float value = input.first;
      float err = sqrt(input.second*input.second+(input.first*error)*(input.first*error));
      return std::make_pair(value,err);
    }



    std::pair<float,float> makeUniformHistogram(TTree* tree,std::string folder,std::string name,std::string cut,float scaleFactor = 1.) {
   if(fout_->Get(folder.c_str())==0)
     fout_->mkdir(folder.c_str());
     TH1F *h=0;

     h = new TH1F(name.c_str(),name.c_str(),1,0.,1.);
     h->Sumw2();

     TH1F* tmp = new TH1F("tmp","tmp",bins_,min_,max_);
     tree->Draw((variable_+">>tmp").c_str(),cut.c_str());
     tmp->Scale(scaleFactor);

     Double_t error=0.0;
     float yield = tmp->IntegralAndError(1,h->GetNbinsX(),error,"");

     h->SetBinContent(1,yield);
     h->SetBinError(1,error);

    fout_->cd(folder.c_str());
     h->Write();
     return std::make_pair(yield,error);
    }


    std::pair<float,float> makeHistogram(TTree* tree,std::string folder,std::string name,std::string cut,float scaleFactor = 1.) {

   if(fout_->Get(folder.c_str())==0)
     fout_->mkdir(folder.c_str());
     TH1F *h=0;

     if(binning_.size()==0)
       h= new TH1F(name.c_str(),name.c_str(),bins_,min_,max_);
     else
       h = new TH1F(name.c_str(),name.c_str(),bins_,&binning_[0]);
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

  void renormalizeHistogram(std::string folder, std::string histo, float yield)
  {
    TH1F * h =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    h->Scale(yield/h->Integral());
    fout_->cd(folder.c_str());
    h->Write(h->GetName(),TObject::kOverwrite);
  }

  void scaleHistogram(std::string folder, std::string histo, float scaleFactor)
  {
    TH1F * h =(TH1F*) fout_->Get((folder+"/"+histo).c_str());
    h->Scale(scaleFactor);
    fout_->cd(folder.c_str());
    h->Write(h->GetName(),TObject::kOverwrite);
  }

  std::pair<float,float> convertToPoisson(std::pair<float,float> measurement) {
    float yield = measurement.first;
    float CLHi = TMath::ChisquareQuantile(1-0.32/2,2*yield+2)/2.;
    float CLLo = TMath::ChisquareQuantile(0.32/2,2*yield)/2.;
    printf("Yield =%f Lo=%f Hi=%f\n",measurement.first,CLLo,CLHi);
    return std::make_pair(measurement.first,(CLHi-CLLo)/2.);

  }

  std::pair<float,float> createHistogramAndShifts(std::string file,std::string name, std::string cut,float scaleFactor = 1, std::string postfix = "") {
    TFile *f  = new TFile(file.c_str());
    if(f==0) printf("Not file Found\n");
    //get the nominal tree first
    TTree *t= (TTree*)f->Get((channel_+"EventTree/eventTree").c_str());
    if(t==0) printf("Not Tree Found\n");

    std::pair<float,float> yield = makeHistogram(t,channel_+postfix,name,cut,scaleFactor);
    //now the shifts
    std::pair<float,float> tmpYield;
    for(unsigned int i=0;i<shifts_.size();++i) {
      TTree *ts= (TTree*)f->Get((channel_+"EventTree"+shifts_[i]+"Up/eventTree").c_str());
      if(ts!=0) {
	tmpYield = makeHistogram(ts,channel_+postfix,name+"_"+shifts_[i]+"Up",cut);
	renormalizeHistogram(channel_+postfix,name+"_"+shifts_[i]+"Up",yield.first);
      }
      TTree *td= (TTree*)f->Get((channel_+"EventTree"+shifts_[i]+"Down/eventTree").c_str());
      if(td!=0) {
	tmpYield = makeHistogram(td,channel_+postfix,name+"_"+shifts_[i]+"Down",cut);
	renormalizeHistogram(channel_+postfix,name+"_"+shifts_[i]+"Down",yield.first);
      }
    }

    f->Close();
    return yield;
  }

  void close() {
    fout_->Close();
  }



  std::pair<float,float> abcdMethod(std::string file, std::string preselection,std::string abSelection)
    {

      //Get file and tree
      TFile *f = new TFile(file.c_str());
      TTree *t =(TTree*) f->Get((channel_+"EventTree/eventTree").c_str());
   
  //calculate events in the regions


      float B = t->GetEntries((preselection+"&&"+abcdCoeffs_[1]+"&&"+abSelection).c_str());
      float C = t->GetEntries((preselection+"&&"+abcdCoeffs_[2]).c_str());
      float D = t->GetEntries((preselection+"&&"+abcdCoeffs_[3]).c_str());
      
      float background = C*B/D;
      float backgrounderr = background*sqrt(1/C+1/D+1/B);
      return std::make_pair(background,backgrounderr);
 
    } 



 private:
  std::string channel_;
  std::vector<std::string> shifts_;

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
  std::string zlftSelection_;
  std::string zjftSelection_;
  std::string qcdSelection_;
  std::string bSelection_;
  std::string antibSelection_;
  std::string antiVBFSelection_;

  ////////////////////////

  //Luminosity and efficiency corrections
  float luminosity_;
  float luminosityErr_;
  float  muID_   ;      
  float muIDErr_;      
  float eleID_ ;       
  float eleIDErr_;     
  float tauID_  ;      
  float tauIDErr_;     
  float tauHLT_ ;      
  float tauHLTErr_;    
  float zttScale_;     
  float zttScaleErr_;  



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
  float zjftErr_;
  float wFactorErr_;
  float qcdFactor_;
  float qcdFactorErr_;


  float bFactor1_;
  float bFactorErr1_;
  float bFactor2_;
  float bFactorErr2_;

  float vbfFactor1_;
  float vbfFactorErr1_;
  float vbfFactor2_;
  float vbfFactorErr2_;



  float bID_;
  float bIDErr_;
  float bMisID_;
  float bMisIDErr_;
  float bJecErr_;
  float vbfJecErr_;
  float vbfErr_;


std::vector<std::string> mssmMasses_;
std::vector<std::string> smMasses_;
std::vector<float> mssmBBFraction_;
std::vector<float> smSigma_;
std::vector<float> vbfSigma_;
std::string dir_;

 std::vector<std::string> abcdCoeffs_;



};



