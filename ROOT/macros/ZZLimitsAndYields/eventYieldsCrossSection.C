#include "helpers.h"
#include "TGraphAsymmErrors.h"
#include "TF1.h"
#include <map>
#include <utility>

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

//			fakeRates();
			//fakeRatesLP();
			applyFakerates();
			zzBG();
			//			don't need the histograms
//			makeHists(selection,selectionNoIso,lumi,"hzz2l2t");

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
//					if (abs(zz-hh->Integral())/zz > 0.10) std::cout << "DIFFERENCE GREATER THAN 10% ---- CHECK IT" << std::endl;
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
//					if (abs(gg-hh->Integral())/gg > 0.10) std::cout << "DIFFERENCE GREATER THAN 10% ---- CHECK IT" << std::endl;
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
//					if (abs(vbf-hh->Integral())/vbf > 0.10) std::cout << "DIFFERENCE GREATER THAN 10% ---- CHECK IT" << std::endl;
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
		void applyFakerates() {

			string line;
			ifstream fRstream("fakeRates");
			vector <string> lines;
			std::map<string,string> frMap;
			std::map<string,string> freMap;
			using namespace std;
			if (fRstream.is_open()){
				while (fRstream.good()){
					getline (fRstream,line);
					lines.push_back(line);
				}
			}
			std::cout << "---- Using parameters: ----" << std::endl;
			for (int i=0; i<lines.size(); ++i){
				std::cout << lines.at(i) << std::endl;
				if (i%2!=0){
					//			std::cout << lines.at(i-1) << ":" << lines.at(i) << std::endl;
					frMap[lines.at(i-1)]=lines.at(i);	
				}
			}
			//	for (map<string, string>::iterator iter = frMap.begin(); iter != frMap.end(); ++iter){
			//		std::cout << iter->first << ": " << iter->second << endl;
			//	}


			//	TFile *e = new TFile("sandbox/zz-latest/DATA.root");
			//	TFile *m = new TFile("sandbox/zz-latest/DATA.root");
			TFile *e = new TFile("/scratch/iross/BG_StdIso.root");
			TFile *m = new TFile("/scratch/iross/BG_StdIso.root");
			TString LEleZ = "dZ13<0.10&&dZ14<0.10&&z1l1SIP<4&&z1l2SIP<4&&HLT_Any&&z1Mass>40&&z1Mass<120&&(z1l1CiCTight&1)==1&&(z1l2CiCTight&1)==1&&z1l1MissHits<2&&z1l2MissHits<2&&"+stdIso("z1l1",0.275,"ele")+"&&"+stdIso("z1l2",0.275,"ele")+"&&z1l1Pt>20&&z1l2Pt>10";
			TString LMuZ = "dZ13<0.10&&dZ14<0.10&&z1l1SIP<4&&z1l2SIP<4&&HLT_Any&&z1Mass>40&&z1Mass<120&&"+stdIso("z1l1",0.275,"mu")+"&&"+stdIso("z1l2",0.275,"mu")+"&&z1l1Pt>20&&z1l2Pt>10";

			TString SEEZcuts_aa = "&&2&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&!"+stdIso("z2l1",0.275,"ele")+"&&!"+stdIso("z2l2",0.275,"ele")+"&&(z2l1CiCTight&1)==1&&(z2l2CiCTight&1)==1&&z2Mass>12&&z2Mass<120";
			TString SMMZcuts_aa = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&!"+stdIso("z2l1",0.275,"mu")+"&&!"+stdIso("z2l2",0.275,"mu")+"&&z2Mass>12&&z2Mass<120";
			TString SEMZcuts_aa = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1MissHits<2&&z2Charge==0&&z2l1CiCTight&1==1&&!"+stdIso("z2l1",0.275,"ele")+"&&!"+stdIso("z2l2",0.275,"mu")+"&&z2Mass<90";
			TString STTZcuts_aa = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&!z2l1MediumIsoCombDB&&!z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SMTZcuts_aa = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2MuVetoTight&&!"+stdIso("z2l1",0.10,"mu")+"&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SETZcuts_aa = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&!"+stdIso("z2l1",0.08,"ele")+"&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

			TString SEEZcuts_ai = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&!"+stdIso("z2l1",0.275,"ele")+"&&"+stdIso("z2l2",0.275,"ele")+"&&(z2l1CiCTight&1)==1&&(z2l2CiCTight&1)==1&&z2Mass>12&&z2Mass<120";
			TString SMMZcuts_ai = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&!"+stdIso("z2l1",0.275,"mu")+"&&"+stdIso("z2l2",0.275,"mu")+"&&z2Mass>12&&z2Mass<120";
			TString SEMZcuts_ai = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1MissHits<2&&z2Charge==0&&z2l1CiCTight&1==1&&!"+stdIso("z2l1",0.275,"ele")+"&&"+stdIso("z2l2",0.275,"mu")+"&&z2Mass<90";
			TString STTZcuts_ai = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&!z2l1MediumIsoCombDB&&z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SMTZcuts_ai = "&&z2l2EleVeto&&z2l2LooseIsoCombDB&&z2l2MuVetoTight&&!"+stdIso("z2l1",0.10,"mu")+"&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SETZcuts_ai = "&&z2l2EleVeto&&z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&!"+stdIso("z2l1",0.08,"ele")+"&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

			TString SEEZcuts_ia = "&&2&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&"+stdIso("z2l1",0.275,"ele")+"&&!"+stdIso("z2l2",0.275,"ele")+"&&(z2l1CiCTight&1)==1&&(z2l2CiCTight&1)==1&&z2Mass>12&&z2Mass<120";
			TString SMMZcuts_ia = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&"+stdIso("z2l1",0.275,"mu")+"&&!"+stdIso("z2l2",0.275,"mu")+"&&z2Mass>12&&z2Mass<120";
			TString SEMZcuts_ia = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1MissHits<2&&z2Charge==0&&z2l1CiCTight&1==1&&"+stdIso("z2l1",0.275,"ele")+"&&!"+stdIso("z2l2",0.275,"mu")+"&&z2Mass<90";
			TString STTZcuts_ia = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIsoCombDB&&!z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SMTZcuts_ia = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2MuVetoTight&&"+stdIso("z2l1",0.10,"mu")+"&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
			TString SETZcuts_ia = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&"+stdIso("z2l1",0.08,"ele")+"&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

			TString SEEZcuts = SEEZcuts_aa; TString SMMZcuts = SMMZcuts_aa; TString SEMZcuts = SEMZcuts_aa;
			TString STTZcuts = STTZcuts_aa; TString SMTZcuts = SMTZcuts_aa; TString SETZcuts = SETZcuts_aa;
			//
			//////////////Fitting, pt dependent fake rates///////////////////
			TString s0 = frMap["s0"];
			TString s1 = frMap["s1"];
			TString s2 = frMap["s2"];
			TString se0 = frMap["se0"];
			TString se1 = frMap["se1"];
			TString se2 = frMap["se2"];
			TString s0VL = frMap["s0VL"];
			TString s1VL = frMap["s1VL"];
			TString s2VL = frMap["s2VL"];
			TString se0VL = frMap["se0VL"];
			TString se1VL = frMap["se1VL"];
			TString se2VL = frMap["se2VL"];
			TString tt1 = "("+s0+"*z2l1Pt/z2l1Pt+"+s1+"*exp(z2l1Pt*"+s2+"))";
			TString tt2 = "("+s0+"*z2l2Pt/z2l2Pt+"+s1+"*exp(z2l2Pt*"+s2+"))";
			TString tte1 = "("+se0+"^2*z2l1Pt/z2l1Pt+("+se1+"^2+"+s1+"^2*z2l1Pt^2*"+se2+"^2)*exp(2*z2l1Pt*"+s2+"))";
			TString tte2 = "("+se0+"^2*z2l2Pt/z2l2Pt+("+se1+"^2+"+s1+"^2*z2l2Pt^2*"+se2+"^2)*exp(2*z2l2Pt*"+s2+"))";
			TString et = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
			std::cout << et << std::endl;
			TString mt = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
			TString ete = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";
			TString mte = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";
			TString eleFR = frMap["eleFR"];
			TString eleFRe = frMap["eleFRe"];
			TString eletFR = frMap["eletFR"];
			TString eletFRe = frMap["eletFRe"];
			TString muFR = frMap["muFR"];
			TString muFRe = frMap["muFRe"];
			TString mutFR = frMap["mutFR"];
			TString mutFRe = frMap["mutFRe"];
			/////////////////Apply fit to individual channels////////////////////////////////////
			double IFREle,IFREleErr,IFRMu,IFRMuErr;
			IFREle = atof(frMap["eleFR"].c_str());
			IFREleErr = atof(frMap["eleFre"].c_str());
			IFRMu = atof(frMap["muFR"].c_str());
			IFRMuErr = atof(frMap["muFRe"].c_str());
			TH1F* ll = new TH1F("ll","ll",1,1,2);
			TH1F* ll2 = new TH1F("ll2","ll2",1,1,2);
			TH1F* lle = new TH1F("lle","lle",1,1,2);
			TH1F* l = new TH1F("l","l",1,1,2);
			TH1F* le = new TH1F("le","le",1,1,2);
			TTree* tree;
			tree = (TTree*)m->Get("muMuTauTauEventTree_antiIso/eventTree");
			tree->Draw("1>>ll","("+LMuZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
			double llv = ll->GetBinContent(1);
			tree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
			double llev1 = lle->GetBinContent(1);
			tree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tte1+"*"+tt2+"");
			double llev2 = lle->GetBinContent(1);
			tree->Draw("1>>lle","("+LMuZ+STTZcuts+")*"+tt1+"*"+tte2+"");
			double llev3 = lle->GetBinContent(1);
			double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
			//printf("$\\mu\\mu\\tauh\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",llv,llev);
			cout << "MMTT: " << llv << "(" << tree->GetEntries(LMuZ+STTZcuts) << ")" << endl;
			bgMap["MMTT"]=llv; bgnMap["MMTT"]=tree->GetEntries(LMuZ+STTZcuts);
			//cout << "MMTT fakeable: " << eventTree->GetEntries(LMuZ+STTZcuts) << endl;
			//cout << "Background for MMTT = " << llv << " +- " << llev << endl;
			//cout << "MMTT cuts: " << LMuZ << STTZcuts << endl;
			//cout << "MMTT: " << llv/0.409 << endl;
			tree=(TTree*)e->Get("eleEleTauTauEventTree_antiIso/eventTree");
			tree->Draw("1>>ll","("+LEleZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
			llv = ll->GetBinContent(1);
			tree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
			llev1 = lle->GetBinContent(1);
			tree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tte1+"*"+tt2+"");
			llev2 = lle->GetBinContent(1);
			tree->Draw("1>>lle","("+LEleZ+STTZcuts+")*"+tt1+"*"+tte2+"");
			llev3 = lle->GetBinContent(1);
			llev = sqrt(llev1+llev2*llev2+llev3*llev3);/////
			cout << "EETT: " << llv << "(" << tree->GetEntries(LEleZ+STTZcuts) << ")" << endl;
			bgMap["EETT"]=llv; bgnMap["EETT"]=tree->GetEntries(LEleZ+STTZcuts);
			//printf("$ee\\tauh\\tauh$ & $--$ & $ %0.2f \\pm  %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",llv,llev);
			//cout << "EETT fakeable: " << eventTree->GetEntries(LEleZ+STTZcuts) << endl;
			//cout << "Background for EETT = " << llv << " +- " << llev << endl;
			//cout << "EETT cuts: " << LEleZ << STTZcuts << endl;
			//cout << "EETT: " << llv/0.360 << endl;
			tree=(TTree*)e->Get("eleEleEleTauEventTree_antiIso/eventTree");
			// need to fix this stuff so that the fake rate for e is applied.
			std::cout << "test" << tree->GetEntries(LEleZ+SETZcuts) << "\t" << eletFR << "\t" << et << std::endl;
			std::cout << "("+LEleZ+SETZcuts+")*"+eletFR+"*"+et+"/(1-"+eletFR+"*"+et+")" << std::endl;
			tree->Draw("1>>l","("+LEleZ+SETZcuts+")*"+eletFR+"*"+et+"/(1-"+eletFR+"*"+et+")");
			double lv;
			lv = l->GetBinContent(1);
			cout << "test2" << lv << endl;
			tree->Draw("1>>le","("+LEleZ+SETZcuts+")*"+et+"^2");
			double ler1 = le->GetBinContent(1);
			tree->Draw("1>>le","("+LEleZ+SETZcuts+")*"+ete+"");
			double ler2 = le->GetBinContent(1);
			double ler = sqrt(ler1+ler2*ler2);
			//printf("$ee\\tau_{e}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
			cout << "EEET: " << lv << "(" << tree->GetEntries(LEleZ+SETZcuts) << ")" << endl;
			bgMap["EEET"]=lv; bgnMap["EEET"]=tree->GetEntries(LEleZ+SETZcuts);
			//cout << "EEET fakeable: " << tree->GetEntries(LEleZ+SETZcuts) << endl;
			//cout << "Background for EEET = " << lv << " +- " << ler << endl;
			//cout << "EEET cuts: " << LEleZ << SETZcuts << endl;
			//cout << "EEET: " << lv/0.476 << endl;
			tree=(TTree*)m->Get("muMuEleTauEventTree_antiIso/eventTree");
			tree->Draw("1>>l","("+LMuZ+SETZcuts+")*"+eletFR+"*"+et+"/(1-"+eletFR+"*"+et+")");
			lv = l->GetBinContent(1);
			tree->Draw("1>>le","("+LMuZ+SETZcuts+")*"+et+"^2");
			ler1 = le->GetBinContent(1);
			tree->Draw("1>>le","("+LMuZ+SETZcuts+")*"+ete+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			//printf("$\\mu\\mu\\tau_{e}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
			//cout << "MMET fakeable: " << tree->GetEntries(LMuZ+SETZcuts) << endl;
			cout << "MMET: " << lv << "(" << tree->GetEntries(LMuZ+SETZcuts) << ")" << endl;
			bgMap["MMET"]=lv; bgnMap["MMET"]=tree->GetEntries(LMuZ+SETZcuts);
			//cout << "Background for MMET = " << lv << " +- " << ler << endl;
			//cout << "MMET cuts: " << LMuZ << SETZcuts << endl;
			//cout << "MMET: " << lv/0.345 << endl;
			tree=(TTree*)m->Get("muMuMuTauEventTree_antiIso/eventTree");
			tree->Draw("1>>l","("+LMuZ+SMTZcuts+")*"+mutFR+"*"+mt+"/(1-"+mutFR+"*"+mt+")");
			lv = l->GetBinContent(1);
			tree->Draw("1>>le","("+LMuZ+SMTZcuts+")*"+mt+"^2");
			ler1 = le->GetBinContent(1);
			tree->Draw("1>>le","("+LMuZ+SMTZcuts+")*"+mte+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			//printf("$\\mu\\mu\\tau_{\\mu}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
			//cout << "MMMT fakeable: " << tree->GetEntries(LMuZ+SMTZcuts) << endl;
			cout << "MMMT: " << lv << "(" << tree->GetEntries(LMuZ+SMTZcuts) << ")" << endl;
			bgMap["MMMT"]=lv; bgnMap["MMMT"]=tree->GetEntries(LMuZ+SMTZcuts);
			//cout << "Background for MMMT = " << lv << " +- " << ler << endl;
			//cout << "MMMT cuts: " << LMuZ << SMTZcuts << endl;
			//cout << "MMMT: " << lv/0.147 << endl;
			tree=(TTree*)e->Get("eleEleMuTauEventTree_antiIso/eventTree");
			tree->Draw("1>>l","("+LEleZ+SMTZcuts+")*"+mutFR+"*"+mt+"/(1-"+mutFR+"*"+mt+")");
			lv = l->GetBinContent(1);
			tree->Draw("1>>le","("+LEleZ+SMTZcuts+")*"+mt+"^2");
			ler1 = le->GetBinContent(1);
			tree->Draw("1>>le","("+LEleZ+SMTZcuts+")*"+mte+"");
			ler2 = le->GetBinContent(1);
			ler = sqrt(ler1+ler2*ler2);
			//printf("$ee\\tau_{\\mu}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
			//cout << "EEMT fakeable: " << tree->GetEntries(LEleZ+SMTZcuts) << endl;
			cout << "EEMT: " << lv << "(" << tree->GetEntries(LEleZ+SMTZcuts) << ")" <<  endl;
			bgMap["EEMT"]=lv; bgnMap["EEMT"]=tree->GetEntries(LEleZ+SMTZcuts);
			//cout << "Background for EEMT = " << lv << " +- " << ler << endl;
			//cout << "EEMT cuts: " << LEleZ << SMTZcuts << endl;
			//cout << "EEMT: " << lv/0.245 << endl;


			////////////////////////////// Integral Method for Leptons /////////////////////////////////////////////
			tree=(TTree*)e->Get("eleEleEleMuEventTree_antiIso/eventTree");
			double EEEM = tree->GetEntries(LEleZ+SEMZcuts);
			double eeem = IFREle*IFRMu*EEEM/(1-IFREle*IFRMu);
			double eeemErr = sqrt(EEEM*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*EEEM*EEEM);
			//printf("$ee\\tau_{e}\\tau_{\\mu}$ & $--$ & $ %0.2f \\pm %0.2f(stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",eeem,eeemErr);
			//cout << "Background for EEEM = " << eeem << " +- " << eeemErr << end;
			//cout << "EEEM cuts: " << LEleZ << SEMZcuts << endl;
			//cout << "EEEM: " << eeem/0.0841 << endl;
			cout << "EEEM: " << eeem << "(" << EEEM << ")" << endl;
			bgMap["EEEM"]=lv; bgnMap["EEEM"]=tree->GetEntries(LEleZ+SEMZcuts);
			//cout << "EEEM fakeable: " << EEEM << endl;
			tree=(TTree*)m->Get("muMuEleMuEventTree_antiIso/eventTree");
			double MMEM = tree->GetEntries(LMuZ+SEMZcuts);
			double mmem = IFREle*IFRMu*MMEM/(1-IFREle*IFRMu);
			double mmemErr = sqrt(MMEM*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*MMEM*MMEM);
			//printf("$\\mu\\mu\\tau_{e}\\tau_{\\mu}$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",mmem,mmemErr);
			//cout << "Background for MMEM = " << mmem << " +- " << mmemErr << endl;
			//cout << "MMEM cuts: " << LMuZ << SEMZcuts << endl;
			//cout << "MMEM: " << mmem/0.1367 << endl;
			cout << "MMEM: " << mmem << "(" << MMEM << ")" << endl;
			bgMap["MMEM"]=lv; bgnMap["MMEM"]=tree->GetEntries(LMuZ+SEMZcuts);
			//cout << "MMEM fakeable: " << MMEM << endl;
			std::cout << "---------- AA ----------" << std::endl;
			tree=(TTree*)e->Get("eleEleEleEleEventTree_antiIso/eventTree");
			double EEEE = tree->GetEntries(LEleZ+SEEZcuts);
			double eeee = IFREle*EEEE/(1-IFREle)*IFREle/(1-IFREle);
			double eeeeErr = sqrt(EEEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*EEEE*EEEE*IFREle*IFREle);
			std::cout << "EEEE: " << eeee << "(" << EEEE << ")" << std::endl;
			bgMap["EEEE"]=eeee; bgnMap["EEEE"]=EEEE;
			//cout << "EEEE cuts: " << LEleZ+SEEZcuts << endl;
			//cout << "Background Est. for EEEE = " << eeee << " +- " << eeeeErr << endl;
			//cout << "EEEE fakeable: " << EEEE << endl;
			tree=(TTree*)m->Get("muMuEleEleEventTree_antiIso/eventTree");
			double MMEE = tree->GetEntries(LMuZ+SEEZcuts);
			double mmee = IFREle*MMEE/(1-IFREle)*IFREle/(1-IFREle);
			double mmeeErr = sqrt(MMEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*MMEE*MMEE*IFREle*IFREle);
			std::cout << "MMEE: " << mmee << "(" << MMEE << ")" << std::endl;
			bgMap["MMEE"]=mmee; bgnMap["MMEE"]=MMEE;
			//	cout << "MMEE cuts: " << LMuZ+SEEZcuts << endl;
			//cout << "MMEE cuts: " << LMuZ+SEEZcuts << endl;
			//cout << "Background Est. for MMEE = " << mmee << " +- " << mmeeErr << endl;
			//cout << "Events In Control Region " << MMEE << endl;
			tree=(TTree*)e->Get("eleEleMuMuEventTree_antiIso/eventTree");
			double EEMM = tree->GetEntries(LEleZ+SMMZcuts);
			double eemm = IFRMu*EEMM/(1-IFRMu)*IFRMu/(1-IFRMu);
			double eemmErr = sqrt(EEMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*EEMM*EEMM);
			std::cout << "EEMM: " << eemm << "(" << EEMM << ")" << std::endl;
			bgMap["EEMM"]=eemm; bgnMap["EEMM"]=EEMM;
			//cout << "Background Est. for EEMM = " << eemm << " +- " << eemmErr << endl;
			//cout << "Events In Control Region " << EEMM << endl;
			tree=(TTree*)m->Get("muMuMuMuEventTree_antiIso/eventTree");
			double MMMM = tree->GetEntries(LMuZ+SMMZcuts);
			double mmmm = IFRMu*MMMM/(1-IFRMu)*IFRMu/(1-IFRMu);
			double mmmmErr = sqrt(MMMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*MMMM*MMMM);
			std::cout << "MMMM: " << mmmm << "(" << MMMM << ")" << std::endl;
			bgMap["MMMM"]=mmmm; bgnMap["MMMM"]=MMMM;
			//cout << "MMMM cuts: " << LMuZ+SMMZcuts << endl;
			//cout << "Background Est. for MMMM = " << mmmm << " +- " << mmmmErr << endl;
			//cout << "Events In Control Region " << MMMM << endl;
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
//			fakeRates();
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
