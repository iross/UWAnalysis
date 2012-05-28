import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *


tagAndProbeConfigurator = CutSequenceProducer(initialCounter  = 'initialTagAndProbeEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())


##Tag and probe 
tagAndProbeConfigurator.addDiCandidateModule('tagAndProbePairs','PATEleTrackPairProducer', 'convRejElectrons','trackCandidates','patMETs','selectedPatJets',1,9999,text = '',leadingObjectsOnly = True,dR = 0.15,recoMode = "")
tagAndProbeConfigurator.addSelector('selectedTagAndProbeMuTracks','PATEleTrackPairSelector','leg1.pt()>5&&abs(leg2.eta())<2.4&&abs(leg1.eta())<2.1','tagAndProbePairs',1,100)
tagAndProbeSequence =tagAndProbeConfigurator.returnSequence()




