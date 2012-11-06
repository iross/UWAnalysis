from combTrees import *
from ROOT import *
import sys
import getopt
from RecoLuminosity.LumiDB import argparse

parser = argparse.ArgumentParser(description='Make cleaned up trees (one entry per event, smaller set of vars, etc...)')
parser.add_argument('--file',type=str,required=True,default='',help='Input file')
parser.add_argument('--out',type=str,required=True,default='',help='Output file')

args = parser.parse_args()

file=args.file
outfile=args.out

if ".root" not in file:
    file=file+".root"

#vars to store
vars4l = ["mass","z1Mass","z2Mass","z1l1Pt","z1l2Pt","z2l1Pt","z2l2Pt","bestZmass","subBestZmass","RUN","LUMI","EVENT","met","z1l1pfCombIso2012","z1l2pfCombIso2012","z2l1pfCombIso2012","z2l2pfCombIso2012","__WEIGHT__","__WEIGHT__noPU","z1l1pfCombIso2012_noFSR","z1l2pfCombIso2012_noFSR","z2l1pfCombIso2012_noFSR","z2l2pfCombIso2012_noFSR","weight","weightnoPU","z1l1Eta","z1l2Eta","z2l1Eta","z2l2Eta","massNoFSR","z1l1Phi","z1l2Phi","z2l1Phi","z2l2Phi","z2Charge","z1l1pfPhotonIso","z1l1PhotonIso","z1l2pfPhotonIso","z1l2PhotonIso","z2l1pfPhotonIso","z2l1PhotonIso","z2l2pfPhotonIso","z2l2PhotonIso"]
varsZ = ["mass","l1Pt","l2Pt","l1Eta","l2Eta","l1Phi","l2Phi","RUN","LUMI","EVENT","met","l1pfCombIso2012","l2pfCombIso2012","__WEIGHT__","__WEIGHT__noPU","l1SIP","l2SIP"]

#set selections
cuts={}


#NOTE: don't apply mass cuts until AFTER best Z1 selection
cuts["eeee"]=defineCuts(pt20_10.cuts(),z2ee.cuts(),z2RelPFIso.cuts(),"fourFour")
cuts["mmmm"]=defineCuts(pt20_10.cuts(),z2mm.cuts(),z2RelPFIso.cuts(),"fourFour")
cuts["mmee"]=defineCuts(pt20_10.cuts(),z2ee.cuts(),z2RelPFIso.cuts(),"fourFour") #...this tree should have full selection applied right now
cuts["mm"]=defineCuts("l1Pt>20&&l2Pt>10") #all cuts applied before trees filled
cuts["ee"]=defineCuts("l1Pt>20&&l2Pt>10") #all cuts applied before trees filled

cuts["eee"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eleDen.cuts())
cuts["eem"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),muDen.cuts())
cuts["mme"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),eleDen.cuts())
cuts["mmm"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),muDen.cuts())

cuts["eeeeAA"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eeAA.cuts(),"z2Charge==0")
cuts["eeeeAI"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eeAI.cuts(),"z2Charge==0")
cuts["eeeeIA"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eeIA.cuts(),"z2Charge==0")

cuts["mmeeAA"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),eeAA.cuts(),"z2Charge==0")
cuts["mmeeAI"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),eeAI.cuts(),"z2Charge==0")
cuts["mmeeIA"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),eeIA.cuts(),"z2Charge==0")

cuts["eemmAA"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),mmAA.cuts(),"z2Charge==0")
cuts["eemmAI"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),mmAI.cuts(),"z2Charge==0")
cuts["eemmIA"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),mmIA.cuts(),"z2Charge==0")

cuts["mmmmAA"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),mmAA.cuts(),"z2Charge==0")
cuts["mmmmAI"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),mmAI.cuts(),"z2Charge==0")
cuts["mmmmIA"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),mmIA.cuts(),"z2Charge==0")

f=TFile(file,"update")
t=f.Get("eleEleEleEleEventTreeFinal/eventTree")

fout=TFile(outfile,"recreate")

#uniquify
eeeeEvents=uniquify(t,cuts["eeee"],"bestZmass",vars4l,True)
eeeeAAEvents=uniquify(t,cuts["eeeeAA"],"bestZmass",vars4l)
eeeeAIEvents=uniquify(t,cuts["eeeeAI"],"bestZmass",vars4l)
eeeeIAEvents=uniquify(t,cuts["eeeeIA"],"bestZmass",vars4l)
eeeeTree=makeTree(eeeeEvents,"eeeeFinal")
eeeeAATree=makeTree(eeeeAAEvents,"eeeeAAFinal")
eeeeAITree=makeTree(eeeeAIEvents,"eeeeAIFinal")
eeeeIATree=makeTree(eeeeIAEvents,"eeeeIAFinal")

