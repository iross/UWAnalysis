checkEntries(TString fileName, TString treeName){
	TFile* f1=new TFile(fileName+".root");
	TTree *tree = (TTree*)f1->Get(treeName+"/eventTree");
	if (tree=="NULL") break;
	tree->GetEntries();
}
