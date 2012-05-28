{

//Load FwLite
//gSystem->Load("libFWCoreFWLite.so");
//AutoLibraryLoader::enable();

//Load the Functions
//gSystem->Load("$CMSSW_BASE/lib/$SCRAM_ARCH/libCIARootAnalysis.so");
gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/NtuplePlotter.cc+");
gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/PhysicsDrawer.cc+");
gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/LimitPlotter.C+");
gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/bandUtils.cxx+");
gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");

//Set plot styles
setTDRStyle();


}
