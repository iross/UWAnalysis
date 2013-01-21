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

selections = "mass > 70 && subBestZmass > 12"
#selections = "mass > 70 && subBestZmass > 12 && mass > 100 && kd > 0.1"

#selections = "mass > 70 && subBestZmass > 12 && mass > 100 && VBFjets == 2"
selections = "mass > 70 && subBestZmass > 12 && mass > 100 && VBFjets == 2 && VBFjets_fisher > 0.4"

print "All    4e   4mu 2e2mu"

mmmm_events = mmmm_tree.GetEntries(selections)
mmee_events = mmee_tree.GetEntries(selections)
eeee_events = eeee_tree.GetEntries(selections)

total = mmmm_events + mmee_events + eeee_events

print '{0:3d} {1:5d} {2:5d} {3:5d}'.format(total,eeee_events,mmmm_events,mmee_events)
