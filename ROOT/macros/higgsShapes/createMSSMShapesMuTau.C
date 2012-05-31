{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/higgsShapes/makeNewZMTShapes.C");

  ///////Mu+TAU
   makeZMTShapes("mu-tau-mvis-nominal.root","muTauEventTreeNominal/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-tauUp.root","muTauEventTreeTauUp/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-tauDown.root","muTauEventTreeTauDown/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-muUp.root","muTauEventTreeMuUp/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-muDown.root","muTauEventTreeMuDown/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-allUp.root","muTauEventTreeOtherUp/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-allDown.root","muTauEventTreeOtherDown/eventTree","muTauMass",60,0.,600.);


   // now SV fit 
   makeZMTShapes("mu-tau-sv-nominal.root","muTauEventTreeNominal/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-tauUp.root","muTauEventTreeTauUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-tauDown.root","muTauEventTreeTauDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-muUp.root","muTauEventTreeMuUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-muDown.root","muTauEventTreeMuDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-jetUp.root","muTauEventTreeJetUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-jetDown.root","muTauEventTreeJetDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-uncUp.root","muTauEventTreeUncUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-uncDown.root","muTauEventTreeUncDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-allUp.root","muTauEventTreeOtherUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-allDown.root","muTauEventTreeOtherDown/eventTree","sv_KineMETPtMass",50,0.,1000.);

   /////////////////3 signa

   makeZMTShapes("mu-tau-mvis-tauUp3.root","muTauEventTreeTauUp3/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-tauDown3.root","muTauEventTreeTauDown3/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-muUp3.root","muTauEventTreeMuUp3/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-muDown3.root","muTauEventTreeMuDown3/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-allUp3.root","muTauEventTreeOtherUp3/eventTree","muTauMass",60,0.,600.);
   makeZMTShapes("mu-tau-mvis-allDown3.root","muTauEventTreeOtherDown3/eventTree","muTauMass",60,0.,600.);


   // now SV fit 
   makeZMTShapes("mu-tau-sv-tauUp3.root","muTauEventTreeTauUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-tauDown3.root","muTauEventTreeTauDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-muUp3.root","muTauEventTreeMuUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-muDown3.root","muTauEventTreeMuDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-jetUp3.root","muTauEventTreeJetUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-jetDown3.root","muTauEventTreeJetDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-uncUp3.root","muTauEventTreeUncUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-uncDown3.root","muTauEventTreeUncDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-allUp3.root","muTauEventTreeOtherUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZMTShapes("mu-tau-sv-allDown3.root","muTauEventTreeOtherDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);



}
