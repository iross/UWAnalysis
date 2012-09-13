from combTrees import *
from ROOT import *

#vars to store
vars4l = ["mass","z1Mass","z2Mass","z1l1Pt","z1l2Pt","z2l1Pt","z2l2Pt","bestZmass","subBestZmass","z2l1mvaNonTrigPass","z2l2mvaNonTrigPass"]

#set selections
cuts={}

cuts["eeee"]=defineCuts(pt20_10.cuts(),z2ee.cuts(),z2RelPFIso.cuts(),"fourFour&&mass>100&&z2Mass>12&&z2Mass<120&&z1Mass>40&&z1Mass<120")
cuts["mmmm"]=defineCuts(pt20_10.cuts(),z2mm.cuts(),z2RelPFIso.cuts(),"fourFour&&mass>100&&z2Mass>12&&z2Mass<120&&z1Mass>40&&z1Mass<120")
cuts["mmee"]=defineCuts(pt20_10.cuts(),z2ee.cuts(),z2RelPFIso.cuts(),"fourFour&&mass>100&&((z1Mass>40&&z1Mass<120&&z2Mass>12||z2Mass<120)||(z2Mass>40&&z2Mass<120&&z1Mass>12&&z1Mass<120))") #...this tree should have full selection applied right now

f=TFile("DATA_2012C_2.root","update")
t=f.Get("eleEleEleEleEventTree/eventTree")

#uniquify
print cuts["eeee"]
eeeeEvents=uniquify(t,cuts["eeee"],"dummy",vars4l)

#make tree
eeeeTree=makeTree(eeeeEvents,"eeeeFinal",vars4l)


t=f.Get("muMuMuMuEventTree/eventTree")
mmmmEvents=uniquify(t,cuts["mmmm"],"dummy",vars4l)
mmmmTree=makeTree(mmmmEvents,"mmmmFinal",vars4l)

t=f.Get("muMuEleEleEventTree/eventTree")
mmeeEvents=uniquify(t,cuts["mmee"],"dummy",vars4l)
mmeeTree=makeTree(mmeeEvents,"mmeeFinal",vars4l)

#write trees
eeeeTree.Write()
mmmmTree.Write()
mmeeTree.Write()

import pickle
fout=open('myEvents.pck','w')
finalEvents={}
finalEvents['eeee']=eeeeEvents
finalEvents['mmmm']=mmmmEvents
finalEvents['mmee']=mmeeEvents
pickle.dump(finalEvents,fout)
f.Close()
fout.close()
