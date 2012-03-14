{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/higgsShapes/makeNewZETShapes.C");
  


  makeZETShapes("ele-tau-mvis-nominal.root","eleTauEventTree/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-tauUp.root","eleTauEventTreeTauUp/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-tauDown.root","eleTauEventTreeTauDown/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-eleUp.root","eleTauEventTreeEleUp/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-eleDown.root","eleTauEventTreeEleDown/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-allUp.root","eleTauEventTreeOtherUp/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-allDown.root","eleTauEventTreeOtherDown/eventTree","eleTauMass",60,0,600);


  //  now SV fit 
  makeZETShapes("ele-tau-sv-nominal.root","eleTauEventTree/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-tauUp.root","eleTauEventTreeTauUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-tauDown.root","eleTauEventTreeTauDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-eleUp.root","eleTauEventTreeEleUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-eleDown.root","eleTauEventTreeEleDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-jetUp.root","eleTauEventTreeJetUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-jetDown.root","eleTauEventTreeJetDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-uncUp.root","eleTauEventTreeUncUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-uncDown.root","eleTauEventTreeUncDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-allUp.root","eleTauEventTreeOtherUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-allDown.root","eleTauEventTreeOtherDown/eventTree","sv_KineMETPtMass",50,0.,1000.);



  /////3 sigma

  makeZETShapes("ele-tau-mvis-tauUp3.root","eleTauEventTreeTauUp3/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-tauDown3.root","eleTauEventTreeTauDown3/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-eleUp3.root","eleTauEventTreeEleUp3/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-eleDown3.root","eleTauEventTreeEleDown3/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-allUp3.root","eleTauEventTreeOtherUp3/eventTree","eleTauMass",60,0,600);
  makeZETShapes("ele-tau-mvis-allDown3.root","eleTauEventTreeOtherDown3/eventTree","eleTauMass",60,0,600);

  //  now SV fit 
  makeZETShapes("ele-tau-sv-tauUp3.root","eleTauEventTreeTauUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-tauDown3.root","eleTauEventTreeTauDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-eleUp3.root","eleTauEventTreeEleUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-eleDown3.root","eleTauEventTreeEleDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-jetUp3.root","eleTauEventTreeJetUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-jetDown3.root","eleTauEventTreeJetDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-uncUp3.root","eleTauEventTreeUncUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-uncDown3.root","eleTauEventTreeUncDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-allUp3.root","eleTauEventTreeOtherUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
  makeZETShapes("ele-tau-sv-allDown3.root","eleTauEventTreeOtherDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);



}
