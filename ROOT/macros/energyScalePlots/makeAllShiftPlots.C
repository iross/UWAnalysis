{
gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/energyScalePlots/makeScaleAndRatioPlots.C");

 makeScaleAndRatioPlots("mu","tau","mvis","tau","ZTT");
 makeScaleAndRatioPlots("mu","tau","mvis","mu","ZTT");
 makeScaleAndRatioPlots("mu","tau","mvis","all","ZTT");

 makeScaleAndRatioPlots("mu","tau","sv","tau","ZTT",60,200,"M(#tau^{+},#tau^{-})");
 makeScaleAndRatioPlots("mu","tau","sv","mu","ZTT",60,200,"M(#tau^{+},#tau^{-})");
 makeScaleAndRatioPlots("mu","tau","sv","jet","ZTT",60,200,"M(#tau^{+},#tau^{-})");
 makeScaleAndRatioPlots("mu","tau","sv","unc","ZTT",60,200,"M(#tau^{+},#tau^{-})",0,3);
 makeScaleAndRatioPlots("mu","tau","sv","all","ZTT",60,200,"M(#tau^{+},#tau^{-})",0,3);


 makeScaleAndRatioPlots("ele","tau","mvis","tau","ZTT");
 makeScaleAndRatioPlots("ele","tau","mvis","ele","ZTT");
 makeScaleAndRatioPlots("ele","tau","mvis","all","ZTT");

 makeScaleAndRatioPlots("ele","tau","sv","tau","ZTT",60,200,"M(#tau^{+},#tau^{-})");
 makeScaleAndRatioPlots("ele","tau","sv","ele","ZTT",60,200,"M(#tau^{+},#tau^{-})");
 makeScaleAndRatioPlots("ele","tau","sv","jet","ZTT",60,200,"M(#tau^{+},#tau^{-})");
 makeScaleAndRatioPlots("ele","tau","sv","unc","ZTT",60,200,"M(#tau^{+},#tau^{-})",0,3);
 makeScaleAndRatioPlots("ele","tau","sv","all","ZTT",60,200,"M(#tau^{+},#tau^{-})",0,3);


}
