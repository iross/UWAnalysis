"""
Runs on UWAnalysis n-tuples to produce a synchronization table

Author: D. Austin Belknap
"""

import ROOT as rt
import sys


input_file = rt.TFile(sys.argv[1])

mmmm_tree = input_file.Get("muMuMuMuEventTreeFinal/eventTree")
mmee_tree = input_file.Get("muMuEleEleEventTreeFinal/eventTree")
eeee_tree = input_file.Get("eleEleEleEleEventTreeFinal/eventTree")

#selections = "mass > 70 && subBestZmass > 12 && mass > 100 && VBFjets == 2 && VBFjets_fisher > 0.4"
#selections = "mass > 70 && subBestZmass > 12 && mass > 100 && kd > 0.1"
#selections = "mass > 100 && subBestZmass > 12 && VBFjets == 2"
#selections = "mass > 100 && VBFjets >= 1"

#selections = "mass > 70 && subBestZmass > 12"
#selections = "mass > 100 && subBestZmass > 12 && VBFjets >= 1"
#selections = "mass > 100 && subBestZmass > 12 && VBFjets == 2"
selections = "mass > 100 && subBestZmass > 12 && VBFjets == 2 && VBFjets_fisher > 0.4"

events1 = set()
events2 = set()

#selections = "subBestZmass > 12 && mass > 100 && VBFjets == 2"

mmmm_sel1 = mmmm_tree.CopyTree( selections )
mmee_sel1 = mmee_tree.CopyTree( selections )
eeee_sel1 = eeee_tree.CopyTree( selections )

for evt in mmmm_sel1:
    events1.add( evt.EVENT )

for evt in mmee_sel1:
    events1.add( evt.EVENT )

for evt in eeee_sel1:
    events1.add( evt.EVENT )

#selections = "subBestZmass > 12 && mass > 100 && VBFjets == 2 && VBFjets_fisher > 0.4"
#selections = "subBestZmass > 12 && mass > 100 && VBFjets == 2"

mmmm_sel2 = mmmm_tree.CopyTree( selections )
mmee_sel2 = mmee_tree.CopyTree( selections )
eeee_sel2 = eeee_tree.CopyTree( selections )

for evt in mmmm_sel2:
    events2.add( evt.EVENT )

for evt in mmee_sel2:
    events2.add( evt.EVENT )

for evt in eeee_sel2:
    events2.add( evt.EVENT )

missing_events = events1 - events2

if len(missing_events) != 0:
    print '{0:>10} {1:>10} {2:>10} {3:>10} {4:>10} {5:>10} {6:>10} {7:>10} {8:>10} {9:>10} {10:>10} {11:>10} {12:>10} {13:>10} {14:>10}'.format(
        "Event","mass","z1mass","z2mass","z1l1Pt","z1l2Pt","z2l1Pt","z2l2Pt","jet1pt","jet1eta","jet2pt","jet2eta","mjj","nJets","fisher")

def print_event(evt):
    print '{0:10} {1:10f} {2:10f} {3:10f} {4:10f} {5:10f} {6:10f} {7:10f} {8:10f} {9:10f} {10:10f} {11:10f} {12:10f} {13:10f} {14:10f}'.format( 
            evt.EVENT, evt.mass, evt.z1Mass, evt.z2Mass, evt.z1l1Pt, evt.z1l2Pt, evt.z2l1Pt, evt.z2l2Pt, evt.VBFjets_jet1pt,
            evt.VBFjets_jet1eta, evt.VBFjets_jet2pt, evt.VBFjets_jet2eta, evt.VBFjets_mjj, evt.VBFjets, evt.VBFjets_fisher)

for evt in mmmm_tree:
    if evt.EVENT in missing_events:
        print_event(evt)

for evt in mmee_tree:
    if evt.EVENT in missing_events:
        print_event(evt)

for evt in eeee_tree:
    if evt.EVENT in missing_events:
        print_event(evt)

mmmm_events = mmmm_tree.GetEntries( selections )
mmee_events = mmee_tree.GetEntries( selections )
eeee_events = eeee_tree.GetEntries( selections )

total = mmmm_events + mmee_events + eeee_events

print '{0:3} {1:>4} {2:>4} {3:>5}'.format("All", "4e", "4mu", "2mu2e")
print '{0:3d} {1:4d} {2:4d} {3:5d}'.format(total, eeee_events, mmmm_events, mmee_events)
