#include "helpers.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
class EventYield {
	public:
		EventYield() {}
		~EventYield() {}
		void addFile(TString tree,TString name,TString label,TString preselection,int type, double dataEstBG, TString winLow="0", TString winHigh="1000"){
			TChain *chain = new TChain(tree);
			chain->Add(name);
			trees_.push_back(chain);
			labels_.push_back(label);
			types_.push_back(type);
			dataDrivenBG_.push_back(dataEstBG);
			preselection_.push_back(preselection);
			winLow_.push_back(winLow);
			winHigh_.push_back(winHigh);
		}
		//void eventYields(){
		//	fakeRates();
		//}
		void eventYield(TString var,TString selection,TString selectionNoIso,TString lumi, int bins, float min, float max, TString finalState, bool useWindow=false, bool leptonic=false){
			if (leptonic){
				hMass_.push_back("115");
				hMass_.push_back("120");
				hMass_.push_back("130");
				hMass_.push_back("140");
				hMass_.push_back("150");
				hMass_.push_back("160");
				hMass_.push_back("170");
			}
			hMass_.push_back("180");
			hMass_.push_back("190");
			hMass_.push_back("200");
			hMass_.push_back("210");
			hMass_.push_back("220");
			hMass_.push_back("230");
			hMass_.push_back("250");
			hMass_.push_back("275");
			hMass_.push_back("300");
			hMass_.push_back("325");
			hMass_.push_back("350");
			hMass_.push_back("375");
			hMass_.push_back("400");
			hMass_.push_back("425");
			hMass_.push_back("450");
			hMass_.push_back("475");
			hMass_.push_back("500");
			hMass_.push_back("525");
			hMass_.push_back("550");
			hMass_.push_back("575");
			hMass_.push_back("600");
			hMassn_.push_back(180);
			hMassn_.push_back(190);
			hMassn_.push_back(200);
			hMassn_.push_back(210);
			hMassn_.push_back(220);
			hMassn_.push_back(230);
			hMassn_.push_back(250);
			hMassn_.push_back(275);
			hMassn_.push_back(300);
			hMassn_.push_back(325);
			hMassn_.push_back(350);
			hMassn_.push_back(375);
			hMassn_.push_back(400);
			hMassn_.push_back(425);
			hMassn_.push_back(450);
			hMassn_.push_back(475);
			hMassn_.push_back(500);
			hMassn_.push_back(525);
			hMassn_.push_back(550);
			hMassn_.push_back(575);
			hMassn_.push_back(600);

			process=finalState;
			TString selectionBase=selection;
			TString selectionBaseNoIso=selectionNoIso;

			fakeRates();
			//fakeRatesLP();
			zzBG();
			makeHists(selection,selectionNoIso,lumi,"hzz2l2t");

			for (unsigned int i=0; i<hMass_.size();++i){
				makeCard(hMass_[i],selectionBase,lumi,"hzz2l2t",hMassn_[i]);
			}
			//std::cout << returnCuts() << std::endl;	
			//fakeRate();
		}	

		void makeHists(TString selection,TString selectionNoIso,TString lumi,TString channel){
			//loop over i files, dump histogram for each into eeet.root (or whatever)
			TFile* fout = new TFile(channel+"/"+channel+"_"+process+".input.root","RECREATE");
			double zzNom=0;
			double zjNom=0;
			for (unsigned int j=0; j<labels_.size(); ++j){
				std::cout << "*****" << channel << "*****" << std::endl;
				std::cout << "Making histograms for " << process << "; " << labels_[j] << std::endl;
				TH1F * hh = new TH1F("test","test",50,0,1000);
				std::cout << "This is " << labels_[j] << std::endl;
				hh->Sumw2();
				if (labels_[j]=="DATA"){
					hh->SetName("data_obs");
					hh->SetTitle("data_obs");
					trees_[j]->Draw("mass>>data_obs",selection);
				} else if (labels_[j]=="Zjets" || labels_[j]=="Zjets_CMS_scale_tUp" || labels_[j]=="Zjets_CMS_scale_tDown"){
					hh->SetName(labels_[j]);
					hh->SetTitle(labels_[j]);
					trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selectionNoIso+")");
				} else {
					hh->SetName(labels_[j]);
					hh->SetTitle(labels_[j]);
					trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selection+")");
				}
				//scale to data-driven amount, if necessary.
				if (labels_[j]=="Zjets") zjNom=hh->Integral();
				if (labels_[j]=="ZZ") zzNom=hh->Integral();
				if (types_[j]==0){
					if (labels_[j]=="Zjets") hh->Scale(bgMap[(std::string)process]/hh->Integral());
					if (labels_[j]=="ZZ") {
						//hh->Scale(dataDrivenBG_[j]/hh->Integral());
						hh->Scale(zzBgMap[(std::string)process]/hh->Integral());
					}
				}
				if (types_[j]==-1){
					//scale higgs samples to overlap-corrected values
					if (labels_[j].Contains("ggH")) {
						std::cout << process << " yield:" << ggHMap[(std::string)labels_[j]] << std::endl;
						hh->Scale(ggHMap[(std::string)labels_[j]]/hh->Integral());
						std::cout << "After scaling: " << hh->Integral() << std::endl;
					}
					else {
						std::cout << process << " yield: " << vbfMap[(std::string)labels_[j]] << std::endl;
						hh->Scale(vbfMap[(std::string)labels_[j]]/hh->Integral());
						std::cout << "After scaling: " << hh->Integral() << std::endl;
					}
				}

				if (types_[j]==10){ //if systematics shape..
					if (labels_[j]=="Zjets" || labels_[j]=="Zjets_CMS_scale_tUp" || labels_[j]=="Zjets_CMS_scale_tDown"){
						//std::cout << labels_[j] << " scaled to " << dataDrivenBG_[j]*hh->Integral()/zjNom << std::endl;
						//std::cout << "Before scaling: " << hh->Integral() << std::endl;
						//hh->Scale(dataDrivenBG_[j]/zjNom);
						hh->Scale(bgMap[(std::string)process]/zjNom);
						std::cout << "After scaling: " << hh->Integral() << std::endl;
					} else if (labels_[j]=="ZZ" || labels_[j]=="ZZ_CMS_scale_tUp" || labels_[j]=="ZZ_CMS_scale_tDown"){
						std::cout << labels_[j] << " scaled to " << dataDrivenBG_[j]*hh->Integral()/zjNom << std::endl;
						std::cout << "Before scaling: " << hh->Integral() << std::endl;
						//hh->Scale(dataDrivenBG_[j]/zzNom);
						
						hh->Scale(zzBgMap[(std::string)process]/zzNom);
						std::cout << "After scaling: " << hh->Integral() << std::endl;
					} else if (labels_[j].Contains("ggH")){
						hh->Scale(ggHMap[(std::string)labels_[j]]/hh->Integral());
					} else if (labels_[j].Contains("vbf")){
						hh->Scale(vbfMap[(std::string)labels_[j]]/hh->Integral());
					}
				}

				//scale down mmet and eeet for MMEE/EEEE cross-contamination
				//if (process=="MMET" || process=="EEET"){
				//	if (labels_[j]!="Zjets" && labels_[j]!="Zjets_CMS_scale_tUp" && labels_[j]!="Zjets_CMS_scale_tDown" && labels_[j]!="DATA"){
						//hh->Scale(0.8);
						//std::cout << "ZZ or Higgs -- scaling down by 20% for cross-contamination!" << std::endl;
				//	}
				//}

