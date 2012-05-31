import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

zMuMuAnalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialZMuMuEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
zMuMuAnalysisConfigurator.addDiCandidateModule('zMuMuCandidates','PATMuPairProducer', 'patMuonsForAnalysis','patMuonsForAnalysis','patMETs','patOverloadedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
zMuMuAnalysisConfigurator.addSorter('zMuMuCandidatesSorted','PATMuPairSorter')
zMuMuAnalysisConfigurator.addCandidateMETModule('wCands','PATMuonNuPairProducer','patMuonsForAnalysis','patMETs','selectedPatJets',1,9999,'AtLeastOneWCandidate')
zMuMuAnalysisConfigurator.addDiCandidateModule('zwMuMuMuCandidates','PATMuMuMuNuQuadProducer','zMuMuCandidates','wCands','patMETs','patOverloadedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
zMuMuAnalysisConfigurator.addSelector('zMuMuCandidatesID','PATMuMuMuNuQuadSelector','leg1.leg1.userFloat("isWWMuon")&&leg1.leg2.userFloat("isWWMuon")&&leg1.leg1.pt()>15&&leg1.leg2.pt()>15&&abs(leg1.leg1.eta)<2.4&&abs(leg1.leg2.eta)<2.4','ZMuMuID')
zMuMuAnalysisConfigurator.addSelector('wMuCandidatesID','PATMuMuMuNuQuadSelector','leg2.lepton.userFloat("isWWMuon")&&leg2.lepton.pt()>15&&abs(leg2.lepton.eta)<2.4','wMuMuID')
zMuMuAnalysisConfigurator.addSelector('zMuMuCandidatesIsol1','PATMuMuMuNuQuadSelector','(leg1.leg1.chargedHadronIso()+leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso())/leg1.leg1.pt()<0.25','ZMuMuLeg1Iso')
zMuMuAnalysisConfigurator.addSelector('zMuMuCandidatesIsol2','PATMuMuMuNuQuadSelector','(leg1.leg2.chargedHadronIso()+leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso())/leg1.leg2.pt()<0.25','ZMuMuLeg2Iso')
zMuMuAnalysisConfigurator.addSelector('wMuMuCandidatesIsol2','PATMuMuMuNuQuadSelector','(leg2.lepton.chargedHadronIso()+leg2.lepton.photonIso()+leg2.lepton.neutralHadronIso())/leg2.lepton.pt()<0.25','WLegIso')
zMuMuAnalysisConfigurator.addSelector('zMuMuMuCandidates','PATMuMuMuNuQuadSelector','leg1.charge==0','ZMuMuOS',0,100)
#create the sequence
selectionSequence=zMuMuAnalysisConfigurator.returnSequence()




