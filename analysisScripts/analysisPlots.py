#!/Library/Frameworks/EPD64.framework/Versions/Current/bin//python
from ROOT import *
from simplePlots import *
import math
import os
from optparse import OptionParser

import numpy as np

ROOT.gROOT.ProcessLine(".X CMSStyle.C")
ROOT.gROOT.SetBatch(True)

def getTrees(file,postfix):
    arr={}
    arr['eeee']=file.Get("eeeeFinal"+postfix)
    arr['eemm']=file.Get("mmeeFinal"+postfix)
    arr['mmmm']=file.Get("mmmmFinal"+postfix)
    #hack: if data, use FSR tree
#   if "DATA" in file.GetName():
#       arr['eemm']=file.Get("eleEleMuMuEventTreeFinalFSR")
    return arr

def eventDump(tree,extra):
    """Dump some info about the contents of the passed tree"""
    print tree
    f=open("2012/"+tree.GetName().split("EventTree")[0]+".txt",'w')
    tree2=tree.CopyTree(extra)
    f.write('-------%s-------\n' % tree.GetName().split("EventTree")[0])
    for ev in tree2:
        f.write("RUN: %.0f\tEVENT: %.0f\n"%(ev.RUN,ev.EVENT))
        f.write("Z1m: %.2f\t Z2m: %.2f\t m_4l: %.2f"%(ev.z1Mass,ev.z2Mass,ev.mass))
        f.write('\n\n')
    f.write('%.0f total events\n' % tree2.GetEntries())
    f.close()

def makeScatter(fd,year,lumi):
    can = TCanvas("can","can",600,600)
    fd=TFile(fd)
    d={}
#these are 2012
#   d["eeee"]=fd.Get("eleEleEleEleEventTreeCleaned")
#   d["mmmm"]=fd.Get("muMuMuMuEventTreeCleaned")
    #use llll and eemm trees with FSR event
#   d["eemm"]=fd.Get("eleEleMuMuEventTreeFinalFSR")
    #these are 2011
    d["eeee"]=fd.Get("eeeeFinal")
    d["eemm"]=fd.Get("mmeeFinal")
    d["mmmm"]=fd.Get("mmmmFinal")
    d["4l"]=fd.Get("llllTree")
    d["2l2t"]=fd.Get("llttTree")


    for state in d:
        #HACK
        varx="z1Mass"
        texx=63
        varxNice="Z_{M}^{1} (GeV)"
        vary="z2Mass"
        varx="z1Mass*(abs(z1Mass-91.2)<abs(z2Mass-91.2))+z2Mass*(abs(z2Mass-91.2)<abs(z1Mass-91.2))"
        vary="z1Mass*(abs(z1Mass-91.2)>abs(z2Mass-91.2))+z2Mass*(abs(z2Mass-91.2)>abs(z1Mass-91.2))"
        if state=="2l2t":
            varyNice="Z_{M}^{#tau#tau} (GeV)"
        else:
            varyNice="Z_{M}^{2} (GeV)"
        min=60
        max=120
        nbins=1200
        if state=="2l2t":
#           d[state].Scan(varx+":"+vary)
            h2=makeHist2D(d[state],"1",varx,nbins,min,max,vary,nbins,30,90)
        else:
#           d[state].Scan(varx+":"+vary)
            print state
            h2=makeHist2D(d[state],"1",varx,nbins,min,max,vary,nbins,min,max)
        h2.GetXaxis().SetTitle(varxNice)
        h2.GetYaxis().SetTitle(varyNice)
        h2.Draw()
        ymax=120
        l1 = TLatex(texx,ymax*1.015,"CMS Preliminary "+year);
        l1.SetTextSize(0.04);
        if year=="2012":
            l="8"
        else:
            l="7"
        l2 = TLatex(texx+0.4,ymax*1.015,"L_{int} = "+lumi+" fb^{-1}, #sqrt{s} = "+l+" TeV");
        l2.SetTextSize(0.04);
        l1.Draw()
        l2.Draw()

        can.SaveAs(year+"/"+state+"/"+state+"_z1Mass_z2Mass.png")
        can.SaveAs(year+"/"+state+"/"+state+"_z1Mass_z2Mass.root")
        can.SaveAs(year+"/"+state+"/"+state+"_z1Mass_z2Mass.C")

def makePlots(dir="2012",postfix="8TeV",lumi="2.95",extra="1",var="z1Mass",varNice="Z_{M}^{1}",bins=range(60,120,5),legx=0.2,legW=0.3,legy=0.3,legH=0.3,log=False):
#    fd=TFile("DATA_12Jun_wMuEG_combed_plusFSR.root")
#    fd=TFile("DATAfinal.root")
    fd=TFile("DATA_fullHcp_lite.root")
    d=getTrees(fd,"")

    eventDump(d["eeee"],extra)
    eventDump(d["eemm"],extra)
    eventDump(d["mmmm"],extra)

    year=dir
    if year=="2012":
        l="8"
    else:
        l="7"

