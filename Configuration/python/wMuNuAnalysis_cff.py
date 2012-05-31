import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *


analysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())


#Make Di Muons to VETO DY
analysisConfigurator.addDiCandidateModule('diMuons','PATMuPairProducer', 'patMuonsForAnalysis','patMuonsForAnalysis','patMETs','selectedPatJets',0,9999,text = '',leadingObjectsOnly = True,dR = 0.15,recoMode = "")
analysisConfigurator.addSorter('diMuonsSorted','PATMuPairSorter')

#Make Muons+MET
analysisConfigurator.addCandidateMETModule('wCands','PATMuonNuPairProducer','patMuonsForAnalysis','patMETs','selectedPatJets',1,9999,'AtLeastOneWCandidate')
analysisConfigurator.addSelector('wCandsGoodMuon','PATMuonNuPairSelector','lepton.pt()>10&&abs(lepton.eta())<2.4','OneLeptonInAcceptance',1)
#analysisConfigurator.addSorter('diTausSorted','PATMuTauPairSorter')


#make Gen Ws
analysisConfigurator.addCandidateMETModule('wGenCands','PATCandNuPairProducer','genMuons','genNeutrinos','selectedPatJets',0,9999,'')
selectionSequence =analysisConfigurator.returnSequence()




