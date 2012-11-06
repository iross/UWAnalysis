'''
File: combTrees.py
Author: Ian Ross
Description: Functions for cleaning, cloning, combining TTrees.
'''

import sys
from ROOT import *
from CommonSelectors import *
from Selector import *
from simplePlots import *
import numpy as N
import logging
from progressbar import Bar, ETA, ProgressBar, ReverseBar

#list of variables to continue storing (needs variables for selection, arbitration, etc...)
#vars=["z1Mass","bestZmass","z2Mass","EVENT"]
#vars=["mass","l1Pt","l2Pt","l1Eta","l2Eta"]

def arbitrate(event1,event2, method=''):
    """Takes a pair of events, chooses which one to keep"""
    if method=='bestZmass':
        if abs(event1['z1Mass']-91.2)<abs(event2['z1Mass']-91.2):
            return event1
        elif abs(event1['z1Mass']-91.2)==abs(event2['z1Mass']-91.2):
            if (event1['z2l1Pt']+event1['z2l2Pt'] > event2['z2l1Pt']+event2['z2l2Pt']):
                return event1
            else:
                return event2
        else:
            return event2
    if method=='dummy':
        return event1
#    if method=='bestZ1':
        #return the ZZ cand with z1 closest to nominal mass (and max z2Pt if still ambiguous)
#    else if method == '':
        #return the first
    pass

def uniquify(tree, cuts, arbMode,vars,allVars=False):
    """Takes a tree as input, applies cuts, and returns a tree with only one entry per event."""
#    tree.SetBranchStatus("*",0)
#    tree.SetBranchStatus("jetsPt20",0)
#    for var in vars:
#        tree.SetBranchStatus(var,1) #don't load unnecessary branches
#    print tree
    cleanTree=tree.CopyTree(cuts)
    events={} #collection of candidates, one per event
    widgets = [Bar('>'), ' ', ETA(), ' ',str(cleanTree.GetEntries()), ' ',ReverseBar('<')]
    try:
        pbar = ProgressBar(widgets=widgets, maxval=max(0,cleanTree.GetEntries())).start()
    except ZeroDivisionError:
        print "No events passing!"
        pbar = ProgressBar(widgets=widgets, maxval=1).start()
    n=0
    if allVars:
        vars=[]
        for branch in cleanTree.GetListOfBranches():
            vars.append(branch.GetName())
    for event in cleanTree:
        eventID=str(event.EVENT/event.z1l1Phi) #divide by z1l1Phi to make sure no EVENT repetitions (relevant especially to MC)
        if eventID not in events:
            events[eventID]={}
            myDic={}
            for var in vars:
                try:
                    myDic[var]=event.GetLeaf(var).GetValue()
                except ReferenceError:
#                    print "Couldn't get variable!",var,"does not exist."
                    continue
            events[eventID]=myDic
        else:
            tempEvent={}
            for var in vars:
                try:
                    tempEvent[var]=event.GetLeaf(var).GetValue()
                except ReferenceError:
                    continue
            events[eventID]=arbitrate(events[eventID],tempEvent,method=arbMode)
        n=n+1
        pbar.update(n)
    pbar.finish()
    return events

def makeTree(events,name):
    """Takes dict of events, returns a new tree with appropriate variables"""
    n={}
    newTree=TTree(name,name)
    newTree.SetAutoSave(3000000000) #set autosave to 3 GB
    try:
        for var in events[events.keys()[0]]: #ugh.
            n[var]=N.zeros(1,dtype=float)
            newTree.Branch(var,n[var],var+'/d')
    except IndexError:
        return newTree
    for i in events:
        for var in events[i].keys():
            n[var][0]=events[i][var]
        newTree.Fill()
    return newTree

def combineTrees(file,tree1,cuts1,tree2,cuts2,vars,name="eleelemumueventtreemerged"):
    """combines two trees, removing overlap between them. returns the merged tree"""
    f=TFile(file)
    totTreeC=TChain(name)
    cleanedTree1=tree1.CopyTree(cuts1)
    cleanedTree2=tree2.CopyTree(cuts2)
    totTreeC.Add(file+"/"+tree1+cleanedTree1)
    totTreeC.Add(cleanedTree2)
    totTree=totTreeC.CloneTree() #so slow for big trees...
    cleanedTree1.Delete()
    cleanedTree2.Delete()

    try:
        totTree.SetName(name)
        totTree.Write()
    except ReferenceError:
        print "Tree empty. :("

