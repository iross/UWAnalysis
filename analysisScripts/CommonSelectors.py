'''
File: CommonSelectors.py
Author: Ian Ross
Description: Defines the selector objects and supporting functions.
'''

from Selector import *

def stdIso(leg, cut, lep, wcut=True):
	temp=""
	if (lep=="ele"):
		temp="(max("+leg+"StdIsoEcaldR03-rho*(0.101*(abs("+leg+"Eta)<1.479)+0.046*(abs("+leg+"Eta)>1.479))";
		temp+="+"+leg+"StdIsoHcaldR03-rho*(0.021*(abs("+leg+"Eta)<1.479)+0.040*(abs("+leg+"Eta)>1.479))";
		temp+="+"+leg+"StdIsoTk,0.0)/"+leg+"Pt";
	elif (lep=="mu"):
		temp="(max("+leg+"StdIsoEcaldR03-rho*(0.074*(abs("+leg+"Eta)<1.479)+0.022*(abs("+leg+"Eta)>1.479))";
		temp+="+"+leg+"StdIsoHcaldR03-rho*(0.022*(abs("+leg+"Eta)<1.479)+0.030*(abs("+leg+"Eta)>1.479))";
		temp+="+"+leg+"StdIsoTk,0.0)/"+leg+"Pt";
	else:
		print "Bad lepton choice! Try harder!"
		return "0"
	if not wcut:
		return temp+")"
	else:
		temp+="<"+str(cut)+")";
		return temp;
		

common = Selector([
	"HLT_Any",
	"z1Charge==0",
	"z1Mass>60",
	"z1Mass<120",
	])

z1ee = Selector([
	"z1l1Pt>20",
	"z1l2Pt>10",
	"(z1l1CiCTight&1)==1",
	"(z1l2CiCTight&1)==1",
	"z1l1MissHits<2",
	"z1l2MissHits<2"
	])

z1mm = Selector([
	"z1l1Pt>20",
	"z1l2Pt>10",
	"z1l1ValidHits>10",
	"z1l2ValidHits>10"
	])

z2ee = Selector([
#	"z2Mass>60",
#	"z2Mass<120",
	"z2l1Pt>7",
	"z2l2Pt>7",
	"(z2l1CiCTight&1)==1",
	"(z2l2CiCTight&1)==1",
	"z2l1MissHits<2",
	"z2l2MissHits<2",
	"z2Charge==0"
	])

z2mm = Selector([
#	"z2Mass>60",
#	"z2Mass<120",
	"z2l1Pt>5",
	"z2l2Pt>5",
	"z2l1ValidHits>10",
	"z2l2ValidHits>10",
	"z2Charge==0"
	])

z2tt = Selector([
	"z2l1Pt>20",
	"z2l2Pt>20",
	"z2l1EleVeto",
	"z2l2EleVeto",
	"z2l1MuVeto",
	"z2l2MuVeto",
	"z2l1MediumIsoCombDB",
	"z2l2MediumIsoCombDB",
	"z2Mass>30",
	"z2Mass<80"
	])

z2et = Selector([
	"z2l1Pt>10",
	"z2l2Pt>20",
	"(z2l1CiCTight&1)==1",
	"z2l1RelPFIsoDB<0.10",
	"z2l1MissHits==0",
	"z2l2EleVeto",
	"z2l2MuVeto",
	"z2Mass>30",
	"z2Mass<80"
	])

z2mt = Selector([
	"z2l1Pt>10",
	"z2l2Pt>20",
	"z2l2EleVeto",
	"z2l2MuVetoTight",
	"z2l1ValidHits>10",
	"z2l1RelPFIsoDB<0.15",
	"z2Mass>30",
	"z2Mass<80"
	])

z2em = Selector([
	"z2l1Pt>10",
	"z2l2Pt>10",
	"z2l1RelPFIsoDB<0.25",
	"(z2l1CiCTight&1)==1",
	"z2l1MissHits<2",
	"z2Charge==0",
	"z2Mass<90"
])

z1RelPFIso = Selector([
	"z1l1RelPFIsoDB<0.25",
	"z1l2RelPFIsoDB<0.25"
	])

z2RelPFIso = Selector([
	"z2l1RelPFIsoDB<0.25",
	"z2l2RelPFIsoDB<0.25"
	])

z1StdIsoee = Selector([
	stdIso("z1l1",0.275,"ele",True),
	stdIso("z1l2",0.275,"ele",True)
	])

z1StdIsomm = Selector([
	stdIso("z1l1",0.275,"mu",True),
	stdIso("z1l2",0.275,"mu",True)
	])

z2RelPFIso = Selector([
	"z2l1RelPFIsoDB<0.25",
	"z2l2RelPFIsoDB<0.25"
	])

z2StdIsoee = Selector([
	stdIso("z2l1",0.275,"ele",True),
	stdIso("z2l2",0.275,"ele",True)
	])

z2StdIsomm = Selector([
	stdIso("z2l1",0.275,"mu",True),
	stdIso("z2l2",0.275,"mu",True)
	])

eleDen = Selector([
	"z2l1Pt>7",
	"z2l1SIP<4",
#	"z2l1MissHits<2",
	"met<25"
	])

eleNum = Selector([
	"met<25",
	"z2l1Pt>7",
	"z2l1SIP<4",
	"z2l1MissHits<2",
	"(z2l1CiCTight&1)==1",
	stdIso("z2l1",0.275,"ele",True),
	])
	
muDen = Selector([
	"met<25",
	"abs(z2l1Eta)<2.5",
	"z2l1Pt>5",
	"z2l1SIP<4",
	])
muNum = Selector([
	"met<25",
	"abs(z2l1Eta)<2.5",
	"z2l1Pt>5",
	"z2l1SIP<4",
	"z2l1ValidHits>10",
	stdIso("z2l1",0.275,"mu",True),
	])

mmFakeable = Selector([
	"z2Mass>12",
	"z2Mass<120",
	"z2l1Pt>5",
	"z2l2Pt>5",
	"z2l1SIP<4",
	"z2l2SIP<4",
	"z2l1ValidHits>10",
	"z2l2ValidHits>10",
	])

eeFakeable = Selector([
	"z2Mass>12",
	"z2Mass<120",
	"z2l1Pt>7",
	"z2l2Pt>7",
	"z2l1SIP<4",
	"z2l2SIP<4",
	"z2l1MissHits<2",
	"z2l2MissHits<2",
#	"(z2l1CiCTight&1)==1",
#	"(z2l2CiCTight&1)==1",
	])

z1sip = Selector([
	"z1l1SIP<4",
	"z1l2SIP<4"
	])

z2sip = Selector([
	"z2l1SIP<4",
	"z2l2SIP<4"
	])

dZ = Selector([
	"dZ12<0.10",
	"dZ13<0.10",
	"dZ14<0.10"
	])
