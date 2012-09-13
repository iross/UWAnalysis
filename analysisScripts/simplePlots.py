#!/usr/bin/env python
from ROOT import *
from array import *
from CommonSelectors import *

import logging,Colorer
logging.basicConfig(level=logging.DEBUG, format='%(asctime)s - %(levelname)s - %(message)s')

ROOT.gROOT.ProcessLine(".X CMSStyle.C")
ROOT.gROOT.SetBatch(True)

def makeHist(tree, var,  nbin, xmin, xmax):
    #	print "Making hist with",nbin,"bins from",xmin,"to",xmax
    h = TH1F("temp","temp",nbin,xmin,xmax)
    tree.Draw(var+">>temp")
    return h


def makeHist(tree, var, cuts, nbin, xmin, xmax, overflow=False, customBinning=False, bins=[0,1]):
    #	logging.debug("Making hist with %i bins, from %d to %d",nbin,xmin,xmax)
    h = TH1F("temp","temp",nbin,xmin,xmax)
    h.Sumw2()
    if customBinning:
        h = TH1F("temp","temp",len(bins)-1,array('d',bins))
    if overflow:
        #		print "\twas",hist.GetBinContent(nbin)
        hist.SetBinContent(nbin,hist.GetBinContent(nbin)+hist.GetBinContent(nbin+1))
#		print "\tnow",hist.GetBinContent(nbin)
    tree.Draw(var+">>temp",cuts,"goff")
    return h

def compTrees(trees,var,bins,cuts="1",names=[""],drawOptions="h",prefix=""):
    """Compare variables from some trees"""
    can=TCanvas("can","can",600,600)
    leg=TLegend(0.7,0.7,0.9,0.9)
    colors=[kBlack,kBlue,kRed,kGreen,kCyan,kRed-9]
    markers=[20,22,24,26,29,34]
    nbin=len(bins)
    xmin=min(bins)
    xmax=max(bins)
    h={}
    maxY=0
    i=0 
    for tree in trees:
        h[tree.GetDirectory().GetName()+names[i]]=makeHist(tree, var, cuts, nbin, xmin, xmax, False, True, bins)
        maxY=max(maxY,h[tree.GetDirectory().GetName()+names[i]].GetMaximum())
#        maxY=max(maxY,h[tree.GetDirectory().GetName()+names[i]].GetMaximum()/h[tree.GetDirectory().GetName()+names[i]].Integral())
        i=i+1
    i=0 
    print h
    for hist in h:
        #temp normalize both to 5.1
        if "2012C" in hist:
            print h[hist].Integral()
            h[hist].Scale(5.05/3.67)
            print h[hist].Integral()
#        h[hist].Scale(1/h[hist].Integral())
        h[hist].SetLineColor(colors[i])
        h[hist].SetMarkerStyle(markers[i])
        h[hist].SetMarkerColor(colors[i])
        h[hist].SetLineWidth(2)
        print i
        h[hist].SetName(names[i])
        h[hist].SetTitle(names[i])
        leg.AddEntry(h[hist])
        if i==0:
            h[hist].GetXaxis().SetTitle(var)
            h[hist].GetYaxis().SetRangeUser(0,maxY*1.15)
            if bins[0]-bins[1] == bins[len(bins)-2]-bins[len(bins)-1]: # if spaced evenly
                div=(float(bins[len(bins)-1])-float(bins[0]))/(len(bins)-1)
                h[hist].GetYaxis().SetTitle("Events / %.2f" %div)
                h[hist].GetYaxis().SetRange(0,15)
            else:
                h[hist].GetYaxis().SetTitle("Events")
                h[hist].GetYaxis().SetRange(0,15)
            h[hist].Draw(drawOptions)
        else:
            print "drrrrrawing"
            h[hist].Draw(drawOptions+"same")
        i+=1
        print h[hist].Integral()
    leg.SetFillColor(kWhite)
    leg.SetShadowColor(0)
    leg.Draw()
    can.SaveAs(prefix+"comp"+var+".png")
    return can

