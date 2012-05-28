{
 std::string lumi="1000";
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZMMTTPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZMMMTPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZMMETPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZMMEMPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZMMMMPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZMMEEPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZEETTPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZEEMTPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZEEETPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZEEEMPlots.C");
gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/plotScripts/makeAllZZEEEEPlots.C");

}

