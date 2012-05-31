{


	TFile* Data = new TFile("Electrons/All2011B.root");
	TFile* ZLL	= new TFile("Electrons/ZEE2011B.root");
	//Configurable Part
	TString Var = "WWIDPass";
	TString DirM = "tagAndProbeelectronHtt15/tagAndProbeTree";
	TString DirD = "tagAndProbeelectronHtt15/tagAndProbeTree";
	const int E = 3;
	const int P = 6;
	double eta[E]={0,1.4,2.1};
	int pt[P]={10,15,20,30,100,200};
	
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

	
	for( int p=0; p < P-2; ++p){
		for( int e=0; e < E-1; ++e ){
		
			std::ostringstream P0;
			std::ostringstream P1;
			std::ostringstream P2;
			std::ostringstream E0;
			std::ostringstream E1;
			P0 << pt[p];
			P1 << pt[p+1];
			P2 << pt[p+2];
			E0 << eta[e];
			E1 << eta[e+1];
			TString pt0 = P0.str();
			TString pt1 = P1.str();
			TString pt2 = P2.str();
			TString eta0 = E0.str();
			TString eta1 = E1.str();
			
			TString cutP = "pt>"+pt0+"&&pt<"+pt1+"&&abs(eta)>"+eta0+"&&abs(eta)<"+eta1+"&&"+Var+"==1";
			TString cutF = "pt>"+pt0+"&&pt<"+pt1+"&&abs(eta)>"+eta0+"&&abs(eta)<"+eta1+"&&"+Var+"==0";
			TString cutPM = "pt>"+pt0+"&&pt<"+pt2+"&&abs(eta)>"+eta0+"&&abs(eta)<"+eta1+"&&"+Var+"==1";
			TString cutFM = "pt>"+pt0+"&&pt<"+pt2+"&&abs(eta)>"+eta0+"&&abs(eta)<"+eta1+"&&"+Var+"==1";
			
			///////////////////////////Pass//////////////////////////////////

			//Create Model
			TH1F *hm = new TH1F("hm", "hm", 60, 60, 120);
			treeM->Draw("mass>>hm",cutPM);
			RooDataHist mc("mc","mc",mass,hm);
			RooRealVar c("c","c",0,-5,5);
			RooRealVar a("a","a",5,0,10);
			RooRealVar n("n","n",0.5,0,1);
			RooRealVar m("m","m",90,88,92);
			RooRealVar m2("m2","m2",0);
			RooRealVar s("s","s",5,0,10);
			RooRealVar g("g","g",3,1,10);
			RooGaussian G("Gaus","Gaus",mass,m2,g);
			RooBreitWigner BW("BW","BW",mass,m,g);
			RooCBShape CB("CB","Crystal Ball",mass,m2,s,a,n);
			RooExponential bkgd("bkgd","bkgd",mass,c);
			RooRealVar NSig("NSig","Signal Events",50000,0,1000000);
			RooRealVar NBkgd("NBkgd","Background Events",50000,0,1000000);
			RooHistPdf ZShape("ZShape","ZShape",mass,mc);
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
			TH1F *hm = new TH1F("hm", "hm", 30, 60, 120);
			treeM->Draw("mass>>hm",cutFM);
			RooDataHist mc("mc","mc",mass,hm);
			RooRealVar c("c","c",0,-5,5);
			RooRealVar a("a","a",5,0,10);
			RooRealVar n("n","n",0.5,0,1);
			RooRealVar m("m","m",90,88,92);
			RooRealVar m2("m2","m2",0);
			RooRealVar s("s","s",5,0,10);
			RooRealVar g("g","g",3,1,10);
			RooGaussian G("Gaus","Gaus",mass,m2,g);
			RooBreitWigner BW("BW","BW",mass,m,g);
			RooCBShape CB("CB","Crystal Ball",mass,m2,s,a,n);
			RooExponential bkgd("bkgd","bkgd",mass,c);
			RooRealVar NSig("NSig","Signal Events",50000,0,1000000);
			RooRealVar NBkgd("NBkgd","Background Events",50000,0,1000000);
			RooHistPdf ZShape("ZShape","ZShape",mass,mc);
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
			
			//////////////////Fit for MC Pass region////////////////////

			//Create Model
			TH1F *hm = new TH1F("hm", "hm", 60, 60, 120);
			treeM->Draw("mass>>hm",cutPM);
			RooDataHist mc("mc","mc",mass,hm);
			RooRealVar c("c","c",0,-5,5);
			RooRealVar a("a","a",5,0,10);
			RooRealVar n("n","n",0.5,0,1);
			RooRealVar m("m","m",90,88,92);
			RooRealVar m2("m2","m2",0);
			RooRealVar s("s","s",5,0,10);
			RooRealVar g("g","g",3,1,10);
			RooGaussian G("Gaus","Gaus",mass,m2,g);
			RooBreitWigner BW("BW","BW",mass,m,g);
			RooCBShape CB("CB","Crystal Ball",mass,m2,s,a,n);
			RooExponential bkgd("bkgd","bkgd",mass,c);
			RooRealVar NSig("NSig","Signal Events",50000,0,1000000);
			RooRealVar NBkgd("NBkgd","Background Events",50000,0,1000000);
			RooHistPdf ZShape("ZShape","ZShape",mass,mc);
			RooFFTConvPdf Z("Z", "FFT Conv MC Z Shape with Gaussian", mass, ZShape, G); 
			RooAddPdf Mod("Mod","ZShape+Expo",RooArgList(Z,bkgd),RooArgList(NSig,NBkgd));
						
			TH1F *hd = new TH1F("hd", "hd", 30, 60, 120);
			hd->Sumw2();
			treeM->Draw("mass>>hd","("+cutP+")*__WEIGHT__*1800");
			//SumW2Error(kTRUE);
			RooDataHist data("data","data",mass,hd);
			Mod.fitTo(data);
			
			//Draw Model
			RooPlot* C = mass.frame();
			data.plotOn(C);
			Mod.plotOn(C);
			Mod.plotOn(C,Components(bkgd),LineStyle(kDashed));
			C->Draw();
			c1->SaveAs("FitPlots/MCPass"+pt0+"-"+pt1+"_"+eta0+"-"+eta1+".png");
			MCPass = NSig.getVal();
			MCPassErr = NSig.getError();
			cout << "Passing: " << MCPass << " +/- " << MCPassErr << endl;
			
			//////////////////Fit for MC Fail region////////////////////

			//Create Model
			TH1F *hm = new TH1F("hm", "hm", 30, 60, 120);
			treeM->Draw("mass>>hm",cutFM);
			RooDataHist mc("mc","mc",mass,hm);
			RooRealVar c("c","c",0,-5,5);
			RooRealVar a("a","a",5,0,10);
			RooRealVar n("n","n",0.5,0,1);
			RooRealVar m("m","m",90,88,92);
			RooRealVar m2("m2","m2",0);
			RooRealVar s("s","s",5,0,10);
			RooRealVar g("g","g",3,1,10);
			RooGaussian G("Gaus","Gaus",mass,m2,g);
			RooBreitWigner BW("BW","BW",mass,m,g);
			RooCBShape CB("CB","Crystal Ball",mass,m2,s,a,n);
			RooExponential bkgd("bkgd","bkgd",mass,c);
			RooRealVar NSig("NSig","Signal Events",50000,0,1000000);
			RooRealVar NBkgd("NBkgd","Background Events",50000,0,1000000);
			RooHistPdf ZShape("ZShape","ZShape",mass,mc);
			RooFFTConvPdf Z("Z", "FFT Conv MC Z Shape with Gaussian", mass, ZShape, G); 
			RooAddPdf Mod("Mod","ZShape+Expo",RooArgList(Z,bkgd),RooArgList(NSig,NBkgd));
			
			TH1F *hd = new TH1F("hd", "hd", 15, 60, 120);
			hd->Sumw2();
			treeM->Draw("mass>>hd","("+cutF+")*__WEIGHT__*1800");
			//SumW2Error(kTRUE);
			RooDataHist data("data","data",mass,hd);
			Mod.fitTo(data);
			
			//Draw Model
			RooPlot* C = mass.frame();
			data.plotOn(C);
			Mod.plotOn(C);
			Mod.plotOn(C,Components(bkgd),LineStyle(kDashed));
			C->Draw();
			c1->SaveAs("FitPlots/MCFail"+pt0+"-"+pt1+"_"+eta0+"-"+eta1+".png");
			MCFail = NSig.getVal();
			MCFailErr = NSig.getError();
			cout << "Failing: " << MCFail << " +/- " << MCFailErr << endl;
			
			/////////////////////////Calculate Efficiency//////////////////////
			
			Double_t Eff, EffErr;
			Eff = DataPass/(DataFail+DataPass);
			effd[p][e] = Eff;
			EffErr = Eff*Eff*sqrt(DataFail*DataFail/(DataPass*DataPass*DataPass*DataPass)*DataPassErr*DataPassErr+DataFailErr*DataFailErr/(DataPass*DataPass));
			effdErr[p][e] = EffErr;
			cout << "Data Efficiency " << Eff << " +/- " << EffErr << endl;
			
			Double_t MCEff, MCEffErr;
			MCEff = MCPass/(MCFail+MCPass);
			effmc[p][e] = MCEff;
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

/////////////////Make a tex table/////////////////////////

   	printf("\\begin{table}[htbp] \n");
   	printf("\\begin{adjustwidth}{-4em}{-4em} \n");
   	printf("\\centering \n");
   	printf("\\begin{tabular}{|c|c|");
   	for( int e=0; e < E-1; ++e ){
   		printf("c|");
   	}
   	printf("} \n");
   	printf("\\hline \n");
   	printf("$p_{T}$ & ");
   	for( int e=0; e < E-1; ++e ){
   		printf(" & $%0.2f < |\\eta| < %0.2f$", eta[e], eta[e+1]);
   	}
   	printf("\\\\ \n");
   	printf("\\hline \n");
   	for( int p=0; p < P-2; ++p ){
   		printf( "\\multirow{3}{*}{%0.0f-%0.0f}", pt[p], pt[p+1]);
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
   		printf( " & $\\frac{\\rm{DATA}}{\\rm{MC}}$ " );
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
   	
///////////////////////Make efficiency plots/////////////////////////////
    //TFile f("TrigEff2011B.root","UPDATE");
    
   	for( int e=0; e < E-1; ++e){
   	
		std::ostringstream E0;
		std::ostringstream E1;
		E0 << eta[e];
		E1 << eta[e+1];
		TString eta0 = E0.str();
		TString eta1 = E1.str();
		
   		TGraphErrors *gd = new TGraphErrors();
   		TGraphErrors *gm = new TGraphErrors();
   		float ptp, pts;
   		
   		for( int p=0; p < P-2; ++p){
   			
   			ptp = (pt[p+1]+pt[p])/2.;
   			pts = (pt[p+1]-pt[p])/2.;
   			gd->SetPoint(p, ptp, effd[p][e]);
			gd->SetPointError(p, pts[p], effdErr[p][e]);
			gm->SetPoint(p, ptp, effmc[p][e]);
			gm->SetPointError(p, pts[p], effmcErr[p][e]);
		}
		
		gd->GetYaxis()->SetRangeUser(0,1);
		gm->GetYaxis()->SetRangeUser(0,1);
		gd->GetYaxis()->SetTitle("Efficiency");
		gd->GetXaxis()->SetTitle("p_{T}");
		gm->SetMarkerStyle(24);
		gm->SetMarkerColor(4);
		gd->SetMarkerStyle(20);
		gd->SetMarkerColor(1);
		gd->Draw("AP");
		gm->Draw("Psame");
		TLatex latex;
		latex.SetNDC();
		latex.SetTextSize(0.045);
		latex.SetTextAlign(11);
		latex.DrawLatex(0.20,0.96,"CMS Preliminary 2011, #sqrt{s}=7 TeV ");
		TLegend *le = new TLegend(0.6,0.4,0.85,0.15,"");
		le.AddEntry(gd,"Data","p");
		le.AddEntry(gm,"Simulation","p");
		le.SetBorderSize(0);
		le.SetFillColor(0);
		le->Draw();
		c1->SaveAs("Eff"+Var+"_"+eta0+"-"+eta1+".png");
		//gd->Write("EffMu15_L114");
		//gm->Write("EffMu12MC2");
		

	}

}

