{
  gROOT->ProcessLine(".L UWAnalysis/ROOT/macros/higgsShapes/makeNewZEMShapesMarkus.C");


   makeZEMShapes("ele-mu-mvis-nominal.root","eleMuEventTreeNominal/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-eleUp.root","eleMuEventTreeEleUp/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-eleDown.root","eleMuEventTreeEleDown/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-muUp.root","eleMuEventTreeMuUp/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-muDown.root","eleMuEventTreeMuDown/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-allUp.root","eleMuEventTreeOtherUp/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-allDown.root","eleMuEventTreeOtherDown/eventTree","eleMuMass",60,0.,600.);



   // now SV fit 
   makeZEMShapes("ele-mu-sv-nominal.root","eleMuEventTreeNominal/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-eleUp.root","eleMuEventTreeEleUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-eleDown.root","eleMuEventTreeEleDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-muUp.root","eleMuEventTreeMuUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-muDown.root","eleMuEventTreeMuDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-jetUp.root","eleMuEventTreeJetUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-jetDown.root","eleMuEventTreeJetDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-uncUp.root","eleMuEventTreeUncUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-uncDown.root","eleMuEventTreeUncDown/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-allUp.root","eleMuEventTreeOtherUp/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-allDown.root","eleMuEventTreeOtherDown/eventTree","sv_KineMETPtMass",50,0.,1000.);






   makeZEMShapes("ele-mu-mvis-eleUp3.root","eleMuEventTreeEleUp3/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-eleDown3.root","eleMuEventTreeEleDown3/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-muUp3.root","eleMuEventTreeMuUp3/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-muDown3.root","eleMuEventTreeMuDown3/eventTree","eleMuMass",60,0.,600.);
   makeZEMShapes("ele-mu-mvis-allUp3.root","eleMuEventTreeOtherUp3/eventTree","eleMuMass",60,0.,600.);
  makeZEMShapes("ele-mu-mvis-allDown3.root","eleMuEventTreeOtherDown3/eventTree","eleMuMass",60,0.,600.);



   // now SV fit 
   makeZEMShapes("ele-mu-sv-eleUp3.root","eleMuEventTreeEleUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-eleDown3.root","eleMuEventTreeEleDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-muUp3.root","eleMuEventTreeMuUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-muDown3.root","eleMuEventTreeMuDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-jetUp3.root","eleMuEventTreeJetUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-jetDown3.root","eleMuEventTreeJetDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-uncUp3.root","eleMuEventTreeUncUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-uncDown3.root","eleMuEventTreeUncDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-allUp3.root","eleMuEventTreeOtherUp3/eventTree","sv_KineMETPtMass",50,0.,1000.);
   makeZEMShapes("ele-mu-sv-allDown3.root","eleMuEventTreeOtherDown3/eventTree","sv_KineMETPtMass",50,0.,1000.);




}
