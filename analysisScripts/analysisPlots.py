
from ROOT import *
from simplePlots import *
import math
import os
from optparse import OptionParser

ROOT.gROOT.ProcessLine(".X CMSStyle.C")
ROOT.gROOT.SetBatch(True)

def getTrees(file,postfix):
	arr={}
	arr['eeee']=file.Get("eleEleEleEleEventTree"+postfix)
	arr['eemm']=file.Get("eleEleMuMuEventTree"+postfix)
	arr['mmmm']=file.Get("muMuMuMuEventTree"+postfix)
	#hack: if data, use FSR tree
	if "DATA" in file.GetName():
		arr['eemm']=file.Get("eleEleMuMuEventTreeFinalFSR")
	return arr

def eventDump(tree,extra):
	"""Dump some info about the contents of the passed tree"""
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
#	d["eeee"]=fd.Get("eleEleEleEleEventTreeCleaned")
#	d["mmmm"]=fd.Get("muMuMuMuEventTreeCleaned")
	#use llll and eemm trees with FSR event
#	d["eemm"]=fd.Get("eleEleMuMuEventTreeFinalFSR")
	#these are 2011
	d["eeee"]=fd.Get("eleEleEleEleEventTreeMerged")
	d["eemm"]=fd.Get("eleEleMuMuEventTreeMerged")
	d["mmmm"]=fd.Get("muMuMuMuEventTreeMerged")
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
			d[state].Scan(varx+":"+vary)
			h2=makeHist2D(d[state],"1",varx,nbins,min,max,vary,nbins,30,90)
		else:
			d[state].Scan(varx+":"+vary)
			h2=makeHist2D(d[state],"1",varx,nbins,min,max,vary,nbins,min,max)
		h2.GetXaxis().SetTitle(varxNice)
		h2.GetYaxis().SetTitle(varyNice)
		h2.Draw()
		ymax=120
		l1 = TLatex(texx,ymax*1.01,"CMS Preliminary "+year);
		l1.SetTextSize(0.04);
		if year=="2012":
			l="8"
		else:
			l="7"
		l2 = TLatex(texx,ymax*0.95,"L_{int} = "+lumi+" fb^{-1}, #sqrt{s} = "+l+" TeV");
		l2.SetTextSize(0.04);
		l1.Draw()
		l2.Draw()

		can.SaveAs(year+"/"+state+"/"+state+"_z1Mass_z2Mass.png")
		can.SaveAs(year+"/"+state+"/"+state+"_z1Mass_z2Mass.root")
		can.SaveAs(year+"/"+state+"/"+state+"_z1Mass_z2Mass.C")

def makePlots(datasets,trees,dir="2012",postfix="8TeV",lumi="2.95",extra="1",var="z1Mass",varNice="Z_{M}^{1}",bins=range(60,120,5),texx=63,texyf=0.3,legx=0.2):
    #	eventDump(d["eeee"],extra)
#	eventDump(d["eemm"],extra)
#	eventDump(d["mmmm"],extra)


    year=dir
    if year=="2012":
        l="8"
    else:
        l="7"

    data={}
    hists={}
    files={}
    for dataset in datasets:
        data[dataset]={}
        hists[dataset]={}
        files[dataset]=TFile(datasets[dataset]['file'])        
        for tree in trees:
            data[dataset][tree]=files[dataset].Get(trees[tree])
            if datasets[dataset]['isMC']:
                hists[dataset][tree]=makeHist(files[dataset].Get(trees[tree]),var,"("+extra+")*(__WEIGHT__noPU*"+lumi+"*1000)",50,100,600,False,True,bins)
            else:
                hists[dataset][tree]=makeHist(files[dataset].Get(trees[tree]),var,extra,50,100,600,False,True,bins)
                hists[dataset][tree].GetXaxis().SetTitle(varNice)
                if bins[0]-bins[1] == bins[len(bins)-2]-bins[len(bins)-1]: # if spaced evenly
                    div=(float(bins[len(bins)-1])-float(bins[0]))/(len(bins)-1)
                    hists[dataset][tree].GetYaxis().SetTitle("Events / %.0f GeV" %div)
                else:
                    hists[dataset][tree].GetYaxis().SetTitle("Events")
            print dataset,'---',hists[dataset][tree].Integral()
            hists[dataset][tree].SetFillColor(datasets[dataset]['color'])

    #stack/style hists

