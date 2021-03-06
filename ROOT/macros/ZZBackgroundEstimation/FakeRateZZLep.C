{

TFile *e = new TFile("sandbox/zz-latest/bkgd.root");
TFile *m = new TFile("sandbox/zz-latest/bkgd.root");
TString LEleZ = "z1Mass>70&&z1Mass<110&&z1l1CiCTight&9==9&&z1l2CiCTight&9==9&&z1l1MissHits<2&&z1l2MissHits<2&&z1l1RelPfIsoRho<0.2&&z1l2RelPfIsoRho<0.2&&z1l1Pt>20&&z1l2Pt>10";
TString LMuZ = "z1Mass>70&&z1Mass<110&&z1l1RelPfIsoRho<0.25&&z1l2RelPfIsoRho<0.25&&z1l1Pt>20&&z1l2Pt>10";
TString SEEZ2n = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge!=0&&z2l1CiCTight&9==9&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l2MissHits<2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20&&met<20";
TString SEEZ1n = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge!=0&&z2l1CiCTight&9==9&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20&&met<20";
TString SMMZ2n = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge!=0&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20&&met<20";
TString SMMZ1n = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge!=0&&z2l2RelPfIsoRho<0.25&&(z2l1Pt+z2l2Pt)>20&&met<20";
TString SEMZMn = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l2RelPfIsoRho<0.25&&z2Charge!=0&&met<20";
TString SEMZEn = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l1RelPfIsoRho<0.2&&z2Charge!=0&&met<20";
TString SEEZtd  = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge!=0&&z2l1CiCTight&9==9&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l2MissHits<2&&(z2l1Pt+z2l2Pt)>20&&met<20";
TString SMMZtd  = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge!=0&&(z2l1Pt+z2l2Pt)>20&&met<20";
TString SEMZtd  = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2Charge!=0&&met<20";
TString SEEZcuts = "&&z2l1Pt>7&&z2l2Pt>7&&z2Charge==0&&z2l1CiCTight&9==9&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2l2MissHits<2&&z2l1RelPfIsoRho>0.2&&z2l2RelPfIsoRho<0.2&&(z2l1Pt+z2l2Pt)>20";
TString SMMZcuts = "&&z2l1Pt>5&&z2l2Pt>5&&z2Charge==0&&z2l2RelPfIsoRho<0.25&&z2l1RelPfIsoRho>0.25&&(z2l1Pt+z2l2Pt)>20";
TString SEMZcuts = "&&z2l1Pt>10&&z2l2Pt>10&&z2l1CiCTight&9==9&&z2l1MissHits<2&&z2Charge==0&&z2l1RelPfIsoRho>0.2&&z2l2RelPfIsoRho<0.25";
gROOT->ProcessLine(".!mkdir FitPlots");

////////////////////////////////////// Measure fake rate and apply fit ////////////////////////////////////////////////////
//Two channels combined for increased statistics: EETT, MMTT

e->cd();
eleEleEleMuEventTreeID->cd();
TGraphAsymmErrors *ee = new TGraphAsymmErrors();
TGraphAsymmErrors *mm = new TGraphAsymmErrors();
double DE,NE,DM,NM;
TCanvas *C = new TCanvas();
TH1F *nm = new TH1F("nm", "nm", 10, 0,100);
TH1F *dm = new TH1F("dm", "dm", 10, 0,100);
TH1F *ne = new TH1F("ne", "ne", 10, 0,100);
TH1F *de = new TH1F("de", "de", 10, 0,100);
eventTree->Draw("z2l1Pt>>ne",LEleZ+SEMZEn);
eventTree->Draw("z2l2Pt>>nm",LEleZ+SEMZMn);
eventTree->Draw("z2l1Pt>>de",LEleZ+SEMZtd);
eventTree->Draw("z2l2Pt>>dm",LEleZ+SEMZtd);
NE = eventTree->GetEntries(LEleZ+SEMZEn);
DE = eventTree->GetEntries(LEleZ+SEMZtd);
NM = eventTree->GetEntries(LEleZ+SEMZMn);
DM = eventTree->GetEntries(LEleZ+SEMZtd);
m->cd();
muMuEleMuEventTreeID->cd();
eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LMuZ+SEMZEn);
eventTree->Draw("z2l2Pt>>nm1(10,0,100)",LMuZ+SEMZMn);
eventTree->Draw("z2l1Pt>>de1(10,0,100)",LMuZ+SEMZtd);
eventTree->Draw("z2l2Pt>>dm1(10,0,100)",LMuZ+SEMZtd);
ne->Add(ne,ne1);
nm->Add(nm,nm1);
de->Add(de,de1);
dm->Add(dm,dm1);
NE += eventTree->GetEntries(LMuZ+SEMZEn);
DE += eventTree->GetEntries(LMuZ+SEMZtd);
NM += eventTree->GetEntries(LMuZ+SEMZMn);
DM += eventTree->GetEntries(LMuZ+SEMZtd);
m->cd();
muMuMuMuEventTreeID->cd();
eventTree->Draw("z2l1Pt>>nm1(10,0,100)",LMuZ+SMMZ1n);
eventTree->Draw("z2l2Pt>>nm2(10,0,100)",LMuZ+SMMZ2n);
eventTree->Draw("z2l1Pt>>dm1(10,0,100)",LMuZ+SMMZtd);
eventTree->Draw("z2l2Pt>>dm2(10,0,100)",LMuZ+SMMZtd);
nm->Add(nm,nm1);
nm->Add(nm,nm2);
dm->Add(dm,dm1);
dm->Add(dm,dm2);
NM += eventTree->GetEntries(LMuZ+SMMZ1n);
NM += eventTree->GetEntries(LMuZ+SMMZ2n);
DM += 2*eventTree->GetEntries(LMuZ+SMMZtd);
e->cd();
eleEleMuMuEventTreeID->cd();
eventTree->Draw("z2l1Pt>>nm1(10,0,100)",LEleZ+SMMZ1n);
eventTree->Draw("z2l2Pt>>nm2(10,0,100)",LEleZ+SMMZ2n);
eventTree->Draw("z2l1Pt>>dm1(10,0,100)",LEleZ+SMMZtd);
eventTree->Draw("z2l2Pt>>dm2(10,0,100)",LEleZ+SMMZtd);
nm->Add(nm,nm1);
nm->Add(nm,nm2);
dm->Add(dm,dm1);
dm->Add(dm,dm2);
NM += eventTree->GetEntries(LEleZ+SMMZ1n);
NM += eventTree->GetEntries(LEleZ+SMMZ2n);
DM += 2*eventTree->GetEntries(LEleZ+SMMZtd);
m->cd();
muMuEleEleEventTreeID->cd();
eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LMuZ+SEEZ1n);
eventTree->Draw("z2l2Pt>>ne2(10,0,100)",LMuZ+SEEZ2n);
eventTree->Draw("z2l1Pt>>de1(10,0,100)",LMuZ+SEEZtd);
eventTree->Draw("z2l2Pt>>de2(10,0,100)",LMuZ+SEEZtd);
ne->Add(ne,ne1);
ne->Add(ne,ne2);
de->Add(de,de1);
de->Add(de,de2);
NE += eventTree->GetEntries(LMuZ+SEEZ1n);
NE += eventTree->GetEntries(LMuZ+SEEZ2n);
DE += 2*eventTree->GetEntries(LMuZ+SEEZtd);
e->cd();
eleEleEleEleEventTreeID->cd();
eventTree->Draw("z2l1Pt>>ne1(10,0,100)",LEleZ+SEEZ1n);
eventTree->Draw("z2l2Pt>>ne2(10,0,100)",LEleZ+SEEZ2n);
eventTree->Draw("z2l1Pt>>de1(10,0,100)",LEleZ+SEEZtd);
eventTree->Draw("z2l2Pt>>de2(10,0,100)",LEleZ+SEEZtd);
ne->Add(ne,ne1);
ne->Add(ne,ne2);
de->Add(de,de1);
de->Add(de,de2);
NE += eventTree->GetEntries(LEleZ+SEEZ1n);
NE += eventTree->GetEntries(LEleZ+SEEZ2n);
DE += 2*eventTree->GetEntries(LEleZ+SEEZtd);