#   fzz=TFile("ZZ_8TeV.root")
#   fzz=TFile("ZZ_8TeV_wNoPU.root")
#   fzz=TFile("ggZZ_combed.root")
#   fzz=TFile("ZZ_combed_test.root")
#    fzz=TFile("qqZZ_combed.root")
#    fzz=TFile("qqZZ_7TeV_combed.root")
#    fzz=TFile("zzz_zz_f4_0.000_f5_0.000.root")
    fzz=TFile("qqZZ_lite.root")
#    fzz=TFile("ZZ4L_final_fixed.root")
    zz=getTrees(fzz,"")

    fzj=TFile("DYJets_lite.root")
    zj=getTrees(fzj,"")
    
    fh=TFile("ggH125_lite.root")
    ht=getTrees(fh,"")

#    fatgc=TFile("fZ_0p015_0p000_combed.root")
#    fatgc=TFile("zzz_zz_f4_0.000_f5_0.000.root")
#    zza=getTrees(fatgc,"Merged")

    can = TCanvas("can","can",600,600)

    leg=TLegend(legx,legy,legx+legW,legy+legH)

    dht=TH1F("dh","dh",len(bins)-1,array('d',bins))
    dh={}
    for tree in d:
        t=d[tree]
        dh[tree]=makeHist(t,var,extra,50,100,600,False,True,bins)
        dht.Add(dh[tree])
    dh["4l"]=dht

    zzht=TH1F("zzh","zzh",len(bins)-1,array('d',bins))
    zzh={}
    for tree in zz:
        t=zz[tree]
#        zzh[tree]=makeHist(t,var,"("+extra+")*(__WEIGHT__noPU*__CORRnoHLT__*149/139*"+lumi+"*1000)",50,100,600,False,True,bins)
#        zzh[tree]=makeHist(t,var,"("+extra+")*(__WEIGHT__noPU*149/139*1.06*"+lumi+"*1000)",50,100,600,False,True,bins)
        zzh[tree]=makeHist(t,var,"("+extra+")*(__WEIGHT__noPU*"+lumi+"*1000)",50,100,600,False,True,bins)
    #   zzh[tree]=makeHist(t,var,"1*"+lumi+"*1000",50,100,600,False,True,bins)
        zzht.Add(zzh[tree])
        zzh[tree].SetFillColor(kAzure-9)
        zzh[tree].SetMarkerSize(0.001)
    zzh["4l"]=zzht

#    zzaht=TH1F("zzh","zzh",len(bins)-1,array('d',bins))
#    zzah={}
#    for tree in zza:
#        t=zza[tree]
#        zzah[tree]=makeHist(t,var,"("+extra+")*(weightnoPU*"+lumi+"*1000*149/139*1.06)",50,100,600,False,True,bins) #do I need this?
#    #   zzah[tree]=makeHist(t,var,"1*"+lumi+"*1000",50,100,600,False,True,bins)
#        zzaht.Add(zzah[tree])
#        zzah[tree].SetFillColor(kWhite-9)
#        zzah[tree].SetMarkerSize(0.001)
#    zzah["4l"]=zzaht
#    print '---------'
#    print zzah["4l"].Integral()
#    print zzh["4l"].Integral()
#    print '---------'

    hht=TH1F("hh","hh",len(bins)-1,array('d',bins))
    hh={}
    for tree in ht:
        t=ht[tree]
        hh[tree]=makeHist(t,var,"("+extra+")*(__WEIGHT__noPU*"+lumi+"*1000)",50,100,600,False,True,bins)
    #   zzh[tree]=makeHist(t,var,"1*"+lumi+"*1000",50,100,600,False,True,bins)
        hht.Add(hh[tree])
        hh[tree].SetFillColor(kWhite)
        hh[tree].SetLineColor(kRed)
        hh[tree].SetLineWidth(2)
        hh[tree].SetMarkerSize(0.001)
    hh["4l"]=hht

    zjht=TH1F("zjh","zjh",len(bins)-1,array('d',bins))
    zjh={}
    for tree in zj:
        t=zj[tree]
        zjh[tree]=makeHist(t,var,"("+extra+")*(__WEIGHT__noPU*"+lumi+"*1000)",50,100,600,False,True,bins)
        zjh[tree].SetFillColor(kGreen-5)
        zjh[tree].SetMarkerSize(0.001)