#    plot(hists) #if data, do on top. Stack others. etc.
    #legend

    can = TCanvas("can","can",600,600)
    for tree in trees:
        leg=TLegend(legx,0.6,legx+0.2,0.9)
        leg.SetFillColor(kWhite)
        if not os.path.exists(dir+"/"+tree):
            os.makedirs(dir+"/"+tree)
        hs=THStack("hs","stack")
        for dataset in datasets:
            if not datasets[dataset]['isMC']:
                leg.AddEntry(hists[dataset][tree],"Data","p")
            else:
                hs.Add(hists[dataset][tree])
                leg.AddEntry(hists[dataset][tree],dataset,"f")
        print datasets
        ymax=max(hists['DATA'][tree].GetMaximum(),hs.GetMaximum())
        ymax=ceil(ymax+sqrt(ymax))
        ymax=int(ymax)
        l1 = TLatex(bins[0]+2,ymax*1.01,"CMS Preliminary "+year);
        l1.SetTextSize(0.04);
        l2 = TLatex(texx,texyf*ymax,"#splitline{L_{int} ="+lumi+" fb^{-1}}{#sqrt{s} = "+l+" TeV}");
        l2.SetTextSize(0.04);
        hists['DATA'][tree].GetYaxis().SetRangeUser(0,ymax)
        hists['DATA'][tree].Draw('e1')
        hs.Draw('hsame')
        hists['DATA'][tree].Draw('e1,same')
        leg.Draw()
        l1.Draw()
        l2.Draw()
#        can.SetLogy(1)
        if bins[0]-bins[1] == bins[len(bins)-2]-bins[len(bins)-1]: # if spaced evenly
            can.SaveAs(dir+"/"+tree+"/"+tree+"_"+var+""+postfix+".png")
            can.SaveAs(dir+"/"+tree+"/"+tree+"_"+var+""+postfix+".root")
            can.SaveAs(dir+"/"+tree+"/"+tree+"_"+var+""+postfix+".C")
        else:
            can.SaveAs(dir+"/"+tree+"/"+tree+"_"+var+"_limitbinning"+postfix+".png")
            can.SaveAs(dir+"/"+tree+"/"+tree+"_"+var+"_limitbinning"+postfix+".root")
            can.SaveAs(dir+"/"+tree+"/"+tree+"_"+var+"_limitbinning"+postfix+".C")

#	#HACK! efficiencies taken as average of Matt's TP corrected yields/uncorrected
#	eff={}
#	eff["eeee"]=0.979
#	eff["eemm"]=0.9885
#	eff["mmmm"]=0.9876
#	eff["4l"]=(eff["eeee"]+eff["mmmm"]+2.0*eff["eemm"])/4.0
#	f=open(dir+"/yields.txt","w")
#	for state in dh:
#		f.write("---"+state+"---\n")
#		f.write("Data: "+str(dh[state].Integral())+"\n")
#		f.write("ZZ: "+str(zzh[state].Integral()*eff[state])+"\n")
#		f.write("ZJets:"+str(zjh[state].Integral())+"\n")
#		if not os.path.exists(dir+"/"+state):
#			os.makedirs(dir+"/"+state)
#		hs=THStack("hs","stack bg")
#		hs.Add(zjh[state])
#		hs.Add(zzh[state])
#		hs.Add(hh[state])	
#		print state,zzh[state].Integral()
#		ymax=max(dh[state].GetMaximum(),hs.GetMaximum())
#		ymax=ceil(ymax+sqrt(ymax))
#		ymax=int(ymax)
#		l1 = TLatex(bins[0]+2,ymax*1.01,"CMS Preliminary "+year);
#		l1.SetTextSize(0.04);
#		l2 = TLatex(texx,texyf*ymax,"#splitline{L_{int} ="+lumi+" fb^{-1}}{#sqrt{s} = "+l+" TeV}");
#		l2.SetTextSize(0.04);
#		dh[state].GetYaxis().SetRangeUser(0,ymax)
#		dh[state].Draw()
#		hs.Draw("hsame")
#		dh[state].Draw("esame")
#		leg.Draw()
#		l1.Draw();
#		l2.Draw();
#		if bins[0]-bins[1] == bins[len(bins)-2]-bins[len(bins)-1]: # if spaced evenly
#			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".png")
#			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".root")
#			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".C")
#		else:
#			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_limitbinning"+postfix+".png")
#			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_limitbinning"+postfix+".root")
#			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_limitbinning"+postfix+".C")
#	f.close()

