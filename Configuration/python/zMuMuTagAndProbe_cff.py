import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *


tagAndProbeConfigurator = CutSequenceProducer(initialCounter  = 'initialTagAndProbeEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())


##Tag and probe 
tagAndProbeConfigurator.addDiCandidateModule('tagAndProbeMuTracks','PATMuTrackPairProducer', 'patMuonsForAnalysis','trackCandidates','patMETs','selectedPatJets',1,9999,text = '',leadingObjectsOnly = True,dR = 0.15,recoMode = "")
tagAndProbeConfigurator.addSelector('selectedTagAndProbeMuTracks','PATMuTrackPairSelector','calibratedMET.pt()<20 && charge==0&&mass>50&&mass<120&&leg1.userFloat("isWWMuon")&&((leg1.chargedHadronIso+leg1.photonIso+leg1.neutralHadronIso)/leg1.pt()<0.2)&&leg1.pt()>25&&leg2.pt()>5&&abs(leg2.eta())<2.4&&abs(leg1.eta())<2.1','tagAndProbePairs',1,100)
tagAndProbeSequence =tagAndProbeConfigurator.returnSequence()