#    zjh['mmmm'].Scale(0.52/zjh['mmmm'].Integral())
#    zjh['eemm'].Scale(0.58/zjh['eemm'].Integral())
#    zjh['eeee'].Scale(0.25/zjh['eeee'].Integral())
    for hist in zjh:
        zjht.Add(zjh[hist])
    zjh['4l']=zjht

    #colors, etc.
    zzht.SetMarkerSize(0.001)
    zzht.SetFillColor(kAzure-9)
    hht.SetMarkerSize(0.001)
    hht.SetFillColor(kWhite)
    hht.SetLineColor(kRed)
    hht.SetLineWidth(2)
    zjht.SetMarkerSize(0.001)
    zjht.SetFillColor(kGreen-5)
#    zzaht.SetMarkerSize(0.001)

    #legend
    leg.SetFillColor(kWhite)
    leg.AddEntry(dht,"Data","p")
    leg.AddEntry(zzht,"ZZ","f")
    leg.AddEntry(zjht,"Z+X","f")
    leg.AddEntry(hht,"h125","f")
#    leg.AddEntry(zzaht,"f_{4}^{Z}=0.015","l")
#    leg.AddEntry(zzaht,"SHERPA","l")
    leg.SetBorderSize(1)

    #set axis options for data
    for state in dh:
        dh[state].GetXaxis().SetTitle(varNice)
    for hist in [dht, dh['mmmm'], dh['eemm'], dh['eeee']]:
        if bins[0]-bins[1] == bins[len(bins)-2]-bins[len(bins)-1]: # if spaced evenly
            div=(float(bins[len(bins)-1])-float(bins[0]))/(len(bins)-1)
            hist.GetYaxis().SetTitle("Events / %.0f GeV" %div)
            hist.GetYaxis().SetRange(0,15)
        else:
            hist.GetYaxis().SetTitle("Events")
            hist.GetYaxis().SetRange(0,15)
    #HACK! efficiencies taken as average of Matt's TP corrected yields/uncorrected
    eff={}
    eff["eeee"]=0.979
    eff["eemm"]=0.9885
    eff["mmmm"]=0.9876
    eff["4l"]=(eff["eeee"]+eff["mmmm"]+2.0*eff["eemm"])/4.0
    f=open(dir+"/yields.txt","w")
    for state in dh:
        f.write("---"+state+"---\n")
        f.write("Data: "+str(dh[state].Integral())+"\n")
        f.write("ZZ: "+str(zzh[state].Integral())+"\n")
#        f.write("ZJets:"+str(zjh[state].Integral())+"\n")
        if not os.path.exists(dir+"/"+state):
            os.makedirs(dir+"/"+state)
        hs=THStack("hs","stack bg")
#        hs.Add(zjh[state])
        hs.Add(zzh[state])
        hs.Add(hh[state])   
        print state,zzh[state].Integral()
        ymax=max(dh[state].GetMaximum(),hs.GetMaximum())
        ymax=ceil(ymax+sqrt(ymax))
        ymax=int(ymax)
        l1 = TLatex(bins[0]+(bins[len(bins)-1]-bins[0])/100.0,ymax*1.015,"CMS Preliminary "+year);
        l1.SetTextSize(0.04);
        l2 = TLatex(bins[0]+(bins[len(bins)-1]-bins[0])/2.0,ymax*1.015,"L_{int} ="+lumi+" fb^{-1}, #sqrt{s} = "+l+" TeV");
        l2.SetTextSize(0.04);
        if log:
            dh[state].GetYaxis().SetRangeUser(0.1,ymax)
        else:
            dh[state].GetYaxis().SetRangeUser(0.,ymax)

        dh[state].Draw("e")

#        hsa=THStack("hsa","stack bg")
#        zzah[state].SetLineStyle(7)
#        zzah[state].SetLineWidth(2)
#        zzah[state].SetMarkerSize(0.0002)
#        hsa.Add(zjh[state])
#        hsa.Add(zzah[state])

        dh[state].SetMarkerStyle(20)
        dh[state].SetMarkerSize(1)

        hs.Draw("hsame")
#        hsa.Draw("hsame")
        dh[state].Draw("esame")
        leg.Draw()
        l1.Draw();
        l2.Draw();
        if log:
            can.SetLogy(1)

        if str(bins[0]-bins[1]) == str(bins[len(bins)-2]-bins[len(bins)-1]): # if spaced evenly
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".png")
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".pdf")
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".root")
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".C")
        else:
            binStr=""
            print
            for i in range(len(bins)-1):
                binStr+="_"+str(bins[i])
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_varbinning"+postfix+binStr+".png")
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_varbinning"+postfix+binStr+".pdf")
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_varbinning"+postfix+binStr+".root")
            can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_varbinning"+postfix+binStr+".C")
    f.close()

