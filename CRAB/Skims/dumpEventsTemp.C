dumpEventsTemp(TString fileName, TString treeName){
	gROOT->ProcessLine(".L ~/HZZ425/UWAnalysis/ROOT/macros/ZZLimitsAndYields/helpers.h");
	TFile* f1=new TFile(fileName+".root");
	//TFile* f1=new TFile("/afs/hep.wisc.edu/cms/iross/HZZ2l2tau/CMSSW_4_2_5/src/UWAnalysis/CRAB/LLLL/sandbox/"+fileName+".root");
	TTree *tree = (TTree*)f1->Get(treeName+"EventTree/eventTree");
	if (tree=="NULL")_break;
	tree->SetScanField(0);
	TString sel=returnCuts(treeName,"selection");
	std::cout << "Selection: " << sel << std::endl;
	tree->Scan("EVENT:met",sel,"col=10.10:");
	f1->Close();
}
