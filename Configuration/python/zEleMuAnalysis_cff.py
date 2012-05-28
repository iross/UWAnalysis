import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *


analysisConfiguratorEMu = CutSequenceProducer(initialCounter  = 'initialEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())


# Give the NSVfit access to the transient track builder, etc.
nSVfitTrackService = cms.Service("NSVfitTrackService")


analysisConfiguratorEMu.addSmearing('patMuVetoTaus','patMuonsForAnalysis','convRejElectrons','patOverloadedJets')

#MakeDileptonPairs
analysisConfiguratorEMu.addDiCandidateModule('diMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
analysisConfiguratorEMu.addSelector('osDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon&&leg2.isGlobalMuon&&leg1.pt()>15&&leg2.pt()>15&&(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()<0.2&&(leg2.chargedHadronIso()+max(0.0,leg2.photonIso+leg2.neutralHadronIso()-0.5*leg2.particleIso()))/leg2.pt()<0.2','DiMuonCreation',0,100)
analysisConfiguratorEMu.addSorter('diMuonsSorted','PATMuPairSorter')

analysisConfiguratorEMu.addDiCandidateModule('diElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
analysisConfiguratorEMu.addSelector('osDiElectrons','PATElePairSelector','leg1.pt()>15&&leg2.pt()>15&&charge==0&&leg1.userFloat("WWID")>0&&leg2.userFloat("wp95")>0&&(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-leg1.userIso(0),0.0))/leg1.pt()<0.3&&(leg2.chargedHadronIso()+max(leg2.photonIso()+leg2.neutralHadronIso()-leg2.userIso(0),0.0))/leg2.pt()<0.3','ZEEVEto',0,100)

#Make muon.electron pairs
analysisConfiguratorEMu.addDiCandidateModule('eleMuons','PATEleMuPairProducer', 'smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text = 'AtLeastOneEleMu',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
analysisConfiguratorEMu.addSelector('eleMuonsElePtEta','PATEleMuPairSelector','leg1.pt()>10&&abs(leg1.eta())<2.5','electronPtEta',1)
analysisConfiguratorEMu.addSelector('eleMuonsMuPtEta','PATEleMuPairSelector','leg2.pt()>10&&abs(leg2.eta())<2.1','muonPtEta',1)
analysisConfiguratorEMu.addSelector('eleMuonsElectronWW','PATEleMuPairSelector','leg1.userFloat("WWID")>0||leg1.userFloat("WWMVAID")>0','WWElectron',1)
analysisConfiguratorEMu.addSelector('eleMuonsMuonWW','PATEleMuPairSelector','leg2.userFloat("isWWMuon")>0','MuonWW',1)
analysisConfiguratorEMu.addEleMuNSVFit('eleMuonsNSVFit')
analysisConfiguratorEMu.addSorter('eleMuonsSorted','PATEleMuPairSorter')
analysisConfiguratorEMu.addSelector('eleMuonsOS','PATEleMuPairSelector','charge==0','OS',1)

#create the sequence
selectionSequence =analysisConfiguratorEMu.returnSequence()




