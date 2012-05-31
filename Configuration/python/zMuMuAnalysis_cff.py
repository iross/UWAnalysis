import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

zMuMuAnalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialZMuMuEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
zMuMuAnalysisConfigurator.addDiCandidateModule('zMuMuCandidates','PATMuPairProducer', 'patMuonsForAnalysis','patMuonsForAnalysis','patMETs','patOverloadedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
zMuMuAnalysisConfigurator.addSorter('zMuMuCandidatesSorted','PATMuPairSorter')
zMuMuAnalysisConfigurator.addSelector('zMuMuCandidatesID','PATMuPairSelector','leg1.userFloat("isWWMuon")&&leg2.userFloat("isWWMuon")&&leg1.pt()>15&&leg2.pt()>15&&abs(leg1.eta)<2.4&&abs(leg2.eta)<2.4','ZMuMuID')
zMuMuAnalysisConfigurator.addSelector('zMuMuCandidatesIsol1','PATMuPairSelector','(leg1.chargedHadronIso()+leg1.photonIso()+leg1.neutralHadronIso())/leg1.pt()<0.25','ZMuMuLeg1Iso')
zMuMuAnalysisConfigurator.addSelector('zMuMuCandidatesIsol2','PATMuPairSelector','(leg2.chargedHadronIso()+leg2.photonIso()+leg2.neutralHadronIso())/leg2.pt()<0.25','ZMuMuLeg2Iso')
zMuMuAnalysisConfigurator.addSelector('zMuMuCandidatesOS','PATMuPairSelector','charge==0','ZMuMuOS',0,100)
#create the sequence
selectionSequence=zMuMuAnalysisConfigurator.returnSequence()