t=f.Get("muMuMuMuEventTreeFinal/eventTree")
mmmmEvents=uniquify(t,cuts["mmmm"],"bestZmass",vars4l,True)
mmmmAAEvents=uniquify(t,cuts["mmmmAA"],"bestZmass",vars4l)
mmmmAIEvents=uniquify(t,cuts["mmmmAI"],"bestZmass",vars4l)
mmmmIAEvents=uniquify(t,cuts["mmmmIA"],"bestZmass",vars4l)
mmmmTree=makeTree(mmmmEvents,"mmmmFinal")
mmmmAATree=makeTree(mmmmAAEvents,"mmmmAAFinal")
mmmmAITree=makeTree(mmmmAIEvents,"mmmmAIFinal")
mmmmIATree=makeTree(mmmmIAEvents,"mmmmIAFinal")

t=f.Get("muMuEleEleEventTreeFinal/eventTree")
mmeeEvents=uniquify(t,cuts["mmee"],"bestZmass",vars4l)
mmeeTree=makeTree(mmeeEvents,"mmeeFinal")

#mmee and eemm come from "ONLY" branch
t=f.Get("muMuEleEleonlyEventTreeFinal/eventTree")
print "mmee"
mmeeAAEvents=uniquify(t,cuts["mmeeAA"],"bestZmass",vars4l)
mmeeAIEvents=uniquify(t,cuts["mmeeAI"],"bestZmass",vars4l)
mmeeIAEvents=uniquify(t,cuts["mmeeIA"],"bestZmass",vars4l)
mmeeAATree=makeTree(mmeeAAEvents,"mmeeAAFinal")
mmeeAITree=makeTree(mmeeAIEvents,"mmeeAIFinal")
mmeeIATree=makeTree(mmeeIAEvents,"mmeeIAFinal")

print "eemm"
t=f.Get("eleEleMuMuEventTreeFinal/eventTree")
eemmAAEvents=uniquify(t,cuts["eemmAA"],"bestZmass",vars4l)
eemmAIEvents=uniquify(t,cuts["eemmAI"],"bestZmass",vars4l)
eemmIAEvents=uniquify(t,cuts["eemmIA"],"bestZmass",vars4l)
eemmAATree=makeTree(eemmAAEvents,"eemmAAFinal")
eemmAITree=makeTree(eemmAIEvents,"eemmAIFinal")
eemmIATree=makeTree(eemmIAEvents,"eemmIAFinal")

#temp.. don't do these because they take so damn long
#t=f.Get("muMuEventTree/eventTree")
#mmEvents=uniquify(t,cuts["mm"],"dummy",varsZ)
#mmTree=makeTree(mmEvents,"mmFinal",varsZ)
#t=f.Get("eleEleEventTree/eventTree")
#eeEvents=uniquify(t,cuts["ee"],"dummy",varsZ)
#eeTree=makeTree(eeEvents,"eeFinal",varsZ)

t=f.Get("muMuEleEventTree/eventTree")
mmeEvents=uniquify(t,cuts["mme"],"dummy",vars4l) #use 4l vars for now
mmeTree=makeTree(mmeEvents,"mmeFinal")

t=f.Get("muMuMuEventTree/eventTree")
mmmEvents=uniquify(t,cuts["mmm"],"dummy",vars4l) #use 4l vars for now
mmmTree=makeTree(mmmEvents,"mmmFinal")

t=f.Get("eleEleEleEventTree/eventTree")
eeeEvents=uniquify(t,cuts["eee"],"dummy",vars4l) #use 4l vars for now
eeeTree=makeTree(eeeEvents,"eeeFinal")

t=f.Get("eleEleMuEventTree/eventTree")
eemEvents=uniquify(t,cuts["eem"],"dummy",vars4l) #use 4l vars for now
eemTree=makeTree(eemEvents,"eemFinal")

#write trees
eeeeTree.Write()
eeeeAATree.Write()
eeeeAITree.Write()
eeeeIATree.Write()
mmmmTree.Write()
mmmmAATree.Write()
mmmmAITree.Write()
mmmmIATree.Write()
mmeeTree.Write()
mmeeAATree.Write()
mmeeAATree.Write()
mmeeAITree.Write()
eemmIATree.Write()
eemmAITree.Write()
eemmIATree.Write()

#mmTree.Write()
#eeTree.Write()
mmeTree.Write()
mmmTree.Write()
eeeTree.Write()
eemTree.Write()

f.Close()
fout.Close()

#make total 4l tree
fout2=TFile(outfile,"UPDATE")
llllTree=TChain("llllTree")
llllTree.Add(outfile+"/eeeeFinal")
llllTree.Add(outfile+"/mmeeFinal")
llllTree.Add(outfile+"/mmmmFinal")
print llllTree.GetEntries()
llllTreeFinal=llllTree.CloneTree()
llllTreeFinal.SetName("llllTree")
llllTreeFinal.Write()
fout2.Close()

#dump them for quick event checks.
import pickle
pout=open('myEvents.pck','w')
finalEvents={}
finalEvents['eeee']=eeeeEvents
finalEvents['mmmm']=mmmmEvents
finalEvents['mmee']=mmeeEvents
pickle.dump(finalEvents,pout)
pout.close()