//////////////////////////////Integral Method/////////////////////////////////////////////
double IFREle,IFREleErr,IFRMu,IFRMuErr;
IFREle = NE/DE;
IFREleErr = sqrt(NE/(DE*DE)+NE*NE/(DE*DE*DE));
IFRMu = NM/DM;
IFRMuErr = sqrt(NM/(DM*DM)+NM*NM/(DM*DM*DM));
cout << "Integral ele fakerate = " << IFREle << " +- " << IFREleErr << endl;
cout << "Integral mu fakerate = " << IFRMu << " +- " << IFRMuErr << endl;
m->cd();
eleEleEleEleEventTreeID->cd();
double EEEE = eventTree->GetEntries(LEleZ+SEEZcuts);
double eeee = IFREle*EEEE/(1-IFREle);
double eeeeErr = sqrt(EEEE*IFREle*IFREle+IFREleErr*IFREleErr*EEEE*EEEE);
cout << "Background Est. for EEEE = " << eeee << " +- " << eeeeErr << endl;
e->cd();
eleEleEleMuEventTreeID->cd();
double EEEM = eventTree->GetEntries(LEleZ+SEMZcuts);
double eeem = IFREle*EEEM/(1-IFREle);
double eeemErr = sqrt(EEEM*IFREle*IFREle+IFREleErr*IFREleErr*EEEM*EEEM);
cout << "Background Est. for EEEM = " << eeem << " +- " << eeemErr << endl;
m->cd();
muMuEleMuEventTreeID->cd();
double MMEM = eventTree->GetEntries(LMuZ+SEMZcuts);
double mmem = IFREle*MMEM/(1-IFREle);
double mmemErr = sqrt(MMEM*IFREle*IFREle+IFREleErr*IFREleErr*MMEM*MMEM);
cout << "Background Est. for MMEM = " << mmem << " +- " << mmemErr << endl;
m->cd();
muMuEleEleEventTreeID->cd();
double MMEE = eventTree->GetEntries(LMuZ+SEEZcuts);
double mmee = IFREle*MMEE/(1-IFREle);
double mmeeErr = sqrt(MMEE*IFREle*IFREle+IFREleErr*IFREleErr*MMEE*MMEE);
cout << "Background Est. for MMEE = " << mmee << " +- " << mmeeErr << endl;
m->cd();
eleEleMuMuEventTreeID->cd();
double EEMM = eventTree->GetEntries(LEleZ+SMMZcuts);
double eemm = IFRMu*IFRMu*EEMM/(1-IFRMu*IFRMu);
double eemmErr = sqrt(EEMM*IFRMu*IFRMu+IFRMuErr*IFRMuErr*EEMM*EEMM);
cout << "Background Est. for EEMM = " << eemm << " +- " << eemmErr << endl;
m->cd();
muMuMuMuEventTreeID->cd();
double MMMM = eventTree->GetEntries(LMuZ+SMMZcuts);
double mmmm = IFRMu*MMMM/(1-IFRMu);
double mmmmErr = sqrt(MMMM*IFRMu*IFRMu+IFRMuErr*IFRMuErr*MMMM*MMMM);
cout << "Background Est. for MMMM = " << mmmm << " +- " << mmmmErr << endl;