				fout->Write();
				hh->Delete();
			}
			fout->Close();
		}

		void makeCard(TString hMass,TString selection,TString lumi,TString channel,double hMassn){
			std::cout << "Making cards for " << channel << ", " << process << ", mH" << hMass << std::endl;
			//loop over trees, get relevant values
			int observed=0;
			double gg=0;
			double vbf=0;
			double zjets=0;
			double zz=0;

			for(unsigned int j=0;j<trees_.size();++j) {
				TH1F * hh = new TH1F("test","test",10,0,1000);
				hh->Sumw2();
				if (labels_[j]=="DATA"){
					hh->SetName("data_obs");
					hh->SetTitle("data_obs");
					trees_[j]->Draw("mass>>data_obs",selection);
					observed=hh->Integral();
				} else if (labels_[j]=="Zjets"){
					//zjets=dataDrivenBG_[j];
					zjets=bgMap[(std::string)process];
				} else if (labels_[j]=="ZZ"){
					//zz=dataDrivenBG_[j];
					zz=zzBgMap[(std::string)process];
					hh->SetName(labels_[j]);
					hh->SetTitle(labels_[j]);
					trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selection+")");
					if (abs(zz-hh->Integral())/zz > 0.10) std::cout << "DIFFERENCE GREATER THAN 10% ---- CHECK IT" << std::endl;
					std::cout << "ZZ: " << zz << ", integral: " << hh->Integral() << std::endl;
					//zz=hh->Integral();
					//std::cout << "********ZZ EXPECTED: " << zz << "********" << std::endl;
					//if (process=="EEET" || process=="MMET") zz*=0.8; //factor already included in ZZ estimates.
				} else if (labels_[j]==("ggH"+hMass)){
					hh->SetName(labels_[j]);
					hh->SetTitle(labels_[j]);
					trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selection+")");
					//gg=hh->Integral();
					//use overlap-corrected value
					gg=ggHMap[std::string("ggH"+hMass)];
					if (abs(gg-hh->Integral())/gg > 0.10) std::cout << "DIFFERENCE GREATER THAN 10% ---- CHECK IT" << std::endl;
					std::cout << "gg: " << gg << ", integral: " << hh->Integral() << abs(gg-hh->Integral())/gg << std::endl;
					//std::cout << "Raw: " << hh->Integral() << ", overlap corrected: " << gg << std::endl;
					//if (process=="EEET" || process=="MMET") gg*=0.8;
				} else if (labels_[j]==("vbf"+hMass)){
					hh->SetName(labels_[j]);
					hh->SetTitle(labels_[j]);
					trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selection+")");
					vbf=hh->Integral();
					//use overlap-corrected value
					vbf=vbfMap[std::string("vbf"+hMass)];
					if (abs(vbf-hh->Integral())/vbf > 0.10) std::cout << "DIFFERENCE GREATER THAN 10% ---- CHECK IT" << std::endl;
					std::cout << "vbf: " << vbf << ", integral: " << hh->Integral() << std::endl;
					//if (process=="EEET" || process=="MMET") vbf*=0.8;
				}
				hh->Delete();
			}

			ofile.open(channel+"/"+process+"_ZZ.txt");
			ofile << "imax 1  number of channels\n";
			ofile << "jmax *  number of backgrounds\n";
			ofile << "kmax *  number of nuisance parameters (sources of systematical uncertainties)\n";
			ofile << "shapes * " << process << " " << channel << "_" << process << ".input.root" << " $PROCESS $PROCESS_$SYSTEMATIC \n"; 
			ofile << "------------\n";
			ofile << "bin\t" << process << "\n";
			ofile << "observation\t"<<itos(observed)<<"\n";
			ofile << "------------" << endl;

			ofile << "# now we list the expected events for signal and all backgrounds in that bin\n";
			ofile << "# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n";
			ofile << "# then we list the independent sources of uncertainties, and give their effect (syst. error)\n";
			ofile << "# on each process and bin\n";
			ofile << "------------" << endl;
			ofile << "bin \t";
			ofile << process << "\t" << process << "\t";
			ofile << endl;
			ofile << "process \t Zjets \t ZZ";
			ofile << endl;
			ofile << "process \t  1 \t 0";
			ofile << endl;
			ofile << "rate \t" << zjets << "\t" << zz; //signal rate
			ofile << endl;
			ofile << "------------" << endl;

			//Lumi
			//signal 
			ofile << "lumi \t lnN  \t - \t -";
			ofile << "\t #A 4.5% lumi uncertainty, affects signal and MC-driven background";
			ofile << endl;
			//ggH cross-section uncertainty
			//signal
			ofile << endl;
			//ofile << "pdf_qqbar \t lnN \t - \t 1.05 \t - \t -" << endl;

			//backgrounds
			// ofile << "CMS_hzz2l2tau_ZjetBkg \t lnN \t - \t - \t 1.3 \t -" << endl;
			double temp=0;

			ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN " << itos(bgnMap[(std::string)process]) << " \t " << dtos(bgMap[(std::string)process]/bgnMap[(std::string)process]) << " \t -" << endl;
			//			if (process=="MMTT") {
			//				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN " << itos(bgnMap[(std::string)process]) << " \t - \t - \t " << dtos(bgMap[(std::string)process]/bgnMap[(std::string)process]) << " \t -" << endl;
			//			} else if (process=="EETT"){
			//				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 629 \t - \t - \t 0.000133545 \t -" << endl;
			//			} else if (process=="EEET"){
			//				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 10 \t - \t - \t 0.024 \t -" << endl;
			//			} else if (process=="MMET"){
			//				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 5 \t - \t - \t 0.024 \t -" << endl;
			//			} else if (process=="MMMT"){
			//				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 2 \t - \t - \t 0.025 \t -" << endl;
			//			} else if (process=="EEMT"){
			//				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 3 \t - \t - \t 0.02333 \t -" << endl;
			//			}
			//
			ofile << "CMS_hzz2l2tau_ZjetBkg_extrap \t lnN  \t 1.3 \t -" << endl;		
			ofile << "CMS_hzz2l2tau_ZZBkg_extrap \t lnN \t - \t 1.1" << endl;

			int numMuons=process.CountChar('M');
			int numEles=process.CountChar('E');

			//triggers
			if (numMuons>=2) ofile << "CMS_trigger_m \t lnN  \t 1.01 \t 1.01" << endl;
			else if (numEles>=2) ofile << "CMS_trigger_e \t lnN \t 1.01 \t 1.01" << endl;

			//-------final state dependent-------
			//Muon eff systematic
			//signal
			ofile << "CMS_eff_m \t lnN \t";
			// if (numMuons>0)
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1+sqrt(numMuons*pow(0.02,2)));
			// else
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			if (process=="MMTT") ofile << "1.01 \t 1.01" << endl;
			else if (process=="MMMT") ofile << "1.02 \t 1.02" << endl;
			else if (process=="MMET") ofile << "1.01 \t 1.01" << endl;
			else if (process=="MMEM") ofile << "1.02 \t 1.02" << endl;
			else if (process=="EEMT") ofile << "1.01 \t 1.01" << endl;
			else if (process=="EEEM") ofile << "1.02 \t 1.02" << endl;
			else if (process=="EEMM") ofile << "1.03 \t 1.03" << endl;
			else if (process=="MMMM") ofile << "1.04 \t 1.04" << endl;
			else if (process=="MMEE") ofile << "1.01 \t 1.01" << endl;
			else ofile << "\t - \t -" << endl;

			//Electron eff systematic
			//signal
			ofile << "CMS_eff_e \t lnN \t";
			// if (numEles>0)
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1+sqrt(numEles*pow(0.03,2)));
			// else
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			// ofile << endl;
			if (process=="MMET") ofile << "1.06 \t 1.06" << endl;
			else if (process=="MMEM") ofile << "1.03 \t 1.03" << endl;
			else if (process=="EETT") ofile << "1.02 \t 1.02" << endl;
			else if (process=="EEMT") ofile << "1.02 \t 1.02" << endl;
			else if (process=="EEET") ofile << "1.06 \t 1.06" << endl;
			else if (process=="EEEM") ofile << "1.04 \t 1.04" << endl;
			else if (process=="EEMM") ofile << "1.02 \t 1.02" << endl;
			else if (process=="MMEE") ofile << "1.05 \t 1.05" << endl;
			else if (process=="EEEE") ofile << "1.06 \t 1.06" << endl;
			else ofile << "- \t - \t - \t -" << endl;


			//Tau ID systematic
			//signal
			ofile << "CMS_eff_t \t lnN";
			int numTaus=process.CountChar('T');
			if (numTaus==1) //et or mt -- loose has 6% uncertainty
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t" << dtos(1+sqrt(pow(0.06,2)*numTaus));
			else if (numTaus==2) //tt -- med has 6.8% uncertainty
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t" << dtos(1+sqrt(pow(0.068,2)*numTaus));
			else
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t-";
			ofile << endl;

			//Muon scale systematic
			ofile << "CMS_scale_m \t lnN";
			numMuons=process.CountChar('M');
			if (numMuons>0)
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t" << dtos(1.01);
			else
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t-";
			ofile << "\t # systematic from muon momentum scale" << endl;
			//Electron scale systematic
			ofile << "CMS_scale_e \t lnN";
			numEles=process.CountChar('E');
			if (numEles>0)
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t" << dtos(1.02);
			else
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t-";
			ofile << "\t # systematic from electron energy scale" << endl;
			//Tau ES systematic
			//temp
			ofile << "CMS_scale_t \t shape";
			//ofile << "CMS_scale_t \t lnN";
			numTaus=process.CountChar('T');
			if (numTaus>0) {
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t" << dtos(1);
				//ofile << "\t 1.03 \t 1.03 \t - \t -";
			} else
				for (unsigned int bk=0; bk<2; bk++) ofile << "\t-";
			ofile << "\t # systematic from tau energy scale" << endl;

			ofile << endl;
			ofile.close();
			//temp
		}
		void setggH(double h180, double h190, double h200, double h210, double h220, double h230, double h250, double h275, double h300, double h325, double h350, double h375, double h400, double h425, double h450, double h475, double h500, double h525, double h550, double h575, double h600){
			ggHMap["ggH180"]=h180;
			ggHMap["ggH190"]=h190;
			ggHMap["ggH200"]=h200;
			ggHMap["ggH210"]=h210;
			ggHMap["ggH220"]=h220;
			ggHMap["ggH230"]=h230;
			ggHMap["ggH250"]=h250;
			ggHMap["ggH275"]=h275;
			ggHMap["ggH300"]=h300;
			ggHMap["ggH325"]=h325;
			ggHMap["ggH350"]=h350;
			ggHMap["ggH375"]=h375;
			ggHMap["ggH400"]=h400;
			ggHMap["ggH425"]=h425;
			ggHMap["ggH450"]=h450;
			ggHMap["ggH475"]=h475;
			ggHMap["ggH500"]=h500;
			ggHMap["ggH525"]=h525;
			ggHMap["ggH550"]=h550;
			ggHMap["ggH575"]=h575;
			ggHMap["ggH600"]=h600;
			ggHMap["ggH180_CMS_scale_tDown"]=h180;
			ggHMap["ggH190_CMS_scale_tDown"]=h190;
			ggHMap["ggH200_CMS_scale_tDown"]=h200;
			ggHMap["ggH210_CMS_scale_tDown"]=h210;
			ggHMap["ggH220_CMS_scale_tDown"]=h220;
			ggHMap["ggH230_CMS_scale_tDown"]=h230;
			ggHMap["ggH250_CMS_scale_tDown"]=h250;
			ggHMap["ggH275_CMS_scale_tDown"]=h275;
			ggHMap["ggH300_CMS_scale_tDown"]=h300;
			ggHMap["ggH325_CMS_scale_tDown"]=h325;
			ggHMap["ggH350_CMS_scale_tDown"]=h350;
			ggHMap["ggH375_CMS_scale_tDown"]=h375;
			ggHMap["ggH400_CMS_scale_tDown"]=h400;
			ggHMap["ggH425_CMS_scale_tDown"]=h425;
			ggHMap["ggH450_CMS_scale_tDown"]=h450;
			ggHMap["ggH475_CMS_scale_tDown"]=h475;
			ggHMap["ggH500_CMS_scale_tDown"]=h500;
			ggHMap["ggH525_CMS_scale_tDown"]=h525;
			ggHMap["ggH550_CMS_scale_tDown"]=h550;
			ggHMap["ggH575_CMS_scale_tDown"]=h575;
			ggHMap["ggH600_CMS_scale_tDown"]=h600;
			ggHMap["ggH180_CMS_scale_tUp"]=h180;
			ggHMap["ggH190_CMS_scale_tUp"]=h190;
			ggHMap["ggH200_CMS_scale_tUp"]=h200;
			ggHMap["ggH210_CMS_scale_tUp"]=h210;
			ggHMap["ggH220_CMS_scale_tUp"]=h220;
			ggHMap["ggH230_CMS_scale_tUp"]=h230;
			ggHMap["ggH250_CMS_scale_tUp"]=h250;
			ggHMap["ggH275_CMS_scale_tUp"]=h275;
			ggHMap["ggH300_CMS_scale_tUp"]=h300;
			ggHMap["ggH325_CMS_scale_tUp"]=h325;
			ggHMap["ggH350_CMS_scale_tUp"]=h350;
			ggHMap["ggH375_CMS_scale_tUp"]=h375;
			ggHMap["ggH400_CMS_scale_tUp"]=h400;
			ggHMap["ggH425_CMS_scale_tUp"]=h425;
			ggHMap["ggH450_CMS_scale_tUp"]=h450;
			ggHMap["ggH475_CMS_scale_tUp"]=h475;
			ggHMap["ggH500_CMS_scale_tUp"]=h500;
			ggHMap["ggH525_CMS_scale_tUp"]=h525;
			ggHMap["ggH550_CMS_scale_tUp"]=h550;
			ggHMap["ggH575_CMS_scale_tUp"]=h575;
			ggHMap["ggH600_CMS_scale_tUp"]=h600;
		}
		void setvbf(double h180, double h190, double h200, double h210, double h220, double h230, double h250, double h275, double h300, double h325, double h350, double h375, double h400, double h425, double h450, double h475, double h500, double h525, double h550, double h575, double h600){
			vbfMap["vbf180"]=h180;
			vbfMap["vbf190"]=h190;
			vbfMap["vbf200"]=h200;
			vbfMap["vbf210"]=h210;
			vbfMap["vbf220"]=h220;
			vbfMap["vbf230"]=h230;
			vbfMap["vbf250"]=h250;
			vbfMap["vbf275"]=h275;
			vbfMap["vbf300"]=h300;
			vbfMap["vbf325"]=h325;
			vbfMap["vbf350"]=h350;
			vbfMap["vbf375"]=h375;
			vbfMap["vbf400"]=h400;
			vbfMap["vbf425"]=h425;
			vbfMap["vbf450"]=h450;
			vbfMap["vbf475"]=h475;
			vbfMap["vbf500"]=h500;
			vbfMap["vbf525"]=h525;
			vbfMap["vbf550"]=h550;
			vbfMap["vbf575"]=h575;
			vbfMap["vbf600"]=h600;
			vbfMap["vbf180_CMS_scale_tDown"]=h180;
			vbfMap["vbf190_CMS_scale_tDown"]=h190;
			vbfMap["vbf200_CMS_scale_tDown"]=h200;
			vbfMap["vbf210_CMS_scale_tDown"]=h210;
			vbfMap["vbf220_CMS_scale_tDown"]=h220;
			vbfMap["vbf230_CMS_scale_tDown"]=h230;
			vbfMap["vbf250_CMS_scale_tDown"]=h250;
			vbfMap["vbf275_CMS_scale_tDown"]=h275;
			vbfMap["vbf300_CMS_scale_tDown"]=h300;
			vbfMap["vbf325_CMS_scale_tDown"]=h325;
			vbfMap["vbf350_CMS_scale_tDown"]=h350;
			vbfMap["vbf375_CMS_scale_tDown"]=h375;
			vbfMap["vbf400_CMS_scale_tDown"]=h400;
			vbfMap["vbf425_CMS_scale_tDown"]=h425;
			vbfMap["vbf450_CMS_scale_tDown"]=h450;
			vbfMap["vbf475_CMS_scale_tDown"]=h475;
			vbfMap["vbf500_CMS_scale_tDown"]=h500;
			vbfMap["vbf525_CMS_scale_tDown"]=h525;
			vbfMap["vbf550_CMS_scale_tDown"]=h550;
			vbfMap["vbf575_CMS_scale_tDown"]=h575;
			vbfMap["vbf600_CMS_scale_tDown"]=h600;
			vbfMap["vbf180_CMS_scale_tUp"]=h180;
			vbfMap["vbf190_CMS_scale_tUp"]=h190;
			vbfMap["vbf200_CMS_scale_tUp"]=h200;
			vbfMap["vbf210_CMS_scale_tUp"]=h210;
			vbfMap["vbf220_CMS_scale_tUp"]=h220;
			vbfMap["vbf230_CMS_scale_tUp"]=h230;
			vbfMap["vbf250_CMS_scale_tUp"]=h250;
			vbfMap["vbf275_CMS_scale_tUp"]=h275;
			vbfMap["vbf300_CMS_scale_tUp"]=h300;
			vbfMap["vbf325_CMS_scale_tUp"]=h325;
			vbfMap["vbf350_CMS_scale_tUp"]=h350;
			vbfMap["vbf375_CMS_scale_tUp"]=h375;
			vbfMap["vbf400_CMS_scale_tUp"]=h400;
			vbfMap["vbf425_CMS_scale_tUp"]=h425;
			vbfMap["vbf450_CMS_scale_tUp"]=h450;
			vbfMap["vbf475_CMS_scale_tUp"]=h475;
			vbfMap["vbf500_CMS_scale_tUp"]=h500;
			vbfMap["vbf525_CMS_scale_tUp"]=h525;
			vbfMap["vbf550_CMS_scale_tUp"]=h550;
			vbfMap["vbf575_CMS_scale_tUp"]=h575;
			vbfMap["vbf600_CMS_scale_tUp"]=h600;
		}
		void setvbfH(){	
		}
		void fakeRates(){
			TFile *e = new TFile("sandbox/zz-latest/DATA_dR03.root");
			TFile *m = new TFile("sandbox/zz-latest/DATA_dR03.root");

			TString LEleZ = "dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10";
			TString LMuZ = "dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10";

			TString STTZt1n = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge!=0";
			TString STTZt2n = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1EleVeto&&z2l2EleVeto&&z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge!=0";
			TString STTZt1nVL = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1EleVeto&&z2l2EleVeto&&z2l1LooseIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge!=0";
			TString STTZt2nVL = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1EleVeto&&z2l2EleVeto&&z2l2LooseIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge!=0";
			TString STTZt1d  = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Charge!=0";
			TString STTZt2d  = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Charge!=0";

			TString SEEZ2n = "&&z2l2Pt>7&&z2Charge!=0&&z2l2CiCTight&1==1&&z2l2MissHits<2&&z2l2RelPFIsoDB<0.25&&met<20";
			TString SEEZ1n = "&&z2l1Pt>7&&z2Charge!=0&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2l1RelPFIsoDB<0.25&&met<20";
			TString SMMZ2n = "&&z2l2Pt>5&&z2Charge!=0&&z2l2RelPFIsoDB<0.25&&met<20";
			TString SMMZ1n = "&&z2l1Pt>5&&z2Charge!=0&&z2l1RelPFIsoDB<0.25&&met<20";
			TString SEMZMn = "&&z2l2Pt>10&&z2l2RelPFIsoDB<0.25&&z2Charge!=0&&met<20";
			TString SEMZEn = "&&z2l1Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2l1RelPFIsoDB<0.25&&z2Charge!=0&&met<20";
			TString SEEZt1d  = "&&z2l1Pt>7&&z2Charge!=0&&met<20";
			TString SEEZt2d  = "&&z2l2Pt>7&&z2Charge!=0&&met<20";
			TString SMMZt1d  = "&&z2l1Pt>5&&z2Charge!=0&&met<20";
			TString SMMZt2d  = "&&z2l2Pt>5&&z2Charge!=0&&met<20";
			TString SEMZtEd  = "&&z2l1Pt>10&&z2Charge!=0&&met<20";
			TString SEMZtMd  = "&&z2l2Pt>10&&z2Charge!=0&&met<20";
			TString SMTZn = "&&z2l1RelPFIsoDB<0.25&&z2l1Pt>10&&z2Charge!=0&&met<20";
			TString SETZn = "&&z2l1CiCTight&1==1&&z2l1Pt>10&&z2l1RelPFIsoDB<0.25&&z2l1MissHits<2&&z2Charge!=0&&met<20";
			TString SMTZd = "&&z2l1Pt>10&&z2Charge!=0&&met<20";
			TString SETZd = "&&z2l1Pt>10&&z2Charge!=0&&met<20";

			TString SEEZcuts = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l1RelPFIsoDB>0.25&&z2l2RelPFIsoDB>0.25&&z2Mass>60&&z2Mass<120"; 
			TString SMMZcuts = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPFIsoDB>0.25&&z2l1RelPFIsoDB>0.25&&z2Mass>60&&z2Mass<120";
			TString SEMZcuts = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPFIsoDB>0.25&&z2l2RelPFIsoDB>0.25&&z2Mass<90";
			TString STTZcuts = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&!z2l1MediumIsoCombDB&&!z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SMTZcuts = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SETZcuts = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&!z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.10&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";


			//
			//			////////////////////////////////Measure Fake Rate for Leptons////////////////////////////////////////////
			//
			//			e->cd();
			//			eleEleEleMuEventTreeID->cd();
			//			
			TTree *eeemTree = (TTree*)e->Get("eleEleEleMuEventTreeID/eventTree");
			//
			TGraphAsymmErrors *ee = new TGraphAsymmErrors();
			TGraphAsymmErrors *mm = new TGraphAsymmErrors();
			double DE,NE,DM,NM,NET,NMT,DET,DMT;
			TCanvas *C = new TCanvas();
			const int nBins=12;
			float xBins[nBins] = {0,5,10,15,17,19,20,30,40,50,70,100};
			TH1F *nm = new TH1F("nm", "nm", nBins-1,xBins);
			TH1F *dm = new TH1F("dm", "dm", nBins-1,xBins);
			TH1F *ne = new TH1F("ne", "ne", nBins-1,xBins);
			TH1F *de = new TH1F("de", "de", nBins-1,xBins);
			eeemTree->Draw("z2l1Pt>>ne",LEleZ+SEMZEn);
			eeemTree->Draw("z2l2Pt>>nm",LEleZ+SEMZMn);
			eeemTree->Draw("z2l1Pt>>de",LEleZ+SEMZtEd);
			eeemTree->Draw("z2l2Pt>>dm",LEleZ+SEMZtMd);
			NE = eeemTree->GetEntries(LEleZ+SEMZEn);
			DE = eeemTree->GetEntries(LEleZ+SEMZtEd);
			NM = eeemTree->GetEntries(LEleZ+SEMZMn);
			DM = eeemTree->GetEntries(LEleZ+SEMZtMd);

			//			m->cd();
			//			muMuEleMuEventTreeID->cd();
			TTree *mmemTree =(TTree*) m->Get("muMuEleMuEventTreeID/eventTree");
			TH1F *nm1 = new TH1F("nm1", "nm1", nBins-1,xBins);
			TH1F *dm1 = new TH1F("dm1", "dm1", nBins-1,xBins);
			TH1F *ne1 = new TH1F("ne1", "ne1", nBins-1,xBins);
			TH1F *de1 = new TH1F("de1", "de1", nBins-1,xBins);
			TH1F *ne2 = new TH1F("ne2", "ne2", nBins-1,xBins);
			TH1F *de2 = new TH1F("de2", "de2", nBins-1,xBins);
			mmemTree->Draw("z2l1Pt>>ne1",LMuZ+SEMZEn);
			mmemTree->Draw("z2l2Pt>>nm",LMuZ+SEMZMn);
			mmemTree->Draw("z2l1Pt>>de1",LMuZ+SEMZtEd);
			mmemTree->Draw("z2l2Pt>>dm1",LMuZ+SEMZtMd);
			ne->Add(ne,ne1);
			nm->Add(nm,nm1);
			de->Add(de,de1);
			dm->Add(dm,dm1);
			NE += mmemTree->GetEntries(LMuZ+SEMZEn);
			DE += mmemTree->GetEntries(LMuZ+SEMZtEd);
			NM += mmemTree->GetEntries(LMuZ+SEMZMn);
			DM += mmemTree->GetEntries(LMuZ+SEMZtMd);
			//			m->cd();
			//			muMuMuMuEventTreeID->cd();
			TTree *mmmmTree = (TTree*)m->Get("muMuMuMuEventTreeID/eventTree");
			//TH1F *nm1 = new TH1F("nm1", "nm1", nBins-1,xBins);
			//TH1F *dm1 = new TH1F("dm1", "dm1", nBins-1,xBins);
			TH1F *nm2 = new TH1F("nm2", "nm2", nBins-1,xBins);
			TH1F *dm2 = new TH1F("dm2", "dm2", nBins-1,xBins);
			mmmmTree->Draw("z2l1Pt>>nm1",LMuZ+SMMZ1n);
			mmmmTree->Draw("z2l2Pt>>nm2",LMuZ+SMMZ2n);
			mmmmTree->Draw("z2l1Pt>>dm1",LMuZ+SMMZt1d);
			mmmmTree->Draw("z2l2Pt>>dm2",LMuZ+SMMZt2d);
			nm->Add(nm,nm1);
			nm->Add(nm,nm2);
			dm->Add(dm,dm1);
			dm->Add(dm,dm2);
			NM += mmmmTree->GetEntries(LMuZ+SMMZ1n);
			NM += mmmmTree->GetEntries(LMuZ+SMMZ2n);
			DM += mmmmTree->GetEntries(LMuZ+SMMZt1d);
			DM += mmmmTree->GetEntries(LMuZ+SMMZt2d);
			//			e->cd();
			//			eleEleMuMuEventTreeID->cd();
			TTree *eemmTree = (TTree*)e->Get("eleEleMuMuEventTreeID/eventTree");
			eemmTree->Draw("z2l1Pt>>nm1",LEleZ+SMMZ1n);
			eemmTree->Draw("z2l2Pt>>nm2",LEleZ+SMMZ2n);
			eemmTree->Draw("z2l1Pt>>dm1",LEleZ+SMMZt1d);
			eemmTree->Draw("z2l2Pt>>dm2",LEleZ+SMMZt2d);
			nm->Add(nm,nm1);
			nm->Add(nm,nm2);
			dm->Add(dm,dm1);
			dm->Add(dm,dm2);
			NM += eemmTree->GetEntries(LEleZ+SMMZ1n);
			NM += eemmTree->GetEntries(LEleZ+SMMZ2n);
			DM += eemmTree->GetEntries(LEleZ+SMMZt1d);
			DM += eemmTree->GetEntries(LEleZ+SMMZt2d);
			//			m->cd();
			//			muMuEleEleEventTreeID->cd();
			TTree *mmeeTree = (TTree*)m->Get("muMuEleEleEventTreeID/eventTree");
			mmeeTree->Draw("z2l1Pt>>ne1",LMuZ+SEEZ1n);
			mmeeTree->Draw("z2l2Pt>>ne2",LMuZ+SEEZ2n);
			mmeeTree->Draw("z2l1Pt>>de1",LMuZ+SEEZt1d);
			mmeeTree->Draw("z2l2Pt>>de2",LMuZ+SEEZt2d);
			ne->Add(ne,ne1);
			ne->Add(ne,ne2);
			de->Add(de,de1);
			de->Add(de,de2);
			NE += mmeeTree->GetEntries(LMuZ+SEEZ1n);
			NE += mmeeTree->GetEntries(LMuZ+SEEZ2n);
			DE += mmeeTree->GetEntries(LMuZ+SEEZt1d);
			DE += mmeeTree->GetEntries(LMuZ+SEEZt2d);
			//			e->cd();
			//			eleEleEleEleEventTreeID->cd();
			//
			TTree *eeeeTree = (TTree*)e->Get("eleEleEleEleEventTreeID/eventTree");
			eeeeTree->Draw("z2l1Pt>>ne1",LEleZ+SEEZ1n);
			eeeeTree->Draw("z2l2Pt>>ne2",LEleZ+SEEZ2n);
			eeeeTree->Draw("z2l1Pt>>de1",LEleZ+SEEZt1d);
			eeeeTree->Draw("z2l2Pt>>de2",LEleZ+SEEZt2d);
			ne->Add(ne,ne1);
			ne->Add(ne,ne2);
			de->Add(de,de1);
			de->Add(de,de2);
			NE += eeeeTree->GetEntries(LEleZ+SEEZ1n);
			NE += eeeeTree->GetEntries(LEleZ+SEEZ2n);
			DE += eeeeTree->GetEntries(LEleZ+SEEZt1d);
			DE += eeeeTree->GetEntries(LEleZ+SEEZt2d);
			//			e->cd();
			//			eleEleEleTauEventTreeID->cd();
			TTree *eeetTree = (TTree*)e->Get("eleEleEleTauEventTreeID/eventTree");
			eeetTree->Draw("z2l1Pt>>ne1",LEleZ+SETZn);
			eeetTree->Draw("z2l1Pt>>de1",LEleZ+SETZd);
			ne->Add(ne,ne1);
			de->Add(de,de1);
			NE += eeetTree->GetEntries(LEleZ+SETZn);
			//	NET = eeetTree->GetEntries(LEleZ+SETZnT);
			//	DET = eeetTree->GetEntries(LEleZ+SETZd);
			DE += eeetTree->GetEntries(LEleZ+SETZd);
			//			m->cd();
			//			muMuEleTauEventTreeID->cd();
			TTree *mmetTree = (TTree*)m->Get("muMuEleTauEventTreeID/eventTree");
			mmetTree->Draw("z2l1Pt>>ne1",LMuZ+SETZn);
			mmetTree->Draw("z2l1Pt>>de1",LMuZ+SETZd);
			ne->Add(ne,ne1);
			de->Add(de,de1);
			NE += mmetTree->GetEntries(LMuZ+SETZn);
			//	NET += mmetTree->GetEntries(LMuZ+SETZnT);
			//	DET += mmetTree->GetEntries(LMuZ+SETZd);
			DE += mmetTree->GetEntries(LMuZ+SETZd);
			//			m->cd();
			//			muMuMuTauEventTreeID->cd();
			TTree *mmmtTree = (TTree*)m->Get("muMuMuTauEventTreeID/eventTree");
			mmmtTree->Draw("z2l1Pt>>nm1",LMuZ+SMTZn);
			mmmtTree->Draw("z2l1Pt>>dm1",LMuZ+SMTZd);
			nm->Add(nm,nm1);
			dm->Add(dm,dm1);
			NM += mmmtTree->GetEntries(LMuZ+SMTZn);
			//		NMT = mmmtTree->GetEntries(LMuZ+SMTZnT);
			//		DMT += mmmtTree->GetEntries(LMuZ+SMTZd);
			DM += mmmtTree->GetEntries(LMuZ+SMTZd);
			//			e->cd();
			TTree *eemtTree = (TTree*)e->Get("eleEleMuTauEventTreeID/eventTree");
			eemtTree->Draw("z2l1Pt>>nm1",LEleZ+SMTZn);
			eemtTree->Draw("z2l1Pt>>dm1",LEleZ+SMTZd);
			nm->Add(nm,nm1);
			dm->Add(dm,dm1);
			NM += eemtTree->GetEntries(LEleZ+SMTZn);
			//	DMT += eemtTree->GetEntries(LEleZ+SMTZd);
			DM += eemtTree->GetEntries(LEleZ+SMTZd);
			//
			//
			//			////////////////////////////////////// Measure fake rate for Taus  ////////////////////////////////////////////////////
			//			//Two channels combined for increased statistics: eett, mmtt
			//
			double DTau,NLoose,NMed;
			//			e->cd();
			//			eleEleTauTauEventTreeID->cd();
			TTree* eettTree = (TTree*)e->Get("eleEleTauTauEventTreeID/eventTree");
			TGraphAsymmErrors *tt = new TGraphAsymmErrors();
			TGraphAsymmErrors *lt = new TGraphAsymmErrors();
			TH1F *n1 = new TH1F("n1", "n1", 18, 10,100);
			TH1F *d1 = new TH1F("d1", "d1", 18, 10,100);
			TH1F *n1VL = new TH1F("n1VL", "n1VL", 18, 10,100);
			TH1F *d1VL = new TH1F("d1VL", "d1VL", 18, 10,100);
			TH1F *n2 = new TH1F("n2", "n2", 18, 10,100);
			TH1F *d2 = new TH1F("d2", "d2", 18, 10,100);
			TH1F *n2VL = new TH1F("n2VL", "n2VL", 18, 10,100);
			TH1F *d2VL = new TH1F("d2VL", "d2VL", 18, 10,100);
			TH1F *n3 = new TH1F("n3", "n3", 18, 10,100);
			TH1F *d3 = new TH1F("d3", "d3", 18, 10,100);
			TH1F *n3VL = new TH1F("n3VL", "n3VL", 18, 10,100);
			TH1F *d3VL = new TH1F("d3VL", "d3VL", 18, 10,100);
			eettTree->Draw("z2l1Pt>>n1",LEleZ+STTZt1n);
			eettTree->Draw("z2l2Pt>>n2",LEleZ+STTZt2n);
			eettTree->Draw("z2l1Pt>>n1VL",LEleZ+STTZt1nVL);
			eettTree->Draw("z2l2Pt>>n2VL",LEleZ+STTZt2nVL);
			TH1F *n4 = new TH1F("n4", "n3", 18, 10,100);
			TH1F *d4 = new TH1F("d4", "d3", 18, 10,100);
			TH1F *n4VL = new TH1F("n4VL", "n4VL", 18, 10,100);
			TH1F *d4VL = new TH1F("d4VL", "d4VL", 18, 10,100);
			n1->Add(n1,n2);
			n1VL->Add(n1VL,n2VL);
			NLoose = eettTree->GetEntries(LEleZ+STTZt1nVL+"&&z2l1Pt>20&&z2l2Pt>20");
			NLoose += eettTree->GetEntries(LEleZ+STTZt2nVL+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1LooseIso");
			NMed = eettTree->GetEntries(LEleZ+STTZt1n+"&&z2l1Pt>20&&z2l2Pt>20");
			NMed += eettTree->GetEntries(LEleZ+STTZt2n+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1MediumIso");
			eettTree->Draw("z2l1Pt>>d1",LEleZ+STTZt1d);
			eettTree->Draw("z2l2Pt>>d2",LEleZ+STTZt2d);
			eettTree->Draw("z2l1Pt>>d1VL",LEleZ+STTZt1d);
			eettTree->Draw("z2l2Pt>>d2VL",LEleZ+STTZt2d);
			d1->Add(d1,d2);
			d1VL->Add(d1VL,d2VL);
			DTau = 2*eettTree->GetEntries(LEleZ+STTZt2d+"&&z2l1Pt>20&&z2l2Pt>20");
			//			m->cd();
			//			muMuTauTauEventTreeID->cd();
			TTree* mmttTree = (TTree*)m->Get("muMuTauTauEventTreeID/eventTree");
			mmttTree->Draw("z2l1Pt>>n3",LMuZ+STTZt1n);
			mmttTree->Draw("z2l1Pt>>n3VL",LMuZ+STTZt1nVL);
			n1->Add(n1,n3);
			n1VL->Add(n1VL,n3VL);
			mmttTree->Draw("z2l2Pt>>n4",LMuZ+STTZt2n);
			mmttTree->Draw("z2l2Pt>>n4VL",LMuZ+STTZt2nVL);
			n1->Add(n1,n4);
			n1VL->Add(n1VL,n4VL);
			mmttTree->Draw("z2l1Pt>>d3",LMuZ+STTZt1d);
			mmttTree->Draw("z2l1Pt>>d3VL",LMuZ+STTZt1d);
			d1->Add(d1,d3);
			d1VL->Add(d1VL,d3VL);
			mmttTree->Draw("z2l2Pt>>d4",LMuZ+STTZt2d);
			mmttTree->Draw("z2l2Pt>>d4VL",LMuZ+STTZt2d);
			d1->Add(d1,d4);
			d1VL->Add(d1VL,d4VL);
			NLoose += mmttTree->GetEntries(LMuZ+STTZt1nVL+"&&z2l1Pt>20&&z2l2Pt>20");
			NLoose += mmttTree->GetEntries(LMuZ+STTZt2nVL+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1LooseIso");
			NMed += mmttTree->GetEntries(LMuZ+STTZt1n+"&&z2l1Pt>20&&z2l2Pt>20");
			NMed += mmttTree->GetEntries(LMuZ+STTZt2n+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1MediumIso");
			DTau += 2*mmttTree->GetEntries(LMuZ+STTZt2d+"&&z2l1Pt>20&&z2l2Pt>20");
			//
			//
			//			//////////////Integral Fake Rate >20/////////////////////
			//
			//			// double IFRL,IFRLErr,IFRM,IFRMErr,IFRET,IFRMT,IFRETErr,IFRMTErr;
			//			// IFRET = NET/DET;
			//			// IFRMT = NMT/DMT;
			//			// IFRL = NLoose/DTau;
			//			// IFRLErr = sqrt(NLoose/(DTau*DTau)+NLoose*NLoose/(DTau*DTau*DTau));
			//			// IFRM = NMed/DTau;
			//			// IFRMErr = sqrt(NMed/(DTau*DTau)+NMed*NMed/(DTau*DTau*DTau));
			//			// cout << "Integral Loose Fakerate = " << IFRL << " +- " << IFRLErr << endl;
			//			// cout << "Integral Medium Fakerate = " << IFRM << " +- " << IFRMErr << endl;
			//			// cout << "Integral Loose Fakerate = " << IFRET << " +- " << IFRETErr << endl;
			//			// cout << "Integral Medium Fakerate = " << IFRMT << " +- " << IFRMTErr << endl;
			//			// 
			//			// m->cd();
			//			// muMuTauTauEventTreeID->cd();
			//			// double mmtt = eventTree->GetEntries(LMuZ+STTZcuts);
			//			// double mmtt = IFRM*IFRM*mmtt/(1-IFRM*IFRM);
			//			// double mmttErr = sqrt(mmtt*IFRM*IFRM*IFRM*IFRM+4*IFRMErr*IFRMErr*mmtt*mmtt*IFRM*IFRM);
			//			// cout << "Events In Control Region " << mmtt << endl;
			//			// cout << "Background Est. for mmtt = " << mmtt << " +- " << mmttErr << endl;
			//			// e->cd();
			//			// eleEleTauTauEventTreeID->cd();
			//			// double eett = eventTree->GetEntries(LEleZ+STTZcuts);
			//			// double eett = IFRM*IFRM*eett/(1-IFRM*IFRM);
			//			// double eettErr = sqrt(eett*IFRM*IFRM*IFRM*IFRM+4*IFRMErr*IFRMErr*eett*eett*IFRM*IFRM);
			//			// cout << "Events In Control Region " << eett << endl;
			//			// cout << "Background Est. for eett = " << eett << " +- " << eettErr << endl;
			//			// e->cd();
			//			// eleEleEleTauEventTreeID->cd();
			//			// double eeet = eventTree->GetEntries(LEleZ+SETZcuts);
			//			// double eeet = IFRL*eeet/(1-IFRL);
			//			// double eeetErr = sqrt(IFRL*IFRL*eeet+eeet*eeet*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << eeet << endl;
			//			// cout << "Background Est. for eeet = " << eeet << " +- " << eeetErr << endl;
			//			// m->cd();
			//			// muMuEleTauEventTreeID->cd();
			//			// double mmet = eventTree->GetEntries(LMuZ+SETZcuts);
			//			// double mmet = IFRL*mmet/(1-IFRL);
			//			// double mmetErr = sqrt(IFRL*IFRL*mmet+mmet*mmet*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << mmet << endl;
			//			// cout << "Background Est. for mmet = " << mmet << " +- " << mmetErr << endl;
			//			// m->cd();
			//			// muMuMuTauEventTreeID->cd();
			//			// double mmmt = eventTree->GetEntries(LMuZ+SMTZcuts);
			//			// double mmmt = IFRL*mmmt/(1-IFRL);
			//			// double mmmtErr = sqrt(IFRL*IFRL*mmmt+mmmt*mmmt*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << mmmt << endl;
			//			// cout << "Background Est. for mmmt = " << mmmt << " +- " << mmmtErr << endl;
			//			// e->cd();
			//			// eleEleMuTauEventTreeID->cd();
			//			// double eemt = eventTree->GetEntries(LEleZ+SMTZcuts);
			//			// double eemt = IFRL*eemt/(1-IFRL);
			//			// double eemtErr = sqrt(IFRL*IFRL*eemt+eemt*eemt*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << eemt << endl;
			//			// cout << "Background Est. for eemt = " << eemt << " +- " << eemtErr << endl;
			//
			//
			//
			//			//////////////Fitting, pt dependant fake rates///////////////////
			tt->BayesDivide(n1,d1);
			tt->GetXaxis()->SetTitle("#tau p_{T} GeV");
			tt->GetYaxis()->SetTitle("Fake Rate");
			tt->Draw("AP");
			TF1 *myfit1 = new TF1("myfit1","[0] + [1]*exp([2]*x)", 15,100);
			myfit1->SetParameter(0, 0);
			myfit1->SetParameter(1, 0);
			myfit1->SetParameter(2, 0);
			tt->Fit("myfit1","WR");
			//			//l1=new TLine(15,IFRM,100,IFRM);
			//			//l1->SetLineColor(38);
			//			//l1->Draw();
			C->SaveAs("FitPlots/tautau.png");
			C->SaveAs("FitPlots/tautau.C");
			double c0 = myfit1->GetParameter(0);
			double c1 = myfit1->GetParameter(1);
			double c2 = myfit1->GetParameter(2);
			double e0 = myfit1->GetParError(0);
			double e1 = myfit1->GetParError(1);
			double e2 = myfit1->GetParError(2);
			lt->BayesDivide(n1VL,d1VL);
			lt->GetXaxis()->SetTitle("#tau p_{T} GeV");
			lt->GetYaxis()->SetTitle("Fake Rate");
			lt->Draw("AP");
			TF1 *myfit2 = new TF1("myfit2","[0] + [1]*exp([2]*x)", 15, 100);
			myfit2->SetParameter(0, 0);
			myfit2->SetParameter(1, 0);
			myfit2->SetParameter(2, 0);
			lt->Fit("myfit2","WR");
			//			//l2=new TLine(15,IFRL,100,IFRL);
			//			//l2->SetLineColor(38);
			//			//l2->Draw();
			C->SaveAs("FitPlots/tautauL.png");
			C->SaveAs("FitPlots/tautauL.C");
			double c0VL = myfit2->GetParameter(0);
			double c1VL = myfit2->GetParameter(1);
			double c2VL = myfit2->GetParameter(2);
			double e0VL = myfit2->GetParError(0);
			double e1VL = myfit2->GetParError(1);
			double e2VL = myfit2->GetParError(2);
			std::ostringstream S0;
			std::ostringstream S1;
			std::ostringstream S2;
			std::ostringstream E0;
			std::ostringstream E1;
			std::ostringstream E2;
			std::ostringstream S0VL;
			std::ostringstream S1VL;
			std::ostringstream S2VL;
			std::ostringstream E0VL;
			std::ostringstream E1VL;
			std::ostringstream E2VL;
			S0 << c0;
			S1 << c1;
			S2 << c2;
			E0 << e0;
			E1 << e1;
			E2 << e2;
			S0VL << c0VL;
			S1VL << c1VL;
			S2VL << c2VL;
			E0VL << e0VL;
			E1VL << e1VL;
			E2VL << e2VL;
			TString s0 = S0.str();
			TString s1 = S1.str();
			TString s2 = S2.str();
			TString se0 = E0.str();
			TString se1 = E1.str();
			TString se2 = E2.str();
			TString s0VL = S0VL.str();
			TString s1VL = S1VL.str();
			TString s2VL = S2VL.str();
			TString se0VL = E0VL.str();
			TString se1VL = E1VL.str();
			TString se2VL = E2VL.str();
			TString tt1 = "("+s0+"*z2l1Pt/z2l1Pt+"+s1+"*exp(z2l1Pt*"+s2+"))";
			TString tt2 = "("+s0+"*z2l2Pt/z2l2Pt+"+s1+"*exp(z2l2Pt*"+s2+"))";
			TString tte1 = "("+se0+"^2*z2l1Pt/z2l1Pt+("+se1+"^2+"+s1+"^2*z2l1Pt^2*"+se2+"^2)*exp(2*z2l1Pt*"+s2+"))";
			TString tte2 = "("+se0+"^2*z2l2Pt/z2l2Pt+("+se1+"^2+"+s1+"^2*z2l2Pt^2*"+se2+"^2)*exp(2*z2l2Pt*"+s2+"))";
			TString et = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
			TString mt = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
			TString ete = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";
			TString mte = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";

			/////////////////Apply fit to individual channels////////////////////////////////////

			//			m->cd();
			//			muMuTauTauEventTreeID->cd();
			TH1F* ll = new TH1F("ll","ll",1,1,2);
			TH1F* lle = new TH1F("lle","lle",1,1,2);
			TH1F* l = new TH1F("l","l",1,1,2);
			TH1F* le = new TH1F("le","le",1,1,2);
			TH1F* hTemp = new TH1F("hTemp","hTemp",1,1,2);
			mmttTree->Draw("1>>ll","("+LMuZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
			mmttTree->Draw("1>>hTemp","("+LMuZ+STTZcuts+")");
			double llv = ll->GetBinContent(1);
			mmttTree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
			double llev1 = lle->GetBinContent(1);
			mmttTree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tte1+"*"+tt2+"");
			double llev2 = lle->GetBinContent(1);
			mmttTree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tt1+"*"+tte2+"");
			double llev3 = lle->GetBinContent(1);
			double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
			cout << "Background for MMTT = " << llv << " +- " << llev << endl;
			cout << "MMTT cuts: " << LMuZ+STTZcuts << endl;
			bgMap["MMTT"] = llv;
			bgnMap["MMTT"] = mmttTree->GetEntries(LMuZ+STTZcuts);
			//std::cout << "nBGMMTT: " << bgnMap["MMTT"]<< std::endl; 
			//			e->cd();
			//			eleEleTauTauEventTreeID->cd();
			eettTree->Draw("1>>ll","("+LEleZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
			llv = ll->GetBinContent(1);
			eettTree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
			llev1 = lle->GetBinContent(1);
			eettTree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tte1+"*"+tt2+"");
			llev2 = lle->GetBinContent(1);
			eettTree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tt1+"*"+tte2+"");
			llev3 = lle->GetBinContent(1);
			llev = sqrt(llev1+llev2*llev2+llev3*llev3);
			cout << "Background for EETT = " << llv << " +- " << llev << endl;
			cout << "EETT cuts: " << LEleZ+STTZcuts << endl;
			bgMap["EETT"] = llv;
			bgnMap["EETT"] = eettTree->GetEntries(LEleZ+STTZcuts);
			//			e->cd();
			//			eleEleEleTauEventTreeID->cd();
			eeetTree->Draw("1>>l","("+LEleZ+SETZcuts+")*"+et+"/(1-"+et+")");
			double lv = l->GetBinContent(1);
			eeetTree->Draw("1>>le","("+LEleZ+SETZcuts+")*"+et+"^2");
			double ler1 = le->GetBinContent(1);
			eeetTree->Draw("1>>le","("+LEleZ+SETZcuts+")*"+ete+"");
			double ler2 = le->GetBinContent(1);
			double ler = sqrt(ler1+ler2*ler2);
			cout << "Background for EEET = " << lv << " +- " << ler << endl;
			cout << "EEET cuts: " << LEleZ+SETZcuts << endl;
			bgMap["EEET"] = lv;
			bgnMap["EEET"] = eeetTree->GetEntries(LEleZ+SETZcuts);
			//m->cd();
			//	muMuEleTauEventTreeID->cd();
			mmetTree->Draw("1>>l","("+LMuZ+SETZcuts+")*"+et+"/(1-"+et+")");
			lv = l->GetBinContent(1);
			mmetTree->Draw("1>>le","("+LMuZ+SETZcuts+")*"+et+"^2");
			ler1 = le->GetBinContent(1);
			mmetTree->Draw("1>>le","("+LMuZ+SETZcuts+")*"+ete+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			cout << "Background for MMET = " << lv << " +- " << ler << endl;
			cout << "MMET cuts: " << LMuZ+SETZcuts << endl;
			bgMap["MMET"] = lv;
			bgnMap["MMET"] = mmetTree->GetEntries(LMuZ+SETZcuts);
			//			m->cd();
			//			muMuMuTauEventTreeID->cd();
			mmmtTree->Draw("1>>l","("+LMuZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
			lv = l->GetBinContent(1);
			mmmtTree->Draw("1>>le","("+LMuZ+SMTZcuts+")*"+mt+"^2");
			ler1 = le->GetBinContent(1);
			mmmtTree->Draw("1>>le","("+LMuZ+SMTZcuts+")*"+mte+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			cout << "Background for MMMT = " << lv << " +- " << ler << endl;
			cout << "MMMT cuts: " << LMuZ+SMTZcuts << endl;
			bgMap["MMMT"] = lv;
			bgnMap["MMMT"] = mmmtTree->GetEntries(LMuZ+SMTZcuts);
			//			e->cd();
			//			eleEleMuTauEventTreeID->cd();
			eemtTree->Draw("1>>l","("+LEleZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
			lv = l->GetBinContent(1);
			eemtTree->Draw("1>>le","("+LEleZ+SMTZcuts+")*"+mt+"^2");
			ler1 = le->GetBinContent(1);
			eemtTree->Draw("1>>le","("+LEleZ+SMTZcuts+")*"+mte+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			cout << "Background for EEMT = " << lv << " +- " << ler << endl;
			cout << "EEMT cuts: " << LEleZ+SMTZcuts << endl;
			bgMap["EEMT"] = lv;
			bgnMap["EEMT"] = eemtTree->GetEntries(LEleZ+SMTZcuts);
			//
			//
			//			////////////////////////////// Integral Method for Leptons /////////////////////////////////////////////
			double IFREle,IFREleErr,IFRMu,IFRMuErr;
			IFREle = NE/DE;
			IFREleErr = sqrt(NE/(DE*DE)+NE*NE/(DE*DE*DE));
			IFRMu = NM/DM;
			IFRMuErr = sqrt(NM/(DM*DM)+NM*NM/(DM*DM*DM));
			//cout << "Integral ele fakerate = " << IFREle << " +- " << IFREleErr << endl;
			//cout << "Integral mu fakerate = " << IFRMu << " +- " << IFRMuErr << endl;
			//	e->cd();
			//			eleEleEleEleEventTreeID->cd();
			double EEEE = eeeeTree->GetEntries(LEleZ+SEEZcuts);
			double eeee = IFREle*IFREle*EEEE/(1-IFREle*IFREle);
			double eeeeErr = sqrt(EEEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*EEEE*EEEE*IFREle*IFREle);
			//cout << "Background Est. for EEEE = " << eeee << " +- " << eeeeErr << endl;
			bgMap["EEEE"] = eeee;
			bgnMap["EEEE"] = eeeeTree->GetEntries(LEleZ+SEEZcuts);
			//			//cout << "Events In Control Region " << EEEE << endl;
			//			e->cd();
			double EEEM = eeemTree->GetEntries(LEleZ+SEMZcuts);
			double eeem = IFREle*IFRMu*EEEM/(1-IFREle*IFRMu);
			double eeemErr = sqrt(eeem*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*eeem*eeem);
			cout << "Background Est. for EEEM = " << eeem << " +- " << eeemErr << endl;
			cout << "EEEM cuts: " << LEleZ+SEMZcuts << endl;
			bgMap["EEEM"] = eeem;
			bgnMap["EEEM"] = eeemTree->GetEntries(LEleZ+SEMZcuts);
			//			//cout << "Events In Control Region " << eeem << endl;
			//			m->cd();
			//			muMuEleMuEventTreeID->cd();
			double MMEM = mmemTree->GetEntries(LMuZ+SEMZcuts);
			double mmem = IFREle*IFRMu*MMEM/(1-IFREle*IFRMu);
			double mmemErr = sqrt(mmem*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*mmem*mmem);
			cout << "Background Est. for MMEM = " << mmem << " +- " << mmemErr << endl;
			cout << "MMEM cuts: " << LMuZ+SEMZcuts << endl;
			bgMap["MMEM"] = mmem;
			bgnMap["MMEM"] = mmemTree->GetEntries(LMuZ+SEMZcuts);
			//			//cout << "Events In Control Region " << mmem << endl;
			//			m->cd();
			//			muMuEleEleEventTreeID->cd();
			double MMEE = mmeeTree->GetEntries(LMuZ+SEEZcuts);
			double mmee = IFREle*IFREle*MMEE/(1-IFREle*IFREle);
			double mmeeErr = sqrt(MMEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*MMEE*MMEE*IFREle*IFREle);
			cout << "Background Est. for MMEE = " << mmee << " +- " << mmeeErr << endl;
			bgMap["MMEE"] = mmee;
			bgnMap["MMEE"] = mmeeTree->GetEntries(LMuZ+SEEZcuts);
			//			//cout << "Events In Control Region " << MMEE << endl;
			//			e->cd();
			//			eleEleMuMuEventTreeID->cd();
			double EEMM = eemmTree->GetEntries(LEleZ+SMMZcuts);
			double eemm = IFRMu*IFRMu*EEMM/(1-IFRMu*IFRMu);
			double eemmErr = sqrt(EEMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*EEMM*EEMM);
			cout << "Background Est. for EEMM = " << eemm << " +- " << eemmErr << endl;
			bgMap["EEMM"] = eemm;
			bgnMap["EEMM"] = eemmTree->GetEntries(LEleZ+SMMZcuts);
			//			//cout << "Events In Control Region " << EEMM << endl;
			//			m->cd();
			//			muMuMuMuEventTreeID->cd();
			double MMMM = mmmmTree->GetEntries(LMuZ+SMMZcuts);
			double mmmm = IFRMu*IFRMu*MMMM/(1-IFRMu*IFRMu);
			double mmmmErr = sqrt(MMMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*MMMM*MMMM);
			cout << "Background Est. for MMMM = " << mmmm << " +- " << mmmmErr << endl;
			bgMap["MMMM"] = mmmm;
			bgnMap["MMMM"] = mmmmTree->GetEntries(LMuZ+SMMZcuts);
			//			//cout << "Events In Control Region " << MMMM << endl;
			//
			mm->BayesDivide(nm,dm);
			mm->Draw("AP");
			C->SaveAs("FitPlots/mu.png");
			ee->BayesDivide(ne,de);
			ee->Draw("AP");
			C->SaveAs("FitPlots/ele.png");
			//
			//
			for (std::map<std::string, double>::const_iterator iter = bgMap.begin(); iter != bgMap.end(); ++iter){
				std::cout << iter->first << ": " << iter->second << std::endl;
			}
			for (std::map<std::string, int>::const_iterator iter = bgnMap.begin(); iter != bgnMap.end(); ++iter){
				std::cout << iter->first << ": " << iter->second << " events" << std::endl;
			}
		}
		void fakeRatesLP(){
			TFile *e = new TFile("sandbox/zz-latest/DATA2011.root");
			TFile *m = new TFile("sandbox/zz-latest/DATA2011.root");

			TString LEleZ = "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1CiCTight&1==1&&z1l2CiCTight&1==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
			TString LMuZ = "HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l1Pt>20&&z1l2Pt>10";

			TString STTZt1n = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge!=0";
			TString STTZt2n = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge!=0";
			TString STTZt1nVL = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1LooseIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge!=0";
			TString STTZt2nVL = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l2LooseIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge!=0";
			TString STTZtd  = "&&z2l1Pt>15&&z2l2Pt>15&&z2l1EleVeto&&z2l2EleVeto&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge!=0";

			TString SEEZ2n = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge!=0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20&&met<20";
			TString SEEZ1n = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge!=0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20&&met<20";
			TString SMMZ2n = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge!=0&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20&&met<20";
			TString SMMZ1n = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge!=0&&z2l1RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20&&met<20";
			TString SEMZMn = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2l2RelPfIsoRho<0.25&&z2Charge!=0&&met<20";
			TString SEMZEn = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2l1RelPfIsoRho<0.2&&z2Charge!=0&&met<20";
			TString SEEZtd  = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge!=0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&met<20";
			TString SMMZtd  = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge!=0&&(z2l1Pt+z2l2Pt)>20&&met<20";
			TString SEMZtd  = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge!=0&&met<20";
			TString SMTZn = "&&z2l2EleVeto&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.25&&z2l2Pt>20&&z2l1Pt>10&&z2Charge!=0&&z2Mass>30&&z2Mass<80&&met<20";
			TString SETZn = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPfIsoRho<0.2&&z2l1MissHits<2&&z2l2MuVeto&&z2Charge!=0&&z2Mass>30&&z2Mass<80&&met<20";
			TString SMTZnT = "&&z2l2EleVeto&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge!=0&&z2Mass>30&&z2Mass<80&&met<20";
			TString SETZnT = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge!=0&&z2Mass>30&&z2Mass<80&&met<20";
			TString SMTZd = "&&z2l2EleVeto&&z2l2MuVetoTight&&z2l2Pt>20&&z2l1Pt>10&&z2Charge!=0&&z2Mass>30&&z2Mass<80&&met<20";
			TString SETZd = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&z2l2Pt>20&&z2l1Pt>10&&z2l1MissHits<2&&z2l2MuVeto&&z2Charge!=0&&z2Mass>30&&z2Mass<80&&met<20";

			TString SEEZcuts = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho>0.2&&z2l2RelPfIsoRho>0.2&&(z2l1Pt+z2l2Pt)>20";
			TString SMMZcuts = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPfIsoRho>0.25&&z2l1RelPfIsoRho>0.25&&(z2l1Pt+z2l2Pt)>20";
			TString SEMZcuts = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&1==1&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPfIsoRho>0.2&&z2l2RelPfIsoRho>0.25";
			TString STTZcuts = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&!z2l1MediumIso&&!z2l2MediumIso&&z2l1MuVeto&&z2l2MuVeto&&z2Mass>30&&z2Mass<80&&z2Charge==0";
			TString SMTZcuts = "&&z2l2EleVeto&&!z2l2LooseIso&&z2l2MuVetoTight&&z2l1RelPfIsoRho<0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SETZcuts = "&&z2l2EleVeto&&z2l1CiCTight&1==1&&!z2l2LooseIso&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPfIsoRho<0.05&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

			//
			//			////////////////////////////////Measure Fake Rate for Leptons////////////////////////////////////////////
			//
			//			e->cd();
			//			eleEleEleMuEventTreeID->cd();
			//			
			TTree *eeemTree = (TTree*)e->Get("eleEleEleMuEventTreeID/eventTree");
			//
			TGraphAsymmErrors *ee = new TGraphAsymmErrors();
			TGraphAsymmErrors *mm = new TGraphAsymmErrors();
			double DE,NE,DM,NM,NET,NMT,DET,DMT;
			TCanvas *C = new TCanvas();
			TH1F *nm = new TH1F("nm", "nm", 10, 0,100);
			TH1F *dm = new TH1F("dm", "dm", 10, 0,100);
			TH1F *ne = new TH1F("ne", "ne", 10, 0,100);
			TH1F *de = new TH1F("de", "de", 10, 0,100);
			eeemTree->Draw("z2l1Pt>>ne",LEleZ+SEMZEn);
			eeemTree->Draw("z2l2Pt>>nm",LEleZ+SEMZMn);
			eeemTree->Draw("z2l1Pt>>de",LEleZ+SEMZtd);
			eeemTree->Draw("z2l2Pt>>dm",LEleZ+SEMZtd);
			NE = eeemTree->GetEntries(LEleZ+SEMZEn);
			DE = eeemTree->GetEntries(LEleZ+SEMZtd);
			NM = eeemTree->GetEntries(LEleZ+SEMZMn);
			DM = eeemTree->GetEntries(LEleZ+SEMZtd);

			//			m->cd();
			//			muMuEleMuEventTreeID->cd();
			TTree *mmemTree =(TTree*) m->Get("muMuEleMuEventTreeID/eventTree");
			TH1F *nm1 = new TH1F("nm1", "nm1", 10, 0,100);
			TH1F *dm1 = new TH1F("dm1", "dm1", 10, 0,100);
			TH1F *ne1 = new TH1F("ne1", "ne1", 10, 0,100);
			TH1F *de1 = new TH1F("de1", "de1", 10, 0,100);
			TH1F *nm2 = new TH1F("nm2", "nm2", 10, 0,100);
			TH1F *dm2 = new TH1F("dm2", "dm2", 10, 0,100);
			TH1F *ne2 = new TH1F("ne2", "ne2", 10, 0,100);
			TH1F *de2 = new TH1F("de2", "de2", 10, 0,100);
			mmemTree->Draw("z2l1Pt>>ne1",LMuZ+SEMZEn);
			mmemTree->Draw("z2l2Pt>>nm",LMuZ+SEMZMn);
			mmemTree->Draw("z2l1Pt>>de1",LMuZ+SEMZtd);
			mmemTree->Draw("z2l2Pt>>dm1",LMuZ+SEMZtd);
			ne->Add(ne,ne1);
			nm->Add(nm,nm1);
			de->Add(de,de1);
			dm->Add(dm,dm1);
			NE += mmemTree->GetEntries(LMuZ+SEMZEn);
			DE += mmemTree->GetEntries(LMuZ+SEMZtd);
			NM += mmemTree->GetEntries(LMuZ+SEMZMn);
			DM += mmemTree->GetEntries(LMuZ+SEMZtd);
			//			m->cd();
			//			muMuMuMuEventTreeID->cd();
			TTree *mmmmTree = (TTree*)m->Get("muMuMuMuEventTreeID/eventTree");
			mmmmTree->Draw("z2l1Pt>>nm1",LMuZ+SMMZ1n);
			mmmmTree->Draw("z2l2Pt>>nm2",LMuZ+SMMZ2n);
			mmmmTree->Draw("z2l1Pt>>dm1",LMuZ+SMMZtd);
			mmmmTree->Draw("z2l2Pt>>dm2",LMuZ+SMMZtd);
			nm->Add(nm,nm1);
			nm->Add(nm,nm2);
			dm->Add(dm,dm1);
			dm->Add(dm,dm2);
			NM += mmmmTree->GetEntries(LMuZ+SMMZ1n);
			NM += mmmmTree->GetEntries(LMuZ+SMMZ2n);
			DM += 2*mmmmTree->GetEntries(LMuZ+SMMZtd);
			//			e->cd();
			//			eleEleMuMuEventTreeID->cd();
			TTree *eemmTree = (TTree*)e->Get("eleEleMuMuEventTreeID/eventTree");
			eemmTree->Draw("z2l1Pt>>nm1",LEleZ+SMMZ1n);
			eemmTree->Draw("z2l2Pt>>nm2",LEleZ+SMMZ2n);
			eemmTree->Draw("z2l1Pt>>dm1",LEleZ+SMMZtd);
			eemmTree->Draw("z2l2Pt>>dm2",LEleZ+SMMZtd);
			nm->Add(nm,nm1);
			nm->Add(nm,nm2);
			dm->Add(dm,dm1);
			dm->Add(dm,dm2);
			NM += eemmTree->GetEntries(LEleZ+SMMZ1n);
			NM += eemmTree->GetEntries(LEleZ+SMMZ2n);
			DM += 2*eemmTree->GetEntries(LEleZ+SMMZtd);
			//			m->cd();
			//			muMuEleEleEventTreeID->cd();
			TTree *mmeeTree = (TTree*)m->Get("muMuEleEleEventTreeID/eventTree");
			mmeeTree->Draw("z2l1Pt>>ne1",LMuZ+SEEZ1n);
			mmeeTree->Draw("z2l2Pt>>ne2",LMuZ+SEEZ2n);
			mmeeTree->Draw("z2l1Pt>>de1",LMuZ+SEEZtd);
			mmeeTree->Draw("z2l2Pt>>de2",LMuZ+SEEZtd);
			ne->Add(ne,ne1);
			ne->Add(ne,ne2);
			de->Add(de,de1);
			de->Add(de,de2);
			NE += mmeeTree->GetEntries(LMuZ+SEEZ1n);
			NE += mmeeTree->GetEntries(LMuZ+SEEZ2n);
			DE += 2*mmeeTree->GetEntries(LMuZ+SEEZtd);
			//			e->cd();
			//			eleEleEleEleEventTreeID->cd();
			//
			TTree *eeeeTree = (TTree*)e->Get("eleEleEleEleEventTreeID/eventTree");
			eeeeTree->Draw("z2l1Pt>>ne1",LEleZ+SEEZ1n);
			eeeeTree->Draw("z2l2Pt>>ne2",LEleZ+SEEZ2n);
			eeeeTree->Draw("z2l1Pt>>de1",LEleZ+SEEZtd);
			eeeeTree->Draw("z2l2Pt>>de2",LEleZ+SEEZtd);
			ne->Add(ne,ne1);
			ne->Add(ne,ne2);
			de->Add(de,de1);
			de->Add(de,de2);
			NE += eeeeTree->GetEntries(LEleZ+SEEZ1n);
			NE += eeeeTree->GetEntries(LEleZ+SEEZ2n);
			DE += 2*eeeeTree->GetEntries(LEleZ+SEEZtd);
			//			e->cd();
			//			eleEleEleTauEventTreeID->cd();
			TTree *eeetTree = (TTree*)e->Get("eleEleEleTauEventTreeID/eventTree");
			eeetTree->Draw("z2l1Pt>>ne1",LEleZ+SETZn);
			eeetTree->Draw("z2l1Pt>>de1",LEleZ+SETZd);
			ne->Add(ne,ne1);
			de->Add(de,de1);
			NE += eeetTree->GetEntries(LEleZ+SETZn);
			//	NET = eeetTree->GetEntries(LEleZ+SETZnT);
			//	DET = eeetTree->GetEntries(LEleZ+SETZd);
			DE += eeetTree->GetEntries(LEleZ+SETZd);
			//			m->cd();
			//			muMuEleTauEventTreeID->cd();
			TTree *mmetTree = (TTree*)m->Get("muMuEleTauEventTreeID/eventTree");
			mmetTree->Draw("z2l1Pt>>ne1",LMuZ+SETZn);
			mmetTree->Draw("z2l1Pt>>de1",LMuZ+SETZd);
			ne->Add(ne,ne1);
			de->Add(de,de1);
			NE += mmetTree->GetEntries(LMuZ+SETZn);
			//	NET += mmetTree->GetEntries(LMuZ+SETZnT);
			//	DET += mmetTree->GetEntries(LMuZ+SETZd);
			DE += mmetTree->GetEntries(LMuZ+SETZd);
			//			m->cd();
			//			muMuMuTauEventTreeID->cd();
			TTree *mmmtTree = (TTree*)m->Get("muMuMuTauEventTreeID/eventTree");
			mmmtTree->Draw("z2l1Pt>>nm1",LMuZ+SMTZn);
			mmmtTree->Draw("z2l1Pt>>dm1",LMuZ+SMTZd);
			nm->Add(nm,nm1);
			dm->Add(dm,dm1);
			NM += mmmtTree->GetEntries(LMuZ+SMTZn);
			//		NMT = mmmtTree->GetEntries(LMuZ+SMTZnT);
			//		DMT += mmmtTree->GetEntries(LMuZ+SMTZd);
			DM += mmmtTree->GetEntries(LMuZ+SMTZd);
			//			e->cd();
			TTree *eemtTree = (TTree*)e->Get("eleEleMuTauEventTreeID/eventTree");
			eemtTree->Draw("z2l1Pt>>nm1",LEleZ+SMTZn);
			eemtTree->Draw("z2l1Pt>>dm1",LEleZ+SMTZd);
			nm->Add(nm,nm1);
			dm->Add(dm,dm1);
			NM += eemtTree->GetEntries(LEleZ+SMTZn);
			//	DMT += eemtTree->GetEntries(LEleZ+SMTZd);
			DM += eemtTree->GetEntries(LEleZ+SMTZd);
			//
			//
			//			////////////////////////////////////// Measure fake rate for Taus  ////////////////////////////////////////////////////
			//			//Two channels combined for increased statistics: eett, mmtt
			//
			double DTau,NLoose,NMed;
			//			e->cd();
			//			eleEleTauTauEventTreeID->cd();
			TTree* eettTree = (TTree*)e->Get("eleEleTauTauEventTreeID/eventTree");
			TGraphAsymmErrors *tt = new TGraphAsymmErrors();
			TGraphAsymmErrors *lt = new TGraphAsymmErrors();
			TH1F *n1 = new TH1F("n1", "n1", 10, 0,100);
			TH1F *d1 = new TH1F("d1", "d1", 10, 0,100);
			TH1F *n1VL = new TH1F("n1VL", "n1VL", 10, 0,100);
			TH1F *d1VL = new TH1F("d1VL", "d1VL", 10, 0,100);
			TH1F *n2 = new TH1F("n2", "n2", 10, 0,100);
			TH1F *d2 = new TH1F("d2", "d2", 10, 0,100);
			TH1F *n2VL = new TH1F("n2VL", "n2VL", 10, 0,100);
			TH1F *d2VL = new TH1F("d2VL", "d2VL", 10, 0,100);
			TH1F *n3 = new TH1F("n3", "n3", 10, 0,100);
			TH1F *d3 = new TH1F("d3", "d3", 10, 0,100);
			TH1F *n3VL = new TH1F("n3VL", "n3VL", 10, 0,100);
			TH1F *d3VL = new TH1F("d3VL", "d3VL", 10, 0,100);
			eettTree->Draw("z2l1Pt>>n1",LEleZ+STTZt1n);
			eettTree->Draw("z2l2Pt>>n2",LEleZ+STTZt2n);
			eettTree->Draw("z2l1Pt>>n1VL",LEleZ+STTZt1nVL);
			eettTree->Draw("z2l2Pt>>n2VL",LEleZ+STTZt2nVL);
			TH1F *n4 = new TH1F("n4", "n3", 10, 0,100);
			TH1F *d4 = new TH1F("d4", "d3", 10, 0,100);
			TH1F *n4VL = new TH1F("n4VL", "n4VL", 10, 0,100);
			TH1F *d4VL = new TH1F("d4VL", "d4VL", 10, 0,100);
			n1->Add(n1,n2);
			n1VL->Add(n1VL,n2VL);
			NLoose = eettTree->GetEntries(LEleZ+STTZt1nVL+"&&z2l1Pt>20&&z2l2Pt>20");
			NLoose += eettTree->GetEntries(LEleZ+STTZt2nVL+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1LooseIso");
			NMed = eettTree->GetEntries(LEleZ+STTZt1n+"&&z2l1Pt>20&&z2l2Pt>20");
			NMed += eettTree->GetEntries(LEleZ+STTZt2n+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1MediumIso");
			eettTree->Draw("z2l1Pt>>d1",LEleZ+STTZtd);
			eettTree->Draw("z2l2Pt>>d2",LEleZ+STTZtd);
			eettTree->Draw("z2l1Pt>>d1VL",LEleZ+STTZtd);
			eettTree->Draw("z2l2Pt>>d2VL",LEleZ+STTZtd);
			d1->Add(d1,d2);
			d1VL->Add(d1VL,d2VL);
			DTau = 2*eettTree->GetEntries(LEleZ+STTZtd+"&&z2l1Pt>20&&z2l2Pt>20");
			//			m->cd();
			//			muMuTauTauEventTreeID->cd();
			TTree* mmttTree = (TTree*)m->Get("muMuTauTauEventTreeID/eventTree");
			mmttTree->Draw("z2l1Pt>>n3",LMuZ+STTZt1n);
			mmttTree->Draw("z2l1Pt>>n3VL",LMuZ+STTZt1nVL);
			n1->Add(n1,n3);
			n1VL->Add(n1VL,n3VL);
			mmttTree->Draw("z2l2Pt>>n4",LMuZ+STTZt2n);
			mmttTree->Draw("z2l2Pt>>n4VL",LMuZ+STTZt2nVL);
			n1->Add(n1,n4);
			n1VL->Add(n1VL,n4VL);
			mmttTree->Draw("z2l1Pt>>d3",LMuZ+STTZtd);
			mmttTree->Draw("z2l1Pt>>d3VL",LMuZ+STTZtd);
			d1->Add(d1,d3);
			d1VL->Add(d1VL,d3VL);
			mmttTree->Draw("z2l2Pt>>d4",LMuZ+STTZtd);
			mmttTree->Draw("z2l2Pt>>d4VL",LMuZ+STTZtd);
			d1->Add(d1,d4);
			d1VL->Add(d1VL,d4VL);
			NLoose += mmttTree->GetEntries(LMuZ+STTZt1nVL+"&&z2l1Pt>20&&z2l2Pt>20");
			NLoose += mmttTree->GetEntries(LMuZ+STTZt2nVL+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1LooseIso");
			NMed += mmttTree->GetEntries(LMuZ+STTZt1n+"&&z2l1Pt>20&&z2l2Pt>20");
			NMed += mmttTree->GetEntries(LMuZ+STTZt2n+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1MediumIso");
			DTau += 2*mmttTree->GetEntries(LMuZ+STTZtd+"&&z2l1Pt>20&&z2l2Pt>20");
			//
			//
			//			//////////////Integral Fake Rate >20/////////////////////
			//
			//			// double IFRL,IFRLErr,IFRM,IFRMErr,IFRET,IFRMT,IFRETErr,IFRMTErr;
			//			// IFRET = NET/DET;
			//			// IFRMT = NMT/DMT;
			//			// IFRL = NLoose/DTau;
			//			// IFRLErr = sqrt(NLoose/(DTau*DTau)+NLoose*NLoose/(DTau*DTau*DTau));
			//			// IFRM = NMed/DTau;
			//			// IFRMErr = sqrt(NMed/(DTau*DTau)+NMed*NMed/(DTau*DTau*DTau));
			//			// cout << "Integral Loose Fakerate = " << IFRL << " +- " << IFRLErr << endl;
			//			// cout << "Integral Medium Fakerate = " << IFRM << " +- " << IFRMErr << endl;
			//			// cout << "Integral Loose Fakerate = " << IFRET << " +- " << IFRETErr << endl;
			//			// cout << "Integral Medium Fakerate = " << IFRMT << " +- " << IFRMTErr << endl;
			//			// 
			//			// m->cd();
			//			// muMuTauTauEventTreeID->cd();
			//			// double mmtt = eventTree->GetEntries(LMuZ+STTZcuts);
			//			// double mmtt = IFRM*IFRM*mmtt/(1-IFRM*IFRM);
			//			// double mmttErr = sqrt(mmtt*IFRM*IFRM*IFRM*IFRM+4*IFRMErr*IFRMErr*mmtt*mmtt*IFRM*IFRM);
			//			// cout << "Events In Control Region " << mmtt << endl;
			//			// cout << "Background Est. for mmtt = " << mmtt << " +- " << mmttErr << endl;
			//			// e->cd();
			//			// eleEleTauTauEventTreeID->cd();
			//			// double eett = eventTree->GetEntries(LEleZ+STTZcuts);
			//			// double eett = IFRM*IFRM*eett/(1-IFRM*IFRM);
			//			// double eettErr = sqrt(eett*IFRM*IFRM*IFRM*IFRM+4*IFRMErr*IFRMErr*eett*eett*IFRM*IFRM);
			//			// cout << "Events In Control Region " << eett << endl;
			//			// cout << "Background Est. for eett = " << eett << " +- " << eettErr << endl;
			//			// e->cd();
			//			// eleEleEleTauEventTreeID->cd();
			//			// double eeet = eventTree->GetEntries(LEleZ+SETZcuts);
			//			// double eeet = IFRL*eeet/(1-IFRL);
			//			// double eeetErr = sqrt(IFRL*IFRL*eeet+eeet*eeet*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << eeet << endl;
			//			// cout << "Background Est. for eeet = " << eeet << " +- " << eeetErr << endl;
			//			// m->cd();
			//			// muMuEleTauEventTreeID->cd();
			//			// double mmet = eventTree->GetEntries(LMuZ+SETZcuts);
			//			// double mmet = IFRL*mmet/(1-IFRL);
			//			// double mmetErr = sqrt(IFRL*IFRL*mmet+mmet*mmet*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << mmet << endl;
			//			// cout << "Background Est. for mmet = " << mmet << " +- " << mmetErr << endl;
			//			// m->cd();
			//			// muMuMuTauEventTreeID->cd();
			//			// double mmmt = eventTree->GetEntries(LMuZ+SMTZcuts);
			//			// double mmmt = IFRL*mmmt/(1-IFRL);
			//			// double mmmtErr = sqrt(IFRL*IFRL*mmmt+mmmt*mmmt*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << mmmt << endl;
			//			// cout << "Background Est. for mmmt = " << mmmt << " +- " << mmmtErr << endl;
			//			// e->cd();
			//			// eleEleMuTauEventTreeID->cd();
			//			// double eemt = eventTree->GetEntries(LEleZ+SMTZcuts);
			//			// double eemt = IFRL*eemt/(1-IFRL);
			//			// double eemtErr = sqrt(IFRL*IFRL*eemt+eemt*eemt*IFRLErr*IFRLErr);
			//			// cout << "Events In Control Region " << eemt << endl;
			//			// cout << "Background Est. for eemt = " << eemt << " +- " << eemtErr << endl;
			//
			//
			//
			//			//////////////Fitting, pt dependant fake rates///////////////////
			tt->BayesDivide(n1,d1);
			tt->GetXaxis()->SetTitle("#tau p_{T} GeV");
			tt->GetYaxis()->SetTitle("Fake Rate");
			tt->Draw("AP");
			TF1 *myfit1 = new TF1("myfit1","[0] + [1]*exp([2]*x)", 15,100);
			myfit1->SetParameter(0, 0);
			myfit1->SetParameter(1, 0);
			myfit1->SetParameter(2, 0);
			tt->Fit("myfit1","WR");
			//			//l1=new TLine(15,IFRM,100,IFRM);
			//			//l1->SetLineColor(38);
			//			//l1->Draw();
			C->SaveAs("FitPlots/tautau.png");
			C->SaveAs("FitPlots/tautau.C");
			double c0 = myfit1->GetParameter(0);
			double c1 = myfit1->GetParameter(1);
			double c2 = myfit1->GetParameter(2);
			double e0 = myfit1->GetParError(0);
			double e1 = myfit1->GetParError(1);
			double e2 = myfit1->GetParError(2);
			lt->BayesDivide(n1VL,d1VL);
			lt->GetXaxis()->SetTitle("#tau p_{T} GeV");
			lt->GetYaxis()->SetTitle("Fake Rate");
			lt->Draw("AP");
			TF1 *myfit2 = new TF1("myfit2","[0] + [1]*exp([2]*x)", 15, 100);
			myfit2->SetParameter(0, 0);
			myfit2->SetParameter(1, 0);
			myfit2->SetParameter(2, 0);
			lt->Fit("myfit2","WR");
			//			//l2=new TLine(15,IFRL,100,IFRL);
			//			//l2->SetLineColor(38);
			//			//l2->Draw();
			C->SaveAs("FitPlots/tautauL.png");
			C->SaveAs("FitPlots/tautauL.C");
			double c0VL = myfit2->GetParameter(0);
			double c1VL = myfit2->GetParameter(1);
			double c2VL = myfit2->GetParameter(2);
			double e0VL = myfit2->GetParError(0);
			double e1VL = myfit2->GetParError(1);
			double e2VL = myfit2->GetParError(2);
			std::ostringstream S0;
			std::ostringstream S1;
			std::ostringstream S2;
			std::ostringstream E0;
			std::ostringstream E1;
			std::ostringstream E2;
			std::ostringstream S0VL;
			std::ostringstream S1VL;
			std::ostringstream S2VL;
			std::ostringstream E0VL;
			std::ostringstream E1VL;
			std::ostringstream E2VL;
			S0 << c0;
			S1 << c1;
			S2 << c2;
			E0 << e0;
			E1 << e1;
			E2 << e2;
			S0VL << c0VL;
			S1VL << c1VL;
			S2VL << c2VL;
			E0VL << e0VL;
			E1VL << e1VL;
			E2VL << e2VL;
			TString s0 = S0.str();
			TString s1 = S1.str();
			TString s2 = S2.str();
			TString se0 = E0.str();
			TString se1 = E1.str();
			TString se2 = E2.str();
			TString s0VL = S0VL.str();
			TString s1VL = S1VL.str();
			TString s2VL = S2VL.str();
			TString se0VL = E0VL.str();
			TString se1VL = E1VL.str();
			TString se2VL = E2VL.str();
			TString tt1 = "("+s0+"*z2l1Pt/z2l1Pt+"+s1+"*exp(z2l1Pt*"+s2+"))";
			TString tt2 = "("+s0+"*z2l2Pt/z2l2Pt+"+s1+"*exp(z2l2Pt*"+s2+"))";
			TString tte1 = "("+se0+"^2*z2l1Pt/z2l1Pt+("+se1+"^2+"+s1+"^2*z2l1Pt^2*"+se2+"^2)*exp(2*z2l1Pt*"+s2+"))";
			TString tte2 = "("+se0+"^2*z2l2Pt/z2l2Pt+("+se1+"^2+"+s1+"^2*z2l2Pt^2*"+se2+"^2)*exp(2*z2l2Pt*"+s2+"))";
			TString et = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
			TString mt = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
			TString ete = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";
			TString mte = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";

			/////////////////Apply fit to individual channels////////////////////////////////////

			//			m->cd();
			//			muMuTauTauEventTreeID->cd();
			TH1F* ll = new TH1F("ll","ll",1,1,2);
			TH1F* lle = new TH1F("lle","lle",1,1,2);
			TH1F* l = new TH1F("l","l",1,1,2);
			TH1F* le = new TH1F("le","le",1,1,2);
			TH1F* hTemp = new TH1F("hTemp","hTemp",1,1,2);
			mmttTree->Draw("1>>ll","("+LMuZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
			mmttTree->Draw("1>>hTemp","("+LMuZ+STTZcuts+")");
			double llv = ll->GetBinContent(1);
			mmttTree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
			double llev1 = lle->GetBinContent(1);
			mmttTree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tte1+"*"+tt2+"");
			double llev2 = lle->GetBinContent(1);
			mmttTree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tt1+"*"+tte2+"");
			double llev3 = lle->GetBinContent(1);
			double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
			cout << "Background for MMTT = " << llv << " +- " << llev << endl;
			bgMap["MMTT"] = llv;
			bgnMap["MMTT"] = mmttTree->GetEntries(LMuZ+STTZcuts);
			std::cout << "nBGMMTT: " << bgnMap["MMTT"]<< std::endl; 
			//			e->cd();
			//			eleEleTauTauEventTreeID->cd();
			eettTree->Draw("1>>ll","("+LEleZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
			llv = ll->GetBinContent(1);
			eettTree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
			llev1 = lle->GetBinContent(1);
			eettTree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tte1+"*"+tt2+"");
			llev2 = lle->GetBinContent(1);
			eettTree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tt1+"*"+tte2+"");
			llev3 = lle->GetBinContent(1);
			llev = sqrt(llev1+llev2*llev2+llev3*llev3);
			cout << "Background for EETT = " << llv << " +- " << llev << endl;
			bgMap["EETT"] = llv;
			bgnMap["EETT"] = eettTree->GetEntries(LEleZ+STTZcuts);
			//			e->cd();
			//			eleEleEleTauEventTreeID->cd();
			eeetTree->Draw("1>>l","("+LEleZ+SETZcuts+")*"+et+"/(1-"+et+")");
			double lv = l->GetBinContent(1);
			eeetTree->Draw("1>>le","("+LEleZ+SETZcuts+")*"+et+"^2");
			double ler1 = le->GetBinContent(1);
			eeetTree->Draw("1>>le","("+LEleZ+SETZcuts+")*"+ete+"");
			double ler2 = le->GetBinContent(1);
			double ler = sqrt(ler1+ler2*ler2);
			cout << "Background for EEET = " << lv << " +- " << ler << endl;
			bgMap["EEET"] = lv;
			bgnMap["EEET"] = eeetTree->GetEntries(LEleZ+SETZcuts);
			//m->cd();
			//	muMuEleTauEventTreeID->cd();
			mmetTree->Draw("1>>l","("+LMuZ+SETZcuts+")*"+et+"/(1-"+et+")");
			lv = l->GetBinContent(1);
			mmetTree->Draw("1>>le","("+LMuZ+SETZcuts+")*"+et+"^2");
			ler1 = le->GetBinContent(1);
			mmetTree->Draw("1>>le","("+LMuZ+SETZcuts+")*"+ete+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			cout << "Background for mmet = " << lv << " +- " << ler << endl;
			bgMap["MMET"] = lv;
			bgnMap["MMET"] = mmetTree->GetEntries(LMuZ+SETZcuts);
			//			m->cd();
			//			muMuMuTauEventTreeID->cd();
			mmmtTree->Draw("1>>l","("+LMuZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
			lv = l->GetBinContent(1);
			mmmtTree->Draw("1>>le","("+LMuZ+SMTZcuts+")*"+mt+"^2");
			ler1 = le->GetBinContent(1);
			mmmtTree->Draw("1>>le","("+LMuZ+SMTZcuts+")*"+mte+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			cout << "Background for MMMT = " << lv << " +- " << ler << endl;
			bgMap["MMMT"] = lv;
			bgnMap["MMMT"] = mmmtTree->GetEntries(LMuZ+SMTZcuts);
			//			e->cd();
			//			eleEleMuTauEventTreeID->cd();
			eemtTree->Draw("1>>l","("+LEleZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
			lv = l->GetBinContent(1);
			eemtTree->Draw("1>>le","("+LEleZ+SMTZcuts+")*"+mt+"^2");
			ler1 = le->GetBinContent(1);
			eemtTree->Draw("1>>le","("+LEleZ+SMTZcuts+")*"+mte+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			cout << "Background for eemt = " << lv << " +- " << ler << endl;
			bgMap["EEMT"] = lv;
			bgnMap["EEMT"] = eemtTree->GetEntries(LEleZ+SMTZcuts);
			//
			//
			//			////////////////////////////// Integral Method for Leptons /////////////////////////////////////////////
			double IFREle,IFREleErr,IFRMu,IFRMuErr;
			IFREle = NE/DE;
			IFREleErr = sqrt(NE/(DE*DE)+NE*NE/(DE*DE*DE));
			IFRMu = NM/DM;
			IFRMuErr = sqrt(NM/(DM*DM)+NM*NM/(DM*DM*DM));
			cout << "Integral ele fakerate = " << IFREle << " +- " << IFREleErr << endl;
			cout << "Integral mu fakerate = " << IFRMu << " +- " << IFRMuErr << endl;
			//	e->cd();
			//			eleEleEleEleEventTreeID->cd();
			double EEEE = eeeeTree->GetEntries(LEleZ+SEEZcuts);
			double eeee = IFREle*IFREle*EEEE/(1-IFREle*IFREle);
			double eeeeErr = sqrt(EEEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*EEEE*EEEE*IFREle*IFREle);
			cout << "Background Est. for EEEE = " << eeee << " +- " << eeeeErr << endl;
			bgMap["EEEE"] = eeee;
			bgnMap["EEEE"] = eeeeTree->GetEntries(LEleZ+SEEZcuts);
			//			//cout << "Events In Control Region " << EEEE << endl;
			//			e->cd();
			double EEEM = eeemTree->GetEntries(LEleZ+SEMZcuts);
			double eeem = IFREle*IFRMu*EEEM/(1-IFREle*IFRMu);
			double eeemErr = sqrt(eeem*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*eeem*eeem);
			cout << "Background Est. for EEEM = " << eeem << " +- " << eeemErr << endl;
			bgMap["EEEM"] = eeem;
			bgnMap["EEEM"] = eeemTree->GetEntries(LEleZ+SEMZcuts);
			//			//cout << "Events In Control Region " << eeem << endl;
			//			m->cd();
			//			muMuEleMuEventTreeID->cd();
			double MMEM = mmemTree->GetEntries(LMuZ+SEMZcuts);
			double mmem = IFREle*IFRMu*MMEM/(1-IFREle*IFRMu);
			double mmemErr = sqrt(mmem*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*mmem*mmem);
			cout << "Background Est. for mmem = " << mmem << " +- " << mmemErr << endl;
			bgMap["MMEM"] = mmem;
			bgnMap["MMEM"] = mmemTree->GetEntries(LMuZ+SEMZcuts);
			//			//cout << "Events In Control Region " << mmem << endl;
			//			m->cd();
			//			muMuEleEleEventTreeID->cd();
			double MMEE = mmeeTree->GetEntries(LMuZ+SEEZcuts);
			double mmee = IFREle*IFREle*MMEE/(1-IFREle*IFREle);
			double mmeeErr = sqrt(MMEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*MMEE*MMEE*IFREle*IFREle);
			cout << "Background Est. for MMEE = " << mmee << " +- " << mmeeErr << endl;
			bgMap["MMEE"] = mmee;
			bgnMap["MMEE"] = mmeeTree->GetEntries(LMuZ+SEEZcuts);
			//			//cout << "Events In Control Region " << MMEE << endl;
			//			e->cd();
			//			eleEleMuMuEventTreeID->cd();
			double EEMM = eemmTree->GetEntries(LEleZ+SMMZcuts);
			double eemm = IFRMu*IFRMu*EEMM/(1-IFRMu*IFRMu);
			double eemmErr = sqrt(EEMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*EEMM*EEMM);
			cout << "Background Est. for EEMM = " << eemm << " +- " << eemmErr << endl;
			bgMap["EEMM"] = eemm;
			bgnMap["EEMM"] = eemmTree->GetEntries(LEleZ+SMMZcuts);
			//			//cout << "Events In Control Region " << EEMM << endl;
			//			m->cd();
			//			muMuMuMuEventTreeID->cd();
			double MMMM = mmmmTree->GetEntries(LMuZ+SMMZcuts);
			double mmmm = IFRMu*IFRMu*MMMM/(1-IFRMu*IFRMu);
			double mmmmErr = sqrt(MMMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*MMMM*MMMM);
			cout << "Background Est. for MMMM = " << mmmm << " +- " << mmmmErr << endl;
			bgMap["MMMM"] = mmmm;
			bgnMap["MMMM"] = mmmmTree->GetEntries(LMuZ+SMMZcuts);
			//			//cout << "Events In Control Region " << MMMM << endl;
			//
			mm->BayesDivide(nm,dm);
			mm->Draw("AP");
			C->SaveAs("FitPlots/mu.png");
			ee->BayesDivide(ne,de);
			ee->Draw("AP");
			C->SaveAs("FitPlots/ele.png");
			//
			//
			for (std::map<std::string, double>::const_iterator iter = bgMap.begin(); iter != bgMap.end(); ++iter){
				std::cout << iter->first << ": " << iter->second << std::endl;
			}
			std::cout << bgMap.size() << " map" << std::endl;
			std::cout << bgnMap.size() << " n map" << std::endl;
			for (std::map<std::string, int>::const_iterator iter = bgnMap.begin(); iter != bgnMap.end(); ++iter){
				std::cout << iter->first << ": " << iter->second << " events" << std::endl;
			}
		}
				
		void zzBG(){
			// ....
			// hard coded for now
			zzBgMap["EEEE"] = 10.39*1.044;
			zzBgMap["EEEM"] = 0.49*1.044; 
			zzBgMap["EEET"] = 1.07*1.044; 
			zzBgMap["EEMM"] = 5.69*1.044;
			zzBgMap["EEMT"] = 0.90*1.044;
			zzBgMap["EETT"] = 0.75*1.044;
			zzBgMap["MMEE"] = 19.84*1.053;
			zzBgMap["MMEM"] = 0.55*1.053;
			zzBgMap["MMET"] = 1.14*1.053;
			zzBgMap["MMMM"] = 14.37*1.053;
			zzBgMap["MMMT"] = 1.03*1.053;
			zzBgMap["MMTT"] = 0.75*1.053;
		}
		std::string dtos(double n){
			std::stringstream ss;
			ss << n;
			return ss.str();
		}
		std::string itos(unsigned int n){
			std::stringstream ss;
			ss << n;
			return ss.str();
		}

	void eventYields(){
		fakeRates();
	}
	private:
		std::vector<TChain*> trees_;
		std::vector<TString> labels_;
		std::vector<TString> preselection_;
		std::vector<int> types_;
		std::vector<int> styles_;
		std::vector<TString> hMass_;
		std::vector<int> hMassn_;
		std::vector<double> contrib_;
		std::vector<TString> winLow_;
		std::vector<TString> winHigh_;
		std::vector<std::vector<double> > backgrounds_;
		std::vector<std::vector<TString> > backgroundLabels_;
		std::vector<std::vector<double> > bgScales_; //MC-based scaling factor (yield noIso in window/yield noIso total)
		std::vector<double> observed_;
		std::vector<double> dataDrivenBG_;
		std::map<std::string, double> bgMap;
		std::map<std::string, int> bgnMap;
		std::map<std::string, double> zzBgMap;
		std::map<std::string, double> ggHMap;
		std::map<std::string, double> vbfMap;
		TString process;
		ofstream ofile;
		ofstream ofile2;
		ofstream ofileDD;

};
