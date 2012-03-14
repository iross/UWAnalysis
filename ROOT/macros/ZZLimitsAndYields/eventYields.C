#include "helpers.h"

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

			makeHists(selection,selectionNoIso,lumi,"HZZ2l2t");

			for (unsigned int i=0; i<hMass_.size();++i){
				makeCard(hMass_[i],selectionBase,lumi,"HZZ2l2t",hMassn_[i]);
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
					if (labels_[j]=="Zjets") hh->Scale(dataDrivenBG_[j]/hh->Integral());
					if (labels_[j]=="ZZ") {
						hh->Scale(dataDrivenBG_[j]/hh->Integral());
					}
				}

				if (types_[j]==10){
					if (labels_[j]=="Zjets" || labels_[j]=="Zjets_CMS_scale_tUp" || labels_[j]=="Zjets_CMS_scale_tDown"){
						std::cout << labels_[j] << " scaled to " << dataDrivenBG_[j]*hh->Integral()/zjNom << std::endl;
						std::cout << "Before scaling: " << hh->Integral() << std::endl;
						hh->Scale(dataDrivenBG_[j]/zjNom);
						std::cout << "After scaling: " << hh->Integral() << std::endl;
					} else if (labels_[j]=="ZZ" || labels_[j]=="ZZ_CMS_scale_tUp" || labels_[j]=="ZZ_CMS_scale_tDown"){
						std::cout << labels_[j] << " scaled to " << dataDrivenBG_[j]*hh->Integral()/zjNom << std::endl;
						std::cout << "Before scaling: " << hh->Integral() << std::endl;
						hh->Scale(dataDrivenBG_[j]/zzNom);
						std::cout << "After scaling: " << hh->Integral() << std::endl;
					}
				}

				//scale down mmet and eeet for MMEE/EEEE cross-contamination
				if (process=="mmet" || process=="eeet"){
					if (labels_[j]!="Zjets" && labels_[j]!="Zjets_CMS_scale_tUp" && labels_[j]!="Zjets_CMS_scale_tDown" && labels_[j]!="DATA"){
						// hh->Scale(0.8);
						std::cout << "ZZ or Higgs -- scaling down by 20% for cross-contamination!" << std::endl;
					}
				}

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
					zjets=dataDrivenBG_[j];
				} else if (labels_[j]=="ZZ"){
					zz=dataDrivenBG_[j];
					//hh->SetName(labels_[j]);
					//hh->SetTitle(labels_[j]);
					//trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selection+")");
					//zz=hh->Integral();
					std::cout << "********ZZ EXPECTED: " << zz << "********" << std::endl;
					// if (process=="eeet" || process=="mmet") zz*=0.8;

				} else if (labels_[j]==("ggH"+hMass)){
					hh->SetName(labels_[j]);
					hh->SetTitle(labels_[j]);
					trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selection+")");
					gg=hh->Integral();
					// if (process=="eeet" || process=="mmet") gg*=0.8;
				} else if (labels_[j]==("vbf"+hMass)){
					hh->SetName(labels_[j]);
					hh->SetTitle(labels_[j]);
					trees_[j]->Draw("mass>>"+labels_[j],lumi+"*__WEIGHT__*("+selection+")");
					vbf=hh->Integral();
					// if (process=="eeet" || process=="mmet") vbf*=0.8;
				}
				hh->Delete();
			}


			ofile.open(channel+"/"+process+"_"+hMass+".txt");
			ofile << "imax 1  number of channels\n";
			ofile << "jmax *  number of backgrounds\n";
			ofile << "kmax *  number of nuisance parameters (sources of systematical uncertainties)\n";
			ofile << "shapes * " << process << " " << channel << "_" << process << ".input.root" << " $PROCESS $PROCESS_$SYSTEMATIC \n"; 
			ofile << "------------\n";
			ofile << "bin\t" << process << "\n";
			ofile << "observation\t"<<itos(observed)<<"\n";
			ofile << "------------" << endl;

			// std::cout << "******" << labels_[i] << "****** : " << contrib_[i] << " in [" << winLow_[i] << ", " << winHigh_[i] << "]" << std::endl;
			ofile << "# now we list the expected events for signal and all backgrounds in that bin\n";
			ofile << "# the second 'process' line must have a positive number for backgrounds, and 0 for signal\n";
			ofile << "# then we list the independent sources of uncertainties, and give their effect (syst. error)\n";
			ofile << "# on each process and bin\n";
			ofile << "------------" << endl;
			ofile << "bin \t";
			ofile << process << "\t" << process << "\t" << process << "\t" << process << "\t" << "\t";
			ofile << endl;
			ofile << "process \t ggH" << hMass << " \t vbf" << hMass << " \t Zjets \t ZZ";
			// for (unsigned int bk=0; bk<backgrounds_.at(i).size(); bk++) ofile << backgroundLabels_.at(i).at(bk) << "\t";
			ofile << endl;
			ofile << "process \t -1 \t 0 \t 1 \t 2";
			ofile << endl;
			ofile << "rate \t" << gg << "\t" << vbf << "\t" << zjets << "\t" << zz; //signal rate
			ofile << endl;
			ofile << "------------" << endl;

			//Lumi
			//signal 
			ofile << "lumi \t lnN \t 1.045 \t 1.045 \t - \t -";
			ofile << "\t #A 4.5% lumi uncertainty, affects signal and MC-driven background";
			ofile << endl;
			ofile << "theoryUncXS_HighMH \t lnN \t " << 1+1.50*pow(hMassn/1000,3) << "\t" << 1+1.50*pow(hMassn/1000,3) << "\t - \t -";
			ofile << endl;
			ofile << "BRhiggs_ZZ4l \t lnN \t 1.02 \t 1.02 \t - \t -";
			ofile << endl;
			//ggH cross-section uncertainty
			//signal
			ofile << "QCDscale_ggH \t lnN \t 1.1 \t - \t - \t -";
			ofile << endl;
			ofile << "QCDscale_qqH \t lnN \t - \t 1.01 \t - \t -";
			ofile << endl;
			ofile << "pdf_gg \t lnN \t  1.08 \t - \t - \t -";
			ofile << endl;
			ofile << "pdf_qqbar \t lnN \t - \t 1.05 \t - \t -";
			ofile << endl;
			//ofile << "pdf_gg \t lnN \t 1.05 \t - \t - \t -" << endl;
			//QCD scale for VV
			//signal
			ofile << "QCDscale_ggVV \t lnN \t - \t -";
			for (unsigned int bk=0; bk<2; bk++) {
				if (labels_[bk]=="ZZ") ofile << "\t1.3";
				else ofile << "\t-";
			}
			ofile << endl;
			//ofile << "pdf_qqbar \t lnN \t - \t 1.05 \t - \t -" << endl;

			//backgrounds
			// ofile << "CMS_hzz2l2tau_ZjetBkg \t lnN \t - \t - \t 1.3 \t -" << endl;
			double temp=0;
			if (process=="MMTT") {
				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 798 \t - \t - \t 0.000082707 \t -" << endl;
			} else if (process=="EETT"){
				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 629 \t - \t - \t 0.000133545 \t -" << endl;
			} else if (process=="EEET"){
				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 10 \t - \t - \t 0.024 \t -" << endl;
			} else if (process=="MMET"){
				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 5 \t - \t - \t 0.024 \t -" << endl;
			} else if (process=="MMMT"){
				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 2 \t - \t - \t 0.025 \t -" << endl;
			} else if (process=="EEMT"){
				ofile << "CMS_hzz2l2tau_ZjetBkg"+process+" \t gmN 3 \t - \t - \t 0.02333 \t -" << endl;
			}

			ofile << "CMS_hzz2l2tau_ZjetBkg_extrap \t lnN \t - \t - \t 1.3 \t -" << endl;		
			ofile << "CMS_hzz2l2tau_ZZBkg_extrap \t lnN \t - \t - \t - \t 1.1" << endl;

			int numMuons=process.CountChar('M');
			int numEles=process.CountChar('E');

			//triggers
			if (numMuons>=2) ofile << "CMS_trigger_m \t lnN \t 1.01 \t 1.01 \t 1.01 \t 1.01" << endl;
			else if (numEles>=2) ofile << "CMS_trigger_e \t lnN \t 1.01 \t 1.01 \t 1.01 \t 1.01" << endl;

			//-------final state dependent-------
			//Muon eff systematic
			//signal
			ofile << "CMS_eff_m \t lnN \t";
			// if (numMuons>0)
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1+sqrt(numMuons*pow(0.02,2)));
			// else
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			if (process=="MMTT") ofile << "1.01 \t 1.01 \t 1.01 \t 1.01" << endl;
			else if (process=="MMMT") ofile << "1.02 \t 1.02 \t 1.02 \t 1.02" << endl;
			else if (process=="MMET") ofile << "1.01 \t 1.01 \t 1.01 \t 1.01" << endl;
			else if (process=="MMEM") ofile << "1.02 \t 1.02 \t 1.02 \t 1.02" << endl;
			else if (process=="EEMT") ofile << "1.01 \t 1.01 \t 1.01 \t 1.01" << endl;
			else if (process=="EEEM") ofile << "1.02 \t 1.02 \t 1.02 \t 1.02" << endl;
			else if (process=="EEMM") ofile << "1.03 \t 1.03 \t 1.03 \t 1.03" << endl;
			else if (process=="MMMM") ofile << "1.04 \t 1.04 \t 1.04 \t 1.04" << endl;
			else if (process=="MMEE") ofile << "1.01 \t 1.01 \t 1.01 \t 1.01" << endl;
			else ofile << "- \t - \t - \t -" << endl;

			//Electron eff systematic
			//signal
			ofile << "CMS_eff_e \t lnN \t";
			// if (numEles>0)
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1+sqrt(numEles*pow(0.03,2)));
			// else
			// 	for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			// ofile << endl;
			if (process=="MMET") ofile << "1.06 \t 1.06 \t 1.06 \t 1.06" << endl;
			else if (process=="MMEM") ofile << "1.03 \t 1.03 \t 1.03 \t 1.03" << endl;
			else if (process=="EETT") ofile << "1.02 \t 1.02 \t 1.02 \t 1.02" << endl;
			else if (process=="EEMT") ofile << "1.02 \t 1.02 \t 1.02 \t 1.02" << endl;
			else if (process=="EEET") ofile << "1.06 \t 1.06 \t 1.06 \t 1.06" << endl;
			else if (process=="EEEM") ofile << "1.04 \t 1.04 \t 1.04 \t 1.04" << endl;
			else if (process=="EEMM") ofile << "1.02 \t 1.02 \t 1.02 \t 1.02" << endl;
			else if (process=="MMEE") ofile << "1.05 \t 1.05 \t 1.05 \t 1.05" << endl;
			else if (process=="EEEE") ofile << "1.06 \t 1.06 \t 1.06 \t 1.06" << endl;
			else ofile << "- \t - \t - \t -" << endl;


			//Tau ID systematic
			//signal
			ofile << "CMS_eff_t \t lnN";
			int numTaus=process.CountChar('T');
			if (numTaus==1) //et or mt -- loose has 6% uncertainty
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1+sqrt(pow(0.06,2)*numTaus));
			else if (numTaus==2) //tt -- med has 6.8% uncertainty
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1+sqrt(pow(0.068,2)*numTaus));
			else
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			ofile << endl;

			//Muon scale systematic
			ofile << "CMS_scale_m \t lnN";
			numMuons=process.CountChar('M');
			if (numMuons>0)
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1.01);
			else
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			ofile << "\t # systematic from muon momentum scale" << endl;
			//Electron scale systematic
			ofile << "CMS_scale_e \t lnN";
			numEles=process.CountChar('E');
			if (numEles>0)
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1.02);
			else
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			ofile << "\t # systematic from electron energy scale" << endl;
			//Tau ES systematic
			ofile << "CMS_scale_t \t shape";
			//ofile << "CMS_scale_t \t lnN";
			numTaus=process.CountChar('T');
			if (numTaus>0) {
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t" << dtos(1);
				//ofile << "\t 1.03 \t 1.03 \t - \t -";
			} else
				for (unsigned int bk=0; bk<4; bk++) ofile << "\t-";
			ofile << "\t # systematic from tau energy scale" << endl;

			ofile << endl;
			ofile.close();
		}
		void fakeRate(){
			TFile *e = new TFile("sandbox/zzeedata-Aug5/DATA.root");
			TFile *m = new TFile("sandbox/zzmm-latest/DATA.root");
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
			TString SEEZtd  = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge!=0&&z2l1CiCTight&1==1&&z2l2CiCTight&1==1&&z2l1MissHits<2&&z2l2MissHits<3&&(z2l1Pt+z2l2Pt)>20&&met<20";
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
			//gROOT->ProcessLine(".!mkdir FitPlots");
//
//			////////////////////////////////Measure Fake Rate for Leptons////////////////////////////////////////////
//
//			e->cd();
//			eleEleEleMuEventTreeID->cd();
//			TGraphAsymmErrors *ee = new TGraphAsymmErrors();
//			TGraphAsymmErrors *mm = new TGraphAsymmErrors();
//			double DE,NE,DM,NM,NET,NMT,DET,DMT;
//			TCanvas *C = new TCanvas();
//			TH1F *nm = new TH1F("nm", "nm", 10, 0,100);
//			TH1F *dm = new TH1F("dm", "dm", 10, 0,100);
//			TH1F *ne = new TH1F("ne", "ne", 10, 0,100);
//			TH1F *de = new TH1F("de", "de", 10, 0,100);
//			eventTree->Draw("z2l1Pt>>ne",LEleZ+SEMZEn);
//			eventTree->Draw("z2l2Pt>>nm",LEleZ+SEMZMn);
//			eventTree->Draw("z2l1Pt>>de",LEleZ+SEMZtd);
//			eventTree->Draw("z2l2Pt>>dm",LEleZ+SEMZtd);
//			NE = eventTree->GetEntries(LEleZ+SEMZEn);
//			DE = eventTree->GetEntries(LEleZ+SEMZtd);
//			NM = eventTree->GetEntries(LEleZ+SEMZMn);
//			DM = eventTree->GetEntries(LEleZ+SEMZtd);
//			m->cd();
//			muMuEleMuEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LMuZ+SEMZEn);
//			eventTree->Draw("z2l2Pt>>nm1(10,0,100)",LMuZ+SEMZMn);
//			eventTree->Draw("z2l1Pt>>de1(10,0,100)",LMuZ+SEMZtd);
//			eventTree->Draw("z2l2Pt>>dm1(10,0,100)",LMuZ+SEMZtd);
//			ne->Add(ne,ne1);
//			nm->Add(nm,nm1);
//			de->Add(de,de1);
//			dm->Add(dm,dm1);
//			NE += eventTree->GetEntries(LMuZ+SEMZEn);
//			DE += eventTree->GetEntries(LMuZ+SEMZtd);
//			NM += eventTree->GetEntries(LMuZ+SEMZMn);
//			DM += eventTree->GetEntries(LMuZ+SEMZtd);
//			m->cd();
//			muMuMuMuEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>nm1(10,0,100)",LMuZ+SMMZ1n);
//			eventTree->Draw("z2l2Pt>>nm2(10,0,100)",LMuZ+SMMZ2n);
//			eventTree->Draw("z2l1Pt>>dm1(10,0,100)",LMuZ+SMMZtd);
//			eventTree->Draw("z2l2Pt>>dm2(10,0,100)",LMuZ+SMMZtd);
//			nm->Add(nm,nm1);
//			nm->Add(nm,nm2);
//			dm->Add(dm,dm1);
//			dm->Add(dm,dm2);
//			NM += eventTree->GetEntries(LMuZ+SMMZ1n);
//			NM += eventTree->GetEntries(LMuZ+SMMZ2n);
//			DM += 2*eventTree->GetEntries(LMuZ+SMMZtd);
//			e->cd();
//			eleEleMuMuEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>nm1(10,0,100)",LEleZ+SMMZ1n);
//			eventTree->Draw("z2l2Pt>>nm2(10,0,100)",LEleZ+SMMZ2n);
//			eventTree->Draw("z2l1Pt>>dm1(10,0,100)",LEleZ+SMMZtd);
//			eventTree->Draw("z2l2Pt>>dm2(10,0,100)",LEleZ+SMMZtd);
//			nm->Add(nm,nm1);
//			nm->Add(nm,nm2);
//			dm->Add(dm,dm1);
//			dm->Add(dm,dm2);
//			NM += eventTree->GetEntries(LEleZ+SMMZ1n);
//			NM += eventTree->GetEntries(LEleZ+SMMZ2n);
//			DM += 2*eventTree->GetEntries(LEleZ+SMMZtd);
//			m->cd();
//			muMuEleEleEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LMuZ+SEEZ1n);
//			eventTree->Draw("z2l2Pt>>ne2(10,0,100)",LMuZ+SEEZ2n);
//			eventTree->Draw("z2l1Pt>>de1(10,0,100)",LMuZ+SEEZtd);
//			eventTree->Draw("z2l2Pt>>de2(10,0,100)",LMuZ+SEEZtd);
//			ne->Add(ne,ne1);
//			ne->Add(ne,ne2);
//			de->Add(de,de1);
//			de->Add(de,de2);
//			NE += eventTree->GetEntries(LMuZ+SEEZ1n);
//			NE += eventTree->GetEntries(LMuZ+SEEZ2n);
//			DE += 2*eventTree->GetEntries(LMuZ+SEEZtd);
//			e->cd();
//			eleEleEleEleEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LEleZ+SEEZ1n);
//			eventTree->Draw("z2l2Pt>>ne2(10,0,100)",LEleZ+SEEZ2n);
//			eventTree->Draw("z2l1Pt>>de1(10,0,100)",LEleZ+SEEZtd);
//			eventTree->Draw("z2l2Pt>>de2(10,0,100)",LEleZ+SEEZtd);
//			ne->Add(ne,ne1);
//			ne->Add(ne,ne2);
//			de->Add(de,de1);
//			de->Add(de,de2);
//			NE += eventTree->GetEntries(LEleZ+SEEZ1n);
//			NE += eventTree->GetEntries(LEleZ+SEEZ2n);
//			DE += 2*eventTree->GetEntries(LEleZ+SEEZtd);
//			e->cd();
//			eleEleEleTauEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LEleZ+SETZn);
//			eventTree->Draw("z2l1Pt>>de1(10,0,100)",LEleZ+SETZd);
//			ne->Add(ne,ne1);
//			de->Add(de,de1);
//			NE += eventTree->GetEntries(LEleZ+SETZn);
//			NET = eventTree->GetEntries(LEleZ+SETZnT);
//			DET = eventTree->GetEntries(LEleZ+SETZd);
//			DE += eventTree->GetEntries(LEleZ+SETZd);
//			m->cd();
//			muMuEleTauEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LMuZ+SETZn);
//			eventTree->Draw("z2l1Pt>>de1(10,0,100)",LMuZ+SETZd);
//			ne->Add(ne,ne1);
//			de->Add(de,de1);
//			NE += eventTree->GetEntries(LMuZ+SETZn);
//			NET += eventTree->GetEntries(LMuZ+SETZnT);
//			DET += eventTree->GetEntries(LMuZ+SETZd);
//			DE += eventTree->GetEntries(LMuZ+SETZd);
//			m->cd();
//			muMuMuTauEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>nm1(10,0,100)",LMuZ+SMTZn);
//			eventTree->Draw("z2l1Pt>>dm1(10,0,100)",LMuZ+SMTZd);
//			nm->Add(nm,nm1);
//			dm->Add(dm,dm1);
//			NM += eventTree->GetEntries(LMuZ+SMTZn);
//			NMT = eventTree->GetEntries(LMuZ+SMTZnT);
//			DMT += eventTree->GetEntries(LMuZ+SMTZd);
//			DM += eventTree->GetEntries(LMuZ+SMTZd);
//			e->cd();
//			eleEleMuTauEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>nm1(10,0,100)",LEleZ+SMTZn);
//			eventTree->Draw("z2l1Pt>>dm1(10,0,100)",LEleZ+SMTZd);
//			nm->Add(nm,nm1);
//			dm->Add(dm,dm1);
//			NM += eventTree->GetEntries(LEleZ+SMTZn);
//			DMT += eventTree->GetEntries(LEleZ+SMTZd);
//			DM += eventTree->GetEntries(LEleZ+SMTZd);
//
//
//			////////////////////////////////////// Measure fake rate for Taus  ////////////////////////////////////////////////////
//			//Two channels combined for increased statistics: eett, mmtt
//
//			double DTau,NLoose,NMed;
//			e->cd();
//			eleEleTauTauEventTreeID->cd();
//			TGraphAsymmErrors *tt = new TGraphAsymmErrors();
//			TGraphAsymmErrors *lt = new TGraphAsymmErrors();
//			TH1F *n1 = new TH1F("n1", "n1", 10, 0,100);
//			TH1F *d1 = new TH1F("d1", "d1", 10, 0,100);
//			TH1F *n1VL = new TH1F("n1VL", "n1VL", 10, 0,100);
//			TH1F *d1VL = new TH1F("d1VL", "d1VL", 10, 0,100);
//			eventTree->Draw("z2l1Pt>>n1",LEleZ+STTZt1n);
//			eventTree->Draw("z2l2Pt>>n2(10,0,100)",LEleZ+STTZt2n);
//			eventTree->Draw("z2l1Pt>>n1VL",LEleZ+STTZt1nVL);
//			eventTree->Draw("z2l2Pt>>n2VL(10,0,100)",LEleZ+STTZt2nVL);
//			n1->Add(n1,n2);
//			n1VL->Add(n1VL,n2VL);
//			NLoose = eventTree->GetEntries(LEleZ+STTZt1nVL+"&&z2l1Pt>20&&z2l2Pt>20");
//			NLoose += eventTree->GetEntries(LEleZ+STTZt2nVL+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1LooseIso");
//			NMed = eventTree->GetEntries(LEleZ+STTZt1n+"&&z2l1Pt>20&&z2l2Pt>20");
//			NMed += eventTree->GetEntries(LEleZ+STTZt2n+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1MediumIso");
//			eventTree->Draw("z2l1Pt>>d1",LEleZ+STTZtd);
//			eventTree->Draw("z2l2Pt>>d2(10,0,100)",LEleZ+STTZtd);
//			eventTree->Draw("z2l1Pt>>d1VL",LEleZ+STTZtd);
//			eventTree->Draw("z2l2Pt>>d2VL(10,0,100)",LEleZ+STTZtd);
//			d1->Add(d1,d2);
//			d1VL->Add(d1VL,d2VL);
//			DTau = 2*eventTree->GetEntries(LEleZ+STTZtd+"&&z2l1Pt>20&&z2l2Pt>20");
//			m->cd();
//			muMuTauTauEventTreeID->cd();
//			eventTree->Draw("z2l1Pt>>n3(10,0,100)",LMuZ+STTZt1n);
//			eventTree->Draw("z2l1Pt>>n3VL(10,0,100)",LMuZ+STTZt1nVL);
//			n1->Add(n1,n3);
//			n1VL->Add(n1VL,n3VL);
//			eventTree->Draw("z2l2Pt>>n4(10,0,100)",LMuZ+STTZt2n);
//			eventTree->Draw("z2l2Pt>>n4VL(10,0,100)",LMuZ+STTZt2nVL);
//			n1->Add(n1,n4);
//			n1VL->Add(n1VL,n4VL);
//			eventTree->Draw("z2l1Pt>>d3(10,0,100)",LMuZ+STTZtd);
//			eventTree->Draw("z2l1Pt>>d3VL(10,0,100)",LMuZ+STTZtd);
//			d1->Add(d1,d3);
//			d1VL->Add(d1VL,d3VL);
//			eventTree->Draw("z2l2Pt>>d4(10,0,100)",LMuZ+STTZtd);
//			eventTree->Draw("z2l2Pt>>d4VL(10,0,100)",LMuZ+STTZtd);
//			d1->Add(d1,d4);
//			d1VL->Add(d1VL,d4VL);
//			NLoose += eventTree->GetEntries(LMuZ+STTZt1nVL+"&&z2l1Pt>20&&z2l2Pt>20");
//			NLoose += eventTree->GetEntries(LMuZ+STTZt2nVL+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1LooseIso");
//			NMed += eventTree->GetEntries(LMuZ+STTZt1n+"&&z2l1Pt>20&&z2l2Pt>20");
//			NMed += eventTree->GetEntries(LMuZ+STTZt2n+"&&z2l1Pt>20&&z2l2Pt>20&&!z2l1MediumIso");
//			DTau += 2*eventTree->GetEntries(LMuZ+STTZtd+"&&z2l1Pt>20&&z2l2Pt>20");
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
//			tt->BayesDivide(n1,d1);
//			tt->GetXaxis()->SetTitle("#tau p_{T} GeV");
//			tt->GetYaxis()->SetTitle("Fake Rate");
//			tt->Draw("AP");
//			TF1 *myfit1 = new TF1("myfit1","[0] + [1]*exp([2]*x)", 15, 60);
//			myfit1->SetParameter(0, 0);
//			myfit1->SetParameter(1, 0);
//			myfit1->SetParameter(2, 0);
//			tt->Fit("myfit1","WR");
//			//l1=new TLine(15,IFRM,100,IFRM);
//			//l1->SetLineColor(38);
//			//l1->Draw();
//			C->SaveAs("FitPlots/tautau.png");
//			C->SaveAs("FitPlots/tautau.C");
//			double c0 = myfit1->GetParameter(0);
//			double c1 = myfit1->GetParameter(1);
//			double c2 = myfit1->GetParameter(2);
//			double e0 = myfit1->GetParError(0);
//			double e1 = myfit1->GetParError(1);
//			double e2 = myfit1->GetParError(2);
//			lt->BayesDivide(n1VL,d1VL);
//			lt->GetXaxis()->SetTitle("#tau p_{T} GeV");
//			lt->GetYaxis()->SetTitle("Fake Rate");
//			lt->Draw("AP");
//			TF1 *myfit2 = new TF1("myfit2","[0] + [1]*exp([2]*x)", 15, 60);
//			myfit2->SetParameter(0, 0);
//			myfit2->SetParameter(1, 0);
//			myfit2->SetParameter(2, 0);
//			lt->Fit("myfit2","WR");
//			//l2=new TLine(15,IFRL,100,IFRL);
//			//l2->SetLineColor(38);
//			//l2->Draw();
//			C->SaveAs("FitPlots/tautauL.png");
//			C->SaveAs("FitPlots/tautauL.C");
//			double c0VL = myfit2->GetParameter(0);
//			double c1VL = myfit2->GetParameter(1);
//			double c2VL = myfit2->GetParameter(2);
//			double e0VL = myfit2->GetParError(0);
//			double e1VL = myfit2->GetParError(1);
//			double e2VL = myfit2->GetParError(2);
//			std::ostringstream S0;
//			std::ostringstream S1;
//			std::ostringstream S2;
//			std::ostringstream E0;
//			std::ostringstream E1;
//			std::ostringstream E2;
//			std::ostringstream S0VL;
//			std::ostringstream S1VL;
//			std::ostringstream S2VL;
//			std::ostringstream E0VL;
//			std::ostringstream E1VL;
//			std::ostringstream E2VL;
//			S0 << c0;
//			S1 << c1;
//			S2 << c2;
//			E0 << e0;
//			E1 << e1;
//			E2 << e2;
//			S0VL << c0VL;
//			S1VL << c1VL;
//			S2VL << c2VL;
//			E0VL << e0VL;
//			E1VL << e1VL;
//			E2VL << e2VL;
//			TString s0 = S0.str();
//			TString s1 = S1.str();
//			TString s2 = S2.str();
//			TString se0 = E0.str();
//			TString se1 = E1.str();
//			TString se2 = E2.str();
//			TString s0VL = S0VL.str();
//			TString s1VL = S1VL.str();
//			TString s2VL = S2VL.str();
//			TString se0VL = E0VL.str();
//			TString se1VL = E1VL.str();
//			TString se2VL = E2VL.str();
//			TString tt1 = "("+s0+"*z2l1Pt/z2l1Pt+"+s1+"*exp(z2l1Pt*"+s2+"))";
//			TString tt2 = "("+s0+"*z2l2Pt/z2l2Pt+"+s1+"*exp(z2l2Pt*"+s2+"))";
//			TString tte1 = "("+se0+"^2*z2l1Pt/z2l1Pt+("+se1+"^2+"+s1+"^2*z2l1Pt^2*"+se2+"^2)*exp(2*z2l1Pt*"+s2+"))";
//			TString tte2 = "("+se0+"^2*z2l2Pt/z2l2Pt+("+se1+"^2+"+s1+"^2*z2l2Pt^2*"+se2+"^2)*exp(2*z2l2Pt*"+s2+"))";
//			TString et = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
//			TString mt = "("+s0VL+"*z2l2Pt/z2l2Pt+"+s1VL+"*exp(z2l2Pt*"+s2VL+"))";
//			TString ete = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";
//			TString mte = "("+se0VL+"^2*z2l2Pt/z2l2Pt+("+se1VL+"^2+"+s1VL+"^2*z2l2Pt^2*"+se2VL+"^2)*exp(2*z2l2Pt*"+s2VL+"))";
//
//			/////////////////Apply fit to individual channels////////////////////////////////////
//
//			m->cd();
//			muMuTauTauEventTreeID->cd();
//			eventTree->Draw("1>>ll(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
//			double llv = ll->GetBinContent(1);
//			eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
//			double llev1 = lle->GetBinContent(1);
//			eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tte1+"*"+tt2+"");
//			double llev2 = lle->GetBinContent(1);
//			eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"*"+tte2+"");
//			double llev3 = lle->GetBinContent(1);
//			double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
//			cout << "Background for mmtt = " << llv << " +- " << llev << endl;
//			e->cd();
//			eleEleTauTauEventTreeID->cd();
//			eventTree->Draw("1>>ll(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
//			double llv = ll->GetBinContent(1);
//			eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
//			double llev1 = lle->GetBinContent(1);
//			eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tte1+"*"+tt2+"");
//			double llev2 = lle->GetBinContent(1);
//			eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"*"+tte2+"");
//			double llev3 = lle->GetBinContent(1);
//			double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
//			cout << "Background for eett = " << llv << " +- " << llev << endl;
//			e->cd();
//			eleEleEleTauEventTreeID->cd();
//			eventTree->Draw("1>>l(1,1,2)","("+LEleZ+SETZcuts+")*"+et+"/(1-"+et+")");
//			double lv = l->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SETZcuts+")*"+et+"^2");
//			double ler1 = le->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SETZcuts+")*"+ete+"");
//			double ler2 = le->GetBinContent(1);
//			double ler = sqrt(ler1+ler2*ler2);
//			cout << "Background for eeet = " << lv << " +- " << ler << endl;
//			m->cd();
//			muMuEleTauEventTreeID->cd();
//			eventTree->Draw("1>>l(1,1,2)","("+LMuZ+SETZcuts+")*"+et+"/(1-"+et+")");
//			double lv = l->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SETZcuts+")*"+et+"^2");
//			double ler1 = le->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SETZcuts+")*"+ete+"");
//			double ler2 = le->GetBinContent(1);
//			double ler = sqrt(ler1+ler2*ler2);
//			cout << "Background for mmet = " << lv << " +- " << ler << endl;
//			m->cd();
//			muMuMuTauEventTreeID->cd();
//			eventTree->Draw("1>>l(1,1,2)","("+LMuZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
//			double lv = l->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SMTZcuts+")*"+mt+"^2");
//			double ler1 = le->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SMTZcuts+")*"+mte+"");
//			double ler2 = le->GetBinContent(1);
//			double ler = sqrt(ler1+ler2*ler2);
//			cout << "Background for mmmt = " << lv << " +- " << ler << endl;
//			e->cd();
//			eleEleMuTauEventTreeID->cd();
//			eventTree->Draw("1>>l(1,1,2)","("+LEleZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
//			double lv = l->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SMTZcuts+")*"+mt+"^2");
//			double ler1 = le->GetBinContent(1);
//			eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SMTZcuts+")*"+mte+"");
//			double ler2 = le->GetBinContent(1);
//			double ler = sqrt(ler1+ler2*ler2);
//			cout << "Background for eemt = " << lv << " +- " << ler << endl;
//
//
//			////////////////////////////// Integral Method for Leptons /////////////////////////////////////////////
//			double IFREle,IFREleErr,IFRMu,IFRMuErr;
//			IFREle = NE/DE;
//			IFREleErr = sqrt(NE/(DE*DE)+NE*NE/(DE*DE*DE));
//			IFRMu = NM/DM;
//			IFRMuErr = sqrt(NM/(DM*DM)+NM*NM/(DM*DM*DM));
//			cout << "Integral ele fakerate = " << IFREle << " +- " << IFREleErr << endl;
//			cout << "Integral mu fakerate = " << IFRMu << " +- " << IFRMuErr << endl;
//			e->cd();
//			eleEleEleEleEventTreeID->cd();
//			double EEEE = eventTree->GetEntries(LEleZ+SEEZcuts);
//			double eeee = IFREle*IFREle*EEEE/(1-IFREle*IFREle);
//			double eeeeErr = sqrt(EEEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*EEEE*EEEE*IFREle*IFREle);
//			cout << "Background Est. for EEEE = " << eeee << " +- " << eeeeErr << endl;
//			//cout << "Events In Control Region " << EEEE << endl;
//			e->cd();
//			eleEleEleMuEventTreeID->cd();
//			double eeem = eventTree->GetEntries(LEleZ+SEMZcuts);
//			double eeem = IFREle*IFRMu*eeem/(1-IFREle*IFRMu);
//			double eeemErr = sqrt(eeem*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*eeem*eeem);
//			cout << "Background Est. for eeem = " << eeem << " +- " << eeemErr << endl;
//			//cout << "Events In Control Region " << eeem << endl;
//			m->cd();
//			muMuEleMuEventTreeID->cd();
//			double mmem = eventTree->GetEntries(LMuZ+SEMZcuts);
//			double mmem = IFREle*IFRMu*mmem/(1-IFREle*IFRMu);
//			double mmemErr = sqrt(mmem*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*mmem*mmem);
//			cout << "Background Est. for mmem = " << mmem << " +- " << mmemErr << endl;
//			//cout << "Events In Control Region " << mmem << endl;
//			m->cd();
//			muMuEleEleEventTreeID->cd();
//			double MMEE = eventTree->GetEntries(LMuZ+SEEZcuts);
//			double mmee = IFREle*IFREle*MMEE/(1-IFREle*IFREle);
//			double mmeeErr = sqrt(MMEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*MMEE*MMEE*IFREle*IFREle);
//			cout << "Background Est. for MMEE = " << mmee << " +- " << mmeeErr << endl;
//			//cout << "Events In Control Region " << MMEE << endl;
//			e->cd();
//			eleEleMuMuEventTreeID->cd();
//			double EEMM = eventTree->GetEntries(LEleZ+SMMZcuts);
//			double eemm = IFRMu*IFRMu*EEMM/(1-IFRMu*IFRMu);
//			double eemmErr = sqrt(EEMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*EEMM*EEMM);
//			cout << "Background Est. for EEMM = " << eemm << " +- " << eemmErr << endl;
//			//cout << "Events In Control Region " << EEMM << endl;
//			m->cd();
//			muMuMuMuEventTreeID->cd();
//			double MMMM = eventTree->GetEntries(LMuZ+SMMZcuts);
//			double mmmm = IFRMu*IFRMu*MMMM/(1-IFRMu*IFRMu);
//			double mmmmErr = sqrt(MMMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*MMMM*MMMM);
//			cout << "Background Est. for MMMM = " << mmmm << " +- " << mmmmErr << endl;
//			//cout << "Events In Control Region " << MMMM << endl;
//
//			mm->BayesDivide(nm,dm);
//			mm->Draw("AP");
//			C->SaveAs("FitPlots/mu.png");
//			ee->BayesDivide(ne,de);
//			ee->Draw("AP");
//			C->SaveAs("FitPlots/ele.png");
//
//
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
		TString process;
		ofstream ofile;
		ofstream ofile2;
		ofstream ofileDD;

};
