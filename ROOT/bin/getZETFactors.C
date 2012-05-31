{

  TString selection_ZEEEnriched = "HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA>-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1<40&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize!=0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass>0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP>0.08)";

  TString selection_WENEnriched =   "HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1>60&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08)";

  TString selection ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&eleTauCharge==0&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08)";

  TString selection_NoCharge ="HLT_Any&&eleTauPt1>15&&eleTauPt2>20&&abs(eleTauEleIP)<0.02&&eleTauLeadCandMVA<-0.1&&eleTauMissHitsWW==0&&((abs(eleTauEta1)<1.4442&&eleTauPFRelIsoLow<0.08)||(abs(eleTauEta1)>1.566&&eleTauPFRelIsoLow<0.04))&&eleTauMt1<40&&PVs>0&&(abs(eleTauEta2)>1.566||abs(eleTauEta2)<1.4442)&&dieleSize==0&&abs(eleTauEta1)<2.1&&!(eleTauProngs==1&&eleTauGammas>0&&eleTauBremEnergy/eleTauEmEnergy>0.99&&eleTauHadMass<0.55)&&!(eleTauProngs==1&&eleTauGammas==0&&eleTauLeadTrackHOP<0.08)";

  TFile::Open("sandbox/zet-latest/ZEE.root");  
  eleTauEventTree->cd();
  
  double ZEENum = eventTree->GetEntries(selection);
  double ZEEDen = eventTree->GetEntries(selection_ZEEEnriched);
  
  double ZFactor = ZEENum/ZEEDen;
  double ZFactorErr = ZFactor*sqrt(ZEENum/(ZEEDen*ZEEDen)+ZEENum*ZEENum/(ZEEDen*ZEEDen*ZEEDen));
  
  printf("Z Scale Factor = %f +- %f \n",ZFactor, ZFactorErr);
  
  TFile::Open("sandbox/zet-latest/WEN.root");  
  eleTauEventTree->cd();
  
  double WENNum = eventTree->GetEntries(selection_NoCharge);
  double WENDen = eventTree->GetEntries(selection_WENEnriched);
  
  double WENFactor = WENNum/WENDen;
  double WENFactorErr = WENFactor*sqrt(WENNum/(WENDen*WENDen)+WENNum*WENNum/(WENDen*WENDen*WENDen));
  
  printf("WEN Scale Factor = %f +- %f \n",WENFactor, WENFactorErr);
  
  TFile::Open("sandbox/zet-latest/WTN.root");  
  eleTauEventTree->cd();
  
  double WTNNum = eventTree->GetEntries(selection_NoCharge);
  
  double WTNFactor = WTNNum/WENNum;
  double WTNFactorErr = WTNFactor*sqrt(WTNNum/(WENNum*WENNum)+WTNNum*WTNNum/(WENNum*WENNum*WENNum));
  
  printf("WTN Scale Factor = %f +- %f \n",WTNFactor, WTNFactorErr);
  
}
  
  