def addDataset(file,color,isMC):
    temp={}
    temp["file"]=file
    temp["color"]=color
    temp["isMC"]=isMC
    return temp

if __name__ == '__main__':
    parser=OptionParser(description="%prog -- dump some analysis-level plots and yields",usage="%prog --extra='extra cuts to apply'")
    parser.add_option("--extra",dest="extra",type="string",default="1")
    parser.add_option("--lumi",dest="lumi",type="string",default="5.02")
    (options,args)=parser.parse_args()
    extra=options.extra
    lumi=options.lumi

    #todo: define samples, nice names, colors, etc.
    datasets={}
    datasets["ZZ"]=addDataset("ZZ4M.root",kAzure-9,True)
    datasets["ZJets"]=addDataset("DYJets.root",kGreen-5,True)
    datasets["DATA"]=addDataset("DATA.root",kBlack,False)
    trees={}
    trees["mm"]="muMuEventTree/eventTree"

    makePlots(datasets,trees,dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass[0]",varNice="M_{#mu#mu}",bins=range(60,125,1),texx=400,texyf=0.4,legx=0.6)
    makePlots(datasets,trees,dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="l1Pt[0]",varNice="#mu_{1} P_{T}",bins=range(0,60,1),texx=400,texyf=0.4,legx=0.6)
    makePlots(datasets,trees,dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="l2Pt[0]",varNice="#mu_{2} P_{T}",bins=range(0,60,1),texx=400,texyf=0.4,legx=0.6)
    makePlots(datasets,trees,dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="vertices[0]",varNice="Reco. Vertices",bins=range(0,50,1),texx=400,texyf=0.4,legx=0.6)

#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{4l}",bins=range(80,610,10),texx=400,texyf=0.4,legx=0.6)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="mass",varNice="M_{4l}",bins=range(90,170,5),texx=400,texyf=0.4,legx=0.6)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1Pt",varNice="Z_{Pt}^{1}",bins=range(0,200,10),texx=131,texyf=0.4,legx=0.7)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2Pt",varNice="Z_{Pt}^{2}",bins=range(0,200,10),texx=131,texyf=0.4,legx=0.7)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l1Pt",varNice="Z_{1}l_{1} p_{T}",bins=range(0,200,10),texx=231,texyf=0.4,legx=0.7)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1l2Pt",varNice="Z_{1}l_{2} p_{T}",bins=range(0,200,10),texx=131,texyf=0.4,legx=0.7)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l1Pt",varNice="Z_{2}l_{1} p_{T}",bins=range(0,200,10),texx=131,texyf=0.4,legx=0.7)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2l2Pt",varNice="Z_{2}l_{2} p_{T}",bins=range(0,200,10),texx=131,texyf=0.4,legx=0.7)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z1Mass",varNice="Z_{M}^{1}",bins=range(60,125,5),texx=63,legx=0.2)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="z2Mass",varNice="Z_{M}^{2}",bins=range(60,125,5),texx=63,legx=0.2)
#	makePlots(dir="2012",postfix="8TeV",lumi=lumi,extra=extra,var="vertices",varNice="Reco. Vertices",bins=range(0,50,50),texx=131,texyf=0.4,legx=0.7)
#	makeScatter("DATA_12Jun_wMuEG_combed_plusFSR.root","2012",lumi)
#	makeScatter("DATAfinal.root","2011","5.02")
#	f=open("2012/yields.txt")
#	print "****----"+extra+"----"
#	for line in f:
#		print line.rstrip("\n\r")
#	f.close()