/////////////////Fit Method/////////////////////////
mm->BayesDivide(nm,dm);
mm->Draw("AP");
TF1 *myfit1 = new TF1("myfit1","[0] + [1]*exp([2]*x)", 0, 100);
myfit1->SetParameter(0, 0);
myfit1->SetParameter(1, 0);
myfit1->SetParameter(2, 0);
mm->Fit("myfit1","WR");
C->SaveAs("FitPlots/mu.png");
double c0 = myfit1->GetParameter(0);
double c1 = myfit1->GetParameter(1);
double c2 = myfit1->GetParameter(2);
double e0 = myfit1->GetParError(0);
double e1 = myfit1->GetParError(1);
double e2 = myfit1->GetParError(2);
ee->BayesDivide(ne,de);
ee->Draw("AP");
TF1 *myfit2 = new TF1("myfit2","[0] + [1]*exp([2]*x)", 0, 100);
myfit2->SetParameter(0, 0);
myfit2->SetParameter(1, 0);
myfit2->SetParameter(2, 0);
ee->Fit("myfit2","WR");
C->SaveAs("FitPlots/ele.png");
// double c0e = myfit2->GetParameter(0);
// double c1e = myfit2->GetParameter(1);
// double c2e = myfit2->GetParameter(2);
// double e0e = myfit2->GetParError(0);
// double e1e = myfit2->GetParError(1);
// double e2e = myfit2->GetParError(2);
// std::ostringstream S0;
// std::ostringstream S1;
// std::ostringstream S2;
// std::ostringstream E0;
// std::ostringstream E1;
// std::ostringstream E2;
// std::ostringstream S0e;
// std::ostringstream S1e;
// std::ostringstream S2e;
// std::ostringstream E0e;
// std::ostringstream E1e;
// std::ostringstream E2e;
// S0 << c0;
// S1 << c1;
// S2 << c2;
// E0 << e0;
// E1 << e1;
// E2 << e2;
// S0e << c0e;
// S1e << c1e;
// S2e << c2e;
// E0e << e0e;
// E1e << e1e;
// E2e << e2e;
// TString s0 = S0.str();
// TString s1 = S1.str();
// TString s2 = S2.str();
// TString se0 = E0.str();
// TString se1 = E1.str();
// TString se2 = E2.str();
// TString s0e = S0e.str();
// TString s1e = S1e.str();
// TString s2e = S2e.str();
// TString se0e = E0e.str();
// TString se1e = E1e.str();
// TString se2e = E2e.str();
// 
// TString tt1 = "("+s0+"*tautauPt1/tautauPt1+"+s1+"*exp(tautauPt1*"+s2+"))";
// TString tt2 = "("+s0+"*tautauPt2/tautauPt2+"+s1+"*exp(tautauPt2*"+s2+"))";
// TString tte1 = "("+se0+"^2*tautauPt1/tautauPt1+("+se1+"^2+"+s1+"^2*tautauPt1^2*"+se2+"^2)*exp(2*tautauPt1*"+s2+"))";
// TString tte2 = "("+se0+"^2*tautauPt2/tautauPt2+("+se1+"^2+"+s1+"^2*tautauPt2^2*"+se2+"^2)*exp(2*tautauPt2*"+s2+"))";
// TString et = "("+s0VL+"*eletauPt/eletauPt+"+s1VL+"*exp(eletauPt*"+s2VL+"))";
// TString mt = "("+s0VL+"*mutauPt/mutauPt+"+s1VL+"*exp(mutauPt*"+s2VL+"))";
// TString ete = "("+se0VL+"^2*eletauPt/eletauPt+("+se1VL+"^2+"+s1VL+"^2*eletauPt^2*"+se2VL+"^2)*exp(2*eletauPt*"+s2VL+"))";
// TString mte = "("+se0VL+"^2*mutauPt/mutauPt+("+se1VL+"^2+"+s1VL+"^2*mutauPt^2*"+se2VL+"^2)*exp(2*mutauPt*"+s2VL+"))";
// 
// /////////////////Apply fit to individual channels////////////////////////////////////
// eventTree->Draw("1>>ll(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
// double llv = ll->GetBinContent(1);
// eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
// double llev1 = lle->GetBinContent(1);
// eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tte1+"*"+tt2+"");
// double llev2 = lle->GetBinContent(1);
// eventTree->Draw("1>>lle(1,1,2)","("+LMuZ+STTZcuts+")*"+tt1+"*"+tte2+"");
// double llev3 = lle->GetBinContent(1);
// double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
// cout << "Z+Jets Background for MMTT = " << llv << " +- " << llev << endl;
// e->cd();
// eleEleTauTauEventTreeID->cd();
// eventTree->Draw("1>>ll(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"*"+tt2+"/(1-"+tt1+"*"+tt2+")");
// double llv = ll->GetBinContent(1);
// eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"^2*"+tt2+"^2");
// double llev1 = lle->GetBinContent(1);
// eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tte1+"*"+tt2+"");
// double llev2 = lle->GetBinContent(1);
// eventTree->Draw("1>>lle(1,1,2)","("+LEleZ+STTZcuts+")*"+tt1+"*"+tte2+"");
// double llev3 = lle->GetBinContent(1);
// double llev = sqrt(llev1+llev2*llev2+llev3*llev3);
// cout << "Z+Jets Background for EETT = " << llv << " +- " << llev << endl;
// e->cd();
// eleEleEleTauEventTreeID->cd();
// eventTree->Draw("1>>l(1,1,2)","("+LEleZ+SETZcuts+")*"+et+"/(1-"+et+")");
// double lv = l->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SETZcuts+")*"+et+"^2");
// double ler1 = le->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SETZcuts+")*"+ete);
// double ler2 = le->GetBinContent(1);
// double ler = sqrt(ler1+ler2*ler2);
// cout << "Z+Jets Background for EEET = " << lv << " +- " << ler << endl;
// m->cd();
// muMuEleTauEventTreeID->cd();
// eventTree->Draw("1>>l(1,1,2)","("+LMuZ+SETZcuts+")*"+et+"/(1-"+et+")");
// double lv = l->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SETZcuts+")*"+et+"^2");
// double ler1 = le->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SETZcuts+")*"+ete);
// double ler2 = le->GetBinContent(1);
// double ler = sqrt(ler1+ler2*ler2);
// cout << "Z+Jets Background for MMET = " << lv << " +- " << ler << endl;
// m->cd();
// muMuMuTauEventTreeID->cd();
// eventTree->Draw("1>>l(1,1,2)","("+LMuZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
// double lv = l->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SMTZcuts+")*"+mt+"^2");
// double ler1 = le->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LMuZ+SMTZcuts+")*"+mte);
// double ler2 = le->GetBinContent(1);
// double ler = sqrt(ler1+ler2*ler2);
// cout << "Z+Jets Background for MMMT = " << lv << " +- " << ler << endl;
// e->cd();
// eleEleMuTauEventTreeID->cd();
// eventTree->Draw("1>>l(1,1,2)","("+LEleZ+SMTZcuts+")*"+mt+"/(1-"+mt+")");
// double lv = l->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SMTZcuts+")*"+mt+"^2");
// double ler1 = le->GetBinContent(1);
// eventTree->Draw("1>>le(1,1,2)","("+LEleZ+SMTZcuts+")*"+mte);
// double ler2 = le->GetBinContent(1);
// double ler = sqrt(ler1+ler2*ler2);
// cout << "Z+Jets Background for EEMT = " << lv << " +- " << ler << endl;


}