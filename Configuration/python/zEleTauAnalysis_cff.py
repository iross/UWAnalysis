import FWCore.ParameterSet.Config as cms



#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *


analysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEvents',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

nSVfitTrackService = cms.Service("NSVfitTrackService")

analysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','patOverloadedJets')


#create dielectrons
analysisConfigurator.addDiCandidateModule('diElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',0,9999,text = '',leadingObjectsOnly = False,dR = 0.15,recoMode = "")
analysisConfigurator.addSelector('osDiElectrons','PATElePairSelector','leg1.pt()>15&&leg2.pt()>15&&charge==0&&(leg1.userFloat("WWID")>0||leg1.userFloat("WWMVAID")>0)&&leg2.userFloat("wp95")>0&&(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.userIso(0),0.0))/leg1.pt()<0.25&&(leg2.chargedHadronIso()+max(leg2.photonIso()+leg2.neutralHadronIso()-0.5*leg2.userIso(0),0.0))/leg2.pt()<0.25','ZEEVEto',0,100)

#Make DiTaus
analysisConfigurator.addDiCandidateModule('eleTaus','PATEleTauPairProducer', 'smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'AtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
analysisConfigurator.addSelector('eleTausWW','PATEleTauPairSelector','leg1.userFloat("WWID")>0||leg1.userFloat("WWMVAID")>0','WWElectronID',1)
analysisConfigurator.addSelector('eleTausElePtEta','PATEleTauPairSelector','leg1.pt()>20&&abs(leg1.eta())<2.1','electronPtEta',1)
#analysisConfigurator.addSelector('eleTausEleIsolation','PATEleTauPairSelector','(leg1.chargedHadronIso()+max(leg1.photonIso()+leg1.neutralHadronIso()-0.5*leg1.particleIso(),0.0))/leg1.pt()<0.1','electronIsolation',1)
analysisConfigurator.addSelector('eleTausTauPtEta','PATEleTauPairSelector','leg2.tauID("decayModeFinding")&&leg2.pt()>20&&abs(leg2.eta())<2.3','TauDecayFound',1)
analysisConfigurator.addSelector('eleTausVLooseIsolation','PATEleTauPairSelector','leg2.tauID("byVLooseCombinedIsolationDeltaBetaCorr")>0','TauLooseIso',1)
#analysisConfigurator.addSelector('eleTausLooseIsolation','PATEleTauPairSelector','leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")>0','TauLooseIso',1)
analysisConfigurator.addSelector('eleTausTauMuonVeto','PATEleTauPairSelector','leg2.tauID("againstMuonLoose")','AgainstMuon',1)
analysisConfigurator.addSelector('eleTausTauElectronVeto','PATEleTauPairSelector','leg2.tauID("againstElectronMedium")','AgainstElectron',1)
analysisConfigurator.addEleTauNSVFit('eleTausNSVFit')
analysisConfigurator.addSorter('eleTausSorted','PATEleTauPairSorter')
analysisConfigurator.addSelector('eleTausOS','PATEleTauPairSelector','charge==0','OS',1)

#create the sequence
selectionSequence =analysisConfigurator.returnSequence()




