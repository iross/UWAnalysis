#!/Library/Frameworks/EPD64.framework/Versions/Current/bin//python
from ROOT import *
from simplePlots import *
import math
import os
from optparse import OptionParser

ROOT.gROOT.ProcessLine(".X CMSStyle.C")

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

def makePlots(dir="2012",postfix="8TeV",lumi="2.95",extra="1",var="z1Mass",varNice="Z_{M}^{1}",bins=range(60,120,5),texx=63,texyf=0.3,legx=0.2):
	fd=TFile("DATA_12Jun_wMuEG_combed_plusFSR.root")
	fd=TFile("DATAfinal.root")
	d=getTrees(fd,"Cleaned")

	eventDump(d["eeee"],extra)
	eventDump(d["eemm"],extra)
	eventDump(d["mmmm"],extra)

	year=dir
	if year=="2012":
		l="8"
	else:
		l="7"

#	fzz=TFile("ZZ_8TeV.root")
#	fzz=TFile("ZZ_8TeV_wNoPU.root")
#	fzz=TFile("ggZZ_combed.root")
#	fzz=TFile("ZZ_combed_test.root")
	fzz=TFile("qqZZ_combed.root")
#	fzz=TFile("qqZZ_7TeV_combed.root")
	zz=getTrees(fzz,"Cleaned")

	fzj=TFile("BGStdIso_17May.root")
	zj=getTrees(fzj,"_noIsoSS/eventTree")
	
	fh=TFile("ggH125_combed.root")
	ht=getTrees(fh,"Cleaned")

	can = TCanvas("can","can",600,600)

	leg=TLegend(legx,0.6,legx+0.2,0.9)

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
		zzh[tree]=makeHist(t,var,"("+extra+")*(weight*"+lumi+"*1000)",50,100,600,False,True,bins)
	#	zzh[tree]=makeHist(t,var,"1*"+lumi+"*1000",50,100,600,False,True,bins)
		zzht.Add(zzh[tree])
		zzh[tree].SetFillColor(kAzure-9)
		zzh[tree].SetMarkerSize(0.001)
	zzh["4l"]=zzht
	hht=TH1F("zzh","zzh",len(bins)-1,array('d',bins))
	hh={}
	for tree in ht:
		t=ht[tree]
		hh[tree]=makeHist(t,var,"("+extra+")*(weight*"+lumi+"*1000)",50,100,600,False,True,bins)
	#	zzh[tree]=makeHist(t,var,"1*"+lumi+"*1000",50,100,600,False,True,bins)
		hht.Add(hh[tree])
		hh[tree].SetFillColor(kAzure-9)
		hh[tree].SetMarkerSize(0.001)
	hh["4l"]=hht
	zjht=TH1F("zjh","zjh",len(bins)-1,array('d',bins))
	zjh={}
	for tree in zj:
		t=zj[tree]
		zjh[tree]=makeHist(t,var,extra+"&&z1l1Pt>5&&z1l2Pt>5&&z2l1Pt>5&&z2l2Pt>5",50,100,600,False,True,bins)
		zjh[tree].SetFillColor(kGreen-5)
		zjh[tree].SetMarkerSize(0.001)
	zjh['mmmm'].Scale(0.52/zjh['mmmm'].Integral())
	zjh['eemm'].Scale(0.44/zjh['eemm'].Integral())
	zjh['eeee'].Scale(0.31/zjh['eeee'].Integral())
	for hist in zjh:
		zjht.Add(zjh[hist])
	zjh['4l']=zjht

	#colors, etc.
	zzht.SetMarkerSize(0.001)
	zzht.SetFillColor(kAzure-9)
	hht.SetMarkerSize(0.001)
	hht.SetFillColor(kWhite)
	zjht.SetMarkerSize(0.001)
	zjht.SetFillColor(kGreen-5)

	#legend
	leg.SetFillColor(kWhite)
	leg.AddEntry(dht,"Data")
	leg.AddEntry(zzht,"ZZ","f")
	leg.AddEntry(zjht,"Z+X","f")

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
		f.write("ZZ: "+str(zzh[state].Integral()*eff[state])+"\n")
		f.write("ZJets:"+str(zjh[state].Integral())+"\n")
		if not os.path.exists(dir+"/"+state):
			os.makedirs(dir+"/"+state)
		hs=THStack("hs","stack bg")
		hs.Add(zjh[state])
		hs.Add(zzh[state])
		hs.Add(hh[state])	
		print state,zzh[state].Integral()
		ymax=max(dh[state].GetMaximum(),hs.GetMaximum())
		ymax=ceil(ymax+sqrt(ymax))
		ymax=int(ymax)
		l1 = TLatex(bins[0]+2,ymax*1.01,"CMS Preliminary "+year);
		l1.SetTextSize(0.04);
		l2 = TLatex(texx,texyf*ymax,"#splitline{L_{int} ="+lumi+" fb^{-1}}{#sqrt{s} = "+l+" TeV}");
		l2.SetTextSize(0.04);
		dh[state].GetYaxis().SetRangeUser(0,ymax)
		dh[state].Draw()
		hs.Draw("hsame")
		dh[state].Draw("esame")
		leg.Draw()
		l1.Draw();
		l2.Draw();
		if bins[0]-bins[1] == bins[len(bins)-2]-bins[len(bins)-1]: # if spaced evenly
			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".png")
			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".root")
			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+""+postfix+".C")
		else:
			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_limitbinning"+postfix+".png")
			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_limitbinning"+postfix+".root")
			can.SaveAs(dir+"/"+state+"/"+state+"_"+var+"_limitbinning"+postfix+".C")
	f.close()

if __name__ == '__main__':
	parser=OptionParser(description="%prog -- dump some analysis-level plots and yields",usage="%prog --extra='extra cuts to apply'")
	parser.add_option("--extra",dest="extra",type="string",default="1")
	parser.add_option("--lumi",dest="lumi",type="string",default="5.02")
	(options,args)=parser.parse_args()
	extra=options.extra
	lumi=options.lumi

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
	makeScatter("DATAfinal.root","2011","5.02")
	f=open("2012/yields.txt")
	print "****----"+extra+"----"
	for line in f:
		print line.rstrip("\n\r")
	f.close()