#	totTree = TTree(name,name)
#	n={}
#	for var in vars:
#		n[var]=N.zeros(1,dtype=float)
#		totTree.Branch(var,n[var],var+'/d')
#	j=0
#	print("Adding %s to merged tree",cleanedTree1)
#    #todo: Combine the trees first, then check grab unique events IAR 10.Sep.2012
#	for i in cleanedTree1:
#			try:
#				if var.find("weight")!=-1:
#					n[var][0]=i.GetLeaf(var).GetValue() * i.GetLeaf("__CORR__").GetValue() * 1.25 #temp--reweigh sherpa samples
#				else:
#					n[var][0]=i.GetLeaf(var).GetValue()
#			except ReferenceError:
##				svar=str(var)
##				logging.error("Couldn't get %s",svar)
#				continue
#		totTree.Fill()
#		j+=1
#	tree1Events = {}
#    #check for overlap within/between the trees
#	for i in cleanedTree1:
#		tree1Events[i.EVENT/i.met] = i
#	tree2Events = {}
#	for j in cleanedTree2:
#		tree2Events[j.EVENT/j.met] = j
#	tree2_not_tree1 = set(tree2Events.keys()) - set(tree1Events.keys())
#	tree1_not_tree2 = set(tree1Events.keys()) - set(tree2Events.keys())
#	#add these events to the totTree
#	j=0
#	print "Checking ",cleanedTree2.GetEntries(),"for overlap in",cleanedTree2
#	print len(tree2_not_tree1),"in 2, not in 1"
#	print len(tree1_not_tree2),"in 1, not in 2"
#	print len(set(tree1Events.keys()).intersection(set(tree2Events.keys()))),"overlap"
#	for i in cleanedTree2:
#		#loop and make sure it's not used in mmee
#		repeat=True
#		if i.EVENT/i.met in tree2_not_tree1:
#			repeat=False
#		if (repeat==False):
#			for var in vars:
#				try:
#					if var.find("weight")!=-1:
#						n[var][0]=i.GetLeaf(var).GetValue() * i.GetLeaf("__CORR__").GetValue() * 1.25
#					else:
#						n[var][0]=i.GetLeaf(var).GetValue()
#				except ReferenceError:
#					svar=str(var)
#					logging.error("Couldn't get %s",svar)
#					continue
#			totTree.Fill()
#		j+=1
#	print cleanedTree1.GetEntries(),cleanedTree2.GetEntries(),totTree.GetEntries()
#	passing["eleEleMuMuTot"]=totTree.GetEntries()
    return totTree

def filterTree(tree1,cuts1,tree2,cuts2,vars,name="eleEleMuMuEventTreeMerged"):
    print cuts1
    print cuts2
    cleanedTree1=tree1.CopyTree(cuts1)
    cleanedTree2=tree2.CopyTree(cuts2)
    totTree = TTree(name,name)
    n={}
    for var in vars:
        n[var]=N.zeros(1,dtype=float)
        totTree.Branch(var,n[var],var+'/d')
    j=0
    tree1Events = {}
    for i in cleanedTree1:
        tree1Events[i.EVENT] = i
    tree2Events = {}
    for j in cleanedTree2:
        tree2Events[j.EVENT] = j
    tree1_not_tree2 = set(tree1Events.keys()) - set(tree2Events.keys())
    #add these events to the totTree
    j=0
    print "Checking ",cleanedTree2.GetEntries(),"for overlap in",cleanedTree2
    print len(tree1_not_tree2),"in 1, not in 2"
    print len(set(tree1Events.keys()).intersection(set(tree2Events.keys()))),"overlap"
    for i in cleanedTree1:
        #		#loop and make sure it's not used in mmee
        repeat=True
        if i.EVENT in tree1_not_tree2:
            repeat=False
        if (repeat==False):
            for var in vars:
                try:
                    if var.find("weight")!=-1:
                        n[var][0]=i.GetLeaf(var).GetValue() * i.GetLeaf("__CORR__").GetValue() * 1.25
                    else:
                        n[var][0]=i.GetLeaf(var).GetValue()
                except ReferenceError:
                    svar=str(var)
                    logging.error("Couldn't get %s",svar)
                    continue
            totTree.Fill()
        j+=1
    print len(tree1_not_tree2),"events cleaned out of",cleanedTree1.GetEntries(),totTree.GetEntries(),"total"
    return totTree