def getYields(file, lumi, cuts=""):
    fin = TFile(file)
    if cuts != "":
        cuts="*"+cuts
    for t in fin.GetListOfKeys():
        tree = t.GetName()
        t=fin.Get(tree)
        #Note: use __CORR__ for 2l2t, __CORRnoHLT__ for 4l
        h=makeHist(t, "z1Mass", "(1)*__WEIGHT__noPU*__CORRnoHLT__*"+lumi+cuts, 60, 60, 120)
        h2 = TH1F("h2","h2",2,0,2)
        h2.Sumw2()
#		t.Draw("1>>h2","(1)*__WEIGHT__noPU*__CORRnoHLT__*"+lumi+cuts)
        t.Draw("1>>h2","(1)*__WEIGHT__noPU*__CORR__*"+lumi+cuts)
        print tree,"--",round(h2.GetBinContent(2)*149/139,2),"+/-",round(h2.GetBinError(2)*149/139,2)
#		print tree,"--",round(h2.GetBinContent(2),2),"+/-",round(h2.GetBinError(2),2)
        h.Delete()
        h2.Delete()

def fit(hist):
    logging.debug("Fitting histogram %s",hist.GetTitle())	
    gSystem.Load("libRooFit")
    mass = RooRealVar("mass","mass",0,120)
    mean = RooRealVar("mean","mean",0,60)
    sigma = RooRealVar("sigma","sigma",0,10)
    Yield = RooRealVar("yield","yield",50,0,1000)
#	hist = TH1F("hist","hist",12,0,120)

#	tree.Draw("z2Mass>>hist",defineCuts(common.cuts(),stdIso("z1l1",0.275,"ele",True),stdIso("z1l2",0.275,"ele",True),"!"+stdIso("z2l1",0.275,"mu"),"!"+stdIso("z2l2",0.275,"mu"),z1Sip.cuts(),"z2Charge==0&&z2Mass>12&&z2Mass<120"))

    print hist.Integral(),"seen in data"
    land = RooLandau("land","land",mass,mean,sigma)
    data = RooDataHist("data","data",RooArgList(mass),hist)

    totalPdf = RooAddPdf("totalPdf","total",RooArgList(land),RooArgList(Yield))

    totalPdf.fitTo(data)
    C = mass.frame()
    data.plotOn(C)
    totalPdf.plotOn(C)
    C.Draw()
    raw_input("How's that fit look?")
    print mean.getVal(),"+-",mean.getErrorHi(),mean.getErrorLo()
    print sigma.getVal(),"+-",sigma.getErrorHi(),sigma.getErrorLo()
    mass.setRange("onshellReg",60,120)
    integral = totalPdf.createIntegral(RooArgSet(mass),RooArgSet(mass),"onshellReg")
    expected = integral.getVal()*Yield.getVal()
    print "Expected in on-shell region:",expected

