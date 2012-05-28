{

  TString selection_ZMMEnriched = "HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA>-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1<40&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize!=0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass>0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP>0.08)";

  TString selection_WMNEnriched =   "HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1>60&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08)";

  TString selection ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08)";

  TString selection_NoCharge ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08)";

  TFile::Open("sandbox/zet-latest/ZMM.root");  
  eleTauEventTree->cd();
  
  double ZMMNum = eventTree->GetEntries(selection);
  double ZMMDen = eventTree->GetEntries(selection_ZMMEnriched);
  
  double ZFactor = ZMMNum/ZMMDen;
  double ZFactorErr = ZFactor*sqrt(ZMMNum/(ZMMDen*ZMMDen)+ZMMNum*ZMMNum/(ZMMDen*ZMMDen*ZMMDen));
  
  printf("Z Scale Factor = %f +- %f \n",ZFactor, ZFactorErr);
  
  TFile::Open("sandbox/zet-latest/WMN.root");  
  eleTauEventTree->cd();
  
  double WMNNum = eventTree->GetEntries(selection_NoCharge);
  double WMNDen = eventTree->GetEntries(selection_WMNEnriched);
  
  double WMNFactor = WMNNum/WMNDen;
  double WMNFactorErr = WMNFactor*sqrt(WMNNum/(WMNDen*WMNDen)+WMNNum*WMNNum/(WMNDen*WMNDen*WMNDen));
  
  printf("WMN Scale Factor = %f +- %f \n",WMNFactor, WMNFactorErr);
  
  TFile::Open("sandbox/zet-latest/WTN.root");  
  eleTauEventTree->cd();
  
  double WTNNum = eventTree->GetEntries(selection_NoCharge);
  
  double WTNFactor = WTNNum/WMNNum;
  double WTNFactorErr = WTNFactor*sqrt(WTNNum/(WMNNum*WMNNum)+WTNNum*WTNNum/(WMNNum*WMNNum*WMNNum));
  
  printf("WTN Scale Factor = %f +- %f \n",WTNFactor, WTNFactorErr);
  
}
  
  