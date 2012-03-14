import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

analysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

# Give the NSVfit access to the transient track builder, etc.
nSVfitTrackService = cms.Service("NSVfitTrackService")

#Add smearing
analysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','patOverloadedJets')

#Create di muon pairs for veto purposes
analysisConfigurator.addDiCandidateModule('diMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
analysisConfigurator.addSelector('osDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon&&leg2.isGlobalMuon&&leg1.pt()>15&&leg2.pt()>15&&(leg1.chargedHadronIso()+max(0.0,leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0)))/leg1.pt()<0.2&&(leg2.chargedHadronIso()+max(0.0,leg2.photonIso+leg2.neutralHadronIso()-0.5*leg2.userIso(0)))/leg2.pt()<0.2','DiMuonCreation',0,100)
analysisConfigurator.addSorter('diMuonsSorted','PATMuPairSorter')

#Make DiTaus
analysisConfigurator.addDiCandidateModule('diTaus','PATMuTauPairProducer','smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text='AtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
analysisConfigurator.addSelector('diTausMuonID','PATMuTauPairSelector','leg1.userFloat("isWWMuon")','MuonWW',1)
analysisConfigurator.addSelector('diTausMuonPtEta','PATMuTauPairSelector','leg1.pt()>15&&abs(leg1.eta())<2.1','MuonPtEta',1)
#analysisConfigurator.addSelector('diTausMuonIsolation','PATMuTauPairSelector','(leg1.chargedHadronIso()+max(0.0,leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0)))/leg1.pt()<0.1','MuonIsolation',1)
analysisConfigurator.addSelector('diTausTauPtEta','PATMuTauPairSelector','leg2.pt()>20&&abs(leg2.eta())<2.3','TauPtEta',1)
analysisConfigurator.addSelector('diTausDecayFound','PATMuTauPairSelector','leg2.tauID("decayModeFinding")>0','TauDecayFound',1)
analysisConfigurator.addSelector('diTausVLooseTauIsolation','PATMuTauPairSelector','(leg2.tauID("byVLooseCombinedIsolationDeltaBetaCorr")>0)','TauVLooseIsoDB',1)
#analysisConfigurator.addSelector('diTausLooseTauIsolation','PATMuTauPairSelector','(leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")>0)','TauLooseIsoDB',1)
analysisConfigurator.addSelector('diTausTauElectronVeto','PATMuTauPairSelector','leg2.tauID("againstElectronLoose")','AgainstElectron',1)
analysisConfigurator.addMuTauNSVFit('muTausNSVFit')
analysisConfigurator.addSelector('diTausTauMuonVeto','PATMuTauPairSelector','leg2.tauID("againstMuonTight")','AgainstMuon',1)
analysisConfigurator.addSelector('diTausWRej','PATMuTauPairSelector','mt1MET<40','WRejection',1)
analysisConfigurator.addSelector('diTausOS','PATMuTauPairSelector','charge==0','OS',1)

#create the sequence
selectionSequence =analysisConfigurator.returnSequence()