def measureLeptonFakes(file, extra="", customBinning=False, bins=[0,1]):
    logging.debug('Measuring fakes from file:%s',file)
    file = TFile(file)
    if customBinning:
        enum = TH1F("enum","enum",len(bins)-1,array('d',bins))
        eden = TH1F("eden","eden",len(bins)-1,array('d',bins))
        mnum = TH1F("mnum","mnum",len(bins)-1,array('d',bins))
        mden = TH1F("mden","mden",len(bins)-1,array('d',bins))
    else: 
        enum = TH1F("enum","enum",12,0,120)
        eden = TH1F("eden","eden",12,0,120)
        mnum = TH1F("mnum","mnum",12,0,120)
        mden = TH1F("mden","mden",12,0,120)
    #todo: re-implement the nElectron/nMuon vetos
    enum.Add(makeHist(file.Get("eleEleEleEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eleNum.cuts()+extra),12,0,120,False,customBinning,bins))
    eden.Add(makeHist(file.Get("eleEleEleEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eleDen.cuts()),12,0,120,False,customBinning,bins))
    enum.Add(makeHist(file.Get("muMuEleEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),eleNum.cuts()+extra),12,0,120,False,customBinning,bins))
    eden.Add(makeHist(file.Get("muMuEleEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),eleDen.cuts()),12,0,120,False,customBinning,bins))

    mnum.Add(makeHist(file.Get("eleEleMuEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),muNum.cuts()+extra),12,0,120,False,customBinning,bins))
    mden.Add(makeHist(file.Get("eleEleMuEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),muDen.cuts()),12,0,120,False,customBinning,bins))
    mnum.Add(makeHist(file.Get("muMuMuEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),muNum.cuts()+extra),12,0,120,False,customBinning,bins))
    mden.Add(makeHist(file.Get("muMuMuEventTree/eventTree"),"z2l1Pt",defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),muDen.cuts()),12,0,120,False,customBinning,bins))

    c1=TCanvas("can","can",600,600)
    eleFr = TGraphAsymmErrors()
    eleFr.BayesDivide(enum,eden)
    eleFr.GetYaxis().SetRangeUser(0,1.0)
    eleFr.GetXaxis().SetTitle("e p_{T}")
    eleFr.GetYaxis().SetTitle("Fake Rate")
    eleFr.Draw("ap")
    c1.SaveAs("ele_FR.C")
    raw_input("Press any key to look at muons")
    muFr = TGraphAsymmErrors()
    muFr.BayesDivide(mnum,mden)
    muFr.GetYaxis().SetRangeUser(0,1.0)
    muFr.GetXaxis().SetTitle("#mu p_{T}")
    muFr.GetYaxis().SetTitle("Fake Rate")
    muFr.Draw("ap")
    c1.SaveAs("mu_FR.C")
    print "------Totals------"
    print "--Electrons--"
    print "\t",enum.Integral()/eden.Integral(),"=",enum.Integral(),"/",eden.Integral()
    print "--Muons--"
    print "\t",mnum.Integral()/mden.Integral(),"=",mnum.Integral(),"/",mden.Integral()
    return [eleFr,muFr]

def main():
    f1 = TFile("BG_StdIso.root")
    f2 = TFile("Z2Jets_BGStdIso.root")
    c = TCanvas()
#	files=[f1,f2]
    files = [f1]
    hs = THStack("hs","stacked")
    for f in files:
        t = f.Get("eleEleMuMuEventTree_antiIso/eventTree")
        histEEMM = makeHist(t,"z2Mass",defineCuts(common.cuts(),stdIso("z1l1",0.275,"ele",True),stdIso("z1l2",0.275,"ele",True),"!"+stdIso("z2l1",0.275,"mu"),"!"+stdIso("z2l2",0.275,"mu"),z1Sip.cuts(),"z2Charge==0&&z2Mass>12&&z2Mass<120"),12,0,120)
        fit(histEEMM)
        t = f.Get("muMuEleEleEventTree_antiIso/eventTree")
        histMMEE = makeHist(t,"z2Mass",defineCuts(common.cuts(),stdIso("z1l1",0.275,"mu",True),stdIso("z1l2",0.275,"mu",True),"!"+stdIso("z2l1",0.275,"ele"),"!"+stdIso("z2l2",0.275,"ele"),z1Sip.cuts(),"z2Charge==0&&z2Mass>12&&z2Mass<120"),12,0,120)
        fit(histMMEE)
        t = f.Get("muMuMuMuEventTree_antiIso/eventTree")
        histMMMM = makeHist(t,"z2Mass",defineCuts(common.cuts(),stdIso("z1l1",0.275,"mu",True),stdIso("z1l2",0.275,"mu",True),"!"+stdIso("z2l1",0.275,"mu"),"!"+stdIso("z2l2",0.275,"mu"),z1Sip.cuts(),"z2Charge==0&&z2Mass>12&&z2Mass<120"),12,0,120)
        fit(histMMMM)
        t = f.Get("eleEleEleEleEventTree_antiIso/eventTree")
        histEEEE = makeHist(t,"z2Mass",defineCuts(common.cuts(),stdIso("z1l1",0.275,"ele",True),stdIso("z1l2",0.275,"ele",True),"!"+stdIso("z2l1",0.275,"ele"),"!"+stdIso("z2l2",0.275,"ele"),z1Sip.cuts(),"z2Charge==0&&z2Mass>12&&z2Mass<120"),12,0,120)
        fit(histEEEE)
        print f.GetName()
        if "Z2" in f.GetName():
            print "Z2j"
            hist.SetFillColor(kRed)
#		hist.Draw()
#		print hist.Integral()
#		hs.Add(hist)
#	hs.Draw()
    histEEMM.Add(histMMEE)
    histEEMM.Add(histMMMM)
    histEEMM.Add(histEEEE)
    print "Total total total:",histEEMM.Integral()
    fit(histEEMM)
    c.Update()
    raw_input("Press Enter")

if __name__=='__main__':main()
