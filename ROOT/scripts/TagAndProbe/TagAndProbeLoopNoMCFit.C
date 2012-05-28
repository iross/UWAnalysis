{



	TFile* Data = new TFile("Muons/All2011A.root");
	TFile* ZLL	= new TFile("Muons/ZMM.root");
	//Configurable Part
	TString Var = "IDPass";
	TString DirM = "tagAndProbeMuonHLTMu8ZZ/tagAndProbeTree";
	TString DirD = "tagAndProbeMuonHLTMu13ZZ/tagAndProbeTree";
	const int E = 6;
	const int P = 5;
	double eta[E]={0,0.9,1.2,1.6,2.1,2.4};
	int pt[P]={10,20,30,50,100};
	
	//Create needed variables
	TTree* treeM = ZLL->Get(DirM);
	TTree* treeD = Data->Get(DirD);
	RooRealVar mass("mass","mass",60,120);
	Double_t DataPass, DataPassErr, DataFail, DataFailErr, MCPass, MCFail, MCPassErr, MCFailErr;
	TCanvas *c1 = new TCanvas();
	using namespace RooFit;
    float effd[20][10];
    float effdErr[20][10];
    float effmc[20][10];
    float effmcErr[20][10];
    float ratio[20][10];
    float ratioErr[20][10];
	gROOT->ProcessLine(".!mkdir FitPlots");

		
	for( int p=0; p < P-1; ++p){
		for( int e=0; e < E-1; ++e ){
		
			std::ostringstream P0;
			std::ostringstream P1;
			std::ostringstream E0;
			std::ostringstream E1;
			P0 << pt[p];
			P1 << pt[p+1];
			E0 << eta[e];
			E1 << eta[e+1];
			TString pt0 = P0.str();
			TString pt1 = P1.str();
			TString eta0 = E0.str();
			TString eta1 = E1.str();
			
			TString cutP = "pt>"+pt0+"&&pt<"+pt1+"&&abs(eta)>"+eta0+"&&abs(eta)<"+eta1+"&&"+Var+"==1";
			TString cutF = "pt>"+pt0+"&&pt<"+pt1+"&&abs(eta)>"+eta0+"&&abs(eta)<"+eta1+"&&"+Var+"==0";
			TString cutPM = cutP;//"pt>10&&pt<20&&abs(eta)>0&&abs(eta)<0.78&&CICPass==1";
			TString cutFM = cutF;//"pt>10&&pt<20&&abs(eta)>0&&abs(eta)<0.78&&CICPass==0";
			
			///////////////////////////Pass//////////////////////////////////

			//Create Model
			TH1F *hm = new TH1F("hm", "hm", 30, 60, 120);
			treeM->Draw("mass>>hm",cutPM);
			RooDataHist mc("mc","mc",mass,hm);
			RooHistPdf ZShape("ZShape","ZShape",mass,mc);
			RooRealVar c("c","c",0,-1,1);
			RooRealVar m("m","m",0,-2,2);
			RooRealVar g("g","g",3,1,5);
			RooGaussian G("Gaus","Gaus",mass,m,g);
			RooExponential bkgd("bkgd","bkgd",mass,c);
			RooRealVar NSig("NSig","Signal Events",50000,0,1000000);
			RooRealVar NBkgd("NBkgd","Background Events",50000,0,1000000);
			RooFFTConvPdf Z("Z", "FFT Conv MC Z Shape with Gaussian", mass, ZShape, G); 
			RooAddPdf Mod("Mod","ZShape+Expo",RooArgList(Z,bkgd),RooArgList(NSig,NBkgd));
			
			//Fit Data
			TH1F *hd = new TH1F("hd", "hd", 30, 60, 120);
			treeD->Draw("mass>>hd",cutP);
			RooDataHist data("data","data",mass,hd);
			Mod.fitTo(data);
			
			//Draw Model
			RooPlot* C = mass.frame();
			data.plotOn(C);
			Mod.plotOn(C);
			Mod.plotOn(C,Components(bkgd),LineStyle(kDashed));
			C->Draw();
			c1->SaveAs("FitPlots/DataPass"+pt0+"-"+pt1+"_"+eta0+"-"+eta1+".png");
			DataPass = NSig.getVal();
			DataPassErr = NSig.getError();
			cout << "Passing: " << DataPass << " +/- " << DataPassErr << endl;

			///////////////////////////Fail//////////////////////////////////
			
			//Create Model
			TH1F *hm = new TH1F("hm", "hm", 15, 60, 120);
			treeM->Draw("mass>>hm",cutFM);
			RooDataHist mc("mc","mc",mass,hm);
			RooHistPdf ZShape("ZShape","ZShape",mass,mc);
			RooRealVar c("c","c",0,-1,1);
			RooRealVar m("m","m",0,-2,2);
			RooRealVar g("g","g",3,1,5);
			RooGaussian G("Gaus","Gaus",mass,m,g);
			RooExponential bkgd("bkgd","bkgd",mass,c);
			RooRealVar NSig("NSig","Signal Events",50000,0,1000000);
			RooRealVar NBkgd("NBkgd","Background Events",50000,0,1000000);
			RooFFTConvPdf Z("Z", "FFT Conv MC Z Shape with Gaussian", mass, ZShape, G); 
			RooAddPdf Mod("Mod","ZShape+Expo",RooArgList(Z,bkgd),RooArgList(NSig,NBkgd));
			
			//Fit Data
			TH1F *hd = new TH1F("hd", "hd", 15, 60, 120);
			treeD->Draw("mass>>hd",cutF);
			RooDataHist data("data","data",mass,hd);
			Mod.fitTo(data);
			
			//Draw Model
			RooPlot* C = mass.frame();
			data.plotOn(C);
			Mod.plotOn(C);
			Mod.plotOn(C,Components(bkgd),LineStyle(kDashed));
			C->Draw();
			c1->SaveAs("FitPlots/DataFail"+pt0+"-"+pt1+"_"+eta0+"-"+eta1+".png");
			DataFail = NSig.getVal();
			DataFailErr = NSig.getError();
			cout << "Failing: " << DataFail << " +/- " << DataFailErr << endl;
			
			
			/////////////////////////Calculate Efficiency//////////////////////
			
			Double_t Eff, EffErr;
			Eff = DataPass/(DataFail+DataPass);
			effd[p][e] = Eff;
			EffErr = Eff*Eff*sqrt(DataFail*DataFail/(DataPass*DataPass*DataPass*DataPass)*DataPassErr*DataPassErr+DataFailErr*DataFailErr/(DataPass*DataPass));
			effdErr[p][e] = EffErr;
			cout << "Data Efficiency " << Eff << " +/- " << EffErr << endl;
			
			Double_t MCEff, MCEffErr;
			TH1F *p1 = new TH1F("p1", "p1", 1, 1, 2);
			treeM->Draw("1>>p1","("+cutPM+")*__WEIGHT__");
			MCPass = p1->GetBinContent(1);
			TH1F *f = new TH1F("f", "f", 1, 1, 2);
			treeM->Draw("1>>f","("+cutFM+")*__WEIGHT__");
			MCFail = f->GetBinContent(1);
			MCEff = MCPass/(MCFail+MCPass);
			effmc[p][e] = MCEff;
			MCPass = treeM->GetEntries(cutPM);
			MCFail = treeM->GetEntries(cutFM);
			MCPassErr = sqrt(MCPass);
			MCFailErr = sqrt(MCFail);
			MCEffErr = MCEff*MCEff*sqrt(MCFail*MCFail/(MCPass*MCPass*MCPass*MCPass)*MCPassErr*MCPassErr+MCFailErr*MCFailErr/(MCPass*MCPass));
			effmcErr[p][e] = MCEffErr;
			cout << "MC Efficiency " << MCEff << " +/- " << MCEffErr << endl;
			
			
			Double_t DataToMC, DataToMCErr;
			DataToMC = Eff/MCEff;
			ratio[p][e] = DataToMC;
			DataToMCErr = sqrt(EffErr*EffErr/(MCEff*MCEff)+Eff*Eff*MCEffErr*MCEffErr/(MCEff*MCEff*MCEff*MCEff));
			ratioErr[p][e] = DataToMCErr;
			cout << "Data/MC " << DataToMC << " +/- " << DataToMCErr << endl;

		}
	}
	
   	printf("\\begin{table}[htbp] \n");
   	printf("\\begin{adjustwidth}{-4em}{-4em} \n");
   	printf("\\centering \n");
   	printf("\\begin{tabular}{|c|c|");
   	for( int e=0; e < E-1; ++e ){
   		printf("c|");
   	}
   	printf("} \n");
   	printf("\\hline \n");
   	printf("$p_{T}$");
   	for( int e=0; e < E-1; ++e ){
   		printf(" & $ %0.4f < |\\eta| < %0.4f $", eta[e], eta[e+1]);
   	}
   	printf("\\\\ \n");
   	printf("\\hline \n");
   	for( int p=0; p < P-1; ++p ){
   		printf( "\\multirow{3}{*}{ %0.0f - %0.0f }", pt[p], pt[p+1]);
   		printf( " & Data " );
   		for( int e=0; e < E-1; ++e ){
   			printf( " & $ %0.3f \\pm %0.3f $ ", effd[p][e], effdErr[p][e]);
   		}
   		printf( "\\\\ \n");
   		printf( " & MC " );
   		for( int e=0; e < E-1; ++e ){
   			printf( " & $ %0.3f \\pm %0.3f $ ", effmc[p][e], effmcErr[p][e]);
   		}
   		printf( "\\\\ \n");
   		printf( " & Data//MC " );
   		for( int e=0; e < E-1; ++e ){
   			printf( " & $ %0.3f \\pm %0.3f $ ", ratio[p][e], ratioErr[p][e]);
   		}   		
   		printf( "\\\\ \n");
   		printf("\\hline \n");
   	}
   	printf("\\end{tabular} \n");
   	printf("\\caption{Tag And Probe}  \n");
   	printf("\\label{table:TnP} \n");
   	printf("\\end{adjustwidth} \n");
   	printf("\\end{table} \n");

}

