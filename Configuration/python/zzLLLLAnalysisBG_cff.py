import FWCore.ParameterSet.Config as cms

#Import tool that creates the cut sequence
from UWAnalysis.Configuration.tools.CutSequenceProducer import *

######################__________________________________MMMT_____________________________________##############################

#for use with mu anti-isolated
MMMTantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsMMMT1',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMMTantiIso1.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets')
MMMTantiIso1.addDiCandidateModule('antiIso1MMMTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMTantiIso1.addSelector('antiIso1MMMTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60 && mass < 120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMMTDiMuonCreation',1)
MMMTantiIso1.addDiCandidateModule('antiIso1MMMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTantiIso1.addDiCandidateModule('antiIso1MMMTzzCands','PATMuMuMuTauQuadProducer','antiIso1MMMTosDiMuons','antiIso1MMMTmuTau','smearedMET','smearedJets',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMTantiIso1.addCrossCleanerModule('antiIso1MMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMTantiIso1.addSelector('antiIso1MMMTzzMuID','PATMuMuMuTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMMTLeadingZMuID')
MMMTantiIso1.addSelector('antiIso1MMMTzzMuIso','PATMuMuMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMMTLeadingZMuIso')
MMMTantiIso1.addSelector('antiIso1MMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','MMMTSecondZMuID')
MMMTantiIso1.addSelector('antiIso1MMMTz2Charge','PATMuMuMuTauQuadSelector','leg2.charge()==0','MMMTTauLeptonDiscrimantor')
MMMTantiIso1.addSelector('antiIso1MMMTzzTauDiscr','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','MMMTTauLeptonDiscrimantor')
MMMTantiIso1.addSelector('antiIso1MMMTpT','PATMuMuMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','MMMTTauLeptonDiscrimantor')
MMMTantiIso1.addSorter('antiIso1MMMTzzCleanedCandsSortedByZMass','PATMuMuMuTauQuadSorterByZMass')
MMMTantiIso1.addSelector('antiIso1MMMTzzdZ','PATMuMuMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMTdZ')
MMMTantiIso1.addSelector('MMMTnoIsoOSF','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMMTTauDecayModeFinding')
MMMTantiIso1.addSelector('MMMTantiIso1F','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','MMMTSecondZMuIso')
MMMTantiIso1Seq =MMMTantiIso1.returnSequence()

MMMTnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsMMMTSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMMTnoIsoSS.addDiCandidateModule('noIsoSSMMMTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMTnoIsoSS.addSelector('noIsoSSMMMTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60 && mass < 120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMMTDiMuonCreation',1)
MMMTnoIsoSS.addDiCandidateModule('noIsoSSMMMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTnoIsoSS.addDiCandidateModule('noIsoSSMMMTzzCands','PATMuMuMuTauQuadProducer','noIsoSSMMMTosDiMuons','noIsoSSMMMTmuTau','smearedMET','smearedJets',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMTnoIsoSS.addCrossCleanerModule('noIsoSSMMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMTnoIsoSS.addSelector('noIsoSSMMMTzzMuID','PATMuMuMuTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMMTLeadingZMuID')
MMMTnoIsoSS.addSelector('noIsoSSMMMTzzMuIso','PATMuMuMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMMTLeadingZMuIso')
MMMTnoIsoSS.addSelector('noIsoSSMMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','MMMTSecondZMuID')
MMMTnoIsoSS.addSelector('noIsoSSMMMTz2Charge','PATMuMuMuTauQuadSelector','leg2.charge()!=0','MMMTTauLeptonDiscrimantor')
MMMTnoIsoSS.addSelector('noIsoSSMMMTz2pt','PATMuMuMuTauQuadSelector','leg2.leg1.pt()>10','MMMTTauLeptonDiscrimantor')
MMMTnoIsoSS.addSorter('noIsoSSMMMTzzCleanedCandsSortedByZMass','PATMuMuMuTauQuadSorterByZMass')
MMMTnoIsoSS.addSelector('noIsoSSMMMTzzdZ','PATMuMuMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMTdZ')
MMMTnoIsoSS.addSelector('MMMTnoIsoSSF','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMMTTauDecayModeFinding')
MMMTnoIsoSS.addSelector('MMMTnoIsoSScheckF','PATMuMuMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','MMMTTauDecayModeFinding')
MMMTnoIsoSSSeq =MMMTnoIsoSS.returnSequence()

#tau anti-isolated
MMMTantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsMMMT2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMMTantiIso2.addDiCandidateModule('antiIso2MMMTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMTantiIso2.addSelector('antiIso2MMMTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMMTDiMuonCreation',1)
MMMTantiIso2.addDiCandidateModule('antiIso2MMMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTantiIso2.addDiCandidateModule('antiIso2MMMTzzCands','PATMuMuMuTauQuadProducer','antiIso2MMMTosDiMuons','antiIso2MMMTmuTau','smearedMET','smearedJets',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMTantiIso2.addCrossCleanerModule('antiIso2MMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMTantiIso2.addSelector('antiIso2MMMTzzMuID','PATMuMuMuTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMMTLeadingZMuID')
MMMTantiIso2.addSelector('antiIso2MMMTzzMuIso','PATMuMuMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMMTLeadingZMuIso')
MMMTantiIso2.addSelector('antiIso2MMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','MMMTSecondZMuID')
MMMTantiIso2.addSelector('antiIso2MMMTzzTauID','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMMTTauDecayModeFinding')
MMMTantiIso2.addSelector('antiIso2MMMTzzTauDiscr','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','MMMTTauLeptonDiscrimantor')
MMMTantiIso2.addSelector('antiIso2MMMTpT','PATMuMuMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','MMMTTauLeptonDiscrimantor')
MMMTantiIso2.addSelector('antiIso2MMMTz2Charge','PATMuMuMuTauQuadSelector','leg2.charge()==0','MMMTTauLeptonDiscrimantor')
MMMTantiIso2.addSorter('antiIso2MMMTzzCleanedCandsSortedByZMass','PATMuMuMuTauQuadSorterByZMass')
MMMTantiIso2.addSelector('antiIso2MMMTzzdZ','PATMuMuMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMTdZ')
MMMTantiIso2.addSelector('MMMTantiIso2F','PATMuMuMuTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.15','MMMTSecondZMuIso')
#create the sequence
MMMTantiIso2Seq =MMMTantiIso2.returnSequence()

#both anti-isolated
MMMTantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsMMMTBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMMTantiIsoBoth.addDiCandidateModule('antiIsoBothMMMTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMMTDiMuonCreation',1)
MMMTantiIsoBoth.addDiCandidateModule('antiIsoBothMMMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'MMMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
MMMTantiIsoBoth.addDiCandidateModule('antiIsoBothMMMTzzCands','PATMuMuMuTauQuadProducer','antiIsoBothMMMTosDiMuons','antiIsoBothMMMTmuTau','smearedMET','smearedJets',1,9999,text='MMMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMTantiIsoBoth.addCrossCleanerModule('antiIsoBothMMMTzzCleanedCands','PATMuMuMuTauQuadCrossCleaner',1,9999,text='MMMTAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTzzMuID','PATMuMuMuTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMMTLeadingZMuID')
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTzzMuIso','PATMuMuMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMMTLeadingZMuIso')
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTzzMuID2','PATMuMuMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','MMMTSecondZMuID')
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTzzTauID','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','MMMTTauDecayModeFinding')
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTzzTauDiscr','PATMuMuMuTauQuadSelector','leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonTight")','MMMTTauLeptonDiscrimantor')
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTpT','PATMuMuMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','MMMTPt')
MMMTantiIsoBoth.addSorter('antiIsoBothMMMTzzCleanedCandsSortedByZMass','PATMuMuMuTauQuadSorterByZMass')
MMMTantiIsoBoth.addSelector('antiIsoBothMMMTzzdZ','PATMuMuMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMTdZ')
MMMTantiIsoBoth.addSelector('MMMTantiIsoBothF','PATMuMuMuTauQuadSelector','leg2.charge()==0','MMMTz2Charge')
#MMMTantiIsoBoth.addSelector('MMMTantiIsoBothF','PATMuMuMuTauQuadSelector','!leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")&&(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.15','MMMTSecondZMuIso')
#create the sequence
MMMTantiIsoBothSeq =MMMTantiIsoBoth.returnSequence()


######################__________________________________MMTT_____________________________________##############################

MMTTantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsMMTT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMTTantiIso1.addDiCandidateModule('antiIso1MMTTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMTTantiIso1.addSelector('antiIso1MMTTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMTT DiMuonCreation',1)
MMTTantiIso1.addDiCandidateModule('antiIso1MMTTdiTaus','PATDiTauPairProducer','smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTantiIso1.addDiCandidateModule('antiIso1MMTTzzCands','PATMuMuTauTauQuadProducer','antiIso1MMTTosDiMuons','antiIso1MMTTdiTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTantiIso1.addCrossCleanerModule('antiIso1MMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1) 
MMTTantiIso1.addSelector('antiIso1MMTTzzMuID','PATMuMuTauTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMTTLeadingZMuID')
MMTTantiIso1.addSelector('antiIso1MMTTzzMuIso','PATMuMuTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMTTLeadingZMuIso')
MMTTantiIso1.addSelector('antiIso1MMTTz2Charge','PATMuMuTauTauQuadSelector','leg2.charge()==0','MMTT')
MMTTantiIso1.addSelector('antiIso1MMTTPt','PATMuMuTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','MMTTPt')
MMTTantiIso1.addSelector('antiIso1MMTTnoIso','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstElectronLoose")&&leg2.leg1.tauID("againstMuonLoose")&&leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonLoose")','MMTTTauLeptonDiscrimantor')
MMTTantiIso1.addSorter('antiIso1MMTTzzCleanedCandsSortedByZMass','PATMuMuTauTauQuadSorterByZMass')
MMTTantiIso1.addSelector('antiIso1MMTTzzdZ','PATMuMuTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMTTdZ')
MMTTantiIso1.addSelector('MMTTnoIsoOSF','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','MMTTDecayModeFinding')
MMTTantiIso1.addSelector('MMTTantiIso1F','PATMuMuTauTauQuadSelector','leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','MMTTTauIsolation1')
MMTTantiIso1Seq =MMTTantiIso1.returnSequence()

MMTTnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsMMTTSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMTTnoIsoSS.addDiCandidateModule('noIsoSSMMTTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMTTnoIsoSS.addSelector('noIsoSSMMTTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMTT DiMuonCreation',1)
MMTTnoIsoSS.addDiCandidateModule('noIsoSSMMTTdiTaus','PATDiTauPairProducer','smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTnoIsoSS.addDiCandidateModule('noIsoSSMMTTzzCands','PATMuMuTauTauQuadProducer','noIsoSSMMTTosDiMuons','noIsoSSMMTTdiTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTnoIsoSS.addCrossCleanerModule('noIsoSSMMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1) 
MMTTnoIsoSS.addSelector('noIsoSSMMTTzzMuID','PATMuMuTauTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMTTLeadingZMuID')
MMTTnoIsoSS.addSelector('noIsoSSMMTTzzMuIso','PATMuMuTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMTTLeadingZMuIso')
MMTTnoIsoSS.addSelector('noIsoSSMMTTz2Charge','PATMuMuTauTauQuadSelector','leg2.charge()!=0','MMTTz2Charge')
MMTTnoIsoSS.addSelector('noIsoSSMMTTz2Pt','PATMuMuTauTauQuadSelector','leg2.leg1.pt()>10&&leg2.leg2.pt()>10','MMTTz2Charge')
MMTTnoIsoSS.addSorter('noIsoSSMMTTzzCleanedCandsSortedByZMass','PATMuMuTauTauQuadSorterByZMass')
MMTTnoIsoSS.addSelector('noIsoSSMMTTzzdZ','PATMuMuTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMTTdZ')
MMTTnoIsoSS.addSelector('MMTTnoIsoSSF','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','MMTTDecayModeFinding')
MMTTnoIsoSS.addSelector('MMTTnoIsoSScheckF','PATMuMuTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','MMTTDecayModeFinding')
MMTTnoIsoSSSeq =MMTTnoIsoSS.returnSequence()


MMTTantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsMMTT2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMTTantiIso2.addDiCandidateModule('antiIso2MMTTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMTTantiIso2.addSelector('antiIso2MMTTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMTT DiMuonCreation',1)
MMTTantiIso2.addDiCandidateModule('antiIso2MMTTdiTaus','PATDiTauPairProducer','smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTantiIso2.addDiCandidateModule('antiIso2MMTTzzCands','PATMuMuTauTauQuadProducer','antiIso2MMTTosDiMuons','antiIso2MMTTdiTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTantiIso2.addCrossCleanerModule('antiIso2MMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1) 
MMTTantiIso2.addSelector('antiIso2MMTTzzMuID','PATMuMuTauTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMTTLeadingZMuID')
MMTTantiIso2.addSelector('antiIso2MMTTzzMuIso','PATMuMuTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMTTLeadingZMuIso')
MMTTantiIso2.addSelector('antiIso2MMTTzzTauID','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','MMTTDecayModeFinding')
MMTTantiIso2.addSelector('antiIso2MMTTnoIso','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstElectronLoose")&&leg2.leg1.tauID("againstMuonLoose")&&leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonLoose")','MMTTTauLeptonDiscrimantor')
MMTTantiIso2.addSelector('antiIso2MMTTPt','PATMuMuTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','MMTTPt')
MMTTantiIso2.addSelector('antiIso2MMTTz2Charge','PATMuMuTauTauQuadSelector','leg2.charge()==0','MMTTz2Charge')
MMTTantiIso2.addSorter('antiIso2MMTTzzCleanedCandsSortedByZMass','PATMuMuTauTauQuadSorterByZMass')
MMTTantiIso2.addSelector('antiIso2MMTTzzdZ','PATMuMuTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMTTdZ')
MMTTantiIso2.addSelector('MMTTantiIso2F','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("byMediumCombinedIsolationDeltaBetaCorr")','MMTTTauIsolation')
MMTTantiIso2Seq =MMTTantiIso2.returnSequence()

MMTTantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsMMTTBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
MMTTantiIsoBoth.addDiCandidateModule('antiIsoBothMMTTdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMTTantiIsoBoth.addSelector('antiIsoBothMMTTosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMTT DiMuonCreation',1)
MMTTantiIsoBoth.addDiCandidateModule('antiIsoBothMMTTdiTaus','PATDiTauPairProducer','smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTantiIsoBoth.addDiCandidateModule('antiIsoBothMMTTzzCands','PATMuMuTauTauQuadProducer','antiIsoBothMMTTosDiMuons','antiIsoBothMMTTdiTaus','smearedMET','smearedJets',1,9999,text='MMTTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMTTantiIsoBoth.addCrossCleanerModule('antiIsoBothMMTTzzCleanedCands','PATMuMuTauTauQuadCrossCleaner',1,9999,text='MMTTAtLeastOneZZCleanedCandidate',dR = 0.1) 
MMTTantiIsoBoth.addSelector('antiIsoBothMMTTzzMuID','PATMuMuTauTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMTTLeadingZMuID')
MMTTantiIsoBoth.addSelector('antiIsoBothMMTTzzMuIso','PATMuMuTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMTTLeadingZMuIso')
MMTTantiIsoBoth.addSelector('antiIsoBothMMTTzzTauID','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','MMTTDecayModeFinding')
MMTTantiIsoBoth.addSelector('antiIsoBothMMTTPt','PATMuMuTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','MMTTPt')
MMTTantiIsoBoth.addSelector('antiIsoBothMMTTz2Charge','PATMuMuTauTauQuadSelector','leg2.charge()==0','MMTTz2Charge')
MMTTantiIsoBoth.addSorter('antiIsoBothMMTTzzCleanedCandsSortedByZMass','PATMuMuTauTauQuadSorterByZMass')
MMTTantiIsoBoth.addSelector('antiIsoBothMMTTzzdZ','PATMuMuTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMTTdZ')
MMTTantiIsoBoth.addSelector('MMTTantiIsoBothF','PATMuMuTauTauQuadSelector','leg2.leg1.tauID("againstElectronLoose")&&leg2.leg1.tauID("againstMuonLoose")&&leg2.leg2.tauID("againstElectronLoose")&&leg2.leg2.tauID("againstMuonLoose")','MMTTTauLeptonDiscrimantor')
#MMTTantiIsoBoth.addSelector('MMTTantiIsoBothF','PATMuMuTauTauQuadSelector','!leg2.leg1.tauID("byMediumCombinedIsolationDeltaBetaCorr")&&!leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','MMTTTauIsolation')
MMTTantiIsoBothSeq =MMTTantiIsoBoth.returnSequence()


######################__________________________________MMET_____________________________________##############################

MMETantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsMMET',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMETantiIso1.addDiCandidateModule('antiIso1MMETdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMETantiIso1.addSelector('antiIso1MMETosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIso1MMET DiMuonCreation',1)
MMETantiIso1.addDiCandidateModule('antiIso1MMETelecTau','PATEleTauPairProducer','smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text='antiIso1MMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETantiIso1.addDiCandidateModule('antiIso1MMETzzCands','PATMuMuEleTauQuadProducer','antiIso1MMETosDiMuons','antiIso1MMETelecTau','smearedMET','smearedJets',1,9999,text='antiIso1MMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETantiIso1.addCrossCleanerModule('antiIso1MMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='antiIso1MMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETantiIso1.addSelector('antiIso1MMETzzCleanedMuID','PATMuMuEleTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIso1MMETLeadingZMuID')
MMETantiIso1.addSelector('antiIso1MMETzzMuIso','PATMuMuEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1MMETLeadingZMuIso')
MMETantiIso1.addSelector('antiIso1MMETzzCleanedEleID','PATMuMuEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIso1MMETEleCiCTight')
MMETantiIso1.addSelector('antiIso1MMETz2Charge','PATMuMuEleTauQuadSelector','leg2.charge()==0','MMETz2Charge')
MMETantiIso1.addSelector('antiIso1MMETpT','PATMuMuEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','MMETpt')
MMETantiIso1.addSorter('antiIso1MMETzzCleanedCandsSortedByZMass','PATMuMuEleTauQuadSorterByZMass')
MMETantiIso1.addSelector('antiIso1MMETzzdZ','PATMuMuEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMETdZ')
MMETantiIso1.addSelector('MMETnoIsoOSF','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIso1MMETDecayModeFinding')
MMETantiIso1.addSelector('MMETantiIso1F','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','antiIso1MMETEleIso')
MMETantiIso1Seq =MMETantiIso1.returnSequence()

MMETnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsMMETSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMETnoIsoSS.addDiCandidateModule('noIsoSSMMETdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMETnoIsoSS.addSelector('noIsoSSMMETosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','noIsoSSMMET DiMuonCreation',1)
MMETnoIsoSS.addDiCandidateModule('noIsoSSMMETelecTau','PATEleTauPairProducer','smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text='noIsoSSMMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETnoIsoSS.addDiCandidateModule('noIsoSSMMETzzCands','PATMuMuEleTauQuadProducer','noIsoSSMMETosDiMuons','noIsoSSMMETelecTau','smearedMET','smearedJets',1,9999,text='noIsoSSMMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETnoIsoSS.addCrossCleanerModule('noIsoSSMMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='noIsoSSMMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETnoIsoSS.addSelector('noIsoSSMMETzzCleanedMuID','PATMuMuEleTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','noIsoSSMMETLeadingZMuID')
MMETnoIsoSS.addSelector('noIsoSSMMETzzMuIso','PATMuMuEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSMMETLeadingZMuIso')
MMETnoIsoSS.addSelector('noIsoSSMMETzzCleanedEleID','PATMuMuEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','noIsoSSMMETEleCiCTight')
MMETnoIsoSS.addSelector('noIsoSSMMETz2Charge','PATMuMuEleTauQuadSelector','leg2.charge()!=0','MMETz2Charge')
MMETnoIsoSS.addSelector('noIsoSSMMETz2Pt','PATMuMuEleTauQuadSelector','leg2.leg1.pt()>10','MMETz2Charge')
MMETnoIsoSS.addSorter('noIsoSSMMETzzCleanedCandsSortedByZMass','PATMuMuEleTauQuadSorterByZMass')
MMETnoIsoSS.addSelector('noIsoSSMMETzzdZ','PATMuMuEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMETdZ')
MMETnoIsoSS.addSelector('MMETnoIsoSSF','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','noIsoSSMMETDecayModeFinding')
MMETnoIsoSS.addSelector('MMETnoIsoSScheckF','PATMuMuEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','noIsoSSMMETDecayModeFinding')
MMETnoIsoSSSeq =MMETnoIsoSS.returnSequence()


MMETantiIso2= CutSequenceProducer(initialCounter  = 'initialEventsMMET2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMETantiIso2.addDiCandidateModule('antiIso2MMETdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMETantiIso2.addSelector('antiIso2MMETosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIso2MMET DiMuonCreation',1)
MMETantiIso2.addDiCandidateModule('antiIso2MMETelecTau','PATEleTauPairProducer','smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text='antiIso2MMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETantiIso2.addDiCandidateModule('antiIso2MMETzzCands','PATMuMuEleTauQuadProducer','antiIso2MMETosDiMuons','antiIso2MMETelecTau','smearedMET','smearedJets',1,9999,text='antiIso2MMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETantiIso2.addCrossCleanerModule('antiIso2MMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='antiIso2MMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETantiIso2.addSelector('antiIso2MMETzzCleanedMuID','PATMuMuEleTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIso2MMETLeadingZMuID')
MMETantiIso2.addSelector('antiIso2MMETzzMuIso','PATMuMuEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2MMETLeadingZMuIso')
MMETantiIso2.addSelector('antiIso2MMETzzCleanedEleID','PATMuMuEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIso2MMETEleCiCTight')
MMETantiIso2.addSelector('antiIso2MMETnoIsoF','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIso2MMETDecayModeFinding')
MMETantiIso2.addSelector('antiIso2MMETpT','PATMuMuEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','MMETpt')
MMETantiIso2.addSelector('antiIso2MMETz2Charge','PATMuMuEleTauQuadSelector','leg2.charge()==0','MMETz2Charge')
MMETantiIso2.addSorter('antiIso2MMETzzCleanedCandsSortedByZMass','PATMuMuEleTauQuadSorterByZMass')
MMETantiIso2.addSelector('antiIso2MMETzzdZ','PATMuMuEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMETdZ')
MMETantiIso2.addSelector('MMETantiIso2F','PATMuMuEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.10','MMEMEleIso')
MMETantiIso2Seq=MMETantiIso2.returnSequence()

MMETantiIsoBoth= CutSequenceProducer(initialCounter  = 'initialEventsMMETBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMETantiIsoBoth.addDiCandidateModule('antiIsoBothMMETdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMETantiIsoBoth.addSelector('antiIsoBothMMETosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothMMET DiMuonCreation',1)
MMETantiIsoBoth.addDiCandidateModule('antiIsoBothMMETelecTau','PATEleTauPairProducer','smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text='antiIsoBothMMETAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETantiIsoBoth.addDiCandidateModule('antiIsoBothMMETzzCands','PATMuMuEleTauQuadProducer','antiIsoBothMMETosDiMuons','antiIsoBothMMETelecTau','smearedMET','smearedJets',1,9999,text='antiIsoBothMMETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMETantiIsoBoth.addCrossCleanerModule('antiIsoBothMMETzzCleanedCands2','PATMuMuEleTauQuadCrossCleaner',1,9999,text='antiIsoBothMMETAtLeastOneZZCleanedCandidate',dR = 0.1)
MMETantiIsoBoth.addSelector('antiIsoBothMMETzzCleanedMuID','PATMuMuEleTauQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIsoBothMMETLeadingZMuID')
MMETantiIsoBoth.addSelector('antiIsoBothMMETzzMuIso','PATMuMuEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothMMETLeadingZMuIso')
MMETantiIsoBoth.addSelector('antiIsoBothMMETzzCleanedEleID','PATMuMuEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIsoBothMMETEleCiCTight')
MMETantiIsoBoth.addSelector('antiIsoBothMMETnoIsoF','PATMuMuEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIsoBothMMETDecayModeFinding')
MMETantiIsoBoth.addSelector('antiIsoBothMMETpT','PATMuMuEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','MMETpt')
MMETantiIsoBoth.addSorter('antiIsoBothMMETzzCleanedCandsSortedByZMass','PATMuMuEleTauQuadSorterByZMass')
MMETantiIsoBoth.addSelector('antiIsoBothMMETzzdZ','PATMuMuEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMETdZ')
MMETantiIsoBoth.addSelector('MMETantiIsoBothF','PATMuMuEleTauQuadSelector','leg2.charge()==0','MMETz2Charge')
#MMETantiIsoBoth.addSelector('MMETantiIsoBothF','PATMuMuEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.10&&!leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','MMEMEleIso')
MMETantiIsoBothSeq=MMETantiIsoBoth.returnSequence()


######################__________________________________MMEM_____________________________________##############################

MMEMantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsMMEM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEMantiIso1.addDiCandidateModule('antiIso1MMEMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEMantiIso1.addSelector('antiIso1MMEMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMEM DiMuonCreation',1)
MMEMantiIso1.addDiCandidateModule('antiIso1MMEMelecMu','PATEleMuPairProducer','smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMantiIso1.addDiCandidateModule('antiIso1MMEMzzCands','PATMuMuEleMuQuadProducer','antiIso1MMEMosDiMuons','antiIso1MMEMelecMu','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMantiIso1.addCrossCleanerModule('antiIso1MMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEMantiIso1.addSelector('antiIso1MMEMzzCleanedMuID','PATMuMuEleMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMEMLeadingZMuID')
MMEMantiIso1.addSelector('antiIso1MMEMzzMuIso','PATMuMuEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMEMLeadingZMuIso')
MMEMantiIso1.addSelector('antiIso1MMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','MMEMThirdMuID')
MMEMantiIso1.addSelector('antiIso1MMEMz2Charge','PATMuMuEleMuQuadSelector','leg2.charge()==0','MMEMEleIso')
MMEMantiIso1.addSelector('antiIso1MMEMPt','PATMuMuEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','MMEMPt')
MMEMantiIso1.addSorter('antiIso1MMEMSorted','PATMuMuEleMuQuadSorterByZMass')
MMEMantiIso1.addSelector('antiIso1MMEMzzdZ','PATMuMuEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEMdZ')
MMEMantiIso1.addSelector('MMEMnoIsoOSF','PATMuMuEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','MMEMEleCiCLoose') 
MMEMantiIso1.addSelector('MMEMantiIso1F','PATMuMuEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','MMEMMuIso')
MMEMantiIso1Seq =MMEMantiIso1.returnSequence()

MMEMnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsMMEMSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEMnoIsoSS.addDiCandidateModule('noIsoSSMMEMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEMnoIsoSS.addSelector('noIsoSSMMEMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMEM DiMuonCreation',1)
MMEMnoIsoSS.addDiCandidateModule('noIsoSSMMEMelecMu','PATEleMuPairProducer','smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMnoIsoSS.addDiCandidateModule('noIsoSSMMEMzzCands','PATMuMuEleMuQuadProducer','noIsoSSMMEMosDiMuons','noIsoSSMMEMelecMu','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMnoIsoSS.addCrossCleanerModule('noIsoSSMMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEMnoIsoSS.addSelector('noIsoSSMMEMzzCleanedMuID','PATMuMuEleMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMEMLeadingZMuID')
MMEMnoIsoSS.addSelector('noIsoSSMMEMzzMuIso','PATMuMuEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMEMLeadingZMuIso')
MMEMnoIsoSS.addSelector('noIsoSSMMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','MMEMThirdMuID')
MMEMnoIsoSS.addSelector('noIsoSSMMEMz2Charge','PATMuMuEleMuQuadSelector','leg2.charge()!=0','MMEMEleIso')
MMEMnoIsoSS.addSorter('noIsoSSMMEMSorted','PATMuMuEleMuQuadSorterByZMass')
MMEMnoIsoSS.addSelector('noIsoSSMMEMzzdZ','PATMuMuEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEMdZ')
MMEMnoIsoSS.addSelector('MMEMnoIsoSSF','PATMuMuEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','MMEMEleCiCLoose') 
MMEMnoIsoSS.addSelector('MMEMnoIsoSScheckF','PATMuMuEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','MMEMEleCiCLoose') 
MMEMnoIsoSSSeq =MMEMnoIsoSS.returnSequence()

MMEMantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsMMEM2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEMantiIso2.addDiCandidateModule('antiIso2MMEMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEMantiIso2.addSelector('antiIso2MMEMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMEM DiMuonCreation',1)
MMEMantiIso2.addDiCandidateModule('antiIso2MMEMelecMu','PATEleMuPairProducer','smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMantiIso2.addDiCandidateModule('antiIso2MMEMzzCands','PATMuMuEleMuQuadProducer','antiIso2MMEMosDiMuons','antiIso2MMEMelecMu','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMantiIso2.addCrossCleanerModule('antiIso2MMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEMantiIso2.addSelector('antiIso2MMEMzzCleanedMuID','PATMuMuEleMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMEMLeadingZMuID')
MMEMantiIso2.addSelector('antiIso2MMEMzzMuIso','PATMuMuEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMEMLeadingZMuIso')
MMEMantiIso2.addSelector('antiIso2MMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','MMEMThirdMuID')
MMEMantiIso2.addSelector('antiIso2MMEMzzEleId','PATMuMuEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','MMEMEleCiCLoose') 
MMEMantiIso2.addSelector('antiIso2MMEMPt','PATMuMuEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','MMEMPt')
MMEMantiIso2.addSelector('antiIso2MMEMz2Charge','PATMuMuEleMuQuadSelector','leg2.charge()==0','MMEMEleIso')
MMEMantiIso2.addSorter('antiIso2MMEMSorted','PATMuMuEleMuQuadSorterByZMass')
MMEMantiIso2.addSelector('antiIso2MMEMzzdZ','PATMuMuEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEMdZ')
MMEMantiIso2.addSelector('MMEMantiIso2F','PATMuMuEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25','MMEMMuIso')
MMEMantiIso2Seq =MMEMantiIso2.returnSequence()

MMEMantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsMMEMBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEMantiIsoBoth.addDiCandidateModule('antiIsoBothMMEMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEMantiIsoBoth.addSelector('antiIsoBothMMEMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMEM DiMuonCreation',1)
MMEMantiIsoBoth.addDiCandidateModule('antiIsoBothMMEMelecMu','PATEleMuPairProducer','smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneDiTau',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMantiIsoBoth.addDiCandidateModule('antiIsoBothMMEMzzCands','PATMuMuEleMuQuadProducer','antiIsoBothMMEMosDiMuons','antiIsoBothMMEMelecMu','smearedMET','smearedJets',1,9999,text='MMEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEMantiIsoBoth.addCrossCleanerModule('antiIsoBothMMEMzzCleanedCands','PATMuMuEleMuQuadCrossCleaner',1,9999,text='MMEMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEMantiIsoBoth.addSelector('antiIsoBothMMEMzzCleanedMuID','PATMuMuEleMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMEMLeadingZMuID')
MMEMantiIsoBoth.addSelector('antiIsoBothMMEMzzMuIso','PATMuMuEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMEMLeadingZMuIso')
MMEMantiIsoBoth.addSelector('antiIsoBothMMEMzzCleanedThirdMuID','PATMuMuEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','MMEMThirdMuID')
MMEMantiIsoBoth.addSelector('antiIsoBothMMEMzzEleId','PATMuMuEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','MMEMEleCiCLoose')
MMEMantiIsoBoth.addSelector('antiIsoBothMMEMPt','PATMuMuEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','MMEMPt')
MMEMantiIsoBoth.addSorter('antiIsoBothMMEMSorted','PATMuMuEleMuQuadSorterByZMass')
MMEMantiIsoBoth.addSelector('antiIsoBothMMEMzzdZ','PATMuMuEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEMdZ')
MMEMantiIsoBoth.addSelector('MMEMantiIsoBothF','PATMuMuEleMuQuadSelector','leg2.charge()==0','MMEMEleIso')
#MMEMantiIsoBoth.addSelector('MMEMantiIsoBothF','PATMuMuEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()>0.25','MMEMMuIso')
MMEMantiIsoBothSeq =MMEMantiIsoBoth.returnSequence()


######################__________________________________MMEE_____________________________________##############################

MMEEantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsMMEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEantiIso1.addDiCandidateModule('antiIso1MMEEdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEEantiIso1.addSelector('antiIso1MMEEosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIso1MMEE DiMuonCreation',1)
MMEEantiIso1.addDiCandidateModule('antiIso1MMEEeleEle','PATElePairProducer','smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,9999,text='antiIso1MMEEAtLeastOneEleEle',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEantiIso1.addDiCandidateModule('antiIso1MMEEzzCands','PATMuMuEleEleQuadProducer','antiIso1MMEEosDiMuons','antiIso1MMEEeleEle','smearedMET','smearedJets',1,9999,text='antiIso1MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEantiIso1.addCrossCleanerModule('antiIso1MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='antiIso1MMEEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEEantiIso1.addSelector('antiIso1MMEEzzCleanedMuID','PATMuMuEleEleQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIso1MMEELeadingZMuID')
MMEEantiIso1.addSelector('antiIso1MMEEzzMuIso','PATMuMuEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1MMEELeadingZMuIso')
MMEEantiIso1.addSelector('antiIso1MMEEz2Charge','PATMuMuEleEleQuadSelector','leg2.charge()==0','antiIso1MMEEZEleIso')
MMEEantiIso1.addSelector('antiIso1MMEEPt','PATMuMuEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso1MMEEZEleIso')
MMEEantiIso1.addSorter('antiIso1MMEEsorted','PATMuMuEleEleQuadSorterByZMass')
MMEEantiIso1.addSelector('antiIso1MMEEzzdZ','PATMuMuEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEEdZ')
MMEEantiIso1.addSelector('MMEEnoIsoOSF','PATMuMuEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','antiIso1MMEEEleCiCTight') 
MMEEantiIso1.addSelector('MMEEantiIso1F','PATMuMuEleEleQuadSelector','(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','antiIso1MMEEZEleIso')
MMEEantiIso1Seq =MMEEantiIso1.returnSequence()

MMEEnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsMMEESS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEnoIsoSS.addDiCandidateModule('noIsoSSMMEEdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEEnoIsoSS.addSelector('noIsoSSMMEEosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','noIsoSSMMEE DiMuonCreation',1)
MMEEnoIsoSS.addDiCandidateModule('noIsoSSMMEEeleEle','PATElePairProducer','smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,9999,text='noIsoSSMMEEAtLeastOneEleEle',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEnoIsoSS.addDiCandidateModule('noIsoSSMMEEzzCands','PATMuMuEleEleQuadProducer','noIsoSSMMEEosDiMuons','noIsoSSMMEEeleEle','smearedMET','smearedJets',1,9999,text='noIsoSSMMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEnoIsoSS.addCrossCleanerModule('noIsoSSMMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='noIsoSSMMEEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEEnoIsoSS.addSelector('noIsoSSMMEEzzCleanedMuID','PATMuMuEleEleQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','noIsoSSMMEELeadingZMuID')
MMEEnoIsoSS.addSelector('noIsoSSMMEEzzMuIso','PATMuMuEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSMMEELeadingZMuIso')
MMEEnoIsoSS.addSelector('noIsoSSMMEEz2Charge','PATMuMuEleEleQuadSelector','leg2.charge()!=0','noIsoSSMMEEZEleIso')
MMEEnoIsoSS.addSorter('noIsoSSMMEEsorted','PATMuMuEleEleQuadSorterByZMass')
MMEEnoIsoSS.addSelector('noIsoSSMMEEzzdZ','PATMuMuEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEEdZ')
MMEEnoIsoSS.addSelector('MMEEnoIsoSSF','PATMuMuEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','noIsoSSMMEEEleCiCTight') 
MMEEnoIsoSS.addSelector('MMEEnoIsoSScheckF','PATMuMuEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','noIsoSSMMEEEleCiCTight') 
MMEEnoIsoSSSeq =MMEEnoIsoSS.returnSequence()

MMEEantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsMMEE2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEantiIso2.addDiCandidateModule('antiIso2MMEEdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEEantiIso2.addSelector('antiIso2MMEEosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIso2MMEE DiMuonCreation',1)
MMEEantiIso2.addDiCandidateModule('antiIso2MMEEeleEle','PATElePairProducer','smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,9999,text='antiIso2MMEEAtLeastOneEleEle',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEantiIso2.addDiCandidateModule('antiIso2MMEEzzCands','PATMuMuEleEleQuadProducer','antiIso2MMEEosDiMuons','antiIso2MMEEeleEle','smearedMET','smearedJets',1,9999,text='antiIso2MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEantiIso2.addCrossCleanerModule('antiIso2MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='antiIso2MMEEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEEantiIso2.addSelector('antiIso2MMEEzzCleanedMuID','PATMuMuEleEleQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIso2MMEELeadingZMuID')
MMEEantiIso2.addSelector('antiIso2MMEEzzMuIso','PATMuMuEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2MMEELeadingZMuIso')
MMEEantiIso2.addSelector('antiIso2MMEEnoIsoF2','PATMuMuEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','antiIso2MMEEEleCiCTight') 
MMEEantiIso2.addSelector('antiIso2MMEEPt','PATMuMuEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso2MMEEZEleIso')
MMEEantiIso2.addSelector('antiIso2MMEEz2Charge','PATMuMuEleEleQuadSelector','leg2.charge()==0','antiIso2MMEEZEleIso')
MMEEantiIso2.addSorter('antiIso2MMEEsorted','PATMuMuEleEleQuadSorterByZMass')
MMEEantiIso2.addSelector('antiIso2MMEEzzdZ','PATMuMuEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEEdZ')
MMEEantiIso2.addSelector('MMEEantiIso2F','PATMuMuEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25','antiIso2MMEEZEleIso')
MMEEantiIso2Seq =MMEEantiIso2.returnSequence()

MMEEantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsMMEEBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEantiIsoBoth.addDiCandidateModule('antiIsoBothMMEEdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMEEantiIsoBoth.addSelector('antiIsoBothMMEEosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothMMEE DiMuonCreation',1)
MMEEantiIsoBoth.addDiCandidateModule('antiIsoBothMMEEeleEle','PATElePairProducer','smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,9999,text='antiIsoBothMMEEAtLeastOneEleEle',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEantiIsoBoth.addDiCandidateModule('antiIsoBothMMEEzzCands','PATMuMuEleEleQuadProducer','antiIsoBothMMEEosDiMuons','antiIsoBothMMEEeleEle','smearedMET','smearedJets',1,9999,text='antiIsoBothMMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEantiIsoBoth.addCrossCleanerModule('antiIsoBothMMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='antiIsoBothMMEEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEEantiIsoBoth.addSelector('antiIsoBothMMEEzzCleanedMuID','PATMuMuEleEleQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIsoBothMMEELeadingZMuID')
MMEEantiIsoBoth.addSelector('antiIsoBothMMEEzzMuIso','PATMuMuEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothMMEELeadingZMuIso')
MMEEantiIsoBoth.addSelector('antiIsoBothMMEEnoIsoF2','PATMuMuEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','antiIsoBothMMEEEleCiCTight') 
MMEEantiIsoBoth.addSelector('antiIsoBothMMEEPt','PATMuMuEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIsoBothMMEEZEleIso')
MMEEantiIsoBoth.addSorter('antiIsoBothMMEEsorted','PATMuMuEleEleQuadSorterByZMass')
MMEEantiIsoBoth.addSelector('antiIsoBothMMEEzzdZ','PATMuMuEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEEdZ')
MMEEantiIsoBoth.addSelector('MMEEantiIsoBothF','PATMuMuEleEleQuadSelector','leg2.charge()==0','antiIsoBothMMEEZEleIso')
#MMEEantiIsoBoth.addSelector('MMEEantiIsoBothF','PATMuMuEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()>0.25','antiIsoBothMMEEZEleIso')
MMEEantiIsoBothSeq =MMEEantiIsoBoth.returnSequence()


######################__________________________________MMMM_____________________________________##############################

MMMMantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsMMMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMMantiIso1.addDiCandidateModule('antiIso1MMMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMMantiIso1.addSelector('antiIso1MMMMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIso1MMMM DiMuonCreation',1)
MMMMantiIso1.addDiCandidateModule('antiIso1MMMMzzCands','PATMuMuMuMuQuadProducer','antiIso1MMMMosDiMuons','antiIso1MMMMdiMuons','smearedMET','smearedJets',1,9999,text='antiIso1MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMMantiIso1.addCrossCleanerModule('antiIso1MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='antiIso1MMMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMMantiIso1.addSelector('antiIso1MMMMzzCleanedMuID','PATMuMuMuMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIso1MMMMLeadingZMuID')
MMMMantiIso1.addSelector('antiIso1MMMMzzMuIso','PATMuMuMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1MMMMLeadingZMuIso')
MMMMantiIso1.addSelector('antiIso1MMMMz2Charge','PATMuMuMuMuQuadSelector','leg2.charge()==0','antiIso1MMMMsecondPairID')
MMMMantiIso1.addSelector('antiIso1MMMMpt','PATMuMuMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso1MMMMsecondPairID')
MMMMantiIso1.addSorter('antiIso1MMMMsorted','PATMuMuMuMuQuadSorterByZMass')
MMMMantiIso1.addSelector('antiIso1MMMMzzdZ','PATMuMuMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMMdZ')
MMMMantiIso1.addSelector('MMMMnoIsoOSF','PATMuMuMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','antiIso1MMMMsecondPairID')
MMMMantiIso1.addSelector('MMMMantiIso1F','PATMuMuMuMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','antiIso1MMMMSecondZMuIso')
MMMMantiIso1Seq =MMMMantiIso1.returnSequence()

MMMMnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsMMMMSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMMnoIsoSS.addDiCandidateModule('noIsoSSMMMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMMnoIsoSS.addSelector('noIsoSSMMMMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','noIsoSSMMMM DiMuonCreation',1)
MMMMnoIsoSS.addDiCandidateModule('noIsoSSMMMMzzCands','PATMuMuMuMuQuadProducer','noIsoSSMMMMosDiMuons','noIsoSSMMMMdiMuons','smearedMET','smearedJets',1,9999,text='noIsoSSMMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMMnoIsoSS.addSelector('noIsoSSMMMMz1Charge','PATMuMuMuMuQuadSelector','leg1.charge()==0','noIsoSSMMMMz1Charge')
MMMMnoIsoSS.addCrossCleanerModule('noIsoSSMMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='noIsoSSMMMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMMnoIsoSS.addSelector('noIsoSSMMMMzzCleanedMuID','PATMuMuMuMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','noIsoSSMMMMLeadingZMuID')
MMMMnoIsoSS.addSelector('noIsoSSMMMMzzMuIso','PATMuMuMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSMMMMLeadingZMuIso')
MMMMnoIsoSS.addSelector('noIsoSSMMMMz2Charge','PATMuMuMuMuQuadSelector','leg2.charge()!=0','noIsoSSMMMMsecondPairID')
MMMMnoIsoSS.addSorter('noIsoSSMMMMsorted','PATMuMuMuMuQuadSorterByZMass')
MMMMnoIsoSS.addSelector('noIsoSSMMMMzzdZ','PATMuMuMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMMdZ')
MMMMnoIsoSS.addSelector('MMMMnoIsoSSF','PATMuMuMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','noIsoSSMMMMsecondPairID')
MMMMnoIsoSS.addSelector('MMMMnoIsoSScheckF','PATMuMuMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','noIsoSSMMMMsecondPairID')
MMMMnoIsoSSSeq =MMMMnoIsoSS.returnSequence()

MMMMantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsMMMM2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMMantiIso2.addDiCandidateModule('antiIso2MMMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMMantiIso2.addSelector('antiIso2MMMMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIso2MMMM DiMuonCreation',1)
MMMMantiIso2.addDiCandidateModule('antiIso2MMMMzzCands','PATMuMuMuMuQuadProducer','antiIso2MMMMosDiMuons','antiIso2MMMMdiMuons','smearedMET','smearedJets',1,9999,text='antiIso2MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMMantiIso2.addCrossCleanerModule('antiIso2MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='antiIso2MMMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMMantiIso2.addSelector('antiIso2MMMMzzCleanedMuID','PATMuMuMuMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIso2MMMMLeadingZMuID')
MMMMantiIso2.addSelector('antiIso2MMMMzzMuIso','PATMuMuMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2MMMMLeadingZMuIso')
MMMMantiIso2.addSelector('antiIso2MMMMnoIsoF','PATMuMuMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','antiIso2MMMMsecondPairID')
MMMMantiIso2.addSelector('antiIso2MMMMpt','PATMuMuMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso2MMMMsecondPairID')
MMMMantiIso2.addSelector('antiIso2MMMMz2Charge','PATMuMuMuMuQuadSelector','leg2.charge()==0','antiIso2MMMMsecondPairID')
MMMMantiIso2.addSorter('antiIso2MMMMsorted','PATMuMuMuMuQuadSorterByZMass')
MMMMantiIso2.addSelector('antiIso2MMMMzzdZ','PATMuMuMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMMdZ')
MMMMantiIso2.addSelector('MMMMantiIso2F','PATMuMuMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25','antiIsoMMMMSecondZMuIso')
MMMMantiIso2Seq =MMMMantiIso2.returnSequence()

MMMMantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsMMMMBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMMantiIsoBoth.addDiCandidateModule('antiIsoBothMMMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1,genParticles='genDaughters')
MMMMantiIsoBoth.addSelector('antiIsoBothMMMMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>60&&mass<120 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothMMMM DiMuonCreation',1)
MMMMantiIsoBoth.addDiCandidateModule('antiIsoBothMMMMzzCands','PATMuMuMuMuQuadProducer','antiIsoBothMMMMosDiMuons','antiIsoBothMMMMdiMuons','smearedMET','smearedJets',1,9999,text='antiIsoBothMMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMMantiIsoBoth.addCrossCleanerModule('antiIsoBothMMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='antiIsoBothMMMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMMantiIsoBoth.addSelector('antiIsoBothMMMMzzCleanedMuID','PATMuMuMuMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','antiIsoBothMMMMLeadingZMuID')
MMMMantiIsoBoth.addSelector('antiIsoBothMMMMzzMuIso','PATMuMuMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothMMMMLeadingZMuIso')
MMMMantiIsoBoth.addSelector('antiIsoBothMMMMnoIsoF','PATMuMuMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','antiIsoBothMMMMsecondPairID')
MMMMantiIsoBoth.addSelector('antiIsoBothMMMMpt','PATMuMuMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIsoBothMMMMsecondPairID')
MMMMantiIsoBoth.addSorter('antiIsoBothMMMMsorted','PATMuMuMuMuQuadSorterByZMass')
MMMMantiIsoBoth.addSelector('antiIsoBothMMMMzzdZ','PATMuMuMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMMdZ')
MMMMantiIsoBoth.addSelector('MMMMantiIsoBothF','PATMuMuMuMuQuadSelector','leg2.charge()==0','antiIsoBothMMMMsecondPairID')
#MMMMantiIsoBoth.addSelector('MMMMantiIsoBothF','PATMuMuMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()>0.25','antiIsoMMMMSecondZMuIso')
MMMMantiIsoBothSeq =MMMMantiIsoBoth.returnSequence()

######################__________________________________EEMT_____________________________________##############################

EEMTantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsEEMT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEMTantiIso1.addDiCandidateModule('antiIso1EEMTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMTantiIso1.addSelector('antiIso1EEMTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso1EEMTDiEleCreation',1)
EEMTantiIso1.addDiCandidateModule('antiIso1EEMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIso1EEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTantiIso1.addDiCandidateModule('antiIso1EEMTzzCands','PATEleEleMuTauQuadProducer','antiIso1EEMTosDiElectrons','antiIso1EEMTmuTau','smearedMET','smearedJets',1,9999,text='antiIso1EEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMTantiIso1.addCrossCleanerModule('antiIso1EEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='antiIso1EEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTantiIso1.addSelector('antiIso1EEMTzzEleIso','PATEleEleMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1EEMTLeadingZEleIso')
EEMTantiIso1.addSelector('antiIso1EEMTzzCleanedmuID','PATEleEleMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','antiIso1EEMTMuID')
EEMTantiIso1.addSelector('antiIso1EEMTz2Charge','PATEleEleMuTauQuadSelector','leg2.charge()==0','antiIso1EEMTMuID')
EEMTantiIso1.addSelector('antiIso1EEMTpt','PATEleEleMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','antiIso1EEMTMuID')
EEMTantiIso1.addSorter('antiIso1EEMTsorted','PATEleEleMuTauQuadSorterByZMass')
EEMTantiIso1.addSelector('antiIso1EEMTzzdZ','PATEleEleMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMTdZ')
EEMTantiIso1.addSelector('EEMTnoIsoOSF','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIso1EEMTDecayModeFinding')
EEMTantiIso1.addSelector('EEMTantiIso1F','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','antiIso1EEMTTauLooseIsolation')
EEMTantiIso1Seq =EEMTantiIso1.returnSequence()

EEMTnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsEEMTSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEMTnoIsoSS.addDiCandidateModule('noIsoSSEEMTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMTnoIsoSS.addSelector('noIsoSSEEMTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','noIsoSSEEMTDiEleCreation',1)
EEMTnoIsoSS.addDiCandidateModule('noIsoSSEEMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'noIsoSSEEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTnoIsoSS.addDiCandidateModule('noIsoSSEEMTzzCands','PATEleEleMuTauQuadProducer','noIsoSSEEMTosDiElectrons','noIsoSSEEMTmuTau','smearedMET','smearedJets',1,9999,text='noIsoSSEEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMTnoIsoSS.addCrossCleanerModule('noIsoSSEEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='noIsoSSEEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTnoIsoSS.addSelector('noIsoSSEEMTzzEleIso','PATEleEleMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSEEMTLeadingZEleIso')
EEMTnoIsoSS.addSelector('noIsoSSEEMTzzCleanedmuID','PATEleEleMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','noIsoSSEEMTMuID')
EEMTnoIsoSS.addSelector('noIsoSSEEMTz2Charge','PATEleEleMuTauQuadSelector','leg2.charge()!=0','noIsoSSEEMTMuID')
EEMTnoIsoSS.addSelector('noIsoSSEEMTz2pt','PATEleEleMuTauQuadSelector','leg2.leg1.pt()>10','noIsoSSEEMTMuID')
EEMTnoIsoSS.addSorter('noIsoSSEEMTsorted','PATEleEleMuTauQuadSorterByZMass')
EEMTnoIsoSS.addSelector('noIsoSSEEMTzzdZ','PATEleEleMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMTdZ')
EEMTnoIsoSS.addSelector('EEMTnoIsoSSF','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','noIsoSSEEMTDecayModeFinding')
EEMTnoIsoSS.addSelector('EEMTnoIsoSScheckF','PATEleEleMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','noIsoSSEEMTDecayModeFinding')
EEMTnoIsoSSSeq =EEMTnoIsoSS.returnSequence()

EEMTantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsEEMT2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEMTantiIso2.addDiCandidateModule('antiIso2EEMTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMTantiIso2.addSelector('antiIso2EEMTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso2EEMTDiEleCreation',1)
EEMTantiIso2.addDiCandidateModule('antiIso2EEMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIso2EEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTantiIso2.addDiCandidateModule('antiIso2EEMTzzCands','PATEleEleMuTauQuadProducer','antiIso2EEMTosDiElectrons','antiIso2EEMTmuTau','smearedMET','smearedJets',1,9999,text='antiIso2EEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMTantiIso2.addCrossCleanerModule('antiIso2EEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='antiIso2EEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTantiIso2.addSelector('antiIso2EEMTzzEleIso','PATEleEleMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2EEMTLeadingZEleIso')
EEMTantiIso2.addSelector('antiIso2EEMTzzCleanedmuID','PATEleEleMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','antiIso2EEMTMuID')
EEMTantiIso2.addSelector('antiIso2EEMTzzTauID','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIso2EEMTDecayModeFinding')
EEMTantiIso2.addSelector('antiIso2EEMTpt','PATEleEleMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','antiIso2EEMTMuID')
EEMTantiIso2.addSelector('antiIso2EEMTz2Charge','PATEleEleMuTauQuadSelector','leg2.charge()==0','antiIso2EEMTMuID')
EEMTantiIso2.addSorter('antiIso2EEMTsorted','PATEleEleMuTauQuadSorterByZMass')
EEMTantiIso2.addSelector('antiIso2EEMTzzdZ','PATEleEleMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMTdZ')
EEMTantiIso2.addSelector('EEMTantiIso2F','PATEleEleMuTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.15','antiIsoEEMTSecondZMuIso')
EEMTantiIso2Seq =EEMTantiIso2.returnSequence()

EEMTantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsEEMTBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEMTantiIsoBoth.addDiCandidateModule('antiIsoBothEEMTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMTantiIsoBoth.addSelector('antiIsoBothEEMTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothEEMTDiEleCreation',1)
EEMTantiIsoBoth.addDiCandidateModule('antiIsoBothEEMTmuTau','PATMuTauPairProducer', 'smearedMuons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIsoBothEEMTAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEMTantiIsoBoth.addDiCandidateModule('antiIsoBothEEMTzzCands','PATEleEleMuTauQuadProducer','antiIsoBothEEMTosDiElectrons','antiIsoBothEEMTmuTau','smearedMET','smearedJets',1,9999,text='antiIsoBothEEMTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMTantiIsoBoth.addCrossCleanerModule('antiIsoBothEEMTzzCleanedCands','PATEleEleMuTauQuadCrossCleaner',1,9999,text='antiIsoBothEEMTAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMTantiIsoBoth.addSelector('antiIsoBothEEMTzzEleIso','PATEleEleMuTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothEEMTLeadingZEleIso')
EEMTantiIsoBoth.addSelector('antiIsoBothEEMTzzCleanedmuID','PATEleEleMuTauQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg1.isTrackerMuon()','antiIsoBothEEMTMuID')
EEMTantiIsoBoth.addSelector('antiIsoBothEEMTzzTauID','PATEleEleMuTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIsoBothEEMTDecayModeFinding')
EEMTantiIsoBoth.addSelector('antiIsoBothEEMTpt','PATEleEleMuTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','antiIsoBothEEMTMuID')
EEMTantiIsoBoth.addSorter('antiIsoBothEEMTsorted','PATEleEleMuTauQuadSorterByZMass')
EEMTantiIsoBoth.addSelector('antiIsoBothEEMTzzdZ','PATEleEleMuTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMTdZ')
EEMTantiIsoBoth.addSelector('EEMTantiIsoBothF','PATEleEleMuTauQuadSelector','leg2.charge()==0','antiIsoBothEEMTMuID')
#EEMTantiIsoBoth.addSelector('EEMTantiIsoBothF','PATEleEleMuTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.15&&!leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','antiIsoEEMTSecondZMuIso')
EEMTantiIsoBothSeq =EEMTantiIsoBoth.returnSequence()


######################__________________________________EEET_____________________________________##############################

EEETantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsEEET',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEETantiIso1.addDiCandidateModule('antiIso1EEETdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEETantiIso1.addSelector('antiIso1EEETosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso1EEETDiEleCreation',1)
EEETantiIso1.addDiCandidateModule('antiIso1EEETeleTau','PATEleTauPairProducer', 'smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIso1EEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETantiIso1.addDiCandidateModule('antiIso1EEETzzCands','PATEleEleEleTauQuadProducer','antiIso1EEETosDiElectrons','antiIso1EEETeleTau','smearedMET','smearedJets',1,9999,text='antiIso1EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEETantiIso1.addCrossCleanerModule('antiIso1EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='antiIso1EEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETantiIso1.addSelector('antiIso1EEETzzEleIso','PATEleEleEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1EEETLeadingZEleIso')
EEETantiIso1.addSelector('antiIso1EEETzzCleanedThirdeleID','PATEleEleEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIso1EEETTightThirdEleCiCTight')
EEETantiIso1.addSelector('antiIso1EEETz2Charge','PATEleEleEleTauQuadSelector','leg2.charge()==0','antiIso1EEETDecayModeFinding')
EEETantiIso1.addSelector('antiIso1EEETpt','PATEleEleEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','antiIso1EEETDecayModeFinding')
EEETantiIso1.addSorter('antiIso1EEETsorted','PATEleEleEleTauQuadSorterByZMass')
EEETantiIso1.addSelector('antiIso1EEETzzdZ','PATEleEleEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEETdZ')
EEETantiIso1.addSelector('EEETnoIsoOSF','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIso1EEETDecayModeFinding')
EEETantiIso1.addSelector('EEETantiIso1F','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','antiIso1EEETTauLooseIsolation')
EEETantiIso1Seq =EEETantiIso1.returnSequence()

EEETnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsEEETSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEETnoIsoSS.addDiCandidateModule('noIsoSSEEETdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEETnoIsoSS.addSelector('noIsoSSEEETosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','noIsoSSEEETDiEleCreation',1)
EEETnoIsoSS.addDiCandidateModule('noIsoSSEEETeleTau','PATEleTauPairProducer', 'smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'noIsoSSEEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETnoIsoSS.addDiCandidateModule('noIsoSSEEETzzCands','PATEleEleEleTauQuadProducer','noIsoSSEEETosDiElectrons','noIsoSSEEETeleTau','smearedMET','smearedJets',1,9999,text='noIsoSSEEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEETnoIsoSS.addCrossCleanerModule('noIsoSSEEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='noIsoSSEEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETnoIsoSS.addSelector('noIsoSSEEETzzEleIso','PATEleEleEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSEEETLeadingZEleIso')
EEETnoIsoSS.addSelector('noIsoSSEEETzzCleanedThirdeleID','PATEleEleEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','noIsoSSEEETTightThirdEleCiCTight')
EEETnoIsoSS.addSelector('noIsoSSEEETz2Charge','PATEleEleEleTauQuadSelector','leg2.charge()!=0','noIsoSSEEETDecayModeFinding')
EEETnoIsoSS.addSelector('noIsoSSEEETz2pt','PATEleEleEleTauQuadSelector','leg2.leg1.pt()>10','noIsoSSEEETDecayModeFinding')
EEETnoIsoSS.addSorter('noIsoSSEEETsorted','PATEleEleEleTauQuadSorterByZMass')
EEETnoIsoSS.addSelector('noIsoSSEEETzzdZ','PATEleEleEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEETdZ')
EEETnoIsoSS.addSelector('EEETnoIsoSSF','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','noIsoSSEEETDecayModeFinding')
EEETnoIsoSS.addSelector('EEETnoIsoSScheckF','PATEleEleEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','noIsoSSEEETDecayModeFinding')
EEETnoIsoSSSeq =EEETnoIsoSS.returnSequence()

EEETantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsEEET2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEETantiIso2.addDiCandidateModule('antiIso2EEETdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEETantiIso2.addSelector('antiIso2EEETosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso2EEETDiEleCreation',1)
EEETantiIso2.addDiCandidateModule('antiIso2EEETeleTau','PATEleTauPairProducer', 'smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIso2EEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETantiIso2.addDiCandidateModule('antiIso2EEETzzCands','PATEleEleEleTauQuadProducer','antiIso2EEETosDiElectrons','antiIso2EEETeleTau','smearedMET','smearedJets',1,9999,text='antiIso2EEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEETantiIso2.addCrossCleanerModule('antiIso2EEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='antiIso2EEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETantiIso2.addSelector('antiIso2EEETzzEleIso','PATEleEleEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2EEETLeadingZEleIso')
EEETantiIso2.addSelector('antiIso2EEETzzCleanedThirdeleID','PATEleEleEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIso2EEETTightThirdEleCiCTight')
EEETantiIso2.addSelector('antiIso2EEETzzTauID','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIso2EEETDecayModeFinding')
EEETantiIso2.addSelector('antiIso2EEETpt','PATEleEleEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','antiIso2EEETDecayModeFinding')
EEETantiIso2.addSelector('antiIso2EEETz2Charge','PATEleEleEleTauQuadSelector','leg2.charge()==0','antiIso2EEETDecayModeFinding')
EEETantiIso2.addSorter('antiIso2EEETsorted','PATEleEleEleTauQuadSorterByZMass')
EEETantiIso2.addSelector('antiIso2EEETzzdZ','PATEleEleEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEETdZ')
EEETantiIso2.addSelector('EEETantiIso2F','PATEleEleEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.10','antiIsoEEETSecondZEleIso')
EEETantiIso2Seq =EEETantiIso2.returnSequence()

EEETantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsEEETBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EEETantiIsoBoth.addDiCandidateModule('antiIsoBothEEETdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEETantiIsoBoth.addSelector('antiIsoBothEEETosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothEEETDiEleCreation',1)
EEETantiIsoBoth.addDiCandidateModule('antiIsoBothEEETeleTau','PATEleTauPairProducer', 'smearedElectrons','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIsoBothEEETAtLeastOneEleTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEETantiIsoBoth.addDiCandidateModule('antiIsoBothEEETzzCands','PATEleEleEleTauQuadProducer','antiIsoBothEEETosDiElectrons','antiIsoBothEEETeleTau','smearedMET','smearedJets',1,9999,text='antiIsoBothEEETAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEETantiIsoBoth.addCrossCleanerModule('antiIsoBothEEETzzCleanedCands','PATEleEleEleTauQuadCrossCleaner',1,9999,text='antiIsoBothEEETAtLeastOneZZCleanedCandidate',dR = 0.1)
EEETantiIsoBoth.addSelector('antiIsoBothEEETzzEleIso','PATEleEleEleTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothEEETLeadingZEleIso')
EEETantiIsoBoth.addSelector('antiIsoBothEEETzzCleanedThirdeleID','PATEleEleEleTauQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIsoBothEEETTightThirdEleCiCTight')
EEETantiIsoBoth.addSelector('antiIsoBothEEETzzTauID','PATEleEleEleTauQuadSelector','leg2.leg2.tauID("decayModeFinding")','antiIsoBothEEETDecayModeFinding')
EEETantiIsoBoth.addSelector('antiIsoBothEEETpt','PATEleEleEleTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>20','antiIsoBothEEETDecayModeFinding')
EEETantiIsoBoth.addSorter('antiIsoBothEEETsorted','PATEleEleEleTauQuadSorterByZMass')
EEETantiIsoBoth.addSelector('antiIsoBothEEETzzdZ','PATEleEleEleTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEETdZ')
EEETantiIsoBoth.addSelector('EEETantiIsoBothF','PATEleEleEleTauQuadSelector','leg2.charge()==0','antiIsoBothEEETDecayModeFinding')
#EEETantiIsoBoth.addSelector('EEETantiIsoBothF','PATEleEleEleTauQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.10&&!leg2.leg2.tauID("byLooseCombinedIsolationDeltaBetaCorr")','antiIsoEEETSecondZEleIso')
EEETantiIsoBothSeq =EEETantiIsoBoth.returnSequence()


######################__________________________________EETT_____________________________________##############################

EETTantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsEETT',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EETTantiIso1.addDiCandidateModule('antiIso1EETTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EETTantiIso1.addSelector('antiIso1EETTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso1EETTDiEleCreation',1)
EETTantiIso1.addDiCandidateModule('antiIso1EETTtauTau','PATDiTauPairProducer', 'smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIso1EETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTantiIso1.addDiCandidateModule('antiIso1EETTzzCands','PATEleEleTauTauQuadProducer','antiIso1EETTosDiElectrons','antiIso1EETTtauTau','smearedMET','smearedJets',1,9999,text='antiIso1EETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EETTantiIso1.addCrossCleanerModule('antiIso1EETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='antiIso1EETTAtLeastOneZZCleanedCandidate',dR = 0.1)
EETTantiIso1.addSelector('antiIso1EETTzzEleIso','PATEleEleTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1EETTLeadingZEleIso')
EETTantiIso1.addSelector('antiIso1EETTz2Charge','PATEleEleTauTauQuadSelector','leg2.charge()==0','antiIso1EETTDecayModeFinding')
EETTantiIso1.addSelector('antiIso1EETTpt','PATEleEleTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','antiIso1EETTDecayModeFinding')
EETTantiIso1.addSorter('antiIso1EETTsorted','PATEleEleTauTauQuadSorterByZMass')
EETTantiIso1.addSelector('antiIso1EETTzzdZ','PATEleEleTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EETTdZ')
EETTantiIso1.addSelector('EETTnoIsoOSF','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','antiIso1EETTDecayModeFinding')
EETTantiIso1.addSelector('EETTantiIso1F','PATEleEleTauTauQuadSelector','leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','antiIso1EETTTauLooseIsolation')
EETTantiIso1Seq =EETTantiIso1.returnSequence()

EETTnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsEETTSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EETTnoIsoSS.addDiCandidateModule('noIsoSSEETTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EETTnoIsoSS.addSelector('noIsoSSEETTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','noIsoSSEETTDiEleCreation',1)
EETTnoIsoSS.addDiCandidateModule('noIsoSSEETTtauTau','PATDiTauPairProducer', 'smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text = 'noIsoSSEETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTnoIsoSS.addDiCandidateModule('noIsoSSEETTzzCands','PATEleEleTauTauQuadProducer','noIsoSSEETTosDiElectrons','noIsoSSEETTtauTau','smearedMET','smearedJets',1,9999,text='noIsoSSEETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EETTnoIsoSS.addCrossCleanerModule('noIsoSSEETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='noIsoSSEETTAtLeastOneZZCleanedCandidate',dR = 0.1)
EETTnoIsoSS.addSelector('noIsoSSEETTzzEleIso','PATEleEleTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSEETTLeadingZEleIso')
EETTnoIsoSS.addSelector('noIsoSSEETTz2Charge','PATEleEleTauTauQuadSelector','leg2.charge()!=0','noIsoSSEETTDecayModeFinding')
EETTnoIsoSS.addSelector('noIsoSSEETTz1Pt','PATEleEleTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10','noIsoSSEETTDecayModeFinding')
EETTnoIsoSS.addSelector('noIsoSSEETTz2Pt','PATEleEleTauTauQuadSelector','leg2.leg1.pt()>10&&leg2.leg2.pt()>10','noIsoSSEETTDecayModeFinding')
EETTnoIsoSS.addSorter('noIsoSSEETTsorted','PATEleEleTauTauQuadSorterByZMass')
EETTnoIsoSS.addSelector('noIsoSSEETTzzdZ','PATEleEleTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EETTdZ')
EETTnoIsoSS.addSelector('EETTnoIsoSSF','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','noIsoSSEETTDecayModeFinding')
EETTnoIsoSS.addSelector('EETTnoIsoSScheckF','PATEleEleTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','noIsoSSEETTDecayModeFinding')
EETTnoIsoSSSeq =EETTnoIsoSS.returnSequence()

EETTantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsEETT2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EETTantiIso2.addDiCandidateModule('antiIso2EETTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EETTantiIso2.addSelector('antiIso2EETTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso2EETTDiEleCreation',1)
EETTantiIso2.addDiCandidateModule('antiIso2EETTtauTau','PATDiTauPairProducer', 'smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIso2EETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTantiIso2.addDiCandidateModule('antiIso2EETTzzCands','PATEleEleTauTauQuadProducer','antiIso2EETTosDiElectrons','antiIso2EETTtauTau','smearedMET','smearedJets',1,9999,text='antiIso2EETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EETTantiIso2.addCrossCleanerModule('antiIso2EETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='antiIso2EETTAtLeastOneZZCleanedCandidate',dR = 0.1)
EETTantiIso2.addSelector('antiIso2EETTzzEleIso','PATEleEleTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2EETTLeadingZEleIso')
EETTantiIso2.addSelector('antiIso2EETTzzTauID','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','antiIso2EETTDecayModeFinding')
EETTantiIso2.addSelector('antiIso2EETTpt','PATEleEleTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','antiIso2EETTDecayModeFinding')
EETTantiIso2.addSelector('antiIso2EETTz2Charge','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','antiIso2EETTDecayModeFinding')
EETTantiIso2.addSorter('antiIso2EETTsorted','PATEleEleTauTauQuadSorterByZMass')
EETTantiIso2.addSelector('antiIso2EETTzzdZ','PATEleEleTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EETTdZ')
EETTantiIso2.addSelector('EETTantiIso2F','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("byMediumCombinedIsolationDeltaBetaCorr")','antiIsoEETTTauLooseIsolation')
EETTantiIso2Seq =EETTantiIso2.returnSequence()

EETTantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsEETTBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

EETTantiIsoBoth.addDiCandidateModule('antiIsoBothEETTdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EETTantiIsoBoth.addSelector('antiIsoBothEETTosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothEETTDiEleCreation',1)
EETTantiIsoBoth.addDiCandidateModule('antiIsoBothEETTtauTau','PATDiTauPairProducer', 'smearedTaus','smearedTaus','smearedMET','smearedJets',1,9999,text = 'antiIsoBothEETTAtLeastOnediTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EETTantiIsoBoth.addDiCandidateModule('antiIsoBothEETTzzCands','PATEleEleTauTauQuadProducer','antiIsoBothEETTosDiElectrons','antiIsoBothEETTtauTau','smearedMET','smearedJets',1,9999,text='antiIsoBothEETTAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EETTantiIsoBoth.addCrossCleanerModule('antiIsoBothEETTzzCleanedCands','PATEleEleTauTauQuadCrossCleaner',1,9999,text='antiIsoBothEETTAtLeastOneZZCleanedCandidate',dR = 0.1)
EETTantiIsoBoth.addSelector('antiIsoBothEETTzzEleIso','PATEleEleTauTauQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothEETTLeadingZEleIso')
EETTantiIsoBoth.addSelector('antiIsoBothEETTzzTauID','PATEleEleTauTauQuadSelector','leg2.leg1.tauID("decayModeFinding")&&leg2.leg2.tauID("decayModeFinding")','antiIsoBothEETTDecayModeFinding')
EETTantiIsoBoth.addSelector('antiIsoBothEETTpt','PATEleEleTauTauQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>20&&leg2.leg2.pt()>20','antiIsoBothEETTDecayModeFinding')
EETTantiIsoBoth.addSorter('antiIsoBothEETTsorted','PATEleEleTauTauQuadSorterByZMass')
EETTantiIsoBoth.addSelector('antiIsoBothEETTzzdZ','PATEleEleTauTauQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EETTdZ')
EETTantiIsoBoth.addSelector('EETTantiIsoBothF','PATEleEleTauTauQuadSelector','leg2.charge()==0','antiIsoBothEETTDecayModeFinding')
#EETTantiIsoBoth.addSelector('EETTantiIsoBothF','PATEleEleTauTauQuadSelector','!leg2.leg1.tauID("byMediumCombinedIsolationDeltaBetaCorr")&&!leg2.leg2.tauID("byMediumCombinedIsolationDeltaBetaCorr")','antiIsoEETTTauLooseIsolation')
EETTantiIsoBothSeq =EETTantiIsoBoth.returnSequence()


######################__________________________________EEEM_____________________________________##############################

EEEMantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsEEEM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEMantiIso1.addDiCandidateModule('antiIso1EEEMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEMantiIso1.addSelector('antiIso1EEEMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso1EEEMDiEleCreation',1)
EEEMantiIso1.addDiCandidateModule('antiIso1EEEMeleMu','PATEleMuPairProducer', 'smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text = 'antiIso1EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEMantiIso1.addDiCandidateModule('antiIso1EEEMzzCands','PATEleEleEleMuQuadProducer','antiIso1EEEMosDiElectrons','antiIso1EEEMeleMu','smearedMET','smearedJets',1,9999,text='antiIso1EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEMantiIso1.addCrossCleanerModule('antiIso1EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='antiIso1EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEMantiIso1.addSelector('antiIso1EEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1EEEMLeadingZEleIso')
EEEMantiIso1.addSelector('antiIso1EEEMzzCleanedThirdeleID','PATEleEleEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIso1EEEMTightThirdEleCiCTight')
EEEMantiIso1.addSelector('antiIso1EEEMz2Charge','PATEleEleEleMuQuadSelector','leg2.charge()==0','antiIso1EEEMMuID')
EEEMantiIso1.addSelector('antiIso1EEEMpt','PATEleEleEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso1EEEMMuID')
EEEMantiIso1.addSorter('antiIso1EEEMsorted','PATEleEleEleMuQuadSorterByZMass')
EEEMantiIso1.addSelector('antiIso1EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEMdZ')
EEEMantiIso1.addSelector('EEEMnoIsoOSF','PATEleEleEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','antiIso1EEEMMuID')
EEEMantiIso1.addSelector('EEEMantiIso1F','PATEleEleEleMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','antiIso1EEEMSecondZMuIso')
EEEMantiIso1Seq =EEEMantiIso1.returnSequence()

EEEMnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsEEEMSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEMnoIsoSS.addDiCandidateModule('noIsoSSEEEMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEMnoIsoSS.addSelector('noIsoSSEEEMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','noIsoSSEEEMDiEleCreation',1)
EEEMnoIsoSS.addDiCandidateModule('noIsoSSEEEMeleMu','PATEleMuPairProducer', 'smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text = 'noIsoSSEEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEMnoIsoSS.addDiCandidateModule('noIsoSSEEEMzzCands','PATEleEleEleMuQuadProducer','noIsoSSEEEMosDiElectrons','noIsoSSEEEMeleMu','smearedMET','smearedJets',1,9999,text='noIsoSSEEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEMnoIsoSS.addCrossCleanerModule('noIsoSSEEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='noIsoSSEEEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEMnoIsoSS.addSelector('noIsoSSEEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSEEEMLeadingZEleIso')
EEEMnoIsoSS.addSelector('noIsoSSEEEMzzCleanedThirdeleID','PATEleEleEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','noIsoSSEEEMTightThirdEleCiCTight')
EEEMnoIsoSS.addSelector('noIsoSSEEEMz2Charge','PATEleEleEleMuQuadSelector','leg2.charge()!=0','noIsoSSEEEMMuID')
EEEMnoIsoSS.addSorter('noIsoSSEEEMsorted','PATEleEleEleMuQuadSorterByZMass')
EEEMnoIsoSS.addSelector('noIsoSSEEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEMdZ')
EEEMnoIsoSS.addSelector('EEEMnoIsoSSF','PATEleEleEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','noIsoSSEEEMMuID')
EEEMnoIsoSS.addSelector('EEEMnoIsoSScheckF','PATEleEleEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','noIsoSSEEEMMuID')
EEEMnoIsoSSSeq =EEEMnoIsoSS.returnSequence()

EEEMantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsEEEM2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEMantiIso2.addDiCandidateModule('antiIso2EEEMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEMantiIso2.addSelector('antiIso2EEEMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso2EEEMDiEleCreation',1)
EEEMantiIso2.addDiCandidateModule('antiIso2EEEMeleMu','PATEleMuPairProducer', 'smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text = 'antiIso2EEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEMantiIso2.addDiCandidateModule('antiIso2EEEMzzCands','PATEleEleEleMuQuadProducer','antiIso2EEEMosDiElectrons','antiIso2EEEMeleMu','smearedMET','smearedJets',1,9999,text='antiIso2EEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEMantiIso2.addCrossCleanerModule('antiIso2EEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='antiIso2EEEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEMantiIso2.addSelector('antiIso2EEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2EEEMLeadingZEleIso')
EEEMantiIso2.addSelector('antiIso2EEEMzzCleanedThirdeleID','PATEleEleEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIso2EEEMTightThirdEleCiCTight')
EEEMantiIso2.addSelector('antiIso2EEEMzzMuID','PATEleEleEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','antiIso2EEEMMuID')
EEEMantiIso2.addSelector('antiIso2EEEMpt','PATEleEleEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso2EEEMMuID')
EEEMantiIso2.addSelector('antiIso2EEEMz2Charge','PATEleEleEleMuQuadSelector','leg2.charge()==0','antiIso2EEEMMuID')
EEEMantiIso2.addSorter('antiIso2EEEMsorted','PATEleEleEleMuQuadSorterByZMass')
EEEMantiIso2.addSelector('antiIso2EEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEMdZ')
EEEMantiIso2.addSelector('EEEMantiIso2F','PATEleEleEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25','antiIsoEEEMSecondZEleIso')
EEEMantiIso2Seq =EEEMantiIso2.returnSequence()

EEEMantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsEEEMBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEMantiIsoBoth.addDiCandidateModule('antiIsoBothEEEMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEMantiIsoBoth.addSelector('antiIsoBothEEEMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothEEEMDiEleCreation',1)
EEEMantiIsoBoth.addDiCandidateModule('antiIsoBothEEEMeleMu','PATEleMuPairProducer', 'smearedElectrons','smearedMuons','smearedMET','smearedJets',1,9999,text = 'antiIsoBothEEEMAtLeastOneMuTau',leadingObjectsOnly = False,dR = 0.5,recoMode = "",genParticles='genDaughters')
EEEMantiIsoBoth.addDiCandidateModule('antiIsoBothEEEMzzCands','PATEleEleEleMuQuadProducer','antiIsoBothEEEMosDiElectrons','antiIsoBothEEEMeleMu','smearedMET','smearedJets',1,9999,text='antiIsoBothEEEMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEMantiIsoBoth.addCrossCleanerModule('antiIsoBothEEEMzzCleanedCands','PATEleEleEleMuQuadCrossCleaner',1,9999,text='antiIsoBothEEEMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEMantiIsoBoth.addSelector('antiIsoBothEEEMzzEleIso','PATEleEleEleMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothEEEMLeadingZEleIso')
EEEMantiIsoBoth.addSelector('antiIsoBothEEEMzzCleanedThirdeleID','PATEleEleEleMuQuadSelector','(leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)','antiIsoBothEEEMTightThirdEleCiCTight')
EEEMantiIsoBoth.addSelector('antiIsoBothEEEMzzMuID','PATEleEleEleMuQuadSelector','leg2.leg2.isGlobalMuon()&&leg2.leg2.isTrackerMuon()','antiIsoBothEEEMMuID')
EEEMantiIsoBoth.addSelector('antiIsoBothEEEMpt','PATEleEleEleMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIsoBothEEEMMuID')
EEEMantiIsoBoth.addSorter('antiIsoBothEEEMsorted','PATEleEleEleMuQuadSorterByZMass')
EEEMantiIsoBoth.addSelector('antiIsoBothEEEMzzdZ','PATEleEleEleMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEMdZ')
EEEMantiIsoBoth.addSelector('EEEMantiIsoBothF','PATEleEleEleMuQuadSelector','leg2.charge()==0','antiIsoBothEEEMMuID')
#EEEMantiIsoBoth.addSelector('EEEMantiIsoBothF','PATEleEleEleMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()>0.25','antiIsoEEEMSecondZEleIso')
EEEMantiIsoBothSeq =EEEMantiIsoBoth.returnSequence()


######################__________________________________EEEE_____________________________________##############################

EEEEantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsEEEE',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEEantiIso1.addDiCandidateModule('antiIso1EEEEdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEEantiIso1.addSelector('antiIso1EEEEosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso1EEEE DiEleCreation',1)
EEEEantiIso1.addDiCandidateModule('antiIso1EEEEzzCands','PATEleEleEleEleQuadProducer','antiIso1EEEEosDiElectrons','antiIso1EEEEdiElectrons','smearedMET','smearedJets',1,9999,text='antiIso1EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEEantiIso1.addCrossCleanerModule('antiIso1EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='antiIso1EEEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEEantiIso1.addSelector('antiIso1EEEEzzEleIso','PATEleEleEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1EEEELeadingZEleIso')
EEEEantiIso1.addSelector('antiIso1EEEEz2Charge','PATEleEleEleEleQuadSelector','leg2.charge()==0','antiIso1EEEEsecondLegEleCiCTight')
EEEEantiIso1.addSelector('antiIso1EEEEpt','PATEleEleEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg1.leg2.pt()>10&&leg2.leg2.pt()>10','antiIso1EEEEsecondLegEleCiCTight')
EEEEantiIso1.addSelector('antiIso1EEEEzzdZ','PATEleEleEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEEdZ')
EEEEantiIso1.addSelector('EEEEnoIsoOSF','PATEleEleEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','antiIso1EEEEsecondLegEleCiCTight')
EEEEantiIso1.addSorter('antiIso1EEEEsorted','PATEleEleEleEleQuadSorterByZMass')
EEEEantiIso1.addSelector('EEEEantiIso1F','PATEleEleEleEleQuadSelector','(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','antiIso1EEEESecondZEleIso')
EEEEantiIso1Seq =EEEEantiIso1.returnSequence()

EEEEnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsEEEESS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEEnoIsoSS.addDiCandidateModule('noIsoSSEEEEdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEEnoIsoSS.addSelector('noIsoSSEEEEDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','noIsoSSEEEE DiEleCreation',1)
EEEEnoIsoSS.addSelector('noIsoSSEEEEosDiElectrons','PATElePairSelector','charge()==0','noIsoSSEEEE DiEleCreation',1)
EEEEnoIsoSS.addDiCandidateModule('noIsoSSEEEEzzCands','PATEleEleEleEleQuadProducer','noIsoSSEEEEosDiElectrons','noIsoSSEEEEdiElectrons','smearedMET','smearedJets',1,9999,text='noIsoSSEEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEEnoIsoSS.addCrossCleanerModule('noIsoSSEEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='noIsoSSEEEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEEnoIsoSS.addSelector('noIsoSSEEEEzzEleIso','PATEleEleEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSEEEELeadingZEleIso')
EEEEnoIsoSS.addSelector('noIsoSSEEEEz2Charge','PATEleEleEleEleQuadSelector','leg2.charge()!=0','noIsoSSEEEEsecondLegEleCiCTight')
EEEEnoIsoSS.addSorter('noIsoSSEEEEsorted','PATEleEleEleEleQuadSorterByZMass')
EEEEnoIsoSS.addSelector('noIsoSSEEEEzzdZ','PATEleEleEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEEdZ')
EEEEnoIsoSS.addSelector('EEEEnoIsoSSF','PATEleEleEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','noIsoSSEEEEsecondLegEleCiCTight')
EEEEnoIsoSS.addSelector('EEEEnoIsoSScheckF','PATEleEleEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','noIsoSSEEEEsecondLegEleCiCTight')
EEEEnoIsoSSSeq =EEEEnoIsoSS.returnSequence()

EEEEantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsEEEE2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEEantiIso2.addDiCandidateModule('antiIso2EEEEdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEEantiIso2.addSelector('antiIso2EEEEosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso2EEEE DiEleCreation',1)
EEEEantiIso2.addDiCandidateModule('antiIso2EEEEzzCands','PATEleEleEleEleQuadProducer','antiIso2EEEEosDiElectrons','antiIso2EEEEdiElectrons','smearedMET','smearedJets',1,9999,text='antiIso2EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEEantiIso2.addCrossCleanerModule('antiIso2EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='antiIso2EEEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEEantiIso2.addSelector('antiIso2EEEEzzEleIso','PATEleEleEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2EEEELeadingZEleIso')
EEEEantiIso2.addSelector('antiIso2EEEEzzEleIDSecond','PATEleEleEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','antiIso2EEEEsecondLegEleCiCTight')
EEEEantiIso2.addSelector('antiIso2EEEEpt','PATEleEleEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg1.leg2.pt()>10&&leg2.leg2.pt()>10','antiIso2EEEEsecondLegEleCiCTight')
EEEEantiIso2.addSelector('antiIso2EEEEz2Charge','PATEleEleEleEleQuadSelector','leg2.charge()==0','antiIso2EEEEsecondLegEleCiCTight')
EEEEantiIso2.addSorter('antiIso2EEEEsorted','PATEleEleEleEleQuadSorterByZMass')
EEEEantiIso2.addSelector('antiIso2EEEEzzdZ','PATEleEleEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEEdZ')
EEEEantiIso2.addSelector('EEEEantiIso2F','PATEleEleEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25','antiIsoEEEESecondZEleIso')
EEEEantiIso2Seq =EEEEantiIso2.returnSequence()

EEEEantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsEEEEBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEEantiIsoBoth.addDiCandidateModule('antiIsoBothEEEEdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEEEantiIsoBoth.addSelector('antiIsoBothEEEEosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothEEEE DiEleCreation',1)
EEEEantiIsoBoth.addDiCandidateModule('antiIsoBothEEEEzzCands','PATEleEleEleEleQuadProducer','antiIsoBothEEEEosDiElectrons','antiIsoBothEEEEdiElectrons','smearedMET','smearedJets',1,9999,text='antiIsoBothEEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEEantiIsoBoth.addCrossCleanerModule('antiIsoBothEEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='antiIsoBothEEEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEEantiIsoBoth.addSelector('antiIsoBothEEEEzzEleIso','PATEleEleEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothEEEELeadingZEleIso')
EEEEantiIsoBoth.addSelector('antiIsoBothEEEEzzEleIDSecond','PATEleEleEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','antiIsoBothEEEEsecondLegEleCiCTight')
EEEEantiIsoBoth.addSelector('antiIsoBothEEEEpt','PATEleEleEleEleQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg1.leg2.pt()>10&&leg2.leg2.pt()>10','antiIsoBothEEEEsecondLegEleCiCTight')
EEEEantiIsoBoth.addSorter('antiIsoBothEEEEsorted','PATEleEleEleEleQuadSorterByZMass')
EEEEantiIsoBoth.addSelector('antiIsoBothEEEEzzdZ','PATEleEleEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEEdZ')
EEEEantiIsoBoth.addSelector('EEEEantiIsoBothF','PATEleEleEleEleQuadSelector','leg2.charge()==0','antiIsoBothEEEEsecondLegEleCiCTight')
#EEEEantiIsoBoth.addSelector('EEEEantiIsoBothF','PATEleEleEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()>0.25','antiIsoEEEESecondZEleIso')
EEEEantiIsoBothSeq =EEEEantiIsoBoth.returnSequence()

######################__________________________________EEMM_____________________________________##############################

EEMMantiIso1 = CutSequenceProducer(initialCounter  = 'initialEventsEEMM',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMMantiIso1.addDiCandidateModule('antiIso1EEMMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMMantiIso1.addSelector('antiIso1EEMMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso1EEMM DiEleCreation',1)
EEMMantiIso1.addDiCandidateModule('antiIso1EEMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1)
EEMMantiIso1.addDiCandidateModule('antiIso1EEMMzzCands','PATEleEleMuMuQuadProducer','antiIso1EEMMosDiElectrons','antiIso1EEMMdiMuons','smearedMET','smearedJets',1,9999,text='antiIso1EEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMMantiIso1.addCrossCleanerModule('antiIso1EEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='antiIso1EEMMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMMantiIso1.addSelector('antiIso1EEMMzzEleIso','PATEleEleMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso1EEMMLeadingZEleIso')
EEMMantiIso1.addSelector('antiIso1EEMMz2Charge','PATEleEleMuMuQuadSelector','leg2.charge()==0','antiIso1EEMMsecondPairID')
EEMMantiIso1.addSelector('antiIso1EEMMpt','PATEleEleMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso1EEMMsecondPairID')
EEMMantiIso1.addSorter('antiIso1EEMMsorted','PATEleEleMuMuQuadSorterByZMass')
EEMMantiIso1.addSelector('antiIso1EEMMzzdZ','PATEleEleMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMMdZ')
EEMMantiIso1.addSelector('EEMMnoIsoOSF','PATEleEleMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','antiIso1EEMMsecondPairID')
EEMMantiIso1.addSelector('EEMMantiIso1F','PATEleEleMuMuQuadSelector','(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','antiIso1EEMMLeadingZMuIso')
EEMMantiIso1Seq =EEMMantiIso1.returnSequence()

EEMMnoIsoSS = CutSequenceProducer(initialCounter  = 'initialEventsEEMMSS',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMMnoIsoSS.addDiCandidateModule('noIsoSSEEMMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMMnoIsoSS.addSelector('noIsoSSEEMMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','noIsoSSEEMM DiEleCreation',1)
EEMMnoIsoSS.addDiCandidateModule('noIsoSSEEMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1)
EEMMnoIsoSS.addDiCandidateModule('noIsoSSEEMMzzCands','PATEleEleMuMuQuadProducer','noIsoSSEEMMosDiElectrons','noIsoSSEEMMdiMuons','smearedMET','smearedJets',1,9999,text='noIsoSSEEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMMnoIsoSS.addCrossCleanerModule('noIsoSSEEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='noIsoSSEEMMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMMnoIsoSS.addSelector('noIsoSSEEMMzzEleIso','PATEleEleMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','noIsoSSEEMMLeadingZEleIso')
EEMMnoIsoSS.addSelector('noIsoSSEEMMz2Charge','PATEleEleMuMuQuadSelector','leg2.charge()!=0','noIsoSSEEMMsecondPairID')
EEMMnoIsoSS.addSorter('noIsoSSEEMMsorted','PATEleEleMuMuQuadSorterByZMass')
EEMMnoIsoSS.addSelector('noIsoSSEEMMzzdZ','PATEleEleMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMMdZ')
EEMMnoIsoSS.addSelector('EEMMnoIsoSSF','PATEleEleMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','noIsoSSEEMMsecondPairID')
EEMMnoIsoSS.addSelector('EEMMnoIsoSScheckF','PATEleEleMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','noIsoSSEEMMsecondPairID')
EEMMnoIsoSSSeq =EEMMnoIsoSS.returnSequence()

EEMMantiIso2 = CutSequenceProducer(initialCounter  = 'initialEventsEEMM2',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMMantiIso2.addDiCandidateModule('antiIso2EEMMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMMantiIso2.addSelector('antiIso2EEMMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIso2EEMM DiEleCreation',1)
EEMMantiIso2.addDiCandidateModule('antiIso2EEMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1)
EEMMantiIso2.addDiCandidateModule('antiIso2EEMMzzCands','PATEleEleMuMuQuadProducer','antiIso2EEMMosDiElectrons','antiIso2EEMMdiMuons','smearedMET','smearedJets',1,9999,text='antiIso2EEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMMantiIso2.addCrossCleanerModule('antiIso2EEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='antiIso2EEMMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMMantiIso2.addSelector('antiIso2EEMMzzEleIso','PATEleEleMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIso2EEMMLeadingZEleIso')
EEMMantiIso2.addSelector('antiIso2EEMMzzMuIDSecondPair','PATEleEleMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','antiIso2EEMMsecondPairID')
EEMMantiIso2.addSelector('antiIso2EEMMpt','PATEleEleMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIso2EEMMsecondPairID')
EEMMantiIso2.addSelector('antiIso2EEMMz2Charge','PATEleEleMuMuQuadSelector','leg2.charge()==0','antiIso2EEMMsecondPairID')
EEMMantiIso2.addSorter('antiIso2EEMMsorted','PATEleEleMuMuQuadSorterByZMass')
EEMMantiIso2.addSelector('antiIso2EEMMzzdZ','PATEleEleMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMMdZ')
EEMMantiIso2.addSelector('EEMMantiIso2F','PATEleEleMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25','antiIsoEEMMLeadingZMuIso')
EEMMantiIso2Seq =EEMMantiIso2.returnSequence()

EEMMantiIsoBoth = CutSequenceProducer(initialCounter  = 'initialEventsEEMMBoth',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMMantiIsoBoth.addDiCandidateModule('antiIsoBothEEMMdiElectrons','PATElePairProducer', 'smearedElectrons','smearedElectrons','smearedMET','smearedJets',1,genParticles='genDaughters')
EEMMantiIsoBoth.addSelector('antiIsoBothEEMMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>60&&mass<120&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','antiIsoBothEEMM DiEleCreation',1)
EEMMantiIsoBoth.addDiCandidateModule('antiIsoBothEEMMdiMuons','PATMuPairProducer', 'smearedMuons','smearedMuons','smearedMET','smearedJets',1)
EEMMantiIsoBoth.addDiCandidateModule('antiIsoBothEEMMzzCands','PATEleEleMuMuQuadProducer','antiIsoBothEEMMosDiElectrons','antiIsoBothEEMMdiMuons','smearedMET','smearedJets',1,9999,text='antiIsoBothEEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMMantiIsoBoth.addCrossCleanerModule('antiIsoBothEEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='antiIsoBothEEMMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMMantiIsoBoth.addSelector('antiIsoBothEEMMzzEleIso','PATEleEleMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','antiIsoBothEEMMLeadingZEleIso')
EEMMantiIsoBoth.addSelector('antiIsoBothEEMMzzMuIDSecondPair','PATEleEleMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','antiIsoBothEEMMsecondPairID')
EEMMantiIsoBoth.addSelector('antiIsoBothEEMMpt','PATEleEleMuMuQuadSelector','leg1.leg1.pt()>20&&leg1.leg2.pt()>10&&leg2.leg1.pt()>10&&leg2.leg2.pt()>10','antiIsoBothEEMMsecondPairID')
EEMMantiIsoBoth.addSorter('antiIsoBothEEMMsorted','PATEleEleMuMuQuadSorterByZMass')
EEMMantiIsoBoth.addSelector('antiIsoBothEEMMzzdZ','PATEleEleMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMMdZ')
EEMMantiIsoBoth.addSelector('EEMMantiIsoBothF','PATEleEleMuMuQuadSelector','leg2.charge()==0','antiIsoBothEEMMsecondPairID')
#EEMMantiIsoBoth.addSelector('EEMMantiIsoBothF','PATEleEleMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()>0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()>0.25','antiIsoEEMMLeadingZMuIso')
EEMMantiIsoBothSeq =EEMMantiIsoBoth.returnSequence()

# add in fourL states for vetoing

MMEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMEEFull',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMEEanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMEE')
MMEEanalysisConfigurator.addDiCandidateModule('MMEEdiMuons','PATMuPairProducer', 'smearedMuonsMMEE','smearedMuonsMMEE','smearedMETMMEE','smearedJetsMMEE',1,genParticles='genDaughters')
MMEEanalysisConfigurator.addSelector('MMEEosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMEE DiMuonCreation',1)
MMEEanalysisConfigurator.addDiCandidateModule('MMEEeleEle','PATElePairProducer','smearedElectronsMMEE','smearedElectronsMMEE','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneEleEle',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEanalysisConfigurator.addDiCandidateModule('MMEEzzCands','PATMuMuEleEleQuadProducer','MMEEosDiMuons','MMEEeleEle','smearedMETMMEE','smearedJetsMMEE',1,9999,text='MMEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMEEanalysisConfigurator.addCrossCleanerModule('MMEEzzCleanedCands','PATMuMuEleEleQuadCrossCleaner',1,9999,text='MMEEAtLeastOneZZCleanedCandidate',dR = 0.1)
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedMuID','PATMuMuEleEleQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMEELeadingZMuID')
MMEEanalysisConfigurator.addSelector('MMEEzzMuIso','PATMuMuEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMEELeadingZMuIso')
MMEEanalysisConfigurator.addSelector('MMEEzzEleId','PATMuMuEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','MMEEEleCiCTight') 
MMEEanalysisConfigurator.addSelector('MMEEzzEleIso','PATMuMuEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','MMEEZEleIso')
MMEEanalysisConfigurator.addSorter('MMEEzzCleanedCandsSortedByZMass','PATMuMuEleEleQuadSorterByZMass')
MMEEanalysisConfigurator.addSelector('MMEEzzdZ','PATMuMuEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMEEdZ')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedCandsAboveThreshold','PATMuMuEleEleQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>7 &&leg2().leg2().pt()>7 && abs(leg2.leg1.eta())<2.5 && abs(leg2.leg2.eta())<2.5','MMEEAtLeastOneZZCandOverThresholds')
MMEEanalysisConfigurator.addSelector('MMEEzzCleanedCandsEleEleQ','PATMuMuEleEleQuadSelector','leg2.charge()==0','EleEleCharge')
MMEEanalysisConfigurator.addSorter('MMEEFinalSel','PATMuMuEleEleQuadSorterByZMass')
MMEEselectionSequence =MMEEanalysisConfigurator.returnSequence()

MMMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsMMMMFull',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())

MMMManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','MMMM')
MMMManalysisConfigurator.addDiCandidateModule('MMMMdiMuons','PATMuPairProducer', 'smearedMuonsMMMM','smearedMuonsMMMM','smearedMETMMMM','smearedJetsMMMM',1,genParticles='genDaughters')
MMMManalysisConfigurator.addSelector('MMMMosDiMuons','PATMuPairSelector','charge==0&&leg1.isGlobalMuon()&&leg2.isGlobalMuon()&& mass>40 && abs(leg1.eta())<2.4 && abs(leg2.eta())<2.4&&leg1.pt()>20&&leg2.pt()>10','MMMM DiMuonCreation',1)
MMMManalysisConfigurator.addDiCandidateModule('MMMMzzCands','PATMuMuMuMuQuadProducer','MMMMosDiMuons','MMMMdiMuons','smearedMETMMMM','smearedJetsMMMM',1,9999,text='MMMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
MMMManalysisConfigurator.addCrossCleanerModule('MMMMzzCleanedCands','PATMuMuMuMuQuadCrossCleaner',1,9999,text='MMMMAtLeastOneZZCleanedCandidate',dR = 0.1)
MMMManalysisConfigurator.addSelector('MMMMzzCleanedMuID','PATMuMuMuMuQuadSelector','leg1.leg1.isGlobalMuon()&&leg1.leg1.isTrackerMuon()&&leg1.leg2.isTrackerMuon()&&leg1.leg2.isTrackerMuon()','MMMMLeadingZMuID')
MMMManalysisConfigurator.addSelector('MMMMzzMuIso','PATMuMuMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','MMMMLeadingZMuIso')
MMMManalysisConfigurator.addSelector('MMMMzzMuIDSecondPair','PATMuMuMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','MMMMsecondPairID')
MMMManalysisConfigurator.addSelector('MMMMzzMuIso2','PATMuMuMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','MMMMSecondZMuIso')
MMMManalysisConfigurator.addSorter('MMMMzzCleanedCandsSortedByZMass','PATMuMuMuMuQuadSorterByZMass')
MMMManalysisConfigurator.addSelector('MMMMzzdZ','PATMuMuMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','MMMMdZ')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedCandsAboveThreshold','PATMuMuMuMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>5 &&leg2().leg2().pt()>5 && abs(leg2.leg1.eta())<2.4 && abs(leg2.leg2.eta())<2.4','MMMMAtLeastOneZZCandOverThresholds')
MMMManalysisConfigurator.addSelector('MMMMzzCleanedCandsMuMuQ','PATMuMuMuMuQuadSelector','leg2.charge()==0','MMMMSecondZCharge')
MMMManalysisConfigurator.addSorter('MMMMFinalSel','PATMuMuMuMuQuadSorterByZMass')
MMMMselectionSequence =MMMManalysisConfigurator.returnSequence()


EEEEanalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEEEFull',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEEEanalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEEE')
EEEEanalysisConfigurator.addDiCandidateModule('EEEEdiElectrons','PATElePairProducer', 'smearedElectronsEEEE','smearedElectronsEEEE','smearedMETEEEE','smearedJetsEEEE',1,genParticles='genDaughters')
EEEEanalysisConfigurator.addSelector('EEEEosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>40&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','EEEE DiEleCreation',1)
EEEEanalysisConfigurator.addDiCandidateModule('EEEEzzCands','PATEleEleEleEleQuadProducer','EEEEosDiElectrons','EEEEdiElectrons','smearedMETEEEE','smearedJetsEEEE',1,9999,text='EEEEAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEEEanalysisConfigurator.addCrossCleanerModule('EEEEzzCleanedCands','PATEleEleEleEleQuadCrossCleaner',1,9999,text='EEEEAtLeastOneZZCleanedCandidate',dR = 0.1)
EEEEanalysisConfigurator.addSelector('EEEEzzEleIso','PATEleEleEleEleQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','EEEELeadingZEleIso')
EEEEanalysisConfigurator.addSelector('EEEEzzEleIDSecond','PATEleEleEleEleQuadSelector','((leg2.leg1.electronID("cicTight")==1||leg2.leg1.electronID("cicTight")==3||leg2.leg1.electronID("cicTight")==5||leg2.leg1.electronID("cicTight")==7||leg2.leg1.electronID("cicTight")==9||leg2.leg1.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg1.electronID("cicTight")==15)&&(leg2.leg2.electronID("cicTight")==1||leg2.leg2.electronID("cicTight")==3||leg2.leg2.electronID("cicTight")==5||leg2.leg2.electronID("cicTight")==7||leg2.leg2.electronID("cicTight")==9||leg2.leg2.electronID("cicTight")==11||leg2.leg1.electronID("cicTight")==13||leg2.leg2.electronID("cicTight")==15))','EEEEsecondLegEleCiCTight')
EEEEanalysisConfigurator.addSelector('EEEEzzEleIso2','PATEleEleEleEleQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','EEEESecondZEleIso')
EEEEanalysisConfigurator.addSorter('EEEEzzCleanedCandsSortedByZMass','PATEleEleEleEleQuadSorterByZMass')
EEEEanalysisConfigurator.addSelector('EEEEzzdZ','PATEleEleEleEleQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEEEdZ')
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedCandsAboveThreshold','PATEleEleEleEleQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>7 &&leg2().leg2().pt()>7 && abs(leg2.leg2.eta())<2.5 && abs(leg2.leg2.eta())<2.5','EEEEAtLeastOneZZCandOverThresholds')
EEEEanalysisConfigurator.addSelector('EEEEzzCleanedCandsEleEleQ','PATEleEleEleEleQuadSelector','leg2.charge()==0','EEEESecondZCharge')
EEEEanalysisConfigurator.addSorter('EEEEFinalSel','PATEleEleEleEleQuadSorterByZMass')

EEEEselectionSequence =EEEEanalysisConfigurator.returnSequence()


EEMManalysisConfigurator = CutSequenceProducer(initialCounter  = 'initialEventsEEMMFull',
                                  pyModuleName = __name__,
                                  pyNameSpace  = locals())
EEMManalysisConfigurator.addSmearing('patOverloadedTaus','patMuonsForAnalysis','convRejElectrons','selectedPatJets','EEMM')
EEMManalysisConfigurator.addDiCandidateModule('EEMMdiElectrons','PATElePairProducer', 'smearedElectronsEEMM','smearedElectronsEEMM','smearedMETEEMM','smearedJetsEEMM',1,genParticles='genDaughters')
EEMManalysisConfigurator.addSelector('EEMMosDiElectrons','PATElePairSelector','leg1.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&leg2.gsfTrack().trackerExpectedHitsInner().numberOfHits()<2&&(leg1.electronID("cicTight")==1||leg1.electronID("cicTight")==3||leg1.electronID("cicTight")==5||leg1.electronID("cicTight")==7||leg1.electronID("cicTight")==9||leg1.electronID("cicTight")==11||leg1.electronID("cicTight")==13||leg1.electronID("cicTight")==15)&&(leg2.electronID("cicTight")==1||leg2.electronID("cicTight")==3||leg2.electronID("cicTight")==5||leg2.electronID("cicTight")==7||leg2.electronID("cicTight")==9||leg2.electronID("cicTight")==11||leg2.electronID("cicTight")==13||leg2.electronID("cicTight")==15)&&charge==0&&mass>40&&abs(leg1.eta())<2.5&&abs(leg2.eta())<2.5&&leg1.pt()>20&&leg2.pt()>10','EEMM DiEleCreation',1)
EEMManalysisConfigurator.addDiCandidateModule('EEMMdiMuons','PATMuPairProducer', 'smearedMuonsEEMM','smearedMuonsEEMM','smearedMETEEMM','smearedJetsEEMM',1)
EEMManalysisConfigurator.addDiCandidateModule('EEMMzzCands','PATEleEleMuMuQuadProducer','EEMMosDiElectrons','EEMMdiMuons','smearedMETEEMM','smearedJetsEEMM',1,9999,text='EEMMAtLeastOneZZ',leadingObjectsOnly = False,dR = 0.5,recoMode ="",genParticles='genDaughters')
EEMManalysisConfigurator.addCrossCleanerModule('EEMMzzCleanedCands','PATEleEleMuMuQuadCrossCleaner',1,9999,text='EEMMAtLeastOneZZCleanedCandidate',dR = 0.1)
EEMManalysisConfigurator.addSelector('EEMMzzEleIso','PATEleEleMuMuQuadSelector','(leg1.leg1.chargedHadronIso()+max(leg1.leg1.photonIso()+leg1.leg1.neutralHadronIso()-0.5*leg1.leg1.userIso(0),0.0))/leg1.leg1.pt()<0.25&&(leg1.leg2.chargedHadronIso()+max(leg1.leg2.photonIso()+leg1.leg2.neutralHadronIso()-0.5*leg1.leg2.userIso(0),0.0))/leg1.leg2.pt()<0.25','EEMMLeadingZEleIso')
#EEMManalysisConfigurator.addSelector('EEMMzzMuMuMass','PATEleEleMuMuQuadSelector','leg2.mass<60','EEMMmumuMass')
EEMManalysisConfigurator.addSelector('EEMMzzMuIDSecondPair','PATEleEleMuMuQuadSelector','leg2.leg1.isGlobalMuon()&&leg2.leg2.isGlobalMuon()&&leg2.leg1.isTrackerMuon()&&leg2.leg2.isTrackerMuon()','EEMMsecondPairID')
EEMManalysisConfigurator.addSelector('EEMMzzMuIso2','PATEleEleMuMuQuadSelector','(leg2.leg1.chargedHadronIso()+max(leg2.leg1.photonIso()+leg2.leg1.neutralHadronIso()-0.5*leg2.leg1.userIso(0),0.0))/leg2.leg1.pt()<0.25&&(leg2.leg2.chargedHadronIso()+max(leg2.leg2.photonIso()+leg2.leg2.neutralHadronIso()-0.5*leg2.leg2.userIso(0),0.0))/leg2.leg2.pt()<0.25','EEMMLeadingZMuIso')
EEMManalysisConfigurator.addSorter('EEMMzzCleanedCandsSortedByZMass','PATEleEleMuMuQuadSorterByZMass')
EEMManalysisConfigurator.addSelector('EEMMzzdZ','PATEleEleMuMuQuadSelector','abs(leg1.z1-leg1.z2)<0.1&&abs(leg1.z1-leg2.z1)<0.1&&abs(leg1.z1-leg2.z2)<0.1','EEMMdZ')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedCandsAboveThreshold','PATEleEleMuMuQuadSelector','leg1().leg1().pt()>20 && leg1().leg2().pt()>10 && leg2().leg1().pt()>5 &&leg2().leg2().pt()>5 && abs(leg2.leg2.eta())<2.5 && abs(leg2.leg2.eta())<2.5','EEMMAtLeastOneZZCandOverThresholds')
EEMManalysisConfigurator.addSelector('EEMMzzCleanedCandsMuMuQ','PATEleEleMuMuQuadSelector','leg2.charge()==0','EEMMSecondZCharge')
EEMManalysisConfigurator.addSorter('EEMMFinalSel','PATEleEleMuMuQuadSorterByZMass')
EEMMselectionSequence =EEMManalysisConfigurator.returnSequence()
#####################_______________________________EndOfConfigurators__________________________################################

