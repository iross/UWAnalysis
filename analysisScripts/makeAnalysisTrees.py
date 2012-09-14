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
vars4l = ["mass","z1Mass","z2Mass","z1l1Pt","z1l2Pt","z2l1Pt","z2l2Pt","bestZmass","subBestZmass","RUN","LUMI","EVENT","met"]
varsZ = ["mass","l1Pt","l2Pt","l1Eta","l2Eta","l1Phi","l2Phi","RUN","LUMI","EVENT","met"]

#set selections
cuts={}

cuts["eeee"]=defineCuts(pt20_10.cuts(),z2ee.cuts(),z2RelPFIso.cuts(),"fourFour&&mass>100&&z2Mass>12&&z2Mass<120&&z1Mass>40&&z1Mass<120")
cuts["mmmm"]=defineCuts(pt20_10.cuts(),z2mm.cuts(),z2RelPFIso.cuts(),"fourFour&&mass>100&&z2Mass>12&&z2Mass<120&&z1Mass>40&&z1Mass<120")
cuts["mmee"]=defineCuts(pt20_10.cuts(),z2ee.cuts(),z2RelPFIso.cuts(),"fourFour&&mass>100&&((z1Mass>40&&z1Mass<120&&z2Mass>12||z2Mass<120)||(z2Mass>40&&z2Mass<120&&z1Mass>12&&z1Mass<120))") #...this tree should have full selection applied right now
cuts["mm"]=defineCuts("l1Pt>20&&l2Pt>10") #all cuts applied before trees filled
cuts["ee"]=defineCuts("l1Pt>20&&l2Pt>10") #all cuts applied before trees filled

cuts["eee"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eleDen.cuts())
cuts["eem"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),muDen.cuts())
cuts["mme"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),eleDen.cuts())
cuts["mmm"]=defineCuts(common.cuts(),z1mm.cuts(),z1relIso.cuts(),muDen.cuts())

#todo BG/control trees
cuts["eeeeAA"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eeAA.cuts(),"z2Charge==0")
cuts["eeeeAI"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eeAI.cuts(),"z2Charge==0")
cuts["eeeeIA"]=defineCuts(common.cuts(),z1ee.cuts(),z1relIso.cuts(),eeIA.cuts(),"z2Charge==0")

f=TFile(file,"update")
t=f.Get("eleEleEleEleEventTree/eventTree")

fout=TFile(outfile,"recreate")

#uniquify
eeeeEvents=uniquify(t,cuts["eeee"],"dummy",vars4l)
eeeeAAEvents=uniquify(t,cuts["eeeeAA"],"dummy",vars4l)
eeeeAIEvents=uniquify(t,cuts["eeeeAI"],"dummy",vars4l)
eeeeIAEvents=uniquify(t,cuts["eeeeIA"],"dummy",vars4l)
eeeeTree=makeTree(eeeeEvents,"eeeeFinal",vars4l)
eeeeAATree=makeTree(eeeeAAEvents,"eeeeAAFinal",vars4l)
eeeeAITree=makeTree(eeeeAIEvents,"eeeeAIFinal",vars4l)
eeeeIATree=makeTree(eeeeIAEvents,"eeeeIAFinal",vars4l)

t=f.Get("muMuMuMuEventTree/eventTree")
mmmmEvents=uniquify(t,cuts["mmmm"],"dummy",vars4l)
mmmmTree=makeTree(mmmmEvents,"mmmmFinal",vars4l)

t=f.Get("muMuEleEleEventTree/eventTree")
mmeeEvents=uniquify(t,cuts["mmee"],"dummy",vars4l)
mmeeTree=makeTree(mmeeEvents,"mmeeFinal",vars4l)

t=f.Get("muMuEventTree/eventTree")
mmEvents=uniquify(t,cuts["mm"],"dummy",varsZ)
mmTree=makeTree(mmEvents,"mmFinal",varsZ)
t=f.Get("eleEleEventTree/eventTree")
eeEvents=uniquify(t,cuts["ee"],"dummy",varsZ)
eeTree=makeTree(eeEvents,"eeFinal",varsZ)

t=f.Get("muMuEleEventTree/eventTree")
mmeEvents=uniquify(t,cuts["mme"],"dummy",vars4l) #use 4l vars for now
mmeTree=makeTree(mmeEvents,"mmeFinal",vars4l)

t=f.Get("muMuMuEventTree/eventTree")
mmmEvents=uniquify(t,cuts["mmm"],"dummy",vars4l) #use 4l vars for now
mmmTree=makeTree(mmmEvents,"mmmFinal",vars4l)

t=f.Get("eleEleEleEventTree/eventTree")
eeeEvents=uniquify(t,cuts["eee"],"dummy",vars4l) #use 4l vars for now
eeeTree=makeTree(eeeEvents,"eeeFinal",vars4l)

t=f.Get("eleEleMuEventTree/eventTree")
eemEvents=uniquify(t,cuts["eem"],"dummy",vars4l) #use 4l vars for now
eemTree=makeTree(eemEvents,"eemFinal",vars4l)

#write trees
eeeeTree.Write()
eeeeAATree.Write()
eeeeAITree.Write()
eeeeIATree.Write()
mmmmTree.Write()
mmeeTree.Write()
mmTree.Write()
eeTree.Write()
mmeTree.Write()
mmmTree.Write()
eeeTree.Write()
eemTree.Write()

f.Close()
fout.Close()

#dump them for quick event checks.
import pickle
pout=open('myEvents.pck','w')
finalEvents={}
finalEvents['eeee']=eeeeEvents
finalEvents['mmmm']=mmmmEvents
finalEvents['mmee']=mmeeEvents
pickle.dump(finalEvents,pout)
pout.close()