def makeHists(t, MC=False):
    """Makes the selected trees into histograms"""
    cut="1"
    if MC:
        cut="1*(weight*5000)"
    for var in ["z1Pt","z1Mass","z2Mass","mass"]:
        if var.find("Pt") !=-1:
            hist=makeHist(t,var,cut,100,0,1000)
        if var.find("Mass") !=-1:
            hist=makeHist(t,var,cut,12,60,120)
        if var.find("mass") !=-1:
            hist=makeHist(t,var,cut,75,0,1500)
        hist.SetName(t.GetName().split("EventTree")[0]+var)
        hist.SetTitle(var)
        hist.Write()

def getCuts(tree):
    """Return cutstring for given tree name."""
    #2l2t
    if tree.find("eleEleTauTau") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1ee.cuts(),z1RelPFIso.cuts(),z2tt.cuts())
    if tree.find("muMuTauTau") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1mm.cuts(),z1RelPFIso.cuts(),z2tt.cuts())
    if tree.find("eleEleEleTau") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1ee.cuts(),z1RelPFIso.cuts(),z2et.cuts(),"EVENT!=344708580")
    if tree.find("muMuEleTau") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1mm.cuts(),z1RelPFIso.cuts(),z2et.cuts(),"EVENT!=286336207")
    if tree.find("eleEleMuTau") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1ee.cuts(),z1RelPFIso.cuts(),z2mt.cuts())
    if tree.find("muMuMuTau") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1mm.cuts(),z1RelPFIso.cuts(),z2mt.cuts())
    if tree.find("eleEleEleMu") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1ee.cuts(),z1RelPFIso.cuts(),z2RelPFIso.cuts(),z2em.cuts())
    if tree.find("muMuEleMu") != -1:
        cuts=defineCuts(common.cuts(),dZ.cuts(),z1mm.cuts(),z1RelPFIso.cuts(),z2RelPFIso.cuts(),z2em.cuts())
    #4l
    if tree.find("eleEleEleEle") != -1:
        cuts=defineCuts(common.cuts(),z1sip.cuts(),z2sip.cuts(),z1ee.cuts(),z1StdIsoee.cuts(),z2StdIsoee.cuts(),z2ee.cuts())
    if tree.find("muMuMuMu") != -1:
        cuts=defineCuts(common.cuts(),z1sip.cuts(),z2sip.cuts(),z1mm.cuts(),z1StdIsomm.cuts(),z2StdIsomm.cuts(),z2mm.cuts())
    if tree.find("muMuEleEle") != -1:
        cuts=defineCuts(common.cuts(),z1sip.cuts(),z2sip.cuts(),z1mm.cuts(),z1StdIsomm.cuts(),z2StdIsoee.cuts(),z2ee.cuts())
    if tree.find("eleEleMuMu") != -1:
        cuts=defineCuts(common.cuts(),z1sip.cuts(),z2sip.cuts(),z1ee.cuts(),z1StdIsoee.cuts(),z2StdIsomm.cuts(),z2mm.cuts())
    return cuts

if __name__ == '__main__':
    logging.info("Making %s from trees in %s",sys.argv[2],sys.argv[1])
    try:
        isMC=sys.argv[3]
    except IndexError:
        isMC=False
    logging.info("Using MC? %s",isMC)
    fin = TFile(sys.argv[1])
    fout = TFile(sys.argv[2],"RECREATE")
    # loop over trees and apply relevent selections
    passing={}
#	for tree in ['eleEleTauTauEventTreeFinal', 'eleEleEleTauEventTreeFinal', 'eleEleMuTauEventTreeFinal', 'eleEleEleMuEventTreeFinal', 'eleEleEleEleEventTreeFinal', 'muMuTauTauEventTreeFinal', 'muMuEleTauEventTreeFinal', 'muMuMuTauEventTreeFinal', 'muMuEleMuEventTreeFinal', 'muMuMuMuEventTreeFinal']:
    h=[]
#	for tree in ['eleEleEleEleEventTreeFinal', 'muMuMuMuEventTreeFinal']:
#	for tree in ['dummy']:
    for tree in fin.GetListOfKeys():
        tree = tree.GetName()
        if tree.find("EventTreeFinal") == -1:
            continue
        t = fin.Get(tree+"/eventTree")
        cuts="0"
        cuts=getCuts(tree)
        logging.info("%s: %s",tree,cuts)
        try:
            temp = t.CopyTree(cuts)
        except AttributeError:
            logging.error("I didn't get the %s tree properly :(",tree)
            break
        temp.SetName(t.GetDirectory().GetName().split("EventTree")[0])
