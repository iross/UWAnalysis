{
	//todo: measure fake rates here
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZMMTTYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZMMETYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZMMMTYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZMMEMYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZEETTYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZEEETYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZEEEMYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZEEMTYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZEEEEYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZEEMMYieldsZZ.C");	
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZMMEEYieldsZZ.C");
	gROOT->ProcessLine(".x UWAnalysis/ROOT/macros/ZZLimitsAndYields/makeAllZZMMMMYieldsZZ.C");
}

