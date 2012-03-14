{
	//	gROOT->ProcessLine(".L UWAnalysis/ROOT/interactive/tdrstyle.C");
	//	setTDRStyle();
	//	setStyle();
	gROOT->ProcessLine(".L loader.C+");
	#include <map>
	#include <utility>
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
	for (int i=0; i<lines.size(); ++i){
		if (i%2!=0){
			//			std::cout << lines.at(i-1) << ":" << lines.at(i) << std::endl;
			frMap[lines.at(i-1)]=lines.at(i);	
		}
	}
	std::cout << "---- Using parameters: ----" << std::endl;
	for (map<string, string>::iterator iter = frMap.begin(); iter != frMap.end(); ++iter){
		std::cout << iter->first << ": " << iter->second << endl;
	}


//	TFile *e = new TFile("sandbox/zz-latest/DATA.root");
//	TFile *m = new TFile("sandbox/zz-latest/DATA.root");
	TFile *e = new TFile("DATA_BG.root");
	TFile *m = new TFile("DATA_BG.root");
	TString LEleZ = "dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&(z1l1CiCTight&1)==1&&(z1l2CiCTight&1)==1&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10";
	TString LMuZ = "dZ12<0.10&&dZ13<0.10&&dZ14<0.10&&HLT_Any&&z1Mass>60&&z1Mass<120&&z1l1RelPFIsoDB<0.25&&z1l2RelPFIsoDB<0.25&&z1l1Pt>20&&z1l2Pt>10";

	TString SEEZcuts_ai = "&&z2l1Pt>10&&z2l2Pt>10&&z2Charge==0&&z2l1RelPFIsoDB>0.25&&z2l2RelPFIsoDB<0.25&&(z2l1CiCTight&1)==1&&z2l2CiCTight&1==1&&z2Mass>60&&z2Mass<120";
	TString SMMZcuts_ai = "&&z2l1Pt>10&&z2l2Pt>10&&z2Charge==0&&z2l2RelPFIsoDB<0.25&&z2l1RelPFIsoDB>0.25&&z2Mass>60&&z2Mass<120";
	TString SEMZcuts_ai = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1MissHits<2&&z2Charge==0&&z2l1CiCTight&1==1&&z2l1RelPFIsoDB>0.25&&z2l2RelPFIsoDB<0.25&&z2Mass<90";
	TString STTZcuts_ai = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&!z2l1MediumIsoCombDB&&z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	TString SMTZcuts_ai = "&&z2l2EleVeto&&z2l2LooseIsoCombDB&&z2l2MuVetoTight&&z2l1RelPFIsoDB>0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	TString SETZcuts_ai = "&&z2l2EleVeto&&z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB>0.10&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	TString SEEZcuts_ia = "&&z2l1Pt>10&&z2l2Pt>10&&z2Charge==0&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB>0.25&&(z2l1CiCTight&1)==1&&z2l2CiCTight&1==1&&z2Mass>60&&z2Mass<120";
	TString SMMZcuts_ia = "&&z2l1Pt>10&&z2l2Pt>10&&z2Charge==0&&z2l2RelPFIsoDB>0.25&&z2l1RelPFIsoDB<0.25&&z2Mass>60&&z2Mass<120";
	TString SEMZcuts_ia = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1MissHits<2&&z2Charge==0&&z2l1CiCTight&1==1&&z2l1RelPFIsoDB<0.25&&z2l2RelPFIsoDB>0.25&&z2Mass<90";
	TString STTZcuts_ia = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&z2l1MediumIsoCombDB&&!z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	TString SMTZcuts_ia = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2MuVetoTight&&z2l1RelPFIsoDB<0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	TString SETZcuts_ia = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB<0.10&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	
	TString SEEZcuts_aa = "&&z2l1Pt>10&&z2l2Pt>10&&z2Charge==0&&z2l1RelPFIsoDB>0.25&&z2l2RelPFIsoDB>0.25&&(z2l1CiCTight&1)==1&&z2l2CiCTight&1==1&&z2Mass>60&&z2Mass<120";
	TString SMMZcuts_aa = "&&z2l1Pt>10&&z2l2Pt>10&&z2Charge==0&&z2l2RelPFIsoDB>0.25&&z2l1RelPFIsoDB>0.25&&z2Mass>60&&z2Mass<120";
	TString SEMZcuts_aa = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1MissHits<2&&z2Charge==0&&z2l1CiCTight&1==1&&z2l1RelPFIsoDB>0.25&&z2l2RelPFIsoDB>0.25&&z2Mass<90";
	TString STTZcuts_aa = "&&z2l1Pt>20&&z2l2Pt>20&&z2l1EleVeto&&z2l2EleVeto&&!z2l1MediumIsoCombDB&&!z2l2MediumIsoCombDB&&z2l1MuVeto&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	TString SMTZcuts_aa = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2MuVetoTight&&z2l1RelPFIsoDB>0.15&&z2l2Pt>20&&z2l1Pt>10&&z2Charge==0&&z2Mass>30&&z2Mass<80";
	TString SETZcuts_aa = "&&z2l2EleVeto&&!z2l2LooseIsoCombDB&&z2l2Pt>20&&z2l1Pt>10&&z2l1RelPFIsoDB>0.10&&z2l1CiCTight&1==1&&z2l1MissHits==0&&z2l2MuVeto&&z2Charge==0&&z2Mass>30&&z2Mass<80";

	TString SEEZcuts = SEEZcuts_aa; TString SMMZcuts = SMMZcuts_aa; TString SEMZcuts = SEMZcuts_aa;
	TString STTZcuts = STTZcuts_aa; TString SMTZcuts = SMTZcuts_aa; TString SETZcuts = SETZcuts_aa;

	//////////////Fitting, pt dependant fake rates///////////////////
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
	m->cd();
	muMuTauTauEventTree_antiIso->cd();
	eventTree->Draw("1>>ll(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
	double llv = ll->GetBinContent(1);
	eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
	double llev1 = lle->GetBinContent(1);
	eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tte1+"*"+tt2+"");
	double llev2 = lle->GetBinContent(1);
	eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"*"+tte2+"");
	double llev3 = lle->GetBinContent(1);
	double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
	//printf("$\\mu\\mu\\tauh\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",llv,llev);
	cout << "MMTT: " << llv << "(" << eventTree->GetEntries(LMuZ+STTZcuts) << ")" << endl;
	//cout << "MMTT fakeable: " << eventTree->GetEntries(LMuZ+STTZcuts) << endl;
	//cout << "Background for MMTT = " << llv << " +- " << llev << endl;
	//cout << "MMTT cuts: " << LMuZ << STTZcuts << endl;
	//cout << "MMTT: " << llv/0.409 << endl;
	e->cd();
	eleEleTauTauEventTree_antiIso->cd();
	eventTree->Draw("1>>ll(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
	double llv = ll->GetBinContent(1);
	eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
	double llev1 = lle->GetBinContent(1);
	eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tte1+"*"+tt2+"");
	double llev2 = lle->GetBinContent(1);
	eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"*"+tte2+"");
	double llev3 = lle->GetBinContent(1);
	double llev = sqrt(llev1+llev2*llev2+llev3*llev3);/////
	cout << "EETT: " << llv << "(" << eventTree->GetEntries(LEleZ+STTZcuts) << ")" << endl;
	//printf("$ee\\tauh\\tauh$ & $--$ & $ %0.2f \\pm  %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",llv,llev);
	//cout << "EETT fakeable: " << eventTree->GetEntries(LEleZ+STTZcuts) << endl;
	//cout << "Background for EETT = " << llv << " +- " << llev << endl;
	//cout << "EETT cuts: " << LEleZ << STTZcuts << endl;
	//cout << "EETT: " << llv/0.360 << endl;
	e->cd();
	eleEleEleTauEventTree_antiIso->cd();
	// need to fix this stuff so that the fake rate for e is applied.
	eventTree->Draw("1>>l(1,1,2)","("+LEleZ+SETZcuts+")*"+eletFR+"*"+et+"/(1-"+eletFR+"*"+et+")");
	double lv = l->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SETZcuts+")*"+et+"^2");
	double ler1 = le->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SETZcuts+")*"+ete+"");
	double ler2 = le->GetBinContent(1);
	double ler = sqrt(ler1+ler2*ler2);
	//printf("$ee\\tau_{e}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
	cout << "EEET: " << lv << "(" << eventTree->GetEntries(LEleZ+SETZcuts) << ")" << endl;
	//cout << "EEET fakeable: " << eventTree->GetEntries(LEleZ+SETZcuts) << endl;
	//cout << "Background for EEET = " << lv << " +- " << ler << endl;
	//cout << "EEET cuts: " << LEleZ << SETZcuts << endl;
	//cout << "EEET: " << lv/0.476 << endl;
	m->cd();
	muMuEleTauEventTree_antiIso->cd();
	eventTree->Draw("1>>l(1,1,2)","("+LMuZ+SETZcuts+")*"+eletFR+"*"+et+"/(1-"+eletFR+"*"+et+")");
	double lv = l->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SETZcuts+")*"+et+"^2");
	double ler1 = le->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SETZcuts+")*"+ete+"");
	double ler2 = le->GetBinContent(1);
	double ler = sqrt(ler1+ler2*ler2);
	//printf("$\\mu\\mu\\tau_{e}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
	//cout << "MMET fakeable: " << eventTree->GetEntries(LMuZ+SETZcuts) << endl;
	cout << "MMET: " << lv << "(" << eventTree->GetEntries(LMuZ+SETZcuts) << ")" << endl;
	//cout << "Background for MMET = " << lv << " +- " << ler << endl;
	//cout << "MMET cuts: " << LMuZ << SETZcuts << endl;
	//cout << "MMET: " << lv/0.345 << endl;
	m->cd();
	muMuMuTauEventTree_antiIso->cd();
	eventTree->Draw("1>>l(1,1,2)","("+LMuZ+SMTZcuts+")*"+mutFR+"*"+mt+"/(1-"+mutFR+"*"+mt+")");
	double lv = l->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SMTZcuts+")*"+mt+"^2");
	double ler1 = le->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SMTZcuts+")*"+mte+"");
	double ler2 = le->GetBinContent(1);
	double ler = sqrt(ler1+ler2*ler2);
	//printf("$\\mu\\mu\\tau_{\\mu}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
	//cout << "MMMT fakeable: " << eventTree->GetEntries(LMuZ+SMTZcuts) << endl;
	cout << "MMMT: " << lv << "(" << eventTree->GetEntries(LMuZ+SMTZcuts) << ")" << endl;
	//cout << "Background for MMMT = " << lv << " +- " << ler << endl;
	//cout << "MMMT cuts: " << LMuZ << SMTZcuts << endl;
	//cout << "MMMT: " << lv/0.147 << endl;
	e->cd();
	eleEleMuTauEventTree_antiIso->cd();
	eventTree->Draw("1>>l(1,1,2)","("+LEleZ+SMTZcuts+")*"+mutFR+"*"+mt+"/(1-"+mutFR+"*"+mt+")");
	double lv = l->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SMTZcuts+")*"+mt+"^2");
	double ler1 = le->GetBinContent(1);
	eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SMTZcuts+")*"+mte+"");
	double ler2 = le->GetBinContent(1);
	double ler = sqrt(ler1+ler2*ler2);
	//printf("$ee\\tau_{\\mu}\\tauh$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",lv,ler);
	//cout << "EEMT fakeable: " << eventTree->GetEntries(LEleZ+SMTZcuts) << endl;
	cout << "EEMT: " << lv << "(" << eventTree->GetEntries(LEleZ+SMTZcuts) << ")" <<  endl;
	//cout << "Background for EEMT = " << lv << " +- " << ler << endl;
	//cout << "EEMT cuts: " << LEleZ << SMTZcuts << endl;
	//cout << "EEMT: " << lv/0.245 << endl;


	////////////////////////////// Integral Method for Leptons /////////////////////////////////////////////
	e->cd();
	eleEleEleEleEventTree_antiIso->cd();
	double EEEE = eventTree->GetEntries(LEleZ+SEEZcuts);
	double eeee = IFREle*EEEE/(1-IFREle);
	double eeeeErr = sqrt(EEEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*EEEE*EEEE*IFREle*IFREle);
	//cout << "EEEE cuts: " << LEleZ+SEEZcuts << endl;
	//cout << "Background Est. for EEEE = " << eeee << " +- " << eeeeErr << endl;
	//cout << "EEEE fakeable: " << EEEE << endl;
	e->cd();
	eleEleEleMuEventTree_antiIso->cd();
	double EEEM = eventTree->GetEntries(LEleZ+SEMZcuts);
	double eeem = IFREle*IFRMu*EEEM/(1-IFREle*IFRMu);
	double eeemErr = sqrt(EEEM*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*EEEM*EEEM);
	//printf("$ee\\tau_{e}\\tau_{\\mu}$ & $--$ & $ %0.2f \\pm %0.2f(stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",eeem,eeemErr);
	//cout << "Background for EEEM = " << eeem << " +- " << eeemErr << end;
	//cout << "EEEM cuts: " << LEleZ << SEMZcuts << endl;
	//cout << "EEEM: " << eeem/0.0841 << endl;
	cout << "EEEM: " << eeem << "(" << EEEM << ")" << endl;
	//cout << "EEEM fakeable: " << EEEM << endl;
	m->cd();
	muMuEleMuEventTree_antiIso->cd();
	double MMEM = eventTree->GetEntries(LMuZ+SEMZcuts);
	double mmem = IFREle*IFRMu*MMEM/(1-IFREle*IFRMu);
	double mmemErr = sqrt(MMEM*IFREle*IFREle*IFRMu*IFRMu+(IFREleErr*IFREleErr*IFRMu*IFRMu+IFRMuErr*IFRMuErr*IFREle*IFREle)*MMEM*MMEM);
	//printf("$\\mu\\mu\\tau_{e}\\tau_{\\mu}$ & $--$ & $ %0.2f \\pm %0.2f (stat.) \\pm XX (sys.)$ & $ -- $\\\\ \n",mmem,mmemErr);
	//cout << "Background for MMEM = " << mmem << " +- " << mmemErr << endl;
	//cout << "MMEM cuts: " << LMuZ << SEMZcuts << endl;
	//cout << "MMEM: " << mmem/0.1367 << endl;
	cout << "MMEM: " << mmem << "(" << MMEM << ")" << endl;
	//cout << "MMEM fakeable: " << MMEM << endl;
	m->cd();
	muMuEleEleEventTree_antiIso->cd();
	double MMEE = eventTree->GetEntries(LMuZ+SEEZcuts);
	double mmee = IFREle*MMEE/(1-IFREle);
	double mmeeErr = sqrt(MMEE*IFREle*IFREle*IFREle*IFREle+4*IFREleErr*IFREleErr*MMEE*MMEE*IFREle*IFREle);
	//	cout << "MMEE cuts: " << LMuZ+SEEZcuts << endl;
	//cout << "MMEE cuts: " << LMuZ+SEEZcuts << endl;
	//cout << "Background Est. for MMEE = " << mmee << " +- " << mmeeErr << endl;
	//cout << "Events In Control Region " << MMEE << endl;
	e->cd();
	eleEleMuMuEventTree_antiIso->cd();
	double EEMM = eventTree->GetEntries(LEleZ+SMMZcuts);
	double eemm = IFRMu*EEMM/(1-IFRMu);
	double eemmErr = sqrt(EEMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*EEMM*EEMM);
	//cout << "Background Est. for EEMM = " << eemm << " +- " << eemmErr << endl;
	//cout << "Events In Control Region " << EEMM << endl;
	m->cd();
	muMuMuMuEventTree_antiIso->cd();
	double MMMM = eventTree->GetEntries(LMuZ+SMMZcuts);
	double mmmm = IFRMu*MMMM/(1-IFRMu);
	double mmmmErr = sqrt(MMMM*IFRMu*IFRMu*IFRMu*IFRMu+4*IFRMuErr*IFRMuErr*IFRMu*IFRMu*MMMM*MMMM);
	//cout << "MMMM cuts: " << LMuZ+SMMZcuts << endl;
	//cout << "Background Est. for MMMM = " << mmmm << " +- " << mmmmErr << endl;
	//cout << "Events In Control Region " << MMMM << endl;
}