#		makeHists(temp,isMC)
        temp.SetBranchStatus("*",0)
        for var in vars:
            temp.SetBranchStatus(var,1)
        temp.SetName(tree.split('2')[0])
        y=temp.CloneTree()
        if tree.find("Final")!=-1:
            passing[tree.split('Event')[0]]=y.GetEntries()
        y.Write()
    #do the mmee state
    eemmTree=fin.Get("eleEleMuMuEventTreeFinal/eventTree")
    mmeeTree=fin.Get("muMuEleEleEventTreeFinal/eventTree")
    eeeeTree=fin.Get("eleEleEleEleEventTreeFinal/eventTree")
    mmmmTree=fin.Get("muMuMuMuEventTreeFinal/eventTree")
    eeetTree=fin.Get("eleEleEleTauEventTreeFinal/eventTree")
    eettTree=fin.Get("eleEleTauTauEventTreeFinal/eventTree")
    mmetTree=fin.Get("muMuEleTauEventTreeFinal/eventTree")
    mmttTree=fin.Get("muMuTauTauEventTreeFinal/eventTree")
    eemtTree=fin.Get("eleEleMuTauEventTreeFinal/eventTree")
    mmmtTree=fin.Get("muMuMuTauEventTreeFinal/eventTree")
    eeemTree=fin.Get("eleEleEleMuEventTreeFinal/eventTree")
    mmemTree=fin.Get("muMuEleMuEventTreeFinal/eventTree")
    #merge mmee and eemm tree
    eemmtotTree=combineTrees(mmeeTree,getCuts("muMuEleEle")+"&&z2Mass>60&&z2Mass<120",eemmTree,getCuts("eleEleMuMu")+"&&z2Mass>60&&z2Mass<120",vars,name="eleEleMuMuEventTreeMerged")
    eeeetotTree=combineTrees(eeeeTree,getCuts("eleEleEleEle")+"&&z2Mass>60&&z2Mass<120",eeeeTree,getCuts("eleEleEleEle")+"&&z2Mass>60&&z2Mass<120",vars,name="eleEleEleEleEventTreeMerged")
    mmmmtotTree=combineTrees(mmmmTree,getCuts("muMuMuMu")+"&&z2Mass>60&&z2Mass<120",mmmmTree,getCuts("muMuMuMu")+"&&z2Mass>60&&z2Mass<120",vars,name="muMuMuMuEventTreeMerged")
    #filter 4L events from 2L2T trees
    eeetfilTree=filterTree(eeetTree,getCuts("eleEleEleTau"),eeeeTree,getCuts("eleEleEleEle"),vars,name="eleEleEleTauEventTreeCleaned")
    mmetfilTree=filterTree(mmetTree,getCuts("muMuEleTau"),mmeeTree,getCuts("muMuEleEle"),vars,name="muMuEleTauEventTreeCleaned")
    eettfilTree=filterTree(eettTree,getCuts("eleEleTauTau"),eeetTree,getCuts("eleEleEleTau"),vars,name="eleEleTauTauEventTreeCleaned")
    mmttfilTree=filterTree(mmttTree,getCuts("muMuTauTau"),mmetTree,getCuts("muMuEleTau"),vars,name="muMuTauTauEventTreeCleaned")
    eemtfilTree=filterTree(eemtTree,getCuts("eleEleMuTau"),eemmTree,getCuts("eleEleMuMu"),vars,name="eleEleMuTauEventTreeCleaned")
    mmmtfilTree=filterTree(mmmtTree,getCuts("muMuMuTau"),mmmmTree,getCuts("muMuMuMu"),vars,name="muMuMuTauEventTreeCleaned")
    eeemfilTree=filterTree(eeemTree,getCuts("eleEleEleMu"),mmeeTree,getCuts("muMuEleEle"),vars,name="eleEleEleMuEventTreeCleaned")
    mmemfilTree=filterTree(mmemTree,getCuts("muMuEleMu"),mmeeTree,getCuts("muMuEleEle"),vars,name="muMuEleMuEventTreeCleaned")

    eemmtotTree.Write()
    eeeetotTree.Write()
    mmmmtotTree.Write()
    eeetfilTree.Write()
    mmetfilTree.Write()
    eettfilTree.Write()
    mmttfilTree.Write()
    eemtfilTree.Write()
    mmmtfilTree.Write()
    eeemfilTree.Write()
    mmemfilTree.Write()

    logging.info("Closing files")
    fin.Close()
    fout.Close()
    logging.info("Files closed")