if __name__ == '__main__':
    parser=OptionParser(description="%prog -- dump some analysis-level plots and yields",usage="%prog --extra='extra cuts to apply'")
    parser.add_option("--extra",dest="extra",type="string",default="1")
    parser.add_option("--lumi",dest="lumi",type="string",default="5.02")
    (options,args)=parser.parse_args()
    extra=options.extra
    lumi=options.lumi

#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{4l}",bins=range(80,610,10),legx=0.6)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{4l}",bins=range(90,170,5),legx=0.6)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1Pt",varNice="Z_{Pt}^{1}",bins=range(0,200,10),legx=0.7)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2Pt",varNice="Z_{Pt}^{2}",bins=range(0,200,10),legx=0.7)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l1Pt",varNice="Z_{1}l_{1} p_{T}",bins=range(0,200,10),legx=0.7)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l2Pt",varNice="Z_{1}l_{2} p_{T}",bins=range(0,200,10),legx=0.7)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l1Pt",varNice="Z_{2}l_{1} p_{T}",bins=range(0,200,10),legx=0.7)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l2Pt",varNice="Z_{2}l_{2} p_{T}",bins=range(0,200,10),legx=0.7)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1Mass",varNice="Z_{M}^{1}",bins=range(60,125,5),legx=0.2)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2Mass",varNice="Z_{M}^{2}",bins=range(60,125,5),legx=0.2)
#   makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="vertices",varNice="Reco. Vertices",bins=range(0,50,50),legx=0.7)
#    tempBin=[100,120,140,160,180,200,250,300,350,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000]
#    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legH=0.2)
#    tempBin=[100,120,140,160,180,200,250,300,350,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000]
#    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legH=0.2)
#    tempBin=[100,120,140,160,180,200,250,300,350,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600]
#    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legH=0.2)
#    tempBin=[100,120,140,160,180,200,225,250,275,300,350,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600]
#    makePlots(dir="2011",postfix="7TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legH=0.2)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=range(80,1020,20),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV_10wide",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=range(80,1010,10),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="_low_8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=range(72,186,3),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="_low_fine_8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=range(100,151,1),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="_zPeak_fine_8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=range(80,101,1),legx=0.15,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1Mass",varNice="M_{Z1}",bins=range(40,125,5),legx=0.2,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV_signal",lumi=lumi,extra=extra+"&&mass>121.5&&mass<131.5",var="z1Mass",varNice="M_{Z1}",bins=range(40,125,5),legx=0.2,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2Mass",varNice="M_{Z2}",bins=range(10,125,5),legx=0.2,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l1Pt",varNice="z1l1Pt",bins=range(0,105,5),legx=0.7,legW=0.2,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l2Pt",varNice="z1l2Pt",bins=range(0,105,5),legx=0.7,legW=0.2,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l1Pt",varNice="z2l1Pt",bins=range(0,105,5),legx=0.7,legW=0.2,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l2Pt",varNice="z2l2Pt",bins=range(0,105,5),legx=0.7,legW=0.2,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l1pfCombIso2012",varNice="z1l1Iso",bins=np.arange(0,0.42,0.02),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l2pfCombIso2012",varNice="z1l2Iso",bins=np.arange(0,0.42,0.02),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l1pfCombIso2012",varNice="z2l1Iso",bins=np.arange(0,0.42,0.02),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
    makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l2pfCombIso2012",varNice="z2l2Iso",bins=np.arange(0,0.42,0.02),legx=0.6,legW=0.3,legy=0.7,legH=0.2,log=False)
#    tempBin=[100,120,140,160,180,200,250,300,350,400,500,600,700,800,900,1050,1200,1400,16002
#    makePlots(dir="2011",postfix="7TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legx=0.6,legW=0.3,legy=0.7,legH=0.2)
#    tempBin=[100,120,140,160,180,200,250,300,350,400,500,600,700,800,900,1000,1100,1300,1500]
#    makePlots(dir="2011",postfix="7TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legx=0.6,legW=0.3,legy=0.7,legH=0.2)
#    tempBin=[100,120,140,160,180,200,250,300,350,400,500,600,700,825,975,1150,1300,1500]
#    makePlots(dir="2011",postfix="7TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legx=0.6,legW=0.3,legy=0.7,legH=0.2)
#    tempBin=[100,120,140,160,180,200,250,300,350,400,500,600,700,800,900,1000,1100,1200,1350]
#    makePlots(dir="2011",postfix="7TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{llll} (GeV)",bins=tempBin,legx=0.6,legW=0.3,legy=0.7,legH=0.2)
#   makeScatter("DATA_12Jun_wMuEG_combed_plusFSR.root","2012",lumi)
    makeScatter("DATA_fullHcp_lite.root","2012","12.1")
    f=open("2012/yields.txt")
    print "****----"+extra+"----"
    for line in f:
        print line.rstrip("\n\r")
    f.close()
